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
// file          : include/CGAL/squared_distance_3_0.h
// package       : Distance_3 (2.4.3)
// source        : sqdistance_3.fw
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : Saarbruecken
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_DISTANCE_3_0_H
#define CGAL_DISTANCE_3_0_H

#ifndef CGAL_POINT_3_H
#include <CGAL/Point_3.h>
#endif // CGAL_POINT_3_H

#ifndef CGAL_UTILS_H
#include <CGAL/utils.h>
#endif // CGAL_UTILS_H
#ifndef CGAL_ENUM_H
#include <CGAL/enum.h>
#endif // CGAL_ENUM_H
#ifndef CGAL_WMULT_H
#include <CGAL/wmult.h>
#endif // CGAL_WMULT_H

CGAL_BEGIN_NAMESPACE



template <class R>
bool is_null(const Vector_3<R> &v)
{
    typedef typename R::RT RT;
    return v.hx()==RT(0) && v.hy()==RT(0) && v.hz()==RT(0);
}


template <class R>
typename R::RT
wdot(const Vector_3<R> &u,
    const Vector_3<R> &v)
{
    return  (u.hx()*v.hx() + u.hy()*v.hy() + u.hz()*v.hz());
}

#ifdef CGAL_HOMOGENEOUS_H
template <class RT>
RT wdot(const Point_3< Homogeneous<RT> > &p,
    const Point_3<Homogeneous<RT> > &q,
    const Point_3<Homogeneous<RT> > &r)
{
    return  (q.hw()*p.hx() - p.hw()*q.hx())*(q.hw()*r.hx() - r.hw()*q.hx()) +
            (q.hw()*p.hy() - p.hw()*q.hy())*(q.hw()*r.hy() - r.hw()*q.hy()) +
            (q.hw()*p.hz() - p.hw()*q.hz())*(q.hw()*r.hz() - r.hw()*q.hz());
}
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
template <class FT>
FT wdot(const Point_3< Cartesian<FT> > &p,
    const Point_3< Cartesian<FT> > &q,
    const Point_3< Cartesian<FT> > &r)
{
    return  (p.hx() - q.hx())*(r.hx() - q.hx()) +
            (p.hy() - q.hy())*(r.hy() - q.hy()) +
            (p.hz() - q.hz())*(r.hz() - q.hz());
}
#endif // CGAL_CARTESIAN_H



template <class R>
Vector_3<R> wcross(const Vector_3<R> &u,
    const Vector_3<R> &v)
{
    return Vector_3<R>(
        u.hy()*v.hz() - u.hz()*v.hy(),
        u.hz()*v.hx() - u.hx()*v.hz(),
        u.hx()*v.hy() - u.hy()*v.hx());
}

#ifdef CGAL_HOMOGENEOUS_H
template <class RT>
Vector_3< Homogeneous<RT> >
wcross(const Point_3< Homogeneous<RT> > &p,
    const Point_3< Homogeneous<RT> > &q,
    const Point_3< Homogeneous<RT> > &r)
{
    RT x,y,z;
    x =  p.hy() * (q.hz()*r.hw() - q.hw()*r.hz() )
       + p.hz() * (q.hw()*r.hy() - q.hy()*r.hw() )
       + p.hw() * (q.hy()*r.hz() - q.hz()*r.hy() );
    y =  p.hz() * (q.hx()*r.hw() - q.hw()*r.hx() )
       + p.hx() * (q.hw()*r.hz() - q.hz()*r.hw() )
       + p.hw() * (q.hz()*r.hx() - q.hx()*r.hz() );
    z =  p.hx() * (q.hy()*r.hw() - q.hw()*r.hy() )
       + p.hy() * (q.hw()*r.hx() - q.hx()*r.hw() )
       + p.hw() * (q.hx()*r.hy() - q.hy()*r.hx() );
    return Vector_3< Homogeneous<RT> >(x, y, z);
}
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
template <class FT>
Vector_3< Cartesian<FT> >
wcross(const Point_3< Cartesian<FT> > &p,
    const Point_3< Cartesian<FT> > &q,
    const Point_3< Cartesian<FT> > &r)
{
    FT x,y,z;
    x = (q.y()-p.y())*(r.z()-q.z()) - (q.z()-p.z())*(r.y()-q.y());
    y = (q.z()-p.z())*(r.x()-q.x()) - (q.x()-p.x())*(r.z()-q.z());
    z = (q.x()-p.x())*(r.y()-q.y()) - (q.y()-p.y())*(r.x()-q.x());
    return Vector_3< Cartesian<FT> >(x, y, z);
}
#endif // CGAL_CARTESIAN_H


template <class R>
inline bool is_acute_angle(const Vector_3<R> &u,
    const Vector_3<R> &v)
{
    typedef typename R::RT RT;
    return RT(wdot(u, v)) > RT(0) ;
}

template <class R>
inline bool is_straight_angle(const Vector_3<R> &u,
    const Vector_3<R> &v)
{
    typedef typename R::RT RT;
    return RT(wdot(u, v)) == RT(0) ;
}

template <class R>
inline bool is_obtuse_angle(const Vector_3<R> &u,
    const Vector_3<R> &v)
{
    typedef typename R::RT RT;
    return RT(wdot(u, v)) < RT(0) ;
}

template <class R>
inline bool is_acute_angle(const Point_3<R> &p,
    const Point_3<R> &q, const Point_3<R> &r)
{
    typedef typename R::RT RT;
    return RT(wdot(p, q, r)) > RT(0) ;
}

template <class R>
inline bool is_straight_angle(const Point_3<R> &p,
    const Point_3<R> &q, const Point_3<R> &r)
{
    typedef typename R::RT RT;
    return RT(wdot(p, q, r)) == RT(0) ;
}

template <class R>
inline bool is_obtuse_angle(const Point_3<R> &p,
    const Point_3<R> &q, const Point_3<R> &r)
{
    typedef typename R::RT RT;
    return RT(wdot(p, q, r)) < RT(0) ;
}


template <class R>
inline typename R::FT
squared_distance(
    const Point_3<R> & pt1,
    const Point_3<R> & pt2)
{
    Vector_3<R> vec(pt1-pt2);
    return vec*vec;
}


template <class R>
typename R::FT
squared_distance_to_plane(
    const Vector_3<R> & normal,
    const Vector_3<R> & diff)
{
    typedef typename R::RT RT;
    RT dot, squared_length;
    dot = wdot(normal, diff);
    squared_length = wdot(normal, normal);
    return (typename R::FT)
        ((dot*dot) / wmult((R*)0, squared_length, diff.hw(), diff.hw()));
}


template <class R>
typename R::FT
squared_distance_to_line(
    const Vector_3<R> & dir,
    const Vector_3<R> & diff)
{
    typedef typename R::RT RT;
    Vector_3<R> wcr = wcross(dir, diff);
    return (typename R::FT)((wcr*wcr)/
        wmult((R*)0, RT(wdot(dir, dir)), diff.hw(), diff.hw()));
}



CGAL_END_NAMESPACE


#endif
