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
// file          : include/CGAL/basic_constructions_ftC3.h
// package       : C3 (2.1.5)
// source        : web/basic_constructions_ftC3.fw
// revision      : $Revision: 1.5 $
// revision_date : $Date: 1999/05/24 06:41:39 $
// author(s)     : Herve.Bronnimann
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_BASIC_CONSTRUCTIONS_FTC3_H
#define CGAL_BASIC_CONSTRUCTIONS_FTC3_H

#ifndef CGAL_DETERMINANT_H
#include <CGAL/determinant.h>
#endif

CGAL_BEGIN_NAMESPACE

template < class FT >
CGAL_KERNEL_INLINE
void
midpointC3( const FT &px, const FT &py, const FT &pz,
            const FT &qx, const FT &qy, const FT &qz,
            FT &x, FT &y, FT &z)
{
  FT half = FT(1) / FT(2);
  x = (px+qx) * half;
  y = (py+qy) * half;
  z = (pz+qz) * half;
}

template < class FT >
void
circumcenterC3( const FT &px, const FT &py, const FT &pz,
                const FT &qx, const FT &qy, const FT &qz,
                const FT &rx, const FT &ry, const FT &rz,
                const FT &sx, const FT &sy, const FT &sz,
                FT &x, FT &y, FT &z)
{
  // Translate s to origin to simplify the expression.
  FT psx = px-sx;
  FT psy = py-sy;
  FT psz = pz-sz;
  FT ps2 = square(psx) + square(psy) + square(psz);
  FT qsx = qx-sx;
  FT qsy = qy-sy;
  FT qsz = qz-sz;
  FT qs2 = square(qsx) + square(qsy) + square(qsz);
  FT rsx = rx-sx;
  FT rsy = ry-sy;
  FT rsz = rz-sz;
  FT rs2 = square(rsx) + square(rsy) + square(rsz);

  FT num_x = det3x3_by_formula(psy,psz,ps2,
                               qsy,qsz,qs2,
                               rsy,rsz,rs2);
  FT num_y = det3x3_by_formula(psx,psz,ps2,
                               qsx,qsz,qs2,
                               rsx,rsz,rs2);
  FT num_z = det3x3_by_formula(psx,psy,ps2,
                               qsx,qsy,qs2,
                               rsx,rsy,rs2);
  FT den   = det3x3_by_formula(psx,psy,psz,
                               qsx,qsy,qsz,
                               rsx,rsy,rsz);
  CGAL_kernel_assertion( den != FT(0) );
  FT inv = FT(1)/(FT(2) * den);

  x = sx + num_x*inv;
  y = sy - num_y*inv;
  z = sz + num_z*inv;
}

template <class FT>
CGAL_KERNEL_MEDIUM_INLINE
void
projectionC3(const FT &pa, const FT &pb, const FT &pc, const FT &pd,
             const FT &px, const FT &py, const FT &pz,
             FT &x, FT &y, FT &z)
{
  // the equation of the plane is Ax+By+Cz+D=0
  // the normal direction is (A,B,C)
  // the projected point is p-lambda(A,B,C) where
  // A(x-lambda A) + B(y-lambda B) + C(z-lambda C) + D = 0

  FT num = pa*px + pb*py + pc*pz + pd;
  FT den = pa*pa + pb*pb + pc*pc;
  FT lambda = num / den;

  x = px - lambda * pa;
  y = py - lambda * pb;
  z = pz - lambda * pc;
}


template < class FT >
CGAL_KERNEL_INLINE
FT
squared_distanceC3( const FT &px, const FT &py, const FT &pz,
                    const FT &qx, const FT &qy, const FT &qz)
{
  return square(px-qx) + square(py-qy) + square(pz-qz);
}

template < class FT >
CGAL_KERNEL_INLINE
FT
scaled_distance_to_directionC3(const FT &pa, const FT &pb, const FT &pc,
                               const FT &px, const FT &py)
{
  return pa*px + pb*py + pc*pz;
}

template < class FT >
CGAL_KERNEL_INLINE
FT
scaled_distance_to_planeC3(
     const FT &pa, const FT &pb, const FT &pc, const FT &pd,
     const FT &px, const FT &py)
{
  return pa*px + pb*py + pc*pz + pd;
}

template < class FT >
CGAL_KERNEL_INLINE
FT
scaled_distance_to_planeC3(
     const FT &ppx, const FT &ppy, const FT &ppz,
     const FT &pqx, const FT &pqy, const FT &pqz,
     const FT &prx, const FT &pry, const FT &prz,
     const FT &px,  const FT &py,  const FT &pz)
{
  return det3x3_by_formula(ppx-px,ppy-py,ppz-pz,
                           pqx-px,pqy-py,pqz-pz,
                           prx-px,pry-py,prz-pz);
}


CGAL_END_NAMESPACE

#endif // CGAL_BASIC_CONSTRUCTIONS_FTC3_H
