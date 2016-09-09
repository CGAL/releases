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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/Filter_construction.h
// package       : Interval_arithmetic (4.114)
// revision      : $Revision: 1.1 $
// revision_date : $Date: 2001/04/24 19:51:40 $
// author(s)     : Sylvain Pion
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_FILTER_CONSTRUCTION_H
#define CGAL_FILTER_CONSTRUCTION_H

#include <CGAL/basic.h>
#include <CGAL/Interval_arithmetic.h>

CGAL_BEGIN_NAMESPACE

template <typename ET> class Lazy_construct;

// Abstract base representation class
template <typename AT, typename ET>
struct Lazy_construct_rep : public Rep
{
  AT app; // could be const, except for rafinement ? or mutable ?
  ET *et;

  Lazy_construct_rep ()
      : app(), et(NULL) {}

  const AT& approx() const
  {
      return app;
  }

  const ET& exact()
  {
      if (et==NULL)
          update_exact();
      return *et;
  }

  // virtual void update_approx() = 0; // Not used anymore...  at the moment :)
  virtual void update_exact() = 0;
  virtual ~Lazy_construct_rep () {};
};

// Ref class for a geometric class, corresponding to a given construction.
template <typename AC, typename EC, typename ACv, typename ECv>
struct Lazy_construct : public Lazy_construct_rep<ET>
{
  Lazy_construct () {} // ?

  // So : we want the interval computation to be try/Protect/catch.
  // We want the exact computation to be lazy, triggered by the above initial
  // construction, or later triggered externally by a predicate (called via
  // update_exact().  BUT, update_exact() needs to know which exact
  // construction to call, that is, which operator() to call.  For a given
  // type, there can be several with different number of arguments, or types
  // of arguments.  We must have a construct for the original exact data,
  // which recursively provides the exact original exact data.
  // This is not trivial, as we need to store pointers to the arguments, which
  // number and types are variable, and do not depend only on the type of the
  // construction object exact/approx which is called.
  // Is it doable dynamically ?  Or maybe we need something else which is
  // triggered when operator() is called at top-level, which selects the
  // actual return type, templated by the argument passed...
  // A bit more complexity...
  template <class A1>
  operator()(const A1 &a1) const
  {
      try
      {

      }
      catch (IA::unsafe_comparison)
      {
	  update_exact();
	  rafine();
      }
  }

  void update_approx() { in = min(op1.approx(), op2.approx()); }
  void update_exact()  { et = new ET(min(op1.exact(), op2.exact())); }
};


// This template class is a wrapper that implements the filtering for all
// constructions (dynamic filters with IA).

template <class EC, class AC, class ECv, class ACv, bool Protection = true>
class Filtered_construction
{
  EC Exact_construction;
  AC Approx_construction;
  ECv To_Exact;
  ACv To_Approx;

public:

  // Here's another subtle part (virtual class hierarchy) :
  typedef Handle___construct<...> result_type; // FIXME

  Filtered_construction() {}

  result_type
  operator()() const // FIXME : makes sense ?
  {
    try
    {
      Protect_FPU_rounding<Protection> P;
      return Approx_construction();
    }
    catch (Interval_nt_advanced::unsafe_comparison)
    {
      Protect_FPU_rounding<!Protection> P(CGAL_FE_TONEAREST);
      return Exact_construction();
    }
  }

  template <class A1>
  result_type
  operator()(const A1 &a1) const
  {
    try
    {
      Protect_FPU_rounding<Protection> P;
      return Approx_construction(To_Approx(a1));
    }
    catch (Interval_nt_advanced::unsafe_comparison)
    {
      Protect_FPU_rounding<!Protection> P(CGAL_FE_TONEAREST);
      return Exact_construction(To_Exact(a1));
    }
  }

  template <class A1, class A2>
  result_type
  operator()(const A1 &a1, const A2 &a2) const
  {
    try
    {
      Protect_FPU_rounding<Protection> P;
      return Approx_construction(To_Approx(a1), To_Approx(a2));
    }
    catch (Interval_nt_advanced::unsafe_comparison)
    {
      Protect_FPU_rounding<!Protection> P(CGAL_FE_TONEAREST);
      return Exact_construction(To_Exact(a1), To_Exact(a2));
    }
  }

  template <class A1, class A2, class A3>
  result_type
  operator()(const A1 &a1, const A2 &a2, const A3 &a3) const
  {
    try
    {
      Protect_FPU_rounding<Protection> P;
      return Approx_construction(To_Approx(a1), To_Approx(a2), To_Approx(a3));
    }
    catch (Interval_nt_advanced::unsafe_comparison)
    {
      Protect_FPU_rounding<!Protection> P(CGAL_FE_TONEAREST);
      return Exact_construction(To_Exact(a1), To_Exact(a2), To_Exact(a3));
    }
  }

  template <class A1, class A2, class A3, class A4>
  result_type
  operator()(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4) const
  {
    try
    {
      Protect_FPU_rounding<Protection> P;
      return Approx_construction(To_Approx(a1), To_Approx(a2), To_Approx(a3),
	      To_Approx(a4));
    }
    catch (Interval_nt_advanced::unsafe_comparison)
    {
      Protect_FPU_rounding<!Protection> P(CGAL_FE_TONEAREST);
      return Exact_construction(To_Exact(a1), To_Exact(a2), To_Exact(a3),
	      To_Exact(a4));
    }
  }

  template <class A1, class A2, class A3, class A4, class A5>
  result_type
  operator()(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4,
	     const A5 &a5) const
  {
    try
    {
      Protect_FPU_rounding<Protection> P;
      return Approx_construction(To_Approx(a1), To_Approx(a2), To_Approx(a3),
	      To_Approx(a4), To_Approx(a5));
    }
    catch (Interval_nt_advanced::unsafe_comparison)
    {
      Protect_FPU_rounding<!Protection> P(CGAL_FE_TONEAREST);
      return Exact_construction(To_Exact(a1), To_Exact(a2), To_Exact(a3),
	      To_Exact(a4), To_Exact(a5));
    }
  }

  template <class A1, class A2, class A3, class A4, class A5, class A6>
  result_type
  operator()(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4,
	     const A5 &a5, const A6 &a6) const
  {
    try
    {
      Protect_FPU_rounding<Protection> P;
      return Approx_construction(To_Approx(a1), To_Approx(a2), To_Approx(a3),
	      To_Approx(a4), To_Approx(a5), To_Approx(a6));
    }
    catch (Interval_nt_advanced::unsafe_comparison)
    {
      Protect_FPU_rounding<!Protection> P(CGAL_FE_TONEAREST);
      return Exact_construction(To_Exact(a1), To_Exact(a2), To_Exact(a3),
	      To_Exact(a4), To_Exact(a5), To_Exact(a6));
    }
  }

  template <class A1, class A2, class A3, class A4, class A5, class A6,
            class A7>
  result_type
  operator()(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4,
	     const A5 &a5, const A6 &a6, const A7 &a7) const
  {
    try
    {
      Protect_FPU_rounding<Protection> P;
      return Approx_construction(To_Approx(a1), To_Approx(a2), To_Approx(a3),
	      To_Approx(a4), To_Approx(a5), To_Approx(a6), To_Approx(a7));
    }
    catch (Interval_nt_advanced::unsafe_comparison)
    {
      Protect_FPU_rounding<!Protection> P(CGAL_FE_TONEAREST);
      return Exact_construction(To_Exact(a1), To_Exact(a2), To_Exact(a3),
	      To_Exact(a4), To_Exact(a5), To_Exact(a6), To_Exact(a7));
    }
  }

  // Idem for more than 7 arguments.  Do it on demand.
};

CGAL_END_NAMESPACE

#endif // CGAL_FILTER_CONSTRUCTION_H
