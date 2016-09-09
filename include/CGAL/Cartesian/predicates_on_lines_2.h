// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : include/CGAL/Cartesian/predicates_on_lines_2.h
// package       : C2 (3.3.11)
// revision      : $Revision: 1.8 $
// revision_date : $Date: 1999/12/10 16:19:45 $
// author(s)     : Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_CARTESIAN_PREDICATES_ON_LINES_2_H
#define CGAL_CARTESIAN_PREDICATES_ON_LINES_2_H

#include <CGAL/Cartesian/redefine_names_2.h>

#include <CGAL/cartesian_classes.h>
#include <CGAL/Cartesian/Point_2.h>
#include <CGAL/Cartesian/Line_2.h>

#include <CGAL/predicates/kernel_ftC2.h>

CGAL_BEGIN_NAMESPACE

template < class R >
inline
bool
equal_line(const LineC2<R CGAL_CTAG> &l1, const LineC2<R CGAL_CTAG> &l2)
{
  return equal_lineC2(l1.a(),l1.b(),l1.c(),l2.a(),l2.b(),l2.c());
}

template < class R >
inline
Comparison_result
compare_x(const PointC2<R CGAL_CTAG> &p,
          const LineC2<R CGAL_CTAG> &l,
          const LineC2<R CGAL_CTAG> &h)
{
  return compare_xC2(p.x(), l.a(),l.b(),l.c(),h.a(),h.b(),h.c());
}

template < class R >
inline
Comparison_result
compare_x(const LineC2<R CGAL_CTAG> &l,
          const LineC2<R CGAL_CTAG> &h1,
          const LineC2<R CGAL_CTAG> &h2)
{
  return compare_xC2(l.a(),l.b(),l.c(),h1.a(),h1.b(),h1.c(),
                                       h2.a(),h2.b(),h2.c());
}

template < class R >
inline
Comparison_result
compare_x(const LineC2<R CGAL_CTAG> &l1,
          const LineC2<R CGAL_CTAG> &h1,
          const LineC2<R CGAL_CTAG> &l2,
          const LineC2<R CGAL_CTAG> &h2)
{
  return compare_xC2(l1.a(),l1.b(),l1.c(),h1.a(),h1.b(),h1.c(),
                     l2.a(),l2.b(),l2.c(),h2.a(),h2.b(),h2.c());
}

template < class R >
inline
Comparison_result
compare_y(const PointC2<R CGAL_CTAG> &p,
          const LineC2<R CGAL_CTAG> &l1,
          const LineC2<R CGAL_CTAG> &l2)
{
  return compare_xC2(p.y(), l1.b(),l1.a(),l1.c(),l2.b(),l2.a(),l2.c());
}

template < class R >
inline
Comparison_result
compare_y(const LineC2<R CGAL_CTAG> &l1,
          const LineC2<R CGAL_CTAG> &l2,
          const LineC2<R CGAL_CTAG> &h1,
          const LineC2<R CGAL_CTAG> &h2)
{
  return compare_xC2(l1.b(),l1.a(),l1.c(),l2.b(),l2.a(),l2.c(),
                     h1.b(),h1.a(),h1.c(),h2.b(),h2.a(),h2.c());
}

template < class R >
inline
Comparison_result
compare_y(const LineC2<R CGAL_CTAG> &l,
          const LineC2<R CGAL_CTAG> &h1,
          const LineC2<R CGAL_CTAG> &h2)
{
  return compare_xC2(l.b(),l.a(),l.c(),h1.b(),h1.a(),h1.c(),
                     l.b(),l.a(),l.c(),h2.b(),h2.a(),h2.c());
}

template < class R >
inline
Comparison_result
compare_y_at_x(const PointC2<R CGAL_CTAG> &p, const LineC2<R CGAL_CTAG> &h)
{
  return compare_y_at_xC2(p.x(),p.y(),h.a(),h.b(),h.c());
}

template < class R >
inline
Comparison_result
compare_y_at_x(const PointC2<R CGAL_CTAG> &p,
               const LineC2<R CGAL_CTAG> &h1,
               const LineC2<R CGAL_CTAG> &h2)
{
  return compare_y_at_xC2(p.x(), h1.a(),h1.b(),h1.c(),h2.a(),h2.b(),h2.c());
}

template < class R >
inline
Comparison_result
compare_y_at_x(const LineC2<R CGAL_CTAG> &l1,
               const LineC2<R CGAL_CTAG> &l2,
               const LineC2<R CGAL_CTAG> &h)
{
  return compare_y_at_xC2(l1.a(),l1.b(),l1.c(),l2.a(),l2.b(),l2.c(),
                          h.a(),h.b(),h.c());
}

template < class R >
inline
Comparison_result
compare_y_at_x(const LineC2<R CGAL_CTAG> &l1,
               const LineC2<R CGAL_CTAG> &l2,
               const LineC2<R CGAL_CTAG> &h1,
               const LineC2<R CGAL_CTAG> &h2)
{
  return compare_y_at_xC2(l1.a(),l1.b(),l1.c(),l2.a(),l2.b(),l2.c(),
                          h1.a(),h1.b(),h1.c(),h2.a(),h2.b(),h2.c());
}

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_PREDICATES_ON_LINES_2_H
