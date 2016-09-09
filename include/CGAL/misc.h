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

// Source: misc.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_MISC_H
#define CGAL_MISC_H

#include <CGAL/workaround.h>
#include <CGAL/workaround_10.h>

// compilers that have rtti need the following file
#ifndef CGAL_WORKAROUND_012
#include <std/typeinfo.h>
#endif  // CGAL_WORKAROUND_012


struct CGAL_No_number_tag{};
struct CGAL_Number_tag{};
struct CGAL_Quotient_tag{};
inline CGAL_Number_tag CGAL_number_type_tag(int)
{
  return CGAL_Number_tag();
}


template < class T >
inline
void
CGAL_swap(T& a, T& b)
{
 T c;
 c = a;
 a = b;
 b = c;
}

#endif // CGAL_MISC_H
