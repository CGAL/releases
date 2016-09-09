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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/squared_distance_2_2.h
// package       : Distance_2 (1.5)
// source        : sqdistance_2.fw
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : Saarbruecken
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_SQUARED_DISTANCE_2_2_H
#define CGAL_SQUARED_DISTANCE_2_2_H

#ifndef CGAL_USER_CLASSES_H
#include <CGAL/user_classes.h>
#endif // CGAL_USER_CLASSES_H



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



#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#include <CGAL/squared_distance_2_2.C>
#endif


#endif
