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
// file          : include/CGAL/squared_distance_utils.h
// package       : Distance_2 (2.1.2)
// source        : sqdistance_2.fw
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : Saarbruecken
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_SQUARED_DISTANCE_UTILS_H
#define CGAL_SQUARED_DISTANCE_UTILS_H

CGAL_BEGIN_NAMESPACE


template <class R>
bool is_null(const Vector_2<R> &v)
{
    typedef typename R::RT RT;
    return v.hx()==RT(0) && v.hy()==RT(0);
}


template <class R>
R_RT_return(R)
wdot(const Vector_2<R> &u,
    const Vector_2<R> &v)
{
    return  (R_RT_return(R))(u.hx()*v.hx() + u.hy()*v.hy());
}

#ifdef CGAL_HOMOGENEOUS_H
template <class RT>
RT wdot(const Point_2< Homogeneous<RT> > &p,
    const Point_2<Homogeneous<RT> > &q,
    const Point_2<Homogeneous<RT> > &r)
{
    return  (q.hw()*p.hx() - p.hw()*q.hx())*(q.hw()*r.hx() - r.hw()*q.hx()) +
            (q.hw()*p.hy() - p.hw()*q.hy())*(q.hw()*r.hy() - r.hw()*q.hy());
}
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
template <class FT>
FT wdot(const Point_2< Cartesian<FT> > &p,
    const Point_2< Cartesian<FT> > &q,
    const Point_2< Cartesian<FT> > &r)
{
    return  (p.hx() - q.hx())*(r.hx() - q.hx()) +
            (p.hy() - q.hy())*(r.hy() - q.hy());
}
#endif // CGAL_CARTESIAN_H



template <class R>
R_RT_return(R)
wcross(const Vector_2<R> &u,
    const Vector_2<R> &v)
{
    return (R_RT_return(R))(u.hx()*v.hy() - u.hy()*v.hx());
}

#ifdef CGAL_HOMOGENEOUS_H
template <class RT>
RT wcross(const Point_2< Homogeneous<RT> > &p,
    const Point_2< Homogeneous<RT> > &q,
    const Point_2< Homogeneous<RT> > &r)
{
    return   p.hx() * (q.hy()*r.hw() - q.hw()*r.hy() )
           + p.hy() * (q.hw()*r.hx() - q.hx()*r.hw() )
           + p.hw() * (q.hx()*r.hy() - q.hy()*r.hx() );
}
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
template <class FT>
FT wcross(const Point_2< Cartesian<FT> > &p,
    const Point_2< Cartesian<FT> > &q,
    const Point_2< Cartesian<FT> > &r)
{
    return (q.x()-p.x())*(r.y()-q.y()) - (q.y()-p.y())*(r.x()-q.x());
}
#endif // CGAL_CARTESIAN_H


template <class R>
inline bool is_acute_angle(const Vector_2<R> &u,
    const Vector_2<R> &v)
{
    typedef typename R::RT RT;
    return RT(wdot(u, v)) > RT(0) ;
}

template <class R>
inline bool is_straight_angle(const Vector_2<R> &u,
    const Vector_2<R> &v)
{
    typedef typename R::RT RT;
    return RT(wdot(u, v)) == RT(0) ;
}

template <class R>
inline bool is_obtuse_angle(const Vector_2<R> &u,
    const Vector_2<R> &v)
{
    typedef typename R::RT RT;
    return RT(wdot(u, v)) < RT(0) ;
}

template <class R>
inline bool is_acute_angle(const Point_2<R> &p,
    const Point_2<R> &q, const Point_2<R> &r)
{
    typedef typename R::RT RT;
    return RT(wdot(p, q, r)) > RT(0) ;
}

template <class R>
inline bool is_straight_angle(const Point_2<R> &p,
    const Point_2<R> &q, const Point_2<R> &r)
{
    typedef typename R::RT RT;
    return RT(wdot(p, q, r)) == RT(0) ;
}

template <class R>
inline bool is_obtuse_angle(const Point_2<R> &p,
    const Point_2<R> &q, const Point_2<R> &r)
{
    typedef typename R::RT RT;
    return RT(wdot(p, q, r)) < RT(0) ;
}


template <class R>
Orientation orientation(const Vector_2<R> &u,
    const Vector_2<R> &v)
{
    typedef typename R::RT RT;
    RT wcr = wcross(u,v);
    return (wcr > RT(0)) ? COUNTERCLOCKWISE :
           (wcr < RT(0)) ? CLOCKWISE
                            : COLLINEAR;
}

template <class R>
inline bool counterclockwise(const Vector_2<R> &u,
    const Vector_2<R> &v)
{
    typedef typename R::RT RT;
    return RT(wcross(u,v)) > RT(0);
}

template <class R>
inline bool leftturn(const Vector_2<R> &u,
    const Vector_2<R> &v)
{
    typedef typename R::RT RT;
    return RT(wcross(u,v)) > RT(0);
}

template <class R>
inline bool clockwise(const Vector_2<R> &u,
    const Vector_2<R> &v)
{
    typedef typename R::RT RT;
    return RT(wcross(u,v)) < RT(0);
}

template <class R>
inline bool rightturn(const Vector_2<R> &u,
    const Vector_2<R> &v)
{
    typedef typename R::RT RT;
    return RT(wcross(u,v)) < RT(0);
}

template <class R>
inline bool collinear(const Vector_2<R> &u,
    const Vector_2<R> &v)
{
    typedef typename R::RT RT;
    return RT(wcross(u,v)) == RT(0);
}

/*
the ordertype, rightturn, leftturn and collinear routines for points are
defined elsewhere.
*/


CGAL_END_NAMESPACE

#endif // CGAL_SQUARED_DISTANCE_UTILS_H
