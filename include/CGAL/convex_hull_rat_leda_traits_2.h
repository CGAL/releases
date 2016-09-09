// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/convex_hull_rat_leda_traits_2.h
// package       : Convex_hull_2 (3.34)
// revision      : $Revision: 1.9 $
// revision_date : $Date: 2002/01/24 17:03:28 $
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

// This file's name must begin with a lower-case letter for backward 
// compatability.  Unfortunately, you can't have a file that differs only 
// in capitalization on the Windows platforms.

#ifndef CGAL_CONVEX_HULL_RAT_LEDA_TRAITS_2_H
#define CGAL_CONVEX_HULL_RAT_LEDA_TRAITS_2_H

#include <CGAL/basic.h>
#include <CGAL/rat_leda_in_CGAL_2.h>
#include <CGAL/Kernel/function_objects.h>

CGAL_BEGIN_NAMESPACE
class Convex_hull_rat_leda_traits_2
{
public:
  typedef   leda_rat_point                                  Point_2;    
  typedef   CGALi::p_Less_xy<Point_2>                       Less_xy_2;
  typedef   CGALi::p_Less_yx<Point_2>                       Less_yx_2;
  typedef   CGALi::p_Less_dist_to_line_2<Point_2>           
                                               Less_signed_distance_to_line_2;
  typedef   CGALi::p_Less_rotate_ccw<Point_2>               Less_rotate_ccw_2;
  typedef   CGALi::p_Left_turn<Point_2>                     Leftturn_2;
  typedef   leda_rat_segment                                Segment_2; 
  
  Less_xy_2
  less_xy_2_object() const 
  { return Less_xy_2(); } 

  Less_yx_2
  less_yx_2_object() const 
  { return Less_yx_2(); } 

  Less_signed_distance_to_line_2
  less_signed_distance_to_line_2_object( ) const
  { return Less_signed_distance_to_line_2( ); } 

  Less_rotate_ccw_2
  less_rotate_ccw_2_object( ) const
  { return Less_rotate_ccw_2( ); }

  Leftturn_2
  leftturn_2_object() const
  { return Leftturn_2(); }

};

// for backward compatability
typedef Convex_hull_rat_leda_traits_2   convex_hull_rat_leda_traits_2;

CGAL_END_NAMESPACE

#endif // CGAL_cONVEX_HULL_RAT_LEDA_TRAITS_2_H

