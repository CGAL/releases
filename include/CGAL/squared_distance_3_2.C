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
// file          : include/CGAL/squared_distance_3_2.C
// package       : Distance_3 (2.1.1)
// source        : sqdistance_3.fw
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : Saarbruecken
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
#ifndef SQUARED_DISTANCE_3_0_H
#include <CGAL/squared_distance_3_0.h>
#endif // SQUARED_DISTANCE_3_0_H

CGAL_BEGIN_NAMESPACE



template <class R>
bool
contains_vector(const Plane_3<R> &pl, const Vector_3<R> &vec)
{
    typedef typename R::RT RT;
    return pl.a()*vec.hx() + pl.b()*vec.hy() + pl.c() * vec.hz() == RT(0);
}


template <class R>
inline R_FT_return(R)
squared_distance(
    const Point_3<R> & pt,
    const Plane_3<R> & plane)
{
    Vector_3<R> diff(pt-plane.point());
    return squared_distance_to_plane(plane.orthogonal_vector(), diff);
}



template <class R>
extern R_FT_return(R)
squared_distance(
    const Line_3<R> &line,
    const Plane_3<R> &plane)
{
    typedef typename R::FT FT;
    if (contains_vector(plane, line.direction().vector() ))
        return squared_distance(plane, line.point());
    return (R_FT_return(R))(FT(0));
}

template <class R>
extern R_FT_return(R)
squared_distance(
    const Ray_3<R> &ray,
    const Plane_3<R> &plane)
{
    typedef typename R::RT RT;
    typedef typename R::FT FT;
    const Point_3<R> &start = ray.start();
//    const Vector_3<R> &end = ray.direction().vector();
    const Point_3<R> &planepoint = plane.point();
    Vector_3<R> start_min_pp = start - planepoint;
    Vector_3<R> end_min_pp = ray.direction().vector();
    const Vector_3<R> &normal = plane.orthogonal_vector();
    RT sdm_rs2pp = wdot(normal, start_min_pp);
    RT sdm_re2pp = wdot(normal, end_min_pp);
    switch (sign(sdm_rs2pp)) {
    case -1:
        if (sdm_re2pp > RT(0))
            return (R_FT_return(R))(FT(0));
        return squared_distance_to_plane(normal, start_min_pp);
    case 0:
    default:
        return (R_FT_return(R))(FT(0));
    case 1:
        if (sdm_re2pp < RT(0))
            return (R_FT_return(R))(FT(0));
        return squared_distance_to_plane(normal, start_min_pp);
    }
}


template <class R>
extern R_FT_return(R)
squared_distance(
    const Segment_3<R> &seg,
    const Plane_3<R> &plane)
{
    typedef typename R::RT RT;
    typedef typename R::FT FT;
    const Point_3<R> &start = seg.start();
    const Point_3<R> &end = seg.end();
    if (start == end)
        return squared_distance(start, plane);
    const Point_3<R> &planepoint = plane.point();
    Vector_3<R> start_min_pp = start - planepoint;
    Vector_3<R> end_min_pp = end - planepoint;
    const Vector_3<R> &normal = plane.orthogonal_vector();
    RT sdm_ss2pp = wdot(normal, start_min_pp);
    RT sdm_se2pp = wdot(normal, end_min_pp);
    switch (sign(sdm_ss2pp)) {
    case -1:
        if (sdm_se2pp >= RT(0))
            return (R_FT_return(R))(FT(0));
        if (sdm_ss2pp >= sdm_se2pp)
            return squared_distance_to_plane(normal, start_min_pp);
        else
            return squared_distance_to_plane(normal, end_min_pp);
    case 0:
    default:
        return (R_FT_return(R))(FT(0));
    case 1:
        if (sdm_se2pp <= RT(0))
            return (R_FT_return(R))(FT(0));
        if (sdm_ss2pp <= sdm_se2pp)
            return squared_distance_to_plane(normal, start_min_pp);
        else
            return squared_distance_to_plane(normal, end_min_pp);
    }
}


CGAL_END_NAMESPACE

