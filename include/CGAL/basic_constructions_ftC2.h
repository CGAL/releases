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
// file          : include/CGAL/basic_constructions_ftC2.h
// package       : C2 (2.1.4)
// source        : web/basic_constructionsC2.fw
// revision      : $Revision: 1.17 $
// revision_date : $Date: 1999/05/24 06:43:34 $
// author(s)     : Sven Schoenherr
//                 Herve Bronnimann
//                 Sylvain Pion
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_BASIC_CONSTRUCTIONS_FTC2_H
#define CGAL_BASIC_CONSTRUCTIONS_FTC2_H

#ifndef CGAL_DETERMINANT_H
#include <CGAL/determinant.h>
#endif

CGAL_BEGIN_NAMESPACE

template < class FT >
CGAL_KERNEL_INLINE
void
midpointC2( const FT &px, const FT& py,
            const FT &qx, const FT &qy,
            FT &x, FT &y )
{
  FT FT1_2 = FT(1) / FT(2);
  x = (px+qx) * FT1_2;
  y = (py+qy) * FT1_2;
}
template < class FT >
CGAL_KERNEL_LARGE_INLINE
void
circumcenterC2( const FT &px, const FT &py,
                const FT &qx, const FT &qy,
                const FT &rx, const FT &ry,
                FT &x, FT &y )
{
  // We translate everything, so that P becomes the origin.
  FT dqx = qx - px;
  FT dqy = qy - py;
  FT drx = rx - px;
  FT dry = ry - py;

  FT r2 = square(drx) + square(dry);
  FT q2 = square(dqx) + square(dqy);

  FT den = drx * dqy - dry * dqx;

  // The 3 points aren't collinear.
  // Hopefully, this is already checked at the upper level.
  CGAL_kernel_assertion ( den != FT(0) );

  // Precompute the inverse => only one division (though we loose precision).
  // IMHO, we should allow FT(double) for FTs (for Cartesian) !!!
  // What we must do here is pretty stupid, I'd like FT(0.5)/den.
  x = y = FT(1) / ( FT(2) * den );

  // And we translate it back.
  x = px + x * ( dqy * r2 - dry * q2 );
  y = py + y * ( drx * q2 - dqx * r2 );
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
FT
squared_circumradiusC2(const FT &px, const FT &py,
                       const FT &qx, const FT &qy,
                       const FT &rx, const FT &ry,
                       FT &x, FT &y )
{
  // We translate everything, so that P becomes the origin.
  FT dqx = qx - px;
  FT dqy = qy - py;
  FT drx = rx - px;
  FT dry = ry - py;

  FT r2 = square(drx) + square(dry);
  FT q2 = square(dqx) + square(dqy);

  FT den = drx * dqy - dry * dqx;

  // The 3 points aren't collinear.
  // Hopefully, this is already checked at the upper level.
  CGAL_kernel_assertion ( den != FT(0) );

  // Precompute the inverse => only one division (though we loose precision).
  // IMHO, we should allow FT(double) for FTs (for Cartesian) !!!
  // What we must do here is pretty stupid, I'd like FT(0.5)/den.
  x = y = square( FT(1) / ( FT(2) * den ));
  cx = dqy * r2 - dry * q2;
  cy = drx * q2 - dqx * r2;

  // And we translate it back.
  x = px + x * cx;
  y = py + y * cy;
  return (square(cx)+square(cy))* square(x);
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
FT
squared_circumradiusC2(const FT &px, const FT &py,
                       const FT &qx, const FT &qy,
                       const FT &rx, const FT &ry)
{
  FT x, y;
  return squared_circumradiusC2(px,py,qx,qy,rx,ry,x,y);
}


template < class FT >
CGAL_KERNEL_INLINE
FT
squared_distanceC2( const FT &px, const FT &py,
                    const FT &qx, const FT &qy)
{
  return square(px-qx) + square(py-qy);
}

template < class FT >
CGAL_KERNEL_INLINE
FT
scaled_distance_to_lineC2( const FT &la, const FT &lb, const FT &lc,
                           const FT &px, const FT &py)
{
  // we'd like not to add lc because it is irrelevant for comparisons
  // but it would make scaled_dist_to_line counter-intuitive
  // and inconsistent with distance to implicit line (below)
  return la*px + lb*py + lc;
}

template < class FT >
CGAL_KERNEL_INLINE
FT
scaled_distance_to_directionC2( const FT &la, const FT &lb,
                                const FT &px, const FT &py)
{
  // this is the fix for not adding lc in the function above
  return la*px + lb*py;
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
FT
scaled_distance_to_lineC2( const FT &px, const FT &py,
                           const FT &qx, const FT &qy,
                           const FT &rx, const FT &ry)
{
  return det2x2_by_formula(px-rx,py-ry,qx-rx,qy-ry);
}


CGAL_END_NAMESPACE

#endif // CGAL_BASIC_CONSTRUCTIONS_FTC2_H
