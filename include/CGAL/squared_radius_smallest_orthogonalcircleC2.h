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
// file          : include/CGAL/squared_radius_smallest_orthogonalcircleC2.h
// package       : Alpha_shapes_2 (11.19)
// source        : $RCSfile: squared_radius_smallest_orthogonalcircleC2.h,v $
// revision      : $Revision: 1.7 $
// revision_date : $Date: 2001/06/15 15:02:05 $
// author(s)     : Tran Kai Frank DA
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_SQUARED_RADIUS_SMALLEST_ORTHOGONALCIRCLEC2_H 
#define CGAL_SQUARED_RADIUS_SMALLEST_ORTHOGONALCIRCLEC2_H

#ifndef CGAL_POINTC2_H
#include <CGAL/Cartesian/Point_2.h>
#endif // CGAL_POINTC2_H

#ifndef CGAL_WEIGHTED_POINT_H
#include <CGAL/Weighted_point.h>
#endif // CGAL_WEIGHTED_POINT_H

#include <CGAL/constructions/squared_radius_smallest_orthogonalcircle_ftC2.h>

//-------------------------------------------------------------------
CGAL_BEGIN_NAMESPACE
//-------------------------------------------------------------------

template< class FT >
CGAL_KERNEL_MEDIUM_INLINE
FT 
squared_radius_orthogonalcircle(
  const Weighted_point<Point_2< Cartesian<FT> >, FT> &p,
  const Weighted_point<Point_2< Cartesian<FT> >, FT> &q,
  const Weighted_point<Point_2< Cartesian<FT> >, FT> &r) 
{   
  FT px(p.point().x());
  FT py(p.point().y());
  FT pw(p.weight());
  FT qx(q.point().x());
  FT qy(q.point().y());
  FT qw(q.weight());
  FT rx(r.point().x());
  FT ry(r.point().y());
  FT rw(r.weight()); 

  return squared_radius_orthogonalcircleC2(px, py, pw,
					   qx, qy, qw,
					   rx, ry, rw);
}

template< class FT >
CGAL_KERNEL_MEDIUM_INLINE
FT 
squared_radius_smallest_orthogonalcircle(
   const Weighted_point<Point_2< Cartesian<FT> >, FT> &p,
   const Weighted_point<Point_2< Cartesian<FT> >, FT> &q) 
{
  FT px(p.point().x());
  FT py(p.point().y());
  FT pw(p.weight());
  FT qx(q.point().x());
  FT qy(q.point().y());
  FT qw(q.weight());
  
  return squared_radius_smallest_orthogonalcircleC2(px, py, pw,
						    qx, qy, qw);
}

//-------------------------------------------------------------------
CGAL_END_NAMESPACE
//-------------------------------------------------------------------

#endif //CGAL_SQUARED_RADIUS_SMALLEST_ORTHOGONALCIRCLEC2_H

