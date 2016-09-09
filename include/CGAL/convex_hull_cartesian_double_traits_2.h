// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : include/CGAL/convex_hull_cartesian_double_traits_2.h
// package       : Convex_hull (2.2.19)
// source        : convex_hull_2.lw
// revision      : 2.2.19
// revision_date : 03 Dec 1999
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_CONVEX_HULL_TRAITS_CARTESIAN_DOUBLE_2_H
#define CGAL_CONVEX_HULL_TRAITS_CARTESIAN_DOUBLE_2_H

#include <CGAL/Point_2.h>
#include <CGAL/predicates_on_points_2.h>
#include <CGAL/distance_predicates_2.h>
#include <CGAL/predicate_objects_on_points_2.h>

CGAL_BEGIN_NAMESPACE
template <class R> class convex_hull_traits_2;

CGAL_TEMPLATE_NULL
class convex_hull_traits_2< Cartesian<double> > 
  : public Cartesian<double>
{
public:
  typedef   CGAL::Cartesian<double>                         R;
  typedef   CGAL::Point_2<R>                                Point_2;    
  typedef   CGAL::p_Less_xy<Point_2>                        Less_xy;
  typedef   CGAL::p_Less_yx<Point_2>                        Less_yx;
  typedef   CGAL::p_Right_of_line_2p_safer<Point_2>         Right_of_line;
  typedef   CGAL::p_Less_negative_dist_to_line_2p<Point_2>  Less_dist_to_line;
  typedef   CGAL::p_Less_rotate_ccw_safer<Point_2>          Less_rotate_ccw;
  typedef   CGAL::p_Leftturn<Point_2>                       Leftturn;
  typedef   CGAL::p_Rightturn<Point_2>                      Rightturn;
  typedef   CGAL::Segment_2<R>                              Segment_2;    
  
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
CGAL_END_NAMESPACE

#endif // CGAL_CONVEX_HULL_TRAITS_CARTESIAN_DOUBLE_2_H

