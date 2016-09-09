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
// file          : include/CGAL/Cartesian/ft_constructions_2.h
// package       : Cartesian_kernel (6.59)
// revision      : $Revision: 1.6 $
// revision_date : $Date: 2002/01/23 17:59:13 $
// author(s)     : Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_FT_CONSTRUCTIONS_2_H
#define CGAL_CARTESIAN_FT_CONSTRUCTIONS_2_H

CGAL_BEGIN_NAMESPACE

template < class R >
inline
typename R::FT
squared_distance(const PointC2<R> &p,
                 const PointC2<R> &q)
{
  return squared_distanceC2(p.x(), p.y(), q.x(), q.y());
}

template < class R >
inline
typename R::FT
scaled_distance_to_line(const LineC2<R> &l,
                        const PointC2<R> &p)
{
  return scaled_distance_to_lineC2(l.a(), l.b(), l.c(), p.x(), p.y());
}

template < class R >
inline
typename R::FT
scaled_distance_to_line(const PointC2<R> &p,
                        const PointC2<R> &q,
                        const PointC2<R> &r)
{
  return scaled_distance_to_lineC2(p.x(), p.y(), q.x(), q.y(), r.x(), r.y());
}

template < class R >
inline
typename R::FT
line_y_at_x(const LineC2<R> &l, const typename R::FT &x)
{
  return line_y_at_xC2(l.a(), l.b(), l.c(), x);
}

template < class R >
inline
typename R::FT
line_x_at_y(const LineC2<R> &l, const typename R::FT &y)
{
  return line_y_at_xC2(l.b(), l.a(), l.c(), y);
}

template < class R >
inline
typename R::FT
squared_radius(const PointC2<R> &p,
                     const PointC2<R> &q,
                     const PointC2<R> &r)
{
  return squared_radiusC2(p.x(), p.y(), q.x(), q.y(), r.x(), r.y());
}

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_FT_CONSTRUCTIONS_2_H
