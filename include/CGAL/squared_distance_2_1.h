// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : include/CGAL/squared_distance_2_1.h
// package       : Distance_2 (2.3.3)
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
#ifndef CGAL_ENUM_H
#include <CGAL/enum.h>
#endif // CGAL_ENUM_H
#ifndef CGAL_WMULT_H
#include <CGAL/wmult.h>
#endif // CGAL_WMULT_H
#ifndef CGAL_SQUARED_DISTANCE_UTILS_H
#include <CGAL/squared_distance_utils.h>
#endif // CGAL_SQUARED_DISTANCE_UTILS_H

CGAL_BEGIN_NAMESPACE

template <class R>
inline typename R::FT
squared_distance(
    const Point_2<R> & pt1,
    const Point_2<R> & pt2)
{
    Vector_2<R> vec(pt1-pt2);
    return (typename R::FT)(vec*vec);
}


template <class R>
typename R::FT
squared_distance(
    const Point_2<R> &pt,
    const Line_2<R> &line)
{
    typedef typename R::RT RT;
    typedef typename R::FT FT;
    RT x = line.a();
    RT y = line.b();
    Vector_2<R> normal(x, y);
    Vector_2<R> diff = pt - line.point();
    FT signdist = diff * normal;
    return (typename R::FT)((signdist*signdist)/FT(x*x+y*y));
}


template <class R>
inline typename R::FT
squared_distance(
    const Line_2<R> & line,
    const Point_2<R> & pt)
{
    return squared_distance(pt, line);
}



template <class R>
extern typename R::FT
squared_distance(
    const Point_2<R> &pt,
    const Ray_2<R> &ray)
{
    Vector_2<R> diff = pt-ray.source();
    const Vector_2<R> &dir = ray.direction().vector();
    if (!is_acute_angle(dir,diff) )
        return (typename R::FT)(diff*diff);
    return squared_distance(pt, ray.supporting_line());
}


template <class R>
inline typename R::FT
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
    const Ray_2<R> &ray)
{
    if (!is_acute_angle(ray.direction().vector(),pt-ray.source())) {
        ind = 0;
        return;
    }
    ind = -1;
}

template <class R>
typename R::FT
squared_distance_indexed(const Point_2<R> &pt,
    const Ray_2<R> &ray, int ind)
{
    if (ind == 0)
        return squared_distance(pt, ray.source());
    return squared_distance(pt, ray.supporting_line());
}




template <class R>
typename R::FT
squared_distance(
    const Point_2<R> &pt,
    const Segment_2<R> &seg)
{
    typedef typename R::RT RT;
    // assert that the segment is valid (non zero length).
    Vector_2<R> diff = pt-seg.source();
    Vector_2<R> segvec = seg.target()-seg.source();
    RT d = wdot(diff,segvec);
    if (d <= (RT)0)
        return (typename R::FT)(diff*diff);
    RT e = wdot(segvec,segvec);
    if (wmult((R*)0 ,d, segvec.hw()) > wmult((R*)0, e, diff.hw()))
        return squared_distance(pt, seg.target());
    return squared_distance(pt, seg.supporting_line());
}


template <class R>
inline typename R::FT
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
    const Segment_2<R> &seg)
{
    if (!is_acute_angle(seg.target(),seg.source(),pt)) {
        ind = 0;
        return;
    }
    if (!is_acute_angle(seg.source(),seg.target(),pt)) {
        ind = 1;
        return;
    }
    ind = -1;
}

template <class R>
typename R::FT
squared_distance_indexed(const Point_2<R> &pt,
    const Segment_2<R> &seg, int ind)
{
    if (ind == 0)
        return squared_distance(pt, seg.source());
    if (ind == 1)
        return squared_distance(pt, seg.target());
    return squared_distance(pt, seg.supporting_line());
}





template <class R>
typename R::FT
squared_distance_parallel(
    const Segment_2<R> &seg1,
    const Segment_2<R> &seg2)
{
    bool same_direction;
    const Vector_2<R> &dir1 = seg1.direction().vector();
    const Vector_2<R> &dir2 = seg2.direction().vector();
    if (abs(dir1.hx()) > abs(dir1.hy())) {
        same_direction = (sign(dir1.hx()) == sign(dir2.hx()));
    } else {
        same_direction = (sign(dir1.hy()) == sign(dir2.hy()));
    }
    if (same_direction) {
        if (!is_acute_angle(seg1.source(), seg1.target(), seg2.source()))
            return squared_distance(seg1.target(), seg2.source());
        if (!is_acute_angle(seg1.target(), seg1.source(), seg2.target()))
            return squared_distance(seg1.source(), seg2.target());
    } else {
        if (!is_acute_angle(seg1.source(), seg1.target(), seg2.target()))
            return squared_distance(seg1.target(), seg2.target());
        if (!is_acute_angle(seg1.target(), seg1.source(), seg2.source()))
            return squared_distance(seg1.source(), seg2.source());
    }
    return squared_distance(seg2.source(), seg1.supporting_line());
}



template <class RT, class R>
RT _distance_measure_sub(RT startwcross, RT endwcross,
const Point_2<R> &start, const Point_2<R> &end
)
{
    return  abs(wmult((R*)0, startwcross, end.hw())) -
            abs(wmult((R*)0, endwcross, start.hw()));
}



template <class R>
typename R::FT
squared_distance(
    const Segment_2<R> &seg1,
    const Segment_2<R> &seg2)
{
    typedef typename R::RT RT;
    typedef typename R::FT FT;
    bool crossing1, crossing2;
    RT c1s, c1e, c2s, c2e;
    if (seg1.source() == seg1.target())
        return squared_distance(seg1.source(), seg2);
    if (seg2.source() == seg2.target())
        return squared_distance(seg2.source(), seg1);
    c1s = wcross(seg2.source(), seg2.target(), seg1.source());
    c1e = wcross(seg2.source(), seg2.target(), seg1.target());
    c2s = wcross(seg1.source(), seg1.target(), seg2.source());
    c2e = wcross(seg1.source(), seg1.target(), seg2.target());
    if (c1s < RT(0)) {
        crossing1 = (c1e >= RT(0));
    } else {
        if (c1e <= RT(0)) {
            if (c1s == RT(0) && c1e == RT(0))
                return squared_distance_parallel(seg1, seg2);
            crossing1 = true;
        } else {
            crossing1 = (c1s == RT(0));
        }
    }
    if (c2s < RT(0)) {
        crossing2 = (c2e >= RT(0));
    } else {
        if (c2e <= RT(0)) {
            if (c2s == RT(0) && c2e == RT(0))
                return squared_distance_parallel(seg1, seg2);
            crossing2 = true;
        } else {
            crossing2 = (c2s == RT(0));
        }
    }

    if (crossing1) {
        if (crossing2)
            return (FT)0;
        RT dm;
        dm = _distance_measure_sub(c2s,c2e, seg2.source(), seg2.target());
        if (dm < RT(0)) {
            return squared_distance(seg2.source(), seg1);
        } else {
            if (dm > RT(0)) {
                return squared_distance(seg2.target(), seg1);
            } else {
                // parallel, should not happen (no crossing)
                return squared_distance_parallel(seg1, seg2);
            }
        }
    } else {
        if (crossing2) {
            RT dm;
            dm =
              _distance_measure_sub(c1s, c1e,seg1.source(),seg1.target());
            if (dm < RT(0)) {
                return squared_distance(seg1.source(), seg2);
            } else {
                if (dm > RT(0)) {
                    return squared_distance(seg1.target(), seg2);
                } else {
                    // parallel, should not happen (no crossing)
                    return squared_distance_parallel(seg1, seg2);
                }
            }
        } else {

            FT min1, min2;
            RT dm = _distance_measure_sub(
                           c1s, c1e, seg1.source(), seg1.target());
            if (dm == RT(0))
                return squared_distance_parallel(seg1, seg2);
            min1 = (dm < RT(0)) ?
                squared_distance(seg1.source(), seg2):
                squared_distance(seg1.target(), seg2);
            dm = _distance_measure_sub(
                           c2s, c2e, seg2.source(), seg2.target());
            if (dm == RT(0))  // should not happen.
                return squared_distance_parallel(seg1, seg2);
            min2 = (dm < RT(0)) ?
                squared_distance(seg2.source(), seg1):
                squared_distance(seg2.target(), seg1);
            return (min1 < min2) ? min1 : min2;
        }
    }
}






template <class RT, class R>
RT _distance_measure_sub(RT startwcross, RT endwcross,
const Vector_2<R> &start, const Vector_2<R> &end
)
{
    return  abs(wmult((R*)0, startwcross, end.hw())) -
            abs(wmult((R*)0, endwcross, start.hw()));
}


template <class R>
typename R::FT
squared_distance_parallel(
    const Segment_2<R> &seg,
    const Ray_2<R> &ray)
{
    bool same_direction;
    const Vector_2<R> &dir1 = seg.direction().vector();
    const Vector_2<R> &dir2 = ray.direction().vector();
    if (abs(dir1.hx()) > abs(dir1.hy())) {
        same_direction = (sign(dir1.hx()) == sign(dir2.hx()));
    } else {
        same_direction = (sign(dir1.hy()) == sign(dir2.hy()));
    }
    if (same_direction) {
        if (!is_acute_angle(seg.source(), seg.target(), ray.source()))
            return squared_distance(seg.target(), ray.source());
    } else {
        if (!is_acute_angle(seg.target(), seg.source(), ray.source()))
            return squared_distance(seg.source(), ray.source());
    }
    return squared_distance(ray.source(), seg.supporting_line());
}



template <class R>
typename R::FT
squared_distance(
    const Segment_2<R> &seg,
    const Ray_2<R> &ray)
{
    typedef typename R::RT RT;
    typedef typename R::FT FT;
    const Vector_2<R> &raydir = ray.direction().vector();
    Vector_2<R> startvec(seg.source()-ray.source());
    Vector_2<R> endvec(seg.target()-ray.source());


    bool crossing1, crossing2;
    RT c1s, c1e;
    Orientation ray_s_side;
    if (seg.source() == seg.target())
        return squared_distance(seg.source(), ray);
    c1s = wcross(raydir, startvec);
    c1e = wcross(raydir, endvec);
    if (c1s < RT(0)) {
        crossing1 = (c1e >= RT(0));
    } else {
        if (c1e <= RT(0)) {
            if (c1s == RT(0) && c1e == RT(0))
                return squared_distance_parallel(seg, ray);
            crossing1 = true;
        } else {
            crossing1 = (c1s == RT(0));
        }
    }
    ray_s_side = orientation(seg.source(), seg.target(), ray.source());
    switch (ray_s_side) {
    case LEFTTURN:
        crossing2 = rightturn(seg.target()-seg.source(), raydir);
        break;
    case RIGHTTURN:
        crossing2 = leftturn(seg.target()-seg.source(), raydir);
        break;
    case COLLINEAR:
        crossing2 = true;
        break;
    }

    if (crossing1) {
        if (crossing2)
            return FT(0);
        return squared_distance(ray.source(), seg);
    } else {
        if (crossing2) {
            RT dm;
            dm = _distance_measure_sub(c1s, c1e, startvec, endvec);
            if (dm < RT(0)) {
                return squared_distance(seg.source(), ray);
            } else {
                if (dm > RT(0)) {
                    return squared_distance(seg.target(), ray);
                } else {
                    // parallel, should not happen (no crossing)
                    return squared_distance_parallel(seg, ray);
                }
            }
        } else {

            FT min1, min2;
            RT dm;
            dm = _distance_measure_sub(c1s, c1e, startvec, endvec);
            if (dm == RT(0))
                return squared_distance_parallel(seg, ray);
            min1 = (dm < RT(0))
                 ? squared_distance(seg.source(), ray)
                 : squared_distance(seg.target(), ray);
            min2 = squared_distance(ray.source(), seg);
            return (min1 < min2) ? min1 : min2;
        }
    }
}



template <class R>
inline typename R::FT
squared_distance(
    const Ray_2<R> & ray,
    const Segment_2<R> & seg)
{
    return squared_distance(seg, ray);
}




template <class RT, class R>
typename R::FT
_sqd_to_line(const Vector_2<R> &diff,
                   const RT & wcross, const Vector_2<R> &dir )
{
    typedef typename R::FT FT;
    RT numerator = wcross*wcross;
    RT denominator = wmult((R*)0, RT(wdot(dir,dir)),
                    diff.hw(), diff.hw());
    FT result = R::make_FT(numerator, denominator);
    return result;
}



template <class R>
typename R::FT
squared_distance(
    const Segment_2<R> &seg,
    const Line_2<R> &line)
{
    typedef typename R::RT RT;
    typedef typename R::FT FT;
    const Vector_2<R> &linedir = line.direction().vector();
    const Point_2<R> &linepoint = line.point();
    Vector_2<R> startvec(seg.source()-linepoint);
    Vector_2<R> endvec(seg.target()-linepoint);

    bool crossing1;
    RT c1s, c1e;
    if (seg.source() == seg.target())
        return squared_distance(seg.source(), line);
    c1s = wcross(linedir, startvec);
    c1e = wcross(linedir, endvec);
    if (c1s < RT(0)) {
        crossing1 = (c1e >= RT(0));
    } else {
        if (c1e <= RT(0)) {
            crossing1 = true;
        } else {
            crossing1 = (c1s == RT(0));
        }
    }

    if (crossing1) {
        return (FT)0;
    } else {
        RT dm;
        dm = _distance_measure_sub(c1s, c1e, startvec, endvec);
        if (dm <= RT(0)) {
            return _sqd_to_line(startvec, c1s, linedir);
        } else {
            return _sqd_to_line(endvec, c1e, linedir);
        }
    }
}



template <class R>
inline typename R::FT
squared_distance(
    const Line_2<R> & line,
    const Segment_2<R> & seg)
{
    return squared_distance(seg, line);
}



template <class R>
typename R::FT
ray_ray_squared_distance_parallel(
    const Vector_2<R> &ray1dir,
    const Vector_2<R> &ray2dir,
    const Vector_2<R> &from1to2)
{
    typedef typename R::RT RT;
    typedef typename R::FT FT;
    if (!is_acute_angle(ray1dir, from1to2)) {
        bool same_direction;
        if (abs(ray1dir.hx()) > abs(ray1dir.hy())) {
            same_direction =
                (sign(ray1dir.hx()) == sign(ray2dir.hx()));
        } else {
            same_direction =
                (sign(ray1dir.hy()) == sign(ray2dir.hy()));
        }
        if (!same_direction)
            return (typename R::FT)(from1to2*from1to2);
    }
    RT wcr, w;
    wcr = wcross(ray1dir, from1to2);
    w = from1to2.hw();
    return (typename R::FT)(FT(wcr*wcr)
         / FT(wmult((R*)0, RT(wdot(ray1dir, ray1dir)), w, w)));
}



template <class R>
typename R::FT
squared_distance(
    const Ray_2<R> &ray1,
    const Ray_2<R> &ray2)
{
    typedef typename R::FT FT;
    const Vector_2<R> &ray1dir = ray1.direction().vector();
    const Vector_2<R> &ray2dir = ray2.direction().vector();
    Vector_2<R> diffvec(ray2.source()-ray1.source());

    bool crossing1, crossing2;
    Orientation dirorder;
    dirorder = orientation(ray1dir, ray2dir);
    switch (dirorder) {
    case COUNTERCLOCKWISE:
        crossing1 = !clockwise(diffvec, ray2dir);
        crossing2 = !counterclockwise(ray1dir, diffvec);
        break;
    case CLOCKWISE:
        crossing1 = !counterclockwise(diffvec, ray2dir);
        crossing2 = !clockwise(ray1dir, diffvec);
        break;
    case COLLINEAR:
        return ray_ray_squared_distance_parallel(ray1dir,ray2dir,diffvec);
    }

    if (crossing1) {
        if (crossing2)
            return (FT)0;
        return squared_distance(ray2.source(), ray1);
    } else {
        if (crossing2) {
            return squared_distance(ray1.source(), ray2);
        } else {

            FT min1, min2;
            min1 = squared_distance(ray1.source(), ray2);
            min2 = squared_distance(ray2.source(), ray1);
            return (min1 < min2) ? min1 : min2;
        }
    }
}





template <class R>
extern typename R::FT
squared_distance(
    const Line_2<R> &line,
    const Ray_2<R> &ray)
{
    typedef typename R::FT FT;
    Vector_2<R> normalvec(line.a(), line.b());
    Vector_2<R> diff = ray.source()-line.point();
    FT sign_dist = diff*normalvec;
    if (sign_dist < FT(0)) {
        if (is_acute_angle(normalvec, ray.direction().vector()) )
            return (FT)0;
    } else {
        if (is_obtuse_angle(normalvec, ray.direction().vector()) )
            return (FT)0;
    }
    return (typename R::FT)((sign_dist*sign_dist)/(normalvec*normalvec));
}


template <class R>
inline typename R::FT
squared_distance(
    const Ray_2<R> & ray,
    const Line_2<R> & line)
{
    return squared_distance(line, ray);
}



template <class R>
bool
_are_parallel(
    const Line_2<R> &line1,
    const Line_2<R> &line2)
{
    return line1.a()*line2.b() == line2.a()*line1.b();
}

template <class R>
typename R::FT
squared_distance(
    const Line_2<R> &line1,
    const Line_2<R> &line2)
{
    typedef typename R::FT FT;
    if (_are_parallel(line1,line2))
        return squared_distance(line1.point(), line2);
    else
        return (FT)0;
}



CGAL_END_NAMESPACE


#endif
