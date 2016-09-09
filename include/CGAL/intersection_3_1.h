// ============================================================================
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
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/intersection_3_1.h
// author(s)     : Geert-Jan Giezeman 
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


#ifndef CGAL_INTERSECTION_3_1_H
#define CGAL_INTERSECTION_3_1_H



#ifndef CGAL_OBJECT_H
#include <CGAL/Object.h>
#endif // CGAL_OBJECT_H
#ifndef CGAL_BBOX_INTERSECTION_3_H
#include <CGAL/bbox_intersection_3.h>
#endif // CGAL_BBOX_INTERSECTION_3_H


template <class R>
CGAL_Object
CGAL_intersection(const CGAL_Plane_3<R> &plane1, const CGAL_Plane_3<R>&plane2);




template <class R>
CGAL_Object
CGAL_intersection(const CGAL_Plane_3<R> &plane, const CGAL_Line_3<R>&line);

template <class R>
inline
CGAL_Object
CGAL_intersection(const CGAL_Line_3<R>&line, const CGAL_Plane_3<R> &plane)
{
    return CGAL_intersection(plane,line);
}



template <class R>
CGAL_Object
CGAL_intersection(const CGAL_Plane_3<R> &plane, const CGAL_Ray_3<R>&ray);

template <class R>
inline
CGAL_Object
CGAL_intersection(const CGAL_Ray_3<R>&ray, const CGAL_Plane_3<R> &plane)
{
    return CGAL_intersection(plane,ray);
}



template <class R>
CGAL_Object
CGAL_intersection(const CGAL_Plane_3<R> &plane, const CGAL_Segment_3<R>&seg);

template <class R>
inline
CGAL_Object
CGAL_intersection(const CGAL_Segment_3<R>&seg, const CGAL_Plane_3<R> &plane)
{
    return CGAL_intersection(plane,seg);
}



template <class R>
CGAL_Object
CGAL_intersection(const CGAL_Line_3<R> &line,
        const CGAL_Bbox_3 &box) ;

template <class R>
inline CGAL_Object
CGAL_intersection(const CGAL_Bbox_3 &box,
        const CGAL_Line_3<R> &line)
{
    return CGAL_intersection(line, box);
}



template <class R>
CGAL_Object
CGAL_intersection(const CGAL_Ray_3<R> &ray,
        const CGAL_Bbox_3 &box) ;

template <class R>
inline CGAL_Object
CGAL_intersection(const CGAL_Bbox_3 &box,
        const CGAL_Ray_3<R> &ray)
{
    return CGAL_intersection(ray, box);
}



template <class R>
CGAL_Object
CGAL_intersection(const CGAL_Segment_3<R> &seg,
        const CGAL_Bbox_3 &box) ;

template <class R>
inline CGAL_Object
CGAL_intersection(const CGAL_Bbox_3 &box,
        const CGAL_Segment_3<R> &seg)
{
    return CGAL_intersection(seg, box);
}




#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#include <CGAL/intersection_3_1.C>
#endif

#endif // CGAL_INTERSECTION_3_1_H