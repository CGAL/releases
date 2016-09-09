// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// file          : include/CGAL/predicates/Regular_triangulation_rtH2.h
// package       : Triangulation_2 (7.32)
// revision      : $Revision: 1.5 $
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

#ifndef CGAL_REGULAR_TRIANGULATION_RTH2_H
#define CGAL_REGULAR_TRIANGULATION_RTH2_H

// This file contains the low level homogeneous predicates
// used by the 2D regular triangulation.

CGAL_BEGIN_NAMESPACE

template <class RT>
Oriented_side
power_testH2( const RT &phx, const RT &phy, const RT &phw, const RT &pwt,
              const RT &qhx, const RT &qhy, const RT &qhw, const RT &qwt,
              const RT &rhx, const RT &rhy, const RT &rhw, const RT &rwt,
              const RT &thx, const RT &thy, const RT &thw, const RT &twt)
{
    RT dphx = phx*phw;
    RT dphy = phy*phw;
    RT dphw = CGAL_NTS square(phw);
    RT dpz = CGAL_NTS square(phx) + CGAL_NTS square(phy) - pwt*dphw;

    RT dqhx = qhx*qhw;
    RT dqhy = qhy*qhw;
    RT dqhw = CGAL_NTS square(qhw);
    RT dqz = CGAL_NTS square(qhx) + CGAL_NTS square(qhy) - qwt*dqhw;

    RT drhx = rhx*rhw;
    RT drhy = rhy*rhw;
    RT drhw = CGAL_NTS square(rhw);
    RT drz = CGAL_NTS square(rhx) + CGAL_NTS square(rhy) - rwt*drhw;

    RT dthx = thx*thw;
    RT dthy = thy*thw;
    RT dthw = CGAL_NTS square(thw);
    RT dtz = CGAL_NTS square(thx) + CGAL_NTS square(thy) - twt*dthw;

    return Oriented_side(sign_of_determinant4x4(dphx, dphy, dpz, dphw,
	                                        dqhx, dqhy, dqz, dqhw,
	                                        drhx, drhy, drz, drhw,
	                                        dthx, dthy, dtz, dthw));
}


template <class RT>
Oriented_side
power_testH2( const RT &phx, const RT &phy, const RT &phw, const RT &pwt,
              const RT &qhx, const RT &qhy, const RT &qhw, const RT &qwt,
              const RT &thx, const RT &thy, const RT &thw, const RT &twt)
{
    // Test if we can project on the (x) axis.  If not, then on the
    // (y) axis
    RT pa, qa, ta;

    if (phx * qhw != qhx * phw )
    {
	pa = phx*phw;
	qa = qhx*qhw;
	ta = thx*thw;
    }
    else
    {   
	pa = phy*phw;
	qa = qhy*qhw;
	ta = thy*thw;
    }

    RT dphw = CGAL_NTS square(phw);
    RT dpz = CGAL_NTS square(phx) + CGAL_NTS square(phy) - pwt*dphw;

    RT dqhw = CGAL_NTS square(qhw);
    RT dqz = CGAL_NTS square(qhx) + CGAL_NTS square(qhy) - qwt*dqhw;

    RT dthw = CGAL_NTS square(thw);
    RT dtz = CGAL_NTS square(thx) + CGAL_NTS square(thy) - twt*dthw;

    return Oriented_side(CGAL_NTS compare(pa, qa) *
	                 sign_of_determinant3x3(pa, dpz, dphw,
				                qa, dqz, dqhw,
				                ta, dtz, dthw));
}

CGAL_END_NAMESPACE

#ifdef CGAL_ARITHMETIC_FILTER_H
#ifndef CGAL_ARITHMETIC_FILTER_REGULAR_TRIANGULATION_RTH2_H
#include <CGAL/Arithmetic_filter/predicates/Regular_triangulation_rtH2.h>
#endif // CGAL_ARITHMETIC_FILTER_REGULAR_TRIANGULATION_RTH2_H
#endif

#endif // CGAL_REGULAR_TRIANGULATION_RTH2_H
