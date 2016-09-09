
// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/Iso_rectangle_2_Iso_rectangle_2_intersection.h
// package       : Intersections_2 (2.6.3)
// source        : intersection_2_2.fw
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : Saarbruecken
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================


#ifndef CGAL_ISO_RECTANGLE_2_ISO_RECTANGLE_2_INTERSECTION_H
#define CGAL_ISO_RECTANGLE_2_ISO_RECTANGLE_2_INTERSECTION_H

#include <CGAL/Iso_rectangle_2.h>
#include <CGAL/Object.h>

CGAL_BEGIN_NAMESPACE

template <class R>
Object
intersection(
    const Iso_rectangle_2<R> &irect1,
    const Iso_rectangle_2<R> &irect2)
{
    const Point_2<R> &min1 = irect1.min();
    const Point_2<R> &min2 = irect2.min();
    const Point_2<R> &max1 = irect1.max();
    const Point_2<R> &max2 = irect2.max();
    typename R::FT minx, miny, maxx, maxy;
    Point_2<R> newmin;
    Point_2<R> newmax;
    minx = (min1.x() >= min2.x()) ? min1.x() : min2.x();
    maxx = (max1.x() <= max2.x()) ? max1.x() : max2.x();
    if (maxx < minx)
        return Object();
    miny = (min1.y() >= min2.y()) ? min1.y() : min2.y();
    maxy = (max1.y() <= max2.y()) ? max1.y() : max2.y();
    if (maxy < miny)
        return Object();
    if (R::FT_denominator(minx) == R::FT_denominator(miny)) {
        newmin = Point_2<R>(R::FT_numerator(minx), R::FT_numerator(miny),
                    R::FT_denominator(minx));
    } else {
        newmin = Point_2<R>(R::FT_numerator(minx)*R::FT_denominator(miny),
                    R::FT_numerator(miny)*R::FT_denominator(minx),
                    R::FT_denominator(minx) * R::FT_denominator(miny));
    }
    if (R::FT_denominator(maxx) == R::FT_denominator(maxy)) {
        newmax = Point_2<R>(R::FT_numerator(maxx), R::FT_numerator(maxy),
                    R::FT_denominator(maxx));
    } else {
        newmax = Point_2<R>(R::FT_numerator(maxx)*R::FT_denominator(maxy),
                    R::FT_numerator(maxy)*R::FT_denominator(maxx),
                    R::FT_denominator(maxx) * R::FT_denominator(maxy));
    }
    return make_object(Iso_rectangle_2<R>(newmin, newmax));
}

template <class R>
inline bool
do_intersect(
    const Iso_rectangle_2<R> &irect1,
    const Iso_rectangle_2<R> &irect2)
{
    Object obj(intersection(irect1, irect2));
    Iso_rectangle_2<R> irect;
    return (assign(irect, obj));
}

CGAL_END_NAMESPACE

#endif
