/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/



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
    return NT(0) < x;
}

template <class NT>
int CGAL_sign(const NT &x)
{
    return (x < NT(0)) ? -1: (NT(0) < x) ? 1 : 0;
}


template <class NT>
int CGAL_lexicographical_sign(const NT &x, const NT &y)
{
    return (x == NT(0)) ? CGAL_sign(y) : CGAL_sign(x);
}


template <class NT>
NT CGAL_abs(const NT &x)
{
    return (x < NT(0)) ? -x: x;
}

template <class NT>
NT CGAL_min(const NT &x, const NT &y)
{
    return (x < y) ? x: y;
}

template <class NT>
NT CGAL_max(const NT &x, const NT &y)
{
    return (x < y) ? y: x;
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
