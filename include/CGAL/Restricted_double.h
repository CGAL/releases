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
// file          : include/CGAL/Restricted_double.h
// package       : Interval_arithmetic (4.141)
// revision      : $Revision: 2.7 $
// revision_date : $Date: 2000/06/25 18:54:18 $
// author(s)     : Sylvain Pion
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_RESTRICTED_DOUBLE_H
#define CGAL_RESTRICTED_DOUBLE_H

// This file contains the description of the class Restricted_double.
// The goal of this class is to be run by some overloaded predicates,
// This is just a wrapper for a double, but with limited functionality,
// to detect non-intented use.
// It's the type over which is run the epsilon variant, and which throws
// the exceptions.

// TODO: I need to add some missing operators and functions, min/max...

#include <CGAL/basic.h>
// #include <CGAL/double.h>

CGAL_BEGIN_NAMESPACE

#ifdef CGAL_IA_CHECK_RESTRICT
struct Restricted_double
{
  typedef Restricted_double Self;
  struct unsafe_comparison {};          // Exception class.

  Restricted_double () {}
  Restricted_double (const double &d) : _d(d) {}
  Restricted_double (const int &i) : _d(double(i)) {}
// Add operator= for efficiency.
  Self operator+ (const Self &f) const { return _d+f._d; }
  Self operator- (const Self &f) const { return _d-f._d; }
  Self operator* (const Self &f) const { return _d*f._d; }
  Self operator/ (const Self &f) const { return _d/f._d; }
  Self operator- ()              const { return -_d; }

  Self& operator+=(const Self &f) { return *this = _d + f._d; }
  Self& operator-=(const Self &f) { return *this = _d - f._d; }
  Self& operator*=(const Self &f) { return *this = _d * f._d; }
  Self& operator/=(const Self &f) { return *this = _d / f._d; }

#if 0
  bool operator< (const Self &f) const { return _d < f._d; }
#endif
  double dbl () const { return _d; }

private:
  double _d;
};

inline
Restricted_double
sqrt(const Restricted_double &f)
{ return CGAL_CLIB_STD::sqrt(f.dbl()); }

inline
Restricted_double
abs(const Restricted_double &f)
{ return CGAL_CLIB_STD::fabs(f.dbl()); }

inline
double
to_double(const Restricted_double &f)
{ return f.dbl(); }

#else
typedef double Restricted_double;
#endif

CGAL_END_NAMESPACE

#endif // CGAL_RESTRICTED_DOUBLE_H
