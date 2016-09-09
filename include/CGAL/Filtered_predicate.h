// ======================================================================
//
// Copyright (c) 2001 The CGAL Consortium

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
// file          : include/CGAL/Filtered_predicate.h
// package       : Interval_arithmetic (4.141)
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2001/09/17 12:03:31 $
// author(s)     : Sylvain Pion
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_FILTER_PREDICATE_H
#define CGAL_FILTER_PREDICATE_H

#include <CGAL/basic.h>
#include <CGAL/Interval_arithmetic.h>

CGAL_BEGIN_NAMESPACE

// This template class is a wrapper that implements the filtering for all
// predicates (dynamic filters with IA).

// TODO :
// - each predicate in the default kernel should define a tag that says if it
//   wants to be filtered or not (=> all homogeneous predicate define this
//   tag).  We could even test-suite that automatically.  It makes a strong
//   new requirement on the kernel though...
// - same thing for constructions => virtual operator() ?
// - similarly, constructions should have a tag saying if they can throw or
//   not, or we let all this up to the compiler optimizer to figure out ?
// - The operators() should probably not be inline (?).
// - Potential caching is done at the Point_2 level.


template <class EP, class AP, class C2E, class C2F, bool Protection = true>
class Filtered_predicate
{
  EP Exact_predicate;
  AP Approx_predicate;
  C2E To_Exact;
  C2F To_Approx;

public:

  typedef typename AP::result_type  result_type;
  // Should be the same type as EP::result_type.

  Filtered_predicate()
  {}

  // These constructors are used for constructive predicates.
  // You should try to avoid constructive predicates, as they will construct
  // the exact values systematically (in the ctor), rather than lazily.
  template <class O>
  Filtered_predicate(const O &o1)
    : Exact_predicate(To_Exact(o1)), Approx_predicate(To_Approx(o1))
  {}

  template <class O>
  Filtered_predicate(const O &o1, const O &o2)
    : Exact_predicate(To_Exact(o1), To_Exact(o2)),
      Approx_predicate(To_Approx(o1), To_Approx(o2))
  {}

  template <class A1>
  result_type
  operator()(const A1 &a1) const
#ifndef _MSC_VER
  ;
#else
  {
    try
    {
      Protect_FPU_rounding<Protection> P;
      return Approx_predicate(To_Approx(a1));
    }
    catch (Interval_nt_advanced::unsafe_comparison)
    {
      Protect_FPU_rounding<!Protection> P(CGAL_FE_TONEAREST);
      return Exact_predicate(To_Exact(a1));
    }
  }
#endif

  template <class A1, class A2>
  result_type
  operator()(const A1 &a1, const A2 &a2) const
#ifndef _MSC_VER
  ;
#else
  {
    try
    {
      Protect_FPU_rounding<Protection> P;
      return Approx_predicate(To_Approx(a1), To_Approx(a2));
    }
    catch (Interval_nt_advanced::unsafe_comparison)
    {
      Protect_FPU_rounding<!Protection> P(CGAL_FE_TONEAREST);
      return Exact_predicate(To_Exact(a1), To_Exact(a2));
    }
  }
#endif

  template <class A1, class A2, class A3>
  result_type
  operator()(const A1 &a1, const A2 &a2, const A3 &a3) const
#ifndef _MSC_VER
  ;
#else
  {
    try
    {
      Protect_FPU_rounding<Protection> P;
      return Approx_predicate(To_Approx(a1), To_Approx(a2), To_Approx(a3));
    }
    catch (Interval_nt_advanced::unsafe_comparison)
    {
      Protect_FPU_rounding<!Protection> P(CGAL_FE_TONEAREST);
      return Exact_predicate(To_Exact(a1), To_Exact(a2), To_Exact(a3));
    }
  }
#endif

  template <class A1, class A2, class A3, class A4>
  result_type
  operator()(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4) const
#ifndef _MSC_VER
  ;
#else
  {
    try
    {
      Protect_FPU_rounding<Protection> P;
      return Approx_predicate(To_Approx(a1), To_Approx(a2), To_Approx(a3),
	      To_Approx(a4));
    }
    catch (Interval_nt_advanced::unsafe_comparison)
    {
      Protect_FPU_rounding<!Protection> P(CGAL_FE_TONEAREST);
      return Exact_predicate(To_Exact(a1), To_Exact(a2), To_Exact(a3),
	      To_Exact(a4));
    }
  }
#endif

  template <class A1, class A2, class A3, class A4, class A5>
  result_type
  operator()(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4,
	     const A5 &a5) const
#ifndef _MSC_VER
  ;
#else
  {
    try
    {
      Protect_FPU_rounding<Protection> P;
      return Approx_predicate(To_Approx(a1), To_Approx(a2), To_Approx(a3),
	      To_Approx(a4), To_Approx(a5));
    }
    catch (Interval_nt_advanced::unsafe_comparison)
    {
      Protect_FPU_rounding<!Protection> P(CGAL_FE_TONEAREST);
      return Exact_predicate(To_Exact(a1), To_Exact(a2), To_Exact(a3),
	      To_Exact(a4), To_Exact(a5));
    }
  }
#endif

  template <class A1, class A2, class A3, class A4, class A5, class A6>
  result_type
  operator()(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4,
	     const A5 &a5, const A6 &a6) const
#ifndef _MSC_VER
  ;
#else
  {
    try
    {
      Protect_FPU_rounding<Protection> P;
      return Approx_predicate(To_Approx(a1), To_Approx(a2), To_Approx(a3),
	      To_Approx(a4), To_Approx(a5), To_Approx(a6));
    }
    catch (Interval_nt_advanced::unsafe_comparison)
    {
      Protect_FPU_rounding<!Protection> P(CGAL_FE_TONEAREST);
      return Exact_predicate(To_Exact(a1), To_Exact(a2), To_Exact(a3),
	      To_Exact(a4), To_Exact(a5), To_Exact(a6));
    }
  }
#endif

  template <class A1, class A2, class A3, class A4, class A5, class A6,
            class A7>
  result_type
  operator()(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4,
	     const A5 &a5, const A6 &a6, const A7 &a7) const
#ifndef _MSC_VER
  ;
#else
  {
    try
    {
      Protect_FPU_rounding<Protection> P;
      return Approx_predicate(To_Approx(a1), To_Approx(a2), To_Approx(a3),
	      To_Approx(a4), To_Approx(a5), To_Approx(a6), To_Approx(a7));
    }
    catch (Interval_nt_advanced::unsafe_comparison)
    {
      Protect_FPU_rounding<!Protection> P(CGAL_FE_TONEAREST);
      return Exact_predicate(To_Exact(a1), To_Exact(a2), To_Exact(a3),
	      To_Exact(a4), To_Exact(a5), To_Exact(a6), To_Exact(a7));
    }
  }
#endif

  // Idem for more than 7 arguments.  Do it on demand.
};

#ifndef _MSC_VER
template <class EP, class AP, class C2E, class C2F, bool Protection>
  template <class A1>
typename Filtered_predicate<EP,AP,C2E,C2F,Protection>::result_type
Filtered_predicate<EP,AP,C2E,C2F,Protection>::
  operator()(const A1 &a1) const
{
    try
    {
      Protect_FPU_rounding<Protection> P;
      return Approx_predicate(To_Approx(a1));
    }
    catch (Interval_nt_advanced::unsafe_comparison)
    {
      Protect_FPU_rounding<!Protection> P(CGAL_FE_TONEAREST);
      return Exact_predicate(To_Exact(a1));
    }
}

template <class EP, class AP, class C2E, class C2F, bool Protection>
  template <class A1, class A2>
typename Filtered_predicate<EP,AP,C2E,C2F,Protection>::result_type
Filtered_predicate<EP,AP,C2E,C2F,Protection>::
  operator()(const A1 &a1, const A2 &a2) const
{
    try
    {
      Protect_FPU_rounding<Protection> P;
      return Approx_predicate(To_Approx(a1), To_Approx(a2));
    }
    catch (Interval_nt_advanced::unsafe_comparison)
    {
      Protect_FPU_rounding<!Protection> P(CGAL_FE_TONEAREST);
      return Exact_predicate(To_Exact(a1), To_Exact(a2));
    }
}

template <class EP, class AP, class C2E, class C2F, bool Protection>
  template <class A1, class A2, class A3>
typename Filtered_predicate<EP,AP,C2E,C2F,Protection>::result_type
Filtered_predicate<EP,AP,C2E,C2F,Protection>::
  operator()(const A1 &a1, const A2 &a2, const A3 &a3) const
{
    try
    {
      Protect_FPU_rounding<Protection> P;
      return Approx_predicate(To_Approx(a1), To_Approx(a2), To_Approx(a3));
    }
    catch (Interval_nt_advanced::unsafe_comparison)
    {
      Protect_FPU_rounding<!Protection> P(CGAL_FE_TONEAREST);
      return Exact_predicate(To_Exact(a1), To_Exact(a2), To_Exact(a3));
    }
}

template <class EP, class AP, class C2E, class C2F, bool Protection>
  template <class A1, class A2, class A3, class A4>
typename Filtered_predicate<EP,AP,C2E,C2F,Protection>::result_type
Filtered_predicate<EP,AP,C2E,C2F,Protection>::
  operator()(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4) const
{
    try
    {
      Protect_FPU_rounding<Protection> P;
      return Approx_predicate(To_Approx(a1), To_Approx(a2), To_Approx(a3),
	      To_Approx(a4));
    }
    catch (Interval_nt_advanced::unsafe_comparison)
    {
      Protect_FPU_rounding<!Protection> P(CGAL_FE_TONEAREST);
      return Exact_predicate(To_Exact(a1), To_Exact(a2), To_Exact(a3),
	      To_Exact(a4));
    }
}

template <class EP, class AP, class C2E, class C2F, bool Protection>
  template <class A1, class A2, class A3, class A4, class A5>
typename Filtered_predicate<EP,AP,C2E,C2F,Protection>::result_type
Filtered_predicate<EP,AP,C2E,C2F,Protection>::
  operator()(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4,
	     const A5 &a5) const
{
    try
    {
      Protect_FPU_rounding<Protection> P;
      return Approx_predicate(To_Approx(a1), To_Approx(a2), To_Approx(a3),
	      To_Approx(a4), To_Approx(a5));
    }
    catch (Interval_nt_advanced::unsafe_comparison)
    {
      Protect_FPU_rounding<!Protection> P(CGAL_FE_TONEAREST);
      return Exact_predicate(To_Exact(a1), To_Exact(a2), To_Exact(a3),
	      To_Exact(a4), To_Exact(a5));
    }
}

template <class EP, class AP, class C2E, class C2F, bool Protection>
  template <class A1, class A2, class A3, class A4, class A5, class A6>
typename Filtered_predicate<EP,AP,C2E,C2F,Protection>::result_type
Filtered_predicate<EP,AP,C2E,C2F,Protection>::
  operator()(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4,
	     const A5 &a5, const A6 &a6) const
{
    try
    {
      Protect_FPU_rounding<Protection> P;
      return Approx_predicate(To_Approx(a1), To_Approx(a2), To_Approx(a3),
	      To_Approx(a4), To_Approx(a5), To_Approx(a6));
    }
    catch (Interval_nt_advanced::unsafe_comparison)
    {
      Protect_FPU_rounding<!Protection> P(CGAL_FE_TONEAREST);
      return Exact_predicate(To_Exact(a1), To_Exact(a2), To_Exact(a3),
	      To_Exact(a4), To_Exact(a5), To_Exact(a6));
    }
}
#endif

CGAL_END_NAMESPACE

#endif // CGAL_FILTER_PREDICATE_H
