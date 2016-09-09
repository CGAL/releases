// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/predicates_on_ftC2.h
// package       : C2 (2.1.4)
// source        : web/predicates_on_ftC2.fw
// revision      : $Revision: 1.20 $
// revision_date : $Date: 1999/05/24 06:43:34 $
// author(s)     : Herve Bronnimann
//                 Sylvain Pion
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_PREDICATES_ON_FTC2_H
#define CGAL_PREDICATES_ON_FTC2_H

#ifndef CGAL_NUMBER_UTILS_H
#include <CGAL/number_utils.h>
#endif // CGAL_NUMBER_UTILS_H
#ifndef CGAL_DETERMINANT_H
#include <CGAL/determinant.h>
#endif // CGAL_DETERMINANT_H
#ifndef CGAL_BASIC_CONSTRUCTIONS_FTC2_H
#include <CGAL/basic_constructions_ftC2.h>
#endif

CGAL_BEGIN_NAMESPACE

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
Comparison_result
compare_xC2(const FT &px,
            const FT &l1a, const FT &l1b, const FT &l1c,
            const FT &l2a, const FT &l2b, const FT &l2c)
{
  Sign sign1 = sign_of_determinant2x2(l1a, l1b, l2a, l2b);
  Sign sign2 = sign_of_determinant3x3(l1a, l1b, l1c,
                                      l2a, l2b, l2c,
                                      -FT(1), FT(0), px);
  CGAL_kernel_assertion( sign1 != 0 );
  return Comparison_result (sign1 * sign2);
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
Comparison_result
compare_xC2(const FT &l1a, const FT &l1b, const FT &l1c,
                 const FT &l2a, const FT &l2b, const FT &l2c,
                 const FT &h1a, const FT &h1b, const FT &h1c,
                 const FT &h2a, const FT &h2b, const FT &h2c)
{
  Sign sign1 = sign_of_determinant2x2(l1a, l1b, l2a, l2b);
  Sign sign2 = sign_of_determinant2x2(h1a, h1b, h2a, h2b);
  // This could probably be optimized.
  // If someone uses it intensively, please feel free to do so.
  FT FT0(0);
  Sign sign3 = sign_of_determinant4x4(l1a, l1b, FT0, l1c,
                                      l2a, l2b, FT0, l2c,
                                      h1a, FT0, h1b, h1c,
                                      h2a, FT0, h2b, h2c);
  CGAL_kernel_assertion( (sign1 != 0) && (sign2 != 0) );
  return Comparison_result (- sign1 * sign2 * sign3);
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
Comparison_result
compare_y_at_xC2(const FT &px, const FT &py,
                 const FT &la, const FT &lb, const FT &lc)
{
  Sign sign1 = CGAL::sign(lb);
  Sign sign2 = CGAL::sign(la*px + lb*py + lc);
  CGAL_kernel_assertion( sign1 != 0 );
  return Comparison_result (sign1 * sign2);
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
Comparison_result
compare_y_at_xC2(const FT &px,
                 const FT &l1a, const FT &l1b, const FT &l1c,
                 const FT &l2a, const FT &l2b, const FT &l2c)
{
  Sign sign1 = CGAL::sign(l1b);
  Sign sign2 = CGAL::sign(l2b);
  Sign sign3 = sign_of_determinant2x2(l1a*px+l1c,l2a*px+l2c,l1b,l2b);
  CGAL_kernel_assertion( (sign1 != 0) && (sign2 != 0) );
  return Comparison_result (- sign1 * sign2 * sign3);
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
Comparison_result
compare_y_at_xC2(const FT &l1a, const FT &l1b, const FT &l1c,
                 const FT &l2a, const FT &l2b, const FT &l2c,
                 const FT &ha,  const FT &hb,  const FT &hc)
{
  Sign sign0 = sign_of_determinant2x2(l1a,l1b,l2a,l2b);
  Sign sign1 = sign_of_determinant3x3(ha,hb,hc,l1a,l1b,l1c,l2a,l2b,l2c);
  CGAL_kernel_assertion( (sign0 != ZERO) && (hb != FT(0)) );
  return Comparison_result (sign0 * CGAL::sign(hb) * sign1);
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
Comparison_result
compare_y_at_xC2(const FT &l1a, const FT &l1b, const FT &l1c,
                 const FT &l2a, const FT &l2b, const FT &l2c,
                 const FT &h1a, const FT &h1b, const FT &h1c,
                 const FT &h2a, const FT &h2b, const FT &h2c)
{
  FT FT0(0);
  Sign s1 = lexicographical_sign(h1b, -h1a);
  Sign s2 = lexicographical_sign(h2b, -h2a);
  Sign s3 = sign_of_determinant2x2(l1a, l1b, l2a, l2b);
  Sign s4 = sign_of_determinant4x4(h2a, h2b, FT0, h2c,
                                   l1a, FT0, l1b, l1c,
                                   l2a, FT0, l2b, l2c,
                                   h1a, h1b, FT0, h1c);
  return Comparison_result (s1 * s2 * s3 * s4);
}

template < class FT >
inline
Comparison_result
compare_deltax_deltayC2(const FT &px, const FT &qx,
                        const FT &ry, const FT &sy)
{
    return CGAL::compare(abs(px-qx), abs(ry-sy));
}

template < class FT >
inline
Comparison_result
compare_lexicographically_xyC2(const FT &px, const FT &py,
                               const FT &qx, const FT &qy)
{
  if (px < qx) return SMALLER;
  if (qx < px) return LARGER;
  if (py < qy) return SMALLER;
  if (qy < py) return LARGER;
  return EQUAL;
}

template < class FT >
inline
Orientation
orientationC2(const FT &px, const FT &py,
              const FT &qx, const FT &qy,
              const FT &rx, const FT &ry)
{
  return sign_of_determinant2x2(px-rx,py-ry,qx-rx,qy-ry);
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
bool
collinear_are_ordered_along_lineC2(const FT &px, const FT &py,
                                   const FT &qx, const FT &qy,
                                   const FT &rx, const FT &ry)
{
  CGAL_kernel_exactness_precondition( collinear(p, q, r) );
  if (px < qx) return !(rx < qx);
  if (qx < px) return !(qx < rx);
  if (py < qy) return !(ry < qy);
  if (qy < py) return !(qy < ry);
  return true; // p===q
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
bool
collinear_are_strictly_ordered_along_lineC2(const FT &px, const FT &py,
                                            const FT &qx, const FT &qy,
                                            const FT &rx, const FT &ry)
{
  CGAL_kernel_exactness_precondition( collinear(p, q, r) );
  if (px < qx) return (qx < rx);
  if (qx < px) return (rx < qx);
  if (py < qy) return (qy < ry);
  if (qy < py) return (ry < qy);
  return false;
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
Oriented_side
side_of_oriented_circleC2(const FT &px, const FT &py,
                          const FT &qx, const FT &qy,
                          const FT &rx, const FT &ry,
                          const FT &tx, const FT &ty)
{
  // Oriented_side(
  //  sign_of_determinant4x4(px, py, px*px + py*py, 1,
  //                         qx, qy, qx*qx + qy*qy, 1,
  //                         rx, ry, rx*rx + ry*ry, 1,
  //                         tx, ty, tx*tx + ty*ty, 1));
  // We first translate so that t is the new origin.
  FT ptx = px-tx;
  FT pty = py-ty;
  FT qtx = qx-tx;
  FT qty = qy-ty;
  FT rtx = rx-tx;
  FT rty = ry-ty;
  return Oriented_side(
           sign_of_determinant3x3(ptx, pty, square(ptx) + square(pty),
                                  qtx, qty, square(qtx) + square(qty),
                                  rtx, rty, square(rtx) + square(rty)));
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
Bounded_side
side_of_bounded_circleC2(const FT &px, const FT &py,
                         const FT &qx, const FT &qy,
                         const FT &rx, const FT &ry,
                         const FT &tx, const FT &ty)
{
  Oriented_side s = side_of_oriented_circleC2(px,py,qx,qy,rx,ry,tx,ty);
  Orientation o = orientationC2(px,py,qx,qy,rx,ry);

  return Bounded_side (s * o);
}

template < class FT >
inline
Comparison_result
cmp_dist_to_pointC2(const FT &px, const FT &py,
                    const FT &qx, const FT &qy,
                    const FT &rx, const FT &ry)
{
  return CGAL::compare(squared_distanceC2(px,py,qx,qy),
                       squared_distanceC2(px,py,rx,ry));
}

template < class FT >
inline
bool
has_larger_dist_to_pointC2(const FT &px, const FT &py,
                           const FT &qx, const FT &qy,
                           const FT &rx, const FT &ry)
{
  return squared_distanceC2(px,py,rx,ry)
       < squared_distanceC2(px,py,qx,qy);
}

template < class FT >
inline
bool
has_smaller_dist_to_pointC2(const FT &px, const FT &py,
                            const FT &qx, const FT &qy,
                            const FT &rx, const FT &ry)
{
  return squared_distanceC2(px,py,qx,qy)
       < squared_distanceC2(px,py,rx,ry);
}

template < class FT >
inline
Comparison_result
cmp_signed_dist_to_lineC2(const FT &la, const FT &lb, const FT &lc,
                          const FT &px, const FT &py,
                          const FT &qx, const FT &qy)
{
  return CGAL::compare(scaled_distance_to_directionC2(la,lb,px,py),
                       scaled_distance_to_directionC2(la,lb,qx,qy));
}

template < class FT >
inline
bool
has_larger_signed_dist_to_lineC2(const FT &la, const FT &lb, const FT &lc,
                                 const FT &px, const FT &py,
                                 const FT &qx, const FT &qy)
{
  return scaled_distance_to_directionC2(la,lb,qx,qy)
       < scaled_distance_to_directionC2(la,lb,px,py);
}

template < class FT >
inline
bool
has_smaller_signed_dist_to_lineC2(const FT &la, const FT &lb, const FT &lc,
                                  const FT &px, const FT &py,
                                  const FT &qx, const FT &qy)
{
  return scaled_distance_to_directionC2(la,lb,px,py)
       < scaled_distance_to_directionC2(la,lb,qx,qy);
}
template <class FT>
inline
Comparison_result
cmp_signed_dist_to_lineC2(const FT &px, const FT &py,
                          const FT &qx, const FT &qy,
                          const FT &rx, const FT &ry,
                          const FT &sx, const FT &sy)
{
  return CGAL::compare(scaled_distance_to_lineC2(px,py,qx,qy,rx,ry),
                       scaled_distance_to_lineC2(px,py,qx,qy,sx,sy));
}

template <class FT>
inline
bool
has_larger_signed_dist_to_lineC2(const FT &px, const FT &py,
                                 const FT &qx, const FT &qy,
                                 const FT &rx, const FT &ry,
                                 const FT &sx, const FT &sy)
{
  return scaled_distance_to_lineC2(px,py,qx,qy,sx,sy)
       < scaled_distance_to_lineC2(px,py,qx,qy,rx,ry);
}

template <class FT>
inline
bool
has_smaller_signed_dist_to_lineC2(const FT &px, const FT &py,
                                  const FT &qx, const FT &qy,
                                  const FT &rx, const FT &ry,
                                  const FT &sx, const FT &sy)
{
  return scaled_distance_to_lineC2(px,py,qx,qy,rx,ry)
       < scaled_distance_to_lineC2(px,py,qx,qy,sx,sy);
}


CGAL_END_NAMESPACE

#ifdef CGAL_ARITHMETIC_FILTER_H
#ifndef CGAL_ARITHMETIC_FILTER_PREDICATES_ON_FTC2_H
#include <CGAL/Arithmetic_filter/predicates_on_ftC2.h>
#endif // CGAL_ARITHMETIC_FILTER_PREDICATES_ON_FTC2_H
#endif

#endif  // CGAL_PREDICATES_ON_FTC2_H
