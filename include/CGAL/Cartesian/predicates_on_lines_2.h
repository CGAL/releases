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
// file          : include/CGAL/Cartesian/predicates_on_lines_2.h
// package       : Cartesian_kernel (6.59)
// revision      : $Revision: 1.7 $
// revision_date : $Date: 2002/01/23 17:59:15 $
// author(s)     : Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_PREDICATES_ON_LINES_2_H
#define CGAL_CARTESIAN_PREDICATES_ON_LINES_2_H

#include <CGAL/Cartesian/Point_2.h>
#include <CGAL/Cartesian/Line_2.h>
#include <CGAL/predicates/kernel_ftC2.h>

CGAL_BEGIN_NAMESPACE

template < class R >
inline
bool
equal_line(const LineC2<R> &l1, const LineC2<R> &l2)
{
  return equal_lineC2(l1.a(), l1.b(), l1.c(), l2.a(), l2.b(), l2.c());
}

template < class R >
inline
Comparison_result
compare_x(const PointC2<R> &p,
          const LineC2<R> &l,
          const LineC2<R> &h)
{
  return compare_xC2(p.x(), l.a(), l.b(), l.c(), h.a(), h.b(), h.c());
}

template < class R >
inline
Comparison_result
compare_x(const LineC2<R> &l,
          const LineC2<R> &h1,
          const LineC2<R> &h2)
{
  return compare_xC2(l.a(), l.b(), l.c(), h1.a(), h1.b(), h1.c(),
                                          h2.a(), h2.b(), h2.c());
}

template < class R >
inline
Comparison_result
compare_x(const LineC2<R> &l1,
          const LineC2<R> &h1,
          const LineC2<R> &l2,
          const LineC2<R> &h2)
{
  return compare_xC2(l1.a(), l1.b(), l1.c(), h1.a(), h1.b(), h1.c(),
                     l2.a(), l2.b(), l2.c(), h2.a(), h2.b(), h2.c());
}

template < class R >
inline
Comparison_result
compare_y(const PointC2<R> &p,
          const LineC2<R> &l1,
          const LineC2<R> &l2)
{
  return compare_xC2(p.y(), l1.b(), l1.a(), l1.c(), l2.b(), l2.a(), l2.c());
}

template < class R >
inline
Comparison_result
compare_y(const LineC2<R> &l1,
          const LineC2<R> &l2,
          const LineC2<R> &h1,
          const LineC2<R> &h2)
{
  return compare_xC2(l1.b(), l1.a(), l1.c(), l2.b(), l2.a(), l2.c(),
                     h1.b(), h1.a(), h1.c(), h2.b(), h2.a(), h2.c());
}

template < class R >
inline
Comparison_result
compare_y(const LineC2<R> &l,
          const LineC2<R> &h1,
          const LineC2<R> &h2)
{
  return compare_xC2(l.b(), l.a(), l.c(), h1.b(), h1.a(), h1.c(),
                     l.b(), l.a(), l.c(), h2.b(), h2.a(), h2.c());
}

template < class R >
inline
Comparison_result
compare_y_at_x(const PointC2<R> &p, const LineC2<R> &h)
{
  return compare_y_at_xC2(p.x(), p.y(), h.a(), h.b(), h.c());
}

template < class R >
inline
Comparison_result
compare_y_at_x(const PointC2<R> &p,
               const LineC2<R> &h1,
               const LineC2<R> &h2)
{
  return compare_y_at_xC2(p.x(), h1.a(), h1.b(), h1.c(),
	                         h2.a(), h2.b(), h2.c());
}

template < class R >
inline
Comparison_result
compare_y_at_x(const LineC2<R> &l1,
               const LineC2<R> &l2,
               const LineC2<R> &h)
{
  return compare_y_at_xC2(l1.a(), l1.b(), l1.c(), l2.a(), l2.b(), l2.c(),
                          h.a(), h.b(), h.c());
}

template < class R >
inline
Comparison_result
compare_y_at_x(const LineC2<R> &l1,
               const LineC2<R> &l2,
               const LineC2<R> &h1,
               const LineC2<R> &h2)
{
  return compare_y_at_xC2(l1.a(), l1.b(), l1.c(), l2.a(), l2.b(), l2.c(),
                          h1.a(), h1.b(), h1.c(), h2.a(), h2.b(), h2.c());
}

template < class R >
inline
Comparison_result
compare_x_at_y(const PointC2<R> &p, const LineC2<R> &h)
{
  return compare_y_at_xC2(p.y(), p.x(), h.b(), h.a(), h.c());
}

template < class R >
inline
Comparison_result
compare_x_at_y(const PointC2<R> &p,
               const LineC2<R> &h1,
               const LineC2<R> &h2)
{
  return compare_y_at_xC2(p.y(), h1.b(), h1.a(), h1.c(),
	                         h2.b(), h2.a(), h2.c());
}

template < class R >
inline
Comparison_result
compare_x_at_y(const LineC2<R> &l1,
               const LineC2<R> &l2,
               const LineC2<R> &h)
{
  return compare_y_at_xC2(l1.b(), l1.a(), l1.c(), l2.b(), l2.a(), l2.c(),
                          h.b(), h.a(), h.c());
}

template < class R >
inline
Comparison_result
compare_x_at_y(const LineC2<R> &l1,
               const LineC2<R> &l2,
               const LineC2<R> &h1,
               const LineC2<R> &h2)
{
  return compare_y_at_xC2(l1.b(), l1.a(), l1.c(), l2.b(), l2.a(), l2.c(),
                          h1.b(), h1.a(), h1.c(), h2.b(), h2.a(), h2.c());
}

template < class R >
Comparison_result
compare_slopes(const LineC2<R> &l1,
               const LineC2<R> &l2)
{
   return compare_slopesC2(l1.a(), l1.b(), l2.a(), l2.b());
}

template < class R >
inline
Oriented_side
side_of_oriented_line(const LineC2<R> &l,
                      const PointC2<R> &p)
{
  return side_of_oriented_lineC2(l.a(), l.b(), l.c(), p.x(), p.y());
}

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_PREDICATES_ON_LINES_2_H
