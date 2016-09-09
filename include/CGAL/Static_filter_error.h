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
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : include/CGAL/Static_filter_error.h
// package       : Interval_arithmetic (4.39)
// revision      : $Revision: 2.8 $
// revision_date : $Date: 1999/11/07 17:54:42 $
// author(s)     : Sylvain Pion
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_STATIC_FILTER_ERROR_H
#define CGAL_STATIC_FILTER_ERROR_H

// This file contains the description of the class Static_filter_error.
// The goal of this class is to be run by some overloaded predicates,
// to compute error bound done in these functions.
// 
// The original idea is from Olivier Devillers.

// It is still EXPERIMENTAL.

// TODO:
// - I need to add some missing operators and functions, min/max...
// - Remove the degree stuff, it's only meant for debug (?).
// - Add __attribute__((const)) for optimizing ?

#include <CGAL/basic.h>
#include <CGAL/Interval_arithmetic/_FPU.h>

CGAL_BEGIN_NAMESPACE

struct Static_filter_error
{
  typedef Static_filter_error Sfe;

  Static_filter_error () {}

  Static_filter_error (const int &i, const double &e = 0, const int &d = 1)
      : _b(i), _e(e), _d(d) {}

  Static_filter_error (const double &b, const double &e = 0, const int &d = 1)
      : _b(b), _e(e), _d(d) {}

  static double ulp (const double &d)
  {
      // You are supposed to call this function with rounding towards
      // +infinity, and on a positive number.
      CGAL_assertion(d>=0);
      double u = (d + CGAL_IA_MIN_DOUBLE) - d;
      CGAL_assertion(u!=0);
      return u;
  }

  Sfe operator+ (const Sfe &f) const
  {
      CGAL_warning_msg(_d == f._d,
	      "you are adding variables of different homogeneous degree");
      double b = _b + f._b;
      FPU_CW_t backup = FPU_get_and_set_cw(CGAL_FE_UPWARD);
      double e = (ulp(b)/2 + _e) + f._e;
      FPU_set_cw(backup);
      return Sfe(b, e, _d);
  }

  Sfe operator* (const Sfe &f) const
  {
      double b = _b * f._b;
      FPU_CW_t backup = FPU_get_and_set_cw(CGAL_FE_UPWARD);
      double e = (ulp(b)/2 + _e * f._e) +  _e * f._b + _b * f._e;
      FPU_set_cw(backup);
      return Sfe(b, e, _d+f._d);
  }

  Sfe operator- (const Sfe &f) const { return *this + f; }
  Sfe operator- ()             const { return *this; }
  // Sfe operator/ (const Sfe &) const { abort(); } // Division not supported.

  Sfe& operator+=(const Sfe &f) { return *this = *this + f; }
  Sfe& operator-=(const Sfe &f) { return *this = *this - f; }
  Sfe& operator*=(const Sfe &f) { return *this = *this * f; }
  // Sfe& operator/=(const Sfe &f) { return *this = *this / f; }

  double error()  const { return _e; }
  double bound()  const { return _b; }
  int    degree() const { return _d; }

  bool operator< (const Sfe &f) const
  {
      Sfe e = *this + f;
      std::cerr << "Static error is" << e.error() << std::endl;
      abort();
      return false;
  }
  bool operator> (const Sfe &f) const { return *this < f; }
  bool operator<=(const Sfe &f) const { return *this < f; }
  bool operator>=(const Sfe &f) const { return *this < f; }
  bool operator==(const Sfe &f) const { return *this < f; }
  bool operator!=(const Sfe &f) const { return *this < f; }

private:
  // _b is a bound on the absolute value of the _double_ value of the
  //    variable.
  // _e is a bound on the absolute error (difference between _b and the
  //    _real_ value of the variable.
  // _d is the degree of the variable, it allows some additionnal checks.
  double _b, _e;
  int _d;
};

inline
Static_filter_error
sqrt(const Static_filter_error &f)
{
  CGAL_warning_msg(f.degree() & 1 == 0,
	  "you really want a non integer degree ???");
  double b = std::sqrt(f.bound());
  FPU_CW_t backup = FPU_get_and_set_cw(CGAL_FE_UPWARD);
  double e = std::sqrt(f.error()) + Static_filter_error::ulp(b)/2;
  FPU_set_cw(backup);
  return Static_filter_error(b, e, f.degree()/2);
}

CGAL_END_NAMESPACE

#endif // CGAL_STATIC_FILTER_ERROR_H
