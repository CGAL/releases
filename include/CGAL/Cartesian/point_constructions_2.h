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
// file          : include/CGAL/Cartesian/point_constructions_2.h
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

#ifndef CGAL_CARTESIAN_POINT_CONSTRUCTIONS_2_H
#define CGAL_CARTESIAN_POINT_CONSTRUCTIONS_2_H

#include <CGAL/Cartesian/Point_2.h>

CGAL_BEGIN_NAMESPACE

template < class R >
inline
PointC2<R>
midpoint(const PointC2<R> &p,
         const PointC2<R> &q )
{
  typename R::FT x, y;
  midpointC2(p.x(), p.y(), q.x(), q.y(), x, y);
  return PointC2<R>(x, y);
}

template < class R >
inline
PointC2<R>
circumcenter(const PointC2<R> &p,
             const PointC2<R> &q,
             const PointC2<R> &r)
{
  typename R::FT x, y;
  circumcenterC2(p.x(), p.y(), q.x(), q.y(), r.x(), r.y(), x, y);
  return PointC2<R>(x, y);
}

template < class R >
inline
PointC2<R>
centroid(const PointC2<R> &p,
         const PointC2<R> &q,
         const PointC2<R> &r)
{
  typename R::FT x, y;
  centroidC2(p.x(), p.y(), q.x(), q.y(), r.x(), r.y(), x, y);
  return PointC2<R>(x, y);
}

template < class R >
inline
PointC2<R>
centroid(const PointC2<R> &p,
         const PointC2<R> &q,
         const PointC2<R> &r,
         const PointC2<R> &s)
{
  typename R::FT x, y;
  centroidC2(p.x(), p.y(), q.x(), q.y(), r.x(), r.y(), s.x(), s.y(), x, y);
  return PointC2<R>(x, y);
}

template < class R >
inline
PointC2<R>
line_get_point(const LineC2<R> &l, int i)
{
  typename R::FT x, y;
  line_get_pointC2(l.a(), l.b(), l.c(), i, x, y);
  return PointC2<R>(x, y);
}

template < class R >
inline
PointC2<R>
line_project_point(const LineC2<R> &l,
                   const PointC2<R> &p)
{
  typename R::FT x, y;
  line_project_pointC2(l.a(), l.b(), l.c(), p.x(), p.y(), x, y);
  return PointC2<R>(x, y);
}

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_POINT_CONSTRUCTIONS_2_H
