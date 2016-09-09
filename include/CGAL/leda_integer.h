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
// file          : include/CGAL/leda_integer.h
// package       : Number_types (4.30)
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2001/05/29 14:16:37 $
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
#include <LEDA/integer.h>

CGAL_BEGIN_NAMESPACE

#ifndef CGAL_CFG_NO_NAMESPACE
inline
double
to_double(const leda_integer & i)
{ return i.to_double(); }
#endif

inline
Number_tag
number_type_tag(const leda_integer& )
{ return Number_tag(); }

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
{ return (Sign)::sign(n); }
#endif

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

CGAL_END_NAMESPACE

#endif // CGAL_LEDA_INTEGER_H
