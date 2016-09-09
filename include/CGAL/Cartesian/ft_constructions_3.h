// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

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
// file          : include/CGAL/Cartesian/ft_constructions_3.h
// package       : Cartesian_kernel (6.59)
// revision      : $Revision: 1.5 $
// revision_date : $Date: 2002/01/23 17:59:13 $
// author(s)     : Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_FT_CONSTRUCTIONS_3_H
#define CGAL_CARTESIAN_FT_CONSTRUCTIONS_3_H

#include <CGAL/Cartesian/Point_3.h>
#include <CGAL/Cartesian/Vector_3.h>
#include <CGAL/Cartesian/Plane_3.h>
#include <CGAL/constructions/kernel_ftC3.h>

CGAL_BEGIN_NAMESPACE

template < class R >
inline
typename R::FT
squared_distance(const PointC3<R> &p,
                 const PointC3<R> &q)
{
  return squared_distanceC3(p.x(), p.y(), p.z(), q.x(), q.y(), q.z());
}

template < class R >
inline
typename R::FT
scaled_distance_to_plane(const PlaneC3<R> &h,
                         const PointC3<R> &p)
{
  return scaled_distance_to_planeC3(h.a(), h.b(), h.c(), h.d(),
                                    p.x(), p.y(), p.z());
}

template < class R >
inline
typename R::FT
scaled_distance_to_plane(const PointC3<R> &hp,
                         const PointC3<R> &hq,
                         const PointC3<R> &hr,
                         const PointC3<R> &p)
{
  return scaled_distance_to_planeC3(hp.x(), hp.y(), hp.z(),
                                    hq.x(), hq.y(), hq.z(),
                                    hr.x(), hr.y(), hr.z(),
                                    p.x(), p.y(), p.z());
}

template < class R >
inline
typename R::FT
squared_radius(const PointC3<R> &p,
                     const PointC3<R> &q,
                     const PointC3<R> &r)
{
  return squared_radiusC3(p.x(), p.y(), p.z(),
	                  q.x(), q.y(), q.z(),
			  r.x(), r.y(), r.z());
}

template < class R >
inline
typename R::FT
squared_radius(const PointC3<R> &p,
                     const PointC3<R> &q,
                     const PointC3<R> &r,
                     const PointC3<R> &s)
{
  return squared_radiusC3(p.x(), p.y(), p.z(),
	                  q.x(), q.y(), q.z(),
			  r.x(), r.y(), r.z(),
			  s.x(), s.y(), s.z());
}

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_FT_CONSTRUCTIONS_3_H
