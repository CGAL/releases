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
// file          : include/CGAL/bops_traits_2.h
// author(s)     :        Wolfgang Freiseisen 
//
// email         : cgal@cs.uu.nl
//
// ============================================================================

#ifndef BOPS_TRAITS_2_H
#define BOPS_TRAITS_2_H
 
 
#include <CGAL/Cartesian.h> 
#include <CGAL/Homogeneous.h> 
#include <CGAL/basic.h> 
#include <list.h>
#include <CGAL/Object.h>
#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Iso_rectangle_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Direction_2.h>

#include <CGAL/min_sqr_distance_traits.h>

/*
    _R should be a representation class 
   (e.g. something like CGAL_Cartesian<CGAL_Rational> )
*/
template <class _R> 
struct Bops_default_I : public min_sqr_distance_traits<_R>
{
  Bops_default_I() {}

  /* representation class */
  typedef _R R;
  typedef CGAL_Object                          Object;

  /*------ constant sized objects ------*/

  typedef CGAL_Bbox_2   Bbox;
  /* required operations:
     bool operator==(Bbox, Bbox);
  */

  bool do_overlap( const Bbox& a, const Bbox& b) const {
    return CGAL_do_overlap(a,b);
  }

  bool box_is_contained_in_box( const Bbox& a, const Bbox& b) const {
    return xmin(b) <= xmin(a) &&
           xmax(b) >= xmax(a) &&
           ymin(b) <= ymin(a) &&
           ymax(b) >= ymax(a) ?  true : false;

  }


  typedef CGAL_Point_2<R>                      Point;
  /* required operations:
    R::NT Point::x() const
    R::NT Point::y() const
  */
  bool is_equal(const Point& p1, const Point& p2) const {
    return p1 == p2;
  }

  bool less_x(const Point& p1, const Point& p2) const {
    return p1.x() < p2.x();
  }
  

  typedef CGAL_Segment_2<R>                    Segment;
  /* required operations:
    Segment(Point,Point);
  */
  typedef CGAL_Triangle_2<R>                   Triangle;
  /* required operations:
    constructor with three points of type Point.
  */
  typedef CGAL_Iso_rectangle_2<R>              Iso_rectangle;
  /* required operations:
    constructor with three points of type Point.
  */

  /*------ non-constant sized objects ------*/
  typedef list<Object>                         Output_object_container;
  /* required operations:
     void Output_object_container::push_back(Object);
  */
  typedef list<Point>                          Container;
  typedef Container                            Input_polygon_container;
  typedef list<Point>                          Output_polygon_container;
  typedef CGAL_Polygon_2<CGAL_Polygon_traits_2<R>,Container>          Polygon;
  typedef Polygon                              Input_polygon;
  typedef typename Polygon::Vertex_const_iterator       Polygon_vertex_const_iterator;
  /* required operations:
     Polygon_vertex_const_iterator Polygon::vertices_begin();
     Polygon_vertex_const_iterator Polygon::vertices_end();
  */
  typedef CGAL_Polygon_2<CGAL_Polygon_traits_2<R>,Output_polygon_container>
          Output_polygon;

  bool is_leftturn(const Point& p0, const Point& p1, const Point& p2) const {
    /* p0 ... origin */
    /* return direction_of(p0,p1) < direction_of(p0,p2);*/
    return CGAL_leftturn(p0, p1, p2);
  }

  Object Make_object(const Point& p) const {
    return CGAL_make_object(p);
  }
  Object Make_object(const Segment& seg) const {
    return CGAL_make_object(seg);
  }
  Object Make_object(const Output_polygon& pgon) const {
    return CGAL_make_object(pgon);
  }
  Object Make_object(const Iso_rectangle& irect) const {
    return CGAL_make_object(irect);
  }
  Object Make_object(const Triangle& triangle) const {
    return CGAL_make_object(triangle);
  }

  Bbox get_Bbox(const Polygon& pgon) const {
    return pgon.bbox();
  }

  bool has_on_bounded_side(const Polygon& pgon, const Point& pt) const {
    /* will be used if there is a better intersection algorithm implemented */
    //return pgon.has_on_bounded_side(pt);
    //return pgon.has_on_bounded_side(pt) || pgon.has_on_boundary(pt);
    return pgon.bounded_side(pt)==CGAL_ON_UNBOUNDED_SIDE ? false : true;
  }
  void reverse_orientation(Polygon& pgon) const {
    pgon.reverse_orientation();
  }
  Polygon_vertex_const_iterator most_left_vertex(const Polygon& pgon) const {
    return pgon.left_vertex();
  }

  /* for intersection plug-in:
     -------------------------

     typedef Intersect_Polygons intersection_result;
     intersection_result Intersection(const Input_polygon& polygon_A,
                                      const Input_polygon& polygon_B)
     {
       return intersection_result(polygon_A, polygon_B);
     }
     int get_result( const intersection_result& result,
                     list<Point>&               point_list,
                     list<pair<int,int> >&      edge_list )
     {
        result.get_graph_information(point_list, edge_list);
     }
     int get_result_on_A( const intersection_result& result,
                          list<Point>&               point_list) {
        point_list= result.get_color_informationA();
     }
     int get_result_on_B( const intersection_result& result,
                          list<Point>&               point_list) {
        point_list= result.get_color_informationB();
     }
  */

  /* for nsquare-intersection algorithm:
     CGAL_assign
     CGAL_collinear_are_ordered_along_line
     CGAL_compare_lexicographically_xy
     CGAL_make_object
     CGAL_do_intersect(Segment, Segment)
     CGAL_intersection(Segment, Segment)
  */

protected:

  typedef CGAL_Direction_2<R>                  Direction;
  /* required operations:
     bool operator<(Direction, Direction);
  */

  Direction direction_of(const Point& from, const Point& to) const {
    return (to-from).direction();
  }

  double xmin(const Bbox& bbox) const { return bbox.xmin(); }
  double xmax(const Bbox& bbox) const { return bbox.xmax(); }
  double ymin(const Bbox& bbox) const { return bbox.ymin(); }
  double ymax(const Bbox& bbox) const { return bbox.ymax(); }

};

#endif /* BOPS_TRAITS_2_H */
