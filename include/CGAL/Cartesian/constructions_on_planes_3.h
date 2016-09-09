// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

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
// file          : include/CGAL/Cartesian/constructions_on_planes_3.h
// package       : C3 (5.2)
// revision      : $Revision: 1.11 $
// revision_date : $Date: 2000/06/27 14:06:46 $
// author(s)     : Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_CONSTRUCTIONS_ON_PLANES_3_H
#define CGAL_CARTESIAN_CONSTRUCTIONS_ON_PLANES_3_H

#include <CGAL/Cartesian/redefine_names_3.h>
#include <CGAL/Cartesian/Point_3.h>
#include <CGAL/constructions/kernel_ftC3.h>

CGAL_BEGIN_NAMESPACE

template <class R>
CGAL_KERNEL_LARGE_INLINE
PlaneC3<R CGAL_CTAG>
plane_from_points(const PointC3<R CGAL_CTAG>& p,
                  const PointC3<R CGAL_CTAG>& q,
		  const PointC3<R CGAL_CTAG>& r)
{
  typename R::FT a,b,c,d;
  plane_from_pointsC3(p.x(),p.y(),p.z(),
                      q.x(),q.y(),q.z(),
                      r.x(),r.y(),r.z(),
                      a,b,c,d);
  return PlaneC3<R CGAL_CTAG>(a,b,c,d);
}

template <class R>
CGAL_KERNEL_LARGE_INLINE
PlaneC3<R CGAL_CTAG>
plane_from_point_direction(const PointC3<R CGAL_CTAG>& p,
                           const DirectionC3<R CGAL_CTAG>& d)
{
  typename R::FT A, B, C, D;
  plane_from_point_directionC3(p.x(),p.y(),p.z(),d.dx(),d.dy(),d.dz(),
                               A,B,C,D);
  return PlaneC3<R CGAL_CTAG>(A,B,C,D);
}

template <class R>
CGAL_KERNEL_LARGE_INLINE
PointC3<R CGAL_CTAG>
point_on_plane(const PlaneC3<R CGAL_CTAG>& p)
{
  typename R::FT x, y, z;
  point_on_planeC3(p.a(),p.b(),p.c(),p.d(),x,y,z);
  return PointC3<R CGAL_CTAG>(x,y,z);
}

template <class R>
CGAL_KERNEL_LARGE_INLINE
PointC3<R CGAL_CTAG>
projection_plane(const PointC3<R CGAL_CTAG>& p,
                 const PlaneC3<R CGAL_CTAG>& h)
{
  typename R::FT x,y,z;
  projection_planeC3(h.a(),h.b(),h.c(),h.d(),
                     p.x(),p.y(),p.z(),
                     x,y,z);
  return PointC3<R CGAL_CTAG>(x,y,z);
}

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_CONSTRUCTIONS_ON_PLANES_3_H
