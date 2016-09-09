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
// file          : include/CGAL/leda_bigfloat.h
// package       : Number_types (4.57)
// revision      : $Revision: 1.6 $
// revision_date : $Date: 2002/03/20 19:59:53 $
// author(s)     : Stefan Schirra
//
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_BIGFLOAT_H
#define CGAL_BIGFLOAT_H

#include <CGAL/basic.h>
#include <CGAL/LEDA_basic.h>

#ifndef CGAL_PROTECT_LEDA_BIGFLOAT_H
#include <LEDA/bigfloat.h>
#define CGAL_PROTECT_LEDA_BIGFLOAT_H
#endif // CGAL_PROTECT_LEDA_BIGFLOAT_H

CGAL_BEGIN_NAMESPACE

template <> struct Number_type_traits<leda_bigfloat> {
  typedef Tag_false Has_gcd;
  typedef Tag_true  Has_division;
  typedef Tag_false Has_sqrt;
};

#ifndef CGAL_CFG_NO_NAMESPACE
inline
double
to_double(const leda_bigfloat & b)
{ return CGAL_LEDA_SCOPE::to_double(b); }
#endif // CGAL_CFG_NO_NAMESPACE

inline
bool
is_finite(const leda_bigfloat & b)
{ return !( CGAL_LEDA_SCOPE::isInf(b) || CGAL_LEDA_SCOPE::isNaN(b) ); }

inline
bool
is_valid(const leda_bigfloat & b)
{ return !( CGAL_LEDA_SCOPE::isNaN(b) ); }

inline
io_Operator
io_tag(const leda_bigfloat &)
{ return io_Operator(); }

inline
Interval_base
to_interval (const leda_bigfloat & z)
{
  // assuming leda_bigfloat guarantee 1 bit error max
  Protect_FPU_rounding<true> P (CGAL_FE_TONEAREST);
  Interval_nt_advanced approx (CGAL_LEDA_SCOPE::to_double(z));
  FPU_set_cw(CGAL_FE_UPWARD);
  return approx + Interval_base::Smallest;
}

CGAL_END_NAMESPACE

#endif // CGAL_BIGFLOAT_H
