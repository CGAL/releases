// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : include/CGAL/constructions/squared_radius_smallest_orthogonalcircle_ftC2.h
// package       : Alpha_shapes_2 (5.5)
// source        : $RCSfile: squared_radius_smallest_orthogonalcircle_ftC2.h,v $
// revision      : $Revision: 1.4 $
// revision_date : $Date: 1999/11/05 16:37:40 $
// author(s)     : Tran Kai Frank DA
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_SQUARED_RADIUS_SMALLEST_ORTHOGONALCIRCLE_FTC2_H 
#define CGAL_SQUARED_RADIUS_SMALLEST_ORTHOGONALCIRCLE_FTC2_H

#include <CGAL/determinant.h>
#include <CGAL/enum.h>

//-------------------------------------------------------------------
CGAL_BEGIN_NAMESPACE
//-------------------------------------------------------------------

template< class FT >
CGAL_MEDIUM_INLINE
FT
squared_radius_orthogonalcircleC2(
  const FT &px, const FT &py, const FT  &pw,
  const FT &qx, const FT &qy, const FT  &qw,  
  const FT &rx, const FT &ry, const FT  &rw)

{
  FT FT4(4);
  FT dpx = px-rx;
  FT dpy = py-ry;
  FT dqx = qx-rx;
  FT dqy = qy-ry;
  FT dpp = square(dpx)+square(dpy)-pw+rw;
  FT dqq = square(dqx)+square(dqy)-qw+rw;

  FT det0 = det2x2_by_formula(dpx, dpy, dqx, dqy);
  
  FT det1 = det2x2_by_formula(dpp, dpy, dqq, dqy);

  FT det2 = det2x2_by_formula(dpx, dpp, dqx, dqq);

  return (square(det1)+square(det2))/(FT4*square(det0)) - rw;
}

template< class FT >
CGAL_MEDIUM_INLINE
FT
squared_radius_smallest_orthogonalcircleC2(
  const FT &px, const FT &py, const FT  &pw,
  const FT &qx, const FT &qy, const FT  &qw)

{
  FT FT4(4);
  FT dpz = square(px-qx)+square(py-qy);

  return (square(dpz-pw+qw)/(FT4*dpz)-qw);
}

//-------------------------------------------------------------------
CGAL_END_NAMESPACE
//-------------------------------------------------------------------

#endif //CGAL_SQUARED_RADIUS_SMALLEST_ORTHOGONALCIRCLE_ftC2_H
