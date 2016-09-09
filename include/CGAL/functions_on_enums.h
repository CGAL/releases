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

#ifndef CGAL_FUNCTIONS_ON_ENUMS_H
#define CGAL_FUNCTIONS_ON_ENUMS_H

#include <CGAL/enum.h>

inline
CGAL_Orientation
CGAL_opposite(const CGAL_Orientation &o)
{
  return (o == CGAL_COUNTERCLOCKWISE) ?
               CGAL_CLOCKWISE :
               (o == CGAL_CLOCKWISE) ?
                     CGAL_COUNTERCLOCKWISE :
                     CGAL_COLLINEAR;
}

inline
CGAL_Oriented_side
CGAL_opposite(const CGAL_Oriented_side &os)
{
  return (os == CGAL_ON_POSITIVE_SIDE) ?
                CGAL_ON_NEGATIVE_SIDE :
                (os == CGAL_ON_NEGATIVE_SIDE) ?
                      CGAL_ON_POSITIVE_SIDE :
                      CGAL_ON_ORIENTED_BOUNDARY;
}

inline
CGAL_Bounded_side
CGAL_opposite(const CGAL_Bounded_side &bs)
{
  return (bs == CGAL_ON_UNBOUNDED_SIDE) ?
                CGAL_ON_BOUNDED_SIDE :
                (bs == CGAL_ON_BOUNDED_SIDE) ?
                       CGAL_ON_UNBOUNDED_SIDE :
                       CGAL_ON_BOUNDARY;
}


#endif // CGAL_FUNCTIONS_ON_ENUMS_H
