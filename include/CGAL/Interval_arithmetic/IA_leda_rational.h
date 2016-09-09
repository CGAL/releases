// ======================================================================
//
// Copyright (c) 1998,1999,2000 The CGAL Consortium

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
// file          : include/CGAL/Interval_arithmetic/IA_leda_rational.h
// package       : Interval_arithmetic (4.58)
// revision      : $Revision: 2.30 $
// revision_date : $Date: 2000/09/01 16:43:22 $
// author(s)     : Sylvain Pion
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_IA_LEDA_RATIONAL_H
#define CGAL_IA_LEDA_RATIONAL_H

CGAL_BEGIN_NAMESPACE

// For this one, I hope that adding 3 ulps will be enough for a safe
// conversion.  Since LEDA types (except real) don't give information on the
// precision of to_double(), we can't do much...

#if 0
inline // well, at that point...  big fat function.
Interval_base
to_interval (const leda_rational & z)
{
  Protect_FPU_rounding<> P (CGAL_FE_TONEAREST);
  Interval_nt_advanced approx (z.to_double());
  FPU_set_cw(CGAL_FE_UPWARD);

  return ( (approx + Interval_base::Smallest) + Interval_base::Smallest)
	 + Interval_base::Smallest;
}
#endif

inline
Interval_nt_advanced
convert_from_to (const Interval_nt_advanced&, const leda_rational & z)
{
    CGAL_expensive_assertion(FPU_empiric_test() == CGAL_FE_UPWARD);
    FPU_set_cw(CGAL_FE_TONEAREST);
    double approx = CGAL::to_double(z);
    FPU_set_cw(CGAL_FE_UPWARD);

    Interval_nt_advanced result = Interval_nt_advanced(approx) +
	    Interval_nt_advanced::Smallest;
    // We play it safe:
    result += Interval_nt_advanced::Smallest;
    result += Interval_nt_advanced::Smallest;
    CGAL_expensive_assertion_code(FPU_set_cw(CGAL_FE_TONEAREST);)
    CGAL_expensive_assertion( leda_rational(result.inf()) <= z &&
		              leda_rational(result.sup()) >= z );
    CGAL_expensive_assertion_code(FPU_set_cw(CGAL_FE_UPWARD);)
    return result;
}

template <>
struct converter<Interval_nt_advanced,leda_rational>
{
    static inline Interval_nt_advanced do_it (const leda_rational & z)
    {
	return convert_from_to(Interval_nt_advanced(), z);
    }
};

CGAL_END_NAMESPACE

#endif // CGAL_IA_LEDA_RATIONAL_H
