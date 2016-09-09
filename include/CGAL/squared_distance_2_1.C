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
#include <CGAL/squared_distance_2_1.h>
#endif
#include <CGAL/utils.h>
#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Line_2.h>
#include <CGAL/Ray_2.h>
#include <CGAL/enum.h>
#include <CGAL/wmult.h>

template <class R>
bool CGAL_is_null(const CGAL_Vector_2<R> &v)
{
    return v.hx()==R::RT(0) && v.hy()==R::RT(0);
}


template <class R>
R_RT_return(R) CGAL_wdot(const CGAL_Vector_2<R> &u,
    const CGAL_Vector_2<R> &v)
{
    return  R_RT_return(R)(u.hx()*v.hx() + u.hy()*v.hy());
}

#ifdef CGAL_HOMOGENEOUS_H
template <class RT>
RT CGAL_wdot(const CGAL_Point_2< CGAL_Homogeneous<RT> > &p,
    const CGAL_Point_2<CGAL_Homogeneous<RT> > &q,
    const CGAL_Point_2<CGAL_Homogeneous<RT> > &r)
{
    return  (q.hw()*p.hx() - p.hw()*q.hx())*(q.hw()*r.hx() - r.hw()*q.hx()) +
            (q.hw()*p.hy() - p.hw()*q.hy())*(q.hw()*r.hy() - r.hw()*q.hy());
}
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
template <class FT>
FT CGAL_wdot(const CGAL_Point_2< CGAL_Cartesian<FT> > &p,
    const CGAL_Point_2< CGAL_Cartesian<FT> > &q,
    const CGAL_Point_2< CGAL_Cartesian<FT> > &r)
{
    return  (p.hx() - q.hx())*(r.hx() - q.hx()) +
            (p.hy() - q.hy())*(r.hy() - q.hy());
}
#endif // CGAL_CARTESIAN_H



template <class R>
R_RT_return(R) CGAL_wcross(const CGAL_Vector_2<R> &u,
    const CGAL_Vector_2<R> &v)
{
    return R_RT_return(R)(u.hx()*v.hy() - u.hy()*v.hx());
}

#ifdef CGAL_HOMOGENEOUS_H
template <class RT>
RT CGAL_wcross(const CGAL_Point_2< CGAL_Homogeneous<RT> > &p,
    const CGAL_Point_2< CGAL_Homogeneous<RT> > &q,
    const CGAL_Point_2< CGAL_Homogeneous<RT> > &r)
{
    return   p.hx() * (q.hy()*r.hw() - q.hw()*r.hy() )
           + p.hy() * (q.hw()*r.hx() - q.hx()*r.hw() )
           + p.hw() * (q.hx()*r.hy() - q.hy()*r.hx() );
}
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
template <class FT>
FT CGAL_wcross(const CGAL_Point_2< CGAL_Cartesian<FT> > &p,
    const CGAL_Point_2< CGAL_Cartesian<FT> > &q,
    const CGAL_Point_2< CGAL_Cartesian<FT> > &r)
{
    return (q.x()-p.x())*(r.y()-q.y()) - (q.y()-p.y())*(r.x()-q.x());
}
#endif // CGAL_CARTESIAN_H

template <class R>
inline bool CGAL_is_acute_angle(const CGAL_Vector_2<R> &u,
    const CGAL_Vector_2<R> &v)
{
    return R::RT(CGAL_wdot(u, v)) > R::RT(0) ;
}

template <class R>
inline bool CGAL_is_straight_angle(const CGAL_Vector_2<R> &u,
    const CGAL_Vector_2<R> &v)
{
    return R::RT(CGAL_wdot(u, v)) == R::RT(0) ;
}

template <class R>
inline bool CGAL_is_obtuse_angle(const CGAL_Vector_2<R> &u,
    const CGAL_Vector_2<R> &v)
{
    return R::RT(CGAL_wdot(u, v)) < R::RT(0) ;
}

template <class R>
inline bool CGAL_is_acute_angle(const CGAL_Point_2<R> &p,
    const CGAL_Point_2<R> &q, const CGAL_Point_2<R> &r)
{
    return R::RT(CGAL_wdot(p, q, r)) > R::RT(0) ;
}

template <class R>
inline bool CGAL_is_straight_angle(const CGAL_Point_2<R> &p,
    const CGAL_Point_2<R> &q, const CGAL_Point_2<R> &r)
{
    return R::RT(CGAL_wdot(p, q, r)) == R::RT(0) ;
}

template <class R>
inline bool CGAL_is_obtuse_angle(const CGAL_Point_2<R> &p,
    const CGAL_Point_2<R> &q, const CGAL_Point_2<R> &r)
{
    return R::RT(CGAL_wdot(p, q, r)) < R::RT(0) ;
}

template <class R>
CGAL_Orientation CGAL_orientation(const CGAL_Vector_2<R> &u,
    const CGAL_Vector_2<R> &v)
{
    R::RT wcr = CGAL_wcross(u,v);
    return (wcr > R::RT(0)) ? CGAL_COUNTERCLOCKWISE :
           (wcr < R::RT(0)) ? CGAL_CLOCKWISE
                            : CGAL_COLLINEAR;
}

template <class R>
inline bool CGAL_counterclockwise(const CGAL_Vector_2<R> &u,
    const CGAL_Vector_2<R> &v)
{
    return R::RT(CGAL_wcross(u,v)) > R::RT(0);
}

template <class R>
inline bool CGAL_leftturn(const CGAL_Vector_2<R> &u,
    const CGAL_Vector_2<R> &v)
{
    return R::RT(CGAL_wcross(u,v)) > R::RT(0);
}

template <class R>
inline bool CGAL_clockwise(const CGAL_Vector_2<R> &u,
    const CGAL_Vector_2<R> &v)
{
    return R::RT(CGAL_wcross(u,v)) < R::RT(0);
}

template <class R>
inline bool CGAL_rightturn(const CGAL_Vector_2<R> &u,
    const CGAL_Vector_2<R> &v)
{
    return R::RT(CGAL_wcross(u,v)) < R::RT(0);
}

template <class R>
inline bool CGAL_collinear(const CGAL_Vector_2<R> &u,
    const CGAL_Vector_2<R> &v)
{
    return R::RT(CGAL_wcross(u,v)) == R::RT(0);
}

/*
the ordertype, rightturn, leftturn and collinear routines for points are
defined elsewhere.
*/



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
    CGAL_Vector_2<R> diff = pt-ray.source();
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
    CGAL_Vector_2<R> diff = pt-seg.source();
    CGAL_Vector_2<R> segvec = seg.target()-seg.source();
    R::RT d = CGAL_wdot(diff,segvec);
    if (d <= (R::RT)0)
        return R_FT_return(R)(diff*diff);
    R::RT e = CGAL_wdot(segvec,segvec);
    if (CGAL_wmult((R*)0 ,d, segvec.hw()) > CGAL_wmult((R*)0, e, diff.hw()))
        return CGAL_squared_distance(pt, seg.target());
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
        if (!CGAL_is_acute_angle(seg1.source(), seg1.target(), seg2.source()))
            return CGAL_squared_distance(seg1.target(), seg2.source());
        if (!CGAL_is_acute_angle(seg1.target(), seg1.source(), seg2.target()))
            return CGAL_squared_distance(seg1.source(), seg2.target());
    } else {
        if (!CGAL_is_acute_angle(seg1.source(), seg1.target(), seg2.target()))
            return CGAL_squared_distance(seg1.target(), seg2.target());
        if (!CGAL_is_acute_angle(seg1.target(), seg1.source(), seg2.source()))
            return CGAL_squared_distance(seg1.source(), seg2.source());
    }
    return CGAL_squared_distance(seg2.source(), seg1.supporting_line());
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
    if (seg1.source() == seg1.target())
        return CGAL_squared_distance(seg1.source(), seg2);
    if (seg2.source() == seg2.target())
        return CGAL_squared_distance(seg2.source(), seg1);
    c1s = CGAL_wcross(seg2.source(), seg2.target(), seg1.source());
    c1e = CGAL_wcross(seg2.source(), seg2.target(), seg1.target());
    c2s = CGAL_wcross(seg1.source(), seg1.target(), seg2.source());
    c2e = CGAL_wcross(seg1.source(), seg1.target(), seg2.target());
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
            return R_FT_return(R)(0);
        R::RT dm;
        dm = CGAL__distance_measure_sub(c2s, c2e, seg2.source(), seg2.target());
        if (dm < R::RT(0)) {
            return CGAL_squared_distance(seg2.source(), seg1);
        } else {
            if (dm > R::RT(0)) {
                return CGAL_squared_distance(seg2.target(), seg1);
            } else {
                // parallel, should not happen (no crossing)
                return CGAL_squared_distance_parallel(seg1, seg2);
            }
        }
    } else {
        if (crossing2) {
            R::RT dm;
            dm = CGAL__distance_measure_sub(c1s, c1e,
                                            seg1.source(),seg1.target());
            if (dm < R::RT(0)) {
                return CGAL_squared_distance(seg1.source(), seg2);
            } else {
                if (dm > R::RT(0)) {
                    return CGAL_squared_distance(seg1.target(), seg2);
                } else {
                    // parallel, should not happen (no crossing)
                    return CGAL_squared_distance_parallel(seg1, seg2);
                }
            }
        } else {

            R::FT min1, min2;
            R::RT dm;
            dm = CGAL__distance_measure_sub(c1s, c1e,
                                            seg1.source(), seg1.target());
            if (dm == R::RT(0))
                return CGAL_squared_distance_parallel(seg1, seg2);
            min1 = (dm < R::RT(0)) ?
                CGAL_squared_distance(seg1.source(), seg2):
                CGAL_squared_distance(seg1.target(), seg2);
            dm = CGAL__distance_measure_sub(c2s, c2e,
                                            seg2.source(), seg2.target());
            if (dm == R::RT(0))  // should not happen.
                return CGAL_squared_distance_parallel(seg1, seg2);
            min2 = (dm < R::RT(0)) ?
                CGAL_squared_distance(seg2.source(), seg1):
                CGAL_squared_distance(seg2.target(), seg1);
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
        if (!CGAL_is_acute_angle(seg.source(), seg.target(), ray.source()))
            return CGAL_squared_distance(seg.target(), ray.source());
    } else {
        if (!CGAL_is_acute_angle(seg.target(), seg.source(), ray.source()))
            return CGAL_squared_distance(seg.source(), ray.source());
    }
    return CGAL_squared_distance(ray.source(), seg.supporting_line());
}


template <class R>
R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Segment_2<R> &seg,
    const CGAL_Ray_2<R> &ray)
{
    const CGAL_Vector_2<R> &raydir = ray.direction().vector();
    CGAL_Vector_2<R> startvec(seg.source()-ray.source());
    CGAL_Vector_2<R> endvec(seg.target()-ray.source());


    bool crossing1, crossing2;
    R::RT c1s, c1e;
    CGAL_Orientation ray_s_side;
    if (seg.source() == seg.target())
        return CGAL_squared_distance(seg.source(), ray);
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
    ray_s_side = CGAL_orientation(seg.source(), seg.target(), ray.source());
    switch (ray_s_side) {
    case CGAL_LEFTTURN:
        crossing2 = CGAL_rightturn(seg.target()-seg.source(), raydir);
        break;
    case CGAL_RIGHTTURN:
        crossing2 = CGAL_leftturn(seg.target()-seg.source(), raydir);
        break;
    case CGAL_COLLINEAR:
        crossing2 = true;
        break;
    }

    if (crossing1) {
        if (crossing2)
            return R_FT_return(R)(R::FT(0));
        return CGAL_squared_distance(ray.source(), seg);
    } else {
        if (crossing2) {
            R::RT dm;
            dm = CGAL__distance_measure_sub(c1s, c1e, startvec, endvec);
            if (dm < R::RT(0)) {
                return CGAL_squared_distance(seg.source(), ray);
            } else {
                if (dm > R::RT(0)) {
                    return CGAL_squared_distance(seg.target(), ray);
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
                 ? CGAL_squared_distance(seg.source(), ray)
                 : CGAL_squared_distance(seg.target(), ray);
            min2 = CGAL_squared_distance(ray.source(), seg);
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
    CGAL_Vector_2<R> startvec(seg.source()-linepoint);
    CGAL_Vector_2<R> endvec(seg.target()-linepoint);

    bool crossing1;
    R::RT c1s, c1e;
    if (seg.source() == seg.target())
        return CGAL_squared_distance(seg.source(), line);
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
        return R_FT_return(R)(0);
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
    CGAL_Vector_2<R> diffvec(ray2.source()-ray1.source());

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
            return R_FT_return(R)(0);
        return CGAL_squared_distance(ray2.source(), ray1);
    } else {
        if (crossing2) {
            return CGAL_squared_distance(ray1.source(), ray2);
        } else {

            R::FT min1, min2;
            min1 = CGAL_squared_distance(ray1.source(), ray2);
            min2 = CGAL_squared_distance(ray2.source(), ray1);
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
    CGAL_Vector_2<R> diff = ray.source()-line.point();
    R::FT sign_dist = diff*normalvec;
    if (sign_dist < R::FT(0)) {
        if (CGAL_is_acute_angle(normalvec, ray.direction().vector()) )
            return R_FT_return(R)(0);
    } else {
        if (CGAL_is_obtuse_angle(normalvec, ray.direction().vector()) )
            return R_FT_return(R)(0);
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
        return R_FT_return(R)(0);
}

