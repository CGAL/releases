// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/bops_dcel_vertex.h
// author(s)     :            Wolfgang Freiseisen 
//
// email         : cgal@cs.uu.nl
//
// ============================================================================

#ifndef CGAL__DCEL_VERTEX_H
#define CGAL__DCEL_VERTEX_H

#include <list.h>
#include <vector.h>

#include <CGAL/bops_dcel_element.h>


/*
  VERTEX in the DCEL:
  -------------------
  vertex_type:      point, header, color;
  vertex:           typedef const CGAL__Dcel_vertex_type* CGAL__Dcel_vertex;
  container:        vector<CGAL__Dcel_vertex_type>
  vertex_iterator:  typedef vector<CGAL__Dcel_vertex_type>::const_iterator vertex_iterator;
  conversion:       vertex and vertex_iterator are type-identical

  *---------------------------------------------------------------------*
  *A CGAL_Point< R > is stored as a CGAL_Object to avoid templatizing of*
  *class CGAL__Dcel_vertex_type!                                        *
  *---------------------------------------------------------------------*

  CGAL-point:       CGAL_Point< R > pt;
                    if( CGAL_assign( pt, vertex->point()) )
                      this is a CGAL-point;
                    else
                      this is not a CGAL-point;

                    ...

  CGAL-object:      CGAL_Object obj= CGAL_make_object(pt);
  
*/

template <class I>
class CGAL__Dcel_vertex_type : public CGAL__Dcel_element_type {
public:
  typedef typename I::Point                                 Point;

#ifdef CGAL_CFG_INCOMPLETE_TYPE_BUG_4
  typedef CGAL__Dcel_point_smaller_x<Point>        Point_smaller;
  typedef set<Point, Point_smaller>                Points_container;
  typedef typename Points_container::const_iterator const_points_iterator;
  typedef typename Points_container::iterator       points_iterator;
  //typedef Point*                   const_points_iterator;
  typedef CGAL__Dcel_edge_type<I>* edge;
#else
  //typedef typename I::points_iterator       points_iterator;
  typedef typename I::const_points_iterator const_points_iterator;
  typedef typename I::const_edges_iterator  edge;
#endif

  CGAL__Dcel_vertex_type() : CGAL__Dcel_element_type(), _degree(0) {}

  CGAL__Dcel_vertex_type(
     //const Point& pt,
     const_points_iterator pt,
     int ind,
     CGAL__Dcel_Color col = CGAL__NO_COLOR
  )
     : CGAL__Dcel_element_type(ind, col),
     _point(pt), _header(NULL), _degree(0) {}

  CGAL__Dcel_vertex_type(
     //const Point& pt,
     const_points_iterator pt,
     CGAL__Dcel_Color col = CGAL__NO_COLOR)
        : CGAL__Dcel_element_type(col),
          _point(pt), _header(NULL), _degree(0) {}

  Point point() const { return *_point; }
  //Point& point() { return (Point)*(points_iterator)_point; }
  //const Point& point() const { return _point; }
  //Point& point() { return _point; }

  int  degree() const { return _degree; }
  edge header() const { return _header; }

protected:
  edge&  header() { return _header; }
  void   header(edge h)       { _header= h; }

  friend class CGAL__Dcel_base<I>;

private:
  //Point _point;
  const_points_iterator _point;
  edge _header;
  int  _degree; /* the degree of this node */
};

#endif /* CGAL__DCEL_VERTEX_H */

