
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

#ifndef CGAL_LINE_2_ISO_RECTANGLE_2_INTERSECTION_H
#define CGAL_LINE_2_ISO_RECTANGLE_2_INTERSECTION_H

#include <CGAL/Line_2.h>
#include <CGAL/Iso_rectangle_2.h>

template <class R>
class CGAL_Line_2_Iso_rectangle_2_pair {
public:
    enum Intersection_results {NO, POINT, SEGMENT};
    CGAL_Line_2_Iso_rectangle_2_pair() ;
    CGAL_Line_2_Iso_rectangle_2_pair(CGAL_Line_2<R> const *pt,
                            CGAL_Iso_rectangle_2<R> const *iso);
    ~CGAL_Line_2_Iso_rectangle_2_pair() {}
#ifndef CGAL_WORKAROUND_005
  Intersection_results intersection_type() const;
#else
  Intersection_results intersection_type() const
{
    typedef CGAL_Line_2<R> line_t;
    if (_known)
        return _result;
// The non const this pointer is used to cast away const.
    CGAL_Line_2_Iso_rectangle_2_pair<R> *ncthis =
                (CGAL_Line_2_Iso_rectangle_2_pair<R> *) this;
    ncthis->_known = true;
    typedef R::FT FT;
    bool all_values = true;
    int i;
    for (i=0; i< _ref_point.dimension(); i++) {
        if (_dir.homogeneous(i) == R::RT(0)) {
            if (_ref_point.cartesian(i) < _isomin.cartesian(i)) {
                ncthis->_result = NO;
                return NO;
            }
            if (_ref_point.cartesian(i) > _isomax.cartesian(i)) {
                ncthis->_result = NO;
                return NO;
            }
        } else {
            FT newmin, newmax;
            if (_dir.homogeneous(i) > R::RT(0)) {
                newmin = (_isomin.cartesian(i) - _ref_point.cartesian(i)) /
                    _dir.cartesian(i);
                newmax = (_isomax.cartesian(i) - _ref_point.cartesian(i)) /
                    _dir.cartesian(i);
            } else {
                newmin = (_isomax.cartesian(i) - _ref_point.cartesian(i)) /
                    _dir.cartesian(i);
                newmax = (_isomin.cartesian(i) - _ref_point.cartesian(i)) /
                    _dir.cartesian(i);
            }
            if (all_values) {
                ncthis->_min = newmin;
                ncthis->_max = newmax;
            } else {
                if (newmin > _min)
                    ncthis->_min = newmin;
                if (newmax < _max)
                    ncthis->_max = newmax;
                if (_max < _min) {
                    ncthis->_result = NO;
                    return NO;
                }
            }
            all_values = false;
        }
    }
    CGAL_kernel_assertion(!all_values);
    if (_max == _min) {
        ncthis->_result = POINT;
        return POINT;
    }
    ncthis->_result = SEGMENT;
    return SEGMENT;
}

#endif // CGAL_WORKAROUND_005
    bool                intersection(CGAL_Point_2<R> &result) const;
    bool                intersection(CGAL_Segment_2<R> &result) const;
protected:
    CGAL_Point_2<R>             _ref_point;
    CGAL_Vector_2<R>            _dir;
    CGAL_Point_2<R>             _isomin;
    CGAL_Point_2<R>             _isomax;
    bool                        _known;
    Intersection_results        _result;
    R::FT                       _min, _max;
};

template <class R>
inline bool CGAL_do_intersect(
    const CGAL_Line_2<R> &p1,
    const CGAL_Iso_rectangle_2<R> &p2)
{
    typedef CGAL_Line_2_Iso_rectangle_2_pair<R> pair_t;
    pair_t pair(&p1, &p2);
    return pair.intersection_type() == pair_t::NO;
}



#include <CGAL/Line_2.h>
#include <CGAL/utils.h>
#include <CGAL/number_utils.h>

template <class R>
CGAL_Line_2_Iso_rectangle_2_pair<R>::
CGAL_Line_2_Iso_rectangle_2_pair()
{
    _known = false;
}

template <class R>
CGAL_Line_2_Iso_rectangle_2_pair<R>::
CGAL_Line_2_Iso_rectangle_2_pair(CGAL_Line_2<R> const *line,
                            CGAL_Iso_rectangle_2<R> const *iso)
{
    _known = false;
    _ref_point = line->point();
    _dir = line->direction().vector();
    _isomin = iso->min();
    _isomax = iso->max();
}

#ifndef CGAL_WORKAROUND_005
template <class R>
CGAL_Line_2_Iso_rectangle_2_pair<R>::Intersection_results
CGAL_Line_2_Iso_rectangle_2_pair<R>::intersection_type() const
{
    typedef CGAL_Line_2<R> line_t;
    if (_known)
        return _result;
// The non const this pointer is used to cast away const.
    CGAL_Line_2_Iso_rectangle_2_pair<R> *ncthis =
                (CGAL_Line_2_Iso_rectangle_2_pair<R> *) this;
    ncthis->_known = true;
    typedef R::FT FT;
    bool all_values = true;
    int i;
    for (i=0; i< _ref_point.dimension(); i++) {
        if (_dir.homogeneous(i) == R::RT(0)) {
            if (_ref_point.cartesian(i) < _isomin.cartesian(i)) {
                ncthis->_result = NO;
                return NO;
            }
            if (_ref_point.cartesian(i) > _isomax.cartesian(i)) {
                ncthis->_result = NO;
                return NO;
            }
        } else {
            FT newmin, newmax;
            if (_dir.homogeneous(i) > R::RT(0)) {
                newmin = (_isomin.cartesian(i) - _ref_point.cartesian(i)) /
                    _dir.cartesian(i);
                newmax = (_isomax.cartesian(i) - _ref_point.cartesian(i)) /
                    _dir.cartesian(i);
            } else {
                newmin = (_isomax.cartesian(i) - _ref_point.cartesian(i)) /
                    _dir.cartesian(i);
                newmax = (_isomin.cartesian(i) - _ref_point.cartesian(i)) /
                    _dir.cartesian(i);
            }
            if (all_values) {
                ncthis->_min = newmin;
                ncthis->_max = newmax;
            } else {
                if (newmin > _min)
                    ncthis->_min = newmin;
                if (newmax < _max)
                    ncthis->_max = newmax;
                if (_max < _min) {
                    ncthis->_result = NO;
                    return NO;
                }
            }
            all_values = false;
        }
    }
    CGAL_kernel_assertion(!all_values);
    if (_max == _min) {
        ncthis->_result = POINT;
        return POINT;
    }
    ncthis->_result = SEGMENT;
    return SEGMENT;
}

#endif


template <class R>
bool
CGAL_Line_2_Iso_rectangle_2_pair<R>::
intersection(CGAL_Point_2<R> &result) const
{
    if (!_known)
        intersection_type();
    if (_result != POINT)
        return false;
    result = _ref_point + _min * _dir;
    return true;
}

template <class R>
bool
CGAL_Line_2_Iso_rectangle_2_pair<R>::
intersection(CGAL_Segment_2<R> &result) const
{
    if (!_known)
        intersection_type();
    if (_result != SEGMENT)
        return false;
    result = CGAL_Segment_2<R>(_ref_point + _min*_dir, _ref_point + _max*_dir);
    return true;
}


#include <CGAL/Object.h>

template <class R>
CGAL_Object
CGAL_intersection(const CGAL_Line_2<R> &line, const CGAL_Iso_rectangle_2<R>&iso)
{
    typedef CGAL_Line_2_Iso_rectangle_2_pair<R> is_t;
    is_t ispair(&line, &iso);
    switch (ispair.intersection_type()) {
    case is_t::NO:
    default:
        return CGAL_Object();
    case is_t::POINT: {
        CGAL_Point_2<R> ipt;
        ispair.intersection(ipt);
        return CGAL_Object(new CGAL_Wrapper< CGAL_Point_2<R> >(ipt));
    }
    case is_t::SEGMENT: {
        CGAL_Segment_2<R> iseg;
        ispair.intersection(iseg);
        return CGAL_Object(new CGAL_Wrapper< CGAL_Segment_2<R> >(iseg));
    }
    }
}

template <class R>
class CGAL_Iso_rectangle_2_Line_2_pair
: public CGAL_Line_2_Iso_rectangle_2_pair<R> {
public:
    CGAL_Iso_rectangle_2_Line_2_pair(
            CGAL_Iso_rectangle_2<R> const *iso,
            CGAL_Line_2<R> const *line) :
                        CGAL_Line_2_Iso_rectangle_2_pair<R>(line, iso) {}
};

template <class R>
inline bool CGAL_do_intersect(
    const CGAL_Iso_rectangle_2<R> &p1,
    const CGAL_Line_2<R> &p2)
{
    typedef CGAL_Iso_rectangle_2_Line_2_pair<R> pair_t;
    pair_t pair(&p1, &p2);
    return pair.intersection_type() == pair_t::NO;
}

template <class R>
inline CGAL_Object
CGAL_intersection(const CGAL_Iso_rectangle_2<R>&iso, const CGAL_Line_2<R>&line)
{
    return CGAL_intersection(line, iso);
}

#endif
