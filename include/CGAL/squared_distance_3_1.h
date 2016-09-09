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
// file          : include/CGAL/squared_distance_3_1.h
// package       : Distance_3 (2.1.1)
// source        : sqdistance_3.fw
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : Saarbruecken
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_DISTANCE_3_1_H
#define CGAL_DISTANCE_3_1_H

#ifndef CGAL_SEGMENT_3_H
#include <CGAL/Segment_3.h>
#endif // CGAL_SEGMENT_3_H
#ifndef CGAL_LINE_3_H
#include <CGAL/Line_3.h>
#endif // CGAL_LINE_3_H
#ifndef CGAL_RAY_3_H
#include <CGAL/Ray_3.h>
#endif // CGAL_RAY_3_H

CGAL_BEGIN_NAMESPACE


template <class R>
extern R_FT_return(R)
squared_distance(
    const Point_3<R> &pt,
    const Line_3<R> &line);

template <class R>
inline R_FT_return(R)
squared_distance(
    const Line_3<R> & line,
    const Point_3<R> & pt)
{
    return squared_distance(pt, line);
}

template <class R>
extern R_FT_return(R)
squared_distance(
    const Point_3<R> &pt,
    const Ray_3<R> &ray);

template <class R>
inline R_FT_return(R)
squared_distance(
    const Ray_3<R> & ray,
    const Point_3<R> & pt)
{
    return squared_distance(pt, ray);
}

template <class R>
extern R_FT_return(R)
squared_distance(
    const Point_3<R> &pt,
    const Segment_3<R> &seg);


template <class R>
inline R_FT_return(R)
squared_distance(
    const Segment_3<R> & seg,
    const Point_3<R> & pt)
{
    return squared_distance(pt, seg);
}


template <class R>
extern R_FT_return(R)
squared_distance(
    const Segment_3<R> &,
    const Segment_3<R> &);


template <class R>
extern R_FT_return(R)
squared_distance(
    const Segment_3<R> &seg,
    const Ray_3<R> &ray);


template <class R>
inline R_FT_return(R)
squared_distance(
    const Ray_3<R> & ray,
    const Segment_3<R> & seg)
{
    return squared_distance(seg, ray);
}


template <class R>
extern R_FT_return(R)
squared_distance(
    const Segment_3<R> &seg,
    const Line_3<R> &line);


template <class R>
inline R_FT_return(R)
squared_distance(
    const Line_3<R> & line,
    const Segment_3<R> & seg)
{
    return squared_distance(seg, line);
}


template <class R>
extern R_FT_return(R)
squared_distance(
    const Ray_3<R> &ray1,
    const Ray_3<R> &ray2);


template <class R>
extern R_FT_return(R)
squared_distance(
    const Line_3<R> &line,
    const Ray_3<R> &ray);


template <class R>
inline R_FT_return(R)
squared_distance(
    const Ray_3<R> & ray,
    const Line_3<R> & line)
{
    return squared_distance(line, ray);
}



template <class R>
extern R_FT_return(R)
squared_distance(
    const Line_3<R> &line1,
    const Line_3<R> &line2);


CGAL_END_NAMESPACE

#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#include <CGAL/squared_distance_3_1.C>
#endif


#endif
