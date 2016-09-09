
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

#ifndef CGAL_POINT_2_LINE_2_INTERSECTION_H
#define CGAL_POINT_2_LINE_2_INTERSECTION_H

#include <CGAL/Line_2.h>
#include <CGAL/Point_2.h>


template <class R>
inline bool
CGAL_do_intersect(const CGAL_Point_2<R> &pt, const CGAL_Line_2<R> &line)
{
    return line.has_on(pt);
}

#include <CGAL/Object.h>

template <class R>
CGAL_Object
CGAL_intersection(const CGAL_Point_2<R> &pt, const CGAL_Line_2<R> &line)
{
    if (CGAL_do_intersect(pt,line)) {
        return CGAL_Object(new CGAL_Wrapper< CGAL_Point_2<R> >(pt));
    }
    return CGAL_Object();
}


template <class R>
inline bool
CGAL_do_intersect(const CGAL_Line_2<R> &line, const CGAL_Point_2<R> &pt)
{
    return line.has_on(pt);
}


template <class R>
inline CGAL_Object
CGAL_intersection(const CGAL_Line_2<R> &line, const CGAL_Point_2<R> &pt)
{
    if (CGAL_do_intersect(pt,line)) {
        return CGAL_Object(new CGAL_Wrapper< CGAL_Point_2<R> >(pt));
    }
    return CGAL_Object();
}

#endif
