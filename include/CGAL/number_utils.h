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

#ifndef CGAL_NUMBER_UTILS_H
#define CGAL_NUMBER_UTILS_H


#include <CGAL/enum.h>

template <class NT>
inline bool CGAL_is_zero(const NT &x)
{
    return x == NT(0);
}

template <class NT>
inline bool CGAL_is_negative(const NT &x)
{
    return x < NT(0);
}

template <class NT>
inline bool CGAL_is_positive(const NT &x)
{
    return x > NT(0);
}

template <class NT>
int CGAL_sign(const NT &x)
{
    return (x < NT(0)) ? -1: (x > NT(0)) ? 1 : 0;
}


template <class NT>
int CGAL_lexicographical_sign(const NT &x, const NT &y)
{
    return (x == NT(0)) ? CGAL_sign(y) : CGAL_sign(x);
}


template <class NT>
NT CGAL_abs(const NT &x)
{
    return (x >= NT(0)) ? x: -x;
}

template <class NT>
NT CGAL_min(const NT &x, const NT &y)
{
    return (x <= y) ? x: y;
}

template <class NT>
NT CGAL_max(const NT &x, const NT &y)
{
    return (x >= y) ? x: y;
}

template <class NT>
inline CGAL_Comparison_result CGAL_compare(const NT &n1, const NT &n2)
{
  if (n1 == n2){
    return CGAL_EQUAL;
  }
  return (n1 < n2) ? CGAL_SMALLER : CGAL_LARGER;
}

#endif
