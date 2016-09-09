// ============================================================================
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
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/squared_distance_3_0.C
// author(s)     : Geert-Jan Giezeman
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


#ifndef CGAL_UTILS_H
#include <CGAL/utils.h>
#endif // CGAL_UTILS_H
#ifndef CGAL_ENUM_H
#include <CGAL/enum.h>
#endif // CGAL_ENUM_H
#ifndef CGAL_WMULT_H
#include <CGAL/wmult.h>
#endif // CGAL_WMULT_H

template <class R>
bool CGAL_is_null(const CGAL_Vector_3<R> &v)
{
    typedef typename R::RT RT;
    return v.hx()==RT(0) && v.hy()==RT(0) && v.hz()==RT(0);
}


template <class R>
R_RT_return(R)
CGAL_wdot(const CGAL_Vector_3<R> &u,
    const CGAL_Vector_3<R> &v)
{
    return  (R_RT_return(R))(u.hx()*v.hx() + u.hy()*v.hy() + u.hz()*v.hz());
}

#ifdef CGAL_HOMOGENEOUS_H
template <class RT>
RT CGAL_wdot(const CGAL_Point_3< CGAL_Homogeneous<RT> > &p,
    const CGAL_Point_3<CGAL_Homogeneous<RT> > &q,
    const CGAL_Point_3<CGAL_Homogeneous<RT> > &r)
{
    return  (q.hw()*p.hx() - p.hw()*q.hx())*(q.hw()*r.hx() - r.hw()*q.hx()) +
            (q.hw()*p.hy() - p.hw()*q.hy())*(q.hw()*r.hy() - r.hw()*q.hy()) +
            (q.hw()*p.hz() - p.hw()*q.hz())*(q.hw()*r.hz() - r.hw()*q.hz());
}
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
template <class FT>
FT CGAL_wdot(const CGAL_Point_3< CGAL_Cartesian<FT> > &p,
    const CGAL_Point_3< CGAL_Cartesian<FT> > &q,
    const CGAL_Point_3< CGAL_Cartesian<FT> > &r)
{
    return  (p.hx() - q.hx())*(r.hx() - q.hx()) +
            (p.hy() - q.hy())*(r.hy() - q.hy()) +
            (p.hz() - q.hz())*(r.hz() - q.hz());
}
#endif // CGAL_CARTESIAN_H



template <class R>
CGAL_Vector_3<R> CGAL_wcross(const CGAL_Vector_3<R> &u,
    const CGAL_Vector_3<R> &v)
{
    return CGAL_Vector_3<R>(
        u.hy()*v.hz() - u.hz()*v.hy(),
        u.hz()*v.hx() - u.hx()*v.hz(),
        u.hx()*v.hy() - u.hy()*v.hx());
}

#ifdef CGAL_HOMOGENEOUS_H
template <class RT>
CGAL_Vector_3< CGAL_Homogeneous<RT> >
CGAL_wcross(const CGAL_Point_3< CGAL_Homogeneous<RT> > &p,
    const CGAL_Point_3< CGAL_Homogeneous<RT> > &q,
    const CGAL_Point_3< CGAL_Homogeneous<RT> > &r)
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
    return CGAL_Vector_3< CGAL_Homogeneous<RT> >(x, y, z);
}
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
template <class FT>
CGAL_Vector_3< CGAL_Cartesian<FT> >
CGAL_wcross(const CGAL_Point_3< CGAL_Cartesian<FT> > &p,
    const CGAL_Point_3< CGAL_Cartesian<FT> > &q,
    const CGAL_Point_3< CGAL_Cartesian<FT> > &r)
{
    FT x,y,z;
    x = (q.y()-p.y())*(r.z()-q.z()) - (q.z()-p.z())*(r.y()-q.y());
    y = (q.z()-p.z())*(r.x()-q.x()) - (q.x()-p.x())*(r.z()-q.z());
    z = (q.x()-p.x())*(r.y()-q.y()) - (q.y()-p.y())*(r.x()-q.x());
    return CGAL_Vector_3< CGAL_Cartesian<FT> >(x, y, z);
}
#endif // CGAL_CARTESIAN_H

template <class R>
inline bool CGAL_is_acute_angle(const CGAL_Vector_3<R> &u,
    const CGAL_Vector_3<R> &v)
{
    typedef typename R::RT RT;
    return RT(CGAL_wdot(u, v)) > RT(0) ;
}

template <class R>
inline bool CGAL_is_straight_angle(const CGAL_Vector_3<R> &u,
    const CGAL_Vector_3<R> &v)
{
    typedef typename R::RT RT;
    return RT(CGAL_wdot(u, v)) == RT(0) ;
}

template <class R>
inline bool CGAL_is_obtuse_angle(const CGAL_Vector_3<R> &u,
    const CGAL_Vector_3<R> &v)
{
    typedef typename R::RT RT;
    return RT(CGAL_wdot(u, v)) < RT(0) ;
}

template <class R>
inline bool CGAL_is_acute_angle(const CGAL_Point_3<R> &p,
    const CGAL_Point_3<R> &q, const CGAL_Point_3<R> &r)
{
    typedef typename R::RT RT;
    return RT(CGAL_wdot(p, q, r)) > RT(0) ;
}

template <class R>
inline bool CGAL_is_straight_angle(const CGAL_Point_3<R> &p,
    const CGAL_Point_3<R> &q, const CGAL_Point_3<R> &r)
{
    typedef typename R::RT RT;
    return RT(CGAL_wdot(p, q, r)) == RT(0) ;
}

template <class R>
inline bool CGAL_is_obtuse_angle(const CGAL_Point_3<R> &p,
    const CGAL_Point_3<R> &q, const CGAL_Point_3<R> &r)
{
    typedef typename R::RT RT;
    return RT(CGAL_wdot(p, q, r)) < RT(0) ;
}

template <class R>
R_FT_return(R)
CGAL_squared_distance_to_plane(
    const CGAL_Vector_3<R> & normal,
    const CGAL_Vector_3<R> & diff)
{
    typedef typename R::RT RT;
    RT dot, squared_length;
    dot = CGAL_wdot(normal, diff);
    squared_length = CGAL_wdot(normal, normal);
    return (R_FT_return(R))
        ((dot*dot) / CGAL_wmult((R*)0, squared_length, diff.hw(), diff.hw()));
}

template <class R>
R_FT_return(R)
CGAL_squared_distance_to_line(
    const CGAL_Vector_3<R> & dir,
    const CGAL_Vector_3<R> & diff)
{
    typedef typename R::RT RT;
    CGAL_Vector_3<R> wcr = CGAL_wcross(dir, diff);
    return (R_FT_return(R))((wcr*wcr)/
        CGAL_wmult((R*)0, RT(CGAL_wdot(dir, dir)), diff.hw(), diff.hw()));
}

