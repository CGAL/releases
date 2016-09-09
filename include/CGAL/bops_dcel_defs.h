//  -*- Mode: c++ -*-
// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/bops_dcel_defs.h
// package       : bops (1.1.2)
// source        : include/CGAL/bops_dcel_defs.h
// revision      : $Revision: 1.1.2 $
// revision_date : $Date: Wed Dec  9 13:28:51 MET 1998  $
// author(s)     :             Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL__DCEL_DEFS_H
#define CGAL__DCEL_DEFS_H

#include <CGAL/basic.h>

#include <pair.h>
#include <list.h>
#include <vector.h>
#include <set.h>
#include <algo.h>

#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Object.h>


#ifdef CGAL__DCEL_DEBUG_ON

# define  _DOUT cout

#  define CGAL__BOPS_DCEL_DEBUG(_t_) _DOUT << _t_ << flush
#  define CGAL__BOPS_DCEL_DEBUG_LN(_t_) _DOUT << _t_ << endl << flush
#  define CGAL__BOPS_DCEL_DEBUG_VAR(_t_,_v_) \
          _DOUT << _t_ << _v_ << endl << flush
#  define CGAL__BOPS_DCEL_DEBUG_PAIR(_t_,_p1_,_p2_)\
          _DOUT << _t_ << '(' << _p1_ << ',' << _p2_ << ')' << flush
#  define CGAL__BOPS_DCEL_DEBUG_ITERATOR(_text_, _begin_, _end_)\
          print(_DOUT, _text_, _begin_, _end_) << flush

#else

#  define CGAL__BOPS_DCEL_DEBUG(_t_)
#  define CGAL__BOPS_DCEL_DEBUG_LN(_t_) 
#  define CGAL__BOPS_DCEL_DEBUG_VAR(_t_,_v_)
#  define CGAL__BOPS_DCEL_DEBUG_PAIR(_t_,_p1_,_p2_)
#  define CGAL__BOPS_DCEL_DEBUG_ITERATOR(_text_, _begin_, _end_) 

#endif /* CGAL__DCEL_DEBUG_ON */

/* Colors for the DCEL */
class CGAL__Dcel_Color {
public:
  CGAL__Dcel_Color() : _c(0) {}
  CGAL__Dcel_Color( const CGAL__Dcel_Color& c ) : _c(c._c) {}
  CGAL__Dcel_Color( int c ) : _c(c) {}

  void operator=(int i) { _c= i; }
  void operator=(CGAL__Dcel_Color other) { _c= other._c; }
  operator int() const {return _c;}
  CGAL__Dcel_Color operator|( const CGAL__Dcel_Color& c) const {
    return CGAL__Dcel_Color( _c | c._c );
  }
private:
  int _c;
};

const CGAL__Dcel_Color   CGAL__NO_COLOR= 0;
const CGAL__Dcel_Color   CGAL__UNCOLORED= 0;
const CGAL__Dcel_Color   CGAL__RED= 1;
const CGAL__Dcel_Color   CGAL__BLACK= 2;
const CGAL__Dcel_Color   CGAL__RED_AND_BLACK= 3;
const CGAL__Dcel_Color   CGAL__TWICE_COLORED= 3;



template<class I> class CGAL__Dcel_base;
template<class I> class CGAL__Dcel_vertex_type;
template<class I> class CGAL__Dcel_face_type;
template<class I> class CGAL__Dcel_edge_type;


/* CGAL__Dcel_point_compare: 
 * ------------------------
 *   predicate structure for the comparison of points in a container
 *   see also in CGAL__Dcel<I>::insert_new_vertex()
 */
template <class point_type, class vertex_type>
struct CGAL__Dcel_point_compare {
    CGAL__Dcel_point_compare() {}
    CGAL__Dcel_point_compare(const point_type& p) : _pt(p) {}
    bool operator()( const vertex_type& v ) {
      return _pt == v.point();
    }
    point_type _pt;
};

template <class point_type>
struct CGAL__Dcel_point_smaller_x :
  binary_function<point_type, point_type, bool>
{
  bool operator()(const point_type& p1, const point_type& p2) const {
    return p1.x() <= p2.x();
  }
};


template <class _I>
struct CGAL__Dcel_defs : public _I {
  typedef CGAL__Dcel_defs<_I>                I;

#ifdef CGAL_CFG_INCOMPLETE_TYPE_BUG_5
  CGAL__Dcel_edge_type<I>   _dummy_edge;
  CGAL__Dcel_face_type<I>   _dummy_face;
  CGAL__Dcel_vertex_type<I> _dummy_vertex;
#endif // ...

  typedef vector<CGAL__Dcel_edge_type<I> >   Edges_container;
  typedef vector<CGAL__Dcel_face_type<I> >   Faces_container;
  typedef vector<CGAL__Dcel_vertex_type<I> > Vertices_container;

  typedef typename Edges_container::const_iterator    const_edges_iterator;
  typedef typename Faces_container::const_iterator    const_faces_iterator;
  typedef typename Vertices_container::const_iterator const_vertices_iterator;

  typedef typename Edges_container::iterator          edges_iterator;
  typedef typename Faces_container::iterator          faces_iterator;
  typedef typename Vertices_container::iterator       vertices_iterator;

#ifndef CGAL_CFG_INCOMPLETE_TYPE_BUG_4
  typedef typename _I::Point                          Point;
#endif

  typedef CGAL__Dcel_point_smaller_x<Point>  Point_smaller;
  typedef set<Point, Point_smaller>          Points_container;
  typedef typename Points_container::const_iterator   const_points_iterator;
  typedef typename Points_container::iterator         points_iterator;


/* old typedefs (they should not be used further!!!) */
  typedef typename Edges_container::const_iterator edge_iterator;
  typedef typename Faces_container::const_iterator face_iterator;
  typedef typename Vertices_container::const_iterator vertex_iterator;
};

#endif /* CGAL__DCEL_DEFS_H */
