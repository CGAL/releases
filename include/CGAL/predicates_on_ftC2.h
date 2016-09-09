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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.1
// release_date  : 1998, July 24
//
// file          : include/CGAL/predicates_on_ftC2.h
// package       : C2 (1.3)
// source        : web/predicates_on_ftC2.fw
// revision      : $Revision: 1.1 $
// revision_date : $Date: 1998/06/15 20:12:00 $
// author(s)     : Herve.Bronnimann
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_PREDICATES_ON_FTC2_H
#define CGAL_PREDICATES_ON_FTC2_H

#ifndef CGAL_DETERMINANT_H
#include <CGAL/determinant.h>
#endif // CGAL_DETERMINANT_H

template < class FT >
CGAL_KERNEL_LARGE_INLINE
CGAL_Comparison_result
CGAL_compare_xC2(const FT &px,const FT &py,
                 const FT &l1a, const FT &l1b, const FT &l1c,
                 const FT &l2a, const FT &l2b, const FT &l2c)
{
  int sign1 = CGAL_sign(CGAL_det2x2_by_formula(l1a, l1b, l2a, l2b));
  int sign2 = CGAL_sign(CGAL_det3x3_by_formula(l1a, l1b, l1c,
                                               l2a, l2b, l2c,
                                               -FT(1), FT(0), px));
  CGAL_kernel_assertion( sign1 != 0 );
  if (sign2 == 0) return CGAL_EQUAL;
  return (sign1 == sign2) ? CGAL_LARGER : CGAL_SMALLER;
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
CGAL_Comparison_result
CGAL_compare_xC2(const FT &l1a, const FT &l1b, const FT &l1c,
                 const FT &l2a, const FT &l2b, const FT &l2c,
                 const FT &h1a, const FT &h1b, const FT &h1c,
                 const FT &h2a, const FT &h2b, const FT &h2c)
{
  FT FT0(0);
  int sign1 = CGAL_sign(CGAL_det2x2_by_formula(l1a, l1b, l2a, l2b));
  int sign2 = CGAL_sign(CGAL_det2x2_by_formula(h1a, h1b, h2a, h2b));
  int sign3 = CGAL_sign(CGAL_det4x4_by_formula(l1a, l1b, FT0, l1c,
                                               l2a, l2b, FT0, l2c,
                                               h1a, FT0, h1b, h1c,
                                               h2a, FT0, h2b, h2c));
  CGAL_kernel_assertion( (sign1 != 0) && (sign2 != 0)  );
  if (sign3 == 0) return CGAL_EQUAL;
  if (sign3 < 0)  return (sign1 == sign2) ? CGAL_LARGER : CGAL_SMALLER;
                  return (sign1 == sign2) ? CGAL_SMALLER : CGAL_LARGER;
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
CGAL_Comparison_result
CGAL_compare_y_at_xC2(const FT &px, const FT&py,
                      const FT &la, const FT &lb, const FT &lc)
{
  int sign1 = CGAL_sign(lb);
  int sign2 = CGAL_sign(la*px + lb*py + lc);
  CGAL_kernel_assertion( sign1 != 0 );
  if (sign2 == 0) return CGAL_EQUAL;
  return (sign1 == sign2) ? CGAL_LARGER : CGAL_SMALLER;
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
CGAL_Comparison_result
CGAL_compare_y_at_xC2(const FT &px,
                      const FT &l1a, const FT &l1b, const FT &l1c,
                      const FT &l2a, const FT &l2b, const FT &l2c)
{
  int sign1 = CGAL_sign(l1b);
  int sign2 = CGAL_sign(l2b);
  int sign3 = CGAL_sign(CGAL_det2x2_by_formula(la1*px+l1c,l2a*px+l2c,l1b,l2b));
  CGAL_kernel_assertion( (sign1 != 0) && (sign2 != 0)  );
  if (sign3 == 0) return CGAL_EQUAL;
  if (sign3 < 0)  return (sign1 == sign2) ? CGAL_LARGER : CGAL_SMALLER;
                  return (sign1 == sign2) ? CGAL_SMALLER : CGAL_LARGER;
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
CGAL_Comparison_result
CGAL_compare_y_at_xC2(const FT &l1a, const FT &l1b, const FT &l1c,
                      const FT &l2a, const FT &l2b, const FT &l2c,
                      const FT &ha,  const FT &hb,  const FT &hc)
{
  FT denom = CGAL_det2x2_by_formula(l1a,l1b,l2a,l2b);
  FT x = CGAL_det2x2_by_formula(l1b,l1c,l2b,l2c)/denom;
  FT y = CGAL_det2x2_by_formula(l1c,l1a,l2c,l2a)/denom;
  FT hy = (-ha*x-hc)/hb;
  return CGAL_compare(y,hy);
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
CGAL_Comparison_result
CGAL_compare_y_at_xC2(const FT &l1a, const FT &l1b, const FT &l1c,
                      const FT &l2a, const FT &l2b, const FT &l2c,
                      const FT &h1a, const FT &h1b, const FT &h1c,
                      const FT &h2a, const FT &h2b, const FT &h2c)
{
  FT FT0(0);
  int s1 = CGAL_lexicographical_sign(h1b, -h1a);
  int s2 = CGAL_lexicographical_sign(h2b, -h2a);
  int s3 = CGAL_sign(CGAL_det2x2_by_formula(l1a, l1b, l2a, l2b));
  int s4 = CGAL_sign(CGAL_det4x4_by_formula(h2a, h2b, FT0, h2c,
                                            l1a, FT0, l1b, l1c,
                                            l2a, FT0, l2b, l2c,
                                            h1a, h1b, FT0, h1c));
  return CGAL_compare(s1*s2*s3*s4,0);
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
CGAL_Comparison_result
inline
CGAL_compare_lexicographically_xyC2(const FT &px, const FT &py,
                                    const FT &qx, const FT &qy)
{
  if (px < qx){ return CGAL_SMALLER; }
  if (px == qx){
    if (py < qy){ return CGAL_SMALLER; }
    if (py == qy){ return CGAL_EQUAL; }
  }
  return CGAL_LARGER;
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
CGAL_Orientation
CGAL_orientationC2(const FT &px, const FT &py,
                   const FT &qx, const FT &qy,
                   const FT &rx, const FT &ry)
{
  FT d1 = (px-qx)*(qy-ry);
  FT d2 = (py-qy)*(qx-rx);
  return  (d1 < d2) ? CGAL_RIGHTTURN
            : ((d1 == d2)? CGAL_COLLINEAR : CGAL_LEFTTURN);
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
bool
CGAL_collinear_are_ordered_along_lineC2(const FT &px, const FT &py,
                                        const FT &qx, const FT &qy,
                                        const FT &rx, const FT &ry)
{
  CGAL_kernel_exactness_precondition( CGAL_collinear(p, q, r) );
  if (px < rx)      return !((qx < px) || (rx < qx));
  else if (rx < px) return !((qx < rx) || (px < qx));
  else if (py < ry) return !((qy < py) || (ry < qy));
  else if (ry < py) return !((qy < ry) || (py < qy));
  return (px==qx) && (py==qy);
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
bool
CGAL_collinear_are_strictly_ordered_along_lineC2(const FT &px, const FT &py,
                                                 const FT &qx, const FT &qy,
                                                 const FT &rx, const FT &ry)
{
  CGAL_kernel_exactness_precondition( CGAL_collinear(p, q, r) );
  if (px < rx)      return ((px < qx) && (qx < rx));
  else if (rx < px) return ((rx < qx) && (qx < px));
  else if (py < ry) return ((py < qy) && (qy < ry));
  else if (ry < py) return ((ry < qy) && (qy < py));
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
  FT FT0(0);
  FT FT1(1);

  FT det = CGAL_det4x4_by_formula(px, py, px*px + py*py, FT1,
                                  qx, qy, qx*qx + qy*qy, FT1,
                                  rx, ry, rx*rx + ry*ry, FT1,
                                  tx, ty, tx*tx + ty*ty, FT1);

  return (det<FT0) ? CGAL_ON_NEGATIVE_SIDE
           : ((det==FT0) ? CGAL_ON_ORIENTED_BOUNDARY : CGAL_ON_POSITIVE_SIDE);
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
CGAL_Bounded_side
CGAL_side_of_bounded_circleC2(const FT &px, const FT &py,
                              const FT &qx, const FT &qy,
                              const FT &rx, const FT &ry,
                              const FT &tx, const FT &ty)
{
  FT FT0(0);
  FT FT1(1);

  FT det = CGAL_det4x4_by_formula(px, py, px*px + py*py, FT1,
                                  qx, qy, qx*qx + qy*qy, FT1,
                                  rx, ry, rx*rx + ry*ry, FT1,
                                  tx, ty, tx*tx + ty*ty, FT1);

  if (CGAL_orientationC2(px, py, qx, qy, rx, ry) == CGAL_LEFTTURN )
    { det = -det; }

  return (det<FT0) ? CGAL_ON_BOUNDED_SIDE
                  : ((det==FT0) ? CGAL_ON_BOUNDARY : CGAL_ON_UNBOUNDED_SIDE);
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
CGAL_Comparison_result
CGAL_cmp_dist_to_pointC2(const FT &px, const FT &py,
                         const FT &qx, const FT &qy,
                         const FT &rx, const FT &ry)
{
  FT square_dist_pq = (px - qx)*(px - qx) + (py - qy)*(py - qy);
  FT square_dist_pr = (px - rx)*(px - rx) + (py - ry)*(py - ry);

  if (square_dist_pr < square_dist_pq) return CGAL_LARGER;
  if (square_dist_pq < square_dist_pr) return CGAL_SMALLER;
  return CGAL_EQUAL;
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
bool
CGAL_has_larger_dist_to_pointC2(const FT &px, const FT &py,
                                const FT &qx, const FT &qy,
                                const FT &rx, const FT &ry)
{
  FT square_dist_pq = (px - qx)*(px - qx) + (py - qy)*(py - qy);
  FT square_dist_pr = (px - rx)*(px - rx) + (py - ry)*(py - ry);
  return (square_dist_pr < square_dist_pq);
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
bool
CGAL_has_smaller_dist_to_pointC2(const FT &px, const FT &py,
                                 const FT &qx, const FT &qy,
                                 const FT &rx, const FT &ry)
{
  FT square_dist_pq = (px - qx)*(px - qx) + (py - qy)*(py - qy);
  FT square_dist_pr = (px - rx)*(px - rx) + (py - ry)*(py - ry);
  return (square_dist_pq < square_dist_pr);
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
CGAL_Comparison_result
CGAL_cmp_signed_dist_to_lineC2(const FT &la, const FT &lb, const FT &lc,
                               const FT &px, const FT &py,
                               const FT &qx, const FT &qy)
{
  FT scaled_dist_p = la*px + lb*py ;
  FT scaled_dist_q = la*qx + lb*qy ;

  if (scaled_dist_p < scaled_dist_q) return CGAL_SMALLER;
  if (scaled_dist_q < scaled_dist_p) return CGAL_LARGER;
  return CGAL_EQUAL;
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
bool
CGAL_has_larger_signed_dist_to_lineC2(const FT &la, const FT &lb, const FT &lc,
                                      const FT &px, const FT &py,
                                      const FT &qx, const FT &qy)
{
  FT scaled_dist_p = la*px + lb*py ;
  FT scaled_dist_q = la*qx + lb*qy ;
  return (scaled_dist_q < scaled_dist_p);
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
bool
CGAL_has_smaller_signed_dist_to_lineC2(const FT &la, const FT &lb, const FT &lc,
                                       const FT &px, const FT &py,
                                       const FT &qx, const FT &qy)
{
  FT scaled_dist_p = la*px + lb*py ;
  FT scaled_dist_q = la*qx + lb*qy ;
  return (scaled_dist_p < scaled_dist_q);
}
template <class FT>
CGAL_KERNEL_LARGE_INLINE
CGAL_Comparison_result
CGAL_cmp_signed_dist_to_lineC2(const FT &px, const FT &py,
                               const FT &qx, const FT &qy,
                               const FT &rx, const FT &ry,
                               const FT &sx, const FT &sy)
{
  FT scaled_dist_r = (px-rx)*(qy-ry) - (py-ry)*(qx-rx);
  FT scaled_dist_s = (px-sx)*(qy-sy) - (py-sy)*(qx-sx);

  if ( scaled_dist_r < scaled_dist_s ) return CGAL_SMALLER;
  if ( scaled_dist_s < scaled_dist_r ) return CGAL_LARGER;
  return CGAL_EQUAL;
}

template <class FT>
CGAL_KERNEL_LARGE_INLINE
bool
CGAL_has_larger_signed_dist_to_lineC2(const FT &px, const FT &py,
                                      const FT &qx, const FT &qy,
                                      const FT &rx, const FT &ry,
                                      const FT &sx, const FT &sy)
{
  FT scaled_dist_r = (px-rx)*(qy-ry) - (py-ry)*(qx-rx);
  FT scaled_dist_s = (px-sx)*(qy-sy) - (py-sy)*(qx-sx);
  return (scaled_dist_s < scaled_dist_r);
}

template <class FT>
CGAL_KERNEL_LARGE_INLINE
bool
CGAL_has_smaller_signed_dist_to_lineC2(const FT &px, const FT &py,
                                       const FT &qx, const FT &qy,
                                       const FT &rx, const FT &ry,
                                       const FT &sx, const FT &sy)
{
  FT scaled_dist_r = (px-rx)*(qy-ry) - (py-ry)*(qx-rx);
  FT scaled_dist_s = (px-sx)*(qy-sy) - (py-sy)*(qx-sx);
  return (scaled_dist_r < scaled_dist_s);
}


#endif  // CGAL_PREDICATES_ON_FTC2_H
