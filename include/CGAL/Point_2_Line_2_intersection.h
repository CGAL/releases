
// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/Point_2_Line_2_intersection.h
// package       : Intersections_2 (2.1.2)
// source        : intersection_2_1.fw
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : Saarbruecken
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_POINT_2_LINE_2_INTERSECTION_H
#define CGAL_POINT_2_LINE_2_INTERSECTION_H

#ifndef CGAL_LINE_2_H
#include <CGAL/Line_2.h>
#endif // CGAL_LINE_2_H
#ifndef CGAL_POINT_2_H
#include <CGAL/Point_2.h>
#endif // CGAL_POINT_2_H

CGAL_BEGIN_NAMESPACE

template <class R>
inline bool
do_intersect(const Point_2<R> &pt, const Line_2<R> &line)
{
    return line.has_on(pt);
}

CGAL_END_NAMESPACE

#ifndef CGAL_OBJECT_H
#include <CGAL/Object.h>
#endif // CGAL_OBJECT_H

CGAL_BEGIN_NAMESPACE

template <class R>
Object
intersection(const Point_2<R> &pt, const Line_2<R> &line)
{
    if (do_intersect(pt,line)) {
        return Object(new Wrapper< Point_2<R> >(pt));
    }
    return Object();
}


template <class R>
inline bool
do_intersect(const Line_2<R> &line, const Point_2<R> &pt)
{
    return line.has_on(pt);
}


template <class R>
inline Object
intersection(const Line_2<R> &line, const Point_2<R> &pt)
{
    if (do_intersect(pt,line)) {
        return Object(new Wrapper< Point_2<R> >(pt));
    }
    return Object();
}

CGAL_END_NAMESPACE

#endif
