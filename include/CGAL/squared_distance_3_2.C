/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/


// Author: Geert-Jan Giezeman

#include <CGAL/utils.h>
#include <CGAL/Point_3.h>
#include <CGAL/Plane_3.h>
#include <CGAL/enum.h>
#include <CGAL/wmult.h>
#include <CGAL/squared_distance_3_0.h>


template <class R>
bool
contains_vector(const CGAL_Plane_3<R> &pl, const CGAL_Vector_3<R> &vec)
{
    return pl.a()*vec.hx() + pl.b()*vec.hy() + pl.c() * vec.hz() == R::RT(0);
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
    if (contains_vector(plane, line.direction().vector() ))
        return CGAL_squared_distance(plane, line.point());
    return R_FT_return(R)(R::FT(0));
}

template <class R>
extern R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Ray_3<R> &ray,
    const CGAL_Plane_3<R> &plane)
{
    const CGAL_Point_3<R> &start = ray.start();
    const CGAL_Vector_3<R> &end = ray.direction().vector();
    const CGAL_Point_3<R> &planepoint = plane.point();
    CGAL_Vector_3<R> start_min_pp = start - planepoint;
    CGAL_Vector_3<R> end_min_pp = ray.direction().vector();
    const CGAL_Vector_3<R> &normal = plane.orthogonal_vector();
    R::RT sdm_rs2pp = CGAL_wdot(normal, start_min_pp);
    R::RT sdm_re2pp = CGAL_wdot(normal, end_min_pp);
    switch (CGAL_sign(sdm_rs2pp)) {
    case -1:
        if (sdm_re2pp > R::RT(0))
            return R_FT_return(R)(R::FT(0));
        return CGAL_squared_distance_to_plane(normal, start_min_pp);
    case 0:
    default:
        return R_FT_return(R)(R::FT(0));
    case 1:
        if (sdm_re2pp < R::RT(0))
            return R_FT_return(R)(R::FT(0));
        return CGAL_squared_distance_to_plane(normal, start_min_pp);
    }
}

template <class R>
extern R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Segment_3<R> &seg,
    const CGAL_Plane_3<R> &plane)
{
    const CGAL_Point_3<R> &start = seg.start();
    const CGAL_Point_3<R> &end = seg.end();
    if (start == end)
        return CGAL_squared_distance(start, plane);
    const CGAL_Point_3<R> &planepoint = plane.point();
    CGAL_Vector_3<R> start_min_pp = start - planepoint;
    CGAL_Vector_3<R> end_min_pp = end - planepoint;
    const CGAL_Vector_3<R> &normal = plane.orthogonal_vector();
    R::RT sdm_ss2pp = CGAL_wdot(normal, start_min_pp);
    R::RT sdm_se2pp = CGAL_wdot(normal, end_min_pp);
    switch (CGAL_sign(sdm_ss2pp)) {
    case -1:
        if (sdm_se2pp >= R::RT(0))
            return R_FT_return(R)(R::FT(0));
        if (sdm_ss2pp >= sdm_se2pp)
            return CGAL_squared_distance_to_plane(normal, start_min_pp);
        else
            return CGAL_squared_distance_to_plane(normal, end_min_pp);
    case 0:
    default:
        return R_FT_return(R)(R::FT(0));
    case 1:
        if (sdm_se2pp <= R::RT(0))
            return R_FT_return(R)(R::FT(0));
        if (sdm_ss2pp <= sdm_se2pp)
            return CGAL_squared_distance_to_plane(normal, start_min_pp);
        else
            return CGAL_squared_distance_to_plane(normal, end_min_pp);
    }
}

