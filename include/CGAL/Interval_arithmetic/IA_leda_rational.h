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
// file          : include/CGAL/Interval_arithmetic/IA_leda_rational.h
// package       : Interval_arithmetic (2.7)
// revision      : $Revision: 2.9 $
// revision_date : $Date: 1998/12/22 13:48:42 $
// author(s)     : Sylvain Pion
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_IA_LEDA_RATIONAL_H
#define CGAL_IA_LEDA_RATIONAL_H

// For this one, I hope that adding 3 ulps will be enough for an exact
// conversion.  Since LEDA types (except real) don't give information on the
// precision of to_double(), we can't do much...

template <>
inline
CGAL_Interval_nt_advanced
CGAL_convert_to <CGAL_Interval_nt_advanced> (const leda_rational &z)
{
#ifdef CGAL_IA_DEBUG
    CGAL_assertion(CGAL_FPU_get_rounding_mode() == CGAL_FPU_PLUS_INFINITY);
#endif
    CGAL_FPU_set_rounding_to_nearest();
    double approx = CGAL_to_double(z);
    CGAL_FPU_set_rounding_to_infinity();

    const CGAL_Interval_nt_advanced result =
	((CGAL_Interval_nt_advanced (approx)
	  + CGAL_Interval_nt_advanced::smallest)
	  + CGAL_Interval_nt_advanced::smallest)
	  + CGAL_Interval_nt_advanced::smallest;
// The following is bad because overflow is highly probable with rationals.
    // return CGAL_convert_to<CGAL_Interval_nt_advanced>(z.numerator())
	// /  CGAL_convert_to<CGAL_Interval_nt_advanced>(z.denominator());
#ifdef CGAL_IA_DEBUG
    CGAL_FPU_set_rounding_to_nearest();
    CGAL_assertion( leda_rational(result.lower_bound()) <= z &&
		    leda_rational(result.upper_bound()) >= z );
    CGAL_FPU_set_rounding_to_infinity();
#endif
    return result;
}

#endif	 // CGAL_IA_LEDA_RATIONAL_H
