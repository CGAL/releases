// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/predicates/in_smallest_orthogonalcircle_ftC2.h
// package       : Alpha_shapes_2 (11.19)
// source        : $RCSfile: in_smallest_orthogonalcircle_ftC2.h,v $
// revision      : $Revision: 1.6 $
// revision_date : $Date: 2000/07/11 16:16:23 $
// author(s)     : Tran Kai Frank DA
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_IN_SMALLEST_ORTHOGONALCIRCLE_FTC2_H 
#define CGAL_IN_SMALLEST_ORTHOGONALCIRCLE_FTC2_H

#include <CGAL/determinant.h>
#include <CGAL/enum.h>

//-------------------------------------------------------------------
CGAL_BEGIN_NAMESPACE
//-------------------------------------------------------------------

template< class FT >
CGAL_MEDIUM_INLINE
Bounded_side
in_smallest_orthogonalcircleC2(const FT &px, const FT &py, const FT  &pw,
			       const FT &qx, const FT &qy, const FT  &qw,  
			       const FT &tx, const FT &ty, const FT  &tw)
{
  FT dpx = px-qx;
  FT dpy = py-qy;
  FT dtx = tx-qx;
  FT dty = ty-qy;
  FT dpz = CGAL_NTS square(dpx)+CGAL_NTS square(dpy);
 
  return Bounded_side 
    (CGAL_NTS sign(-(CGAL_NTS square(dtx)+CGAL_NTS square(dty)-tw+qw)*dpz
		   +(dpz-pw+qw)*(dpx*dtx+dpy*dty)));
}

//-------------------------------------------------------------------
CGAL_END_NAMESPACE
//-------------------------------------------------------------------

#endif //CGAL_IN_SMALLEST_ORTHOGONALCIRCLEC2_H
