// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
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
// file          : include/CGAL/predicates_on_ftC3.h
// package       : C3 (1.6)
// source        : web/predicates_on_ftC3.fw
// revision      : $Revision: 1.2 $
// revision_date : $Date: 1998/12/08 15:12:50 $
// author(s)     : Herve.Bronnimann
//
// coordinator   : INRIA Sophia-Antipolis
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_PREDICATES_ON_FTC3_H
#define CGAL_PREDICATES_ON_FTC3_H

#ifndef CGAL_DETERMINANT_H
#include <CGAL/determinant.h>
#endif // CGAL_DETERMINANT_H
#ifndef CGAL_BASIC_CONSTRUCTIONS_FTC3_H
#include <CGAL/basic_constructions_ftC3.h>
#endif // CGAL_BASIC_CONSTRUCTIONS_FTC3_H

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
CGAL_Comparison_result
CGAL_compare_lexicographically_xyzC3(const FT &x1, const FT &y1, const FT &z1,
                                     const FT &x2, const FT &y2, const FT &z2)
{
  if (x1 < x2) return CGAL_SMALLER;
  if (x2 < x1) return CGAL_LARGER;
  if (y1 < y2) return CGAL_SMALLER;
  if (y2 < y1) return CGAL_LARGER;
  if (z1 < z2) return CGAL_SMALLER;
  if (z2 < z1) return CGAL_LARGER;
  return CGAL_EQUAL;
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
bool
CGAL_collinearC3(const FT &px, const FT &py, const FT &pz,
                 const FT &qx, const FT &qy, const FT &qz,
                 const FT &rx, const FT &ry, const FT &rz)
{
  return (CGAL_sign(CGAL_det2x2_by_formula(px-rx,qx-rx,
                                           py-ry,qy-ry)) == CGAL_ZERO)
      && (CGAL_sign(CGAL_det2x2_by_formula(px-rx,qx-rx,
                                           pz-rz,qz-rz)) == CGAL_ZERO)
      && (CGAL_sign(CGAL_det2x2_by_formula(py-ry,qy-ry,
                                           pz-rz,qz-rz)) == CGAL_ZERO);
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
CGAL_Orientation
CGAL_orientationC3(const FT &px, const FT &py, const FT &pz,
                   const FT &qx, const FT &qy, const FT &qz,
                   const FT &rx, const FT &ry, const FT &rz,
                   const FT &sx, const FT &sy, const FT &sz)
{
  return CGAL_Orientation(
         CGAL_sign(CGAL_det3x3_by_formula(qx-px,rx-px,sx-px,
                                          qy-py,ry-py,sy-py,
                                          qz-pz,rz-pz,sz-pz)));
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
bool
CGAL_collinear_are_ordered_along_lineC3(
     const FT &px, const FT &py, const FT &pz,
     const FT &qx, const FT &qy, const FT &qz,
     const FT &rx, const FT &ry, const FT &rz)
{
  CGAL_kernel_exactness_precondition( CGAL_collinear(p, q, r) );
  if (px < qx) return !(rx < qx);
  if (qx < px) return !(qx < rx);
  if (py < qy) return !(ry < qy);
  if (qy < py) return !(qy < ry);
  if (pz < qz) return !(rz < qz);
  if (qz < pz) return !(qz < rz);
  return true; // p==q
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
bool
CGAL_collinear_are_strictly_ordered_along_lineC3(
     const FT &px, const FT &py, const FT &pz,
     const FT &qx, const FT &qy, const FT &qz,
     const FT &rx, const FT &ry, const FT &rz)
{
  CGAL_kernel_exactness_precondition( CGAL_collinear(p, q, r) );
  if (px < qx) return (qx < rx);
  if (qx < px) return (rx < qx);
  if (py < qy) return (qy < ry);
  if (qy < py) return (ry < qy);
  if (pz < qz) return (qz < rz);
  if (qz < pz) return (rz < qz);
  return false; // p==q
}


template <class FT >
CGAL_KERNEL_LARGE_INLINE
CGAL_Oriented_side
CGAL_side_of_oriented_sphereC3(const FT &px, const FT &py, const FT &pz,
                               const FT &qx, const FT &qy, const FT &qz,
                               const FT &rx, const FT &ry, const FT &rz,
                               const FT &sx, const FT &sy, const FT &sz,
                               const FT &tx, const FT &ty, const FT &tz)
{
  // FT FT1(1);
  // return CGAL_Oriented_side(CGAL_sign(-
  //        CGAL_det5x5_by_formula(px, py, pz, px*px + py*py + pz*pz, FT1,
  //                               qx, qy, qz, qx*qx + qy*qy + qz*qz, FT1,
  //                               rx, ry, rz, rx*rx + ry*ry + rz*rz, FT1,
  //                               sx, sy, sz, sx*sx + sy*sy + sz*sz, FT1,
  //                               tx, ty, tz, tx*tx + ty*ty + tz*tz, FT1)));
  // Optimized version:
  const FT ptx = px - tx;
  const FT pty = py - ty;
  const FT ptz = pz - tz;
  const FT pt2 = (px+tx)*ptx + (py+ty)*pty + (pz+tz)*ptz;
  const FT qtx = qx - tx;
  const FT qty = qy - ty;
  const FT qtz = qz - tz;
  const FT qt2 = (qx+tx)*qtx + (qy+ty)*qty + (qz+tz)*qtz;
  const FT rtx = rx - tx;
  const FT rty = ry - ty;
  const FT rtz = rz - tz;
  const FT rt2 = (rx+tx)*rtx + (ry+ty)*rty + (rz+tz)*rtz;
  const FT stx = sx - tx;
  const FT sty = sy - ty;
  const FT stz = sz - tz;
  const FT st2 = (sx+tx)*stx + (sy+ty)*sty + (sz+tz)*stz;
  return CGAL_Oriented_side(CGAL_sign(-
           CGAL_det4x4_by_formula(ptx,pty,ptz,pt2,
                                  qtx,qty,qtz,qt2,
                                  rtx,rty,rtz,rt2,
                                  stx,sty,stz,st2)));
}

template <class FT >
CGAL_KERNEL_MEDIUM_INLINE
CGAL_Bounded_side
CGAL_side_of_bounded_sphereC3(const FT &px, const FT &py, const FT &pz,
                              const FT &qx, const FT &qy, const FT &qz,
                              const FT &rx, const FT &ry, const FT &rz,
                              const FT &sx, const FT &sy, const FT &sz,
                              const FT &tx, const FT &ty, const FT &tz)
{
  const CGAL_Sign s = CGAL_sign(
                      CGAL_side_of_oriented_sphereC3(px, py, pz,
                                                     qx, qy, qz,
                                                     rx, ry, rz,
                                                     sx, sy, sz,
                                                     tx, ty, tz));
  const CGAL_Orientation o = CGAL_orientationC3(px, py, pz,
                                                qx, qy, qz,
                                                rx, ry, rz,
                                                sx, sy, sz);
  return CGAL_Bounded_side(- s * o);
}


template < class FT >
CGAL_KERNEL_INLINE
CGAL_Comparison_result
CGAL_cmp_dist_to_pointC3(const FT &px, const FT &py, const FT &pz,
                         const FT &qx, const FT &qy, const FT &qz,
                         const FT &rx, const FT &ry, const FT &rz)
{
  return CGAL_compare(CGAL_squared_distanceC3(px,py,pz,qx,qy,qz),
                      CGAL_squared_distanceC3(px,py,pz,rx,ry,rz));
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
bool
CGAL_has_larger_dist_to_pointC3(const FT &px, const FT &py, const FT &pz,
                                const FT &qx, const FT &qy, const FT &qz,
                                const FT &rx, const FT &ry, const FT &rz)
{
  return CGAL_squared_distanceC3(px,py,pz,rx,ry,rz)
       < CGAL_squared_distanceC3(px,py,pz,qx,qy,qz);
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
bool
CGAL_has_smaller_dist_to_pointC3(const FT &px, const FT &py, const FT &pz,
                                 const FT &qx, const FT &qy, const FT &qz,
                                 const FT &rx, const FT &ry, const FT &rz)
{
  return CGAL_squared_distanceC3(px,py,pz,qx,qy,qz)
       < CGAL_squared_distanceC3(px,py,pz,rx,ry,rz);
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
CGAL_Comparison_result
CGAL_cmp_signed_dist_to_planeC3(
     const FT &pa, const FT &pb, const FT &pc, const FT &pd,
     const FT &px, const FT &py, const FT &pz,
     const FT &qx, const FT &qy, const FT &qz)
{
  return CGAL_compare( CGAL_scaled_distance_to_planeC3(pa,pb,pc,pd,px,py,pz),
                       CGAL_scaled_distance_to_planeC3(pa,pb,pc,pd,qx,qy,qz));
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
bool
CGAL_has_larger_signed_dist_to_planeC3(
     const FT &pa, const FT &pb, const FT &pc, const FT &pd,
     const FT &px, const FT &py, const FT &pz,
     const FT &qx, const FT &qy, const FT &qz)
{
  return CGAL_scaled_distance_to_planeC3(pa,pb,pc,pd,qx,qy,qz)
       < CGAL_scaled_distance_to_planeC3(pa,pb,pc,pd,px,py,pz);
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
bool
CGAL_has_smaller_signed_dist_to_planeC3(
     const FT &pa, const FT &pb, const FT &pc, const FT &pd,
     const FT &px, const FT &py, const FT &pz,
     const FT &qx, const FT &qy, const FT &qz)
{
  return CGAL_scaled_distance_to_planeC3(pa,pb,pc,pd,px,py,pz)
       < CGAL_scaled_distance_to_planeC3(pa,pb,pc,pd,qx,qy,qz);
}
template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
CGAL_Comparison_result
CGAL_cmp_signed_dist_to_planeC3(
     const FT &ppx, const FT &ppy, const FT &ppz,
     const FT &pqx, const FT &pqy, const FT &pqz,
     const FT &prx, const FT &pry, const FT &prz,
     const FT &px, const FT &py, const FT &pz,
     const FT &qx, const FT &qy, const FT &qz)
{
  return CGAL_compare(
           CGAL_scaled_distance_to_planeC3(ppx,ppy,ppz,pqx,pqy,pqz,
                                           prx,pry,prz,psx,psy,psz,
                                           px,py,pz),
           CGAL_scaled_distance_to_planeC3(ppx,ppy,ppz,pqx,pqy,pqz,
                                           prx,pry,prz,psx,psy,psz,
                                           qx,qy,qz) );
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
bool
CGAL_has_larger_signed_dist_to_planeC3(
     const FT &ppx, const FT &ppy, const FT &ppz,
     const FT &pqx, const FT &pqy, const FT &pqz,
     const FT &prx, const FT &pry, const FT &prz,
     const FT &px, const FT &py, const FT &pz,
     const FT &qx, const FT &qy, const FT &qz)
{
  return CGAL_scaled_distance_to_planeC3(ppx,ppy,ppz,pqx,pqy,pqz,
                                         prx,pry,prz,psx,psy,psz,
                                         qx,qy,qz)
       < CGAL_scaled_distance_to_planeC3(ppx,ppy,ppz,pqx,pqy,pqz,
                                         prx,pry,prz,psx,psy,psz,
                                         px,py,pz);
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
bool
CGAL_has_smaller_signed_dist_to_planeC3(
     const FT &ppx, const FT &ppy, const FT &ppz,
     const FT &pqx, const FT &pqy, const FT &pqz,
     const FT &prx, const FT &pry, const FT &prz,
     const FT &px, const FT &py, const FT &pz,
     const FT &qx, const FT &qy, const FT &qz)
{
  return CGAL_scaled_distance_to_planeC3(ppx,ppy,ppz,pqx,pqy,pqz,
                                         prx,pry,prz,psx,psy,psz,
                                         px,py,pz)
       < CGAL_scaled_distance_to_planeC3(ppx,ppy,ppz,pqx,pqy,pqz,
                                         prx,pry,prz,psx,psy,psz,
                                         qx,qy,qz);
}

#ifdef CGAL_ARITHMETIC_FILTER_H
#include <CGAL/Arithmetic_filter/predicates_on_ftC3.h>
#endif


#endif // CGAL_PREDICATES_ON_FTC3_H
