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
// file          : include/CGAL/smallest_radius_2.h
// package       : Alpha_shapes_2 (8.3)
// source        : $RCSfile: smallest_radius_2.h,v $
// revision      : $Revision: 1.6 $
// revision_date : $Date: 2000/02/04 12:56:06 $
// author(s)     : Tran Kai Frank DA
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_SMALLEST_RADIUS_2_H
#define CGAL_SMALLEST_RADIUS_2_H

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/smallest_radiusH2.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/smallest_radiusC2.h>
#endif // CGAL_CARTESIAN_H

#include <CGAL/Point_2.h>
#include <CGAL/Circle_2.h>

//-------------------------------------------------------------------
CGAL_BEGIN_NAMESPACE
//-------------------------------------------------------------------

template <class R >
inline
typename R::FT
squared_radius_smallest_circumcircle(const Point_2<R> &p,
				     const Point_2<R> &q) 
{
  typedef typename R::FT Return_type;
  Vector_2<R> v(p - q);
  return (Return_type ((v*v)/4));
}

template <class R >
inline
typename R::FT
squared_radius_circumcircle(const Point_2<R> &p,
			    const Point_2<R> &q,
			    const Point_2<R> &r) 
{
  typedef typename R::Point_2_base Point_two; 
  // compute the smallest radius directly
  return squared_radius_circumcircle((const Point_two&) p,
				     (const Point_two&) q,
				     (const Point_two&) r);
}

//-------------------------------------------------------------------
CGAL_END_NAMESPACE
//-------------------------------------------------------------------

#endif // SMALLEST_RADIUS_2_H

