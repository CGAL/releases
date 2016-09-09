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
// file          : include/CGAL/intersection_3_1.h
// package       : Intersections_3 (2.1.1)
// source        : web/intersection_3.fw
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : Saarbruecken
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_INTERSECTION_3_1_H
#define CGAL_INTERSECTION_3_1_H



#ifndef CGAL_OBJECT_H
#include <CGAL/Object.h>
#endif // CGAL_OBJECT_H
#ifndef CGAL_BBOX_INTERSECTION_3_H
#include <CGAL/bbox_intersection_3.h>
#endif // CGAL_BBOX_INTERSECTION_3_H


CGAL_BEGIN_NAMESPACE

template <class R>
Object
intersection(const Plane_3<R> &plane1, const Plane_3<R>&plane2);

template <class R>
inline bool
do_intersect(const Plane_3<R> &plane1, const Plane_3<R>&plane2)
{
    return ! intersection(plane1, plane2).is_empty();
}
CGAL_END_NAMESPACE




CGAL_BEGIN_NAMESPACE

template <class R>
Object
intersection(const Plane_3<R> &plane, const Line_3<R>&line);

template <class R>
inline
Object
intersection(const Line_3<R>&line, const Plane_3<R> &plane)
{
    return intersection(plane,line);
}

template <class R>
bool
do_intersect(const Plane_3<R> &p2, const Line_3<R> &p1);


template <class R>
inline bool
do_intersect(
    const Line_3<R> &p1,
    const Plane_3<R> &p2)
{
    return do_intersect(p2,p1);
}

CGAL_END_NAMESPACE




CGAL_BEGIN_NAMESPACE

template <class R>
Object
intersection(const Plane_3<R> &plane, const Ray_3<R>&ray);

template <class R>
inline
Object
intersection(const Ray_3<R>&ray, const Plane_3<R> &plane)
{
    return intersection(plane,ray);
}

template <class R>
bool
do_intersect(const Plane_3<R> &p1, const Ray_3<R> &p2);


template <class R>
inline bool
do_intersect(
    const Ray_3<R> &p1,
    const Plane_3<R> &p2)
{
    return do_intersect(p2,p1);
}
CGAL_END_NAMESPACE



CGAL_BEGIN_NAMESPACE

template <class R>
Object
intersection(const Plane_3<R> &plane, const Segment_3<R>&seg);

template <class R>
inline
Object
intersection(const Segment_3<R>&seg, const Plane_3<R> &plane)
{
    return intersection(plane,seg);
}

template <class R>
bool
do_intersect(const Plane_3<R> &p1, const Segment_3<R> &p2);


template <class R>
inline bool
do_intersect(
    const Segment_3<R> &p1,
    const Plane_3<R> &p2)
{
    return do_intersect(p2,p1);
}

CGAL_END_NAMESPACE




CGAL_BEGIN_NAMESPACE

template <class R>
Object
intersection(const Line_3<R> &line,
        const Bbox_3 &box) ;

template <class R>
inline Object
intersection(const Bbox_3 &box,
        const Line_3<R> &line)
{
    return intersection(line, box);
}

CGAL_END_NAMESPACE



CGAL_BEGIN_NAMESPACE

template <class R>
Object
intersection(const Ray_3<R> &ray,
        const Bbox_3 &box) ;

template <class R>
inline Object
intersection(const Bbox_3 &box,
        const Ray_3<R> &ray)
{
    return intersection(ray, box);
}

CGAL_END_NAMESPACE



CGAL_BEGIN_NAMESPACE

template <class R>
Object
intersection(const Segment_3<R> &seg,
        const Bbox_3 &box) ;

template <class R>
inline Object
intersection(const Bbox_3 &box,
        const Segment_3<R> &seg)
{
    return intersection(seg, box);
}
CGAL_END_NAMESPACE




#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#include <CGAL/intersection_3_1.C>
#endif

#endif // CGAL_INTERSECTION_3_1_H
