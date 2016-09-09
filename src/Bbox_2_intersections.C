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

// Author: Geert-Jan Giezeman

#include <CGAL/Cartesian.h>
#include <CGAL/Bbox_2_Line_2_intersection.h>
#include <CGAL/Ray_2_Bbox_2_intersection.h>


CGAL_Bbox_2_Line_2_pair< CGAL_Cartesian<double> >::CGAL_Bbox_2_Line_2_pair(
    CGAL_Bbox_2 const *bbox, CGAL_Line_2< CGAL_Cartesian<double> > const *line)
{
    _bbox = bbox;
    _line = *line;
    _known = false;
}


CGAL_Ray_2_Bbox_2_pair< CGAL_Cartesian<double> >::
CGAL_Ray_2_Bbox_2_pair(
            CGAL_Ray_2< CGAL_Cartesian<double> > const *ray,
            CGAL_Bbox_2 const *box)
{
    _known = false;
    _box = box;
    _ref_point = ray->start();
    _dir = ray->direction().vector();
    _min = 0;
}

