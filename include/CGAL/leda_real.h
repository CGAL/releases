// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.0
// release_date  : 1999, June 03
// 
// source        : Real.fw
// file          : include/CGAL/leda_real.h
// package       : Number_types (2.1.5)
// revision      : 2.1.5
// revision_date : 09 May 1999 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
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

#ifndef IO_IO_TAGS_H
#include <CGAL/IO/io_tags.h>
#endif // IO_IO_TAGS_H
#ifndef CGAL_NUMBER_TYPE_TAGS_H
#include <CGAL/number_type_tags.h>
#endif // CGAL_NUMBER_TYPE_TAGS_H
#ifndef CGAL_PROTECT_LEDA_REAL_H
#include <LEDA/real.h>
#define CGAL_PROTECT_LEDA_REAL_H
#endif // CGAL_PROTECT_LEDA_REAL_H

CGAL_BEGIN_NAMESPACE


#ifndef CGAL_NO_NAMESPACE
inline
double
to_double(const leda_real & r)
{ return r.to_double(); }
#endif // CGAL_NO_NAMESPACE

inline
Number_tag
number_type_tag(const leda_real& )
{ return Number_tag(); }

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
{ return (Sign)::sign(r); }

Comparison_result
compare(const leda_real& r1, const leda_real& r2)
{
  int c = ::compare(r1,r2);
  return (c < 0) ? SMALLER : ((0 < c) ?  LARGER : EQUAL);
}
#endif // CGAL_CFG_NO_NAMESPACE

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

#ifdef CGAL_INTERVAL_ARITHMETIC_H
#include <CGAL/Interval_arithmetic/IA_leda_real.h>
#endif // CGAL_INTERVAL_ARITHMETIC_H

#endif // CGAL_REAL_H
