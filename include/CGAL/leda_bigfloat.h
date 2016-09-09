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
// file          : include/CGAL/leda_bigfloat.h
// package       : Number_types (4.30)
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2001/01/09 18:56:25 $
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

// #ifndef IO_IO_TAGS_H
// #include <CGAL/IO/io_tags.h>
// #endif // IO_IO_TAGS_H
// #ifndef CGAL_NUMBER_TYPE_TAGS_H
// #include <CGAL/number_type_tags.h>
// #endif // CGAL_NUMBER_TYPE_TAGS_H

#ifndef CGAL_PROTECT_LEDA_BIGFLOAT_H
#include <LEDA/bigfloat.h>
#define CGAL_PROTECT_LEDA_BIGFLOAT_H
#endif // CGAL_PROTECT_LEDA_BIGFLOAT_H

CGAL_BEGIN_NAMESPACE


#ifndef CGAL_CFG_NO_NAMESPACE
inline
double
to_double(const leda_bigfloat & b)
{ return ::to_double(b); }
#endif // CGAL_CFG_NO_NAMESPACE

inline
Number_tag
number_type_tag(const leda_bigfloat& )
{ return Number_tag(); }

inline
bool
is_finite(const leda_bigfloat & b)
{ return !( isInf(b) || isNaN(b) ); }

inline
bool
is_valid(const leda_bigfloat & b)
{ return !( isNaN(b) ); }

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
  Interval_nt_advanced approx (::to_double(z));
  FPU_set_cw(CGAL_FE_UPWARD);
  return approx + Interval_base::Smallest;
}


CGAL_END_NAMESPACE



#endif // CGAL_BIGFLOAT_H
