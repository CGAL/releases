// Copyright (c) 2005, 2006 Fernando Luis Cacciola Carballal. All rights reserved.
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

// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.2-branch/Straight_skeleton_2/include/CGAL/Straight_skeleton_builder_2.h $
// $Id: Straight_skeleton_builder_2.h 29770 2006-03-26 16:16:40Z fcacciola $
//
// Author(s)     : Fernando Cacciola <fernando_cacciola@ciudad.com.ar>
//
#ifndef CGAL_STRAIGHT_SKELETON_BUILDER_2_H
#define CGAL_STRAIGHT_SKELETON_BUILDER_2_H 1

#include <list>
#include <queue>
#include <exception>
#include <string>

#include <boost/tuple/tuple.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <CGAL/algorithm.h>
#include <CGAL/Straight_skeleton_aux.h>
#include <CGAL/Straight_skeleton_2.h>
#include <CGAL/Straight_skeleton_builder_traits_2.h>
#include <CGAL/Straight_skeleton_builder_events_2.h>
#include <CGAL/HalfedgeDS_const_decorator.h>
#include <CGAL/enum.h>

CGAL_BEGIN_NAMESPACE

template<class Traits_, class SSkel_>
class Straight_skeleton_builder_2
{
public:

  typedef Traits_ Traits ;
  typedef SSkel_  SSkel ;
  
  typedef boost::shared_ptr<SSkel> SSkelPtr ;

  typedef typename SSkel::Traits::Segment_2 Segment_2 ;

private :

  typedef typename Traits::FT      FT ;
  typedef typename Traits::Point_2 Point_2 ;

  typedef typename SSkel::Vertex   Vertex ;
  typedef typename SSkel::Halfedge Halfedge ;
  typedef typename SSkel::Face     Face ;

  typedef typename SSkel::Vertex_const_handle   Vertex_const_handle ;
  typedef typename SSkel::Halfedge_const_handle Halfedge_const_handle ;
  typedef typename SSkel::Face_const_handle     Face_const_handle ;

  typedef typename SSkel::Vertex_const_iterator   Vertex_const_iterator ;
  typedef typename SSkel::Halfedge_const_iterator Halfedge_const_iterator ;
  typedef typename SSkel::Face_const_iterator     Face_const_iterator ;

  typedef typename SSkel::Vertex_handle   Vertex_handle ;
  typedef typename SSkel::Halfedge_handle Halfedge_handle ;
  typedef typename SSkel::Face_handle     Face_handle ;

  typedef typename SSkel::Vertex_iterator   Vertex_iterator ;
  typedef typename SSkel::Halfedge_iterator Halfedge_iterator ;
  typedef typename SSkel::Face_iterator     Face_iterator ;

  typedef typename Vertex::Halfedge_around_vertex_circulator Halfedge_around_vertex_circulator ;
  
  typedef typename SSkel::size_type size_type ;

  typedef Straight_skeleton_builder_event_2<SSkel>        Event ;
  typedef Straight_skeleton_builder_edge_event_2<SSkel>   EdgeEvent ;
  typedef Straight_skeleton_builder_split_event_2<SSkel>  SplitEvent ;
  typedef Straight_skeleton_builder_vertex_event_2<SSkel> VertexEvent ;

  typedef boost::intrusive_ptr<Event> EventPtr ;

  typedef std::vector<EventPtr>        EventPtr_Vector ;
  typedef std::vector<Halfedge_handle> Halfedge_handle_vector ;
  typedef std::vector<Vertex_handle>   Vertex_handle_vector ;

  typedef typename Halfedge_handle_vector::iterator Halfedge_handle_vector_iterator ;
  typedef typename Vertex_handle_vector  ::iterator Vertex_handle_vector_iterator ;
  typedef typename EventPtr_Vector       ::iterator event_iterator ;

  typedef boost::tuple<Halfedge_handle, Halfedge_handle, Halfedge_handle> BorderTriple ;

  typedef CGAL_SS_i::Vertex <FT> iVertex ;
  typedef CGAL_SS_i::Edge   <FT> iEdge ;
  typedef CGAL_SS_i::Triedge<FT> iTriedge ;

  typedef Straight_skeleton_builder_2<Traits,SSkel> Self ;
  
  typedef typename Halfedge::Base_base HBase_base ;
  typedef typename Halfedge::Base      HBase ;
  typedef typename Vertex::Base        VBase ;
  typedef typename Face::Base          FBase ;
  
public:

  struct straight_skeleton_exception : std::runtime_error
  {
    straight_skeleton_exception( std::string what ) : std::runtime_error(what) {}  
  } ;
  
  Straight_skeleton_builder_2 ( Traits const& = Traits() ) ;

  // NOTE: The following public method is implemented here in this header file to support some broken compilers.
  // But it's right at the end of the class declaration becuause it needs all of the class.
  //
  // template<class InputPointIterator> Straight_skeleton_builder_2& enter_contour ( InputPointIterator aBegin, InputPointIterator aEnd ) ;


  SSkelPtr construct_skeleton() ;

private :

  void throw_error ( char const* what ) const ;
  
  class Event_compare : public std::binary_function<bool,EventPtr,EventPtr>
  {
  public:

    Event_compare ( Self const& aBuilder ) : mBuilder(aBuilder) {}

    bool operator() ( EventPtr const& aA, EventPtr const& aB ) const
    {
      return mBuilder.CompareEvents(aA,aB) == LARGER ;
    }

  private:

    Self const& mBuilder ;
  } ;


  typedef std::priority_queue<EventPtr,std::vector<EventPtr>,Event_compare> PQ ;

  typedef std::pair<Vertex_handle,Vertex_handle> Vertex_handle_pair ;

  typedef std::vector<Vertex_handle_pair> SplitNodesVector ;

  struct VertexWrapper
  {
    VertexWrapper( Vertex_handle aVertex )
        :
        mVertex(aVertex)
      , mIsReflex(false)
      , mIsProcessed(false)
      , mIsExcluded(false)
      , mPrev(-1)
      , mNext(-1)
    {}

    Vertex_handle   mVertex ;
    bool            mIsReflex ;
    bool            mIsProcessed ;
    bool            mIsExcluded ;
    int             mPrev ;
    int             mNext ;
    Halfedge_handle mDefiningBorderA ;
    Halfedge_handle mDefiningBorderB ;
    Halfedge_handle mDefiningBorderC ;
    EventPtr_Vector mReflexSplits ; // For fast vertex-event discovery.
  } ;

private :

  inline Halfedge_handle validate( Halfedge_handle aH ) const
  {
    if ( !handle_assigned(aH) )
      throw_error("Unassigned halfedge handle") ;
    return aH ;
  }
  
  inline Vertex_handle validate( Vertex_handle aH ) const
  {
    if ( !handle_assigned(aH) )
      throw_error("Unassigned vertex handle") ;
    return aH ;
  }
  
  inline Halfedge_handle GetDefiningBorderA ( Vertex_handle aV ) const
  {
    return mWrappedVertices[aV->id()].mDefiningBorderA ;
  }
  inline Halfedge_handle GetDefiningBorderB ( Vertex_handle aV ) const
  {
    return mWrappedVertices[aV->id()].mDefiningBorderB ;
  }
  inline Halfedge_handle GetDefiningBorderC ( Vertex_handle aV ) const
  {
    return mWrappedVertices[aV->id()].mDefiningBorderC ;
  }
  inline void SetDefiningBorderA ( Vertex_handle aV, Halfedge_handle aH )
  {
    mWrappedVertices[aV->id()].mDefiningBorderA = aH ;
  }
  inline void SetDefiningBorderB ( Vertex_handle aV, Halfedge_handle aH )
  {
    mWrappedVertices[aV->id()].mDefiningBorderB = aH ;
  }
  inline void SetDefiningBorderC ( Vertex_handle aV, Halfedge_handle aH )
  {
    mWrappedVertices[aV->id()].mDefiningBorderC = aH ;
  }

  inline iEdge CreateEdge ( Halfedge_const_handle aH ) const
  {
    Point_2 s = aH->opposite()->vertex()->point() ;
    Point_2 t = aH->vertex()->point() ;
    return Construct_ss_edge_2<Traits>(mTraits)()(s,t);
  }

  inline iTriedge CreateTriedge ( Halfedge_const_handle aE0
                                , Halfedge_const_handle aE1
                                , Halfedge_const_handle aE2
                                ) const
  {
    return Construct_ss_triedge_2<Traits>(mTraits)()(CreateEdge(aE0),CreateEdge(aE1),CreateEdge(aE2));
  }

  inline iTriedge CreateTriedge ( BorderTriple const& aTriple ) const
  {
    Halfedge_handle lE0, lE1, lE2 ;
    boost::tie(lE0,lE1,lE2) = aTriple ;
    return Construct_ss_triedge_2<Traits>(mTraits)()(CreateEdge(lE0),CreateEdge(lE1),CreateEdge(lE2));
  }

  Vertex_handle GetVertex ( int aIdx )
  {
    return mWrappedVertices[aIdx].mVertex ;
  }

  Vertex_handle GetPrevInLAV ( Vertex_handle aV )
  {
    return GetVertex ( mWrappedVertices[aV->id()].mPrev ) ;
  }

  Vertex_handle GetNextInLAV ( Vertex_handle aV )
  {
    return GetVertex ( mWrappedVertices[aV->id()].mNext ) ;
  }

  Vertex_handle GetNextInLAV_NonSkeleton ( Vertex_handle aV )
  {
    Vertex_handle lNext = GetNextInLAV(aV);
    while ( lNext->is_skeleton() )
      lNext = GetNextInLAV(lNext);
    return lNext;
  }

  void SetPrevInLAV ( Vertex_handle aV, Vertex_handle aPrev )
  {
    mWrappedVertices[aV->id()].mPrev = aPrev->id();
  }

  void SetNextInLAV ( Vertex_handle aV, Vertex_handle aPrev )
  {
    mWrappedVertices[aV->id()].mNext = aPrev->id();
  }

  BorderTriple GetSkeletonVertexDefiningBorders( Vertex_handle aVertex ) const
  {
    CGAL_precondition(aVertex->is_skeleton() ) ;

    return boost::make_tuple( GetDefiningBorderA(aVertex)
                            , GetDefiningBorderB(aVertex)
                            , GetDefiningBorderC(aVertex)
                            ) ;
  }

  void Exclude ( Vertex_handle aVertex )
  {
    mWrappedVertices[aVertex->id()].mIsExcluded = true ;
  }
  bool IsExcluded ( Vertex_const_handle aVertex ) const
  {
    return mWrappedVertices[aVertex->id()].mIsExcluded ;
  }

  void SetIsReflex ( Vertex_handle aVertex )
  {
    mWrappedVertices[aVertex->id()].mIsReflex = true ;
  }

  bool IsReflex ( Vertex_handle aVertex )
  {
    return mWrappedVertices[aVertex->id()].mIsReflex ;
  }

  void SetIsProcessed ( Vertex_handle aVertex )
  {
    mWrappedVertices[aVertex->id()].mIsProcessed = true ;
  }

  bool IsProcessed ( Vertex_handle aVertex )
  {
    return mWrappedVertices[aVertex->id()].mIsProcessed ;
  }

  void AddReflexSplit ( Vertex_handle aSeed, EventPtr aReflexSplit )
  {
    return mWrappedVertices[aSeed->id()].mReflexSplits.push_back(aReflexSplit) ;
  }
  EventPtr_Vector const& GetReflexSplits ( Vertex_handle aSeed )
  {
    return mWrappedVertices[aSeed->id()].mReflexSplits  ;
  }

  void EnqueEvent( EventPtr aEvent )
  {
    mPQ.push(aEvent);
    CGAL_SSBUILDER_TRACE(0, *aEvent);
  }

  EventPtr PopEventFromPQ()
  {
    EventPtr rR = mPQ.top();
    mPQ.pop();
    return rR ;
  }

  // Returns 1 aE is in the set (aA,aB,aC), 0 otherwise
  int CountInCommon( Halfedge_handle aE, Halfedge_handle aA, Halfedge_handle aB, Halfedge_handle aC ) const
  {
    return aE == aA || aE == aB || aE == aC ? 1 : 0 ;
  }

  // Returns the number of common halfedges in the sets (aXA,aXB,aXC) and (aYA,aYB,aYC)
  int CountInCommon( Halfedge_handle aXA, Halfedge_handle aXB, Halfedge_handle aXC
                   , Halfedge_handle aYA, Halfedge_handle aYB, Halfedge_handle aYC
                   ) const
  {
    return   CountInCommon(aXA,aYA,aYB,aYC)
           + CountInCommon(aXB,aYA,aYB,aYC)
           + CountInCommon(aXC,aYA,aYB,aYC) ;
  }

  // Returns true if the intersection of the sets (aXA,aXB,aXC) and (aYA,aYB,aYC) has size exactly 2
  // (that is, both sets have 2 elements in common)
  bool HaveTwoInCommon( Halfedge_handle aXA, Halfedge_handle aXB, Halfedge_handle aXC
                      , Halfedge_handle aYA, Halfedge_handle aYB, Halfedge_handle aYC
                      ) const
  {
    return CountInCommon(aXA,aXB,aXC,aYA,aYB,aYC) == 2 ;
  }
  
  // Returns true if the intersection of the sets (aXA,aXB,aXC) and (aYA,aYB,aYC) has size exactly 2
  // (that is, both sets have 2 elements in common)
  bool HaveTwoInCommon( BorderTriple aX, BorderTriple aY ) const
  {
    Halfedge_handle lXA, lXB, lXC, lYA, lYB, lYC ;
    boost::tie(lXA,lXB,lXC) = aX ;
    boost::tie(lYA,lYB,lYC) = aY ;
    return CountInCommon(lXA,lXB,lXC,lYA,lYB,lYC) == 2 ;
  }

  // Returns true if the sets of halfedges (aXA,aXB,aXC) and (aYA,aYB,aYC) are equivalent
  // (one is a permutation of the other)
  bool AreTheSameTriple( Halfedge_handle aXA, Halfedge_handle aXB, Halfedge_handle aXC
                       , Halfedge_handle aYA, Halfedge_handle aYB, Halfedge_handle aYC
                       ) const
  {
    return CountInCommon(aXA,aXB,aXC,aYA,aYB,aYC) == 3 ;
  }

  // Returns the 0-base index of the one element from (aX[3]) NOT IN (aY[3])
  // NOTE: This function shall be called only when it is known that such an element exists
  // as 2 is returned by default without proper testing. That is, this function is for vertex-event analysis only.
  int GetUnique( Halfedge_handle aX[], Halfedge_handle aY[] ) const
  {
    return CountInCommon(aX[0],aY[0],aY[1],aY[2]) == 0 ? 0
             : CountInCommon(aX[1],aY[0],aY[1],aY[2]) == 0 ? 1
               : 2 ;
  }

  // Sorts the elements in the sets aX[2] and aY[3] returing (D0,D1,E0,E1)
  // where D0,D1 are unique elements in aX and aY respectively and E0,E1 are elements in common.
  // NOTE: This function shall only be called when it is known that thet sets aX and aY can indeed be sorted this way.
  // That is, this function is for vertex-event analysis only.
  boost::tuple<Halfedge_handle,Halfedge_handle,Halfedge_handle,Halfedge_handle>
    SortTwoDistinctAndTwoEqual( Halfedge_handle aX[], Halfedge_handle aY[] ) const
  {
     int lUniqueX = GetUnique(aX,aY) ;
     int lUniqueY = GetUnique(aY,aX) ;
     int lCommon1 = ( lUniqueX + 1 ) % 3 ;
     int lCommon2 = ( lUniqueX + 2 ) % 3 ;
     return boost::make_tuple(aX[lUniqueX],aY[lUniqueY],aX[lCommon1],aX[lCommon2]);
  }


  bool ExistEvent ( Halfedge_const_handle aE0, Halfedge_const_handle aE1, Halfedge_const_handle aE2 ) const
  {
    return Do_ss_event_exist_2<Traits>(mTraits)()(CreateTriedge(aE0, aE1, aE2));
  }

  bool IsEventInsideOffsetZone( Halfedge_const_handle aReflexL
                              , Halfedge_const_handle aReflexR
                              , Halfedge_const_handle aOpposite
                              , Halfedge_const_handle aOppositePrev
                              , Halfedge_const_handle aOppositeNext
                              ) const
  {
    return Is_ss_event_inside_offset_zone_2<Traits>(mTraits)()( CreateTriedge(aReflexL     , aReflexR, aOpposite)
                                                              , CreateTriedge(aOppositePrev,aOpposite, aOppositeNext)
                                                              ) ;
  }

  Comparison_result CompareEvents ( iTriedge const& aA, iTriedge const& aB ) const
  {
    return Compare_ss_event_times_2<Traits>(mTraits)()(aA,aB) ;
  }

  Comparison_result CompareEvents ( EventPtr const& aA, EventPtr const& aB ) const
  {
    if ( !AreTheSameTriple( aA->border_a(), aA->border_b(), aA->border_c()
                          , aB->border_a(), aB->border_b(), aB->border_c()
                          )
        )
    {
      return CompareEvents( CreateTriedge(aA->border_a(), aA->border_b(), aA->border_c())
                          , CreateTriedge(aB->border_a(), aB->border_b(), aB->border_c())
                          ) ;
    }
    else return EQUAL ;
  }

  Comparison_result CompareEventsDistanceToSeed ( Vertex_handle   aSeed
                                                , EventPtr const& aA
                                                , EventPtr const& aB
                                                ) const
  {
    if ( !AreTheSameTriple( aA->border_a(), aA->border_b(), aA->border_c()
                          , aB->border_a(), aB->border_b(), aB->border_c()
                          )
        )
    {
      if ( aSeed->is_skeleton() )
      {
        BorderTriple lTriple = GetSkeletonVertexDefiningBorders(aSeed);

        CGAL_SSBUILDER_TRACE(3
                            ,"Seed N" << aSeed->id() << " is a skeleton node,"
                            << " defined by: E" << lTriple.get<0>()->id()
                                       << ", E" << lTriple.get<1>()->id()
                                       << ", E" << lTriple.get<2>()->id()
                            );

        return Compare_ss_event_distance_to_seed_2<Traits>(mTraits)()( CreateTriedge(lTriple)
                                                                     , CreateTriedge(aA->border_a(), aA->border_b(), aA->border_c())
                                                                     , CreateTriedge(aB->border_a(), aB->border_b(), aB->border_c())
                                                                     ) ;
      }
      else
      {
        return Compare_ss_event_distance_to_seed_2<Traits>(mTraits)()( aSeed->point()
                                                                     , CreateTriedge(aA->border_a(), aA->border_b(), aA->border_c())
                                                                     , CreateTriedge(aB->border_a(), aB->border_b(), aB->border_c())
                                                                     ) ;
      }
    }
    else return EQUAL ;
  }
  
  bool AreEventsSimultaneous( EventPtr const& aX, EventPtr const& aY ) const
  {
    Halfedge_handle xa = aX->border_a() ;
    Halfedge_handle xb = aX->border_b() ;
    Halfedge_handle xc = aX->border_c() ;
    Halfedge_handle ya = aY->border_a() ;
    Halfedge_handle yb = aY->border_b() ;
    Halfedge_handle yc = aY->border_c() ;

    if ( HaveTwoInCommon(xa,xb,xc,ya,yb,yc) )
         return Are_ss_events_simultaneous_2<Traits>(mTraits)()( CreateTriedge(xa,xb,xc), CreateTriedge(ya,yb,yc)) ;
    else return false ;
  }

  bool AreSkeletonNodesCoincident( Vertex_handle aX, Vertex_handle aY ) const
  {
    BorderTriple lBordersX = GetSkeletonVertexDefiningBorders(aX);
    BorderTriple lBordersY = GetSkeletonVertexDefiningBorders(aY);
    return Are_ss_events_simultaneous_2<Traits>(mTraits)()( CreateTriedge(lBordersX), CreateTriedge(lBordersY)) ;
  }
  
  bool IsNewEventInThePast( Halfedge_handle aBorderA
                          , Halfedge_handle aBorderB
                          , Halfedge_handle aBorderC
                          , Vertex_handle   aSeedNode
                          ) const
  {
    bool rResult = false ;

    Halfedge_handle lSeedBorderA, lSeedBorderB, lSeedBorderC ;

    boost::tie(lSeedBorderA,lSeedBorderB,lSeedBorderC) = GetSkeletonVertexDefiningBorders(aSeedNode) ;

    if ( !AreTheSameTriple(aBorderA,aBorderB,aBorderC,lSeedBorderA,lSeedBorderB,lSeedBorderC) )
    {
      if ( CompareEvents( CreateTriedge(aBorderA,aBorderB,aBorderC)
                        , CreateTriedge(lSeedBorderA,lSeedBorderB,lSeedBorderC)
                        ) == SMALLER
         )
      {
        rResult = true ;
      }   
    }

    return rResult ;
  }

  boost::tuple< boost::optional<FT>, boost::optional<Point_2> >  ConstructEventTimeAndPoint( iTriedge const& aTri ) const
  {
    return Construct_ss_event_time_and_point_2<Traits>(mTraits)()(aTri);
  }

  void SetEventTimeAndPoint( Event& aE )
  {
    boost::optional<FT>      lTime ;
    boost::optional<Point_2> lP ;
    boost::tie(lTime,lP) = ConstructEventTimeAndPoint( CreateTriedge(aE.border_a(),aE.border_b(),aE.border_c()) );
    
    if ( !lTime || !lP )
      throw_error("CGAL_STRAIGHT_SKELETON: Overflow during skeleton node computation."); // Contained in the main entry function
    
    aE.SetTimeAndPoint(*lTime,*lP);
  }

  void EraseBisector( Halfedge_handle aB )
  {
    mSSkel->SSkel::Base::edges_erase(aB);
  }

  BorderTriple GetDefiningBorders( Vertex_handle aA, Vertex_handle aB ) ;

  bool AreBisectorsCoincident ( Halfedge_const_handle aA, Halfedge_const_handle aB ) const ;

  void CollectSplitEvent( Vertex_handle    aNode
                        , Halfedge_handle  aReflexLBorder
                        , Halfedge_handle  aReflexRBorder
                        , Halfedge_handle  aOppositeBorder
                        ) ;

  void CollectSplitEvents( Vertex_handle aNode ) ;

  EventPtr FindEdgeEvent( Vertex_handle aLNode, Vertex_handle aRNode ) ;


  EventPtr FindVertexEvent( EventPtr aE0, Vertex_handle aOV ) ;
  EventPtr FindVertexEvent( EventPtr aE0 ) ;

  void HandleSimultaneousEdgeEvent( Vertex_handle aA, Vertex_handle aB ) ;

  void CollectNewEvents( Vertex_handle aNode ) ;
  void UpdatePQ( Vertex_handle aV ) ;
  void CreateInitialEvents();
  void CreateContourBisectors();
  void InitPhase();

  bool SetupVertexEventNode( Vertex_handle   aNode
                           , Halfedge_handle aDefiningBorderA
                           , Halfedge_handle aDefiningBorderB
                           );

  Vertex_handle LookupOnSLAV ( Halfedge_handle aOBorder, Event const& aEvent ) ;

  Vertex_handle_pair ConstructSplitEventNodes ( SplitEvent&  aEvent, Vertex_handle aOppR ) ;
  Vertex_handle      ConstructEdgeEventNode   ( EdgeEvent&   aEvent ) ;
  Vertex_handle_pair ConstructVertexEventNodes( VertexEvent& aEvent ) ;

  void HandleSplitEvent          ( EventPtr aEvent, Vertex_handle aOppR ) ;
  void HandleEdgeEvent           ( EventPtr aEvent ) ;
  void HandleVertexEvent         ( EventPtr aEvent ) ;
  void HandlePotentialSplitEvent ( EventPtr aEvent ) ;
  bool IsProcessed               ( EventPtr aEvent ) ;

  void Propagate();

  void MergeSplitNodes ( Vertex_handle_pair aSplitNodes ) ;

  void MergeCoincidentNodes( Vertex_handle           v0
                           , Vertex_handle           v1 
                           , Halfedge_handle_vector& rHalfedgesToRemove
                           , Vertex_handle_vector&   rVerticesToRemove
                           ) ;
  
  void MergeCoincidentNodes() ;
  
  void FinishUp();

  void Run();

private:

#ifdef CGAL_STRAIGHT_SKELETON_ENABLE_SHOW
  template<class Halfedge>
  void DrawBisector ( Halfedge aHalfedge )
  {
    SS_IO_AUX::ScopedSegmentDrawing draw_( aHalfedge->opposite()->vertex()->point()
                                         , aHalfedge->vertex()->point()
                                         , aHalfedge->is_inner_bisector() ? CGAL::BLUE  : CGAL::GREEN
                                         , aHalfedge->is_inner_bisector() ? "IBisector" : "CBisector"
                                         ) ;
    draw_.Release();
  }

#endif


private:

  //Input
  Traits mTraits ;

  typename Traits::Equal_2     Equal ;
  typename Traits::Left_turn_2 Left_turn ;
  typename Traits::Collinear_2 Collinear ;

  std::vector<VertexWrapper> mWrappedVertices ;
  Halfedge_handle_vector     mDanglingBisectors ;
  Halfedge_handle_vector     mContourHalfedges ;

  std::list<Vertex_handle> mSLAV ;

//  EventPtr_Vector  mSplitEvents ;
  SplitNodesVector mSplitNodes ;

  Event_compare mEventCompare ;

  int mVertexID ;
  int mEdgeID   ;
  int mEventID  ;
  int mStepID   ;

  PQ mPQ ;

  //Output
  SSkelPtr mSSkel ;

public:

  template<class InputPointIterator>
  Straight_skeleton_builder_2& enter_contour ( InputPointIterator aBegin, InputPointIterator aEnd  )
  {
    CGAL_SSBUILDER_TRACE(0,"Inserting Connected Component of the Boundary....");

    Halfedge_handle lFirstCCWBorder ;
    Halfedge_handle lPrevCCWBorder ;
    Halfedge_handle lNextCWBorder ;
    Vertex_handle   lFirstVertex ;
    Vertex_handle   lPrevVertex ;

    InputPointIterator lLast = CGAL::predecessor(aEnd) ;
     
    // Remove last points coincident with the first point.
    while ( lLast != aBegin )
    {
      if ( Equal(*lLast,*aBegin) )
        -- lLast ;
      else break ;  
    }    
    
    aEnd = CGAL::successor(lLast);
    
    InputPointIterator lCurr = aBegin ;
    InputPointIterator lPrev = aBegin ;
    
    int c = 0 ;
    
    while ( lCurr != aEnd )
    {
      // Skip ahead consecutive coincident vertices.
      if (  ( lCurr != aBegin && Equal(*lPrev,*lCurr) )
         || ( lCurr != lLast  && Equal(*lCurr,*lLast) )
         )
      {
        ++ lCurr ;
        continue ;
      }
      
      Halfedge_handle lCCWBorder = mSSkel->SSkel::Base::edges_push_back ( Halfedge(mEdgeID),Halfedge(mEdgeID+1)  );
      Halfedge_handle lCWBorder = lCCWBorder->opposite();
      mEdgeID += 2 ;

      mContourHalfedges.push_back(lCCWBorder);

      Vertex_handle lVertex = mSSkel->SSkel::Base::vertices_push_back( Vertex(mVertexID++,*lCurr) ) ;
      CGAL_SSBUILDER_TRACE(2,"Vertex: V" << lVertex->id() << " at " << lVertex->point() );
      mWrappedVertices.push_back( VertexWrapper(lVertex) ) ;

      Face_handle lFace = mSSkel->SSkel::Base::faces_push_back( Face() ) ;

      ++ c ;
      
      lCCWBorder->HBase_base::set_face(lFace);
      lFace     ->FBase::set_halfedge(lCCWBorder);

      lVertex   ->VBase::set_halfedge(lCCWBorder);
      lCCWBorder->HBase_base::set_vertex(lVertex);

      if ( lCurr == aBegin )
      {
        lFirstVertex    = lVertex ;
        lFirstCCWBorder = lCCWBorder ;
      }
      else
      {
        SetPrevInLAV(lVertex    ,lPrevVertex);
        SetNextInLAV(lPrevVertex,lVertex    );

        SetDefiningBorderA(lVertex    ,lCCWBorder);
        SetDefiningBorderB(lPrevVertex,lCCWBorder);

        lCWBorder->HBase_base::set_vertex(lPrevVertex);

        lCCWBorder    ->HBase_base::set_prev(lPrevCCWBorder);
        lPrevCCWBorder->HBase_base::set_next(lCCWBorder);

        lNextCWBorder->HBase_base::set_prev(lCWBorder);
        lCWBorder    ->HBase_base::set_next(lNextCWBorder);

        CGAL_SSBUILDER_TRACE(2,"CCW Border: E" << lCCWBorder->id() << ' ' << lPrevVertex->point() << " -> " << lVertex    ->point());
        CGAL_SSBUILDER_TRACE(2,"CW  Border: E" << lCWBorder ->id() << ' ' << lVertex    ->point() << " -> " << lPrevVertex->point() );

        CGAL_SSBUILDER_SHOW
        ( 
          SS_IO_AUX::ScopedSegmentDrawing draw_(lPrevVertex->point(),lVertex->point(), CGAL::RED, "Border" ) ;
          draw_.Release();
        )
      }

      lPrev = lCurr ;
      
      ++ lCurr ;

      lPrevVertex    = lVertex ;
      lPrevCCWBorder = lCCWBorder ;
      lNextCWBorder  = lCWBorder ;
    }

    SetPrevInLAV(lFirstVertex,lPrevVertex );
    SetNextInLAV(lPrevVertex ,lFirstVertex);

    SetDefiningBorderA(lFirstVertex,lFirstCCWBorder);
    SetDefiningBorderB(lPrevVertex ,lFirstCCWBorder);

    lFirstCCWBorder->opposite()->HBase_base::set_vertex(lPrevVertex);

    CGAL_SSBUILDER_SHOW
    ( SS_IO_AUX::ScopedSegmentDrawing draw_(lPrevVertex->point(),lFirstVertex->point(), CGAL::RED, "Border" ) ;
      draw_.Release();
    )

    lFirstCCWBorder->HBase_base::set_prev(lPrevCCWBorder);
    lPrevCCWBorder ->HBase_base::set_next(lFirstCCWBorder);

    lPrevCCWBorder ->opposite()->HBase_base::set_prev(lFirstCCWBorder->opposite());
    lFirstCCWBorder->opposite()->HBase_base::set_next(lPrevCCWBorder ->opposite());

    CGAL_SSBUILDER_TRACE(2
                        , "CCW Border: E" << lFirstCCWBorder->id()
                        << ' ' << lPrevVertex ->point() << " -> " << lFirstVertex->point() << '\n'
                        << "CW  Border: E" << lFirstCCWBorder->opposite()->id()
                        << ' ' << lFirstVertex->point() << " -> " << lPrevVertex ->point()
                        );
     
    CGAL_precondition_msg(c >=3, "The contour must have at least 3 _distinct_ vertices" ) ;

    return *this ;
  }

} ;

CGAL_END_NAMESPACE

#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#  include <CGAL/Straight_skeleton_builder_2.C>
#endif


#endif // CGAL_STRAIGHT_SKELETON_BUILDER_2_H //
// EOF //
