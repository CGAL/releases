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


#ifndef DOUBLECOMP_H
#define DOUBLECOMP_H 1

#include <CGAL/misc.h>
#include <CGAL/bool.h>
#include <math.h>


inline double CGAL_to_double(double d)
{
    return d;
}
/*
inline double CGAL_abs(double d)
{
    return fabs(d);
}
*/
inline double CGAL_numerator(double d)
{
  return d;
}

inline double CGAL_denominator(double)
{
  return 1.0;
}

inline CGAL_Number_tag CGAL_number_type_tag(double)
{
  return CGAL_Number_tag();
}

extern bool CGAL_is_finite(double d);

extern bool CGAL_is_valid(double d);

#endif
