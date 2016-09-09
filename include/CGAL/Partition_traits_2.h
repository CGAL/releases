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
// file          : include/CGAL/Partition_traits_2.h
// package       : Partition_2 (1.38)
// chapter       : Planar Polygon Partitioning
//
// revision      : $Revision: 1.13 $
// revision_date : $Date: 2002/04/24 11:24:34 $
//
// author(s)     : Susan Hert
//
// coordinator   : MPI (Susan Hert)
//
// implementation: Traits class for polygon partitioning functions
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef PARTITION_TRAITS_2_H
#define PARTITION_TRAITS_2_H

#include <CGAL/Polygon_2.h>
#include <CGAL/Polygon_traits_2.h>
#include <CGAL/Partition_traits_2_base.h>
#include <CGAL/polygon_function_objects.h>
#include <list>

namespace CGAL {

template <class Kernel_>
class Partition_traits_2  : public Partition_traits_2_base<Kernel_>
{
  private:
    typedef Kernel_                                     Kernel;
    typedef Partition_traits_2<Kernel_>                 Self;
  public:
    typedef CGAL::Polygon_traits_2<Kernel_>             Poly_Traits;
    typedef typename Poly_Traits::Point_2               Point_2;
    typedef ::std::list<Point_2>                        Container;
    typedef CGAL::Polygon_2<Poly_Traits, Container>     Polygon_2;
    typedef typename Kernel::Less_yx_2                  Less_yx_2;
    typedef typename Kernel::Less_xy_2                  Less_xy_2;
    typedef typename Kernel::Leftturn_2                 Leftturn_2;
    typedef typename Kernel::Orientation_2              Orientation_2;
    typedef typename Kernel::Compare_y_2                Compare_y_2;
    typedef typename Kernel::Compare_x_2                Compare_x_2;
    typedef CGAL::Is_convex_2<Self>                     Is_convex_2;
    typedef CGAL::Is_y_monotone_2<Self>                 Is_y_monotone_2;

    // needed by Indirect_edge_compare, used in y_monotone and greene_approx
    typedef typename Kernel::Line_2                     Line_2;
    typedef typename Kernel::Construct_line_2           Construct_line_2;
    typedef typename Kernel::Compare_x_at_y_2           Compare_x_at_y_2;
    typedef typename Kernel::Is_horizontal_2            Is_horizontal_2;

    // needed by visibility graph and thus by optimal convex
    typedef typename Kernel::Ray_2                      Ray_2; 
    typedef typename Kernel::Collinear_are_ordered_along_line_2
                                            Collinear_are_ordered_along_line_2;
    typedef typename Kernel::Are_strictly_ordered_along_line_2
                                            Are_strictly_ordered_along_line_2;
    typedef typename Kernel::Intersect_2                Intersect_2;
    typedef typename Kernel::Assign_2                   Assign_2;
    typedef typename Kernel::Object_2                   Object_2;

    // needed by approx_convex (for constrained triangulation)
    // and optimal convex (for vis. graph)
    typedef typename Kernel::Segment_2                  Segment_2;
    // needed by optimal convex (for vis. graph)
    typedef typename Kernel::Construct_segment_2        Construct_segment_2;
    typedef typename Kernel::Construct_ray_2            Construct_ray_2;

 
    Construct_line_2
    construct_line_2_object() const
    {  return Construct_line_2(); }

    Compare_x_at_y_2
    compare_x_at_y_2_object() const
    { return Compare_x_at_y_2(); }

    Construct_segment_2
    construct_segment_2_object() const
    { return Construct_segment_2(); }

    Construct_ray_2
    construct_ray_2_object() const
    { return Construct_ray_2(); }

    Collinear_are_ordered_along_line_2
    collinear_are_ordered_along_line_2_object() const
    { return Collinear_are_ordered_along_line_2(); }

    Are_strictly_ordered_along_line_2
    are_strictly_ordered_along_line_2_object() const
    { return Are_strictly_ordered_along_line_2(); }

    Is_horizontal_2
    is_horizontal_2_object() const
    {  return Is_horizontal_2(); }

    Is_convex_2
    is_convex_2_object(const Self& traits) const
    {  return Is_convex_2(traits); }

    Is_y_monotone_2
    is_y_monotone_2_object(const Self& traits) const
    {  return Is_y_monotone_2(traits); }

    Intersect_2
    intersect_2_object() const
    {  return Intersect_2(); }

    Assign_2
    assign_2_object() const
    {  return Assign_2(); }
};

}

#endif // PARTITION_TRAITS_2_H
