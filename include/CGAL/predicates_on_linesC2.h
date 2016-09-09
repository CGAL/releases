// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/predicates_on_linesC2.h
// package       : C2 (1.7)
// source        : web/predicates_on_linesC2.fw
// revision      : $Revision: 1.10 $
// revision_date : $Date: 1999/01/04 06:54:16 $
// author(s)     : Herve.Bronnimann
//
// coordinator   : INRIA Sophia-Antipolis
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_PREDICATES_ON_LINESC2_H
#define CGAL_PREDICATES_ON_LINESC2_H

#ifndef CGAL_CARTESIAN_CLASSES_H
#include <CGAL/cartesian_classes.h>
#endif // CGAL_CARTESIAN_CLASSES_H
#ifndef CGAL_LINEC2_H
#include <CGAL/LineC2.h>
#endif // CGAL_LINEC2_H
#ifndef CGAL_PREDICATES_ON_POINTSC2_H
#include <CGAL/predicates_on_pointsC2.h>
#endif // CGAL_PREDICATES_ON_POINTSC2_H


template < class FT >
CGAL_Comparison_result CGAL_compare_x(const CGAL_PointC2<FT> &p,
                                      const CGAL_LineC2<FT> &l1,
                                      const CGAL_LineC2<FT> &l2)
{
  return CGAL_compare_xC2(p.x(),p.y(),
                          l1.a(),l1.b(),l1.c(),l2.a(),l2.b(),l2.c());
}


template < class FT >
CGAL_Comparison_result CGAL_compare_x(const CGAL_LineC2<FT> &l1,
                                      const CGAL_LineC2<FT> &l2,
                                      const CGAL_LineC2<FT> &h1,
                                      const CGAL_LineC2<FT> &h2)
{
  return CGAL_compare_xC2(l1.a(),l1.b(),l1.c(),l2.a(),l2.b(),l2.c(),
                          h1.a(),h1.b(),h1.c(),h2.a(),h2.b(),h2.c());
}



template < class FT >
CGAL_Comparison_result CGAL_compare_y(const CGAL_PointC2<FT> &p,
                                      const CGAL_LineC2<FT> &l1,
                                      const CGAL_LineC2<FT> &l2)
{
  return CGAL_compare_xC2(p.y(),p.x(),
                          l1.b(),l1.a(),l1.c(),l2.b(),l2.a(),l2.c());
}


template < class FT >
CGAL_Comparison_result CGAL_compare_y(const CGAL_LineC2<FT> &l1,
                                      const CGAL_LineC2<FT> &l2,
                                      const CGAL_LineC2<FT> &h1,
                                      const CGAL_LineC2<FT> &h2)
{
  return CGAL_compare_xC2(l1.b(),l1.a(),l1.c(),l2.b(),l2.a(),l2.c(),
                          h1.b(),h1.a(),h1.c(),h2.b(),h2.a(),h2.c());
}
template < class FT >
CGAL_Comparison_result CGAL_compare_y_at_x(const CGAL_PointC2<FT> &p,
                                           const CGAL_LineC2<FT> &h)
{
  return CGAL_compare_y_at_xC2(p.x(),p.y(),h.a(),h.b(),h.c());
}


template < class FT >
CGAL_Comparison_result CGAL_compare_y_at_x(const CGAL_PointC2<FT> &p,
                                           const CGAL_LineC2<FT> &h1,
                                           const CGAL_LineC2<FT> &h2)
{
  return CGAL_compare_y_at_xC2(p.x(),
                               h1.a(),h1.b(),h1.c(),h2.a(),h2.b(),h2.c());
}


template < class FT >
CGAL_Comparison_result CGAL_compare_y_at_x(const CGAL_LineC2<FT> &l1,
                                           const CGAL_LineC2<FT> &l2,
                                           const CGAL_LineC2<FT> &h)
{
  return CGAL_compare_y_at_xC2(l1.a(),l1.b(),l1.c(),l2.a(),l2.b(),l2.c(),
                               h.a(),h.b(),h.c());
}


template < class FT >
CGAL_Comparison_result CGAL_compare_y_at_x(const CGAL_LineC2<FT> &l1,
                                           const CGAL_LineC2<FT> &l2,
                                           const CGAL_LineC2<FT> &h1,
                                           const CGAL_LineC2<FT> &h2)
{
  return CGAL_compare_y_at_xC2(l1.a(),l1.b(),l1.c(),l2.a(),l2.b(),l2.c(),
                               h1.a(),h1.b(),h1.c(),h2.a(),h2.b(),h2.c());
}


#endif  // CGAL_PREDICATES_ON_LINESC2_H
