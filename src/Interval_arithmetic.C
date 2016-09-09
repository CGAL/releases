// ======================================================================
//
// Copyright (c) 1999,2000 The CGAL Consortium

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
// file          : src/Interval_arithmetic.C
// package       : Interval_arithmetic (4.141)
// revision      : $Revision: 1.24 $
// revision_date : $Date: 2001/06/20 19:00:51 $
// author(s)     : Sylvain Pion
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 
#include <CGAL/basic.h>
#include <CGAL/Interval_base.h>

// M$ VC++ doesn't like them yet.
#ifdef CGAL_IA_NEW_FILTERS
#include <CGAL/predicates/kernel_ftC2.h>
#include <CGAL/predicates/kernel_ftC3.h>
#include <CGAL/predicates/sign_of_determinant.h>
#include <CGAL/predicates/Regular_triangulation_ftC2.h>
#include <CGAL/predicates/Regular_triangulation_ftC3.h>
#include <CGAL/predicates/Regular_triangulation_rtH2.h>
#include <CGAL/predicates/Regular_triangulation_rtH3.h>
#endif

#include <CGAL/Filtered_exact.h>

CGAL_BEGIN_NAMESPACE

// Static variables:
#ifdef CGAL_IA_NEW_FILTERS
#include <CGAL/Arithmetic_filter/static_infos/dispatch.h>
#endif

unsigned Interval_base::number_of_failures;

const Interval_base Interval_base::Largest (-HUGE_VAL, HUGE_VAL);
const Interval_base Interval_base::Smallest (-CGAL_IA_MIN_DOUBLE,
                                              CGAL_IA_MIN_DOUBLE);

std::ostream &
operator<< (std::ostream & os, const Interval_base & I)
{
    return os << "[" << I.inf() << ";" << I.sup() << "]";
}

std::istream &
operator>> (std::istream & is, Interval_base & I)
{
    double d;
    is >> d;
    I = d;
    return is;
}

void force_ieee_double_precision()
{
#if defined __i386__ || defined _MSC_VER || defined __BORLANDC__
    FPU_set_cw(CGAL_FE_TONEAREST);
#endif
}

#ifdef __BORLANDC__
// Borland doesn't initialize the FPU exception mask correctly
// => FP exceptions.
struct Borland_workaround
{
    Borland_workaround() { FPU_set_cw(CGAL_FE_TONEAREST); }
};

static Borland_workaround Borland_workaround_object;
#endif // __BORLANDC__


// The results of 1-epsilon and -1+epsilon are enough
// to detect exactly the current rounding mode.
//                          1-MIN_DOUBLE
//                        +------+-------+
//                        |  1   | 1-ulp |
//               +--------+------+-------+
// -1+MIN_DOUBLE | -1     | near |  -inf |
//               | -1+ulp | +inf |  zero |
//               +--------+------+-------+

// I use a global variable here to avoid constant propagation.
double IA_min_double = CGAL_IA_MIN_DOUBLE;

FPU_CW_t
FPU_empiric_test()
{
    double y = 1.0, z = -1.0;
    double ye, ze;
    ye = y - IA_min_double;
    ze = z + IA_min_double;
    if (y == ye && z == ze) return CGAL_FE_TONEAREST;
    if (y == ye) return CGAL_FE_UPWARD;
    if (z == ze) return CGAL_FE_DOWNWARD;
    return CGAL_FE_TOWARDZERO;
}

CGAL_END_NAMESPACE
