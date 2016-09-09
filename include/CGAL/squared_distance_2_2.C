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
// file          : include/CGAL/squared_distance_2_2.C
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


#ifndef CGAL_UTILS_H
#include <CGAL/utils.h>
#endif // CGAL_UTILS_H
#ifndef CGAL_POINT_2_H
#include <CGAL/Point_2.h>
#endif // CGAL_POINT_2_H
#ifndef CGAL_SEGMENT_2_H
#include <CGAL/Segment_2.h>
#endif // CGAL_SEGMENT_2_H
#ifndef CGAL_LINE_2_H
#include <CGAL/Line_2.h>
#endif // CGAL_LINE_2_H
#ifndef CGAL_RAY_2_H
#include <CGAL/Ray_2.h>
#endif // CGAL_RAY_2_H
#ifndef CGAL_TRIANGLE_2_H
#include <CGAL/Triangle_2.h>
#endif // CGAL_TRIANGLE_2_H
#ifndef CGAL_ENUM_H
#include <CGAL/enum.h>
#endif // CGAL_ENUM_H
#ifndef CGAL_WMULT_H
#include <CGAL/wmult.h>
#endif // CGAL_WMULT_H
#ifndef CGAL_SQUARED_DISTANCE_UTILS_H
#include <CGAL/squared_distance_utils.h>
#endif // CGAL_SQUARED_DISTANCE_UTILS_H
#ifndef CGAL_SQUARED_DISTANCE_2_1_H
#include <CGAL/squared_distance_2_1.h>
#endif // CGAL_SQUARED_DISTANCE_2_1_H

template <class R>
extern void
CGAL_distance_index(
    int &ind1,
    int &ind2,
    const CGAL_Point_2<R> &pt,
    const CGAL_Triangle_2<R> &triangle)
{
    const CGAL_Point_2<R> &vt0 = triangle.vertex(0);
    const CGAL_Point_2<R> &vt1 = triangle.vertex(1);
    const CGAL_Point_2<R> &vt2 = triangle.vertex(2);
    if (CGAL_leftturn(vt0, vt1, vt2)) {
        if (CGAL_rightturn(vt0, vt1, pt)) {
            if (!CGAL_is_acute_angle(vt0, vt1, pt)) {
                if (CGAL_rightturn(vt1, vt2, pt)) {
                    if (!CGAL_is_acute_angle(vt1, vt2, pt)) {
                        ind1 = 2; ind2 = -1;
                        return;
                    }
                    if (!CGAL_is_acute_angle(vt2, vt1, pt)) {
                        ind1 = 1; ind2 = -1;
                        return;
                    }
                    ind1 = 1; ind2 = 2;
                    return;
                }
                ind1 = 1; ind2 = -1;
                return;
            }
            if (!CGAL_is_acute_angle(vt1, vt0, pt)) {
                if (CGAL_rightturn(vt2, vt0, pt)) {
                    if (!CGAL_is_acute_angle(vt0, vt2, pt)) {
                        ind1 = 2; ind2 = -1;
                        return;
                    }
                    if (!CGAL_is_acute_angle(vt2, vt0, pt)) {
                        ind1 = 0; ind2 = -1;
                        return;
                    }
                    ind1 = 2; ind2 = 0;
                    return;
                }
                ind1 = 0; ind2 = -1;
                return;
            }
            ind1 = 0; ind2 = 1;
            return;
        } else {
            if (CGAL_rightturn(vt1, vt2, pt)) {
                if (!CGAL_is_acute_angle(vt1, vt2, pt)) {
                    if (CGAL_rightturn(vt2, vt0, pt)) {
                        if (!CGAL_is_acute_angle(vt0, vt2, pt)) {
                            ind1 = 2; ind2 = -1;
                            return;
                        }
                        if (!CGAL_is_acute_angle(vt2, vt0, pt)) {
                            ind1 = 0; ind2 = -1;
                            return;
                        }
                        ind1 = 2; ind2 = 0;
                        return;
                    }
                    ind1 = 0; ind2 = -1;
                    return;
                }
                if (!CGAL_is_acute_angle(vt2, vt1, pt)) {
                    ind1 = 1; ind2 = -1;
                    return;
                }
                ind1 = 1; ind2 = 2;
                return;
            } else {
                if (CGAL_rightturn(vt2, vt0, pt)) {
                    if (!CGAL_is_acute_angle(vt2, vt0, pt)) {
                        ind1 = 0; ind2 = -1;
                        return;
                    }
                    if (!CGAL_is_acute_angle(vt0, vt2, pt)) {
                        ind1 = 2; ind2 = -1;
                        return;
                    }
                    ind1 = 2; ind2 = 0;
                    return;
                } else {
                    ind1 = -1; ind2 = -1; // point inside or on boundary.
                    return;
                }
            }
        }
    } else {
        if (CGAL_rightturn(vt0, vt2, pt)) {
            if (!CGAL_is_acute_angle(vt0, vt2, pt)) {
                if (CGAL_rightturn(vt2, vt1, pt)) {
                    if (!CGAL_is_acute_angle(vt2, vt1, pt)) {
                        ind1 = 1; ind2 = -1;
                        return;
                    }
                    if (!CGAL_is_acute_angle(vt1, vt2, pt)) {
                        ind1 = 2; ind2 = -1;
                        return;
                    }
                    ind1 = 2; ind2 = 1;
                    return;
                }
                ind1 = 2; ind2 = -1;
                return;
            }
            if (!CGAL_is_acute_angle(vt2, vt0, pt)) {
                if (CGAL_rightturn(vt1, vt0, pt)) {
                    if (!CGAL_is_acute_angle(vt0, vt1, pt)) {
                        ind1 = 1; ind2 = -1;
                        return;
                    }
                    if (!CGAL_is_acute_angle(vt1, vt0, pt)) {
                        ind1 = 0; ind2 = -1;
                        return;
                    }
                    ind1 = 1; ind2 = 0;
                    return;
                }
                ind1 = 0; ind2 = -1;
                return;
            }
            ind1 = 0; ind2 = 2;
            return;
        } else {
            if (CGAL_rightturn(vt2, vt1, pt)) {
                if (!CGAL_is_acute_angle(vt2, vt1, pt)) {
                    if (CGAL_rightturn(vt1, vt0, pt)) {
                        if (!CGAL_is_acute_angle(vt0, vt1, pt)) {
                            ind1 = 1; ind2 = -1;
                            return;
                        }
                        if (!CGAL_is_acute_angle(vt1, vt0, pt)) {
                            ind1 = 0; ind2 = -1;
                            return;
                        }
                        ind1 = 1; ind2 = 0;
                        return;
                    }
                    ind1 = 0; ind2 = -1;
                    return;
                }
                if (!CGAL_is_acute_angle(vt1, vt2, pt)) {
                    ind1 = 2; ind2 = -1;
                    return;
                }
                ind1 = 2; ind2 = 1;
                return;
            } else {
                if (CGAL_rightturn(vt1, vt0, pt)) {
                    if (!CGAL_is_acute_angle(vt1, vt0, pt)) {
                        ind1 = 0; ind2 = -1;
                        return;
                    }
                    if (!CGAL_is_acute_angle(vt0, vt1, pt)) {
                        ind1 = 1; ind2 = -1;
                        return;
                    }
                    ind1 = 1; ind2 = 0;
                    return;
                } else {
                    ind1 = -1; ind2 = -1; // point inside or on boundary.
                    return;
                }
            }
        }
    }
}

template <class R>
extern R_FT_return(R)
CGAL_squared_distance_indexed(const CGAL_Point_2<R> &pt,
    const CGAL_Triangle_2<R> &triangle, int ind1, int ind2)
{
    typedef typename R::FT FT;
    if (ind1 == -1)
        return (R_FT_return(R))(FT(0));
    if (ind2 == -1)
        return CGAL_squared_distance(pt, triangle.vertex(ind1));
    return CGAL_squared_distance(pt,
        CGAL_Line_2<R>(triangle.vertex(ind1), triangle.vertex(ind2)));
}

template <class R>
extern R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Point_2<R> &pt,
    const CGAL_Triangle_2<R> &triangle)
{
    int ind1,ind2;
    CGAL_distance_index(ind1, ind2, pt, triangle);
    return CGAL_squared_distance_indexed(pt, triangle, ind1, ind2);
}

template <class R>
extern R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Line_2<R> &line,
    const CGAL_Triangle_2<R> &triangle)
{
    typedef typename R::FT FT;
    CGAL_Oriented_side side0;
    side0 = line.oriented_side(triangle.vertex(0));
    if (line.oriented_side(triangle.vertex(1)) != side0)
        return (R_FT_return(R))(FT(0));
    if (line.oriented_side(triangle.vertex(2)) != side0)
        return (R_FT_return(R))(FT(0));
    FT mindist, dist;
    int i;
    mindist = CGAL_squared_distance(triangle.vertex(0),line);
    for (i=1; i<3; i++) {
        dist = CGAL_squared_distance(triangle.vertex(i),line);
        if (dist < mindist)
            mindist = dist;
    }
    return (R_FT_return(R))(mindist);
}

template <class R>
extern R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Ray_2<R> &ray,
    const CGAL_Triangle_2<R> &triangle)
{
    typedef typename R::FT FT;
    int i, ind_tr1, ind_tr2, ind_ray = 0, ind1;
    FT mindist, dist;
    CGAL_distance_index(ind_tr1, ind_tr2, ray.source(), triangle);
    mindist =
        CGAL_squared_distance_indexed(ray.source(), triangle, ind_tr1,ind_tr2);
    for (i=0; i<3; i++) {
        const CGAL_Point_2<R>& pt = triangle.vertex(i);
        CGAL_distance_index(ind1, pt, ray);
        dist = CGAL_squared_distance_indexed(pt, ray, ind1);
        if (dist < mindist) {
            ind_ray = ind1;
            ind_tr1 = i; ind_tr2 = -1;
            mindist = dist;
        }
    }
    // now check if all vertices are on the right side of the separating line.
    // In case of vertex-vertex smallest distance this is the case.
    if (ind_tr2 == -1 && ind_ray != -1)
        return (R_FT_return(R))(mindist);
    if (ind_tr2 != -1) {
// Check if all the segment vertices lie at the same side of
// the triangle segment.
        const CGAL_Point_2<R> &vt1 = triangle.vertex(ind_tr1);
        const CGAL_Point_2<R> &vt2 = triangle.vertex(ind_tr2);
        if (CGAL_clockwise(ray.direction().vector(), vt2-vt1)) {
            mindist = FT(0);
        }
    } else {
// Check if all the triangle vertices lie at the same side of the segment.
        const CGAL_Line_2<R> &sl = ray.supporting_line();
        CGAL_Oriented_side or = sl.oriented_side(triangle.vertex(0));
        for (i=1; i<3; i++) {
            if (sl.oriented_side(triangle.vertex(i)) != or) {
                mindist = FT(0);
                break;
            }
        }
    }
    return (R_FT_return(R))(mindist);
}

template <class R>
extern R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Segment_2<R> &seg,
    const CGAL_Triangle_2<R> &triangle)
{
    typedef typename R::FT FT;
    int i, ind_tr1 = 0, ind_tr2 = -1, ind_seg = 0, ind1, ind2;
    FT mindist, dist;
    mindist = CGAL_squared_distance(seg.source(), triangle.vertex(0));
    for (i=0; i<2; i++) {
        const CGAL_Point_2<R> &pt = seg.vertex(i);
        CGAL_distance_index(ind1, ind2, pt, triangle);
        dist = CGAL_squared_distance_indexed(pt, triangle, ind1, ind2);
        if (dist < mindist) {
            ind_seg = i;
            ind_tr1 = ind1; ind_tr2 = ind2;
            mindist = dist;
        }
    }
    for (i=0; i<3; i++) {
        const CGAL_Point_2<R>& pt = triangle.vertex(i);
        CGAL_distance_index(ind1, pt, seg);
        dist = CGAL_squared_distance_indexed(pt, seg, ind1);
        if (dist < mindist) {
            ind_seg = ind1;
            ind_tr1 = i; ind_tr2 = -1;
            mindist = dist;
        }
    }
    // now check if all vertices are on the right side of the separating line.
    // In case of vertex-vertex smallest distance this is the case.
    if (ind_tr2 == -1 && ind_seg != -1)
        return (R_FT_return(R))(mindist);

    if (ind_tr2 != -1) {
// Check if all the segment vertices lie at the same side of
// the triangle segment.
        const CGAL_Point_2<R> &vt1 = triangle.vertex(ind_tr1);
        const CGAL_Point_2<R> &vt2 = triangle.vertex(ind_tr2);
        CGAL_Orientation or = CGAL_orientation(vt1, vt2, seg.source());
        if (CGAL_orientation(vt1, vt2, seg.target()) != or) {
            mindist = FT(0);
        }
    } else {
// Check if all the triangle vertices lie at the same side of the segment.
        const CGAL_Point_2<R> &vt1 = seg.source();
        const CGAL_Point_2<R> &vt2 = seg.target();
        CGAL_Orientation or = CGAL_orientation(vt1, vt2, triangle.vertex(0));
        for (i=1; i<3; i++) {
            if (CGAL_orientation(vt1, vt2, triangle.vertex(i)) != or) {
                mindist = FT(0);
                break;
            }
        }
    }
    return (R_FT_return(R))(mindist);
}

template <class R>
extern R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Triangle_2<R> &triangle1,
    const CGAL_Triangle_2<R> &triangle2)
{
    typedef typename R::FT FT;
    int i, ind1_1 = 0,ind1_2 = -1, ind2_1 = 0, ind2_2 = -1, ind1, ind2;
    FT mindist, dist;
    mindist =
       CGAL_squared_distance(triangle1.vertex(0), triangle2.vertex(0));
    for (i=0; i<3; i++) {
        const CGAL_Point_2<R>& pt = triangle1.vertex(i);
        CGAL_distance_index(ind1, ind2, pt, triangle2);
        dist = CGAL_squared_distance_indexed(pt, triangle2, ind1, ind2);
        if (dist < mindist) {
            ind1_1 = i; ind1_2 = -1;
            ind2_1 = ind1; ind2_2 = ind2;
            mindist = dist;
        }
    }
    for (i=0; i<3; i++) {
        const CGAL_Point_2<R>& pt = triangle2.vertex(i);
        CGAL_distance_index(ind1, ind2, pt, triangle1);
        dist = CGAL_squared_distance_indexed(pt, triangle1, ind1, ind2);
        if (dist < mindist) {
            ind1_1 = ind1; ind1_2 = ind2;
            ind2_1 = i; ind2_2 = -1;
            mindist = dist;
        }
    }
    // now check if all vertices are on the right side of the separating line.
    if (ind1_2 == -1 && ind2_2 == -1)
        return (R_FT_return(R))(mindist);
    // In case of point-segment closest distance, there is still the possibility
    // of overlapping triangles.
    // Check if all the vertices lie at the same side of the segment.
    if (ind1_2 != -1) {
        const CGAL_Point_2<R> &vt1 = triangle1.vertex(ind1_1);
        const CGAL_Point_2<R> &vt2 = triangle1.vertex(ind1_2);
        CGAL_Orientation or = CGAL_orientation(vt1, vt2, triangle2.vertex(0));
        for (i=1; i<3; i++) {
            if (CGAL_orientation(vt1, vt2, triangle2.vertex(i)) != or) {
                mindist = FT(0);
                break;
            }
        }
    } else {
        const CGAL_Point_2<R> &vt1 = triangle2.vertex(ind2_1);
        const CGAL_Point_2<R> &vt2 = triangle2.vertex(ind2_2);
        CGAL_Orientation or = CGAL_orientation(vt1, vt2, triangle1.vertex(0));
        for (i=1; i<3; i++) {
            if (CGAL_orientation(vt1, vt2, triangle1.vertex(i)) != or) {
                mindist = FT(0);
                break;
            }
        }
    }
    return (R_FT_return(R))(mindist);
}

