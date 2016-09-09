// ======================================================================
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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-1.2
// release_date  : 1999, January 18
// 
// source        : predicate_classes_2.fw
// file          : include/CGAL/predicate_classes_2.h
// package       : _2 (1.3)
// revision      : 1.3
// revision_date : 15 Dec 1998 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_PREDICATES_CLASSES_2_H
#define CGAL_PREDICATES_CLASSES_2_H
#include <CGAL/predicates_on_points_2.h>
#include <CGAL/distance_predicates_2.h>
#include <CGAL/predicates_on_lines_2.h>

template <class Point>             struct CGAL_X_equal_2;;
template <class Point>             struct CGAL_Y_equal_2;;
template <class Point>             struct CGAL_Compare_x_2;
template <class Point>             struct CGAL_Compare_y_2;
template <class Point>             struct CGAL_Compare_deltax_deltay_2;
template <class Point>             struct CGAL_Compare_xy_2;
template <class Point>             struct CGAL_Less_xy_2;
template <class Point>             struct CGAL_Compare_yx_2;
template <class Point>             struct CGAL_Less_yx_2;
template <class Point>             struct CGAL_Are_ordered_along_line_2 ;
template <class Point>             struct CGAL_Collinear_are_ordered_along_line_2;
template <class Point>             struct CGAL_Are_strictly_ordered_along_line_2;
template <class Point>             struct CGAL_Collinear_are_strictly_ordered_along_line_2;
template <class Point>             struct CGAL_Collinear_2;
template <class Point>             struct CGAL_Leftturn_2;
template <class Point>             struct CGAL_Rightturn_2;
template <class Point>             struct CGAL_Orientation_2;
template <class Point>             struct CGAL_Side_of_oriented_circle_2;
template <class Point>             struct CGAL_Side_of_bounded_circle_2;
template <class Point>             class  CGAL_Compare_distance_to_point_2;
template <class Point>             class  CGAL_Less_distance_to_point_2;
template <class Point, class Line> class  CGAL_Compare_signed_distance_to_line_2;
template <class Point, class Line> class  CGAL_Less_signed_distance_to_line_2;
template <class Point>             class  CGAL_Compare_signed_distance_to_implicit_line_2;
template <class Point>             class  CGAL_Less_signed_distance_to_implicit_line_2;
template <class Point, class Line> struct CGAL_Compare_y_at_point_2;
template <class Line>              struct CGAL_Compare_y_at_implicit_point_2;
template <class Point, class Line> struct CGAL_Compare_y_of_lines_at_point_2;
template <class Line>              struct CGAL_Compare_y_of_lines_at_implicit_point_2;
template <class Point, class Line> struct CGAL_Compare_x_implicit_point_2;
template <class Line>              struct CGAL_Compare_x_implicit_points_2;
template <class Line>              struct CGAL_Compare_x_implicit_points_same_line_2;
template <class Point, class Line> struct CGAL_Compare_y_implicit_point_2;
template <class Line>              struct CGAL_Compare_y_implicit_points_2;
template <class Line>              struct CGAL_Compare_y_implicit_points_same_line_2;




template <class Point>
struct CGAL_X_equal_2
 : public binary_function< Point, Point, bool>
{
  bool operator()( const Point& p, const Point& q) const
       { return CGAL_x_equal( p, q); }
};

template <class Point>
struct CGAL_Y_equal_2
 : public binary_function< Point, Point, bool>
{
  bool operator()( const Point& p, const Point& q) const
       { return CGAL_y_equal( p, q); }
};

template <class Point>
struct CGAL_Compare_x_2
 : public binary_function< Point, Point, CGAL_Comparison_result>
{
  CGAL_Comparison_result operator()( const Point& p, const Point& q) const
       { return CGAL_compare_x( p, q); }
};

template <class Point>
struct CGAL_Compare_y_2
 : public binary_function< Point, Point, CGAL_Comparison_result>
{
  CGAL_Comparison_result operator()( const Point& p, const Point& q) const
       { return CGAL_compare_y( p, q); }
};

template <class Point>
struct CGAL_Compare_deltax_deltay_2
{
  CGAL_Comparison_result operator()( const Point& p, const Point& q,
                                     const Point& r, const Point& s )
       { return CGAL_compare_deltax_deltay( p,q,r,s); }
};

template <class Point>
struct CGAL_Compare_xy_2
 : public binary_function< Point, Point, CGAL_Comparison_result>
{
  CGAL_Comparison_result operator()( const Point& p, const Point& q) const
      { return CGAL_compare_lexicographically_xy( p,q); }
};

template <class Point>
struct CGAL_Less_xy_2
 : public binary_function< Point, Point, bool>
{
  bool operator()( const Point& p, const Point& q) const
       { return CGAL_lexicographically_xy_smaller( p,q); }
};

template <class Point>
struct CGAL_Compare_yx_2
 : public binary_function< Point, Point, CGAL_Comparison_result>
{
  CGAL_Comparison_result operator()( const Point& p, const Point& q) const
      { return CGAL_compare_lexicographically_yx( p,q); }
};

template <class Point>
struct CGAL_Less_yx_2
 : public binary_function< Point, Point, bool>
{
  bool operator()( const Point& p, const Point& q) const
       { return CGAL_lexicographically_yx_smaller( p,q); }
};


template <class Point>
struct CGAL_Are_ordered_along_line_2
{
  bool operator()( const Point& p, const Point& q, const Point& r) const
       { return CGAL_are_ordered_along_line( p,q,r); }
};

template <class Point>
struct CGAL_Collinear_are_ordered_along_line_2
{
  bool operator()( const Point& p, const Point& q, const Point& r) const
       { return CGAL_collinear_are_ordered_along_line( p,q,r); }
};

template <class Point>
struct CGAL_Are_strictly_ordered_along_line_2
{
  bool operator()( const Point& p, const Point& q, const Point& r) const
       { return CGAL_are_strictly_ordered_along_line( p,q,r); }
};

template <class Point>
struct CGAL_Collinear_are_strictly_ordered_along_line_2
{
  bool operator()( const Point& p, const Point& q, const Point& r) const
       { return CGAL_collinear_are_strictly_ordered_along_line( p,q,r); }
};

template <class Point>
struct CGAL_Collinear_2
{
  bool operator()( const Point& p, const Point& q, const Point& r) const
       { return CGAL_collinear( p,q,r); }
};

template <class Point>
struct CGAL_Leftturn_2
{
  bool operator()( const Point& p, const Point& q, const Point& r) const
       { return CGAL_leftturn( p,q,r); }
};

template <class Point>
struct CGAL_Rightturn_2
{
  bool operator()( const Point& p, const Point& q, const Point& r) const
       { return CGAL_rightturn( p,q,r); }
};

template <class Point>
struct CGAL_Orientation_2
{
  CGAL_Orientation operator()( const Point& p, const Point& q, const Point& r) const
       { return CGAL_orientation( p,q,r); }
};

template <class Point>
struct CGAL_Side_of_oriented_circle_2
{
  CGAL_Oriented_side operator()( const Point& p, const Point& q,
                                 const Point& r, const Point& s)
       { return CGAL_side_of_oriented_circle( p,q,r,s); }
};

template <class Point>
struct CGAL_Side_of_bounded_circle_2
{
  CGAL_Oriented_side operator()( const Point& p, const Point& q,
                                 const Point& r, const Point& s)
       { return CGAL_side_of_bounded_circle( p,q,r,s); }
};



template <class Point>
class CGAL_Compare_distance_to_point_2
 : public binary_function< Point, Point, CGAL_Comparison_result>
{
 public:
  CGAL_Compare_distance_to_point_2( const Point& p) : _p(p) {}
  CGAL_Comparison_result
       operator()( const Point& q, const Point& r)
       { return CGAL_cmp_dist_to_point( _p,q,r); }
 private:
  Point _p;
};

template <class Point>
class CGAL_Less_distance_to_point_2
 : public binary_function< Point, Point, bool>
{
 public:
  CGAL_Less_distance_to_point_2( const Point& p) : _p(p) {}
  bool operator()( const Point& q, const Point& r)
       { return CGAL_has_smaller_dist_to_point( _p,q,r); }
 private:
  Point _p;
};

template <class Point, class Line>
class CGAL_Compare_signed_distance_to_line_2
 : public binary_function< Point, Point, CGAL_Comparison_result>
{
 public:
  CGAL_Compare_signed_distance_to_line_2( const Line& l) : _l(l) {}
  CGAL_Comparison_result
       operator()( const Point& p, const Point& q)
       { return CGAL_cmp_signed_dist_to_line( _l, p, q); }
 private:
  Line _l;
};

template <class Point, class Line>
class CGAL_Less_signed_distance_to_line_2
 : public binary_function< Point, Point, bool>
{
 public:
  CGAL_Less_signed_distance_to_line_2( const Line& l) : _l(l) {}
  bool operator()( const Line& l, const Point& p, const Point& q)
       { return CGAL_has_smaller_signed_dist_to_line( l, p, q); }
 private:
  Line _l;
};

template <class Point>
class CGAL_Compare_signed_distance_to_implicit_line_2
 : public binary_function< Point, Point, CGAL_Comparison_result>
{
 public:
  CGAL_Compare_signed_distance_to_implicit_line_2( const Point& p, const Point& q)
   : _p(p), _q(q)
  {}
  CGAL_Comparison_result
       operator()( const Point& r, const Point& s)
       { return CGAL_cmp_signed_dist_to_line( _p, _q, r, s); }
 private:
  Point _p;
  Point _q;
};

template <class Point>
class CGAL_Less_signed_distance_to_implicit_line_2
 : public binary_function< Point, Point, bool>
{
 public:
  CGAL_Less_signed_distance_to_implicit_line_2( const Point& p, const Point& q)
   : _p(p), _q(q)
  {}
  bool operator()( const Point& r, const Point& s)
       { return CGAL_has_smaller_signed_dist_to_line( _p, _q, r, s); }
 private:
  Point _p;
  Point _q;
};



template <class Point, class Line>
struct CGAL_Compare_y_at_point_2
 : public binary_function< Point, Line, CGAL_Comparison_result>
{
  CGAL_Comparison_result operator()( const Point& p, const Line& l)
       { return CGAL_compare_y_at_x( p, l); }
};

template <class Line>
struct CGAL_Compare_y_at_implicit_point_2
{
  CGAL_Comparison_result operator()( const Line& l1, const Line& l2, const Line& l)
       { return CGAL_compare_y_at_x( l1, l2, l); }
};

template <class Point, class Line>
struct CGAL_Compare_y_of_lines_at_point_2
{
  CGAL_Comparison_result operator()( const Point& p, const Line& l1, const Line& l2)
       { return CGAL_compare_y_at_x( p, l1, l2); }
};

template <class Line>
struct CGAL_Compare_y_of_lines_at_implicit_point_2
{
  CGAL_Comparison_result operator()( const Line& l1, const Line& l2,
                                     const Line& h1, const Line& h2)
       { return CGAL_compare_y_at_x( l1, l2, h1, h2); }
};

template <class Point, class Line>
struct CGAL_Compare_x_implicit_point_2
{
  CGAL_Comparison_result operator()( const Point& p,
                                     const Line& l1, const Line& l2)
       { return CGAL_compare_x( p, l1, l2); }
};

template <class Line>
struct CGAL_Compare_x_implicit_points_2
{
  CGAL_Comparison_result operator()( const Line& l1, const Line& l2,
                                     const Line& h1, const Line& h2)
       { return CGAL_compare_x( l1, l2, h1, h2); }
};

template <class Line>
struct CGAL_Compare_x_implicit_points_same_line_2
{
  CGAL_Comparison_result
       operator()( const Line& l, const Line& h1, const Line& h2)
       { return CGAL_compare_x( l, h1, h2); }
};

template <class Point, class Line>
struct CGAL_Compare_y_implicit_point_2
{
  CGAL_Comparison_result operator()( const Point& p,
                                     const Line& l1, const Line& l2)
       { return CGAL_compare_y( p, l1, l2); }
};

template <class Line>
struct CGAL_Compare_y_implicit_points_2
{
  CGAL_Comparison_result operator()( const Line& l1, const Line& l2,
                                     const Line& h1, const Line& h2)
       { return CGAL_compare_y( l1, l2, h1, h2); }
};

template <class Line>
struct CGAL_Compare_y_implicit_points_same_line_2
{
  CGAL_Comparison_result
       operator()( const Line& l, const Line& h1, const Line& h2)
       { return CGAL_compare_y( l, h1, h2); }
};


#endif // CGAL_PREDICATES_CLASSES_2_H
