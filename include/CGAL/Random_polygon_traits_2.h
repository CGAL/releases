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
// file          : include/CGAL/Random_polygon_traits_2.h
// package       : Generator (2.62)
// chapter       : Geometric Object Generators
//
// revision      : 1.0
// revision_date : 19 April 2000
//
// author(s)     : Susan Hert
//
// coordinator   : ETH Zurich (Bernd Gaertner)
//
// implementation: Random Simple Polygon Traits
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_RANDOM_POLYGON_TRAITS_2_H
#define CGAL_RANDOM_POLYGON_TRAITS_2_H

CGAL_BEGIN_NAMESPACE

//-----------------------------------------------------------------------//
//                          Random_polygon_traits_2
//-----------------------------------------------------------------------//

template <class R_>
class Random_polygon_traits_2 
{
  public:
    typedef R_                            R;
    typedef typename R::FT                FT;
    typedef typename R::Point_2           Point_2;
    typedef typename R::Less_xy_2         Less_xy_2;
    typedef typename R::Orientation_2     Orientation_2;

    Less_xy_2
    less_xy_2_object() const
    { return Less_xy_2(); }

    Orientation_2
    orientation_2_object() const
    { return Orientation_2(); }
};

CGAL_END_NAMESPACE

#endif // CGAL_RANDOM_POLYGON_TRAITS_2_H

