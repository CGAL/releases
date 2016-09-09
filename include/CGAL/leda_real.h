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
// file          : include/CGAL/leda_real.h
// package       : Number_types (4.57)
// revision      : $Revision: 1.6 $
// revision_date : $Date: 2002/03/20 19:59:54 $
// author(s)     : Stefan Schirra
//
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_REAL_H
#define CGAL_REAL_H

/*
#if !defined(LEDA_ROOT_INCL_ID)
#define LEDA_ROOT_INCL_ID 349117
#include <LEDA/REDEFINE_NAMES.h>
#endif
*/

#include <CGAL/basic.h>
#include <CGAL/LEDA_basic.h>

#ifndef CGAL_PROTECT_LEDA_REAL_H
#include <LEDA/real.h>
#define CGAL_PROTECT_LEDA_REAL_H
#endif // CGAL_PROTECT_LEDA_REAL_H

CGAL_BEGIN_NAMESPACE

template <> struct Number_type_traits<leda_real> {
  typedef Tag_false Has_gcd;
  typedef Tag_true  Has_division;
  typedef Tag_true  Has_sqrt;
};

#ifndef CGAL_NO_NAMESPACE
inline
double
to_double(const leda_real & r)
{ return r.to_double(); }
#endif // CGAL_NO_NAMESPACE

inline
leda_real
sqrt(const leda_real & r)
{ return CGAL_LEDA_SCOPE::sqrt(r); }

inline
bool
is_finite(const leda_real &)
{ return true; }

inline
bool
is_valid(const leda_real &)
{ return true; }

inline
io_Operator
io_tag(const leda_real &)
{ return io_Operator(); }

#ifndef CGAL_CFG_NO_NAMESPACE
inline
Sign
sign(const leda_real& r)
{ return (Sign)CGAL_LEDA_SCOPE::sign(r); }

inline
Comparison_result
compare(const leda_real& r1, const leda_real& r2)
{
  int c = CGAL_LEDA_SCOPE::compare(r1,r2);
  return (c < 0) ? SMALLER : ((0 < c) ?  LARGER : EQUAL);
}
#endif // CGAL_CFG_NO_NAMESPACE

inline
Interval_base
to_interval (const leda_real & z)
{
  Protect_FPU_rounding<true> P (CGAL_FE_TONEAREST);
  double approx = z.to_double();
  double rel_error = z.get_double_error();
  FPU_set_cw(CGAL_FE_UPWARD);
  return ( Interval_nt_advanced(-rel_error,rel_error) + 1 ) * approx;
}

namespace NTS {
  inline
  leda_real
  sqrt( const leda_real& n)
  { 
    return CGAL_LEDA_SCOPE::sqrt(n);
  }
}

CGAL_END_NAMESPACE


#if ( __LEDA__ < 362 )
inline
leda_real
operator/= (leda_real&x, const leda_real&y)
{ x = x / y; return x; }
#endif // __LEDA__ < 362

/*
#if LEDA_ROOT_INCL_ID == 349117
#undef LEDA_ROOT_INCL_ID
#include <LEDA/UNDEFINE_NAMES.h>
#endif
*/

#endif // CGAL_REAL_H
