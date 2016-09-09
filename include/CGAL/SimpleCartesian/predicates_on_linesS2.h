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
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// source        : webS2/S2.lw
// file          : include/CGAL/SimpleCartesian/predicates_on_linesS2.h
// package       : S2 (1.7)
// revision      : 1.6
// revision_date : 27 Jun 2000
// author(s)     : Stefan Schirra
//                 based on code by
//                 Andreas Fabri and
//                 Herve Brönnimann
//
// coordinator   : MPI, Saarbrücken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================


#ifndef CGAL_PREDICATES_ON_LINESS2_H
#define CGAL_PREDICATES_ON_LINESS2_H

#include <CGAL/SimpleCartesian/simple_cartesian_classes.h>
#include <CGAL/SimpleCartesian/LineS2.h>
#include <CGAL/SimpleCartesian/predicates_on_pointsS2.h>

CGAL_BEGIN_NAMESPACE


template < class FT >
Comparison_result compare_x(const PointS2<FT> &p,
                            const LineS2<FT> &l1,
                            const LineS2<FT> &l2)
{
  return compare_xC2(p.x(), l1.a(),l1.b(),l1.c(),l2.a(),l2.b(),l2.c());
}


template < class FT >
Comparison_result compare_x(const LineS2<FT> &l1,
                            const LineS2<FT> &l2,
                            const LineS2<FT> &h1,
                            const LineS2<FT> &h2)
{
  return compare_xC2(l1.a(),l1.b(),l1.c(),l2.a(),l2.b(),l2.c(),
                     h1.a(),h1.b(),h1.c(),h2.a(),h2.b(),h2.c());
}



template < class FT >
Comparison_result compare_y(const PointS2<FT> &p,
                            const LineS2<FT> &l1,
                            const LineS2<FT> &l2)
{
  return compare_xC2(p.y(), l1.b(),l1.a(),l1.c(),l2.b(),l2.a(),l2.c());
}


template < class FT >
Comparison_result compare_y(const LineS2<FT> &l1,
                            const LineS2<FT> &l2,
                            const LineS2<FT> &h1,
                            const LineS2<FT> &h2)
{
  return compare_xC2(l1.b(),l1.a(),l1.c(),l2.b(),l2.a(),l2.c(),
                     h1.b(),h1.a(),h1.c(),h2.b(),h2.a(),h2.c());
}
template < class FT >
Comparison_result compare_y_at_x(const PointS2<FT> &p, const LineS2<FT> &h)
{
  return compare_y_at_xC2(p.x(),p.y(),h.a(),h.b(),h.c());
}


template < class FT >
Comparison_result compare_y_at_x(const PointS2<FT> &p,
                                 const LineS2<FT> &h1,
                                 const LineS2<FT> &h2)
{
  return compare_y_at_xC2(p.x(), h1.a(),h1.b(),h1.c(),h2.a(),h2.b(),h2.c());
}


template < class FT >
Comparison_result compare_y_at_x(const LineS2<FT> &l1,
                                 const LineS2<FT> &l2,
                                 const LineS2<FT> &h)
{
  return compare_y_at_xC2(l1.a(),l1.b(),l1.c(),l2.a(),l2.b(),l2.c(),
                          h.a(),h.b(),h.c());
}


template < class FT >
Comparison_result compare_y_at_x(const LineS2<FT> &l1,
                                 const LineS2<FT> &l2,
                                 const LineS2<FT> &h1,
                                 const LineS2<FT> &h2)
{
  return compare_y_at_xC2(l1.a(),l1.b(),l1.c(),l2.a(),l2.b(),l2.c(),
                          h1.a(),h1.b(),h1.c(),h2.a(),h2.b(),h2.c());
}


CGAL_END_NAMESPACE

#endif  // CGAL_PREDICATES_ON_LINESS2_H
