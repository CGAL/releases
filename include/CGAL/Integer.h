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

// Source: Integer.h
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL_INTEGER_H
#define CGAL_INTEGER_H

#include <CGAL/misc.h>
#include <LEDA/integer.h>
#include <CGAL/number_utils.h>


#include <LEDA/REDEFINE_NAMES.h>
inline
bool
CGAL_is_finite(const integer &)
{
  return true;
}

inline
bool
CGAL_is_valid(const integer &)
{
  return true;
}

inline
double
CGAL_to_double(const integer & i)
{
 return i.todouble();
}

inline
CGAL_Number_tag
CGAL_number_type_tag(const integer& )
{
 return CGAL_Number_tag();
}
#include <LEDA/UNDEFINE_NAMES.h>

#endif // CGAL_INTEGER_H
