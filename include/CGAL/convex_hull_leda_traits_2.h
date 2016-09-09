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
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/convex_hull_leda_traits_2.h
// package       : Convex_hull_2 (3.21)
// revision      : $Revision: 1.6 $
// revision_date : $Date: 2001/07/20 09:21:22 $
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


#ifndef CGAL_CONVEX_HULL_LEDA_TRAITS_2_H
#define CGAL_CONVEX_HULL_LEDA_TRAITS_2_H

#include <CGAL/ch_utils.h>
#include <CGAL/leda_in_CGAL_2.h>
#include <CGAL/predicate_objects_on_points_2.h>

CGAL_BEGIN_NAMESPACE
class Convex_hull_leda_traits_2
{
public:
  typedef   leda_point                                      Point_2;    
  typedef   CGAL::p_Less_xy<Point_2>                        Less_xy_2;
  typedef   CGAL::p_Less_yx<Point_2>                        Less_yx_2;
  typedef   CGAL::p_Less_dist_to_line_2<Point_2>           
                                               Less_signed_distance_to_line_2;
  typedef   CGAL::p_Less_rotate_ccw<Point_2>                Less_rotate_ccw_2;
  typedef   CGAL::p_Leftturn<Point_2>                       Leftturn_2;
  typedef   leda_segment                                    Segment_2; 
  
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
  { return Less_rotate_ccw_2(); }

  Leftturn_2
  leftturn_2_object() const
  { return Leftturn_2(); }

};

// for backward compatability
typedef Convex_hull_leda_traits_2   convex_hull_leda_traits_2;

CGAL_END_NAMESPACE

#endif // CGAL_CONVEX_HULL_LEDA_TRAITS_2_H

