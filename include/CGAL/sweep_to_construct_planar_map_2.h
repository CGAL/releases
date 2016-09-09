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
// file          : include/CGAL/sweep_to_construct_planar_map_2.h
// package       : Sweep_line_2 (1.33)
// source        : 
// revision      : 
// revision_date : 
// author(s)     : Eti Ezra
//
//
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// Chapter       : 
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_SWEEP_TO_CONSTRUCT_PLANAR_MAP_2_H
#define CGAL_SWEEP_TO_CONSTRUCT_PLANAR_MAP_2_H

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif

#ifndef CGAL_SWEEP_CURVES_TO_PLANAR_MAP_2_H
#include <CGAL/Sweep_line_2/Sweep_curves_to_planar_map_2.h>
#endif

CGAL_BEGIN_NAMESPACE

template <class Curve_iterator, class SweepLineTraits_2, class PM>
void sweep_to_construct_planar_map_2(Curve_iterator curves_begin, 
                                     Curve_iterator curves_end,
                                     SweepLineTraits_2 & traits,
                                     PM & result,
                                     typename PM::Change_notification * 
                                       change_notification = 0)
{
  Sweep_curves_to_planar_map_2<Curve_iterator, 
                               SweepLineTraits_2, 
                               PM,
                               CGAL_TYPENAME_MSVC_NULL
                                 PM::Change_notification> 
    sweep_line(&traits);
  
  sweep_line.sweep_curves_to_planar_map(curves_begin, 
                                        curves_end, 
                                        result,
                                        change_notification);
}


CGAL_END_NAMESPACE

#endif
