// ============================================================================
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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/predicates_on_linesC2.h
// author(s)     : Andreas Fabri
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


#ifndef CGAL_PREDICATES_ON_LINESC2_H
#define CGAL_PREDICATES_ON_LINESC2_H
#include <CGAL/cartesian_classes.h>
#include <CGAL/LineC2.h>
#include <CGAL/predicates_on_pointsC2.h>


template < class FT >
CGAL_Comparison_result CGAL_compare_x(const CGAL_PointC2<FT> &p,
                                      const CGAL_LineC2<FT> &l1,
                                      const CGAL_LineC2<FT> &l2)
{
  const FT &px = p.x();
  const FT &l1a = l1.a();
  const FT &l2a = l2.a();

  const FT &l1b = l1.b();
  const FT &l2b = l2.b();

  const FT &l1c = l1.c();
  const FT &l2c = l2.c();

  int sign1 = CGAL_sign(CGAL_det2x2_by_formula(l1a, l1b, l2a, l2b));
  int sign2 = CGAL_sign(CGAL_det3x3_by_formula(l1a, l1b, l1c,
                                               l2a, l2b, l2c,
                                               -FT(1), FT(0), px));
  CGAL_kernel_assertion( sign1 != 0 );

  if (sign2 == 0){
    return CGAL_EQUAL;
  }

  return (sign1 == sign2) ? CGAL_LARGER : CGAL_SMALLER;
}


template < class FT >
CGAL_Comparison_result CGAL_compare_x(const CGAL_LineC2<FT> &l1,
                                      const CGAL_LineC2<FT> &l2,
                                      const CGAL_LineC2<FT> &h1,
                                      const CGAL_LineC2<FT> &h2)
{
  const FT &a = l1.a();
  const FT &b = l1.b();
  const FT &c = l1.c();

  const FT &d = l2.a();
  const FT &e = l2.b();
  const FT &f = l2.c();

  const FT &g = h1.a();
  const FT &h = h1.b();
  const FT &i = h1.c();

  const FT &j = h2.a();
  const FT &k = h2.b();
  const FT &l = h2.c();

  int sign1 = CGAL_sign(CGAL_det2x2_by_formula(a,b,d,e));
  int sign2 = CGAL_sign(CGAL_det2x2_by_formula(g,h,j,k));
  int sign3 = CGAL_sign(CGAL_det4x4_by_formula(a, b, FT(0), c,
                                               d, e, FT(0), f,
                                               g, FT(0), h, i,
                                               j, FT(0), k, l));

  CGAL_kernel_precondition( (! (sign1 == 0)) && (! (sign2 == 0)) );

  if(sign3 == 0){
    return CGAL_EQUAL;
  }
  if(sign3 < 0){
    return (sign1 == sign2) ? CGAL_LARGER : CGAL_SMALLER;
  }
  return (sign1 != sign2) ? CGAL_LARGER : CGAL_SMALLER;
}



template < class FT >
CGAL_Comparison_result CGAL_compare_y(const CGAL_PointC2<FT> &p,
                                      const CGAL_LineC2<FT> &l1,
                                      const CGAL_LineC2<FT> &l2)
{
  const FT &py = p.y();
  const FT &l1a = l1.a();
  const FT &l2a = l2.a();

  const FT &l1b = l1.b();
  const FT &l2b = l2.b();

  const FT &l1c = l1.c();
  const FT &l2c = l2.c();

  int sign1 = CGAL_sign(CGAL_det2x2_by_formula(l1a, l1b, l2a, l2b));
  int sign2 = CGAL_sign(CGAL_det3x3_by_formula(l1a, l1b, l1c,
                                               l2a, l2b, l2c,
                                               FT(0), -FT(1), py));
  CGAL_kernel_assertion( sign1 != 0 );

  if (sign2 == 0){
    return CGAL_EQUAL;
  }

  return (sign1 == sign2) ? CGAL_LARGER : CGAL_SMALLER;
}


template < class FT >
CGAL_Comparison_result CGAL_compare_y(const CGAL_LineC2<FT> &l1,
                                      const CGAL_LineC2<FT> &l2,
                                      const CGAL_LineC2<FT> &h1,
                                      const CGAL_LineC2<FT> &h2)
{
  const FT &a = l1.a();
  const FT &b = l1.b();
  const FT &c = l1.c();

  const FT &d = l2.a();
  const FT &e = l2.b();
  const FT &f = l2.c();

  const FT &g = h1.a();
  const FT &h = h1.b();
  const FT &i = h1.c();

  const FT &j = h2.a();
  const FT &k = h2.b();
  const FT &l = h2.c();

  FT y1 = CGAL_det2x2_by_formula(a,-c,d,-f) /
            CGAL_det2x2_by_formula(a,b,d,e);

  FT y2 = CGAL_det2x2_by_formula(g,-i,j,-l) /
            CGAL_det2x2_by_formula(g,h,j,k);


  if (y1 == y2){
    return CGAL_EQUAL;
  }

  return (y1 < y2) ? CGAL_SMALLER : CGAL_LARGER;
}
template < class FT >
CGAL_Comparison_result CGAL_compare_y_at_x(const CGAL_PointC2<FT> &p,
                                           const CGAL_LineC2<FT> &h)
{
  CGAL_kernel_precondition( ! h.is_vertical() );
  const FT &py = p.y();
  FT y = h.y_at_x(p.x());

  return CGAL_compare(py,y);
}


template < class FT >
CGAL_Comparison_result CGAL_compare_y_at_x(const CGAL_PointC2<FT> &p,
                                           const CGAL_LineC2<FT> &h1,
                                           const CGAL_LineC2<FT> &h2)
{
  const FT &x = p.x();
  return CGAL_compare(h1.y_at_x(x), h2.y_at_x(x));
}


template < class FT >
CGAL_Comparison_result CGAL_compare_y_at_x(const CGAL_LineC2<FT> &l1,
                                           const CGAL_LineC2<FT> &l2,
                                           const CGAL_LineC2<FT> &h)
{
  return CGAL_compare_y_at_x( l1, l2, l1, h );
}


template < class FT >
CGAL_Comparison_result CGAL_compare_y_at_x(const CGAL_LineC2<FT> &l1,
                                           const CGAL_LineC2<FT> &l2,
                                           const CGAL_LineC2<FT> &h1,
                                           const CGAL_LineC2<FT> &h2)
{
  const FT &a = l1.a();
  const FT &b = l1.b();
  const FT &c = l1.c();

  const FT &d = l2.a();
  const FT &e = l2.b();
  const FT &f = l2.c();

  const FT &g = h1.a();
  const FT &h = h1.b();
  const FT &i = h1.c();

  const FT &j = h2.a();
  const FT &k = h2.b();
  const FT &l = h2.c();

  int s = CGAL_lexicographical_sign(h,-g)
            * CGAL_lexicographical_sign(k,-j)
            * CGAL_sign(CGAL_det2x2_by_formula(a, b, d, e))
            * CGAL_sign(CGAL_det4x4_by_formula(j, k,     FT(0), l,
                                               a, FT(0), b,     c,
                                               d, FT(0), e,     f,
                                               g, h,     FT(0), i));

  return CGAL_compare(s,0);
}


#endif  // CGAL_PREDICATES_ON_LINESC2_H
