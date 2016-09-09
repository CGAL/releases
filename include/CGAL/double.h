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
// source        : Double.fw
// file          : include/CGAL/double.h
// package       : Number_types (2.1.5)
// revision      : 2.1.5
// revision_date : 09 May 1999 
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : cgal@cs.uu.nl
//
// ======================================================================
 

#ifndef CGAL_DOUBLE_H
#define CGAL_DOUBLE_H 1

#include <CGAL/config.h>
#ifndef CGAL_TAGS_H
#include <CGAL/tags.h>
#endif // CGAL_TAGS_H
#include <cmath>

CGAL_BEGIN_NAMESPACE


inline
double
to_double(double d)
{ return d; }

inline
Number_tag
number_type_tag(double)
{ return Number_tag(); }

#ifdef OLD_FINITE_VALID
extern
bool
is_finite(double d);

extern
bool
is_valid(double d);

#else

#ifdef __sgi
#include <fp_class.h>

inline
bool is_finite(double d)
{
    switch (fp_class_d(d)) {
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
bool is_valid(double d)
{
    switch (fp_class_d(d)) {
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

#else

inline
bool
is_valid(double d)
{ return (d == d); }

inline
bool
is_finite(double d)
{ return (d == d) && (is_valid(d-d)); }

#endif // __sgi

#endif // OLD_FINITE_VALID

inline
io_Operator
io_tag(double)
{ return io_Operator(); }

#ifndef CGAL_CFG_NO_NAMESPACE
#ifndef CGAL_NUMBER_UTILS_H
template <class NT> NT abs(const NT &x);
#endif // CGAL_NUMBER_UTILS_H

CGAL_TEMPLATE_NULL
inline
double
abs(const double& d)
{ return std::fabs(d); }


#endif // CGAL_CFG_NO_NAMESPACE

CGAL_END_NAMESPACE

#endif // CGAL_DOUBLE_H
