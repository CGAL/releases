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
// file          : include/CGAL/Partition_traits_2_base.h
// package       : Partition_2 (1.18)
// chapter       : Planar Polygon Partitioning
//
// revision      : $Revision: 1.7 $
// revision_date : $Date: 2001/07/06 17:04:43 $
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

template <class R_>
class Partition_traits_2_base
{
  public:
    typedef R_                                      R;
    typedef CGAL::Polygon_traits_2<R>               Poly_Traits;
    typedef typename Poly_Traits::Point_2           Point_2;
    typedef ::std::list<Point_2>                    Container;
    typedef CGAL::Polygon_2<Poly_Traits, Container> Polygon_2;
    typedef typename R::Less_yx_2                   Less_yx_2;
    typedef typename R::Less_xy_2                   Less_xy_2;
    typedef typename R::Leftturn_2                  Leftturn_2;
    typedef typename R::Orientation_2               Orientation_2;
    typedef typename R::Compare_y_2                 Compare_y_2;
    typedef typename R::Compare_x_2                 Compare_x_2;


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
