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
// file          : include/CGAL/Polygon_traits_2.h
// package       : Polygon (2.4.7)
// source        :
// revision      : 1.8a
// revision_date : 13 Mar 1998
// author(s)     : Wieger Wesselink
//
// coordinator   : Utrecht University
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_POLYGON_TRAITS_2_H
#define CGAL_POLYGON_TRAITS_2_H

#ifndef CGAL_DIRECTION_2_H
#include <CGAL/Direction_2.h>
#endif // CGAL_DIRECTION_2_H
#ifndef CGAL_ISO_RECTANGLE_2_H
#include <CGAL/Iso_rectangle_2.h>
#endif // CGAL_ISO_RECTANGLE_2_H
#ifndef CGAL_POINT_2_H
#include <CGAL/Point_2.h>
#endif // CGAL_POINT_2_H
#ifndef CGAL_SEGMENT_2_H
#include <CGAL/Segment_2.h>
#endif // CGAL_SEGMENT_2_H
#ifndef CGAL_TRIANGLE_2_H
#include <CGAL/Triangle_2.h>
#endif // CGAL_TRIANGLE_2_H
#ifndef CGAL_VECTOR_2_H
#include <CGAL/Vector_2.h>
#endif // CGAL_VECTOR_2_H

#ifndef CGAL_NUMBER_UTILS_H
#include <CGAL/number_utils.h>
#endif // CGAL_NUMBER_UTILS_H
#ifndef CGAL_PREDICATES_ON_POINTS_2_H
#include <CGAL/predicates_on_points_2.h>
#endif // CGAL_PREDICATES_ON_POINTS_2_H
#ifndef CGAL_PREDICATES_CLASSES_2_H
#include <CGAL/predicate_classes_2.h>
#endif // CGAL_PREDICATES_CLASSES_2_H
#ifndef CGAL_SEGMENT_2_SEGMENT_2_INTERSECTION_H
#include <CGAL/Segment_2_Segment_2_intersection.h>
#endif // CGAL_SEGMENT_2_SEGMENT_2_INTERSECTION_H

CGAL_BEGIN_NAMESPACE

//-----------------------------------------------------------------------//
//                          Polygon_traits_2_aux
//-----------------------------------------------------------------------//
// The class Polygon_traits_2_aux is needed as a workaround for compilers
// that have problems with member functions with return type R::FT.
// The template parameter _Point is added to simplify the use of points
// with additional information. It is assumed that _Point inherits from
// Point_2<_R>.

template <class _R, class _FT, class _Point>
class Polygon_traits_2_aux : public _R
{
  public:
    typedef _FT                           FT;
    typedef _Point                        Point_2;
    typedef ::CGAL::Segment_2<_R>            Segment_2;
    typedef ::CGAL::Vector_2<_R>             Vector_2;

    typedef Less_xy_2<Point_2>       Less_xy;
    typedef Less_yx_2<Point_2>       Less_yx;

    bool lexicographically_xy_smaller(const Point_2& p, const Point_2& q) const
    {
      return ::CGAL::lexicographically_xy_smaller(p,q);
    }

    bool lexicographically_yx_smaller_or_equal(const Point_2& p,
                                               const Point_2& q) const
    {
      return ::CGAL::lexicographically_yx_smaller_or_equal(p,q);
    }

    FT cross_product_2(const Vector_2& p, const Vector_2& q) const
    {
      return p.x() * q.y() - q.x() * p.y();
      // there should be multiple versions of this function
      // to distinguish between cartesian and homogeneous coordinates
      // (for efficiency reasons)
    }

    FT determinant_2(const Point_2& p, const Point_2& q, const Point_2& r) const
    {
      return cross_product_2(p-q, p-r);
    }

    int sign(const FT& x) const
    {
      return ::CGAL::sign(x);
    }

    bool is_negative(const FT& x) const
    {
      return ::CGAL::is_negative(x);
    }

    bool do_intersect(const Point_2& p1,
                      const Point_2& q1,
                      const Point_2& p2,
                      const Point_2& q2) const
    {
      return ::CGAL::do_intersect(Segment_2(p1,q1), Segment_2(p2,q2));
    }

    Orientation orientation(const Point_2& p,
                                 const Point_2& q,
                                 const Point_2& r) const
    {
       return ::CGAL::orientation(p, q, r);
    }

    Comparison_result compare_x(const Point_2 &p, const Point_2 &q) const
    {
       return ::CGAL::compare_x(p, q);
    }

    Comparison_result compare_y(const Point_2 &p, const Point_2 &q) const
    {
       return ::CGAL::compare_y(p, q);
    }

    bool have_equal_direction(const Vector_2& v1,
                              const Vector_2& v2 ) const
    {
       return ::CGAL::Direction_2<_R>(v1) == ::CGAL::Direction_2<_R>(v2);
    }
};

//-----------------------------------------------------------------------//
//                          Polygon_traits_2
//-----------------------------------------------------------------------//
// The class Polygon_traits_2 is a traits class for Polygon_2.

template <class _R>
class Polygon_traits_2 :
  public Polygon_traits_2_aux<_R, typename _R::FT, Point_2<_R> >
{
};

CGAL_END_NAMESPACE

#endif // CGAL_POLYGON_TRAITS_2_H

