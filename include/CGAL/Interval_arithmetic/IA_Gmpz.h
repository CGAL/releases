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
// file          : include/CGAL/Interval_arithmetic/IA_Gmpz.h
// package       : Interval_arithmetic (4.58)
// revision      : $Revision: 2.36 $
// revision_date : $Date: 2000/09/01 16:43:21 $
// author(s)     : Sylvain Pion
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_IA_GMPZ_H
#define CGAL_IA_GMPZ_H

#include <CGAL/Quotient.h> // Just for the converter double -> Quotient<Gmpz>.
#include <CGAL/double.h>   // for is_integral().

CGAL_BEGIN_NAMESPACE

// We choose the lazy approach, which is good enough: we take the double
// approximation, which is guaranted 1 bit error max (when rounding to
// nearest), and return an interval around this value.
// It could be better to have a low level function especially designed
// for that using rounding to infinity.

#if 0
inline // better in libCGAL...
Interval_base
to_interval(const Gmpz & z)
{
  Protect_FPU_rounding<> P(CGAL_FE_TONEAREST);
  Interval_nt_advanced approx (CGAL::to_double(z));
  FPU_set_cw(CGAL_FE_UPWARD);
  return approx + Interval_base::Smallest;
}
#endif

inline
Interval_nt_advanced
convert_from_to (const Interval_nt_advanced&, const Gmpz & z)
{
	CGAL_expensive_assertion(FPU_empiric_test() == CGAL_FE_UPWARD);
	FPU_set_cw(CGAL_FE_TONEAREST);
	double approx = CGAL::to_double(z);
	FPU_set_cw(CGAL_FE_UPWARD);
	Interval_nt_advanced result = Interval_nt_advanced(approx) +
	       	Interval_nt_advanced::Smallest;
	CGAL_expensive_assertion_code(FPU_set_cw(CGAL_FE_TONEAREST);)
	CGAL_expensive_assertion(Gmpz(result.inf()) <= z &&
		                 Gmpz(result.sup()) >= z);
	CGAL_expensive_assertion_code(FPU_set_cw(CGAL_FE_UPWARD);)
	return result;
}

template <>
struct converter<Interval_nt_advanced,Gmpz>
{
    static inline Interval_nt_advanced do_it (const Gmpz & z)
    {
	return convert_from_to(Interval_nt_advanced(), z);
    }
};

// Now we also have an exact converter from double to Quotient<Gmpz>, so that
// Filtered_exact<double, Quotient<Gmpz> > is useful.

inline
Quotient<Gmpz>
convert_from_to (const Quotient<Gmpz>&, const double& d)
{ 
  // We multiply the value by 2, until it reaches an integral value.
  // Then it can be converted exactly to a Gmpz.
  // Note: it's not really optimized (it'll do 1000 iterations at worst).
  double num=d;
  double den=1.0;
  while ( ! is_integral(num) )
  {
    den*=2.0;
    num*=2.0;
  }
  return Quotient<Gmpz>(Gmpz(num), Gmpz(den));
}

template <>
struct converter<Quotient<Gmpz>,double>
{
  static inline Quotient<Gmpz> do_it (const double & z)
  { return convert_from_to(Quotient<Gmpz>(), z); }
};

CGAL_END_NAMESPACE

#endif // CGAL_IA_GMPZ_H
