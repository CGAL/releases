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
// file          : include/CGAL/predicates_on_ftC2.h
// package       : C2 (1.7)
// source        : web/predicates_on_ftC2.fw
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


#ifndef CGAL_PREDICATES_ON_FTC2_H
#define CGAL_PREDICATES_ON_FTC2_H

#ifndef CGAL_DETERMINANT_H
#include <CGAL/determinant.h>
#endif // CGAL_DETERMINANT_H

#ifndef CGAL_BASIC_CONSTRUCTIONS_FTC2_H
#include <CGAL/basic_constructions_ftC2.h>
#endif

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
CGAL_Comparison_result
CGAL_compare_xC2(const FT &px,const FT &py,
                 const FT &l1a, const FT &l1b, const FT &l1c,
                 const FT &l2a, const FT &l2b, const FT &l2c)
{
  const CGAL_Sign sign1 = CGAL_sign(CGAL_det2x2_by_formula(l1a, l1b, l2a, l2b));
  const CGAL_Sign sign2 = CGAL_sign(CGAL_det3x3_by_formula(l1a, l1b, l1c,
                                                     l2a, l2b, l2c,
                                                     -FT(1), FT(0), px));
  CGAL_kernel_assertion( sign1 != 0 );
  return CGAL_Comparison_result (sign1 * sign2);
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
CGAL_Comparison_result
CGAL_compare_xC2(const FT &l1a, const FT &l1b, const FT &l1c,
                 const FT &l2a, const FT &l2b, const FT &l2c,
                 const FT &h1a, const FT &h1b, const FT &h1c,
                 const FT &h2a, const FT &h2b, const FT &h2c)
{
  FT FT0(0);
  const CGAL_Sign sign1 = CGAL_sign(CGAL_det2x2_by_formula(l1a, l1b, l2a, l2b));
  const CGAL_Sign sign2 = CGAL_sign(CGAL_det2x2_by_formula(h1a, h1b, h2a, h2b));
  const CGAL_Sign sign3 = CGAL_sign(CGAL_det4x4_by_formula(l1a, l1b, FT0, l1c,
                                                     l2a, l2b, FT0, l2c,
                                                     h1a, FT0, h1b, h1c,
                                                     h2a, FT0, h2b, h2c));
  CGAL_kernel_assertion( (sign1 != 0) && (sign2 != 0) );
  return CGAL_Comparison_result (- sign1 * sign2 * sign3);
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
CGAL_Comparison_result
CGAL_compare_y_at_xC2(const FT &px, const FT &py,
                      const FT &la, const FT &lb, const FT &lc)
{
  const CGAL_Sign sign1 = CGAL_sign(lb);
  const CGAL_Sign sign2 = CGAL_sign(la*px + lb*py + lc);
  CGAL_kernel_assertion( sign1 != 0 );
  return CGAL_Comparison_result (sign1 * sign2);
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
CGAL_Comparison_result
CGAL_compare_y_at_xC2(const FT &px,
                      const FT &l1a, const FT &l1b, const FT &l1c,
                      const FT &l2a, const FT &l2b, const FT &l2c)
{
  const CGAL_Sign sign1 = CGAL_sign(l1b);
  const CGAL_Sign sign2 = CGAL_sign(l2b);
  const CGAL_Sign sign3 = CGAL_sign(
          CGAL_det2x2_by_formula(la1*px+l1c,l2a*px+l2c,l1b,l2b));
  CGAL_kernel_assertion( (sign1 != 0) && (sign2 != 0) );
  return CGAL_Comparison_result (- sign1 * sign2 * sign3);
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
CGAL_Comparison_result
CGAL_compare_y_at_xC2(const FT &l1a, const FT &l1b, const FT &l1c,
                      const FT &l2a, const FT &l2b, const FT &l2c,
                      const FT &ha,  const FT &hb,  const FT &hc)
{
  const FT d0 = CGAL_det2x2_by_formula(l1a,l1b,l2a,l2b);
  const FT d1 = CGAL_det2x2_by_formula(l1b,l1c,l2b,l2c);
  const FT d2 = CGAL_det2x2_by_formula(l1c,l1a,l2c,l2a);
  CGAL_kernel_assertion( (d0 != FT(0)) && (hb != FT(0)) );
  return CGAL_Comparison_result (CGAL_sign(d0) * CGAL_sign(hb)
                                 * CGAL_sign(ha*d1+hb*d2+hc*d0));
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
CGAL_Comparison_result
CGAL_compare_y_at_xC2(const FT &l1a, const FT &l1b, const FT &l1c,
                      const FT &l2a, const FT &l2b, const FT &l2c,
                      const FT &h1a, const FT &h1b, const FT &h1c,
                      const FT &h2a, const FT &h2b, const FT &h2c)
{
  const FT FT0(0);
  const CGAL_Sign s1 = CGAL_lexicographical_sign(h1b, -h1a);
  const CGAL_Sign s2 = CGAL_lexicographical_sign(h2b, -h2a);
  const CGAL_Sign s3 = CGAL_sign(CGAL_det2x2_by_formula(l1a, l1b, l2a, l2b));
  const CGAL_Sign s4 = CGAL_sign(CGAL_det4x4_by_formula(h2a, h2b, FT0, h2c,
                                                  l1a, FT0, l1b, l1c,
                                                  l2a, FT0, l2b, l2c,
                                                  h1a, h1b, FT0, h1c));
  return CGAL_Comparison_result (s1 * s2 * s3 * s4);
}

template < class FT >
inline
CGAL_Comparison_result
CGAL_compare_deltax_deltayC2(const FT &px, const FT &qx,
                             const FT &ry, const FT &sy)
{
    return CGAL_compare(CGAL_abs(px-qx), CGAL_abs(ry-sy));
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
CGAL_Comparison_result
inline
CGAL_compare_lexicographically_xyC2(const FT &px, const FT &py,
                                    const FT &qx, const FT &qy)
{
  if (px < qx) return CGAL_SMALLER;
  if (qx < px) return CGAL_LARGER;
  if (py < qy) return CGAL_SMALLER;
  if (qy < py) return CGAL_LARGER;
  return CGAL_EQUAL;
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
CGAL_Orientation
CGAL_orientationC2(const FT &px, const FT &py,
                   const FT &qx, const FT &qy,
                   const FT &rx, const FT &ry)
{
  return CGAL_sign(CGAL_det2x2_by_formula(px-rx,py-ry,qx-rx,qy-ry));
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
bool
CGAL_collinear_are_ordered_along_lineC2(const FT &px, const FT &py,
                                        const FT &qx, const FT &qy,
                                        const FT &rx, const FT &ry)
{
  CGAL_kernel_exactness_precondition( CGAL_collinear(p, q, r) );
  if (px < qx) return !(rx < qx);
  if (qx < px) return !(qx < rx);
  if (py < qy) return !(ry < qy);
  if (qy < py) return !(qy < ry);
  return true; // p===q
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
bool
CGAL_collinear_are_strictly_ordered_along_lineC2(const FT &px, const FT &py,
                                                 const FT &qx, const FT &qy,
                                                 const FT &rx, const FT &ry)
{
  CGAL_kernel_exactness_precondition( CGAL_collinear(p, q, r) );
  if (px < qx) return (qx < rx);
  if (qx < px) return (rx < qx);
  if (py < qy) return (qy < ry);
  if (qy < py) return (ry < qy);
  return false;
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
CGAL_Oriented_side
CGAL_side_of_oriented_circleC2(const FT &px, const FT &py,
                               const FT &qx, const FT &qy,
                               const FT &rx, const FT &ry,
                               const FT &tx, const FT &ty)
{
  // const FT FT1(1);
  // return CGAL_Oriented_side(CGAL_sign(
  //       CGAL_det4x4_by_formula(px, py, px*px + py*py, FT1,
  //                              qx, qy, qx*qx + qy*qy, FT1,
  //                              rx, ry, rx*rx + ry*ry, FT1,
  //                              tx, ty, tx*tx + ty*ty, FT1)));
  // Optimized expression:
  // leads to slightly smaller code with -O even though det4x4 is inlined
  // and the multiplications with FT1 are optimized away
  const FT ptx = px-tx;
  const FT pty = py-ty;
  const FT ptz =(px+tx)*ptx + (py+ty)*pty;
  const FT qtx = qx-tx;
  const FT qty = qy-ty;
  const FT qtz =(qx+tx)*qtx + (qy+ty)*qty;
  const FT rtx = rx-tx;
  const FT rty = ry-ty;
  const FT rtz =(rx+tx)*rtx + (ry+ty)*rty;
  return CGAL_Oriented_side(CGAL_sign(
           CGAL_det3x3_by_formula(ptx,pty,ptz,qtx,qty,qtz,rtx,rty,rtz)));
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
CGAL_Bounded_side
CGAL_side_of_bounded_circleC2(const FT &px, const FT &py,
                              const FT &qx, const FT &qy,
                              const FT &rx, const FT &ry,
                              const FT &tx, const FT &ty)
{
  const CGAL_Oriented_side s =
          CGAL_side_of_oriented_circleC2(px,py,qx,qy,rx,ry,tx,ty);
  const CGAL_Orientation o = CGAL_orientationC2(px,py,qx,qy,rx,ry);

  return CGAL_Bounded_side (- s * o);
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
CGAL_Comparison_result
CGAL_cmp_dist_to_pointC2(const FT &px, const FT &py,
                         const FT &qx, const FT &qy,
                         const FT &rx, const FT &ry)
{
  return CGAL_compare(CGAL_squared_distanceC2(px,py,qx,qy),
                      CGAL_squared_distanceC2(px,py,rx,ry));
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
bool
CGAL_has_larger_dist_to_pointC2(const FT &px, const FT &py,
                                const FT &qx, const FT &qy,
                                const FT &rx, const FT &ry)
{
  return CGAL_squared_distanceC2(px,py,rx,ry)
       < CGAL_squared_distanceC2(px,py,qx,qy);
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
bool
CGAL_has_smaller_dist_to_pointC2(const FT &px, const FT &py,
                                 const FT &qx, const FT &qy,
                                 const FT &rx, const FT &ry)
{
  return CGAL_squared_distanceC2(px,py,qx,qy)
       < CGAL_squared_distanceC2(px,py,rx,ry);
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
CGAL_Comparison_result
CGAL_cmp_signed_dist_to_lineC2(const FT &la, const FT &lb, const FT &lc,
                               const FT &px, const FT &py,
                               const FT &qx, const FT &qy)
{
  return CGAL_compare( CGAL_scaled_distance_to_lineC2(la,lb,lc,px,py),
                       CGAL_scaled_distance_to_lineC2(la,lb,lc,qx,qy));
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
bool
CGAL_has_larger_signed_dist_to_lineC2(const FT &la, const FT &lb, const FT &lc,
                                      const FT &px, const FT &py,
                                      const FT &qx, const FT &qy)
{
  return CGAL_scaled_distance_to_lineC2(la,lb,lc,qx,qy)
       < CGAL_scaled_distance_to_lineC2(la,lb,lc,px,py);
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
bool
CGAL_has_smaller_signed_dist_to_lineC2(const FT &la, const FT &lb, const FT &lc,
                                       const FT &px, const FT &py,
                                       const FT &qx, const FT &qy)
{
  return CGAL_scaled_distance_to_lineC2(la,lb,lc,px,py)
       < CGAL_scaled_distance_to_lineC2(la,lb,lc,qx,qy);
}
template <class FT>
CGAL_KERNEL_MEDIUM_INLINE
CGAL_Comparison_result
CGAL_cmp_signed_dist_to_lineC2(const FT &px, const FT &py,
                               const FT &qx, const FT &qy,
                               const FT &rx, const FT &ry,
                               const FT &sx, const FT &sy)
{
  return CGAL_compare( CGAL_scaled_distance_to_lineC2(px,py,qx,qy,rx,ry),
                       CGAL_scaled_distance_to_lineC2(px,py,qx,qy,sx,sy));
}

template <class FT>
CGAL_KERNEL_MEDIUM_INLINE
bool
CGAL_has_larger_signed_dist_to_lineC2(const FT &px, const FT &py,
                                      const FT &qx, const FT &qy,
                                      const FT &rx, const FT &ry,
                                      const FT &sx, const FT &sy)
{
  return CGAL_scaled_distance_to_lineC2(px,py,qx,qy,sx,sy)
       < CGAL_scaled_distance_to_lineC2(px,py,qx,qy,rx,ry);
}

template <class FT>
CGAL_KERNEL_MEDIUM_INLINE
bool
CGAL_has_smaller_signed_dist_to_lineC2(const FT &px, const FT &py,
                                       const FT &qx, const FT &qy,
                                       const FT &rx, const FT &ry,
                                       const FT &sx, const FT &sy)
{
  return CGAL_scaled_distance_to_lineC2(px,py,qx,qy,rx,ry)
       < CGAL_scaled_distance_to_lineC2(px,py,qx,qy,sx,sy);
}

#ifdef CGAL_ARITHMETIC_FILTER_H
#include <CGAL/Arithmetic_filter/predicates_on_ftC2.h>
#endif


#endif  // CGAL_PREDICATES_ON_FTC2_H
