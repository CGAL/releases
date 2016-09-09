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
// file          : include/CGAL/Arithmetic_filter/predicates/builtin.h
// package       : Interval_arithmetic (4.141)
// author(s)     : Sylvain Pion
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_ARITHMETIC_FILTER_PREDICATES_BUILTIN_H
#define CGAL_ARITHMETIC_FILTER_PREDICATES_BUILTIN_H

CGAL_BEGIN_NAMESPACE

namespace NTS { // because the script transforms CGAL_NTS sign() into ...

struct Static_Filtered_sign_1
{
  static double _bound;
  static double _epsilon_0;
  static Sign update_epsilon( const Static_filter_error &a, double & epsilon_0)
  {
      epsilon_0 = a.error();
      return ZERO;
  }

  static void new_bound (const double b) // , const double error = 0)
  {
    _bound = b;
    (void) update_epsilon(b,_epsilon_0);
  }

  static Sign epsilon_variant( const Restricted_double &a,
                                const double & epsilon_0)
  {    // return compare_SAF(a,0,epsilon);
    if (to_double(a)> epsilon_0) return POSITIVE;
    if (to_double(a)<-epsilon_0) return NEGATIVE;
    if (to_double(a)==0 && epsilon_0==0) return ZERO;
    Interval_nt_advanced::number_of_failures++;
    throw Interval_nt_advanced::unsafe_comparison();
  }
};

struct Static_Filtered_compare_2
{
  static double _bound;
  static double _epsilon_0;
  static Comparison_result update_epsilon(
          const Static_filter_error &a,
          const Static_filter_error &b,
          double & epsilon_0)
  {
      Static_filter_error c = a-b;
      epsilon_0 = c.error();
      return EQUAL;
  }

  static void new_bound (const double b) // , const double error = 0)
  {
    _bound = b;
    (void) update_epsilon(b,b,_epsilon_0);
  }

  static Comparison_result epsilon_variant(
          const Restricted_double &a,
          const Restricted_double &b,
          const double & epsilon_0)
  {
    if (to_double(a) > to_double(b)+epsilon_0) return LARGER;
    if (to_double(a) < to_double(b)-epsilon_0) return SMALLER;
    if (to_double(a)==to_double(b) && epsilon_0==0) return EQUAL;
    Interval_nt_advanced::number_of_failures++;
    throw Interval_nt_advanced::unsafe_comparison();
  }
};

} // namespace NTS

CGAL_END_NAMESPACE

#endif // CGAL_ARITHMETIC_FILTER_PREDICATES_BUILTIN_H
