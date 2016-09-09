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
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/squared_radius_smallest_orthogonalsphereC3.h
// package       : Alpha_shapes_3 (3.6)
// source        : $RCSfile: squared_radius_smallest_orthogonalsphereC3.h,v $
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2001/06/15 15:00:45 $
// author(s)     : Tran Kai Frank DA
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_SQUARED_RADIUS_SMALLEST_ORTHOGONALSPHEREC3_H 
#define CGAL_SQUARED_RADIUS_SMALLEST_ORTHOGONALSPHEREC3_H

#ifndef CGAL_POINTC3_H
#include <CGAL/Cartesian/Point_3.h>
#endif // CGAL_POINTC3_H

#ifndef CGAL_WEIGHTED_POINT_H
#include <CGAL/Weighted_point.h>
#endif // CGAL_WEIGHTED_POINT_H

#include <CGAL/constructions/squared_radius_smallest_orthogonalsphere_ftC3.h>

//-------------------------------------------------------------------
CGAL_BEGIN_NAMESPACE
//-------------------------------------------------------------------

template< class FT >
CGAL_KERNEL_MEDIUM_INLINE
FT 
squared_radius_orthogonalsphere(
  const Weighted_point<Point_3< Cartesian<FT> >, FT> &p,
  const Weighted_point<Point_3< Cartesian<FT> >, FT> &q,
  const Weighted_point<Point_3< Cartesian<FT> >, FT> &r,
  const Weighted_point<Point_3< Cartesian<FT> >, FT> &s) 
{  
  FT px(p.point().x());
  FT py(p.point().y());
  FT pz(p.point().z());
  FT pw(p.weight());
  FT qx(q.point().x());
  FT qy(q.point().y());
  FT qz(q.point().z());
  FT qw(q.weight());
  FT rx(r.point().x());
  FT ry(r.point().y()); 
  FT rz(r.point().z());
  FT rw(r.weight()); 
  FT sx(s.point().x());
  FT sy(s.point().y());
  FT sz(s.point().z());
  FT sw(s.weight());
  return squared_radius_orthogonalsphereC3(px, py, pz, pw,
					   qx, qy, qz, qw,
					   rx, ry, rz, rw,
					   sx, sy, sz, sw);
}

template< class FT >
CGAL_KERNEL_MEDIUM_INLINE
FT 
squared_radius_smallest_orthogonalsphere(
  const Weighted_point<Point_3< Cartesian<FT> >, FT> &p,
  const Weighted_point<Point_3< Cartesian<FT> >, FT> &q,
  const Weighted_point<Point_3< Cartesian<FT> >, FT> &r) 
{   
  FT px(p.point().x());
  FT py(p.point().y());
  FT pz(p.point().z());
  FT pw(p.weight());
  FT qx(q.point().x());
  FT qy(q.point().y());
  FT qz(q.point().z());
  FT qw(q.weight());
  FT rx(r.point().x());
  FT ry(r.point().y()); 
  FT rz(r.point().z());
  FT rw(r.weight()); 

  return squared_radius_smallest_orthogonalsphereC3(px, py, pz, pw,
						    qx, qy, qz, qw,
						    rx, ry, rz, rw);
}

template< class FT >
CGAL_KERNEL_MEDIUM_INLINE
FT 
squared_radius_smallest_orthogonalsphere(
   const Weighted_point<Point_3< Cartesian<FT> >, FT> &p,
   const Weighted_point<Point_3< Cartesian<FT> >, FT> &q) 
{
  FT px(p.point().x());
  FT py(p.point().y());
  FT pz(p.point().z());
  FT pw(p.weight());
  FT qx(q.point().x());
  FT qy(q.point().y());
  FT qz(q.point().z());
  FT qw(q.weight());

  return squared_radius_smallest_orthogonalsphereC3(px, py, pz, pw,
						    qx, qy, qz, qw);
}

//-------------------------------------------------------------------
CGAL_END_NAMESPACE
//-------------------------------------------------------------------

#endif //CGAL_SQUARED_RADIUS_SMALLEST_ORTHOGONALSPHERE_C3_H
