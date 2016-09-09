//  Copyright CGAL 1996
//
//  cgal@cs.ruu.nl
//
//  This file is part of an internal release of the CGAL kernel.
//  The code herein may be used and/or copied only in accordance
//  with the terms and conditions stipulated in the agreement
//  under which the code has been supplied or with the written
//  permission of the CGAL Project.
//
//  Look at http://www.cs.ruu.nl/CGAL/ for more information.
//  Please send any bug reports and comments to cgal@cs.ruu.nl
//
//  The code comes WITHOUT ANY WARRANTY; without even the implied
//  warranty of FITNESS FOR A PARTICULAR PURPOSE.
//


#include <CGAL/Double.h>


#ifdef __sgi

// implementation for SGI IRIX 5.3.
#include <fp_class.h>

bool CGAL_is_finite(double d)
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

bool CGAL_is_valid(double d)
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

#endif // __sgi


#ifdef __hpux

// implementation for HP
#include <math.h>

bool CGAL_is_valid(double d)
{
    return isnan(d) == 0;
}

bool CGAL_is_finite(double d)
{
    switch (fpclassify(d)) {
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

#include <math.h>
#include <CGAL/bool.h>
bool CGAL_is_finite(double d)
{
  if(finite(d)){
    return true;
  }
  return false; // NOT REACHED
}

bool CGAL_is_valid(double d)
{
  return isnan(d) == 0;
}

#endif // __sun


