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
// file          : include/CGAL/squared_distance_3_2.C
// package       : Distance_3 (1.5)
// source        : sqdistance_3.fw
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : Saarbruecken
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_UTILS_H
#include <CGAL/utils.h>
#endif // CGAL_UTILS_H
#ifndef CGAL_POINT_3_H
#include <CGAL/Point_3.h>
#endif // CGAL_POINT_3_H
#ifndef CGAL_PLANE_3_H
#include <CGAL/Plane_3.h>
#endif // CGAL_PLANE_3_H
#ifndef CGAL_ENUM_H
#include <CGAL/enum.h>
#endif // CGAL_ENUM_H
#ifndef CGAL_WMULT_H
#include <CGAL/wmult.h>
#endif // CGAL_WMULT_H
#ifndef CGAL_SQUARED_DISTANCE_3_0_H
#include <CGAL/squared_distance_3_0.h>
#endif // CGAL_SQUARED_DISTANCE_3_0_H


template <class R>
bool
contains_vector(const CGAL_Plane_3<R> &pl, const CGAL_Vector_3<R> &vec)
{
    typedef typename R::RT RT;
    return pl.a()*vec.hx() + pl.b()*vec.hy() + pl.c() * vec.hz() == RT(0);
}

template <class R>
inline R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Point_3<R> & pt,
    const CGAL_Plane_3<R> & plane)
{
    CGAL_Vector_3<R> diff(pt-plane.point());
    return CGAL_squared_distance_to_plane(plane.orthogonal_vector(), diff);
}


template <class R>
extern R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Line_3<R> &line,
    const CGAL_Plane_3<R> &plane)
{
    typedef typename R::FT FT;
    if (contains_vector(plane, line.direction().vector() ))
        return CGAL_squared_distance(plane, line.point());
    return (R_FT_return(R))(FT(0));
}

template <class R>
extern R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Ray_3<R> &ray,
    const CGAL_Plane_3<R> &plane)
{
    typedef typename R::RT RT;
    typedef typename R::FT FT;
    const CGAL_Point_3<R> &start = ray.start();
    const CGAL_Vector_3<R> &end = ray.direction().vector();
    const CGAL_Point_3<R> &planepoint = plane.point();
    CGAL_Vector_3<R> start_min_pp = start - planepoint;
    CGAL_Vector_3<R> end_min_pp = ray.direction().vector();
    const CGAL_Vector_3<R> &normal = plane.orthogonal_vector();
    RT sdm_rs2pp = CGAL_wdot(normal, start_min_pp);
    RT sdm_re2pp = CGAL_wdot(normal, end_min_pp);
    switch (CGAL_sign(sdm_rs2pp)) {
    case -1:
        if (sdm_re2pp > RT(0))
            return (R_FT_return(R))(FT(0));
        return CGAL_squared_distance_to_plane(normal, start_min_pp);
    case 0:
    default:
        return (R_FT_return(R))(FT(0));
    case 1:
        if (sdm_re2pp < RT(0))
            return (R_FT_return(R))(FT(0));
        return CGAL_squared_distance_to_plane(normal, start_min_pp);
    }
}

template <class R>
extern R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Segment_3<R> &seg,
    const CGAL_Plane_3<R> &plane)
{
    typedef typename R::RT RT;
    typedef typename R::FT FT;
    const CGAL_Point_3<R> &start = seg.start();
    const CGAL_Point_3<R> &end = seg.end();
    if (start == end)
        return CGAL_squared_distance(start, plane);
    const CGAL_Point_3<R> &planepoint = plane.point();
    CGAL_Vector_3<R> start_min_pp = start - planepoint;
    CGAL_Vector_3<R> end_min_pp = end - planepoint;
    const CGAL_Vector_3<R> &normal = plane.orthogonal_vector();
    RT sdm_ss2pp = CGAL_wdot(normal, start_min_pp);
    RT sdm_se2pp = CGAL_wdot(normal, end_min_pp);
    switch (CGAL_sign(sdm_ss2pp)) {
    case -1:
        if (sdm_se2pp >= RT(0))
            return (R_FT_return(R))(FT(0));
        if (sdm_ss2pp >= sdm_se2pp)
            return CGAL_squared_distance_to_plane(normal, start_min_pp);
        else
            return CGAL_squared_distance_to_plane(normal, end_min_pp);
    case 0:
    default:
        return (R_FT_return(R))(FT(0));
    case 1:
        if (sdm_se2pp <= RT(0))
            return (R_FT_return(R))(FT(0));
        if (sdm_ss2pp <= sdm_se2pp)
            return CGAL_squared_distance_to_plane(normal, start_min_pp);
        else
            return CGAL_squared_distance_to_plane(normal, end_min_pp);
    }
}

