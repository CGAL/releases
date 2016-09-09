
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

#ifndef CGAL_SEGMENT_2_SEGMENT_2_INTERSECTION_H
#define CGAL_SEGMENT_2_SEGMENT_2_INTERSECTION_H

#include <CGAL/Segment_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/utils.h>
#include <CGAL/number_utils.h>

template <class R>
class CGAL_Segment_2_Segment_2_pair {
public:
    enum Intersection_results {NO, POINT, SEGMENT};
    CGAL_Segment_2_Segment_2_pair() ;
    CGAL_Segment_2_Segment_2_pair(CGAL_Segment_2<R> const *seg1,
                            CGAL_Segment_2<R> const *seg2);
    ~CGAL_Segment_2_Segment_2_pair() {}

#ifndef CGAL_WORKAROUND_005
    Intersection_results intersection_type() const;
#else
    Intersection_results intersection_type() const
{
    if (_known)
        return _result;
    // The non const this pointer is used to cast away const.
    CGAL_Segment_2_Segment_2_pair<R> *ncthis =
                (CGAL_Segment_2_Segment_2_pair<R> *) this;
    ncthis->_known = true;
    if (!CGAL_do_overlap(_seg1->bbox(), _seg2->bbox())) {
        ncthis->_result = NO;
        return _result;
    }
    CGAL_Line_2<R> const &l1 = _seg1->supporting_line();
    CGAL_Line_2<R> const &l2 = _seg2->supporting_line();
    CGAL_Line_2_Line_2_pair<R> linepair(&l1, &l2);
    switch ( linepair.intersection_type()) {
    case CGAL_Line_2_Line_2_pair<R>::NO:
        ncthis->_result = NO;
        break;
    case CGAL_Line_2_Line_2_pair<R>::POINT:
        linepair.intersection(ncthis->_intersection_point);
        ncthis->_result = (_seg1->collinear_has_on(_intersection_point)
            && _seg2->collinear_has_on(_intersection_point)) ? POINT : NO;
        break;
    case CGAL_Line_2_Line_2_pair<R>::LINE:
        {
        typedef R::RT RT;
        CGAL_Point_2<R> const &start1 = _seg1->start();
        CGAL_Point_2<R> const &end1   = _seg1->end();
        CGAL_Point_2<R> const &start2 = _seg2->start();
        CGAL_Point_2<R> const &end2   = _seg2->end();
        CGAL_Vector_2<R> diff1 = end1-start1;
        CGAL_Point_2<R> const *minpt;
        CGAL_Point_2<R> const *maxpt;
        if (CGAL_abs(diff1.x()) > CGAL_abs(diff1.y())) {
            if (start1.x() < end1.x()) {
                minpt = &start1;
                maxpt = &end1;
            } else {
                minpt = &end1;
                maxpt = &start1;
            }
            if (start2.x() < end2.x()) {
                if (start2.x() > minpt->x()) {
                    minpt = &start2;
                }
                if (end2.x() < maxpt->x()) {
                    maxpt = &end2;
                }
            } else {
                if (end2.x() > minpt->x()) {
                    minpt = &end2;
                }
                if (start2.x() < maxpt->x()) {
                    maxpt = &start2;
                }
            }
            if (maxpt->x() < minpt->x()) {
                ncthis->_result = NO;
                return _result;
            }
            if (maxpt->x() == minpt->x()) {
                ncthis->_intersection_point = *minpt;
                ncthis->_result = POINT;
                return _result;
            }
            ncthis->_intersection_point = *minpt;
            ncthis->_other_point = *maxpt;
            ncthis->_result = SEGMENT;
            return _result; 
        } else {
            if (start1.y() < end1.y()) {
                minpt = &start1;
                maxpt = &end1;
            } else {
                minpt = &end1;
                maxpt = &start1;
            }
            if (start2.y() < end2.y()) {
                if (start2.y() > minpt->y()) {
                    minpt = &start2;
                }
                if (end2.y() < maxpt->y()) {
                    maxpt = &end2;
                }
            } else {
                if (end2.y() > minpt->y()) {
                    minpt = &end2;
                }
                if (start2.y() < maxpt->y()) {
                    maxpt = &start2;
                }
            }
            if (maxpt->y() < minpt->y()) {
                ncthis->_result = NO;
                return _result;
            }
            if (maxpt->y() == minpt->y()) {
                ncthis->_intersection_point = *minpt;
                ncthis->_result = POINT;
                return _result;
            }
            ncthis->_intersection_point = *minpt;
            ncthis->_other_point = *maxpt;
            ncthis->_result = SEGMENT;
            return _result; 
        }
        } 
    }
    return _result;
}

#endif // CGAL_WORKAROUND_005
    bool                intersection(CGAL_Point_2<R> &result) const;
    bool                intersection(CGAL_Segment_2<R> &result) const;
protected:
    CGAL_Segment_2<R> const*   _seg1;
    CGAL_Segment_2<R> const *  _seg2;
    bool                       _known;
    Intersection_results       _result;
    CGAL_Point_2<R>            _intersection_point, _other_point;
};

template <class R>
inline bool CGAL_do_intersect(
    const CGAL_Segment_2<R> &p1,
    const CGAL_Segment_2<R> &p2)
{
    typedef CGAL_Segment_2_Segment_2_pair<R> pair_t;
    pair_t pair(&p1, &p2);
    return pair.intersection_type() == pair_t::NO;
}


#include <CGAL/Line_2.h>
#include <CGAL/Line_2_Line_2_intersection.h>

template <class R>
CGAL_Segment_2_Segment_2_pair<R>::CGAL_Segment_2_Segment_2_pair()
{
    _seg1 = 0;
    _seg2 = 0;
    _known = false;
}

template <class R>
CGAL_Segment_2_Segment_2_pair<R>::CGAL_Segment_2_Segment_2_pair(
    CGAL_Segment_2<R> const *seg1, CGAL_Segment_2<R> const *seg2)
{
    _seg1 = seg1;
    _seg2 = seg2;
    _known = false;
}

#ifndef CGAL_WORKAROUND_005
template <class R>
CGAL_Segment_2_Segment_2_pair<R>::Intersection_results
CGAL_Segment_2_Segment_2_pair<R>::intersection_type() const
{
    if (_known)
        return _result;
    // The non const this pointer is used to cast away const.
    CGAL_Segment_2_Segment_2_pair<R> *ncthis =
                (CGAL_Segment_2_Segment_2_pair<R> *) this;
    ncthis->_known = true;
    if (!CGAL_do_overlap(_seg1->bbox(), _seg2->bbox())) {
        ncthis->_result = NO;
        return _result;
    }
    CGAL_Line_2<R> const &l1 = _seg1->supporting_line();
    CGAL_Line_2<R> const &l2 = _seg2->supporting_line();
    CGAL_Line_2_Line_2_pair<R> linepair(&l1, &l2);
    switch ( linepair.intersection_type()) {
    case CGAL_Line_2_Line_2_pair<R>::NO:
        ncthis->_result = NO;
        break;
    case CGAL_Line_2_Line_2_pair<R>::POINT:
        linepair.intersection(ncthis->_intersection_point);
        ncthis->_result = (_seg1->collinear_has_on(_intersection_point)
            && _seg2->collinear_has_on(_intersection_point)) ? POINT : NO;
        break;
    case CGAL_Line_2_Line_2_pair<R>::LINE:
        {
        typedef R::RT RT;
        CGAL_Point_2<R> const &start1 = _seg1->start();
        CGAL_Point_2<R> const &end1   = _seg1->end();
        CGAL_Point_2<R> const &start2 = _seg2->start();
        CGAL_Point_2<R> const &end2   = _seg2->end();
        CGAL_Vector_2<R> diff1 = end1-start1;
        CGAL_Point_2<R> const *minpt;
        CGAL_Point_2<R> const *maxpt;
        if (CGAL_abs(diff1.x()) > CGAL_abs(diff1.y())) {
            if (start1.x() < end1.x()) {
                minpt = &start1;
                maxpt = &end1;
            } else {
                minpt = &end1;
                maxpt = &start1;
            }
            if (start2.x() < end2.x()) {
                if (start2.x() > minpt->x()) {
                    minpt = &start2;
                }
                if (end2.x() < maxpt->x()) {
                    maxpt = &end2;
                }
            } else {
                if (end2.x() > minpt->x()) {
                    minpt = &end2;
                }
                if (start2.x() < maxpt->x()) {
                    maxpt = &start2;
                }
            }
            if (maxpt->x() < minpt->x()) {
                ncthis->_result = NO;
                return _result;
            }
            if (maxpt->x() == minpt->x()) {
                ncthis->_intersection_point = *minpt;
                ncthis->_result = POINT;
                return _result;
            }
            ncthis->_intersection_point = *minpt;
            ncthis->_other_point = *maxpt;
            ncthis->_result = SEGMENT;
            return _result; 
        } else {
            if (start1.y() < end1.y()) {
                minpt = &start1;
                maxpt = &end1;
            } else {
                minpt = &end1;
                maxpt = &start1;
            }
            if (start2.y() < end2.y()) {
                if (start2.y() > minpt->y()) {
                    minpt = &start2;
                }
                if (end2.y() < maxpt->y()) {
                    maxpt = &end2;
                }
            } else {
                if (end2.y() > minpt->y()) {
                    minpt = &end2;
                }
                if (start2.y() < maxpt->y()) {
                    maxpt = &start2;
                }
            }
            if (maxpt->y() < minpt->y()) {
                ncthis->_result = NO;
                return _result;
            }
            if (maxpt->y() == minpt->y()) {
                ncthis->_intersection_point = *minpt;
                ncthis->_result = POINT;
                return _result;
            }
            ncthis->_intersection_point = *minpt;
            ncthis->_other_point = *maxpt;
            ncthis->_result = SEGMENT;
            return _result; 
        }
        } 
    }
    return _result;
}

#endif // CGAL_WORKAROUND_005

template <class R>
bool
CGAL_Segment_2_Segment_2_pair<R>::intersection(CGAL_Point_2<R> &result) const
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
CGAL_Segment_2_Segment_2_pair<R>::intersection(CGAL_Segment_2<R> &result) const
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
CGAL_intersection(const CGAL_Segment_2<R> &seg1, const CGAL_Segment_2<R>&seg2)
{
    typedef CGAL_Segment_2_Segment_2_pair<R> is_t;
    is_t ispair(&seg1, &seg2);
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

#endif
