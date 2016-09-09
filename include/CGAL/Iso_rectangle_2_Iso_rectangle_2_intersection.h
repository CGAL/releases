
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

#ifndef CGAL_ISO_RECTANGLE_2_ISO_RECTANGLE_2_INTERSECTION_H
#define CGAL_ISO_RECTANGLE_2_ISO_RECTANGLE_2_INTERSECTION_H

#include <CGAL/Iso_rectangle_2.h>
#include <CGAL/Object.h>

template <class R>
CGAL_Object
CGAL_intersection(
    const CGAL_Iso_rectangle_2<R> &irect1,
    const CGAL_Iso_rectangle_2<R> &irect2)
{
    const CGAL_Point_2<R> &min1 = irect1.min();
    const CGAL_Point_2<R> &min2 = irect2.min();
    const CGAL_Point_2<R> &max1 = irect1.max();
    const CGAL_Point_2<R> &max2 = irect2.max();
    R::FT minx, miny, maxx, maxy;
    CGAL_Point_2<R> newmin;
    CGAL_Point_2<R> newmax;
    minx = (min1.x() >= min2.x()) ? min1.x() : min2.x();
    maxx = (max1.x() <= max2.x()) ? max1.x() : max2.x();
    if (maxx < minx)
        return CGAL_Object();
    miny = (min1.y() >= min2.y()) ? min1.y() : min2.y();
    maxy = (max1.y() <= max2.y()) ? max1.y() : max2.y();
    if (maxy < miny)
        return CGAL_Object();
    if (R::FT_denominator(minx) == R::FT_denominator(miny)) {
        newmin = CGAL_Point_2<R>(R::FT_numerator(minx), R::FT_numerator(miny),
                    R::FT_denominator(minx));
    } else {
        newmin = CGAL_Point_2<R>(R::FT_numerator(minx)*R::FT_denominator(miny),
                    R::FT_numerator(miny)*R::FT_denominator(minx),
                    R::FT_denominator(minx) * R::FT_denominator(miny));
    }
    if (R::FT_denominator(maxx) == R::FT_denominator(maxy)) {
        newmax = CGAL_Point_2<R>(R::FT_numerator(maxx), R::FT_numerator(maxy),
                    R::FT_denominator(maxx));
    } else {
        newmax = CGAL_Point_2<R>(R::FT_numerator(maxx)*R::FT_denominator(maxy),
                    R::FT_numerator(maxy)*R::FT_denominator(maxx),
                    R::FT_denominator(maxx) * R::FT_denominator(maxy));
    }
    return CGAL_make_object(CGAL_Iso_rectangle_2<R>(newmin, newmax));
}

template <class R>
inline bool
CGAL_do_intersect(
    const CGAL_Iso_rectangle_2<R> &irect1,
    const CGAL_Iso_rectangle_2<R> &irect2)
{
    CGAL_Object obj(CGAL_intersection(rect1, rect2));
    CGAL_Iso_rectangle_2<R> irect;
    return (CGAL_assign(irect, obj));
}

#endif
