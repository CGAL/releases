// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/Vertex_visibility_traits_2.h
// package       : Partition_2 (1.18)
// chapter       : Planar Polygon Partitioning
//
// revision      : $Revision: 1.5 $
// revision_date : $Date: 2001/01/12 12:58:50 $
//
// author(s)     : Susan Hert
//
// coordinator   : MPI (Susan Hert)
//
// implementation: Traits class for polygon vertex visibility graph
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef VERTEX_VISIBILITY_TRAITS_2_H
#define VERTEX_VISIBILITY_TRAITS_2_H


#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Ray_2.h>
#include <CGAL/Direction_2.h>

namespace CGAL {

template <class R_>
class Vertex_visibility_traits_2  
{
  public:
    typedef R_                               R;
    typedef typename R::Point_2              Point_2; 
    typedef typename R::Segment_2            Segment_2; 
    typedef typename R::Ray_2                Ray_2; 
    typedef typename R::Construct_segment_2  Construct_segment_2;
    typedef typename R::Construct_ray_2      Construct_ray_2;
    typedef typename R::Less_yx_2            Less_yx_2;
    typedef typename R::Less_xy_2            Less_xy_2;
    typedef typename R::Compare_x_2          Compare_x_2;
    typedef typename R::Compare_y_2          Compare_y_2;
    typedef typename R::Leftturn_2           Leftturn_2;
    typedef typename R::Orientation_2        Orientation_2;
    typedef typename R::Collinear_are_ordered_along_line_2
                                          Collinear_are_ordered_along_line_2;
    typedef typename R::Are_strictly_ordered_along_line_2
                                          Are_strictly_ordered_along_line_2;

    // Needed for Polygon_algorithms_2 without the _2
    typedef typename R::Less_xy_2            Less_xy;

    // Needed for simplicity and CCW order precondition checking
    typedef typename R::Vector_2             Vector_2;
    typedef typename R::FT                   FT;

 
    // necessary for the simplicity precondition checking
    Comparison_result 
    compare_x(const Point_2 &p, const Point_2 &q) const
    {
       return ::CGAL::compare_x(p, q);
    }

    // necessary for simplicity precondition checking
    Comparison_result 
    compare_y(const Point_2 &p, const Point_2 &q) const
    {
       return ::CGAL::compare_y(p, q);
    }

    // necessary for convexity postcondition checking
    bool 
    lexicographically_xy_smaller(const Point_2& p, const Point_2& q) const
    {
       return Less_xy_2()(p,q);
    }

    // necessary for convexity postcondition checking
    ::CGAL::Orientation 
    orientation(const Point_2& p, const Point_2& q, const Point_2& r) const
    {
       return Orientation_2()(p,q,r);
    }


    // ----------
    //   needed for simplicity and counterclockwise order precondition checking
    FT 
    cross_product_2(const ::CGAL::Vector_2<R>& p, 
                    const ::CGAL::Vector_2<R>& q) const
    {
        return p.x() * q.y() - q.x() * p.y();
    }

    bool 
    do_intersect(const Point_2& p1, const Point_2& q1, const Point_2& p2,
                 const Point_2& q2) const
    {
       return ::CGAL::do_intersect(Segment_2(p1,q1), Segment_2(p2,q2));
    }

    bool 
    have_equal_direction(const ::CGAL::Vector_2<R>& v1, 
                         const ::CGAL::Vector_2<R>& v2) const
    {
       return ::CGAL::Direction_2<R>(v1) == ::CGAL::Direction_2<R>(v2);
    }

    bool 
    is_negative(const FT& x) const
    {
       return CGAL_NTS is_negative(x);
    }

    bool 
    lexicographically_yx_smaller_or_equal(const Point_2& p, 
                                          const Point_2& q) const
    {
       return ::CGAL::lexicographically_yx_smaller_or_equal(p,q);
    }
    // ----------

    Compare_x_2
    compare_x_2_object() const
    {  return Compare_x_2(); }

    Compare_y_2
    compare_y_2_object() const
    {  return Compare_y_2(); }

    Less_yx_2
    less_yx_2_object() const
    { return Less_yx_2(); }

    Less_xy_2
    less_xy_2_object() const
    { return Less_xy_2(); }

    Leftturn_2
    leftturn_2_object() const
    { return Leftturn_2(); }

    Orientation_2
    orientation_2_object() const
    { return Orientation_2(); }

    Collinear_are_ordered_along_line_2
    collinear_are_ordered_along_line_2_object() const
    { return Collinear_are_ordered_along_line_2(); }

    Are_strictly_ordered_along_line_2
    are_strictly_ordered_along_line_2_object() const
    { return Are_strictly_ordered_along_line_2(); }

    Construct_segment_2
    construct_segment_2_object() const
    { return Construct_segment_2(); }

    Construct_ray_2
    construct_ray_2_object() const
    { return Construct_ray_2(); }

};

}

#endif // VERTEX_VISIBILITY_TRAITS_2_H
