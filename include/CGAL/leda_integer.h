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
// file          : include/CGAL/leda_integer.h
// package       : Number_types (4.57)
// revision      : $Revision: 1.7 $
// revision_date : $Date: 2002/03/20 19:59:53 $
// author(s)     : Andreas Fabri
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 
#ifndef CGAL_LEDA_INTEGER_H
#define CGAL_LEDA_INTEGER_H

#include <CGAL/basic.h>
#include <CGAL/LEDA_basic.h>
#include <LEDA/integer.h>

CGAL_BEGIN_NAMESPACE

template <> struct Number_type_traits<leda_integer> {
  typedef Tag_true  Has_gcd;
  typedef Tag_false Has_division;
  typedef Tag_false Has_sqrt;
};

#ifndef CGAL_CFG_NO_NAMESPACE
inline
double
to_double(const leda_integer & i)
{ return i.to_double(); }
#endif

inline
bool
is_finite(const leda_integer &)
{ return true; }

inline
bool
is_valid(const leda_integer &)
{ return true; }

inline
io_Operator
io_tag(const leda_integer &)
{ return io_Operator(); }

#ifndef CGAL_CFG_NO_NAMESPACE
inline
Sign
sign(const leda_integer& n)
{ return (Sign) CGAL_LEDA_SCOPE::sign(n); }
#endif

inline
leda_integer
div( const leda_integer& n1, const leda_integer& n2)
{ 
  return n1 / n2;
}

inline
Interval_base
to_interval (const leda_integer & n)
{
  Protect_FPU_rounding<true> P (CGAL_FE_TONEAREST);
  double cn = CGAL::to_double(n);
  leda_integer pn = ( n>0 ? n : -n);
  if ( pn.iszero() || log(pn) < 53 )
      return Interval_base(cn);
  else {
    FPU_set_cw(CGAL_FE_UPWARD);
    return Interval_nt_advanced(cn)+Interval_nt_advanced::Smallest;
  }
}

namespace NTS {
  inline
  leda_integer
  gcd( const leda_integer& n1, const leda_integer& n2)
  { 
    return CGAL_LEDA_SCOPE::gcd(n1, n2);
  }
}

CGAL_END_NAMESPACE

#endif // CGAL_LEDA_INTEGER_H
