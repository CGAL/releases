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
// file          : include/CGAL/squared_distance_2_1.h
// package       : Distance_2 (2.1.2)
// source        : sqdistance_2.fw
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : Saarbruecken
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_SQUARED_DISTANCE_2_1_H
#define CGAL_SQUARED_DISTANCE_2_1_H

#ifndef CGAL_USER_CLASSES_H
#include <CGAL/user_classes.h>
#endif // CGAL_USER_CLASSES_H

CGAL_BEGIN_NAMESPACE

template <class R>
inline R_FT_return(R)
squared_distance(
    const Point_2<R> & pt1,
    const Point_2<R> & pt2)
{
    Vector_2<R> vec(pt1-pt2);
    return (R_FT_return(R))(vec*vec);
}


template <class R>
extern R_FT_return(R)
squared_distance(
    const Point_2<R> &pt,
    const Line_2<R> &line);

template <class R>
inline R_FT_return(R)
squared_distance(
    const Line_2<R> & line,
    const Point_2<R> & pt)
{
    return squared_distance(pt, line);
}

template <class R>
extern R_FT_return(R)
squared_distance(
    const Point_2<R> &pt,
    const Ray_2<R> &ray);

template <class R>
inline R_FT_return(R)
squared_distance(
    const Ray_2<R> & ray,
    const Point_2<R> & pt)
{
    return squared_distance(pt, ray);
}


template <class R>
extern void
distance_index(
    int &ind,
    const Point_2<R> &pt,
    const Ray_2<R> &ray);

template <class R>
extern R_FT_return(R)
squared_distance_indexed(const Point_2<R> &pt,
    const Ray_2<R> &ray, int ind1, int ind2);

template <class R>
extern R_FT_return(R)
squared_distance(
    const Point_2<R> &pt,
    const Segment_2<R> &seg);


template <class R>
inline R_FT_return(R)
squared_distance(
    const Segment_2<R> & seg,
    const Point_2<R> & pt)
{
    return squared_distance(pt, seg);
}


template <class R>
extern void
distance_index(
    int &ind,
    const Point_2<R> &pt,
    const Segment_2<R> &seg);

template <class R>
extern R_FT_return(R)
squared_distance_indexed(const Point_2<R> &pt,
    const Segment_2<R> &seg, int ind1, int ind2);

template <class R>
extern R_FT_return(R)
squared_distance(
    const Segment_2<R> &,
    const Segment_2<R> &);


template <class R>
extern R_FT_return(R)
squared_distance(
    const Segment_2<R> &seg,
    const Ray_2<R> &ray);


template <class R>
inline R_FT_return(R)
squared_distance(
    const Ray_2<R> & ray,
    const Segment_2<R> & seg)
{
    return squared_distance(seg, ray);
}


template <class R>
extern R_FT_return(R)
squared_distance(
    const Segment_2<R> &seg,
    const Line_2<R> &line);


template <class R>
inline R_FT_return(R)
squared_distance(
    const Line_2<R> & line,
    const Segment_2<R> & seg)
{
    return squared_distance(seg, line);
}


template <class R>
extern R_FT_return(R)
squared_distance(
    const Ray_2<R> &ray1,
    const Ray_2<R> &ray2);


template <class R>
extern R_FT_return(R)
squared_distance(
    const Line_2<R> &line,
    const Ray_2<R> &ray);


template <class R>
inline R_FT_return(R)
squared_distance(
    const Ray_2<R> & ray,
    const Line_2<R> & line)
{
    return squared_distance(line, ray);
}


template <class R>
extern R_FT_return(R)
squared_distance(
    const Line_2<R> &line1,
    const Line_2<R> &line2);


CGAL_END_NAMESPACE

#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#include <CGAL/squared_distance_2_1.C>
#endif


#endif
