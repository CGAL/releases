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
#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Line_2.h>
#include <CGAL/Ray_2.h>
#include <CGAL/enum.h>
#include <CGAL/wmult.h>
#include <CGAL/squared_distance_utils.h>

template <class R>
R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Point_2<R> &pt,
    const CGAL_Line_2<R> &line)
{
    R::RT x = line.a();
    R::RT y = line.b();
    CGAL_Vector_2<R> normal(x, y);
    CGAL_Vector_2<R> diff = pt - line.point();
    R::FT signdist = diff * normal;
    return R_FT_return(R)((signdist*signdist)/R::FT(x*x+y*y));
}

template <class R>
extern R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Point_2<R> &pt,
    const CGAL_Ray_2<R> &ray)
{
    CGAL_Vector_2<R> diff = pt-ray.start();
    const CGAL_Vector_2<R> &dir = ray.direction().vector();
    if (!CGAL_is_acute_angle(dir,diff) )
        return R_FT_return(R)(diff*diff);
    return CGAL_squared_distance(pt, ray.supporting_line());
}

template <class R>
extern void
CGAL_distance_index(
    int &ind,
    const CGAL_Point_2<R> &pt,
    const CGAL_Ray_2<R> &ray)
{
    if (!CGAL_is_acute_angle(ray.direction().vector(),pt-ray.source())) {
        ind = 0;
        return;
    }
    ind = -1;
}

template <class R>
R_FT_return(R)
CGAL_squared_distance_indexed(const CGAL_Point_2<R> &pt,
    const CGAL_Ray_2<R> &ray, int ind)
{
    if (ind == 0)
        return CGAL_squared_distance(pt, ray.source());
    return CGAL_squared_distance(pt, ray.supporting_line());
}

template <class R>
R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Point_2<R> &pt,
    const CGAL_Segment_2<R> &seg)
{
    // assert that the segment is valid (non zero length).
    CGAL_Vector_2<R> diff = pt-seg.start();
    CGAL_Vector_2<R> segvec = seg.end()-seg.start();
    R::RT d = CGAL_wdot(diff,segvec);
    if (d <= (R::RT)0)
        return R_FT_return(R)(diff*diff);
    R::RT e = CGAL_wdot(segvec,segvec);
    if (CGAL_wmult((R*)0 ,d, segvec.hw()) > CGAL_wmult((R*)0, e, diff.hw()))
        return CGAL_squared_distance(pt, seg.end());
    return CGAL_squared_distance(pt, seg.supporting_line());
}

template <class R>
extern void
CGAL_distance_index(
    int &ind,
    const CGAL_Point_2<R> &pt,
    const CGAL_Segment_2<R> &seg)
{
    if (!CGAL_is_acute_angle(seg.target(),seg.source(),pt)) {
        ind = 0;
        return;
    }
    if (!CGAL_is_acute_angle(seg.source(),seg.target(),pt)) {
        ind = 1;
        return;
    }
    ind = -1;
}

template <class R>
R_FT_return(R)
CGAL_squared_distance_indexed(const CGAL_Point_2<R> &pt,
    const CGAL_Segment_2<R> &seg, int ind)
{
    if (ind == 0)
        return CGAL_squared_distance(pt, seg.source());
    if (ind == 1)
        return CGAL_squared_distance(pt, seg.target());
    return CGAL_squared_distance(pt, seg.supporting_line());
}



template <class R>
R_FT_return(R)
CGAL_squared_distance_parallel(
    const CGAL_Segment_2<R> &seg1,
    const CGAL_Segment_2<R> &seg2)
{
    bool same_direction;
    const CGAL_Vector_2<R> &dir1 = seg1.direction().vector();
    const CGAL_Vector_2<R> &dir2 = seg2.direction().vector();
    if (CGAL_abs(dir1.hx()) > CGAL_abs(dir1.hy())) {
        same_direction = (CGAL_sign(dir1.hx()) == CGAL_sign(dir2.hx()));
    } else {
        same_direction = (CGAL_sign(dir1.hy()) == CGAL_sign(dir2.hy()));
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
RT CGAL__distance_measure_sub(RT startwcross, RT endwcross,
const CGAL_Point_2<R> &start, const CGAL_Point_2<R> &end
)
{
    return  CGAL_abs(CGAL_wmult((R*)0, startwcross, end.hw())) -
            CGAL_abs(CGAL_wmult((R*)0, endwcross, start.hw()));
}


template <class R>
R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Segment_2<R> &seg1,
    const CGAL_Segment_2<R> &seg2)
{
    bool crossing1, crossing2;
    R::RT c1s, c1e, c2s, c2e;
    if (seg1.start() == seg1.end())
        return CGAL_squared_distance(seg1.start(), seg2);
    if (seg2.start() == seg2.end())
        return CGAL_squared_distance(seg2.start(), seg1);
    c1s = CGAL_wcross(seg2.start(), seg2.end(), seg1.start());
    c1e = CGAL_wcross(seg2.start(), seg2.end(), seg1.end());
    c2s = CGAL_wcross(seg1.start(), seg1.end(), seg2.start());
    c2e = CGAL_wcross(seg1.start(), seg1.end(), seg2.end());
    if (c1s < R::RT(0)) {
        crossing1 = (c1e >= R::RT(0));
    } else {
        if (c1e <= R::RT(0)) {
            crossing1 = true;
        } else {
            crossing1 = (c1s == R::RT(0));
        }
    }
    if (c2s < R::RT(0)) {
        crossing2 = (c2e >= R::RT(0));
    } else {
        if (c2e <= R::RT(0)) {
            crossing2 = true;
        } else {
            crossing2 = (c2s == R::RT(0));
        }
    }

    if (crossing1) {
        if (crossing2)
            return R_FT_return(R)((R::FT)0);
        R::RT dm;
        dm = CGAL__distance_measure_sub(c2s, c2e, seg2.start(), seg2.end());
        if (dm < R::RT(0)) {
            return CGAL_squared_distance(seg2.start(), seg1);
        } else {
            if (dm > R::RT(0)) {
                return CGAL_squared_distance(seg2.end(), seg1);
            } else {
                // parallel, should not happen (no crossing)
                return CGAL_squared_distance_parallel(seg1, seg2);
            }
        }
    } else {
        if (crossing2) {
            R::RT dm;
            dm = CGAL__distance_measure_sub(c1s, c1e,seg1.start(),seg1.end());
            if (dm < R::RT(0)) {
                return CGAL_squared_distance(seg1.start(), seg2);
            } else {
                if (dm > R::RT(0)) {
                    return CGAL_squared_distance(seg1.end(), seg2);
                } else {
                    // parallel, should not happen (no crossing)
                    return CGAL_squared_distance_parallel(seg1, seg2);
                }
            }
        } else {

            R::FT min1, min2;
            R::RT dm;
            dm = CGAL__distance_measure_sub(c1s, c1e, seg1.start(), seg1.end());
            if (dm == R::RT(0))
                return CGAL_squared_distance_parallel(seg1, seg2);
            min1 = (dm < R::RT(0)) ?
                CGAL_squared_distance(seg1.start(), seg2):
                CGAL_squared_distance(seg1.end(), seg2);
            dm = CGAL__distance_measure_sub(c2s, c2e, seg2.start(), seg2.end());
            if (dm == R::RT(0))  // should not happen.
                return CGAL_squared_distance_parallel(seg1, seg2);
            min2 = (dm < R::RT(0)) ?
                CGAL_squared_distance(seg2.start(), seg1):
                CGAL_squared_distance(seg2.end(), seg1);
            return (min1 < min2) ? R_FT_return(R)(min1) : R_FT_return(R)(min2);
        }
    }
}




template <class RT, class R>
RT CGAL__distance_measure_sub(RT startwcross, RT endwcross,
const CGAL_Vector_2<R> &start, const CGAL_Vector_2<R> &end
)
{
    return  CGAL_abs(CGAL_wmult((R*)0, startwcross, end.hw())) -
            CGAL_abs(CGAL_wmult((R*)0, endwcross, start.hw()));
}


template <class R>
R_FT_return(R)
CGAL_squared_distance_parallel(
    const CGAL_Segment_2<R> &seg,
    const CGAL_Ray_2<R> &ray)
{
    bool same_direction;
    const CGAL_Vector_2<R> &dir1 = seg.direction().vector();
    const CGAL_Vector_2<R> &dir2 = ray.direction().vector();
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
    const CGAL_Segment_2<R> &seg,
    const CGAL_Ray_2<R> &ray)
{
    const CGAL_Vector_2<R> &raydir = ray.direction().vector();
    CGAL_Vector_2<R> startvec(seg.start()-ray.start());
    CGAL_Vector_2<R> endvec(seg.end()-ray.start());


    bool crossing1, crossing2;
    R::RT c1s, c1e;
    CGAL_Orientation ray_s_side;
    if (seg.start() == seg.end())
        return CGAL_squared_distance(seg.start(), ray);
    c1s = CGAL_wcross(raydir, startvec);
    c1e = CGAL_wcross(raydir, endvec);
    if (c1s < R::RT(0)) {
        crossing1 = (c1e >= R::RT(0));
    } else {
        if (c1e <= R::RT(0)) {
            crossing1 = true;
        } else {
            crossing1 = (c1s == R::RT(0));
        }
    }
    ray_s_side = CGAL_orientation(seg.start(), seg.end(), ray.start());
    switch (ray_s_side) {
    case CGAL_LEFTTURN:
        crossing2 = CGAL_rightturn(seg.end()-seg.start(), raydir);
        break;
    case CGAL_RIGHTTURN:
        crossing2 = CGAL_leftturn(seg.end()-seg.start(), raydir);
        break;
    case CGAL_COLLINEAR:
        crossing2 = true;
        break;
    }

    if (crossing1) {
        if (crossing2)
            return R_FT_return(R)(R::FT(0));
        return CGAL_squared_distance(ray.start(), seg);
    } else {
        if (crossing2) {
            R::RT dm;
            dm = CGAL__distance_measure_sub(c1s, c1e, startvec, endvec);
            if (dm < R::RT(0)) {
                return CGAL_squared_distance(seg.start(), ray);
            } else {
                if (dm > R::RT(0)) {
                    return CGAL_squared_distance(seg.end(), ray);
                } else {
                    // parallel, should not happen (no crossing)
                    return CGAL_squared_distance_parallel(seg, ray);
                }
            }
        } else {

            R::FT min1, min2;
            R::RT dm;
            dm = CGAL__distance_measure_sub(c1s, c1e, startvec, endvec);
            if (dm == R::RT(0))
                return CGAL_squared_distance_parallel(seg, ray);
            min1 = (dm < R::RT(0))
                 ? CGAL_squared_distance(seg.start(), ray)
                 : CGAL_squared_distance(seg.end(), ray);
            min2 = CGAL_squared_distance(ray.start(), seg);
            return (min1 < min2) ? R_FT_return(R)(min1) : R_FT_return(R)(min2);
        }
    }
}



template <class RT, class R>
R_FT_return(R) CGAL__sqd_to_line(const CGAL_Vector_2<R> &diff,
                   const RT & wcross, const CGAL_Vector_2<R> &dir )
{
    RT numerator = CGAL_wmult((R*)0, wcross*wcross, dir.hw());
    RT denominator = CGAL_wmult((R*)0, R::RT(CGAL_wdot(dir,dir)), diff.hw());
    return R_FT_return(R)(R::FT(numerator)/R::FT(denominator));
}


template <class R>
R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Segment_2<R> &seg,
    const CGAL_Line_2<R> &line)
{
    const CGAL_Vector_2<R> &linedir = line.direction().vector();
    const CGAL_Point_2<R> &linepoint = line.point();
    CGAL_Vector_2<R> startvec(seg.start()-linepoint);
    CGAL_Vector_2<R> endvec(seg.end()-linepoint);

    bool crossing1;
    R::RT c1s, c1e;
    if (seg.start() == seg.end())
        return CGAL_squared_distance(seg.start(), line);
    c1s = CGAL_wcross(linedir, startvec);
    c1e = CGAL_wcross(linedir, endvec);
    if (c1s < R::RT(0)) {
        crossing1 = (c1e >= R::RT(0));
    } else {
        if (c1e <= R::RT(0)) {
            crossing1 = true;
        } else {
            crossing1 = (c1s == R::RT(0));
        }
    }

    if (crossing1) {
        return R_FT_return(R)((R::FT)0);
    } else {
        R::RT dm;
        dm = CGAL__distance_measure_sub(c1s, c1e, startvec, endvec);
        if (dm <= R::RT(0)) {
            return CGAL__sqd_to_line(startvec, c1s, linedir);
        } else {
            return CGAL__sqd_to_line(endvec, c1e, linedir);
        }
    }
}



template <class R>
R_FT_return(R)
CGAL_ray_ray_squared_distance_parallel(
    const CGAL_Vector_2<R> &ray1dir,
    const CGAL_Vector_2<R> &ray2dir,
    const CGAL_Vector_2<R> &from1to2)
{
    if (!CGAL_is_acute_angle(ray1dir, from1to2)) {
        bool same_direction;
        if (CGAL_abs(ray1dir.hx()) > CGAL_abs(ray1dir.hy())) {
            same_direction =
                (CGAL_sign(ray1dir.hx()) == CGAL_sign(ray2dir.hx()));
        } else {
            same_direction =
                (CGAL_sign(ray1dir.hy()) == CGAL_sign(ray2dir.hy()));
        }
        if (!same_direction)
            return R_FT_return(R)(from1to2*from1to2);
    }
    R::RT wcr, w;
    wcr = CGAL_wcross(ray1dir, from1to2);
    w = from1to2.hw();
    return R_FT_return(R)(R::FT(wcr*wcr)
         / R::FT(CGAL_wmult((R*)0, R::RT(CGAL_wdot(ray1dir, ray1dir)), w, w)));
}


template <class R>
R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Ray_2<R> &ray1,
    const CGAL_Ray_2<R> &ray2)
{
    const CGAL_Vector_2<R> &ray1dir = ray1.direction().vector();
    const CGAL_Vector_2<R> &ray2dir = ray2.direction().vector();
    CGAL_Vector_2<R> diffvec(ray2.start()-ray1.start());

    bool crossing1, crossing2;
    CGAL_Orientation dirorder;
    dirorder = CGAL_orientation(ray1dir, ray2dir);
    switch (dirorder) {
    case CGAL_COUNTERCLOCKWISE:
        crossing1 = !CGAL_clockwise(diffvec, ray2dir);
        crossing2 = !CGAL_counterclockwise(ray1dir, diffvec);
        break;
    case CGAL_CLOCKWISE:
        crossing1 = !CGAL_counterclockwise(diffvec, ray2dir);
        crossing2 = !CGAL_clockwise(ray1dir, diffvec);
        break;
    case CGAL_COLLINEAR:
        return CGAL_ray_ray_squared_distance_parallel(ray1dir,ray2dir,diffvec);
    }

    if (crossing1) {
        if (crossing2)
            return R_FT_return(R)((R::FT)0);
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
    const CGAL_Line_2<R> &line,
    const CGAL_Ray_2<R> &ray)
{
    CGAL_Vector_2<R> normalvec(line.a(), line.b());
    CGAL_Vector_2<R> diff = ray.start()-line.point();
    R::FT sign_dist = diff*normalvec;
    if (sign_dist < R::FT(0)) {
        if (CGAL_is_acute_angle(normalvec, ray.direction().vector()) )
            return R_FT_return(R)((R::FT)0);
    } else {
        if (CGAL_is_obtuse_angle(normalvec, ray.direction().vector()) )
            return R_FT_return(R)((R::FT)0);
    }
    return R_FT_return(R)((sign_dist*sign_dist)/(normalvec*normalvec));
}

template <class R>
bool
CGAL__are_parallel(
    const CGAL_Line_2<R> &line1,
    const CGAL_Line_2<R> &line2)
{
    return line1.a()*line2.b() == line2.a()*line1.b();
}

template <class R>
R_FT_return(R) CGAL_squared_distance(
    const CGAL_Line_2<R> &line1,
    const CGAL_Line_2<R> &line2)
{
    if (CGAL__are_parallel(line1,line2))
        return CGAL_squared_distance(line1.point(), line2);
    else
        return R_FT_return(R)((R::FT)0);
}

