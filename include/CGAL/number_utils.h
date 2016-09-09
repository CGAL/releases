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
// file          : include/CGAL/number_utils.h
// package       : Number_types (4.57)
// revision      : $Revision: 1.6 $
// revision_date : $Date: 2002/03/21 16:44:54 $
// author(s)     : Stefan Schirra
//
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_NUMBER_UTILS_H
#define CGAL_NUMBER_UTILS_H

#include <CGAL/config.h>
#include <CGAL/enum.h>
#include <CGAL/kernel_basic.h>
#include <algorithm>

CGAL_BEGIN_NAMESPACE

template <class NT>
inline
bool
is_zero(const NT& x)
{
  bool is_zero_is_obsolete__qualify_call_by_CGAL_NTS;
  return x == NT(0);
}

template <class NT>
inline
bool
is_one(const NT& x)
{
  bool is_one_is_obsolete__qualify_call_by_CGAL_NTS;
  return x == NT(1);
}

template <class NT>
inline
bool
is_negative(const NT& x)
{
  bool is_negative_is_obsolete__qualify_call_by_CGAL_NTS;
  return x < NT(0);
}

template <class NT>
inline
bool
is_positive(const NT& x)
{
  bool is_positive_is_obsolete__qualify_call_by_CGAL_NTS;
  return NT(0) < x;
}

template <class NT>
CGAL_KERNEL_INLINE
Sign
sign(const NT& x)
{
  bool sign_is_obsolete__qualify_call_by_CGAL_NTS;
  return (x < NT(0)) ? NEGATIVE : (NT(0) < x) ? POSITIVE : ZERO;
}

template <class NT>
CGAL_KERNEL_INLINE
NT
abs(const NT& x)
{
  bool abs_is_obsolete__qualify_call_by_CGAL_NTS;
  return (x < NT(0)) ? -x: x;
}

// for min and max see <CGAL/basic.h>

template <class NT>
CGAL_KERNEL_INLINE
Comparison_result
compare(const NT& n1, const NT& n2)
{
  bool compare_is_obsolete__qualify_call_by_CGAL_NTS;
  if (n1 < n2)
  {
    return SMALLER ;
  }
  return (n2 < n1) ? LARGER : EQUAL;
}

template <class NT>
inline
NT
square( const NT& n)
{
  bool square_is_obsolete__qualify_call_by_CGAL_NTS;
  return n*n;
}

namespace NTS {

template <class NT>
inline
bool
is_zero(const NT& x)
{ return x == NT(0); }

template <class NT>
inline
bool
is_one(const NT& x)
{ return x == NT(1); }

template <class NT>
inline
bool
is_negative(const NT& x)
{ return x < NT(0); }

template <class NT>
inline
bool
is_positive(const NT& x)
{ return NT(0) < x; }

template <class NT>
CGAL_KERNEL_INLINE
Sign
sign(const NT& x)
{ return (x < NT(0)) ? NEGATIVE : (NT(0) < x) ? POSITIVE : ZERO; }

template <class NT>
CGAL_KERNEL_INLINE
NT
abs(const NT& x)
{ return (x < NT(0)) ? -x: x; }

template <class NT>
CGAL_KERNEL_INLINE
const NT&
min(const NT& x, const NT& y)
{ return (y < x) ? y : x; }

template <class NT>
CGAL_KERNEL_INLINE
const NT&
max(const NT& x, const NT& y)
{ return (x < y) ? y : x; }

template <class NT>
CGAL_KERNEL_INLINE
Comparison_result
compare(const NT& n1, const NT& n2)
{
  if (n1 < n2)
  {
    return SMALLER ;
  }
  return (n2 < n1) ? LARGER : EQUAL;
}

template <class NT>
inline
NT
square( const NT& n)
{ return n*n; }

template <class NT>
inline
double
to_double( const NT& n)
{ return CGAL::to_double(n); }

template <class NT>
inline
NT
div( const NT& n1, const NT& n2)
{ return CGAL::div(n1, n2); }

template <class NT>
inline
NT
sqrt( const NT& n)
{ return CGAL::sqrt(n); }

template <class NT>
inline
bool
is_valid( const NT& n)
{ return CGAL::is_valid(n); }

template <class NT>
inline
bool
is_finite( const NT& n)
{ return CGAL::is_finite(n); }

template <class NT>
inline
bool
is_integral( const NT& n)
{ return CGAL::is_integral(n); }

template <class NT>
inline
NT
gcd( const NT& n1, const NT& n2)
{ 
  CGAL_precondition(!CGAL_NTS is_zero(n2));
  NT x = CGAL_NTS abs(n1);
  NT y = CGAL_NTS abs(n2);
  do {
    x %= y;
    if (CGAL_NTS is_zero(x)) return y;
    y %= x;
  } while (CGAL_NTS is_positive(y));
  return x;
}

} // namespace NTS

CGAL_END_NAMESPACE

#endif // CGAL_NUMBER_UTILS_H
