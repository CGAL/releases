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
#include <CGAL/enum.h>
#include <CGAL/wmult.h>
#include <CGAL/squared_distance_3_0.h>


template <class R>
R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Point_3<R> &pt,
    const CGAL_Line_3<R> &line)
{
    CGAL_Vector_3<R> dir(line.direction().vector());
    CGAL_Vector_3<R> diff = pt - line.point();
    return CGAL_squared_distance_to_line(dir, diff);
}

template <class R>
extern R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Point_3<R> &pt,
    const CGAL_Ray_3<R> &ray)
{
    CGAL_Vector_3<R> diff = pt-ray.start();
    const CGAL_Vector_3<R> &dir = ray.direction().vector();
    if (!CGAL_is_acute_angle(dir,diff) )
        return R_FT_return(R)(diff*diff);
    return CGAL_squared_distance_to_line(dir, diff);
}

template <class R>
R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Point_3<R> &pt,
    const CGAL_Segment_3<R> &seg)
{
    // assert that the segment is valid (non zero length).
    CGAL_Vector_3<R> diff = pt-seg.start();
    CGAL_Vector_3<R> segvec = seg.end()-seg.start();
    R::RT d = CGAL_wdot(diff,segvec);
    if (d <= (R::RT)0)
        return R_FT_return(R)(R::FT(diff*diff));
    R::RT e = CGAL_wdot(segvec,segvec);
    if (CGAL_wmult((R*)0 ,d, segvec.hw()) > CGAL_wmult((R*)0, e, diff.hw()))
        return CGAL_squared_distance(pt, seg.end());
    return CGAL_squared_distance_to_line(segvec, diff);
}



template <class R>
R_FT_return(R)
CGAL_squared_distance_parallel(
    const CGAL_Segment_3<R> &seg1,
    const CGAL_Segment_3<R> &seg2)
{
    bool same_direction;
    const CGAL_Vector_3<R> &dir1 = seg1.direction().vector();
    const CGAL_Vector_3<R> &dir2 = seg2.direction().vector();
    if (CGAL_abs(dir1.hx()) > CGAL_abs(dir1.hy())) {
        if (CGAL_abs(dir1.hx()) > CGAL_abs(dir1.hz())) {
            same_direction = (CGAL_sign(dir1.hx()) == CGAL_sign(dir2.hx()));
        } else {
            same_direction = (CGAL_sign(dir1.hz()) == CGAL_sign(dir2.hz()));
        }
    } else {
        if (CGAL_abs(dir1.hy()) > CGAL_abs(dir1.hz())) {
            same_direction = (CGAL_sign(dir1.hy()) == CGAL_sign(dir2.hy()));
        } else {
            same_direction = (CGAL_sign(dir1.hz()) == CGAL_sign(dir2.hz()));
        }
    }
    if (same_direction) {
        if (!CGAL_is_acute_angle(seg1.start(), seg1.end(), seg2.start()))
            return CGAL_squared_distance(seg1.end(), seg2.start());
        if (!CGAL_is_acute_angle(seg1.end(), seg1.start(), seg2.end()))
            return CGAL_squared_distance(seg1.start(), seg2.end());
    } else {
        if (!CGAL_is_acute_angle(seg1.start(), seg1.end(), seg2.end()))
            return CGAL_squared_distance(seg1.end(), seg2.end());
        if (!CGAL_is_acute_angle(seg1.end(), seg1.start(), seg2.start()))
            return CGAL_squared_distance(seg1.start(), seg2.start());
    }
    return CGAL_squared_distance(seg2.start(), seg1.supporting_line());
}


template <class RT, class R>
RT CGAL__distance_measure_sub(RT startwdist, RT endwdist,
const CGAL_Vector_3<R> &start, const CGAL_Vector_3<R> &end
)
{
    return  CGAL_abs(CGAL_wmult((R*)0, startwdist, end.hw())) -
            CGAL_abs(CGAL_wmult((R*)0, endwdist, start.hw()));
}

template <class R>
R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Segment_3<R> &seg1,
    const CGAL_Segment_3<R> &seg2)
{
    const CGAL_Point_3<R> &start1 = seg1.start();
    const CGAL_Point_3<R> &start2 = seg2.start();
    const CGAL_Point_3<R> &end1 = seg1.end();
    const CGAL_Point_3<R> &end2 = seg2.end();

    if (start1 == end1)
        return CGAL_squared_distance(start1, seg2);
    if (start2 == end2)
        return CGAL_squared_distance(start2, seg1);
    
    CGAL_Vector_3<R> dir1, dir2, normal;
    dir1 = seg1.direction().vector();
    dir2 = seg2.direction().vector();
    normal = CGAL_wcross(dir1, dir2);
    if (CGAL_is_null(normal))
        return CGAL_squared_distance_parallel(seg1, seg2);
    
    bool crossing1, crossing2;
    R::RT sdm_s1to2, sdm_e1to2, sdm_s2to1, sdm_e2to1;
    CGAL_Vector_3<R> perpend1, perpend2, s2mins1, e2mins1, e1mins2;
    perpend1 = CGAL_wcross(dir1, normal);
    perpend2 = CGAL_wcross(dir2, normal);
    s2mins1 = start2-start1;
    e2mins1 = end2-start1;
    e1mins2 = end1-start2;
    sdm_s1to2 = -R::RT(CGAL_wdot(perpend2, s2mins1));
    sdm_e1to2 = CGAL_wdot(perpend2, e1mins2);
    sdm_s2to1 = CGAL_wdot(perpend1, s2mins1);
    sdm_e2to1 = CGAL_wdot(perpend1, e2mins1);
    
    if (sdm_s1to2 < R::RT(0)) {
        crossing1 = (sdm_e1to2 >= R::RT(0));
    } else {
        if (sdm_e1to2 <= R::RT(0)) {
            crossing1 = true;
        } else {
            crossing1 = (sdm_s1to2 == R::RT(0));
        }
    }
    if (sdm_s2to1 < R::RT(0)) {
        crossing2 = (sdm_e2to1 >= R::RT(0));
    } else {
        if (sdm_e2to1 <= R::RT(0)) {
            crossing2 = true;
        } else {
            crossing2 = (sdm_s2to1 == R::RT(0));
        }
    }
    
    if (crossing1) {
        if (crossing2) {
            return CGAL_squared_distance_to_plane(normal, s2mins1);
        }
    
        R::RT dm;
        dm = CGAL__distance_measure_sub(sdm_s2to1, sdm_e2to1, s2mins1, e2mins1);
        if (dm < R::RT(0)) {
            return CGAL_squared_distance(start2, seg1);
        } else {
            if (dm > R::RT(0)) {
                return CGAL_squared_distance(end2, seg1);
            } else {
                // should not happen with exact arithmetic.
                return CGAL_squared_distance_parallel(seg1, seg2);
            }
        }
    } else {
        if (crossing2) {
            R::RT dm;
            dm = CGAL__distance_measure_sub(sdm_s1to2, sdm_e1to2, s2mins1, e1mins2);
            if (dm < R::RT(0)) {
                return CGAL_squared_distance(start1, seg2);
            } else {
                if (dm > R::RT(0)) {
                    return CGAL_squared_distance(end1, seg2);
                } else {
                    // should not happen with exact arithmetic.
                    return CGAL_squared_distance_parallel(seg1, seg2);
                }
            }
        } else {
    
            R::FT min1, min2;
            R::RT dm;
            dm = CGAL__distance_measure_sub(sdm_s1to2, sdm_e1to2, s2mins1, e1mins2);
            if (dm == R::RT(0)) // should not happen with exact arithmetic.
               return CGAL_squared_distance_parallel(seg1, seg2);
            min1 = (dm < R::RT(0)) ?
                CGAL_squared_distance(seg1.start(), seg2):
                CGAL_squared_distance(end1, seg2);
            dm = CGAL__distance_measure_sub(sdm_s2to1, sdm_e2to1, s2mins1, e2mins1);
            if (dm == R::RT(0)) // should not happen with exact arithmetic.
                return CGAL_squared_distance_parallel(seg1, seg2);
            min2 = (dm < R::RT(0)) ?
                CGAL_squared_distance(start2, seg1):
                CGAL_squared_distance(end2, seg1);
            return (min1 < min2) ? R_FT_return(R)(min1) : R_FT_return(R)(min2);
        }
    }
    
}



template <class R>
R_FT_return(R)
CGAL_squared_distance_parallel(
    const CGAL_Segment_3<R> &seg,
    const CGAL_Ray_3<R> &ray)
{
    bool same_direction;
    const CGAL_Vector_3<R> &dir1 = seg.direction().vector();
    const CGAL_Vector_3<R> &dir2 = ray.direction().vector();
    if (CGAL_abs(dir1.hx()) > CGAL_abs(dir1.hy())) {
        same_direction = (CGAL_sign(dir1.hx()) == CGAL_sign(dir2.hx()));
    } else {
        same_direction = (CGAL_sign(dir1.hy()) == CGAL_sign(dir2.hy()));
    }
    if (same_direction) {
        if (!CGAL_is_acute_angle(seg.start(), seg.end(), ray.start()))
            return CGAL_squared_distance(seg.end(), ray.start());
    } else {
        if (!CGAL_is_acute_angle(seg.end(), seg.start(), ray.start()))
            return CGAL_squared_distance(seg.start(), ray.start());
    }
    return CGAL_squared_distance(ray.start(), seg.supporting_line());
}


template <class R>
R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Segment_3<R> &seg,
    const CGAL_Ray_3<R> &ray)
{
    const CGAL_Point_3<R> & ss (seg.start());
    const CGAL_Point_3<R> & se (seg.end());
    if (ss == se)
        return CGAL_squared_distance(ss, ray);
    CGAL_Vector_3<R> raydir, segdir, normal;
    raydir = ray.direction().vector();
    segdir = seg.direction().vector();
    normal = CGAL_wcross(segdir, raydir);
    if (CGAL_is_null(normal))
        return CGAL_squared_distance_parallel(seg, ray);

    bool crossing1, crossing2;
    R::RT sdm_ss2r, sdm_se2r, sdm_rs2s, sdm_re2s;
    CGAL_Vector_3<R> perpend2seg, perpend2ray, ss_min_rs, se_min_rs;
    perpend2seg = CGAL_wcross(segdir, normal);
    perpend2ray = CGAL_wcross(raydir, normal);
    ss_min_rs = ss-ray.start();
    se_min_rs = se-ray.start();
    sdm_ss2r = CGAL_wdot(perpend2ray, ss_min_rs);
    sdm_se2r = CGAL_wdot(perpend2ray, se_min_rs);
    if (sdm_ss2r < R::RT(0)) {
        crossing1 = (sdm_se2r >= R::RT(0));
    } else {
        if (sdm_se2r <= R::RT(0)) {
            crossing1 = true;
        } else {
            crossing1 = (sdm_ss2r == R::RT(0));
        }
    }

    sdm_rs2s = -R::RT(CGAL_wdot(perpend2seg, ss_min_rs));
    sdm_re2s = CGAL_wdot(perpend2seg, raydir);
    if (sdm_rs2s < R::RT(0)) {
        crossing2 = (sdm_re2s >= R::RT(0));
    } else {
        if (sdm_re2s <= R::RT(0)) {
            crossing2 = true;
        } else {
            crossing2 = (sdm_rs2s == R::RT(0));
        }
    }

    if (crossing1) {
        if (crossing2) {
            return CGAL_squared_distance_to_plane(normal, ss_min_rs);
        }
        return CGAL_squared_distance(ray.start(), seg);
    } else {
        if (crossing2) {
            R::RT dm;
            dm = CGAL__distance_measure_sub(
                    sdm_ss2r, sdm_se2r, ss_min_rs, se_min_rs);
            if (dm < R::RT(0)) {
                return CGAL_squared_distance(ss, ray);
            } else {
                if (dm > R::RT(0)) {
                    return CGAL_squared_distance(se, ray);
                } else {
                    // parallel, should not happen (no crossing)
                    return CGAL_squared_distance_parallel(seg, ray);
                }
            }
        } else {
            R::FT min1, min2;
            R::RT dm;
            dm = CGAL__distance_measure_sub(
                    sdm_ss2r, sdm_se2r, ss_min_rs, se_min_rs);
            if (dm == R::RT(0))
                return CGAL_squared_distance_parallel(seg, ray);
            min1 = (dm < R::RT(0))
                 ? CGAL_squared_distance(ss, ray)
                 : CGAL_squared_distance(se, ray);
            min2 = CGAL_squared_distance(ray.start(), seg);
            return (min1 < min2) ? R_FT_return(R)(min1) : R_FT_return(R)(min2);
        }
    }
}



template <class R>
R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Segment_3<R> &seg,
    const CGAL_Line_3<R> &line)
{
    const CGAL_Point_3<R> &linepoint = line.point();
    const CGAL_Point_3<R> &start = seg.start();
    const CGAL_Point_3<R> &end = seg.end();

    if (start == end)
        return CGAL_squared_distance(start, line);
    CGAL_Vector_3<R> linedir = line.direction().vector();
    CGAL_Vector_3<R> segdir = seg.direction().vector();
    CGAL_Vector_3<R> normal = CGAL_wcross(segdir, linedir);
    if (CGAL_is_null(normal))
        return CGAL_squared_distance_to_line(linedir, start-linepoint);

    bool crossing;
    R::RT sdm_ss2l, sdm_se2l;
    CGAL_Vector_3<R> perpend2line, start_min_lp, end_min_lp;
    perpend2line = CGAL_wcross(linedir, normal);
    start_min_lp = start-linepoint;
    end_min_lp = end-linepoint;
    sdm_ss2l = CGAL_wdot(perpend2line, start_min_lp);
    sdm_se2l = CGAL_wdot(perpend2line, end_min_lp);
    if (sdm_ss2l < R::RT(0)) {
        crossing = (sdm_se2l >= R::RT(0));
    } else {
        if (sdm_se2l <= R::RT(0)) {
            crossing = true;
        } else {
            crossing = (sdm_ss2l == R::RT(0));
        }
    }

    if (crossing) {
        return CGAL_squared_distance_to_plane(normal, start_min_lp);
    } else {
        R::RT dm;
        dm = CGAL__distance_measure_sub(
                sdm_ss2l, sdm_se2l, start_min_lp, end_min_lp);
        if (dm <= R::RT(0)) {
            return CGAL_squared_distance_to_line(linedir, start_min_lp);
        } else {
            return CGAL_squared_distance_to_line(linedir, end_min_lp);
        }
    }
}



template <class R>
R_FT_return(R)
CGAL_ray_ray_squared_distance_parallel(
    const CGAL_Vector_3<R> &ray1dir,
    const CGAL_Vector_3<R> &ray2dir,
    const CGAL_Vector_3<R> &s1_min_s2)
{
    if (!CGAL_is_acute_angle(ray2dir, s1_min_s2)) {
        bool same_direction;
        if (CGAL_abs(ray1dir.hx()) > CGAL_abs(ray1dir.hy())) {
            if (CGAL_abs(ray1dir.hx()) > CGAL_abs(ray1dir.hz()))
                same_direction =
                    (CGAL_sign(ray1dir.hx()) == CGAL_sign(ray2dir.hx()));
            else
                same_direction =
                    (CGAL_sign(ray1dir.hz()) == CGAL_sign(ray2dir.hz()));
        } else {
            if (CGAL_abs(ray1dir.hy()) > CGAL_abs(ray1dir.hz()))
                same_direction =
                    (CGAL_sign(ray1dir.hy()) == CGAL_sign(ray2dir.hy()));
            else
                same_direction =
                    (CGAL_sign(ray1dir.hz()) == CGAL_sign(ray2dir.hz()));
        }
        if (!same_direction)
            return R_FT_return(R)(s1_min_s2*s1_min_s2);
    }
    return CGAL_squared_distance_to_line(ray1dir, s1_min_s2);
}


template <class R>
R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Ray_3<R> &ray1,
    const CGAL_Ray_3<R> &ray2)
{
    const CGAL_Point_3<R> & s1 (ray1.start());
    const CGAL_Point_3<R> & s2 (ray2.start());
    CGAL_Vector_3<R> dir1, dir2, normal;
    dir1 = ray1.direction().vector();
    dir2 = ray2.direction().vector();
    normal = CGAL_wcross(dir1, dir2);
    CGAL_Vector_3<R> s1_min_s2 = s1-s2;
    if (CGAL_is_null(normal))
        return CGAL_ray_ray_squared_distance_parallel(dir1, dir2, s1_min_s2);

    bool crossing1, crossing2;
    R::RT sdm_s1_2, sdm_s2_1;
    CGAL_Vector_3<R> perpend1, perpend2;
    perpend1 = CGAL_wcross(dir1, normal);
    perpend2 = CGAL_wcross(dir2, normal);

    sdm_s1_2 = CGAL_wdot(perpend2, s1_min_s2);
    if (sdm_s1_2 < R::RT(0)) {
        crossing1 = (R::RT(CGAL_wdot(perpend2, dir1)) >= R::RT(0));
    } else {
        if (R::RT(CGAL_wdot(perpend2, dir1)) <= R::RT(0)) {
            crossing1 = true;
        } else {
            crossing1 = (sdm_s1_2 == R::RT(0));
        }
    }
    sdm_s2_1 = -R::RT(CGAL_wdot(perpend1, s1_min_s2));
    if (sdm_s2_1 < R::RT(0)) {
        crossing2 = (R::RT(CGAL_wdot(perpend1, dir2)) >= R::RT(0));
    } else {
        if (R::RT(CGAL_wdot(perpend1, dir2)) <= R::RT(0)) {
            crossing2 = true;
        } else {
            crossing2 = (sdm_s2_1 == R::RT(0));
        }
    }
    if (crossing1) {
        if (crossing2)
            return CGAL_squared_distance_to_plane(normal, s1_min_s2);
        return CGAL_squared_distance(ray2.start(), ray1);
    } else {
        if (crossing2) {
            return CGAL_squared_distance(ray1.start(), ray2);
        } else {
          R::FT min1, min2;
            min1 = CGAL_squared_distance(ray1.start(), ray2);
            min2 = CGAL_squared_distance(ray2.start(), ray1);
            return (min1 < min2) ? R_FT_return(R)(min1) : R_FT_return(R)(min2);
        }
    }
}


template <class R>
extern R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Line_3<R> &line,
    const CGAL_Ray_3<R> &ray)
{
    const CGAL_Point_3<R> & rs (ray.start());
    CGAL_Vector_3<R> raydir, linedir, normal;
    linedir = line.direction().vector();
    raydir = ray.direction().vector();
    normal = CGAL_wcross(raydir, linedir);
    CGAL_Vector_3<R> rs_min_lp = rs-line.point();
    if (CGAL_is_null(normal))
        return CGAL_squared_distance_to_line(linedir, rs_min_lp);

    bool crossing;
    R::RT sdm_sr_l;
    CGAL_Vector_3<R> perpend2l;
    perpend2l = CGAL_wcross(linedir, normal);

    sdm_sr_l = CGAL_wdot(perpend2l, rs_min_lp);
    if (sdm_sr_l < R::RT(0)) {
        crossing = (R::RT(CGAL_wdot(perpend2l, raydir)) >= R::RT(0));
    } else {
        if (R::RT(CGAL_wdot(perpend2l, raydir)) <= R::RT(0)) {
            crossing = true;
        } else {
            crossing = (sdm_sr_l == R::RT(0));
        }
    }

    if (crossing)
        return CGAL_squared_distance_to_plane(normal, rs_min_lp);
    else
        return CGAL_squared_distance_to_line(linedir, rs_min_lp);
}

template <class R>
R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Line_3<R> &line1,
    const CGAL_Line_3<R> &line2)
{
    CGAL_Vector_3<R> dir1, dir2, normal, diff;
    dir1 = line1.direction().vector();
    dir2 = line2.direction().vector();
    normal = CGAL_wcross(dir1, dir2);
    diff = line2.point() - line1.point();
    if (CGAL_is_null(normal))
        return CGAL_squared_distance_to_line(dir2, diff);
    return CGAL_squared_distance_to_plane(normal, diff);
}

