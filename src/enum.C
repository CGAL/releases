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

#include <CGAL/enum.h>

CGAL_Orientation  CGAL_LEFTTURN   = CGAL_POSITIVE;
CGAL_Orientation  CGAL_RIGHTTURN  = CGAL_NEGATIVE;

CGAL_Orientation  CGAL_CLOCKWISE  = CGAL_NEGATIVE;
CGAL_Orientation  CGAL_COUNTERCLOCKWISE = CGAL_POSITIVE;

CGAL_Orientation  CGAL_COLLINEAR  = CGAL_ZERO;
CGAL_Orientation  CGAL_COPLANAR   = CGAL_ZERO;
CGAL_Orientation  CGAL_DEGENERATE = CGAL_ZERO;
