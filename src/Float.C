// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : src/Float.C
// author(s)     : Stefan Schirra  
//                 Geert-Jan Giezeman
//                 Sylvain Pion
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


#include <CGAL/float.h>

#if !defined(__sgi) && !defined(__sun) && !defined(__hpux) && !defined(__linux)

bool CGAL_is_valid(float d)
{
    return !(d == d);
}

bool CGAL_is_finite(float d)
{
    return (d == d) && (CGAL_is_valid(d-d));
}

#else  // custom definitions.

#ifdef __sgi

// implementation for SGI IRIX 5.3.
#include <fp_class.h>

bool CGAL_is_finite(float d)
{
    switch (fp_class_f(d)) {
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

bool CGAL_is_valid(float d)
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

#endif // __sgi

#ifdef __hpux

// implementation for HP

bool CGAL_is_valid(float f)
{
    return isnanf(f) == 0;
}

bool CGAL_is_finite(float f)
{
    switch (fpclassifyf(f)) {
    case FP_PLUS_NORM:
    case FP_MINUS_NORM:
    case FP_PLUS_ZERO:
    case FP_MINUS_ZERO:
    case FP_PLUS_DENORM:
    case FP_MINUS_DENORM:
        return true;
    case FP_PLUS_INF:
    case FP_MINUS_INF:
    case FP_SNAN:
    case FP_QNAN:
        return false;
    }
    return false; // NOT REACHED
}

#endif // __hpux

#ifdef __sun

// implementation for SUN

#ifdef __SVR4
#include <ieeefp.h>
#endif // __SVR4

#ifdef __svr4__
#include <ieeefp.h>
#endif //  __svr4__

// implementation for Sun

bool CGAL_is_valid(float f)
{
    return isnanf(f) == 0;
}

bool CGAL_is_finite(float f)
{
    return finite(f);
}

#endif // __sun

#ifdef __linux

// Implementation for Linux

bool CGAL_is_finite(float f)
{
  return finite(f) != 0;
}

bool CGAL_is_valid(float f)
{
  return isnan(f) == 0;
}

#endif // __linux

#endif // custom definitions.
