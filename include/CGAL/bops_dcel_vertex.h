// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : include/CGAL/bops_dcel_vertex.h
// package       : bops (2.4)
// source        : include/CGAL/bops_dcel_vertex.h
// revision      : $Revision: 1.1.1.1 $
// revision_date : $Date: 1999/10/11 13:50:32 $
// author(s)     : Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL__DCEL_VERTEX_H
#define CGAL__DCEL_VERTEX_H

#include <list>
#include <vector>

#include <CGAL/bops_dcel_element.h>

CGAL_BEGIN_NAMESPACE

/*
  VERTEX in the DCEL:
  -------------------
  vertex_type:      point, header, color;
  vertex:           typedef const _Dcel_vertex_type* _Dcel_vertex;
  container:        vector<_Dcel_vertex_type>
  vertex_iterator:  typedef vector<_Dcel_vertex_type>::const_iterator
                    vertex_iterator;
  conversion:       vertex and vertex_iterator are type-identical

  *---------------------------------------------------------------------*
  *A Point< R > is stored as a Object to avoid templatizing of*
  *class _Dcel_vertex_type!                                        *
  *---------------------------------------------------------------------*

  CGAL-point:       Point< R > pt;
                    if( assign( pt, vertex->point()) )
                      this is a CGAL-point;
                    else
                      this is not a CGAL-point;

                    ...

  CGAL-object:      Object obj= make_object(pt);
  
*/

template <class I>
class _Dcel_vertex_type : public _Dcel_element_type {
public:
  typedef typename I::Point                                 Point;

#ifdef CGAL_CFG_INCOMPLETE_TYPE_BUG_4
  typedef _Dcel_point_smaller_x<Point>        Point_smaller;
  typedef set<Point, Point_smaller>                Points_container;
  typedef typename Points_container::const_iterator const_points_iterator;
  typedef typename Points_container::iterator       points_iterator;
  //typedef Point*                   const_points_iterator;
  typedef _Dcel_edge_type<I>* edge;
#else
  //typedef typename I::points_iterator       points_iterator;
  typedef typename I::const_points_iterator const_points_iterator;
  typedef typename I::const_edges_iterator  edge;
#endif

  _Dcel_vertex_type() : _Dcel_element_type(), _degree(0) {}

  _Dcel_vertex_type(
     //const Point& pt,
     const_points_iterator pt,
     int ind,
     _Dcel_Color col = _NO_COLOR
  )
     : _Dcel_element_type(ind, col),
     _point(pt), _header(NULL), _degree(0) {}

  _Dcel_vertex_type(
     //const Point& pt,
     const_points_iterator pt,
     _Dcel_Color col = _NO_COLOR)
        : _Dcel_element_type(col),
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

  friend class _Dcel_base<I>;

private:
  //Point _point;
  const_points_iterator _point;
  edge _header;
  int  _degree; /* the degree of this node */
};

CGAL_END_NAMESPACE

#endif /* CGAL__DCEL_VERTEX_H */

