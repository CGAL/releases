// Copyright (c) 1997  INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source: /CVSROOT/CGAL/Packages/Alpha_shapes_3/include/CGAL/predicates/in_smallest_orthogonalsphere_ftC3.h,v $
// $Revision: 1.2 $ $Date: 2003/09/18 10:19:18 $
// $Name: current_submission $
//
// Author(s)     : Tran Kai Frank DA <Frank.Da@sophia.inria.fr>

#ifndef CGAL_IN_SMALLEST_ORTHOGONALSPHERE_FTC3_H 
#define CGAL_IN_SMALLEST_ORTHOGONALSPHERE_FTC3_H

#include <CGAL/determinant.h>
#include <CGAL/enum.h>

//-------------------------------------------------------------------
CGAL_BEGIN_NAMESPACE
//-------------------------------------------------------------------

template< class FT >
CGAL_MEDIUM_INLINE
Bounded_side
in_smallest_orthogonalsphereC3(
  const FT &px, const FT &py, const FT &pz, const FT  &pw,
  const FT &qx, const FT &qy, const FT &qz, const FT  &qw,
  const FT &rx, const FT &ry, const FT &rz, const FT  &rw,
  const FT &tx, const FT &ty, const FT &tz, const FT  &tw)
{
  FT dpx = px-rx;
  FT dpy = py-ry;
  FT dpz = pz-rz;
  FT dp = CGAL_NTS square(dpx)+CGAL_NTS square(dpy)+CGAL_NTS square(dpz);
  FT dpp = dp-pw+rw;
  FT dqx = qx-rx;
  FT dqy = qy-ry;
  FT dqz = qz-rz;
  FT dq = CGAL_NTS square(dqx)+CGAL_NTS square(dqy)+CGAL_NTS square(dqz);
  FT dqq = dq-qw+rw;
  FT dpdq = dpx*dqx+dpy*dqy+dpz*dqz;
  FT denom = dp*dq-CGAL_NTS square(dpdq);
  FT Lambda = (dpp*dq-dqq*dpdq)/denom;
  FT Mu = (dqq*dp-dpp*dpdq)/denom;
  
  FT dtx = tx-rx;
  FT dty = ty-ry;
  FT dtz = tz-rz;
  
  return Bounded_side 
    (CGAL_NTS sign(
	-(CGAL_NTS square(dtx)+CGAL_NTS square(dty)+CGAL_NTS square(dtz)-tw+rw)
        +Lambda*(dpx*dtx+dpy*dty+dpz*dtz)+Mu*(dqx*dtx+dqy*dty+dqz*dtz)));
}

//-------------------------------------------------------------------
CGAL_END_NAMESPACE
//-------------------------------------------------------------------

#endif //CGAL_IN_SMALLEST_ORTHOGONALSPHEREC3_H
