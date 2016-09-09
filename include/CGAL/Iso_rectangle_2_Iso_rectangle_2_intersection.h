
// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.1
// release_date  : 1998, July 24
//
// file          : include/CGAL/Iso_rectangle_2_Iso_rectangle_2_intersection.h
// package       : Intersections_2 (1.5)
// source        : intersection_2_2.fw
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : Saarbruecken
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_ISO_RECTANGLE_2_ISO_RECTANGLE_2_INTERSECTION_H
#define CGAL_ISO_RECTANGLE_2_ISO_RECTANGLE_2_INTERSECTION_H

#ifndef CGAL_ISO_RECTANGLE_2_H
#include <CGAL/Iso_rectangle_2.h>
#endif // CGAL_ISO_RECTANGLE_2_H
#ifndef CGAL_OBJECT_H
#include <CGAL/Object.h>
#endif // CGAL_OBJECT_H

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
    typename R::FT minx, miny, maxx, maxy;
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
    CGAL_Object obj(CGAL_intersection(irect1, irect2));
    CGAL_Iso_rectangle_2<R> irect;
    return (CGAL_assign(irect, obj));
}

#endif
