
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

#ifndef CGAL_RAY_2_LINE_2_INTERSECTION_H
#define CGAL_RAY_2_LINE_2_INTERSECTION_H

#include <CGAL/Line_2.h>
#include <CGAL/Ray_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/utils.h>
#include <CGAL/number_utils.h>

template <class R>
class CGAL_Ray_2_Line_2_pair {
public:
    enum Intersection_results {NO, POINT, RAY};
    CGAL_Ray_2_Line_2_pair() ;
    CGAL_Ray_2_Line_2_pair(CGAL_Ray_2<R> const *ray,
                            CGAL_Line_2<R> const *line);
    ~CGAL_Ray_2_Line_2_pair() {}

#ifndef CGAL_WORKAROUND_005
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

#endif // CGAL_WORKAROUND_005

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
    return pair.intersection_type() == pair_t::NO;
}

#include <CGAL/Object.h>

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
    return pair.intersection_type() == pair_t::NO;
}

template <class R>
inline CGAL_Object
CGAL_intersection(const CGAL_Line_2<R> &line, const CGAL_Ray_2<R> &ray)
{
    return CGAL_intersection(ray, line);
}


#include <CGAL/Line_2_Line_2_intersection.h>

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

#ifndef CGAL_WORKAROUND_005
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

#endif // CGAL_WORKAROUND_005

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
