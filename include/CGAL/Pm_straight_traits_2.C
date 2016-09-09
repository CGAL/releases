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
// file          : include/CGAL/Pm_straight_traits_2.C
// package       : Planar_map (5.113)
// source        : 
// revision      : 
// revision_date : 
// author(s)     : Oren Nechushtan
//                 
//
//
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// Chapter       : 
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_PM_STRAIGHT_TRAITS_2_C
#define CGAL_PM_STRAIGHT_TRAITS_2_C

#ifndef CGAL_PM_STRAIGHT_TRAITS_2_H
#include <CGAL/Pm_straight_traits_2.h>
#endif

CGAL_BEGIN_NAMESPACE

template <class R_>
const typename Pm_straight_traits_2<R_>::Bounding_box 
Pm_straight_traits_2<R_>::unbounded_box()
{
  static const typename Pm_straight_traits_2<R_>::Bounding_box 
    unbounded_box_;
  return unbounded_box_;
}

template <class R_>
const typename Pm_straight_traits_2<R_>::Bounding_box 
Pm_straight_traits_2<R_>::unbounded_box_;
// unbounded_box_ initialized to default Bounding_box

CGAL_END_NAMESPACE

#endif // CGAL_PM_STRAIGHT_TRAITS_2_C
// EOF

