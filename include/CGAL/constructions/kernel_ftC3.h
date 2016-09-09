// Copyright (c) 2000  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source: /CVSROOT/CGAL/Packages/Cartesian_kernel/include/CGAL/constructions/kernel_ftC3.h,v $
// $Revision: 1.11 $ $Date: 2003/10/21 12:14:38 $
// $Name: current_submission $
//
// Author(s)     : Herve Bronnimann

#ifndef CGAL_CONSTRUCTIONS_KERNEL_FTC3_H
#define CGAL_CONSTRUCTIONS_KERNEL_FTC3_H

#include <CGAL/determinant.h>

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
  // Translate p to origin to simplify the expression.
  FT qpx = qx-px;
  FT qpy = qy-py;
  FT qpz = qz-pz;
  FT qp2 = CGAL_NTS square(qpx) + CGAL_NTS square(qpy) + CGAL_NTS square(qpz);
  FT rpx = rx-px;
  FT rpy = ry-py;
  FT rpz = rz-pz;
  FT rp2 = CGAL_NTS square(rpx) + CGAL_NTS square(rpy) + CGAL_NTS square(rpz);
  FT spx = sx-px;
  FT spy = sy-py;
  FT spz = sz-pz;
  FT sp2 = CGAL_NTS square(spx) + CGAL_NTS square(spy) + CGAL_NTS square(spz);

  FT num_x = det3x3_by_formula(qpy,qpz,qp2,
                               rpy,rpz,rp2,
                               spy,spz,sp2);
  FT num_y = det3x3_by_formula(qpx,qpz,qp2,
                               rpx,rpz,rp2,
                               spx,spz,sp2);
  FT num_z = det3x3_by_formula(qpx,qpy,qp2,
                               rpx,rpy,rp2,
                               spx,spy,sp2);
  FT den   = det3x3_by_formula(qpx,qpy,qpz,
                               rpx,rpy,rpz,
                               spx,spy,spz);
  CGAL_kernel_assertion( ! CGAL_NTS is_zero(den) );
  FT inv = FT(1)/(FT(2) * den);

  x = px + num_x*inv;
  y = py - num_y*inv;
  z = pz + num_z*inv;
}

template < class FT >
void
circumcenterC3( const FT &px, const FT &py, const FT &pz,
                const FT &qx, const FT &qy, const FT &qz,
                const FT &sx, const FT &sy, const FT &sz,
                FT &x, FT &y, FT &z)
{
  // Translate s to origin to simplify the expression.
  FT psx = px-sx;
  FT psy = py-sy;
  FT psz = pz-sz;
  FT ps2 = CGAL_NTS square(psx) + CGAL_NTS square(psy) + CGAL_NTS square(psz);
  FT qsx = qx-sx;
  FT qsy = qy-sy;
  FT qsz = qz-sz;
  FT qs2 = CGAL_NTS square(qsx) + CGAL_NTS square(qsy) + CGAL_NTS square(qsz);
  FT rsx = psy*qsz-psz*qsy;
  FT rsy = psz*qsx-psx*qsz;
  FT rsz = psx*qsy-psy*qsx;

  // The following determinants can be developped and simplified.
  //
  // FT num_x = det3x3_by_formula(psy,psz,ps2,
  //                              qsy,qsz,qs2,
  //                              rsy,rsz,FT(0));
  // FT num_y = det3x3_by_formula(psx,psz,ps2,
  //                              qsx,qsz,qs2,
  //                              rsx,rsz,FT(0));
  // FT num_z = det3x3_by_formula(psx,psy,ps2,
  //                              qsx,qsy,qs2,
  //                              rsx,rsy,FT(0));

  FT num_x = ps2 * det2x2_by_formula(qsy,qsz,rsy,rsz)
	   - qs2 * det2x2_by_formula(psy,psz,rsy,rsz);
  FT num_y = ps2 * det2x2_by_formula(qsx,qsz,rsx,rsz)
	   - qs2 * det2x2_by_formula(psx,psz,rsx,rsz);
  FT num_z = ps2 * det2x2_by_formula(qsx,qsy,rsx,rsy)
	   - qs2 * det2x2_by_formula(psx,psy,rsx,rsy);

  FT den   = det3x3_by_formula(psx,psy,psz,
                               qsx,qsy,qsz,
                               rsx,rsy,rsz);

  CGAL_kernel_assertion( den != FT(0) );
  FT inv = FT(1)/(FT(2) * den);

  x = sx + num_x*inv;
  y = sy - num_y*inv;
  z = sz + num_z*inv;
}

template < class FT >
void
centroidC3( const FT &px, const FT &py, const FT &pz,
            const FT &qx, const FT &qy, const FT &qz,
            const FT &rx, const FT &ry, const FT &rz,
            const FT &sx, const FT &sy, const FT &sz,
            FT &x, FT &y, FT &z)
{
   x = (px + qx + rx + sx)/FT(4);
   y = (py + qy + ry + sy)/FT(4);
   z = (pz + qz + rz + sz)/FT(4);
}

template < class FT >
void
centroidC3( const FT &px, const FT &py, const FT &pz,
            const FT &qx, const FT &qy, const FT &qz,
            const FT &rx, const FT &ry, const FT &rz,
            FT &x, FT &y, FT &z)
{
   x = (px + qx + rx)/FT(3);
   y = (py + qy + ry)/FT(3);
   z = (pz + qz + rz)/FT(3);
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
FT
squared_radiusC3(const FT &px, const FT &py, const FT &pz,
                       const FT &qx, const FT &qy, const FT &qz,
                       const FT &rx, const FT &ry, const FT &rz,
                       const FT &sx, const FT &sy, const FT &sz)
{
  // Translate p to origin to simplify the expression.
  FT qpx = qx-px;
  FT qpy = qy-py;
  FT qpz = qz-pz;
  FT qp2 = CGAL_NTS square(qpx) + CGAL_NTS square(qpy) + CGAL_NTS square(qpz);
  FT rpx = rx-px;
  FT rpy = ry-py;
  FT rpz = rz-pz;
  FT rp2 = CGAL_NTS square(rpx) + CGAL_NTS square(rpy) + CGAL_NTS square(rpz);
  FT spx = sx-px;
  FT spy = sy-py;
  FT spz = sz-pz;
  FT sp2 = CGAL_NTS square(spx) + CGAL_NTS square(spy) + CGAL_NTS square(spz);

  FT num_x = det3x3_by_formula(qpy,qpz,qp2,
                               rpy,rpz,rp2,
                               spy,spz,sp2);
  FT num_y = det3x3_by_formula(qpx,qpz,qp2,
                               rpx,rpz,rp2,
                               spx,spz,sp2);
  FT num_z = det3x3_by_formula(qpx,qpy,qp2,
                               rpx,rpy,rp2,
                               spx,spy,sp2);
  FT den   = det3x3_by_formula(qpx,qpy,qpz,
                               rpx,rpy,rpz,
                               spx,spy,spz);
  CGAL_kernel_assertion( ! CGAL_NTS is_zero(den) );

  return (CGAL_NTS square(num_x) + CGAL_NTS square(num_y)
        + CGAL_NTS square(num_z)) / CGAL_NTS square<FT>(FT(2) * den);
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
FT
squared_radiusC3(const FT &px, const FT &py, const FT &pz,
                       const FT &qx, const FT &qy, const FT &qz,
                       const FT &sx, const FT &sy, const FT &sz)
{
  // Translate s to origin to simplify the expression.
  FT psx = px-sx;
  FT psy = py-sy;
  FT psz = pz-sz;
  FT ps2 = CGAL_NTS square(psx) + CGAL_NTS square(psy) + CGAL_NTS square(psz);
  FT qsx = qx-sx;
  FT qsy = qy-sy;
  FT qsz = qz-sz;
  FT qs2 = CGAL_NTS square(qsx) + CGAL_NTS square(qsy) + CGAL_NTS square(qsz);
  FT rsx = psy*qsz-psz*qsy;
  FT rsy = psz*qsx-psx*qsz;
  FT rsz = psx*qsy-psy*qsx;

  FT num_x = ps2 * det2x2_by_formula(qsy,qsz,rsy,rsz)
	   - qs2 * det2x2_by_formula(psy,psz,rsy,rsz);
  FT num_y = ps2 * det2x2_by_formula(qsx,qsz,rsx,rsz)
	   - qs2 * det2x2_by_formula(psx,psz,rsx,rsz);
  FT num_z = ps2 * det2x2_by_formula(qsx,qsy,rsx,rsy)
	   - qs2 * det2x2_by_formula(psx,psy,rsx,rsy);

  FT den   = det3x3_by_formula(psx,psy,psz,
                               qsx,qsy,qsz,
                               rsx,rsy,rsz);

  CGAL_kernel_assertion( den != FT(0) );

  return (CGAL_NTS square(num_x) + CGAL_NTS square(num_y)
        + CGAL_NTS square(num_z)) / CGAL_NTS square<FT>(FT(2) * den);
}

template <class FT>
CGAL_KERNEL_MEDIUM_INLINE
void
point_on_lineC3(const FT &lpx, const FT &lpy, const FT &lpz,
                const FT &ldx, const FT &ldy, const FT &ldz,
		int i,
                FT &x, FT &y, FT &z)
{
  x = lpx + ldx*FT(i);
  y = lpy + ldy*FT(i);
  z = lpz + ldz*FT(i);
}

template <class FT>
CGAL_KERNEL_MEDIUM_INLINE
void
projection_lineC3(const FT &px, const FT &py, const FT &pz,
                  const FT &lpx, const FT &lpy, const FT &lpz,
                  const FT &ldx, const FT &ldy, const FT &ldz,
                  FT &x, FT &y, FT &z)
{
  // projects p on the line l
  FT dpx = px-lpx;
  FT dpy = py-lpy;
  FT dpz = pz-lpz;
  FT lambda = (ldx*dpx+ldy*dpy+ldz*dpz) / (ldx*ldx+ldy*ldy+ldz*ldz);
  x = lpx + lambda * ldx;
  y = lpy + lambda * ldy;
  z = lpz + lambda * ldz;
}

template <class FT> 
CGAL_KERNEL_MEDIUM_INLINE
void            
plane_from_pointsC3(const FT &px, const FT &py, const FT &pz,
                    const FT &qx, const FT &qy, const FT &qz,
                    const FT &rx, const FT &ry, const FT &rz,
		    FT &pa, FT &pb, FT &pc, FT &pd)
{
  FT rpx = px-rx;
  FT rpy = py-ry;
  FT rpz = pz-rz;
  FT rqx = qx-rx;
  FT rqy = qy-ry;
  FT rqz = qz-rz;
  // Cross product rp * rq
  pa = rpy*rqz - rqy*rpz;
  pb = rpz*rqx - rqz*rpx;
  pc = rpx*rqy - rqx*rpy;
  pd = - pa*rx - pb*ry - pc*rz;
}

template <class FT>
CGAL_KERNEL_MEDIUM_INLINE
void
plane_from_point_directionC3(const FT &px, const FT &py, const FT &pz,
                             const FT &dx, const FT &dy, const FT &dz,
                             FT &pa, FT &pb, FT &pc, FT &pd)
{
  // d is the normal direction
  pa = dx; pb = dy; pc = dz; pd = -dx*px - dy*py - dz*pz;
}

template <class FT>
CGAL_KERNEL_MEDIUM_INLINE
void
point_on_planeC3(const FT &pa, const FT &pb, const FT &pc, const FT &pd,
                 FT &x, FT &y, FT &z)
{
  x = y = z = FT(0);
  if (! CGAL_NTS is_zero(pa))      x = -pd/pa;
  else if (! CGAL_NTS is_zero(pb)) y = -pd/pb;
  else                  z = -pd/pc;
}

template <class FT>
CGAL_KERNEL_MEDIUM_INLINE
void
projection_planeC3(const FT &pa, const FT &pb, const FT &pc, const FT &pd,
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
  return CGAL_NTS square<FT>(px-qx) + CGAL_NTS square<FT>(py-qy) +
	 CGAL_NTS square<FT>(pz-qz);
}

template < class FT >
CGAL_KERNEL_INLINE
FT
squared_radiusC3( const FT &px, const FT &py, const FT &pz,
                  const FT &qx, const FT &qy, const FT &qz)
{
  return squared_distanceC3(px, py, pz, qx, qy, qz)/FT(4);
}

template < class FT >
CGAL_KERNEL_INLINE
FT
scaled_distance_to_directionC3(const FT &pa, const FT &pb, const FT &pc,
                               const FT &px, const FT &py, const FT &pz)
{
  return pa*px + pb*py + pc*pz;
}

template < class FT >
CGAL_KERNEL_INLINE
FT
scaled_distance_to_planeC3(
     const FT &pa, const FT &pb, const FT &pc, const FT &pd,
     const FT &px, const FT &py, const FT &pz)
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

#endif // CGAL_CONSTRUCTIONS_KERNEL_FTC3_H
