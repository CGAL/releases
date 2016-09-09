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
// file          : include/CGAL/float.h
// package       : Number_types (4.30)
// revision      : $Revision: 1.7 $
// revision_date : $Date: 2001/06/14 13:03:06 $
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_FLOAT_H
#define CGAL_FLOAT_H

#include <CGAL/basic.h>
#include <CGAL/tags.h>
#include <cmath>
#if defined(_MSC_VER) || defined(__BORLANDC__) || \
    defined(CGAL_MASK_FINITE_VALID)
#  include <CGAL/IEEE_754_unions.h>
#endif
#ifdef __sgi
#  include <fp_class.h>
#endif

CGAL_BEGIN_NAMESPACE

inline
double
to_double(float f)
{ return static_cast<double>(f); }

inline
Number_tag
number_type_tag(float)
{ return Number_tag(); }

#ifdef __sgi

inline
bool is_finite(float f)
{
    switch (fp_class_f(f)) {
    case FP_POS_NORM:
    case FP_NEG_NORM:
    case FP_POS_ZERO:
    case FP_NEG_ZERO:
    case FP_POS_DENORM:
    case FP_NEG_DENORM:
        return true;
    case FP_SNAN:
    case FP_QNAN:
    case FP_POS_INF:
    case FP_NEG_INF:
        return false;
    }
    return false; // NOT REACHED
}

inline
bool is_valid(float d)
{
    switch (fp_class_f(d)) {
    case FP_POS_NORM:
    case FP_NEG_NORM:
    case FP_POS_ZERO:
    case FP_NEG_ZERO:
    case FP_POS_INF:
    case FP_NEG_INF:
    case FP_POS_DENORM:
    case FP_NEG_DENORM:
        return true;
    case FP_SNAN:
    case FP_QNAN:
        return false;
    }
    return false; // NOT REACHED
}

#elif defined(_MSC_VER) || defined(__BORLANDC__) || \
      defined(CGAL_MASK_FINITE_VALID)

#define CGAL_EXPONENT_FLOAT_MASK   0x7f800000
#define CGAL_MANTISSA_FLOAT_MASK   0x007fffff

inline
bool
is_finite_by_mask_float(unsigned int u)
{
  unsigned int e = u & CGAL_EXPONENT_FLOAT_MASK;
  return ( (e ^ CGAL_EXPONENT_FLOAT_MASK) != 0);
}

inline
bool
is_nan_by_mask_float(unsigned int u)
{
  if ( is_finite_by_mask_float(u) ) return false;
  // unsigned int m = u & CGAL_MANTISSA_FLOAT_MASK;
  return ( (u & CGAL_MANTISSA_FLOAT_MASK) != 0);
}

inline
bool
is_finite( const float& flt)
{
  float f = flt;
  IEEE_754_float* p = reinterpret_cast<IEEE_754_float*>(&f);
  return is_finite_by_mask_float( p->c );
}

inline
bool
is_valid( const float& flt)
{
  float f = flt;
  IEEE_754_float* p = reinterpret_cast<IEEE_754_float*>(&f);
  return !is_nan_by_mask_float( p->c );
}

#else

inline
bool
is_valid(float d)
{ return (d == d); }

inline
bool
is_finite(float d)
{ return (d == d) && (is_valid(d-d)); }

#endif

inline
io_Operator
io_tag(float)
{ return io_Operator(); }

CGAL_END_NAMESPACE

#endif // CGAL_FLOAT_H
