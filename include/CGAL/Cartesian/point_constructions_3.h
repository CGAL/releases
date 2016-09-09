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
// file          : include/CGAL/Cartesian/point_constructions_3.h
// package       : Cartesian_kernel (6.59)
// revision      : $Revision: 1.5 $
// revision_date : $Date: 2002/01/23 17:59:15 $
// author(s)     : Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_POINT_CONSTRUCTIONS_3_H
#define CGAL_CARTESIAN_POINT_CONSTRUCTIONS_3_H

#include <CGAL/Cartesian/Point_3.h>
#include <CGAL/constructions/kernel_ftC3.h>

CGAL_BEGIN_NAMESPACE

template < class R >
CGAL_KERNEL_MEDIUM_INLINE
PointC3<R>
midpoint(const PointC3<R> &p,
         const PointC3<R> &q)
{
  typename R::FT x, y, z;
  midpointC3(p.x(), p.y(), p.z(), q.x(), q.y(), q.z(), x, y, z);
  return PointC3<R>(x, y, z);
}

template < class R >
PointC3<R>
centroid(const PointC3<R> &p,
         const PointC3<R> &q,
         const PointC3<R> &r,
         const PointC3<R> &s)
{
  typename R::FT x, y, z;
  centroidC3(p.x(), p.y(), p.z(),
             q.x(), q.y(), q.z(),
             r.x(), r.y(), r.z(),
             s.x(), s.y(), s.z(),
             x, y, z);
  return PointC3<R>(x, y, z);
}

template < class R >
PointC3<R>
centroid(const PointC3<R> &p,
         const PointC3<R> &q,
         const PointC3<R> &r)
{
  typename R::FT x, y, z;
  centroidC3(p.x(), p.y(), p.z(),
             q.x(), q.y(), q.z(),
             r.x(), r.y(), r.z(),
             x, y, z);
  return PointC3<R>(x, y, z);
}

template < class R >
PointC3<R>
circumcenter(const PointC3<R> &p,
             const PointC3<R> &q,
             const PointC3<R> &r,
             const PointC3<R> &s)
{
  typename R::FT x, y, z;
  circumcenterC3(p.x(), p.y(), p.z(),
                 q.x(), q.y(), q.z(),
                 r.x(), r.y(), r.z(),
                 s.x(), s.y(), s.z(),
                 x, y, z);
  return PointC3<R>(x, y, z);
}

template < class R >
PointC3<R>
circumcenter(const PointC3<R> &p,
             const PointC3<R> &q,
             const PointC3<R> &r)
{
  typename R::FT x, y, z;
  circumcenterC3(p.x(), p.y(), p.z(),
                 q.x(), q.y(), q.z(),
                 r.x(), r.y(), r.z(),
                 x, y, z);
  return PointC3<R>(x, y, z);
}

template <class R>
CGAL_KERNEL_LARGE_INLINE
PointC3<R>
point_on_line(int i, const LineC3<R> &l)
{
  typename R::FT x, y, z;
  point_on_lineC3(l.point().x(), l.point().y(), l.point().z(),
                  l.direction().dx(), l.direction().dy(), l.direction().dz(),
                  i, x, y, z);
  return PointC3<R>(x, y, z);
}

template <class R>
CGAL_KERNEL_LARGE_INLINE
PointC3<R>
projection_line(const PointC3<R> &p, const LineC3<R> &l)
{
  typename R::FT x, y, z;
  projection_lineC3(p.x(), p.y(), p.z(),
		    l.point().x(), l.point().y(), l.point().z(),
                    l.direction().dx(), l.direction().dy(), l.direction().dz(),
                    x, y, z);
  return PointC3<R>(x, y, z);
}

template <class R>
CGAL_KERNEL_LARGE_INLINE
PointC3<R>
point_on_plane(const PlaneC3<R> &p)
{
  typename R::FT x, y, z;
  point_on_planeC3(p.a(), p.b(), p.c(), p.d(), x, y, z);
  return PointC3<R>(x, y, z);
}

template <class R>
CGAL_KERNEL_LARGE_INLINE
PointC3<R>
projection_plane(const PointC3<R> &p,
                 const PlaneC3<R> &h)
{
  typename R::FT x, y, z;
  projection_planeC3(h.a(), h.b(), h.c(), h.d(),
                     p.x(), p.y(), p.z(),
                     x, y, z);
  return PointC3<R>(x, y, z);
}

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_POINT_CONSTRUCTIONS_3_H
