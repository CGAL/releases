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
// source        : number_utils.fw
// file          : include/CGAL/number_utils.h
// package       : Number_types (2.1.5)
// revision      : 2.1.5
// revision_date : 09 May 1999 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_NUMBER_UTILS_H
#define CGAL_NUMBER_UTILS_H

#ifndef CGAL_CONFIG_H
#include <CGAL/config.h>
#endif // CGAL_CONFIG_H

#ifndef CGAL_ENUM_H
#include <CGAL/enum.h>
#endif // CGAL_ENUM_H

#include <CGAL/kernel_basic.h>

#include <algorithm>

CGAL_BEGIN_NAMESPACE


template <class NT>
inline
bool
is_zero(const NT &x)
{ return x == NT(0); }

template <class NT>
inline
bool
is_one(const NT &x)
{ return x == NT(1); }

template <class NT>
inline
bool
is_negative(const NT &x)
{ return x < NT(0); }

template <class NT>
inline
bool
is_positive(const NT &x)
{ return NT(0) < x; }

template <class NT>
CGAL_KERNEL_INLINE   /* XXX ok with spezialisations ??? */
Sign
// int
sign(const NT &x)
// { return (x < NT(0)) ? -1: (NT(0) < x) ? 1 : 0; }
{
  return
  (x < NT(0)) ? NEGATIVE : (NT(0) < x) ? POSITIVE : ZERO;
}

template <class NT>
CGAL_KERNEL_INLINE
Sign
// int
lexicographical_sign(const NT &x, const NT &y)
{ return (x == NT(0)) ? CGAL::sign(y) : CGAL::sign(x); }

template <class NT>
CGAL_KERNEL_INLINE
NT
abs(const NT &x)
{ return (x < NT(0)) ? -x: x; }

/*
template <class NT>
CGAL_KERNEL_INLINE
NT
min(const NT &x, const NT &y)
{ return (x < y) ? x: y; }

template <class NT>
CGAL_KERNEL_INLINE
NT
max(const NT &x, const NT &y)
{ return (x < y) ? y: x; }
*/

template <class NT>
CGAL_KERNEL_INLINE
Comparison_result
compare(const NT &n1, const NT &n2)
{
  if (n1 < n2){
    return SMALLER ;
  }
  return (n2 < n1) ? LARGER : EQUAL ;
}

template <class NT>
inline
NT
square( const NT& n)
{ return n*n; }

CGAL_END_NAMESPACE


// #ifndef CGAL_NUMBER_UTILS_CLASSES_H
// #include <CGAL/number_utils_classes.h>
// #endif // CGAL_NUMBER_UTILS_CLASSES_H
// now included after Quotient.h

#endif // CGAL_NUMBER_UTILS_H
