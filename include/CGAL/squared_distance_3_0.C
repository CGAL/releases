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
// file          : include/CGAL/squared_distance_3_0.C
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
R_RT_return(R)
wdot(const Vector_3<R> &u,
    const Vector_3<R> &v)
{
    return  (R_RT_return(R))(u.hx()*v.hx() + u.hy()*v.hy() + u.hz()*v.hz());
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
R_FT_return(R)
squared_distance_to_plane(
    const Vector_3<R> & normal,
    const Vector_3<R> & diff)
{
    typedef typename R::RT RT;
    RT dot, squared_length;
    dot = wdot(normal, diff);
    squared_length = wdot(normal, normal);
    return (R_FT_return(R))
        ((dot*dot) / wmult((R*)0, squared_length, diff.hw(), diff.hw()));
}


template <class R>
R_FT_return(R)
squared_distance_to_line(
    const Vector_3<R> & dir,
    const Vector_3<R> & diff)
{
    typedef typename R::RT RT;
    Vector_3<R> wcr = wcross(dir, diff);
    return (R_FT_return(R))((wcr*wcr)/
        wmult((R*)0, RT(wdot(dir, dir)), diff.hw(), diff.hw()));
}


CGAL_END_NAMESPACE
