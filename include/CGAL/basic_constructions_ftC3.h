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
// file          : include/CGAL/basic_constructions_ftC3.h
// package       : C3 (1.6)
// source        : web/basic_constructions_ftC3.fw
// revision      : $Revision: 1.1 $
// revision_date : $Date: 1998/12/04 12:24:07 $
// author(s)     : Herve.Bronnimann
//
// coordinator   : INRIA Sophia-Antipolis
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_BASIC_CONSTRUCTIONS_FTC3_H
#define CGAL_BASIC_CONSTRUCTIONS_FTC3_H

#ifndef CGAL_DETERMINANT_H
#include <CGAL/determinant.h>
#endif

template < class FT >
CGAL_KERNEL_INLINE
void
CGAL_midpointC3( const FT &px, const FT &py, const FT &pz,
                 const FT &qx, const FT &qy, const FT &qz,
                 FT &x, FT &y, FT &z)
{
  const FT FT2(2);
  x = (px+qx) / FT2;
  y = (py+qy) / FT2;
  z = (pz+qz) / FT2;
}

template < class FT >
void
CGAL_circumcenterC3( const FT &px, const FT &py, const FT &pz,
                     const FT &qx, const FT &qy, const FT &qz,
                     const FT &rx, const FT &ry, const FT &rz,
                     const FT &sx, const FT &sy, const FT &sz,
                     FT &x, FT &y, FT &z)
{
  // const FT FT1(1);
  // FT p2( px*px + py*py + pz*pz );
  // FT q2( qx*qx + qy*qy + qz*qz );
  // FT r2( rx*rx + ry*ry + rz*rz );
  // FT s2( sx*sx + sy*sy + sz*sz );
  // FT num_x( CGAL_det4x4_by_formula(py,pz,p2,FT1,
  //                                  qy,qz,q2,FT1,
  //                                  ry,rz,r2,FT1,
  //                                  sy,sz,s2,FT1));
  // FT num_y( CGAL_det4x4_by_formula(px,pz,p2,FT1,
  //                                  qx,qz,q2,FT1,
  //                                  rx,rz,r2,FT1,
  //                                  sx,sz,s2,FT1));
  // FT num_z( CGAL_det4x4_by_formula(px,py,p2,FT1,
  //                                  qx,qy,q2,FT1,
  //                                  rx,ry,r2,FT1,
  //                                  sx,sy,s2,FT1));
  // FT den( CGAL_det4x4_by_formula(px,py,pz,FT1,
  //                                qx,qy,qz,FT1,
  //                                rx,ry,rz,FT1,
  //                                sx,sy,sz,FT1) * FT(2) );
  // Optimized code: [equivalent to above, but less readble]
  const FT psx = px-sx;
  const FT psy = py-sy;
  const FT psz = pz-sz;
  const FT ps2 = (px+sx)*psx + (py+sy)*psy + (pz+sz)*psz;
  const FT qsx = qx-sx;
  const FT qsy = qy-sy;
  const FT qsz = qz-sz;
  const FT qs2 = (qx+sx)*qsx + (qy+sy)*qsy + (qz+sz)*qsz;
  const FT rsx = rx-sx;
  const FT rsy = ry-sy;
  const FT rsz = rz-sz;
  const FT rs2 = (rx+sx)*rsx + (ry+sy)*rsy + (rz+sz)*rsz;
  const FT num_x( CGAL_det3x3_by_formula(psy,psz,ps2,
                                         qsy,qsz,qs2,
                                         rsy,rsz,rs2));
  const FT num_y( CGAL_det3x3_by_formula(psx,psz,ps2,
                                         qsx,qsz,qs2,
                                         rsx,rsz,rs2));
  const FT num_z( CGAL_det3x3_by_formula(psx,psy,ps2,
                                         qsx,qsy,qs2,
                                         rsx,rsy,rs2));
  const FT den( CGAL_det3x3_by_formula(psx,psy,psz,
                                       qsx,qsy,qsz,
                                       rsx,rsy,rsz) * FT(2) );
  CGAL_kernel_assertion( den != FT(0) );

  x = num_x/den;
  y = - num_y/den;
  z = num_z/den;
}

template <class FT>
CGAL_KERNEL_MEDIUM_INLINE
void
CGAL_projectionC3(const FT &pa, const FT &pb, const FT &pc, const FT &pd,
                  const FT &px, const FT &py, const FT &pz,
                  FT &x, FT &y, FT &z)
{
  // the equation of the plane is Ax+By+Cz+D=0
  // the normal direction is (A,B,C)
  // the projected point is p-lambda(A,B,C) where
  // A(x-lambda A) + B(y-lambda B) + C(z-lambda C) + D = 0

  const FT num = pa*px + pb*py + pc*pz + pd;
  const FT den = pa*pa + pb*pb + pc*pc;
  const FT lambda = num / den;

  x = px - lambda * pa;
  y = py - lambda * pb;
  z = pz - lambda * pc;
}


template < class FT >
CGAL_KERNEL_INLINE
FT
CGAL_squared_distanceC3( const FT &px, const FT &py, const FT &pz,
                         const FT &qx, const FT &qy, const FT &qz)
{
  FT x = px - qx;
  FT y = py - qy;
  FT z = pz - qz;
  return( x*x + y*y + z*z );
}

template < class FT >
CGAL_KERNEL_INLINE
FT
CGAL_scaled_distance_to_planeC3(
     const FT &pa, const FT &pb, const FT &pc, const FT &pd,
     const FT &px, const FT &py)
{
  // as for C2, we could avoid the extra +pd for comparison purposes,
  // but it is not consistent with the name nor with the implicit
  // version below...
  return pa*px + pb*py + pc*pz + pd;
}

template < class FT >
CGAL_KERNEL_INLINE
FT
CGAL_scaled_distance_to_planeC3(
     const FT &ppx, const FT &ppy, const FT &ppz,
     const FT &pqx, const FT &pqy, const FT &pqz,
     const FT &prx, const FT &pry, const FT &prz,
     const FT &px, const FT &py, const FT &pz)
{
  return CGAL_det3x3_by_formula(ppx-px,ppy-py,ppz-pz,
                                pqx-px,pqy-py,pqz-pz,
                                prx-px,pry-py,prz-pz);
}


#endif // CGAL_BASIC_CONSTRUCTIONS_FTC3_H
