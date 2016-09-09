// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/convex_hull_leda_traits_2.h
// author(s)     : Stefan Schirra 
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


#ifndef CGAL_CONVEX_HULL_LEDA_TRAITS_2_H
#define CGAL_CONVEX_HULL_LEDA_TRAITS_2_H

#include <CGAL/ch_utils.h>
#include <CGAL/leda_in_CGAL_2.h>
#include <CGAL/predicate_objects_on_points_2.h>

class CGAL_convex_hull_leda_traits_2
{
public:
  typedef   leda_point                                     Point_2;    
  typedef   CGAL_p_Less_xy<Point_2>                        Less_xy;
  typedef   CGAL_p_Less_yx<Point_2>                        Less_yx;
  typedef   CGAL_p_Right_of_line_2p<Point_2>               Right_of_line;
  typedef   CGAL_p_Less_negative_dist_to_line_2p<Point_2>  Less_dist_to_line;
  typedef   CGAL_p_Less_rotate_ccw<Point_2>                Less_rotate_ccw;
  typedef   CGAL_p_Leftturn<Point_2>                       Leftturn;
  typedef   CGAL_p_Rightturn<Point_2>                      Rightturn;
  typedef   leda_segment                                   Segment_2; 
};

#endif // CGAL_CONVEX_HULL_LEDA_TRAITS_2_H
