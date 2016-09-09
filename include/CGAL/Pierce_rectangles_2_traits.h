// ======================================================================
//
// Copyright (c) 1998, 1999, 2000 The CGAL Consortium

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
// file          : include/CGAL/Pierce_rectangles_2_traits.h
// package       : Matrix_search (1.54)
// chapter       : $CGAL_Chapter: Geometric Optimisation $
// source        : pcenter.aw
// revision      : $Revision: 1.52 $
// revision_date : $Date: 2002/03/25 15:04:55 $
// author(s)     : Michael Hoffmann
//
// coordinator   : ETH
//
// 2-4-Piercing Axis-Parallel 2D-Rectangles
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#if ! (CGAL_PIERCE_RECTANGLES_2_TRAITS_H)
#define CGAL_PIERCE_RECTANGLES_2_TRAITS_H 1

#include <CGAL/Point_2.h>

CGAL_BEGIN_NAMESPACE

template < class R_ >
struct Piercing_traits_cartesian {
  // types
  typedef R_                           R;
  typedef typename R::FT               FT;
  typedef Point_2< R >                 Point_2;
  // constructions
  typedef Infinity_distance_2< R >     Infinity_distance_2;

  // get object methods:
  Infinity_distance_2
  get_infinity_distance_2() const
  { return Infinity_distance_2(); }

}; // Piercing_traits_cartesian
CGAL_END_NAMESPACE


#endif // ! (CGAL_PIERCE_RECTANGLES_2_TRAITS_H)
// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

