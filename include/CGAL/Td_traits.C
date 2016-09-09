// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// file          : include/CGAL/Td_traits.C
// package       : Trapezoidal_decomposition (1.17)
// source        : 
// revision      : 
// revision_date : 
// author(s)     : Oren Nechushtan
//
//
// maintainer(s) : Oren Nechushtan
//
//
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// Chapter       : 
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_TD_TRAITS_H
#include <CGAL/Td_traits.h>
#endif

CGAL_BEGIN_NAMESPACE

template <class Traits,class X_curve_plus>
const typename Td_traits<Traits,X_curve_plus>::Point&
Td_traits<Traits,X_curve_plus>::get_point_at_left_top_infinity(){
  /*
  static typename Td_traits<Traits,X_curve_plus>::Point
    Td_traits<Traits,X_curve_plus>::POINT_AT_LEFT_TOP_INFINITY;
  return Td_traits<Traits,X_curve_plus>::POINT_AT_LEFT_TOP_INFINITY;
  */
  //  static Point POINT_AT_LEFT_TOP_INFINITY;
  return POINT_AT_LEFT_TOP_INFINITY;
}

template <class Traits,class X_curve_plus>
const typename Td_traits<Traits,X_curve_plus>::Point&
Td_traits<Traits,X_curve_plus>::get_point_at_right_bottom_infinity(){
  /*
  static typename Td_traits<Traits,X_curve_plus>::Point
    Td_traits<Traits,X_curve_plus>::POINT_AT_RIGHT_BOTTOM_INFINITY;
  return Td_traits<Traits,X_curve_plus>::POINT_AT_RIGHT_BOTTOM_INFINITY;
  */
  //  static Point POINT_AT_RIGHT_BOTTOM_INFINITY;
  return POINT_AT_RIGHT_BOTTOM_INFINITY;
}

template <class Traits,class X_curve_plus>
const typename Td_traits<Traits,X_curve_plus>::X_curve&
Td_traits<Traits,X_curve_plus>::get_curve_at_infinity(){
  /*
  static typename typename Traits::X_curveTraits::X_curve 
    Td_traits<Traits,X_curve_plus>::CURVE_AT_INFINITY;
  return Td_traits<Traits,X_curve_plus>::CURVE_AT_INFINITY;
  */
  //  static X_curve CURVE_AT_INFINITY;
  return CURVE_AT_INFINITY;
}

template <class Traits,class X_curve_plus>
typename Td_traits<Traits,X_curve_plus>::Point
Td_traits<Traits,X_curve_plus>::POINT_AT_LEFT_TOP_INFINITY = 
Point(0,0);

template <class Traits,class X_curve_plus>
typename Td_traits<Traits,X_curve_plus>::Point
Td_traits<Traits,X_curve_plus>::POINT_AT_RIGHT_BOTTOM_INFINITY = 
Point(0,0);


template <class Traits,class X_curve_plus>
typename Td_traits<Traits,X_curve_plus>::X_curve
Td_traits<Traits,X_curve_plus>::CURVE_AT_INFINITY = X_curve();

CGAL_END_NAMESPACE
