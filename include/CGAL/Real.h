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

// Source: Real.h
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL_REAL_H
#define CGAL_REAL_H

#include <LEDA/real.h>
#include <CGAL/number_utils.h>
#include <CGAL/misc.h>

inline
bool
CGAL_is_finite(const real &)
{
  return true;
}

inline
bool
CGAL_is_valid(const real &)
{
  return true;
}

inline
double
CGAL_to_double(const real & r)
{
 return r.todouble();
}

inline
CGAL_Number_tag
CGAL_number_type_tag(const real& )
{
 return CGAL_Number_tag();
}

#endif // CGAL_REAL_H
