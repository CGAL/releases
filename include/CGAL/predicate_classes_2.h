// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.0
// release_date  : 1999, June 03
// 
// source        : predicate_classes_2.fw
// file          : include/CGAL/predicate_classes_2.h
// package       : _2 (2.1.2)
// revision      : 2.1.2
// revision_date : 09 May 1999 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_PREDICATES_CLASSES_2_H
#define CGAL_PREDICATES_CLASSES_2_H
#include <CGAL/predicates_on_points_2.h>
#include <CGAL/distance_predicates_2.h>
#include <CGAL/predicates_on_lines_2.h>

CGAL_BEGIN_NAMESPACE

template <class Point>             struct X_equal_2;
template <class Point>             struct Y_equal_2;
template <class Point>             struct Compare_x_2;
template <class Point>             struct Compare_y_2;
template <class Point>             struct Compare_deltax_deltay_2;
template <class Point>             struct Compare_xy_2;
template <class Point>             struct Less_xy_2;
template <class Point>             struct Compare_yx_2;
template <class Point>             struct Less_yx_2;
template <class Point>             struct Are_ordered_along_line_2 ;
template <class Point>             struct Collinear_are_ordered_along_line_2;
template <class Point>             struct Are_strictly_ordered_along_line_2;
template <class Point>             struct Collinear_are_strictly_ordered_along_line_2;
template <class Point>             struct Collinear_2;
template <class Point>             struct Leftturn_2;
template <class Point>             struct Rightturn_2;
template <class Point>             struct Orientation_2;
template <class Point>             struct Side_of_oriented_circle_2;
template <class Point>             struct Side_of_bounded_circle_2;
template <class Point>             class  Compare_distance_to_point_2;
template <class Point>             class  Less_distance_to_point_2;
template <class Point, class Line> class  Compare_signed_distance_to_line_2;
template <class Point, class Line> class  Less_signed_distance_to_line_2;
template <class Point>             class  Compare_signed_distance_to_implicit_line_2;
template <class Point>             class  Less_signed_distance_to_implicit_line_2;
template <class Point, class Line> struct Compare_y_at_point_2;
template <class Line>              struct Compare_y_at_implicit_point_2;
template <class Point, class Line> struct Compare_y_of_lines_at_point_2;
template <class Line>              struct Compare_y_of_lines_at_implicit_point_2;
template <class Point, class Line> struct Compare_x_implicit_point_2;
template <class Line>              struct Compare_x_implicit_points_2;
template <class Line>              struct Compare_x_implicit_points_same_line_2;
template <class Point, class Line> struct Compare_y_implicit_point_2;
template <class Line>              struct Compare_y_implicit_points_2;
template <class Line>              struct Compare_y_implicit_points_same_line_2;



template <class Point>
struct X_equal_2
 : public CGAL_STD::binary_function< Point, Point, bool>
{
  bool operator()( const Point& p, const Point& q) const
       { return x_equal( p, q); }
};

template <class Point>
struct Y_equal_2
 : public CGAL_STD::binary_function< Point, Point, bool>
{
  bool operator()( const Point& p, const Point& q) const
       { return y_equal( p, q); }
};

template <class Point>
struct Compare_x_2
 : public CGAL_STD::binary_function< Point, Point, Comparison_result>
{
  Comparison_result operator()( const Point& p, const Point& q) const
       { return compare_x( p, q); }
};

template <class Point>
struct Compare_y_2
 : public CGAL_STD::binary_function< Point, Point, Comparison_result>
{
  Comparison_result operator()( const Point& p, const Point& q) const
       { return compare_y( p, q); }
};

template <class Point>
struct Compare_deltax_deltay_2
{
  Comparison_result operator()( const Point& p, const Point& q,
                                     const Point& r, const Point& s )
       { return compare_deltax_deltay( p,q,r,s); }
};

template <class Point>
struct Compare_xy_2
 : public CGAL_STD::binary_function< Point, Point, Comparison_result>
{
  Comparison_result operator()( const Point& p, const Point& q) const
      { return compare_lexicographically_xy( p,q); }
};

template <class Point>
struct Less_xy_2
 : public CGAL_STD::binary_function< Point, Point, bool>
{
  bool operator()( const Point& p, const Point& q) const
       { return lexicographically_xy_smaller( p,q); }
};

template <class Point>
struct Compare_yx_2
 : public CGAL_STD::binary_function< Point, Point, Comparison_result>
{
  Comparison_result operator()( const Point& p, const Point& q) const
      { return compare_lexicographically_yx( p,q); }
};

template <class Point>
struct Less_yx_2
 : public CGAL_STD::binary_function< Point, Point, bool>
{
  bool operator()( const Point& p, const Point& q) const
       { return lexicographically_yx_smaller( p,q); }
};


template <class Point>
struct Are_ordered_along_line_2
{
  bool operator()( const Point& p, const Point& q, const Point& r) const
       { return are_ordered_along_line( p,q,r); }
};

template <class Point>
struct Collinear_are_ordered_along_line_2
{
  bool operator()( const Point& p, const Point& q, const Point& r) const
       { return collinear_are_ordered_along_line( p,q,r); }
};

template <class Point>
struct Are_strictly_ordered_along_line_2
{
  bool operator()( const Point& p, const Point& q, const Point& r) const
       { return are_strictly_ordered_along_line( p,q,r); }
};

template <class Point>
struct Collinear_are_strictly_ordered_along_line_2
{
  bool operator()( const Point& p, const Point& q, const Point& r) const
       { return collinear_are_strictly_ordered_along_line( p,q,r); }
};

template <class Point>
struct Collinear_2
{
  bool operator()( const Point& p, const Point& q, const Point& r) const
       { return collinear( p,q,r); }
};

template <class Point>
struct Leftturn_2
{
  bool operator()( const Point& p, const Point& q, const Point& r) const
       { return leftturn( p,q,r); }
};

template <class Point>
struct Rightturn_2
{
  bool operator()( const Point& p, const Point& q, const Point& r) const
       { return rightturn( p,q,r); }
};

template <class Point>
struct Orientation_2
{
  Orientation operator()( const Point& p, const Point& q, const Point& r) const
       { return orientation( p,q,r); }
};

template <class Point>
struct Side_of_oriented_circle_2
{
  Oriented_side operator()( const Point& p, const Point& q,
                                 const Point& r, const Point& s)
       { return side_of_oriented_circle( p,q,r,s); }
};

template <class Point>
struct Side_of_bounded_circle_2
{
  Oriented_side operator()( const Point& p, const Point& q,
                                 const Point& r, const Point& s)
       { return side_of_bounded_circle( p,q,r,s); }
};



template <class Point>
class Compare_distance_to_point_2
 : public CGAL_STD::binary_function< Point, Point, Comparison_result>
{
 public:
  Compare_distance_to_point_2( const Point& p) : _p(p) {}
  Comparison_result
       operator()( const Point& q, const Point& r)
       { return cmp_dist_to_point( _p,q,r); }
 private:
  Point _p;
};

template <class Point>
class Less_distance_to_point_2
 : public CGAL_STD::binary_function< Point, Point, bool>
{
 public:
  Less_distance_to_point_2( const Point& p) : _p(p) {}
  bool operator()( const Point& q, const Point& r)
       { return has_smaller_dist_to_point( _p,q,r); }
 private:
  Point _p;
};

template <class Point, class Line>
class Compare_signed_distance_to_line_2
 : public CGAL_STD::binary_function< Point, Point, Comparison_result>
{
 public:
  Compare_signed_distance_to_line_2( const Line& l) : _l(l) {}
  Comparison_result
       operator()( const Point& p, const Point& q)
       { return cmp_signed_dist_to_line( _l, p, q); }
 private:
  Line _l;
};

template <class Point, class Line>
class Less_signed_distance_to_line_2
 : public CGAL_STD::binary_function< Point, Point, bool>
{
 public:
  Less_signed_distance_to_line_2( const Line& l) : _l(l) {}
  bool operator()( const Line& l, const Point& p, const Point& q)
       { return has_smaller_signed_dist_to_line( l, p, q); }
 private:
  Line _l;
};

template <class Point>
class Compare_signed_distance_to_implicit_line_2
 : public CGAL_STD::binary_function< Point, Point, Comparison_result>
{
 public:
  Compare_signed_distance_to_implicit_line_2( const Point& p, const Point& q)
   : _p(p), _q(q)
  {}
  Comparison_result
       operator()( const Point& r, const Point& s)
       { return cmp_signed_dist_to_line( _p, _q, r, s); }
 private:
  Point _p;
  Point _q;
};

template <class Point>
class Less_signed_distance_to_implicit_line_2
 : public CGAL_STD::binary_function< Point, Point, bool>
{
 public:
  Less_signed_distance_to_implicit_line_2( const Point& p, const Point& q)
   : _p(p), _q(q)
  {}
  bool operator()( const Point& r, const Point& s)
       { return has_smaller_signed_dist_to_line( _p, _q, r, s); }
 private:
  Point _p;
  Point _q;
};



template <class Point, class Line>
struct Compare_y_at_point_2
 : public CGAL_STD::binary_function< Point, Line, Comparison_result>
{
  Comparison_result operator()( const Point& p, const Line& l)
       { return compare_y_at_x( p, l); }
};

template <class Line>
struct Compare_y_at_implicit_point_2
{
  Comparison_result operator()( const Line& l1, const Line& l2, const Line& l)
       { return compare_y_at_x( l1, l2, l); }
};

template <class Point, class Line>
struct Compare_y_of_lines_at_point_2
{
  Comparison_result operator()( const Point& p, const Line& l1, const Line& l2)
       { return compare_y_at_x( p, l1, l2); }
};

template <class Line>
struct Compare_y_of_lines_at_implicit_point_2
{
  Comparison_result operator()( const Line& l1, const Line& l2,
                                     const Line& h1, const Line& h2)
       { return compare_y_at_x( l1, l2, h1, h2); }
};

template <class Point, class Line>
struct Compare_x_implicit_point_2
{
  Comparison_result operator()( const Point& p,
                                     const Line& l1, const Line& l2)
       { return compare_x( p, l1, l2); }
};

template <class Line>
struct Compare_x_implicit_points_2
{
  Comparison_result operator()( const Line& l1, const Line& l2,
                                     const Line& h1, const Line& h2)
       { return compare_x( l1, l2, h1, h2); }
};

template <class Line>
struct Compare_x_implicit_points_same_line_2
{
  Comparison_result
       operator()( const Line& l, const Line& h1, const Line& h2)
       { return compare_x( l, h1, h2); }
};

template <class Point, class Line>
struct Compare_y_implicit_point_2
{
  Comparison_result operator()( const Point& p,
                                     const Line& l1, const Line& l2)
       { return compare_y( p, l1, l2); }
};

template <class Line>
struct Compare_y_implicit_points_2
{
  Comparison_result operator()( const Line& l1, const Line& l2,
                                     const Line& h1, const Line& h2)
       { return compare_y( l1, l2, h1, h2); }
};

template <class Line>
struct Compare_y_implicit_points_same_line_2
{
  Comparison_result
       operator()( const Line& l, const Line& h1, const Line& h2)
       { return compare_y( l, h1, h2); }
};


CGAL_END_NAMESPACE


#endif // CGAL_PREDICATES_CLASSES_2_H
