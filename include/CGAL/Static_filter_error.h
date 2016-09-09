// Copyright (c) 1999,2000  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source: /CVSROOT/CGAL/Packages/Interval_arithmetic/include/CGAL/Static_filter_error.h,v $
// $Revision: 2.19 $ $Date: 2003/10/21 12:17:25 $
// $Name: current_submission $
//
// Author(s)     : Sylvain Pion

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
#include <CGAL/FPU.h>

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
  // Sfe operator/ (const Sfe &) const { CGAL_CLIB_STD::abort(); }
  // Division not supported.

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
      std::cerr << "Static error is : " << e.error() << std::endl;
      CGAL_CLIB_STD::abort();
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
  double b = CGAL_CLIB_STD::sqrt(f.bound());
  FPU_CW_t backup = FPU_get_and_set_cw(CGAL_FE_UPWARD);
  double e = CGAL_CLIB_STD::sqrt(f.error()) + Static_filter_error::ulp(b)/2;
  FPU_set_cw(backup);
  return Static_filter_error(b, e, f.degree()/2);
}

CGAL_END_NAMESPACE

#endif // CGAL_STATIC_FILTER_ERROR_H
