// ======================================================================
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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/convex_hull_constructive_traits_2.h
// package       : Convex_hull (1.3.2)
// source        : convex_hull_2.lw
// revision      : 1.3.2
// revision_date : 09 Dec 1998
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_CONVEX_HULL_CONSTRUCTIVE_TRAITS_2_H 
#define CGAL_CONVEX_HULL_CONSTRUCTIVE_TRAITS_2_H

#include <CGAL/Point_2.h>
#include <CGAL/Line_2.h>
#include <CGAL/predicates_on_points_2.h>
#include <CGAL/distance_predicates_2.h>
#include <CGAL/predicate_objects_on_points_2.h>

template <class _R>
class CGAL_convex_hull_constructive_traits_2 : public _R
{
public:
  typedef   _R                                             R;
  typedef   CGAL_Point_2<R>                                Point_2;    
  typedef   CGAL_p_Less_xy<Point_2>                        Less_xy;
  typedef   CGAL_p_Less_yx<Point_2>                        Less_yx;
  typedef   CGAL_r_Right_of_line<R>                        Right_of_line;
  typedef   CGAL_r_Less_negative_dist_to_line<R>           Less_dist_to_line;
  typedef   CGAL_p_Less_rotate_ccw<Point_2>                Less_rotate_ccw;
  typedef   CGAL_p_Leftturn<Point_2>                       Leftturn;
  typedef   CGAL_p_Rightturn<Point_2>                      Rightturn;
  typedef   CGAL_Segment_2<R>                              Segment_2;    
  
  Less_xy
  get_less_xy_object() const 
  { return Less_xy(); } 

  Less_yx
  get_less_yx_object() const 
  { return Less_yx(); } 

  Right_of_line
  get_right_of_line_object( const Point_2& p, const Point_2& q) const 
  { return Right_of_line( p, q); } 

  Less_dist_to_line
  get_less_dist_to_line_object( const Point_2& p, const Point_2& q) const
  { return Less_dist_to_line( p, q); } 

  Less_rotate_ccw
  get_less_rotate_ccw_object( const Point_2& p ) const
  { return Less_rotate_ccw( p); }

  Leftturn
  get_leftturn_object() const
  { return Leftturn(); }

  Rightturn
  get_rightturn_object() const
  { return Rightturn(); }
};


#endif // CGAL_CONVEX_HULL_CONSTRUCTIVE_TRAITS_2_H

