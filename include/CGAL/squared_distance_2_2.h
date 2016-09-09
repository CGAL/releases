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

#ifndef CGAL_SQUARED_DISTANCE_2_2_H
#define CGAL_SQUARED_DISTANCE_2_2_H

template <class T>
class CGAL_Segment_2;
template <class T>
class CGAL_Line_2;
template <class T>
class CGAL_Ray_2;
template <class T>
class CGAL_Triangle_2;
#include <CGAL/workaround_10.h>



template <class R>
extern void
CGAL_distance_index(
    int &ind1,
    int &ind2,
    const CGAL_Point_2<R> &pt,
    const CGAL_Triangle_2<R> &triangle);

template <class R>
extern R_FT_return(R)
CGAL_squared_distance_indexed(const CGAL_Point_2<R> &pt,
    const CGAL_Triangle_2<R> &triangle, int ind1, int ind2);
template <class R>
extern R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Point_2<R> &pt,
    const CGAL_Triangle_2<R> &triangle);


template <class R>
inline R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Triangle_2<R> & triangle,
    const CGAL_Point_2<R> & pt)
{
    return CGAL_squared_distance(pt, triangle);
}

template <class R>
extern R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Line_2<R> &line,
    const CGAL_Triangle_2<R> &triangle);


template <class R>
inline R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Triangle_2<R> & triangle,
    const CGAL_Line_2<R> & line)
{
    return CGAL_squared_distance(line, triangle);
}

template <class R>
extern R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Ray_2<R> &ray,
    const CGAL_Triangle_2<R> &triangle);


template <class R>
inline R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Triangle_2<R> & triangle,
    const CGAL_Ray_2<R> & ray)
{
    return CGAL_squared_distance(ray, triangle);
}

template <class R>
extern R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Segment_2<R> &seg,
    const CGAL_Triangle_2<R> &triangle);


template <class R>
inline R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Triangle_2<R> & triangle,
    const CGAL_Segment_2<R> & seg)
{
    return CGAL_squared_distance(seg, triangle);
}

template <class R>
extern R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Triangle_2<R> &triangle1,
    const CGAL_Triangle_2<R> &triangle2);



#ifdef CGAL_INCLUDE_CODE
#include <CGAL/squared_distance_2_2.C>
#endif


#endif
