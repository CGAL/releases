// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
//
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/side_of_smallest_circle_2.h
// package       : Alpha_shapes_2 (8.3)
// source        : $RCSfile: side_of_smallest_circle_2.h,v $
// revision      : $Revision: 1.1.1.1 $
// revision_date : $Date: 1999/07/27 14:19:40 $
// author(s)     : Tran Kai Frank DA
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
// Additional predicates for predicates_on_points_2.h needed for computing
// alpha-shapes.
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_SIDE_OF_SMALLEST_CIRCLE_2_PLUS_H
#define CGAL_SIDE_OF_SMALLEST_CIRCLE_2_PLUS_H
#include <CGAL/Point_2.h>
#include <CGAL/Vector_2.h>
#include <CGAL/predicates_on_points_2.h>

#include <CGAL/smallest_radius_2.h>

//-------------------------------------------------------------------
CGAL_BEGIN_NAMESPACE
//-------------------------------------------------------------------

template <class R >
inline Bounded_side side_of_bounded_circle(const Point_2<R>& p,
					   const Point_2<R>& q,
					   const Point_2<R>& test) 
{
  
  Vector_2<R> v(test - (p + (q - p)/2));
  typename R::FT squared_distance = v*v;

  typename R::FT squared_radius = squared_radius_smallest_circumcircle(p, q);
 
  return (squared_radius > squared_distance) ?
    ON_BOUNDED_SIDE :
    ((squared_radius < squared_distance) ?
     ON_UNBOUNDED_SIDE :
     ON_BOUNDARY);
}

//-------------------------------------------------------------------
CGAL_END_NAMESPACE
//-------------------------------------------------------------------

#endif  // SIDE_OF_SMALLEST_CIRCLE_2_PLUS_H
