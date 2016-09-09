// // Copyright (c) 2005, 2006 Fernando Luis Cacciola Carballal. All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/Straight_skeleton_2/include/CGAL/Straight_skeleton_2/Straight_skeleton_builder_2_impl.h $
// $Id: Straight_skeleton_builder_2_impl.h 37144 2007-03-16 08:17:51Z afabri $
//
// Author(s)     : Fernando Cacciola <fernando_cacciola@ciudad.com.ar>
//
#ifndef CGAL_STRAIGHT_SKELETON_BUILDER_2_IMPL_H
#define CGAL_STRAIGHT_SKELETON_BUILDER_2_IMPL_H 1

#include <boost/bind.hpp>
#include <boost/utility.hpp>
#include <boost/graph/adjacency_matrix.hpp>
#include <CGAL/Unique_hash_map.h>

#include <CGAL/Real_timer.h>

#if defined(BOOST_MSVC)
#  pragma warning(push)
#  pragma warning(disable:4355) // complaint about using 'this' to
#endif                          // initialize a member

CGAL_BEGIN_NAMESPACE

namespace {

template<class Handle> inline bool handle_assigned ( Handle const& aH )
{
  Handle null ;
  return aH != null ;
}

}


template<class Gt, class SS, class V>
Straight_skeleton_builder_2<Gt,SS,V>::Straight_skeleton_builder_2 ( Traits const& aTraits, Visitor const& aVisitor )
  :
  mTraits(aTraits)
 ,mVisitor(aVisitor)
 ,mEventCompare(this)
 ,mVertexID(0)
 ,mEdgeID(0)
 ,mEventID(0)
 ,mStepID(0)
 ,mPQ(mEventCompare)
 ,mSSkel( new SSkel() )
{
}

// This is defined out-of-class, here, just so it's easy to set a breakpoint
template<class Gt, class SS, class V>
void Straight_skeleton_builder_2<Gt,SS,V>::throw_error ( char const* what ) const
{
  throw straight_skeleton_exception(what);
}

template<class Gt, class SS, class V>
void Straight_skeleton_builder_2<Gt,SS,V>::InsertEventInPQ( EventPtr aEvent )
{
  mPQ.push(aEvent);
  CGAL_STSKEL_BUILDER_TRACE(2, "Main PQ: " << *aEvent);
}

template<class Gt, class SS, class V>
typename Straight_skeleton_builder_2<Gt,SS,V>::EventPtr 
Straight_skeleton_builder_2<Gt,SS,V>::PopEventFromPQ()
{
  EventPtr rR = mPQ.top(); mPQ.pop();
  return rR ;
}

// Tests whether there is an edge event between the 3 contour edges defining nodes 'aLnode' and 'aRNode'.
// If such event exits and is not in the past, it's returned. Otherwise the result is null
//
template<class Gt, class SS, class V>
typename Straight_skeleton_builder_2<Gt,SS,V>::EventPtr
Straight_skeleton_builder_2<Gt,SS,V>::FindEdgeEvent( Vertex_handle aLNode, Vertex_handle aRNode )
{
  EventPtr rResult ;
 
  Triedge lTriedge = GetTriedge(aLNode) & GetTriedge(aRNode) ;
  
  if ( lTriedge.is_valid() )
  {
    Seeded_trisegment_2 lSTrisegment = CreateSeededTrisegment(lTriedge,aLNode,aRNode);
    
    if ( ExistEvent(lSTrisegment) )
    {
      bool lAccepted = true ;

      if ( IsNewEventInThePast(lSTrisegment,aLNode) )
        lAccepted = false ;

      if ( IsNewEventInThePast(lSTrisegment,aRNode) )
        lAccepted = false ;

      if ( lAccepted )
      {
        rResult = EventPtr( new EdgeEvent( lTriedge, lSTrisegment, aLNode, aRNode ) ) ;

        mVisitor.on_edge_event_created(aLNode, aRNode) ;
        
        CGAL_STSKEL_DEBUG_CODE( SetEventTimeAndPoint(*rResult) );
      }
    }
  }
  return rResult ;
}

template<class Gt, class SS, class V>
bool Straight_skeleton_builder_2<Gt,SS,V>::IsInverseSplitEventCoincident( Vertex_handle const&        aReflexOppN 
                                                                        , Triedge const&              aEventTriedge
                                                                        , Seeded_trisegment_2 const&  aEventSTrisegment
                                                                        )
{
  Triedge lOppTriedge = GetTriedge(aReflexOppN);
  
  Triedge lOppLTriedge(lOppTriedge.e0(),lOppTriedge.e1(),aEventTriedge.e0());
  Triedge lOppRTriedge(lOppTriedge.e0(),lOppTriedge.e1(),aEventTriedge.e1());
  
  Vertex_handle null ;
  
  Seeded_trisegment_2 lOppLSTrisegment = CreateSeededTrisegment(lOppLTriedge,aReflexOppN,null);
  Seeded_trisegment_2 lOppRSTrisegment = CreateSeededTrisegment(lOppRTriedge,aReflexOppN,null);

  return (  (  lOppLSTrisegment.event().collinearity() != TRISEGMENT_COLLINEARITY_02 
            && ExistEvent(lOppLSTrisegment) 
            && AreEventsSimultaneous(aEventSTrisegment,lOppLSTrisegment) 
            )
         || (  lOppRSTrisegment.event().collinearity() != TRISEGMENT_COLLINEARITY_02 
            && ExistEvent(lOppRSTrisegment) 
            && AreEventsSimultaneous(aEventSTrisegment,lOppRSTrisegment) 
            )
         ) ;
}

template<class Gt, class SS, class V>
typename Straight_skeleton_builder_2<Gt,SS,V>::EventPtr 
Straight_skeleton_builder_2<Gt,SS,V>::IsPseudoSplitEvent( EventPtr const& aEvent, Vertex_handle aOppN )
{
  bool lIsPseudoSplitEvent = false ;
  bool lCoupleIsPrev       = false ;

  SplitEvent& lEvent = dynamic_cast<SplitEvent&>(*aEvent) ;
  
  Triedge              lEventTriedge     = lEvent.triedge();
  Seeded_trisegment_2  lEventSTrisegment = lEvent.strisegment();
  Vertex_handle        lSeedN            = lEvent.seed0();
  
  Vertex_handle lOppPrevN = GetPrevInLAV(aOppN) ;       
  
  if ( IsReflex(lOppPrevN) && IsInverseSplitEventCoincident(lOppPrevN,lEventTriedge,lEventSTrisegment) )
  {
    lIsPseudoSplitEvent = true ;
    lCoupleIsPrev       = true ;
    CGAL_STSKEL_BUILDER_TRACE(1,"Pseudo-split-event found against N" << lOppPrevN->id() ) ;
  }
  else if ( IsReflex(aOppN) && IsInverseSplitEventCoincident(aOppN,lEventTriedge,lEventSTrisegment) )
  {
    lIsPseudoSplitEvent = true ;
    lCoupleIsPrev       = false ;
    CGAL_STSKEL_BUILDER_TRACE(1,"Pseudo-split-event found against E" << aOppN->id() ) ;
  }

  EventPtr rPseudoSplitEvent ;

  if ( lIsPseudoSplitEvent )
  {
    if ( lCoupleIsPrev )
    {
      rPseudoSplitEvent = EventPtr( new PseudoSplitEvent(lEventTriedge,lEventSTrisegment,lOppPrevN,lSeedN) ) ;

      mVisitor.on_pseudo_split_event_created(lOppPrevN,lSeedN) ;
    }
    else
    {
      rPseudoSplitEvent = EventPtr( new PseudoSplitEvent(lEventTriedge, lEventSTrisegment, lSeedN, aOppN) ) ;  

      mVisitor.on_pseudo_split_event_created(lSeedN,aOppN) ;
    }

    rPseudoSplitEvent->SetTimeAndPoint(aEvent->time(),aEvent->point());
  }

  return rPseudoSplitEvent ;
}

// Tests whether there is a split event between the contour edges (aReflexLBorder,aReflexRBorder,aOppositeBorder).
// If such event exits and is not in the past, it's returned. Otherwise the result is null
// 'aReflexLBorder' and 'aReflexRBorder' are consecutive contour edges which 'aNode' as the vertex.
// 'aOppositeBorder' is some other edge in the polygon which, if the event exists, is split by the reflex wavefront.
//
// NOTE: 'aNode' can be a skeleton node (an interior split event produced by a previous vertex event). In that case,
// the 'reflex borders' are not consecutive in the input polygon but they are in the corresponding offset polygon that
// contains aNode as a vertex.
//
template<class Gt, class SS, class V>
void Straight_skeleton_builder_2<Gt,SS,V>::CollectSplitEvent( Vertex_handle aNode, Triedge const& aTriedge )
{
  if ( IsOppositeEdgeFacingTheSplitSeed(aNode,aTriedge.e2()) )
  {
    Vertex_handle null ;
    
    Seeded_trisegment_2 lSTrisegment = CreateSeededTrisegment(aTriedge,aNode,null);
    
    if ( lSTrisegment.event().collinearity() != TRISEGMENT_COLLINEARITY_02 && ExistEvent(lSTrisegment) )
    {
      if ( !IsNewEventInThePast(lSTrisegment,aNode) )
      {
        EventPtr lEvent = EventPtr( new SplitEvent (aTriedge,lSTrisegment,aNode) ) ;
        
        mVisitor.on_split_event_created(aNode) ;
 
        CGAL_STSKEL_DEBUG_CODE( SetEventTimeAndPoint(*lEvent) ) ;
  
        AddSplitEvent(aNode,lEvent);      
      }
    }
  }
}

// Tests the reflex wavefront emerging from 'aNode' against the other contour edges in search for split events.
template<class Gt, class SS, class V>
void Straight_skeleton_builder_2<Gt,SS,V>::CollectSplitEvents( Vertex_handle aNode )
{
  // lLBorder and lRBorder are the consecutive contour edges forming the reflex wavefront.
  Triedge lTriedge = GetTriedge(aNode);
  
  Halfedge_handle lLBorder = lTriedge.e0();
  Halfedge_handle lRBorder = lTriedge.e1();
  
  // For a strictly simple polygon, without antennas, it can be shown that the reflex wavefront cannot split 
  // the edges adjacent to it (the prev and next of each wavefront edge), so these are excluded from the search.
  // (this is NOT an optimization, they must be excluded otherwise an illegal split event could be found)
  
  Vertex_handle lPrev = GetPrevInLAV(aNode) ;
  Vertex_handle lNext = GetNextInLAV(aNode) ;

  Halfedge_handle lLBorderP = lLBorder->opposite()->next()->opposite();
  Halfedge_handle lLBorderN = lLBorder->opposite()->prev()->opposite();
  Halfedge_handle lRBorderP = lRBorder->opposite()->next()->opposite();
  Halfedge_handle lRBorderN = lRBorder->opposite()->prev()->opposite();

  CGAL_STSKEL_BUILDER_TRACE(3
                      ,"Finding SplitEvent for N" << aNode->id()
                      << " LBorder: E" << lLBorder->id() << " RBorder: E" << lRBorder->id()
                      << " LBorderP: E" << lLBorderP->id() << " LBorderN: E" << lLBorderN->id()
                      << " RBorderP: E" << lRBorderP->id() << " RBorderN: E" << lRBorderN->id()
                      );

  for ( Halfedge_handle_vector_iterator i = mContourHalfedges.begin(); i != mContourHalfedges.end(); ++ i )
  {
    Halfedge_handle lOpposite = *i ;

    if (    lOpposite != lLBorder
         && lOpposite != lRBorder
         && lOpposite != lLBorderP
         && lOpposite != lLBorderN
         && lOpposite != lRBorderP
         && lOpposite != lRBorderN
       )
      CollectSplitEvent(aNode, Triedge(lLBorder, lRBorder, lOpposite) ) ;
  }
}


// Finds and enques all the new potential events produced by the vertex wavefront emerging from 'aNode' (which can be a reflex wavefront).
// This new events are simply stored in the priority queue, not processed.
template<class Gt, class SS, class V>
void Straight_skeleton_builder_2<Gt,SS,V>::CollectNewEvents( Vertex_handle aNode )
{
  // A Straight Skeleton is the trace of the 'grassfire propagation' that corresponds to the inward move of all the vertices 
  // of a polygon along their angular bisectors.
  // Since vertices are the common endpoints of contour edges, the propagation corresponds to contour edges moving inward,
  // shrinking and expanding as neccesasry to keep the vertices along the angular bisectors.
  // At each instant in time the current location of vertices (and edges) describe the current 'Offset polygon'
  // (with at time zero corresponds to the input polygon).
  // 
  // An 'edge wavefront' is a moving contour edge.
  // A 'vertex wavefront' is the wavefront of two consecutive edge wavefronts (sharing a moving vertex).
  //
  // An 'Event' is the coallision of 2 wavefronts.
  // Each event changes the topology of the shrinking polygon; that is, at the event, the current polygon differs from the
  // inmediately previous polygon in the number of vertices.
  //
  // If 2 vertex wavefronts sharing a common edge collide, the event is called an edge event. At the time of the event, the current
  // polygon doex not have the common edge anynmore, and the two vertices become one. This new 'skeleton' vertex generates a new
  // vertex wavefront which can further collide with other wavefronts, producing for instance, more edge events.
  //
  // If a refex vertex wavefront collide with an edge wavefront, the event is called a split event. At the time of the event, the current
  // polygon is split in two unconnected polygons, each one containing a portion of the edge hit and split by the reflex wavefront.
  //
  // If 2 reflex wavefronts collide each other, the event is called a vertex event. At the time of the event, the current polygon
  // is split in two unconnected polygons. Each one contains a different combination of the colliding reflex edges. That is, if the
  // wavefront (edgea,edgeb) collides with (edgec,edged), the two resulting polygons will contain (edgea,edgec) and (edgeb,edged).
  // Furthermore, one of the new vertices can be a reflex vertex generating a reflex wavefront which can further produce more split or
  // vertex events (or edge events of course)
  // 
  // Each vertex wavefront (reflex or not) results in one and only one event from a set of possible events.
  // It can result in a edge event against the vertex wavefronts emerging from the adjacent vertices (in the current polygon, not
  // in the input polygon); or it can result in a split event (or vertex event) against any other wavefront in the rest of 
  // current polygon.

  
  // Adjacent vertices in the current polygon containing aNode (called LAV)
  Vertex_handle lPrev = GetPrevInLAV(aNode) ;
  Vertex_handle lNext = GetNextInLAV(aNode) ;

  CGAL_STSKEL_BUILDER_TRACE
    ( 2
    , "Collecting new events generated by N" << aNode->id() << " at " << aNode->point() << " (Prev: N" << lPrev->id() << " Next: N"
       << lNext->id() << ")"
    ) ;

  if ( IsReflex(aNode) )
    CollectSplitEvents(aNode) ;
    
  EventPtr lLEdgeEvent = FindEdgeEvent( lPrev , aNode ) ;
  EventPtr lREdgeEvent = FindEdgeEvent( aNode , lNext ) ;

  bool lAcceptL = !!lLEdgeEvent ;
  bool lAcceptR = !!lREdgeEvent ;

  // Altough one and only one of the potential events actually happens, the ocurrence of a particular candidate is
  // determined by all the previous events. That is, at this point we may find that the vertex wavefront collides, for instance,
  // with both adjacent vertex wavefronts, thus encountering 2 potential edge events; however, we cannot rule out one of these
  // potential edge events based on the other because it is, precisely, potential. 
  // IOW, if event A happens before event B (for both A and B correspoding to the same wavefront), then for sure B won't happen; 
  // but at this point we can't tell whether A will actually ocurr so we can't discard B just yet. 
  // Both must be placed in the queue; if A is effectively processed, then B will naturally by ignored when it's pop off the queue.
  
  
  // But there is one exception to the "don't discard B yet" rule:
  // If A and B are coincident in time, their relative ordering in the queue is undetermined. Thus, 
  // the 'wrong' event could be pop off and processed first.
  // In this case, and only this case, we rule out B (the event that can't ocurr if A does)
  // TODO: This may be incorrect still... the priority queue should resolve the "second level" ordering in case of time coincidence.
  if ( lLEdgeEvent && lREdgeEvent )
  {
    Comparison_result lRel = CompareEvents(lLEdgeEvent,lREdgeEvent) ;
    if ( lRel == EQUAL )
    {
      if ( CompareEventsDistanceToSeed(aNode,lLEdgeEvent,lREdgeEvent) == LARGER )
           lAcceptL = false ;
      else lAcceptR = false ; 
    
      CGAL_STSKEL_BUILDER_TRACE(3,"Both Left and Right Edge Events found with the same time:"
                               << "LEvent:" << *lLEdgeEvent << '\n'
                               << "REvent:" << *lREdgeEvent << '\n'
                               << "Selecting the one closer to the seed: " << (lAcceptL ? "Left" : "Right") 
                               );
    }
  }
    
  if ( lAcceptL )
    InsertEventInPQ(lLEdgeEvent);
    
  if ( lAcceptR )
    InsertEventInPQ(lREdgeEvent);
}

// Handles the special case of two simultaneous edge events, that is, two edges
// collapsing along the line/point were they meet at the same time.
// This ocurrs when the bisector emerging from vertex 'aA' is defined by the same pair of 
// contour edges as the bisector emerging from vertex 'aB' (but in opposite order).
//
template<class Gt, class SS, class V>
void Straight_skeleton_builder_2<Gt,SS,V>::HandleSimultaneousEdgeEvent( Vertex_handle aA, Vertex_handle aB )
{
  CGAL_STSKEL_BUILDER_TRACE ( 2, "Handling simultaneous EdgeEvent between N" << aA ->id() << " and N"  << aB ->id() ) ;

  mVisitor.on_anihiliation_event_processed(aA,aB) ;

  Halfedge_handle lOA = aA->primary_bisector() ;
  Halfedge_handle lOB = aB->primary_bisector() ;
  Halfedge_handle lIA = lOA->opposite();
  Halfedge_handle lIB = lOB->opposite();

  CGAL_STSKEL_BUILDER_TRACE ( 2
                            ,    "OA: B" << lOA->id() << '\n'
                              << "IA: B" << lIA->id() << '\n'
                              << "OB: B" << lOB->id() << '\n'
                              << "IB: B" << lIB->id()
                            ) ;

  SetIsProcessed(aA) ;
  SetIsProcessed(aB) ;
  mSLAV.remove(aA);
  mSLAV.remove(aB);

  CGAL_STSKEL_BUILDER_TRACE ( 3, 'N' << aA->id() << " processed\nN" << aB->id() << " processed" ) ;

  Halfedge_handle lOA_Prev = lOA->prev() ;
  Halfedge_handle lIA_Next = lIA->next() ;

  Halfedge_handle lOB_Prev = lOB->prev() ;
  Halfedge_handle lIB_Next = lIB->next() ;

  CGAL_STSKEL_BUILDER_TRACE ( 2
                            ,   "OA_Prev: B" << lOA_Prev->id() << '\n'
                              << "IA_Next: B" << lIA_Next->id() << '\n'
                              << "OB_Prev: B" << lOB_Prev->id() << '\n'
                              << "IB_Next: B" << lIB_Next->id()
                           ) ;

  lOB     ->HBase_base::set_next( lIA_Next );
  lIA_Next->HBase_base::set_prev( lOB      );
  lIB     ->HBase_base::set_prev( lOA_Prev );
  lOA_Prev->HBase_base::set_next( lIB      );

  lOB->HBase_base::set_vertex  (aA);

  CGAL_STSKEL_BUILDER_TRACE ( 1, "B" << lOA->id() << " and B" << lIA->id() << " erased." ) ;
  mDanglingBisectors.push_back(lOA);

  //
  // The code above corrects the links for vertices aA/aB to the erased halfedges lOA and lIA.
  // However, any of these vertices (aA/aB) maybe one of the twin vertices of a split event.
  // If that's the case, the erased halfedge maybe be linked to a 'couple' of those vertices.
  // This situation is corrected below:

  if ( handle_assigned(lOA->vertex()) && lOA->vertex() != aA && lOA->vertex() != aB )
  {
    lOA->vertex()->VBase::set_halfedge(lIB);
    
    CGAL_STSKEL_BUILDER_TRACE ( 1, "N" << lOA->vertex()->id() << " has B" << lOA->id() 
                              << " as it's halfedge. Replacing it with B" << lIB->id() 
                              ) ;
  }
  if ( handle_assigned(lIA->vertex()) && lIA->vertex() != aA && lIA->vertex() != aB )
  {
    lIA->vertex()->VBase::set_halfedge(lOB);
    
    CGAL_STSKEL_BUILDER_TRACE ( 1, "N" << lIA->vertex()->id() << " has B" << lIA->id() 
                              << " as it's halfedge. Replacing it with B" << lOB->id() 
                              ) ;
  }

  CGAL_STSKEL_BUILDER_TRACE ( 2, "N" << aA->id() << " halfedge: B" << aA->halfedge()->id() ) ;
  CGAL_STSKEL_BUILDER_TRACE ( 2, "N" << aB->id() << " halfedge: B" << aB->halfedge()->id() ) ;

  CGAL_assertion( aA->primary_bisector() == lIB ) ;
}

// Returns true if the skeleton edges 'aA' and 'aB' are defined by the same pair of contour edges (but possibly in reverse order)
//
template<class Gt, class SS, class V>
bool Straight_skeleton_builder_2<Gt,SS,V>::AreBisectorsCoincident ( Halfedge_const_handle aA, Halfedge_const_handle aB  ) const
{
  CGAL_STSKEL_BUILDER_TRACE ( 3, "Testing for simultaneous EdgeEvents between B" << aA->id() << " and B" << aB->id() ) ;

  Halfedge_const_handle lA_LBorder = aA->defining_contour_edge();
  Halfedge_const_handle lA_RBorder = aA->opposite()->defining_contour_edge();
  Halfedge_const_handle lB_LBorder = aB->defining_contour_edge();
  Halfedge_const_handle lB_RBorder = aB->opposite()->defining_contour_edge();

  return    ( lA_LBorder == lB_LBorder && lA_RBorder == lB_RBorder )
         || ( lA_LBorder == lB_RBorder && lA_RBorder == lB_LBorder ) ;
}

template<class Gt, class SS, class V>
void Straight_skeleton_builder_2<Gt,SS,V>::UpdatePQ( Vertex_handle aNode )
{
  Vertex_handle lPrev = GetPrevInLAV(aNode) ;
  Vertex_handle lNext = GetNextInLAV(aNode) ;

  CGAL_STSKEL_BUILDER_TRACE ( 3, "Updating PQ for N" << aNode->id() << " Prev N" << lPrev->id() << " Next N" << lNext->id() ) ;

  Halfedge_handle lOBisector_P = lPrev->primary_bisector() ;
  Halfedge_handle lOBisector_C = aNode->primary_bisector() ;
  Halfedge_handle lOBisector_N = lNext->primary_bisector() ;

  if ( AreBisectorsCoincident(lOBisector_C,lOBisector_P) )
    HandleSimultaneousEdgeEvent( aNode, lPrev ) ;
  else
  if ( AreBisectorsCoincident(lOBisector_C,lOBisector_N) )
    HandleSimultaneousEdgeEvent( aNode, lNext ) ;
  else
     CollectNewEvents(aNode);
}
template<class Gt, class SS, class V>
void Straight_skeleton_builder_2<Gt,SS,V>::CreateInitialEvents()
{
  CGAL_STSKEL_BUILDER_TRACE(0, "Creating initial events...");
  for ( Vertex_iterator v = mSSkel->vertices_begin(); v != mSSkel->vertices_end(); ++ v )
  {
    UpdatePQ(v);
    mVisitor.on_initial_events_collected(v,IsReflex(v),IsDegenerate(v)) ;
  }
}


template<class Gt, class SS, class V>
void Straight_skeleton_builder_2<Gt,SS,V>::CreateContourBisectors()
{
  CGAL_STSKEL_BUILDER_TRACE(0, "Creating contour bisectors...");
  for ( Vertex_iterator v = mSSkel->vertices_begin(); v != mSSkel->vertices_end(); ++ v )
  {
    mSLAV.push_back(static_cast<Vertex_handle>(v));
    Vertex_handle lPrev = GetPrevInLAV(v) ;
    Vertex_handle lNext = GetNextInLAV(v) ;

    Orientation lOrientation = CGAL::orientation(lPrev->point(),v->point(),lNext->point()); 
    if ( lOrientation == COLLINEAR )
    {
      SetIsDegenerate(v);
      CGAL_STSKEL_BUILDER_TRACE(1, "COLLINEAR vertex: N" << v->id() );
    }
    else if ( lOrientation == RIGHT_TURN )
    {
      mReflexVertices.push_back(v);
      SetIsReflex(v);
      CGAL_STSKEL_BUILDER_TRACE(1,"Reflex vertex: N" << v->id() );
    }

    Halfedge lOB(mEdgeID++), lIB(mEdgeID++);
    Halfedge_handle lOBisector = mSSkel->SSkel::Base::edges_push_back (lOB, lIB);
    Halfedge_handle lIBisector = lOBisector->opposite();
    lOBisector->HBase_base::set_face(v->halfedge()->face());
    lIBisector->HBase_base::set_face(v->halfedge()->next()->face());
    lIBisector->HBase_base::set_vertex(v);

    Halfedge_handle lIBorder = v->halfedge() ;
    Halfedge_handle lOBorder = v->halfedge()->next() ;
    lIBorder  ->HBase_base::set_next(lOBisector);
    lOBisector->HBase_base::set_prev(lIBorder);
    lOBorder  ->HBase_base::set_prev(lIBisector);
    lIBisector->HBase_base::set_next(lOBorder);
    CGAL_STSKEL_BUILDER_TRACE(3
                             ,"Adding Contour Bisector at N:" << v->id() << "\n B" << lOBisector->id()
                             << " (Out)\n B" << lIBisector->id() << " (In)"
                             ) ;
  }
}

template<class Gt, class SS, class V>
void Straight_skeleton_builder_2<Gt,SS,V>::InitPhase()
{
  mVisitor.on_initialization_started(mSSkel->size_of_vertices());
  CreateContourBisectors();
  CreateInitialEvents();
  mVisitor.on_initialization_finished();
}

template<class Gt, class SS, class V>
typename Straight_skeleton_builder_2<Gt,SS,V>::Vertex_handle
Straight_skeleton_builder_2<Gt,SS,V>::ConstructEdgeEventNode( EdgeEvent& aEvent )
{
  CGAL_STSKEL_BUILDER_TRACE ( 2, "Creating EdgeEvent Node" ) ;

  Vertex_handle lLSeed = aEvent.seed0() ;
  Vertex_handle lRSeed = aEvent.seed1() ;

  Vertex_handle lNewNode = mSSkel->SSkel::Base::vertices_push_back( Vertex( mVertexID++, aEvent.point(), aEvent.time()) ) ;
  mSLAV.push_back(lNewNode);

  InitVertexData(lNewNode);
  SetSeededTrisegment(lNewNode,aEvent.strisegment());
  
  Halfedge_handle lLOBisector = lLSeed->primary_bisector();
  Halfedge_handle lROBisector = lRSeed->primary_bisector();
  Halfedge_handle lLIBisector = lLOBisector->opposite();
  Halfedge_handle lRIBisector = lROBisector->opposite();

  lNewNode->VBase::set_halfedge(lLOBisector);
  lLOBisector->HBase_base::set_vertex(lNewNode);
  lROBisector->HBase_base::set_vertex(lNewNode);

  lLIBisector->HBase_base::set_prev( lROBisector ) ;
  lROBisector->HBase_base::set_next( lLIBisector ) ;

  CGAL_STSKEL_BUILDER_TRACE
  ( 3
  ,    "LSeed: N" << lLSeed->id() << " proccesed\n"
    << "RSeed: N" << lRSeed->id() << " proccesed"
  ) ;

  SetIsProcessed(lLSeed) ;
  SetIsProcessed(lRSeed) ;
  mSLAV.remove(lLSeed);
  mSLAV.remove(lRSeed);

  Vertex_handle lLPrev = GetPrevInLAV(lLSeed) ;
  Vertex_handle lRNext = GetNextInLAV(lRSeed) ;

  SetPrevInLAV(lNewNode, lLPrev ) ;
  SetNextInLAV(lLPrev  , lNewNode  ) ;

  SetNextInLAV(lNewNode, lRNext ) ;
  SetPrevInLAV(lRNext  , lNewNode  ) ;

  CGAL_STSKEL_BUILDER_TRACE
  ( 2
  ,    "LO: B" << lLOBisector->id() << " LI: B" << lLIBisector->id() << " RO: B" << lROBisector->id() << " RI: B" << lRIBisector->id() << '\n'
    << "New Node: N" << lNewNode->id() << " at " << lNewNode->point() << '\n'
    << "New Links: B" << lROBisector->id() << "->B" << lLIBisector->id() << '\n'
    << 'N' << lNewNode->id() << " inserted into LAV: N" << lLPrev->id() << "->N" << lNewNode->id() << "->N" << lRNext->id() << std::endl
    << 'N' << lLSeed->id() << " removed from LAV\n"
    << 'N' << lRSeed->id() << " removed from LAV"
  );


  return lNewNode ;
}


 template<class Gt, class SS, class V>
typename Straight_skeleton_builder_2<Gt,SS,V>::Vertex_handle
Straight_skeleton_builder_2<Gt,SS,V>::LookupOnSLAV ( Halfedge_handle aBorder, EventPtr const& aEvent )
{
  Vertex_handle rResult ;

  CGAL_STSKEL_BUILDER_TRACE ( 3, "Looking up for E" << aBorder->id() << " on SLAV. P=" << aEvent->point() ) ;

  CGAL_STSKEL_DEBUG_CODE( bool lFound = false ; )

  for ( typename std::list<Vertex_handle>::const_iterator vi = mSLAV.begin(); vi != mSLAV.end(); ++ vi )
  {
    Vertex_handle v = *vi;
 
    Triedge lTriedge = GetTriedge(v);
       
    if (  handle_assigned(GetPrevInLAV(v))
       && handle_assigned(GetNextInLAV(v))
       && lTriedge.e0() == aBorder
       )
    {
      CGAL_STSKEL_DEBUG_CODE( lFound = true ; )

      Vertex_handle lPrev = GetPrevInLAV(v);
      Vertex_handle lNext = GetNextInLAV(v);
      
      Halfedge_handle lPrevBorder = GetTriedge(lPrev).e0();
      Halfedge_handle lNextBorder = GetTriedge(lNext).e0();
      
      CGAL_assertion(handle_assigned(lPrevBorder));
      CGAL_assertion(handle_assigned(lNextBorder));
      
      CGAL_STSKEL_BUILDER_TRACE ( 3
                                , "Subedge found in SLAV: N" << lPrev->id() << "->N" << v->id()
                                  << " (E" << lPrevBorder->id() << "->E" << aBorder->id() << "->E" << lNextBorder->id() << ")"
                                ) ;
                                
      if ( IsSplitEventInsideOffsetZone( aEvent, Triedge(lPrevBorder, aBorder, lNextBorder), lPrev, v ) )
      {
        rResult = v ;
        CGAL_STSKEL_BUILDER_TRACE ( 3, "That's the correct subedge. Found") ;
        break ;
      }
    }
  }
  
#ifdef CGAL_STRAIGHT_SKELETON_ENABLE_TRACE
  if ( !handle_assigned(rResult) )
  {
    if ( !lFound )
    {
      CGAL_STSKEL_BUILDER_TRACE(1,"Split event is no longer valid. Opposite edge vanished.");
    }
    else
    { 
      CGAL_STSKEL_BUILDER_TRACE(1,"Split event is no longer valid. Not inside the opposite edge offset zone.");
    }
  } 
#endif

  return rResult ;
}



template<class Gt, class SS, class V>
typename Straight_skeleton_builder_2<Gt,SS,V>::Vertex_handle_pair
Straight_skeleton_builder_2<Gt,SS,V>::ConstructSplitEventNodes( SplitEvent& aEvent, Vertex_handle aOppR )
{
  Vertex_handle_pair rResult;

  CGAL_STSKEL_BUILDER_TRACE ( 2, "Creating SplitEvent Nodes" ) ;

  Vertex_handle lOppL = GetPrevInLAV(aOppR) ;

  Vertex_handle lNodeA = mSSkel->SSkel::Base::vertices_push_back( Vertex( mVertexID++, aEvent.point(), aEvent.time() ) ) ;
  Vertex_handle lNodeB = mSSkel->SSkel::Base::vertices_push_back( Vertex( mVertexID++, aEvent.point(), aEvent.time() ) ) ;

  mSLAV.push_back(lNodeA);
  mSLAV.push_back(lNodeB);
  
  InitVertexData(lNodeA);
  InitVertexData(lNodeB);
  SetSeededTrisegment(lNodeA,aEvent.strisegment());
  SetSeededTrisegment(lNodeB,aEvent.strisegment());

  Vertex_handle lSeed = aEvent.seed0() ;

  Halfedge_handle lXOutBisector = lSeed->primary_bisector() ;
  Halfedge_handle lXInBisector  = lXOutBisector->opposite();

  lNodeA->VBase::set_halfedge(lXOutBisector);
  // lNodeB hafledge is set outside with the New In Bisector to the Right.

  lXOutBisector->HBase_base::set_vertex(lNodeA);

  CGAL_STSKEL_BUILDER_TRACE ( 3, "Seed: N" << lSeed->id() << " proccesed" ) ;

  SetIsProcessed(lSeed) ;
  mSLAV.remove(lSeed);

  CGAL_STSKEL_BUILDER_TRACE ( 2, 'N' << lNodeA->id() << " and N" << lNodeB->id() << " inserted into LAV." ) ;

  Vertex_handle lPrev = GetPrevInLAV(lSeed) ;
  Vertex_handle lNext = GetNextInLAV(lSeed) ;

  SetNextInLAV(lPrev , lNodeA ) ;
  SetPrevInLAV(lNodeA, lPrev  ) ;

  SetNextInLAV(lNodeA, aOppR  ) ;
  SetPrevInLAV(aOppR , lNodeA ) ;

  SetNextInLAV(lOppL , lNodeB ) ;
  SetPrevInLAV(lNodeB, lOppL  ) ;

  SetNextInLAV(lNodeB, lNext  ) ;
  SetPrevInLAV(lNext , lNodeB ) ;

  CGAL_STSKEL_BUILDER_TRACE
  (
   2
   ,   "Updated LAV: N" << lPrev->id() << "->N" << lNodeA->id() << "->N" << aOppR->id() << std::endl
    << "Updated LAV: N" << lOppL->id() << "->N" << lNodeB->id() << "->N" << lNext->id() << std::endl
    << 'N' << lSeed->id() << " removed from LAV"
  );

  rResult = std::make_pair(lNodeA,lNodeB);

  mSplitNodes.push_back(rResult);

  return rResult ;
}

template<class Gt, class SS, class V>
typename Straight_skeleton_builder_2<Gt,SS,V>::Vertex_handle_pair
Straight_skeleton_builder_2<Gt,SS,V>::ConstructPseudoSplitEventNodes( PseudoSplitEvent& aEvent )
{
  Vertex_handle_pair rResult;

  CGAL_STSKEL_BUILDER_TRACE ( 2, "Creating PseudoSplitEvent Nodes" ) ;

  Vertex_handle lLSeed = aEvent.seed0() ;
  Vertex_handle lRSeed = aEvent.seed1() ;

  Vertex_handle lNewNodeA = mSSkel->SSkel::Base::vertices_push_back( Vertex( mVertexID++, aEvent.point(), aEvent.time()) ) ;
  Vertex_handle lNewNodeB = mSSkel->SSkel::Base::vertices_push_back( Vertex( mVertexID++, aEvent.point(), aEvent.time()) ) ;

  mSLAV.push_back(lNewNodeA);
  mSLAV.push_back(lNewNodeB);

  InitVertexData(lNewNodeA);
  InitVertexData(lNewNodeB);
  SetSeededTrisegment(lNewNodeA,aEvent.strisegment());
  SetSeededTrisegment(lNewNodeB,aEvent.strisegment());
  
  Halfedge_handle lLOBisector = lLSeed->primary_bisector();
  Halfedge_handle lROBisector = lRSeed->primary_bisector();
  Halfedge_handle lLIBisector = lLOBisector->opposite();
  Halfedge_handle lRIBisector = lROBisector->opposite();

  lNewNodeA->VBase::set_halfedge(lLOBisector);
  lNewNodeB->VBase::set_halfedge(lROBisector);
  lLOBisector->HBase_base::set_vertex(lNewNodeA);
  lROBisector->HBase_base::set_vertex(lNewNodeB);

  lLIBisector->HBase_base::set_prev( lROBisector ) ;
  lROBisector->HBase_base::set_next( lLIBisector ) ;
  
  lLOBisector->HBase_base::set_next( lRIBisector ) ;
  lRIBisector->HBase_base::set_prev( lLOBisector ) ;

  CGAL_STSKEL_BUILDER_TRACE
  (
   3
   ,   "LSeed: N" << lLSeed->id() << " proccesed\n"
    << "RSeed: N" << lRSeed->id() << " proccesed"
  ) ;

  SetIsProcessed(lLSeed) ;
  SetIsProcessed(lRSeed) ;
  mSLAV.remove(lLSeed);
  mSLAV.remove(lRSeed);

  Vertex_handle lLPrev = GetPrevInLAV(lLSeed) ;
  Vertex_handle lLNext = GetNextInLAV(lLSeed) ;
  Vertex_handle lRPrev = GetPrevInLAV(lRSeed) ;
  Vertex_handle lRNext = GetNextInLAV(lRSeed) ;

  SetPrevInLAV(lNewNodeA, lLPrev    ) ;
  SetNextInLAV(lLPrev   , lNewNodeA ) ;

  SetNextInLAV(lNewNodeA, lRNext    ) ;
  SetPrevInLAV(lRNext   , lNewNodeA ) ;

  SetPrevInLAV(lNewNodeB, lRPrev    ) ;
  SetNextInLAV(lRPrev   , lNewNodeB ) ;

  SetNextInLAV(lNewNodeB, lLNext    ) ;
  SetPrevInLAV(lLNext   , lNewNodeB ) ;

  CGAL_STSKEL_BUILDER_TRACE
  (
  2
  ,    "LO: B" << lLOBisector->id() << " LI: B" << lLIBisector->id() << " RO: B" << lROBisector->id() << " RI: B" << lRIBisector->id() << '\n'
    << "NewNodeA: N" << lNewNodeA->id() << " at " << lNewNodeA->point() << '\n'
    << "NewNodeB: N" << lNewNodeB->id() << " at " << lNewNodeB->point() << '\n'
    << "New Links: B" << lROBisector->id() << "->B" << lLIBisector->id() << '\n'
    << 'N' << lNewNodeA->id() << " and N" << lNewNodeB->id() << " inserted into LAV:\n"
    << 'N' << lLPrev->id() << "->N" << lNewNodeA->id() << "->N" << lRNext->id() << '\n'
    << 'N' << lRPrev->id() << "->N" << lNewNodeB->id() << "->N" << lLNext->id() << '\n'
    << 'N' << lLSeed->id() << " removed from LAV\n"
    << 'N' << lRSeed->id() << " removed from LAV"
  );

  rResult = std::make_pair(lNewNodeA,lNewNodeB);

  mSplitNodes.push_back(rResult);

  return rResult ;
}

template<class Gt, class SS, class V>
bool Straight_skeleton_builder_2<Gt,SS,V>::IsProcessed( EventPtr aEvent )
{
  return IsProcessed(aEvent->seed0()) || IsProcessed(aEvent->seed1()) ;
}

template<class Gt, class SS, class V>
void Straight_skeleton_builder_2<Gt,SS,V>::HandleEdgeEvent( EventPtr aEvent )
{
  EdgeEvent& lEvent = dynamic_cast<EdgeEvent&>(*aEvent) ;

  Vertex_handle lLSeed = lEvent.seed0() ;
  Vertex_handle lRSeed = lEvent.seed1() ;

  Vertex_handle lNewNode = ConstructEdgeEventNode(lEvent);

  Halfedge_handle lLOBisector = lLSeed->primary_bisector() ;
  Halfedge_handle lROBisector = lRSeed->primary_bisector() ;
  Halfedge_handle lLIBisector = lLOBisector->opposite();
  Halfedge_handle lRIBisector = lROBisector->opposite();

  if ( !handle_assigned(lLOBisector->next()) && !handle_assigned(lRIBisector->prev()) )
  {
    CGAL_STSKEL_BUILDER_TRACE(3,"Creating new Edge Event's Bisector");

    Halfedge_handle lNOBisector = mSSkel->SSkel::Base::edges_push_back ( Halfedge(mEdgeID),Halfedge(mEdgeID+1) );

    Halfedge_handle lNIBisector = lNOBisector->opposite();
    mEdgeID += 2 ;

    lRIBisector->HBase_base::set_prev(lNIBisector);
    lNIBisector->HBase_base::set_next(lRIBisector);

    lNOBisector->HBase_base::set_face(lLOBisector->face());
    lNIBisector->HBase_base::set_face(lRIBisector->face());
    lNIBisector->HBase_base::set_vertex(lNewNode);

    lLOBisector->HBase_base::set_next(lNOBisector);
    lNOBisector->HBase_base::set_prev(lLOBisector);

    Halfedge_handle lDefiningBorderA = lNewNode->halfedge()->face()->halfedge();
    Halfedge_handle lDefiningBorderB = lNewNode->halfedge()->opposite()->prev()->opposite()->face()->halfedge();
    Halfedge_handle lDefiningBorderC = lNewNode->halfedge()->opposite()->prev()->face()->halfedge();

    SetTriedge(lNewNode, Triedge(lDefiningBorderA,lDefiningBorderB,lDefiningBorderC) ) ;

    CGAL_STSKEL_BUILDER_TRACE
      ( 2
      , "NewNode N" << lNewNode->id() << " at " << lNewNode->point() << " defining borders: E"
        << lDefiningBorderA->id()
        << ",E" << lDefiningBorderB->id()
        << ",E" << lDefiningBorderC->id() << '\n'
        << "New Bisectors:\nB" << lNOBisector->id() << " [E" << lNOBisector->defining_contour_edge()->id()
        << ",E" << lNOBisector->opposite()->defining_contour_edge()->id()
        << "] (Out: Prev: B" << lNOBisector->prev()->id() << ")\nB"
        << lNIBisector->id() << " [E" << lNIBisector->defining_contour_edge()->id()
        << ",E" << lNIBisector->opposite()->defining_contour_edge()->id()
        << "] (In: Next: B" << lNIBisector->next()->id() << ")\n"
        << "N" << lNewNode->id() << " halfedge: " << lNewNode->halfedge()->id()
        << " primary bisector: B" << lNewNode->primary_bisector()->id()
      ) ;

    UpdatePQ(lNewNode);
  }
  else
  {
    Halfedge_handle lDefiningBorderA = lNewNode->halfedge()->face()->halfedge();
    Halfedge_handle lDefiningBorderB = lNewNode->halfedge()->opposite()->prev()->opposite()->face()->halfedge();
    Halfedge_handle lDefiningBorderC = lNewNode->halfedge()->opposite()->prev()->face()->halfedge();

    SetTriedge(lNewNode, Triedge(lDefiningBorderA,lDefiningBorderB,lDefiningBorderC) ) ;
    
    CGAL_STSKEL_BUILDER_TRACE(2
                        ,  "NewNode N" << lNewNode->id() << " at " << lNewNode->point() << " defining borders:"
                        << " E" << lDefiningBorderA->id()
                        << ",E" << lDefiningBorderB->id()
                        << ",E" << lDefiningBorderC->id() 
                        << ".\nThis is a multiple node (A node with these defining edges already exist in the LAV)"
                        );
  }

  mVisitor.on_edge_event_processed(lLSeed,lRSeed,lNewNode) ;
  
}

template<class Gt, class SS, class V>
void Straight_skeleton_builder_2<Gt,SS,V>::HandleSplitEvent( EventPtr aEvent, Vertex_handle aOppR )
{
  SplitEvent& lEvent = dynamic_cast<SplitEvent&>(*aEvent) ;

  Halfedge_handle lOppBorder = lEvent.triedge().e2() ;

  Vertex_handle lSeed = lEvent.seed0();

  Vertex_handle lNewNode_L, lNewNode_R ;
  boost::tie(lNewNode_L,lNewNode_R) = ConstructSplitEventNodes(lEvent,aOppR);

  Triedge lTriedge = aEvent->triedge();
      
  Halfedge_handle lReflexLBorder = lTriedge.e0();
  Halfedge_handle lReflexRBorder = lTriedge.e1();

  Halfedge_handle lNOBisector_L = mSSkel->SSkel::Base::edges_push_back ( Halfedge(mEdgeID++),Halfedge(mEdgeID++) );
  Halfedge_handle lNOBisector_R = mSSkel->SSkel::Base::edges_push_back ( Halfedge(mEdgeID++),Halfedge(mEdgeID++) );
  Halfedge_handle lNIBisector_L = lNOBisector_L->opposite();
  Halfedge_handle lNIBisector_R = lNOBisector_R->opposite();

  lNewNode_R->VBase::set_halfedge(lNIBisector_L) ;

  Halfedge_handle lXOBisector = lSeed->primary_bisector() ;
  Halfedge_handle lXIBisector = lXOBisector->opposite();

  lNOBisector_L->HBase_base::set_face(lXOBisector->face());
  lNIBisector_L->HBase_base::set_face(lOppBorder ->face());
  lNOBisector_R->HBase_base::set_face(lOppBorder ->face());
  lNIBisector_R->HBase_base::set_face(lXIBisector->face());

  lNIBisector_L->HBase_base::set_vertex(lNewNode_R);
  lNIBisector_R->HBase_base::set_vertex(lNewNode_R);

  lXOBisector  ->HBase_base::set_next(lNOBisector_L);
  lNOBisector_L->HBase_base::set_prev(lXOBisector);

  lXIBisector  ->HBase_base::set_prev(lNIBisector_R);
  lNIBisector_R->HBase_base::set_next(lXIBisector);

  lNIBisector_L->HBase_base::set_next(lNOBisector_R);
  lNOBisector_R->HBase_base::set_prev(lNIBisector_L);

  Halfedge_handle lNewNode_L_DefiningBorderA = lNewNode_L->halfedge()->face()->halfedge();
  Halfedge_handle lNewNode_L_DefiningBorderB = lNewNode_L->halfedge()->opposite()->prev()->opposite()->face()->halfedge();
  Halfedge_handle lNewNode_L_DefiningBorderC = lNewNode_L->halfedge()->opposite()->prev()->face()->halfedge();
  Halfedge_handle lNewNode_R_DefiningBorderA = lNewNode_R->halfedge()->face()->halfedge();
  Halfedge_handle lNewNode_R_DefiningBorderB = lNewNode_R->halfedge()->opposite()->prev()->opposite()->face()->halfedge();
  Halfedge_handle lNewNode_R_DefiningBorderC = lNewNode_R->halfedge()->opposite()->prev()->face()->halfedge();

  SetTriedge(lNewNode_L, Triedge(lNewNode_L_DefiningBorderA,lNewNode_L_DefiningBorderB,lNewNode_L_DefiningBorderC) ) ;
  SetTriedge(lNewNode_R, Triedge(lNewNode_R_DefiningBorderA,lNewNode_R_DefiningBorderB,lNewNode_R_DefiningBorderC) ) ;
  
  CGAL_STSKEL_BUILDER_TRACE
    (
     2
    ,    "New Node L: N" << lNewNode_L->id() << " at " << lNewNode_L->point()
      << " defining borders: E" << lNewNode_L_DefiningBorderA->id()
      << ",E" << lNewNode_L_DefiningBorderB->id()
      << ",E" << lNewNode_L_DefiningBorderC->id() << '\n'
      << "New Node R: N" << lNewNode_R->id() << " at " << lNewNode_R->point()
      << " defining borders: E" << lNewNode_R_DefiningBorderA->id()
      << ",E" << lNewNode_R_DefiningBorderB->id() << '\n'
      << ",E" << lNewNode_R_DefiningBorderC->id() << '\n'
      << "New Bisector OL:\nB" << lNOBisector_L->id()
      << "[E"  << lNOBisector_L            ->defining_contour_edge()->id()
      << ",E" << lNOBisector_L->opposite()->defining_contour_edge()->id() << "]"
      << " (Out: Prev: B" << lNOBisector_L->prev()->id() << ")\n"
      << "New Bisector IL:\nB" << lNIBisector_L->id()
      << "[E" << lNIBisector_L            ->defining_contour_edge()->id()
      << ",E" << lNIBisector_L->opposite()->defining_contour_edge()->id() << "]"
      << " (In: Next: B" << lNIBisector_L->next()->id() << ")\n"
      << "New Bisector OR:\nB" << lNOBisector_R->id()
      << "[E" << lNOBisector_R            ->defining_contour_edge()->id()
      << ",E" << lNOBisector_R->opposite()->defining_contour_edge()->id() << "]"
      << " (Out: Prev: B" << lNOBisector_R->prev()->id() << ")\n"
      << "New Bisector IR:\nB" << lNIBisector_R->id()
      << "[E" << lNIBisector_R            ->defining_contour_edge()->id()
      << ",E" << lNIBisector_R->opposite()->defining_contour_edge()->id()
      << "] (In: Next: B" << lNIBisector_R->next()->id() << ")\n"
      << "N" << lNewNode_L->id() << " halfedge: " << lNewNode_L->halfedge()->id()
      << " primary bisector: B" << lNewNode_L->primary_bisector()->id() << '\n'
      << "N" << lNewNode_R->id() << " halfedge: " << lNewNode_R->halfedge()->id()
      << " primary bisector: B" << lNewNode_R->primary_bisector()->id()
    ) ;

  UpdatePQ(lNewNode_L);
  UpdatePQ(lNewNode_R);

  mVisitor.on_split_event_processed(lSeed,lNewNode_L,lNewNode_R) ;
}

template<class Gt, class SS, class V>
void Straight_skeleton_builder_2<Gt,SS,V>::SetupPseudoSplitEventNode( Vertex_handle   aNode
                                                                    , Halfedge_handle aDefiningBorderA
                                                                    , Halfedge_handle aDefiningBorderB
                                                                    )
{
  Point_2 p = aDefiningBorderA->opposite()->vertex()->point() ;
  Point_2 q = aDefiningBorderA->opposite()->prev()->vertex()->point() ;
  Point_2 r = aDefiningBorderB->opposite()->prev()->vertex()->point() ;

  Orientation lOrientation = CGAL::orientation(p,q,r) ;
  if ( lOrientation == COLLINEAR )
  {
    SetIsDegenerate(aNode);
    CGAL_STSKEL_BUILDER_TRACE(1, "COLLINEAR *NEW* vertex: N" << aNode->id() );
  }
  else if ( lOrientation == RIGHT_TURN )
  {
    mReflexVertices.push_back(aNode);
    SetIsReflex(aNode);
    CGAL_STSKEL_BUILDER_TRACE(1, "Reflex *NEW* vertex: N" << aNode->id() );
  }
}

template<class Gt, class SS, class V>
void Straight_skeleton_builder_2<Gt,SS,V>::HandlePseudoSplitEvent( EventPtr aEvent )
{
  
  PseudoSplitEvent& lEvent = dynamic_cast<PseudoSplitEvent&>(*aEvent) ;
  
  Vertex_handle lLSeed = lEvent.seed0() ;
  Vertex_handle lRSeed = lEvent.seed1() ;

  Vertex_handle lNewNode_L, lNewNode_R ;
  boost::tie(lNewNode_L,lNewNode_R) = ConstructPseudoSplitEventNodes(lEvent);

  Halfedge_handle lNBisector_LO = mSSkel->SSkel::Base::edges_push_back ( Halfedge(mEdgeID++),Halfedge(mEdgeID++) );
  Halfedge_handle lNBisector_RO = mSSkel->SSkel::Base::edges_push_back ( Halfedge(mEdgeID++),Halfedge(mEdgeID++) );
  Halfedge_handle lNBisector_LI = lNBisector_LO->opposite();
  Halfedge_handle lNBisector_RI = lNBisector_RO->opposite();

  Halfedge_handle lSBisector_LO = lLSeed->primary_bisector() ;
  Halfedge_handle lSBisector_LI = lSBisector_LO->opposite();

  Halfedge_handle lSBisector_RO = lRSeed->primary_bisector() ;
  Halfedge_handle lSBisector_RI = lSBisector_RO->opposite();

  lNBisector_LO->HBase_base::set_face(lSBisector_LO->face());
  lNBisector_LI->HBase_base::set_face(lSBisector_RI->face());
  lNBisector_RO->HBase_base::set_face(lSBisector_RO->face());
  lNBisector_RI->HBase_base::set_face(lSBisector_LI->face());

  lNBisector_LI->HBase_base::set_vertex(lNewNode_L);
  lNBisector_RI->HBase_base::set_vertex(lNewNode_R);

  lSBisector_LO->HBase_base::set_next(lNBisector_LO);
  lNBisector_LO->HBase_base::set_prev(lSBisector_LO);

  lSBisector_LI->HBase_base::set_prev(lNBisector_RI);
  lNBisector_RI->HBase_base::set_next(lSBisector_LI);

  lSBisector_RI->HBase_base::set_prev(lNBisector_LI);
  lNBisector_LI->HBase_base::set_next(lSBisector_RI);

  lSBisector_RO->HBase_base::set_next(lNBisector_RO);
  lNBisector_RO->HBase_base::set_prev(lSBisector_RO);

  lNewNode_L->VBase::set_halfedge(lSBisector_LO);
  lNewNode_R->VBase::set_halfedge(lSBisector_RO);

  Halfedge_handle lNewNode_L_DefiningBorderA = lNewNode_L->halfedge()->face()->halfedge();
  Halfedge_handle lNewNode_L_DefiningBorderB = lNewNode_L->halfedge()->next()->opposite()->face()->halfedge();
  Halfedge_handle lNewNode_L_DefiningBorderC = lNewNode_L->halfedge()->opposite()->prev()->face()->halfedge();
  Halfedge_handle lNewNode_R_DefiningBorderA = lNewNode_R->halfedge()->face()->halfedge();
  Halfedge_handle lNewNode_R_DefiningBorderB = lNewNode_R->halfedge()->next()->opposite()->face()->halfedge();
  Halfedge_handle lNewNode_R_DefiningBorderC = lNewNode_R->halfedge()->opposite()->prev()->face()->halfedge();

  SetTriedge(lNewNode_L, Triedge(lNewNode_L_DefiningBorderA, lNewNode_L_DefiningBorderB, lNewNode_L_DefiningBorderC) )  ;
  SetTriedge(lNewNode_R, Triedge(lNewNode_R_DefiningBorderA, lNewNode_R_DefiningBorderB, lNewNode_R_DefiningBorderC) )  ;

  CGAL_STSKEL_BUILDER_TRACE
    (2
    ,    "New Node L: N" << lNewNode_L->id() << " at " << lNewNode_L->point()
      << " defining borders: E" << lNewNode_L_DefiningBorderA->id()
      << ",E" << lNewNode_L_DefiningBorderB->id()
      << ",E" << lNewNode_L_DefiningBorderC->id() << '\n'
      << "New Node R: N" << lNewNode_R->id() << " at " << lNewNode_R->point()
      << " defining borders: E" << lNewNode_R_DefiningBorderA->id()
      << ",E" << lNewNode_R_DefiningBorderB->id()
      << ",E" << lNewNode_R_DefiningBorderC->id() << '\n'
      << "New Bisector LO: B" << lNBisector_LO->id()
      << "[E"  << lNBisector_LO            ->defining_contour_edge()->id()
      << ",E" << lNBisector_LO->opposite()->defining_contour_edge()->id() << "]\n"
      << "New Bisector LI: B" << lNBisector_LI->id()
      << "[E" << lNBisector_LI            ->defining_contour_edge()->id()
      << ",E" << lNBisector_LI->opposite()->defining_contour_edge()->id() << "]\n"
      << "New Bisector RO: B" << lNBisector_RO->id()
      << "[E" << lNBisector_RO            ->defining_contour_edge()->id()
      << ",E" << lNBisector_RO->opposite()->defining_contour_edge()->id() << "]\n"
      << "New Bisector RI: B" << lNBisector_RI->id()
      << "[E" << lNBisector_RI            ->defining_contour_edge()->id()
      << ",E" << lNBisector_RI->opposite()->defining_contour_edge()->id() << "]\n"
      << "N" << lNewNode_L->id() << " halfedge: " << lNewNode_L->halfedge()->id()
      << " primary bisector: B" << lNewNode_L->primary_bisector()->id() << '\n'
      << "N" << lNewNode_R->id() << " halfedge: " << lNewNode_R->halfedge()->id()
      << " primary bisector: B" << lNewNode_R->primary_bisector()->id()
    ) ;

  SetupPseudoSplitEventNode(lNewNode_L,lNewNode_L_DefiningBorderA,lNewNode_L_DefiningBorderB) ;
  SetupPseudoSplitEventNode(lNewNode_R,lNewNode_R_DefiningBorderA,lNewNode_R_DefiningBorderB) ;

  
  UpdatePQ(lNewNode_L);
  UpdatePQ(lNewNode_R);
  

  mVisitor.on_pseudo_split_event_processed(lLSeed,lRSeed,lNewNode_L,lNewNode_R) ;
}

template<class Gt, class SS, class V>
void Straight_skeleton_builder_2<Gt,SS,V>::HandleSplitOrPseudoSplitEvent( EventPtr aEvent )
{
  Vertex_handle lOppR = LookupOnSLAV(aEvent->triedge().e2(),aEvent);
  if ( handle_assigned(lOppR) )
  {
    EventPtr lPseudoSplitEvent = IsPseudoSplitEvent(aEvent,lOppR);
    if ( lPseudoSplitEvent )
         HandlePseudoSplitEvent(lPseudoSplitEvent);
    else HandleSplitEvent      (aEvent,lOppR);  
  }
}

template<class Gt, class SS, class V>
void Straight_skeleton_builder_2<Gt,SS,V>::InsertNextSplitEventInPQ( Vertex_handle v )
{
  EventPtr lSplitEvent = PopNextSplitEvent(v);
  if ( !!lSplitEvent )
    InsertEventInPQ(lSplitEvent);
}

template<class Gt, class SS, class V>
void Straight_skeleton_builder_2<Gt,SS,V>::InsertNextSplitEventsInPQ()
{
  for ( typename Vertex_handle_vector::iterator v = mReflexVertices.begin(), ev = mReflexVertices.end(); v != ev ; ++ v )
    if ( !IsProcessed(*v) )
      InsertNextSplitEventInPQ(*v);
}

template<class Gt, class SS, class V>
void Straight_skeleton_builder_2<Gt,SS,V>::Propagate()
{
  CGAL_STSKEL_BUILDER_TRACE(0,"Propagating events...");
  mVisitor.on_propagation_started();

  while ( !mPQ.empty() )
  {
    InsertNextSplitEventsInPQ();
       
    EventPtr lEvent = PopEventFromPQ();

    if ( lEvent->type() != Event::cEdgeEvent )    
      AllowNextSplitEvent(lEvent->seed0());

    if ( !IsProcessed(lEvent) )
    {
      CGAL_STSKEL_BUILDER_TRACE (1,"\nS" << mStepID << " Event: " << *lEvent ) ;

      SetEventTimeAndPoint(*lEvent) ;
      
      switch ( lEvent->type() )
      {
        case Event::cEdgeEvent       : HandleEdgeEvent              (lEvent) ; break ;
        case Event::cSplitEvent      : HandleSplitOrPseudoSplitEvent(lEvent) ; break ;
        case Event::cPseudoSplitEvent: HandlePseudoSplitEvent       (lEvent) ; break ; 
      }

      ++ mStepID ;
    }
  }
  
  mVisitor.on_propagation_finished();
}

template<class Gt, class SS, class V>
void Straight_skeleton_builder_2<Gt,SS,V>::MergeSplitNodes ( Vertex_handle_pair aSplitNodes )
{
  Vertex_handle lLNode, lRNode ;
  boost::tie(lLNode,lRNode)=aSplitNodes;

  Halfedge_handle lIBisectorL1 = lLNode->primary_bisector()->opposite();
  Halfedge_handle lIBisectorR1 = lRNode->primary_bisector()->opposite();
  Halfedge_handle lIBisectorL2 = lIBisectorL1->next()->opposite();
  Halfedge_handle lIBisectorR2 = lIBisectorR1->next()->opposite();
  
  CGAL_STSKEL_BUILDER_TRACE(2
                      ,"Merging SplitNodes: (L) N" << lLNode->id() << " and (R) N" << lRNode->id() << ".\n"
                       << "  LOut: B" << lLNode->primary_bisector()->id() << '\n'
                       << "  ROut: B" << lRNode->primary_bisector()->id() << '\n'
                       << "  LIn1: B" << lIBisectorL1->id() << '\n'
                       << "  RIn1: B" << lIBisectorR1->id() << '\n'
                       << "  LIn2: B" << lIBisectorL2->id() << '\n'
                       << "  RIn2: B" << lIBisectorR2->id() 
                       );

  if ( lIBisectorL1->vertex() == lRNode )
    lIBisectorL1->HBase_base::set_vertex(lLNode);

  if ( lIBisectorR1->vertex() == lRNode )
    lIBisectorR1->HBase_base::set_vertex(lLNode);

  if ( lIBisectorL2->vertex() == lRNode )
    lIBisectorL2->HBase_base::set_vertex(lLNode);

  if ( lIBisectorR2->vertex() == lRNode )
    lIBisectorR2->HBase_base::set_vertex(lLNode);

  CGAL_STSKEL_BUILDER_TRACE(2
                      ,   "  N" << lRNode->id() << " excluded.\n"
                       << "  LIn1 B" << lIBisectorL1->id() << " now linked to N" << lIBisectorL1->vertex()->id() << '\n'
                       << "  RIn1 B" << lIBisectorR1->id() << " now linked to N" << lIBisectorR1->vertex()->id() << '\n'
                       << "  LIn2 B" << lIBisectorL2->id() << " now linked to N" << lIBisectorL2->vertex()->id() << '\n'
                       << "  RIn2 B" << lIBisectorR2->id() << " now linked to N" << lIBisectorR2->vertex()->id()
                       );

  mSSkel->SSkel::Base::vertices_erase(lRNode);

}


#ifdef CGAL_STRAIGHT_SKELETON_ENABLE_TRACE
template<class Halfedge_handle>
void TraceMultinode( char const* t, Halfedge_handle b, Halfedge_handle e )
{
  std::ostringstream ss ;
  ss << t ;
  
  do
  {
    ss << "B" << b->id() << " N" << b->vertex()->id() << " " ;
  }
  while ( b = b->next(), b != e ) ;
  
  std::string s = ss.str();
  CGAL_STSKEL_BUILDER_TRACE(0, s);
}


template<class Point>
double angle_wrt_X ( Point const& a, Point const& b )
{
  double dx = to_double(b.x() - a.x() ) ;
  double dy = to_double(b.y() - a.y() ) ;
  double atan = std::atan2(dy,dx);
  double rad  = atan >= 0.0 ? atan : 2.0 * 3.141592 + atan ;
  double deg  = rad * 180.0 / 3.141592 ;
  return deg ;
}

template<class Vertex_handle, class Halfedge_around_vertex_circulator>
void TraceFinalBisectors( Vertex_handle v, Halfedge_around_vertex_circulator cb )
{
  Halfedge_around_vertex_circulator c = cb ;

  do
  {
    double phi = angle_wrt_X((*c)->vertex()->point(),(*c)->opposite()->vertex()->point());
    
    CGAL_STSKEL_BUILDER_TRACE(2, "  N" << v->id() << " in=B" << (*c)->id() 
                        << " E" << (*c)->defining_contour_edge()->id() 
                        << " out=B" << (*c)->opposite()->id() 
                        << " E" << (*c)->opposite()->defining_contour_edge()->id() 
                        << " phi=" << phi
                        );
    
    ++ c ;
  }
  while( c != cb ) ;
  
}
#endif

template<class Vertex_handle, class Halfedge_around_vertex_circulator>
bool ValidateFinalBisectorsAfterMerge( Vertex_handle /* v */, Halfedge_around_vertex_circulator cb )
{
  bool rOK = true ;
  
  Halfedge_around_vertex_circulator c = cb ;

  do
  {
    if ( (*c)->defining_contour_edge() != (*c)->prev()->defining_contour_edge() )
      rOK = false ;
      
    ++ c ;
  }
  while( rOK && c != cb ) ;
  
  return rOK ;
  
}

template<class Gt, class SS, class V>
void Straight_skeleton_builder_2<Gt,SS,V>::RelinkBisectorsAroundMultinode( Vertex_handle const& v0, Halfedge_handle_vector& aLinks )
{
  CGAL_assertion( aLinks.size() > 0 ) ;
  
  CGAL_STSKEL_BUILDER_TRACE(4, "Relinking " << aLinks.size() << " bisectors around N" << v0->id() ) ;
  
  // Connect the bisectors with each other following the CCW ordering
  
  Halfedge_handle first_he = aLinks.front();        
  Halfedge_handle prev_he  = first_he ;
  
  first_he->HBase_base::set_vertex(v0);
  
  for ( typename Halfedge_handle_vector::iterator i = successor(aLinks.begin()), ei = aLinks.end(); i != ei ; ++ i )
  {
    Halfedge_handle he = *i ;

    he->HBase_base::set_vertex(v0);
            
    Halfedge_handle prev_he_opp = prev_he->opposite();
    
    he         ->HBase_base::set_next(prev_he_opp);
    prev_he_opp->HBase_base::set_prev(he);

    CGAL_STSKEL_BUILDER_TRACE(4, "Relinking B" << he->id() << "->B" << prev_he_opp->id() ) ;
    
    prev_he = he ;
  }

  Halfedge_handle prev_he_opp = prev_he->opposite();
    
  first_he   ->HBase_base::set_next(prev_he_opp);
  prev_he_opp->HBase_base::set_prev(first_he);

  CGAL_STSKEL_BUILDER_TRACE(4, "Relinking B" << first_he->id() << "->B" << prev_he_opp->id() ) ;
  
  // Reset the main halfedge for v0  
  v0->VBase::set_halfedge(first_he) ;
  
  CGAL_STSKEL_DEBUG_CODE( TraceFinalBisectors(v0,v0->halfedge_around_vertex_begin()); )

  CGAL_postcondition( ValidateFinalBisectorsAfterMerge(v0,v0->halfedge_around_vertex_begin()) ) ;
}


template<class Gt, class SS, class V>
void Straight_skeleton_builder_2<Gt,SS,V>::PreprocessMultinode( Multinode& aMN )
{
  //
  // A Multinode is a run of coincident nodes along a face.
  // Its represented by a pair of halfedges describing a linear profile.
  // The first halfedge in the pair points to the first node in the multinode.
  // Each ->next() halfedge in the profile points to a subsequent node.
  // The second halfedge in the pair is past-the-end (it points to the first node around the face that IS NOT part of the multinode)
  //
  
  Halfedge_handle oend = validate(aMN.end->opposite());
  
  Halfedge_handle h = aMN.begin ;
 
  aMN.bisectors_to_relink.push_back(h);
  
  // Traverse the profile collecting:
  //  The nodes to be removed from the HDS (all but the first)
  //  The bisectors to be removed from the HDS (each bisector pointing to the next node in the multinode)
  //  The bisectors around each node that must be relinked to the first node (which will be kept in place of the multinode)
  do
  {
    ++ aMN.size ;
    Halfedge_handle nx = validate(h->next());
    if ( nx != aMN.end )
      aMN.bisectors_to_remove.push_back(nx);

    // Since each halfedge "h" in this lineal profile corresponds to a single face, all the bisectors around
    // each node which must be relinked are those found ccw between h and h->next()
    Halfedge_handle ccw = h ;
    Halfedge_handle ccw_end = validate(h->next()->opposite());
    for(;;)
    {
      ccw = validate(ccw->opposite()->prev()) ;
      if ( ccw != ccw_end )
           aMN.bisectors_to_relink.push_back(ccw);
      else break ;  
    }    
    if ( h != aMN.begin )
      aMN.nodes_to_remove.push_back(h->vertex());
      
    h = nx;
  }
  while ( h != aMN.end ) ;
  
  aMN.bisectors_to_relink.push_back(aMN.end->opposite());
  
  CGAL_STSKEL_DEBUG_CODE( TraceMultinode("Preprocessing multinode: ", aMN.begin,aMN.end) ) ;
}

//
// Replaces a run of coincident nodes with a single one by removing all but the first, remvong node-to-node bisectors and
// relinking the other bisectors.
//
template<class Gt, class SS, class V>
void Straight_skeleton_builder_2<Gt,SS,V>::ProcessMultinode( Multinode&              aMN 
                                                           , Halfedge_handle_vector& rBisectorsToRemove 
                                                           , Vertex_handle_vector&   rNodesToRemove
                                                           )
{
  bool lSomeNodeAlreadyProcessed = false ;
  
  Halfedge_handle h = aMN.begin ;

  do
  {
    if ( IsExcluded(h->vertex()))
      lSomeNodeAlreadyProcessed = true ;
  }
  while ( h = h->next(), !lSomeNodeAlreadyProcessed && h != aMN.end ) ;
  
  if ( !lSomeNodeAlreadyProcessed )
  {
    CGAL_STSKEL_DEBUG_CODE( TraceMultinode("Processing multinode: ", aMN.begin,aMN.end) ) ;
    
    Halfedge_handle h = aMN.begin ;
    do
    {
      Exclude(h->vertex());
    }
    while ( h = h->next(), h != aMN.end ) ;

    std::copy(aMN.bisectors_to_remove.begin(), aMN.bisectors_to_remove.end(), std::back_inserter(rBisectorsToRemove));
    std::copy(aMN.nodes_to_remove    .begin(), aMN.nodes_to_remove    .end(), std::back_inserter(rNodesToRemove));
     
    RelinkBisectorsAroundMultinode(aMN.v,aMN.bisectors_to_relink);    
  }
}


template<class Gt, class SS, class V>
typename Straight_skeleton_builder_2<Gt,SS,V>::MultinodePtr
Straight_skeleton_builder_2<Gt,SS,V>::CreateMultinode( Halfedge_handle begin, Halfedge_handle end )
{
  return MultinodePtr( new Multinode(begin,end) );
}


//
// Finds coincident skeleton nodes and merge them
//
// If moving edges Ei,Ej collide with moving edge Ek causing Ej to collapse, Ei and Ek becomes consecutive and a new
// polygon vertex (Ei,Ek) appears in the wavefront.
// If moving edges Ei,Ej collide with moving edge Ek causing Ek to be split in two halves, L(Ek) amd R(Ek) resp, two new 
// polygon vertices appears in the wavefront; namely: (Ei,R(Ek)) and (L(Ek),Ej))
// If moving edge Ei,Ej collide with both Ek,El simultaneously causing the edges to cross-connect, two new vertices
// (Ei,Ek) and (El,Ej) appear in the wavefront.
//
// In all those 3 cases, each new polygon vertex is represented in the straight skeleton as a skeleton node.
// Every skeleton node is describing the coallision of at least 3 edges (called the "defining edges" of the node)
// and it has at least 3 incident bisectors, each one pairing 2 out of the total number of defining egdes. 
// 
// Any skeleton node has a degree of at least 3, but if more than 3 edges collide simultaneously, the corresponding
// skeleton node has a higher degree. (the degree of the node is exactly the number of colliding edges)
//
// However, the algorithm handles the coallison of 3 edges at a time so each skeleton node initially created
// has degree exactly 3 so this function which detects higher degree nodes and merge them into a single node
// of the proper degree is needed.
//
// Two skeleton nodes are "coincident" IFF they have 2 defining edges in common and each triedge of edges collide
// at the same time and point. IOW, 2 nodes are coincident if they represent the simultaneous 
// coallison of exactly 4 edges (the union of 2 triedges with 2 common elements is a set of 4).
//
template<class Gt, class SS, class V>
void Straight_skeleton_builder_2<Gt,SS,V>::MergeCoincidentNodes()
{
  //
  // NOTE: This code might be executed on a topologically incosistent HDS, thus the need to check
  // the structure along the way.
  //

  CGAL_STSKEL_BUILDER_TRACE(0, "Merging coincident nodes...");

  // ALGORITHM DESCRIPTION:
  //
  // While circulating the bisectors along the face for edge Ei we find all those edges E* which
  // are or become consecutive to Ei during the wavefront propagation. Each bisector along the face:
  // (Ei,Ea), (Ei,Eb), (Ei,Ec), etcc pairs Ei with such other edge.
  // Between one bisector (Ei,Ea) and the next (Ei,Eb) there is skeleton node which represents
  // the coallision between the 3 edges (Ei,Ea,Eb).
  // It follows from the pairing that any skeleton node Ni, for example (Ei,Ea,Eb), neccesarily
  // shares two edges (Ei and Eb precisely) with any next skeleton node Ni+1 around the face.
  // That is, the triedge of defining edges that correspond to each skeleton node around the face follow this
  // sequence: (Ei,Ea,Eb), (Ei,Eb,Ec), (Ei,Ec,Ed), ...
  //
  // Any 2_ consecutive_ skeleton nodes around a face share 2 out of the 3 defining edges, which is one of the 
  // neccesary conditions for "coincidence". Therefore, coincident nodes can only come as consecutive along a face
  //

  MultinodeVector lMultinodes ;

  for( Face_iterator fit = mSSkel->SSkel::Base::faces_begin(); fit != mSSkel->SSkel::Base::faces_end(); ++fit)
  {
    // 'h' is the first (CCW) skeleton halfedge.
    Halfedge_handle h = validate(validate(fit->halfedge())->next());

    CGAL_assertion ( h->is_bisector() ) ;

    // 'last' is the last (CCW) skeleton halfedge
    Halfedge_handle last = validate(fit->halfedge()->prev()) ;

    CGAL_assertion ( last->is_bisector() ) ;
    CGAL_assertion ( last->vertex()->is_contour() ) ;

    Halfedge_handle h0 = h ;
    Vertex_handle   v0 = validate(h0->vertex()) ;

    CGAL_assertion ( v0->is_skeleton() ) ;

    h = validate(h->next()) ;

    while ( h != last )
    {
      Vertex_handle v = validate(h->vertex());

      CGAL_assertion ( v->is_skeleton() ) ;

      if ( !AreSkeletonNodesCoincident(v0,v) )
      {
        if ( h0->next() != h )
          lMultinodes.push_back( CreateMultinode(h0,h) );

        v0 = v ;
        h0 = h ;
      }

      h = validate(h->next());
    } 

    if ( h0->next() != h )
      lMultinodes.push_back( CreateMultinode(h0,h) );
  }

  //
  // The merging loop removes all but one of the coincident skeleton nodes and the halfedges between them.
  // But it can't physically erase those from the HDS while looping, so the nodes/bisector to erase 
  // are collected in these sequences are erased after the merging loop.
  // 
  Halfedge_handle_vector lBisectorsToRemove ;
  Vertex_handle_vector   lNodesToRemove ;

  for ( typename MultinodeVector::iterator it = lMultinodes.begin(), eit = lMultinodes.end() ; it != eit ; ++ it )
    PreprocessMultinode(**it);
    
  std::sort(lMultinodes.begin(), lMultinodes.end(), MultinodeComparer());
    
  for ( typename MultinodeVector::iterator it = lMultinodes.begin(), eit = lMultinodes.end() ; it != eit ; ++ it )
    ProcessMultinode(**it,lBisectorsToRemove,lNodesToRemove);
  
  for( Halfedge_handle_vector_iterator hi = lBisectorsToRemove.begin(), ehi = lBisectorsToRemove.end() ; hi != ehi ; ++ hi )
  {
    CGAL_STSKEL_BUILDER_TRACE(1, "B" << (*hi)->id() << " removed.");
    mSSkel->SSkel::Base::edges_erase(*hi);    
  }
    
  for( Vertex_handle_vector_iterator vi = lNodesToRemove.begin(), evi = lNodesToRemove.end() ; vi != evi ; ++ vi )
  {
    CGAL_STSKEL_BUILDER_TRACE(1, "N" << (*vi)->id() << " removed.");
    mSSkel->SSkel::Base::vertices_erase(*vi);    
  }  

}



template<class Gt, class SS, class V>
bool Straight_skeleton_builder_2<Gt,SS,V>::FinishUp()
{
  CGAL_STSKEL_BUILDER_TRACE(0, "\n\nFinishing up...");

  mVisitor.on_cleanup_started();
  
  std::for_each( mSplitNodes.begin()
                ,mSplitNodes.end  ()
                ,boost::bind(&Straight_skeleton_builder_2<Gt,SS,V>::MergeSplitNodes,this,_1)
               ) ;
  
  std::for_each( mDanglingBisectors.begin()
                ,mDanglingBisectors.end  ()
                ,boost::bind(&Straight_skeleton_builder_2<Gt,SS,V>::EraseBisector,this,_1)
               ) ;
               
  MergeCoincidentNodes();             

  mVisitor.on_cleanup_finished();

  return mSSkel->is_valid() ;
}

template<class Gt, class SS, class V>
bool Straight_skeleton_builder_2<Gt,SS,V>::Run()
{
  InitPhase();
  Propagate();
  return FinishUp();
}

template<class Gt, class SS, class V>
typename Straight_skeleton_builder_2<Gt,SS,V>::SSkelPtr Straight_skeleton_builder_2<Gt,SS,V>::construct_skeleton()
{
  bool ok = false ;
  
  try
  {
    ok = Run() ;
  }
  catch( std::exception const& e ) 
  {
    mVisitor.on_error ( e.what() ) ;
    CGAL_STSKEL_BUILDER_TRACE(0,"EXCEPTION THROWN (" << e.what() << ") during straight skeleton construction.");
 }

  if ( !ok ) 
  {
    CGAL_STSKEL_BUILDER_TRACE(0,"Invalid result.");
    mSSkel = SSkelPtr() ; 
  }

  mVisitor.on_algorithm_finished(ok);
  
  return mSSkel ;
}

CGAL_END_NAMESPACE

#if defined(BOOST_MSVC)
#  pragma warning(pop)
#endif

#endif // CGAL_STRAIGHT_SKELETON_BUILDER_2_IMPL_H //
// EOF //
