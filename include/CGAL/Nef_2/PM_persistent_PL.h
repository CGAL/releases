// ======================================================================
//
// Copyright (c) 1997-2000 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/Nef_2/PM_persistent_PL.h
// package       : Nef_2 (1.18)
// chapter       : Nef Polyhedra
//
// source        : nef_2d/PM_point_locator_2.lw
// revision      : $Revision: 1.12 $
// revision_date : $Date: 2001/12/27 15:17:39 $
//
// author(s)     : Michael Seel
// coordinator   : Michael Seel
//
// implementation: Point location module
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_PM_PERSISTENT_PL_H
#define CGAL_PM_PM_PERSISTENT_PL_H
#include <CGAL/Nef_2/gen_point_location.h>

template <typename PMPL>
struct PM_persistent_PL_traits 
{
  typedef PMPL  Graph;
  typedef typename PMPL::Vertex_const_handle   Node;
  typedef typename PMPL::Halfedge_const_handle Edge;
  typedef typename PMPL::Face_const_handle     Face;
  typedef typename PMPL::Object_handle         Object_handle;

  typedef typename PMPL::Geometry  Geometry;
  typedef typename PMPL::Point     Point;
  typedef typename PMPL::Segment   Segment;
  const Geometry* pK;

  typedef typename PMPL::Vertex_const_iterator NodeIterator;
  NodeIterator Nodes_begin(const Graph& G) const { return G.vertices_begin(); }
  NodeIterator Nodes_end(const Graph& G) const { return G.vertices_end(); }
  Node toNode(const NodeIterator& nit) const { return nit; }

  typedef typename PMPL::Halfedge_around_vertex_const_circulator HAVC;
  struct IncEdgeIterator {
    HAVC _start, _curr;
    bool met;
    IncEdgeIterator() {}
    IncEdgeIterator(HAVC c) : 
      _start(c), _curr(c), met(false) {}
    IncEdgeIterator& operator++()
    { if (_curr==_start)
        if (!met)  { met=true; ++_curr; }
        else       { _curr=HAVC(); }
      else ++_curr;
      return *this; 
    }
    bool operator==(const IncEdgeIterator& it2) const
    { return _curr==it2._curr; }
    bool operator!=(const IncEdgeIterator& it2) const
    { return !(*this==it2); }
  };
  Edge toEdge(const IncEdgeIterator& eit) const { return eit._curr; }

  IncEdgeIterator IncEdges_begin(const Graph& G, const Node& n) 
  { return IncEdgeIterator(HAVC(G.first_out_edge(n))); }
  IncEdgeIterator IncEdges_end(const Graph& G, const Node& n)   
  { return IncEdgeIterator(); }

  enum EdgeCategory 
  { StartingNonVertical, StartingVertical, EndingNonVertical, EndingVertical };

  Node opposite(const Graph& G, const Edge& e, const Node& u)
  { if ( G.source(e) == u ) return G.target(e);
    else                    return G.source(e); }

  EdgeCategory ClassifyEdge(const Graph& G, const Edge& e, const Node& u)
  {
    Point p_u = G.point(u);
    Point p_v = G.point(opposite(G,e,u));

    int cmpX = pK->compare_x(p_u, p_v);
    if ( cmpX < 0 ) return StartingNonVertical;
    if ( cmpX > 0 ) return EndingNonVertical;

    int cmpY = pK->compare_y(p_u, p_v); 
    assert(cmpY != 0);
    if ( cmpY < 0 ) return StartingVertical;
    return EndingVertical;
  }    

  typedef Point XCoord;
  const XCoord getXCoord(const Point& p) const 
  { return p; }
  const XCoord getXCoord(const Graph& G, const Node& n) const 
  { return G.point(n); }

  class PredLessThanX {
    const Geometry* pK;
  public:
    PredLessThanX() : pK(0) {}
    PredLessThanX(const Geometry* pKi) : pK(pKi) {}
    PredLessThanX(const PredLessThanX& P) : pK(P.pK) 
    { TRACEN("copy PredLessThanX"); }
    int operator() (const XCoord& x1, const XCoord& x2) const
    { return pK->compare_x(x1,x2) < 0; }
  };
  PredLessThanX getLessThanX() const { return PredLessThanX(pK); }

  // Curve connected functionality:
  typedef Segment  Curve;

  Curve makeCurve(const Point& p) const 
  { return pK->construct_segment(p,p); }
  Curve makeCurve(const Graph& G, const Node& n) const
  { return makeCurve(G.point(n)); }
  Curve makeCurve(const Graph& G, const Edge& e) const
  { Point ps = G.point(G.source(e)), pt = G.point(G.target(e));
    Curve res(G.point(G.source(e)),G.point(G.target(e)));
    if ( pK->compare_xy(ps,pt) < 0 ) res = pK->construct_segment(ps,pt);
    else                             res = pK->construct_segment(pt,ps);
    return res; 
  }

  struct PredCompareCurves {
   const Geometry* pK;
   PredCompareCurves() : pK(0) {}
   PredCompareCurves(const Geometry* pKi) : pK(pKi) {}
   PredCompareCurves(const PredCompareCurves& P) : pK(P.pK) {}

   int cmppntseg(const Point& p, const Curve& s) const
   { 
     if ( pK->compare_x(pK->source(s),pK->target(s)) != 0 ) // !vertical
       return pK->orientation(pK->source(s),pK->target(s), p); 
     if ( pK->compare_y(p,pK->source(s)) <= 0 ) return -1;
     if ( pK->compare_y(p,pK->target(s)) >= 0 ) return +1;
     return 0;
   }

   int operator()(const Curve& s1, const Curve& s2) const
   { 
     Point a = pK->source(s1); 
     Point b = pK->target(s1);
     Point c = pK->source(s2);
     Point d = pK->target(s2);
     if ( a==b ) 
       if ( c==d ) return pK->compare_y(a,c);
       else        return  cmppntseg(a, s2);
     if ( c==d )   return -cmppntseg(c, s1);
     // now both are non-trivial:
     int cmpX = pK->compare_x(a, c);
     if ( cmpX < 0 ) 
       return - pK->orientation(a,b,c);
     if ( cmpX > 0 ) 
       return   pK->orientation(c,d,a);

     int cmpY = pK->compare_y(a, c);
     if ( cmpY < 0 ) return -1;
     if ( cmpY > 0 )  return +1;
      
     // cmpX == cmpY == 0 => a == c
     return pK->orientation(c,d,b);
   }
  };

  PredCompareCurves getCompareCurves() const
  { return PredCompareCurves(pK); }

  typedef GenericLocation<Node, Edge> Location;
  typedef Object_handle QueryResult;

  virtual Object_handle 
  PostProcess(const Location& L, const Location& L_plus, 
    const Point& p) const 
  { /* we only get an L_plus (non-nil) if L is ABOVE a vertex
       in which case we want to extract the face from the edge
       below (p+epsilon) available via L_plus. */
    if (!L_plus.is_nil()) { assert(L_plus.is_edge());
      return Object_handle(Edge(L_plus));
    } else { 
      if ( L.is_edge() ) {
        return Object_handle(Edge(L));
      }
      if ( L.is_node() ) {
        Node v(L); assert( v != Node() );
        return Object_handle(v);
      }
      return Object_handle();
    }
  }

  PM_persistent_PL_traits() : pK(0) {}
  PM_persistent_PL_traits(const Geometry& k) : pK(&k) {}
  virtual ~PM_persistent_PL_traits() {}
  virtual void sweep_begin(const Graph&) {}
  virtual void sweep_moveto(const XCoord&) {}
  virtual void sweep_end() {}
  virtual void clear() {}

};


#endif // CGAL_PM_PM_PERSISTENT_PL_H

