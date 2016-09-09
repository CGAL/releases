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
// file          : include/CGAL/Cartesian/line_constructions_2.h
// package       : Cartesian_kernel (6.24)
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2000/11/03 13:53:55 $
// author(s)     : Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_LINE_CONSTRUCTIONS_2_H
#define CGAL_CARTESIAN_LINE_CONSTRUCTIONS_2_H

#include <CGAL/Cartesian/Point_2.h>
#include <CGAL/Cartesian/Line_2.h>

CGAL_BEGIN_NAMESPACE

template < class R >
inline
LineC2<R CGAL_CTAG>
line_from_points(const PointC2<R CGAL_CTAG> &p,
                 const PointC2<R CGAL_CTAG> &q)
{
  typename R::FT a, b, c;
  line_from_pointsC2(p.x(), p.y(), q.x(), q.y(), a, b, c);
  return LineC2<R CGAL_CTAG>(a, b, c);
}

template < class R >
inline
LineC2<R CGAL_CTAG>
line_from_point_direction(const PointC2<R CGAL_CTAG> &p,
                          const DirectionC2<R CGAL_CTAG> &d)
{
  typename R::FT a, b, c;
  line_from_point_directionC2(p.x(), p.y(), d.dx(), d.dy(), a, b, c);
  return LineC2<R CGAL_CTAG>(a, b, c);
}

template < class R >
inline
LineC2<R CGAL_CTAG>
bisector(const PointC2<R CGAL_CTAG> &p,
         const PointC2<R CGAL_CTAG> &q)
{
  typename R::FT a, b, c;
  bisector_of_pointsC2(p.x(), p.y(), q.x(), q.y(), a, b, c);
  return LineC2<R CGAL_CTAG>(a, b, c);
}

template < class R >
inline
LineC2<R CGAL_CTAG>
perpendicular_through_point(const LineC2<R CGAL_CTAG> &l,
                            const PointC2<R CGAL_CTAG> &p)
{
  typename R::FT a, b, c;
  perpendicular_through_pointC2(l.a(), l.b(), p.x(), p.y(), a, b, c);
  return LineC2<R CGAL_CTAG>(a, b, c);
}

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_LINE_CONSTRUCTIONS_2_H
