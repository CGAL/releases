//  Copyright CGAL 1996
//
//  cgal@cs.ruu.nl
//
//  This file is part of an internal release of the CGAL kernel.
//  The code herein may be used and/or copied only in accordance
//  with the terms and conditions stipulated in the agreement
//  under which the code has been supplied or with the written
//  permission of the CGAL Project.
//
//  Look at http://www.cs.ruu.nl/CGAL/ for more information.
//  Please send any bug reports and comments to cgal@cs.ruu.nl
//
//  The code comes WITHOUT ANY WARRANTY; without even the implied
//  warranty of FITNESS FOR A PARTICULAR PURPOSE.
//

// Author: Geert-Jan Giezeman

#ifndef CGAL_INCLUDE_CODE
#include <CGAL/squared_distance_2_2.h>
#endif
#include <CGAL/utils.h>
#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Line_2.h>
#include <CGAL/Ray_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/enum.h>
#include <CGAL/wmult.h>
#include <CGAL/squared_distance_2_1.h>

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
    if (ind1 == -1)
        return R_FT_return(R)(R::FT(0));
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
    CGAL_Oriented_side side0;
    side0 = line.oriented_side(triangle.vertex(0));
    if (line.oriented_side(triangle.vertex(1)) != side0)
        return R_FT_return(R)(R::FT(0));
    if (line.oriented_side(triangle.vertex(2)) != side0)
        return R_FT_return(R)(R::FT(0));
    R::FT mindist, dist;
    int i;
    mindist = CGAL_squared_distance(triangle.vertex(0),line);
    for (i=1; i<3; i++) {
        dist = CGAL_squared_distance(triangle.vertex(i),line);
        if (dist < mindist)
            mindist = dist;
    }
    return R_FT_return(R)(mindist);
}

template <class R>
extern R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Ray_2<R> &ray,
    const CGAL_Triangle_2<R> &triangle)
{
    int i, ind_tr1, ind_tr2, ind_ray = 0, ind1;
    R::FT mindist, dist;
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
        return R_FT_return(R)(mindist);
    if (ind_tr2 != -1) {
// Check if all the segment vertices lie at the same side of
// the triangle segment.
        const CGAL_Point_2<R> &vt1 = triangle.vertex(ind_tr1);
        const CGAL_Point_2<R> &vt2 = triangle.vertex(ind_tr2);
        if (CGAL_clockwise(ray.direction().vector(), vt2-vt1)) {
            mindist = R::FT(0);
        }
    } else {
// Check if all the triangle vertices lie at the same side of the segment.
        const CGAL_Line_2<R> &sl = ray.supporting_line();
        CGAL_Oriented_side or = sl.oriented_side(triangle.vertex(0));
        for (int i=1; i<3; i++) {
            if (sl.oriented_side(triangle.vertex(i)) != or) {
                mindist = R::FT(0);
                break;
            }
        }
    }
    return R_FT_return(R)(mindist);
}

template <class R>
extern R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Segment_2<R> &seg,
    const CGAL_Triangle_2<R> &triangle)
{
    int i, ind_tr1 = 0, ind_tr2 = -1, ind_seg = 0, ind1, ind2;
    R::FT mindist, dist;
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
        return R_FT_return(R)(mindist);

    if (ind_tr2 != -1) {
// Check if all the segment vertices lie at the same side of
// the triangle segment.
        const CGAL_Point_2<R> &vt1 = triangle.vertex(ind_tr1);
        const CGAL_Point_2<R> &vt2 = triangle.vertex(ind_tr2);
        CGAL_Orientation or = CGAL_orientation(vt1, vt2, seg.source());
        if (CGAL_orientation(vt1, vt2, seg.target()) != or) {
            mindist = R::FT(0);
        }
    } else {
// Check if all the triangle vertices lie at the same side of the segment.
        const CGAL_Point_2<R> &vt1 = seg.source();
        const CGAL_Point_2<R> &vt2 = seg.target();
        CGAL_Orientation or = CGAL_orientation(vt1, vt2, triangle.vertex(0));
        for (int i=1; i<3; i++) {
            if (CGAL_orientation(vt1, vt2, triangle.vertex(i)) != or) {
                mindist = R::FT(0);
                break;
            }
        }
    }
    return R_FT_return(R)(mindist);
}

template <class R>
extern R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Triangle_2<R> &triangle1,
    const CGAL_Triangle_2<R> &triangle2)
{
    int i, ind1_1 = 0,ind1_2 = -1, ind2_1 = 0, ind2_2 = -1, ind1, ind2;
    R::FT mindist, dist;
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
        return R_FT_return(R)(mindist);
    // In case of point-segment closest distance, there is still the possibility
    // of overlapping triangles.
    // Check if all the vertices lie at the same side of the segment.
    if (ind1_2 != -1) {
        const CGAL_Point_2<R> &vt1 = triangle1.vertex(ind1_1);
        const CGAL_Point_2<R> &vt2 = triangle1.vertex(ind1_2);
        CGAL_Orientation or = CGAL_orientation(vt1, vt2, triangle2.vertex(0));
        for (int i=1; i<3; i++) {
            if (CGAL_orientation(vt1, vt2, triangle2.vertex(i)) != or) {
                mindist = R::FT(0);
                break;
            }
        }
    } else {
        const CGAL_Point_2<R> &vt1 = triangle2.vertex(ind2_1);
        const CGAL_Point_2<R> &vt2 = triangle2.vertex(ind2_2);
        CGAL_Orientation or = CGAL_orientation(vt1, vt2, triangle1.vertex(0));
        for (int i=1; i<3; i++) {
            if (CGAL_orientation(vt1, vt2, triangle1.vertex(i)) != or) {
                mindist = R::FT(0);
                break;
            }
        }
    }
    return R_FT_return(R)(mindist);
}

