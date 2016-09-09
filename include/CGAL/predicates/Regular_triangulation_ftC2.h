// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/predicates/Regular_triangulation_ftC2.h
// package       : Triangulation (4.69)
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2000/06/26 14:27:18 $
// author(s)     : Sylvain Pion
//                 Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_REGULAR_TRIANGULATION_FTC2_H
#define CGAL_REGULAR_TRIANGULATION_FTC2_H

// This file contains the low level cartesian predicates
// used by the 2D regular triangulation.

CGAL_BEGIN_NAMESPACE

template <class FT>
Oriented_side
power_testC2( const FT &px, const FT &py, const FT &pwt,
              const FT &qx, const FT &qy, const FT &qwt,
              const FT &rx, const FT &ry, const FT &rwt,
              const FT &tx, const FT &ty, const FT &twt)
{
    // Note: maybe this can be further optimized like the usual in_circle() ?

    // We translate the 4 points so that T becomes the origin.
    FT dpx = px - tx;
    FT dpy = py - ty;
    FT dpz = CGAL_NTS square(dpx) + CGAL_NTS square(dpy) - pwt + twt;
    FT dqx = qx - tx;
    FT dqy = qy - ty;
    FT dqz = CGAL_NTS square(dqx) + CGAL_NTS square(dqy) - qwt + twt;
    FT drx = rx - tx;
    FT dry = ry - ty;
    FT drz = CGAL_NTS square(drx) + CGAL_NTS square(dry) - rwt + twt;

    return Oriented_side(sign_of_determinant3x3(dpx, dpy, dpz,
                                                dqx, dqy, dqz,
                                                drx, dry, drz));
}


template <class FT>
Oriented_side
power_testC2( const FT &px, const FT &py, const FT &pwt,
	      const FT &qx, const FT &qy, const FT &qwt,
	      const FT &tx, const FT &ty, const FT &twt)
{
    // Same translation as above.
    FT dpx = px - tx;
    FT dpy = py - ty;
    FT dpz = CGAL_NTS square(dpx) + CGAL_NTS square(dpy) - pwt + twt;
    FT dqx = qx - tx;
    FT dqy = qy - ty;
    FT dqz = CGAL_NTS square(dqx) + CGAL_NTS square(dqy) - qwt + twt;

    // We do an orthogonal projection on the (x) axis, if possible.
    Comparison_result cmpx = CGAL_NTS compare(px, qx);
    if (cmpx != EQUAL)
	return Oriented_side(cmpx * sign_of_determinant2x2(dpx, dpz, dqx, dqz));

    // If not possible, then on the (y) axis.
    Comparison_result cmpy = CGAL_NTS compare(py, qy);
    return Oriented_side(cmpy * sign_of_determinant2x2(dpy, dpz, dqy, dqz));
}

CGAL_END_NAMESPACE

#ifdef CGAL_ARITHMETIC_FILTER_H
#ifndef CGAL_ARITHMETIC_FILTER_REGULAR_TRIANGULATION_FTC2_H
#include <CGAL/Arithmetic_filter/predicates/Regular_triangulation_ftC2.h>
#endif // CGAL_ARITHMETIC_FILTER_REGULAR_TRIANGULATION_FTC2_H
#endif

#endif // CGAL_REGULAR_TRIANGULATION_FTC2_H
