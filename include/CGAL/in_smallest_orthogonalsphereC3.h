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
// file          : include/CGAL/in_smallest_orthogonalsphereC3.h
// package       : Alpha_shapes_3 (3.16)
// source        : $RCSfile: in_smallest_orthogonalsphereC3.h,v $
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2001/06/15 15:00:42 $
// author(s)     : Tran Kai Frank DA
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_IN_SMALLEST_ORTHOGONALSPHEREC3_H 
#define CGAL_IN_SMALLEST_ORTHOGONALSPHEREC3_H

#ifndef CGAL_POINTC3_H
#include <CGAL/Cartesian/Point_3.h>
#endif // CGAL_POINTC3_H

#ifndef CGAL_WEIGHTED_POINT_H
#include <CGAL/Weighted_point.h>
#endif // CGAL_WEIGHTED_POINT_H

#include <CGAL/predicates/in_smallest_orthogonalsphere_ftC3.h>

//-------------------------------------------------------------------
CGAL_BEGIN_NAMESPACE
//-------------------------------------------------------------------

template< class FT >
CGAL_KERNEL_MEDIUM_INLINE
Bounded_side
in_smallest_orthogonalsphere(
			     const Weighted_point<Point_3< Cartesian<FT> >, FT > &p,
			     const Weighted_point<Point_3< Cartesian<FT> >, FT > &q, 
			     const Weighted_point<Point_3< Cartesian<FT> >, FT > &r,
			     const Weighted_point<Point_3< Cartesian<FT> >, FT > &t) 
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
  FT tx(t.point().x());
  FT ty(t.point().y());
  FT tz(t.point().z());
  FT tw(t.weight());

  return in_smallest_orthogonalsphereC3(px, py, pz, pw,
					qx, qy, qz, qw,
					rx, ry, rz, rw,
					tx, ty, tz, tw);
}

//-------------------------------------------------------------------
CGAL_END_NAMESPACE
//-------------------------------------------------------------------

#endif //CGAL_IN_SMALLEST_ORTHOGONALSPHEREC3_H
