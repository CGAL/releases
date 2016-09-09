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
// file          : include/CGAL/Cartesian/ft_constructions_2.h
// package       : Cartesian_kernel (6.24)
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2001/03/20 12:08:55 $
// author(s)     : Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_FT_CONSTRUCTIONS_2_H
#define CGAL_CARTESIAN_FT_CONSTRUCTIONS_2_H

#include <CGAL/Cartesian/redefine_names_2.h>

CGAL_BEGIN_NAMESPACE

template < class R >
inline
typename R::FT
squared_distance(const PointC2<R CGAL_CTAG> &p,
                 const PointC2<R CGAL_CTAG> &q)
{
  return squared_distanceC2(p.x(), p.y(), q.x(), q.y());
}

template < class R >
inline
typename R::FT
scaled_distance_to_line(const LineC2<R CGAL_CTAG> &l,
                        const PointC2<R CGAL_CTAG> &p)
{
  return scaled_distance_to_lineC2(l.a(), l.b(), l.c(), p.x(), p.y());
}

template < class R >
inline
typename R::FT
scaled_distance_to_line(const PointC2<R CGAL_CTAG> &p,
                        const PointC2<R CGAL_CTAG> &q,
                        const PointC2<R CGAL_CTAG> &r)
{
  return scaled_distance_to_lineC2(p.x(), p.y(), q.x(), q.y(), r.x(), r.y());
}

template < class R >
inline
typename R::FT
line_y_at_x(const LineC2<R CGAL_CTAG> &l, const typename R::FT &x)
{
  return line_y_at_xC2(l.a(), l.b(), l.c(), x);
}

template < class R >
inline
typename R::FT
line_x_at_y(const LineC2<R CGAL_CTAG> &l, const typename R::FT &y)
{
  return line_y_at_xC2(l.b(), l.a(), l.c(), y);
}

template < class R >
inline
typename R::FT
squared_radius(const PointC2<R CGAL_CTAG> &p,
                     const PointC2<R CGAL_CTAG> &q,
                     const PointC2<R CGAL_CTAG> &r)
{
  return squared_radiusC2(p.x(), p.y(), q.x(), q.y(), r.x(), r.y());
}

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_FT_CONSTRUCTIONS_2_H
