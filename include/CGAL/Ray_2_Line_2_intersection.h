
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
// file          : include/CGAL/Ray_2_Line_2_intersection.h
// package       : Intersections_2 (1.5)
// source        : intersection_2_1.fw
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : Saarbruecken
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_RAY_2_LINE_2_INTERSECTION_H
#define CGAL_RAY_2_LINE_2_INTERSECTION_H

#ifndef CGAL_LINE_2_H
#include <CGAL/Line_2.h>
#endif // CGAL_LINE_2_H
#ifndef CGAL_RAY_2_H
#include <CGAL/Ray_2.h>
#endif // CGAL_RAY_2_H
#ifndef CGAL_POINT_2_H
#include <CGAL/Point_2.h>
#endif // CGAL_POINT_2_H
#ifndef CGAL_UTILS_H
#include <CGAL/utils.h>
#endif // CGAL_UTILS_H
#ifndef CGAL_NUMBER_UTILS_H
#include <CGAL/number_utils.h>
#endif // CGAL_NUMBER_UTILS_H

template <class R>
class CGAL_Ray_2_Line_2_pair {
public:
    enum Intersection_results {NO, POINT, RAY};
    CGAL_Ray_2_Line_2_pair() ;
    CGAL_Ray_2_Line_2_pair(CGAL_Ray_2<R> const *ray,
                            CGAL_Line_2<R> const *line);
    ~CGAL_Ray_2_Line_2_pair() {}

#ifndef CGAL_CFG_RETURN_TYPE_BUG_2
    Intersection_results intersection_type() const;
#else
    Intersection_results intersection_type() const
{
    if (_known)
        return _result;
    // The non const this pointer is used to cast away const.
    CGAL_Ray_2_Line_2_pair<R> *ncthis =
                (CGAL_Ray_2_Line_2_pair<R> *) this;
    ncthis->_known = true;
    const CGAL_Line_2<R> &l1 = _ray->supporting_line();
    CGAL_Line_2_Line_2_pair<R> linepair(&l1, _line);
    switch ( linepair.intersection_type()) {
    case CGAL_Line_2_Line_2_pair<R>::NO:
        ncthis->_result = NO;
        break;
    case CGAL_Line_2_Line_2_pair<R>::POINT:
        linepair.intersection(ncthis->_intersection_point);
        ncthis->_result = (_ray->collinear_has_on(_intersection_point) ) ?
                POINT : NO;
        break;
    case CGAL_Line_2_Line_2_pair<R>::LINE:
        ncthis->_result = RAY;
        break;
    }
    return _result;
}

#endif // CGAL_CFG_RETURN_TYPE_BUG_2

    bool                intersection(CGAL_Point_2<R> &result) const;
    bool                intersection(CGAL_Ray_2<R> &result) const;
protected:
    CGAL_Ray_2<R> const *   _ray;
    CGAL_Line_2<R> const *  _line;
    bool                    _known;
    Intersection_results    _result;
    CGAL_Point_2<R>         _intersection_point;
};

template <class R>
inline bool CGAL_do_intersect(
    const CGAL_Ray_2<R> &p1,
    const CGAL_Line_2<R> &p2)
{
    typedef CGAL_Ray_2_Line_2_pair<R> pair_t;
    pair_t pair(&p1, &p2);
    return pair.intersection_type() != pair_t::NO;
}

#ifndef CGAL_OBJECT_H
#include <CGAL/Object.h>
#endif // CGAL_OBJECT_H

template <class R>
CGAL_Object
CGAL_intersection(const CGAL_Ray_2<R> &ray, const CGAL_Line_2<R>&line)
{
    typedef CGAL_Ray_2_Line_2_pair<R> is_t;
    is_t ispair(&ray, &line);
    switch (ispair.intersection_type()) {
    case is_t::NO:
    default:
        return CGAL_Object();
    case is_t::POINT: {
        CGAL_Point_2<R> pt;
        ispair.intersection(pt);
        return CGAL_Object(new CGAL_Wrapper< CGAL_Point_2<R> >(pt));
    }
    case is_t::RAY: {
        return CGAL_Object(new CGAL_Wrapper< CGAL_Ray_2<R> >(ray));
    }
    }
}

template <class R>
class CGAL_Line_2_Ray_2_pair: public CGAL_Ray_2_Line_2_pair<R> {
public:
    CGAL_Line_2_Ray_2_pair(
            CGAL_Line_2<R> const *line,
            CGAL_Ray_2<R> const *ray) :
                                CGAL_Ray_2_Line_2_pair<R>(ray, line) {}
};

template <class R>
inline bool CGAL_do_intersect(
    const CGAL_Line_2<R> &p1,
    const CGAL_Ray_2<R> &p2)
{
    typedef CGAL_Line_2_Ray_2_pair<R> pair_t;
    pair_t pair(&p1, &p2);
    return pair.intersection_type() != pair_t::NO;
}

template <class R>
inline CGAL_Object
CGAL_intersection(const CGAL_Line_2<R> &line, const CGAL_Ray_2<R> &ray)
{
    return CGAL_intersection(ray, line);
}


#ifndef CGAL_LINE_2_LINE_2_INTERSECTION_H
#include <CGAL/Line_2_Line_2_intersection.h>
#endif // CGAL_LINE_2_LINE_2_INTERSECTION_H

template <class R>
CGAL_Ray_2_Line_2_pair<R>::CGAL_Ray_2_Line_2_pair()
{
    _ray = 0;
    _line = 0;
    _known = false;
}

template <class R>
CGAL_Ray_2_Line_2_pair<R>::CGAL_Ray_2_Line_2_pair(
    CGAL_Ray_2<R> const *ray, CGAL_Line_2<R> const *line)
{
    _ray = ray;
    _line = line;
    _known = false;
}

#ifndef CGAL_CFG_RETURN_TYPE_BUG_2
template <class R>
CGAL_Ray_2_Line_2_pair<R>::Intersection_results
CGAL_Ray_2_Line_2_pair<R>::intersection_type() const
{
    if (_known)
        return _result;
    // The non const this pointer is used to cast away const.
    CGAL_Ray_2_Line_2_pair<R> *ncthis =
                (CGAL_Ray_2_Line_2_pair<R> *) this;
    ncthis->_known = true;
    const CGAL_Line_2<R> &l1 = _ray->supporting_line();
    CGAL_Line_2_Line_2_pair<R> linepair(&l1, _line);
    switch ( linepair.intersection_type()) {
    case CGAL_Line_2_Line_2_pair<R>::NO:
        ncthis->_result = NO;
        break;
    case CGAL_Line_2_Line_2_pair<R>::POINT:
        linepair.intersection(ncthis->_intersection_point);
        ncthis->_result = (_ray->collinear_has_on(_intersection_point) ) ?
                POINT : NO;
        break;
    case CGAL_Line_2_Line_2_pair<R>::LINE:
        ncthis->_result = RAY;
        break;
    }
    return _result;
}

#endif // CGAL_CFG_RETURN_TYPE_BUG_2

template <class R>
bool
CGAL_Ray_2_Line_2_pair<R>::intersection(CGAL_Point_2<R> &result) const
{
    if (!_known)
        intersection_type();
    if (_result != POINT)
        return false;
    result = _intersection_point;
    return true;
}

template <class R>
bool
CGAL_Ray_2_Line_2_pair<R>::intersection(CGAL_Ray_2<R> &result) const
{
    if (!_known)
        intersection_type();
    if (_result != RAY)
        return false;
    result = *_ray;
    return true;
}


#endif
