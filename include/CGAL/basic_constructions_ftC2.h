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
// file          : include/CGAL/basic_constructions_ftC2.h
// package       : C2 (1.7)
// source        : web/basic_constructionsC2.fw
// revision      : $Revision: 1.7 $
// revision_date : $Date: 1999/01/04 06:54:15 $
// author(s)     : Sven Schoenherr
//                 Herve Bronnimann
//
// coordinator   : INRIA Sophia-Antipolis
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_BASIC_CONSTRUCTIONS_FTC2_H
#define CGAL_BASIC_CONSTRUCTIONS_FTC2_H 1

#ifndef CGAL_DETERMINANT_H
#include <CGAL/determinant.h>
#endif

template < class FT >
CGAL_KERNEL_INLINE
void
CGAL_midpointC2( const FT &px, const FT& py,
                 const FT &qx, const FT &qy,
                 FT &x, FT &y )
{
  const FT FT2(2);
  x = (px+qx) / FT2;
  y = (py+qy) / FT2;
}
template < class FT >
CGAL_KERNEL_LARGE_INLINE
void
CGAL_circumcenterC2( const FT &px, const FT& py,
                     const FT &qx, const FT &qy,
                     const FT &rx, const FT &ry,
                     FT &x, FT &y )
{
    const FT px_qx( px - qx);
    const FT py_qy( py - qy);
    const FT qx_rx( qx - rx);
    const FT qy_ry( qy - ry);
    const FT rx_px( rx - px);
    const FT ry_py( ry - py);

    const FT p2( px*px + py*py);
    const FT q2( qx*qx + qy*qy);
    const FT r2( rx*rx + ry*ry);

    const FT num_x( p2*qy_ry + q2*ry_py + r2*py_qy);
    const FT num_y( p2*qx_rx + q2*rx_px + r2*px_qx);

    const FT den_x( ( px*qy_ry + qx*ry_py + rx*py_qy) * FT( 2));
    CGAL_kernel_assertion( den_x != FT(0) );
    const FT den_y( ( py*qx_rx + qy*rx_px + ry*px_qx) * FT( 2));
    CGAL_kernel_assertion( den_y != FT(0) );

    x = num_x / den_x;
    y = num_y / den_y;
}


template < class FT >
CGAL_KERNEL_INLINE
FT
CGAL_squared_distanceC2( const FT &px, const FT &py,
                         const FT &qx, const FT &qy)
{
  const FT x = px - qx;
  const FT y = py - qy;
  return( x*x + y*y );
}

template < class FT >
CGAL_KERNEL_INLINE
FT
CGAL_scaled_distance_to_lineC2( const FT &la, const FT &lb, const FT &lc,
                                const FT &px, const FT &py)
{
  // we'd like not to add lc because it is irrelevant for comparisons
  // but it would make scaled_dist_to_line counter-intuitive
  // and inconsistent with distance to implicit line (below)
  return la*px + lb*py + lc;
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
FT
CGAL_scaled_distance_to_lineC2( const FT &px, const FT &py,
                                const FT &qx, const FT &qy,
                                const FT &rx, const FT &ry)
{
  return CGAL_det2x2_by_formula(px-rx,py-ry,qx-rx,qy-ry);
}


#endif // CGAL_BASIC_CONSTRUCTIONS_FTC2_H
