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
// file          : include/CGAL/Polygon_traits_2.h
// author(s)     : Wieger Wesselink 
//
// email         : cgal@cs.uu.nl
//
// ============================================================================

#ifndef CGAL_POLYGON_TRAITS_2_H
#define CGAL_POLYGON_TRAITS_2_H

#include <CGAL/Direction_2.h>
#include <CGAL/Iso_rectangle_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Vector_2.h>

#include <CGAL/number_utils.h>
#include <CGAL/predicates_on_points_2.h>
#include <CGAL/predicate_objects_on_points_2.h>
#include <CGAL/Segment_2_Segment_2_intersection.h>

//-----------------------------------------------------------------------//
//                          CGAL_Polygon_traits_2_aux
//-----------------------------------------------------------------------//
// The class CGAL_Polygon_traits_2_aux is needed as a workaround for compilers
// that have problems with member functions with return type R::FT.
// The template parameter _Point is added to simplify the use of points
// with additional information. It is assumed that _Point inherits from
// CGAL_Point_2<_R>.

template <class _R, class _FT, class _Point>
class CGAL_Polygon_traits_2_aux : public _R
{
  public:
    typedef _FT                           FT;
    typedef _Point                        Point_2;
    typedef CGAL_Segment_2<_R>            Segment_2;
    typedef CGAL_Vector_2<_R>             Vector_2;

    typedef CGAL_p_Less_xy<Point_2>       Less_xy;
    typedef CGAL_p_Less_yx<Point_2>       Less_yx;

    bool lexicographically_xy_smaller(const Point_2& p, const Point_2& q) const
    {
      return CGAL_lexicographically_xy_smaller(p,q);
    }

    bool lexicographically_yx_smaller_or_equal(const Point_2& p,
                                               const Point_2& q) const
    {
      return CGAL_lexicographically_yx_smaller_or_equal(p,q);
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
      return CGAL_sign(x);
    }

    bool is_negative(const FT& x) const
    {
      return CGAL_is_negative(x);
    }

    bool do_intersect(const Point_2& p1,
                      const Point_2& q1,
                      const Point_2& p2,
                      const Point_2& q2) const
    {
      return CGAL_do_intersect(Segment_2(p1,q1), Segment_2(p2,q2));
    }

    CGAL_Orientation orientation(const Point_2& p,
                                 const Point_2& q,
                                 const Point_2& r) const
    {
       return CGAL_orientation(p, q, r);
    }

    CGAL_Comparison_result compare_x(const Point_2 &p, const Point_2 &q) const
    {
       return CGAL_compare_x(p, q);
    }

    CGAL_Comparison_result compare_y(const Point_2 &p, const Point_2 &q) const
    {
       return CGAL_compare_y(p, q);
    }

    bool have_equal_direction(const Vector_2& v1,
                              const Vector_2& v2 ) const
    {
       return CGAL_Direction_2<_R>(v1) == CGAL_Direction_2<_R>(v2);
    }
};

//-----------------------------------------------------------------------//
//                          CGAL_Polygon_traits_2
//-----------------------------------------------------------------------//
// The class CGAL_Polygon_traits_2 is a traits class for CGAL_Polygon_2.

template <class _R>
class CGAL_Polygon_traits_2 :
  public CGAL_Polygon_traits_2_aux<_R, typename _R::FT, CGAL_Point_2<_R> >
{
};

#endif // CGAL_POLYGON_TRAITS_2_H

