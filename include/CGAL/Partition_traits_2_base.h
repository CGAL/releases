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
// file          : include/CGAL/Partition_traits_2_base.h
// package       : Partition_2 (1.38)
// chapter       : Planar Polygon Partitioning
//
// revision      : $Revision: 1.8 $
// revision_date : $Date: 2002/03/24 12:49:47 $
//
// author(s)     : Susan Hert
//
// coordinator   : MPI (Susan Hert)
//
// implementation: Base class for polygon partitioning function traits classes
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef PARTITION_TRAITS_2_BASE_H
#define PARTITION_TRAITS_2_BASE_H

#include <CGAL/Polygon_2.h>
#include <CGAL/Polygon_traits_2.h>
#include <list>

namespace CGAL {

template <class Kernel_>
class Partition_traits_2_base
{
  private:
    typedef Kernel_                                 Kernel;
  public:
    typedef CGAL::Polygon_traits_2<Kernel>          Poly_Traits;
    typedef typename Poly_Traits::Point_2           Point_2;
    typedef ::std::list<Point_2>                    Container;
    typedef CGAL::Polygon_2<Poly_Traits, Container> Polygon_2;
    typedef typename Kernel::Less_yx_2              Less_yx_2;
    typedef typename Kernel::Less_xy_2              Less_xy_2;
    typedef typename Kernel::Leftturn_2             Leftturn_2;
    typedef typename Kernel::Orientation_2          Orientation_2;
    typedef typename Kernel::Compare_y_2            Compare_y_2;
    typedef typename Kernel::Compare_x_2            Compare_x_2;

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

    Compare_y_2
    compare_y_2_object() const
    {  return Compare_y_2(); }

    Compare_x_2
    compare_x_2_object() const
    {  return Compare_x_2(); }

};

}

#endif // PARTITION_TRAITS_2_BASE_H
