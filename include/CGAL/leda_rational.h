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
// file          : include/CGAL/leda_rational.h
// package       : Number_types (4.30)
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2001/01/09 18:56:25 $
// author(s)     : Andreas Fabri
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_LEDA_RATIONAL_H
#define CGAL_LEDA_RATIONAL_H

#include <CGAL/basic.h>

// #ifndef CGAL_NUMBER_TYPE_TAGS_H
// #include <CGAL/number_type_tags.h>
// #endif // CGAL_NUMBER_TYPE_TAGS_H
// #ifndef IO_IO_TAGS_H
// #include <CGAL/IO/io_tags.h>
// #endif // IO_IO_TAGS_H

/*
#if !defined(LEDA_ROOT_INCL_ID)
#define LEDA_ROOT_INCL_ID 349115
#include <LEDA/REDEFINE_NAMES.h>
#endif
*/

#ifndef CGAL_PROTECT_LEDA_RATIONAL_H
#include <LEDA/rational.h>
#define CGAL_PROTECT_LEDA_RATIONAL_H
#endif // CGAL_PROTECT_LEDA_RATIONAL_H

CGAL_BEGIN_NAMESPACE


#ifndef CGAL_NO_NAMESPACE
inline
double
to_double(const leda_rational &r)
{ return r.to_double(); }
#endif // CGAL_NO_NAMESPACE

inline
Number_tag
number_type_tag(const leda_rational &)
{ return Number_tag(); }

inline
bool
is_finite(const leda_rational &)
{ return true; }

inline
bool
is_valid(const leda_rational &)
{ return true; }

inline
io_Operator
io_tag(const leda_rational &)
{ return io_Operator(); }

#ifndef CGAL_CFG_NO_NAMESPACE
inline
Sign
sign(const leda_rational& r)
{ return (Sign)::sign(r); }
#endif // CGAL_CFG_NO_NAMESPACE

inline
Interval_base
to_interval (const leda_rational & z)
{
  // There's no guarantee about the error of to_double(), so I add 3 ulps...
  Protect_FPU_rounding<true> P (CGAL_FE_TONEAREST);
  Interval_nt_advanced approx (z.to_double());
  FPU_set_cw(CGAL_FE_UPWARD);

  return ( (approx + Interval_base::Smallest) + Interval_base::Smallest)
         + Interval_base::Smallest;
}


CGAL_END_NAMESPACE


/*
#if LEDA_ROOT_INCL_ID == 349115
#undef LEDA_ROOT_INCL_ID
#include <LEDA/UNDEFINE_NAMES.h>
#endif
*/

#endif  // CGAL_LEDA_RATIONAL_H
