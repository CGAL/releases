
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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/Segment_2_Segment_2_intersection.h
// package       : Intersections_2 (1.7)
// source        : intersection_2_1.fw
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : Saarbruecken
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_SEGMENT_2_SEGMENT_2_INTERSECTION_H
#define CGAL_SEGMENT_2_SEGMENT_2_INTERSECTION_H

#ifndef CGAL_SEGMENT_2_H
#include <CGAL/Segment_2.h>
#endif // CGAL_SEGMENT_2_H
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
class CGAL_Segment_2_Segment_2_pair {
public:
    enum Intersection_results {NO, POINT, SEGMENT};
    CGAL_Segment_2_Segment_2_pair() ;
    CGAL_Segment_2_Segment_2_pair(CGAL_Segment_2<R> const *seg1,
                            CGAL_Segment_2<R> const *seg2);
    ~CGAL_Segment_2_Segment_2_pair() {}

#ifndef CGAL_CFG_RETURN_TYPE_BUG_2
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
        typedef typename R::RT RT;
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

#endif // CGAL_CFG_RETURN_TYPE_BUG_2
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
    return pair.intersection_type() != pair_t::NO;
}


#ifndef CGAL_LINE_2_H
#include <CGAL/Line_2.h>
#endif // CGAL_LINE_2_H
#ifndef CGAL_LINE_2_LINE_2_INTERSECTION_H
#include <CGAL/Line_2_Line_2_intersection.h>
#endif // CGAL_LINE_2_LINE_2_INTERSECTION_H

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

#ifndef CGAL_CFG_RETURN_TYPE_BUG_2
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
        typedef typename R::RT RT;
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

#endif // CGAL_CFG_RETURN_TYPE_BUG_2

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



#ifndef CGAL_OBJECT_H
#include <CGAL/Object.h>
#endif // CGAL_OBJECT_H

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
