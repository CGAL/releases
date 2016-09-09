
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

#ifndef CGAL_RAY_2_TRIANGLE_2_INTERSECTION_H
#define CGAL_RAY_2_TRIANGLE_2_INTERSECTION_H

#include <CGAL/Segment_2.h>
#include <CGAL/Ray_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Point_2.h>

template <class R>
class CGAL_Ray_2_Triangle_2_pair {
public:
    enum Intersection_results {NO, POINT, SEGMENT};
    CGAL_Ray_2_Triangle_2_pair() ;
    CGAL_Ray_2_Triangle_2_pair(CGAL_Ray_2<R> const *ray,
                            CGAL_Triangle_2<R> const *trian);
    ~CGAL_Ray_2_Triangle_2_pair() {}
#ifdef CGAL_WORKAROUND_005
    Intersection_results intersection_type() const
    {
        if (_known)
            return _result;
    // The non const this pointer is used to cast away const.
        CGAL_Ray_2_Triangle_2_pair<R> *ncthis =
                    (CGAL_Ray_2_Triangle_2_pair<R> *) this;
        ncthis->_known = true;
        CGAL__Straight_2<R> straight(*_ray);
    CGAL_Line_2<R> l(_trian->vertex(0), _trian->vertex(1));
    if (l.oriented_side(_trian->vertex(2)) == CGAL_ON_POSITIVE_SIDE) {
    //    if (_trian->is_counterclockwise()) {
            straight.cut_right_off(
                CGAL_Line_2<R>(_trian->vertex(0), _trian->vertex(1)));
            straight.cut_right_off(
                CGAL_Line_2<R>(_trian->vertex(1), _trian->vertex(2)));
            straight.cut_right_off(
                CGAL_Line_2<R>(_trian->vertex(2), _trian->vertex(0)));
        } else {
            straight.cut_right_off(
                CGAL_Line_2<R>(_trian->vertex(2), _trian->vertex(1)));
            straight.cut_right_off(
                CGAL_Line_2<R>(_trian->vertex(1), _trian->vertex(0)));
            straight.cut_right_off(
                CGAL_Line_2<R>(_trian->vertex(0), _trian->vertex(2)));
        }
        switch (straight.current_state()) {
        case CGAL__Straight_2<R>::EMPTY:
            ncthis->_result = NO;
            return _result;
        case CGAL__Straight_2<R>::POINT: {
            straight.current(ncthis->_intersection_point);
            ncthis->_result = POINT;
            return _result;
            }
        case CGAL__Straight_2<R>::SEGMENT: {
            CGAL_Segment_2<R> seg;
            straight.current(seg);
            ncthis->_intersection_point = seg.start();
            ncthis->_other_point = seg.end();
            ncthis->_result = SEGMENT;
            return _result;
            }
        default:  // should not happen.
            CGAL_kernel_assertion(false);
            ncthis->_result = NO;
            return _result;
        }
    }
    
#else
    Intersection_results intersection_type() const;
#endif // CGAL_WORKAROUND_005
    bool                intersection(CGAL_Point_2<R> &result) const;
    bool                intersection(CGAL_Segment_2<R> &result) const;
protected:
    CGAL_Ray_2<R> const* _ray;
    CGAL_Triangle_2<R> const *  _trian;
    bool                    _known;
    Intersection_results     _result;
    CGAL_Point_2<R>         _intersection_point;
    CGAL_Point_2<R>         _other_point;
};

template <class R>
inline bool CGAL_do_intersect(
    const CGAL_Ray_2<R> &p1,
    const CGAL_Triangle_2<R> &p2)
{
    typedef CGAL_Ray_2_Triangle_2_pair<R> pair_t;
    pair_t pair(&p1, &p2);
    return pair.intersection_type() == pair_t::NO;
}



#include <CGAL/Line_2.h>
#include <CGAL/utils.h>
#include <CGAL/number_utils.h>
#include <CGAL/Straight_2.h>

template <class R>
CGAL_Ray_2_Triangle_2_pair<R>::
CGAL_Ray_2_Triangle_2_pair()
{
    _known = false;
    _ray = 0;
    _trian = 0;
}

template <class R>
CGAL_Ray_2_Triangle_2_pair<R>::
CGAL_Ray_2_Triangle_2_pair(CGAL_Ray_2<R> const *ray,
                            CGAL_Triangle_2<R> const *trian)
{
    _known = false;
    _ray = ray;
    _trian = trian;
}

#ifndef CGAL_WORKAROUND_005
template <class R>
CGAL_Ray_2_Triangle_2_pair<R>::Intersection_results
CGAL_Ray_2_Triangle_2_pair<R>::intersection_type() const
{
    if (_known)
        return _result;
// The non const this pointer is used to cast away const.
    CGAL_Ray_2_Triangle_2_pair<R> *ncthis =
                (CGAL_Ray_2_Triangle_2_pair<R> *) this;
    ncthis->_known = true;
    CGAL__Straight_2<R> straight(*_ray);
CGAL_Line_2<R> l(_trian->vertex(0), _trian->vertex(1));
if (l.oriented_side(_trian->vertex(2)) == CGAL_ON_POSITIVE_SIDE) {
//    if (_trian->is_counterclockwise()) {
        straight.cut_right_off(
            CGAL_Line_2<R>(_trian->vertex(0), _trian->vertex(1)));
        straight.cut_right_off(
            CGAL_Line_2<R>(_trian->vertex(1), _trian->vertex(2)));
        straight.cut_right_off(
            CGAL_Line_2<R>(_trian->vertex(2), _trian->vertex(0)));
    } else {
        straight.cut_right_off(
            CGAL_Line_2<R>(_trian->vertex(2), _trian->vertex(1)));
        straight.cut_right_off(
            CGAL_Line_2<R>(_trian->vertex(1), _trian->vertex(0)));
        straight.cut_right_off(
            CGAL_Line_2<R>(_trian->vertex(0), _trian->vertex(2)));
    }
    switch (straight.current_state()) {
    case CGAL__Straight_2<R>::EMPTY:
        ncthis->_result = NO;
        return _result;
    case CGAL__Straight_2<R>::POINT: {
        straight.current(ncthis->_intersection_point);
        ncthis->_result = POINT;
        return _result;
        }
    case CGAL__Straight_2<R>::SEGMENT: {
        CGAL_Segment_2<R> seg;
        straight.current(seg);
        ncthis->_intersection_point = seg.start();
        ncthis->_other_point = seg.end();
        ncthis->_result = SEGMENT;
        return _result;
        }
    default:  // should not happen.
        CGAL_kernel_assertion(false);
        ncthis->_result = NO;
        return _result;
    }
}

#endif // CGAL_WORKAROUND_005

template <class R>
bool
CGAL_Ray_2_Triangle_2_pair<R>::
intersection(CGAL_Point_2<R> &result) const
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
CGAL_Ray_2_Triangle_2_pair<R>::
intersection(CGAL_Segment_2<R> &result) const
{
    if (!_known)
        intersection_type();
    if (_result != SEGMENT)
        return false;
    result = CGAL_Segment_2<R>(_intersection_point, _other_point);
    return true;
}


#include <CGAL/Object.h>

template <class R>
CGAL_Object
CGAL_intersection(const CGAL_Ray_2<R> &ray, const CGAL_Triangle_2<R>&tr)
{
    typedef CGAL_Ray_2_Triangle_2_pair<R> is_t;
    is_t ispair(&ray, &tr);
    switch (ispair.intersection_type()) {
    case is_t::NO:
    default:
        return CGAL_Object();
    case is_t::POINT: {
        CGAL_Point_2<R> pt;
        ispair.intersection(pt);
        return CGAL_Object(new CGAL_Wrapper< CGAL_Point_2<R> >(pt));
    }
    case is_t::SEGMENT: {
        CGAL_Segment_2<R> iseg;
        ispair.intersection(iseg);
        return CGAL_Object(new CGAL_Wrapper< CGAL_Segment_2<R> >(iseg));
    }
    }
}

template <class R>
class CGAL_Triangle_2_Ray_2_pair
: public CGAL_Ray_2_Triangle_2_pair<R> {
public:
    CGAL_Triangle_2_Ray_2_pair(
            CGAL_Triangle_2<R> const *trian,
            CGAL_Ray_2<R> const *ray) :
                        CGAL_Ray_2_Triangle_2_pair<R>(ray, trian) {}
};

template <class R>
inline bool CGAL_do_intersect(
    const CGAL_Triangle_2<R> &p1,
    const CGAL_Ray_2<R> &p2)
{
    typedef CGAL_Triangle_2_Ray_2_pair<R> pair_t;
    pair_t pair(&p1, &p2);
    return pair.intersection_type() == pair_t::NO;
}

template <class R>
inline CGAL_Object
CGAL_intersection(const CGAL_Triangle_2<R> &tr, const CGAL_Ray_2<R> &ray)
{
    return CGAL_intersection(ray, tr);
}
#endif
