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

#ifndef CGAL_ENUM_H
#define CGAL_ENUM_H



enum  CGAL_Sign
      { CGAL_NEGATIVE   = -1,
        CGAL_ZERO,
        CGAL_POSITIVE
      };

typedef CGAL_Sign CGAL_Orientation;

extern CGAL_Orientation  CGAL_LEFTTURN;
extern CGAL_Orientation  CGAL_RIGHTTURN;

extern CGAL_Orientation  CGAL_CLOCKWISE;
extern CGAL_Orientation  CGAL_COUNTERCLOCKWISE;

extern CGAL_Orientation  CGAL_COLLINEAR;
extern CGAL_Orientation  CGAL_COPLANAR;
extern CGAL_Orientation  CGAL_DEGENERATE;




enum  CGAL_Oriented_side
      { CGAL_ON_NEGATIVE_SIDE = -1,
        CGAL_ON_ORIENTED_BOUNDARY,
        CGAL_ON_POSITIVE_SIDE
      };


enum  CGAL_Bounded_side
      { CGAL_ON_BOUNDED_SIDE = -1,
        CGAL_ON_BOUNDARY,
        CGAL_ON_UNBOUNDED_SIDE
      };



enum  CGAL_Comparison_result
      { CGAL_SMALLER   = -1,
        CGAL_EQUAL,
        CGAL_LARGER
      };




#include <CGAL/functions_on_enums.h>

#endif // CGAL_ENUM_H
