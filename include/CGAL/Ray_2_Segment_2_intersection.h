
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
// file          : include/CGAL/Ray_2_Segment_2_intersection.h
// package       : Intersections_2 (1.5)
// source        : intersection_2_1.fw
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : Saarbruecken
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_RAY_2_SEGMENT_2_INTERSECTION_H
#define CGAL_RAY_2_SEGMENT_2_INTERSECTION_H

#ifndef CGAL_RAY_2_H
#include <CGAL/Ray_2.h>
#endif // CGAL_RAY_2_H
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
class CGAL_Ray_2_Segment_2_pair {
public:
    enum Intersection_results {NO, POINT, SEGMENT};
    CGAL_Ray_2_Segment_2_pair() ;
    CGAL_Ray_2_Segment_2_pair(CGAL_Ray_2<R> const *ray,
                            CGAL_Segment_2<R> const *line);
    ~CGAL_Ray_2_Segment_2_pair() {}

#ifndef CGAL_CFG_RETURN_TYPE_BUG_2
    Intersection_results intersection_type() const;
#else
    Intersection_results intersection_type() const
{
    if (_known)
        return _result;
    // The non const this pointer is used to cast away const.
    CGAL_Ray_2_Segment_2_pair<R> *ncthis =
                (CGAL_Ray_2_Segment_2_pair<R> *) this;
    ncthis->_known = true;
//    if (!CGAL_do_overlap(_ray->bbox(), _seg->bbox()))
//        return NO;
    const CGAL_Line_2<R> &l1 = _ray->supporting_line();
    const CGAL_Line_2<R> &l2 = _seg->supporting_line();
    CGAL_Line_2_Line_2_pair<R> linepair(&l1, &l2);
    switch ( linepair.intersection_type()) {
    case CGAL_Line_2_Line_2_pair<R>::NO:
        ncthis->_result = NO;
        return _result;
    case CGAL_Line_2_Line_2_pair<R>::POINT:
        linepair.intersection(ncthis->_intersection_point);
        ncthis->_result = (_ray->collinear_has_on(_intersection_point)
                && _seg->collinear_has_on(_intersection_point) )
            ? POINT :  NO;
        return _result;
    case CGAL_Line_2_Line_2_pair<R>::LINE: {
        typedef typename R::RT RT;
        const CGAL_Point_2<R> &start1 = _seg->start();
        const CGAL_Point_2<R> &end1 = _seg->end();
        const CGAL_Point_2<R> &start2 = _ray->start();
        const CGAL_Point_2<R> *minpt,  *maxpt;
        CGAL_Vector_2<R> diff1 = end1-start1;
        if (CGAL_abs(diff1.x()) > CGAL_abs(diff1.y())) {
            typedef typename R::FT FT;
            if (start1.x() < end1.x()) {
                minpt = &start1;
                maxpt = &end1;
            } else {
                minpt = &end1;
                maxpt = &start1;
            }
            if (_ray->direction().vector().x() > FT(0)) {
                if (maxpt->x() < start2.x()) {
                    ncthis->_result = NO;
                    return _result;
                }
                if (maxpt->x() == start2.x()) {
                    ncthis->_intersection_point = *maxpt;
                    ncthis->_result = POINT;
                    return _result;
                }
                if (minpt->x() < start2.x()) {
                    ncthis->_intersection_point = start2;
                    ncthis->_other_point = *maxpt;
                } else {
                    ncthis->_intersection_point = _seg->start();
                    ncthis->_other_point = _seg->end();
                }
                ncthis->_result = SEGMENT;
                return _result;
            } else {
                if (minpt->x() > start2.x()) {
                    ncthis->_result = NO;
                    return _result;
                }
                if (minpt->x() == start2.x()) {
                    ncthis->_intersection_point = *minpt;
                    ncthis->_result = POINT;
                    return _result;
                }
                if (maxpt->x() > start2.x()) {
                    ncthis->_intersection_point = start2;
                    ncthis->_other_point = *maxpt;
                } else {
                    ncthis->_intersection_point = _seg->start();
                    ncthis->_other_point = _seg->end();
                }
                ncthis->_result = SEGMENT;
                return _result;
            }
        } else {
            typedef typename R::FT FT;
            if (start1.y() < end1.y()) {
                minpt = &start1;
                maxpt = &end1;
            } else {
                minpt = &end1;
                maxpt = &start1;
            }
            if (_ray->direction().vector().y() > FT(0)) {
                if (maxpt->y() < start2.y()) {
                    ncthis->_result = NO;
                    return _result;
                }
                if (maxpt->y() == start2.y()) {
                    ncthis->_intersection_point = *maxpt;
                    ncthis->_result = POINT;
                    return _result;
                }
                if (minpt->y() < start2.y()) {
                    ncthis->_intersection_point = start2;
                    ncthis->_other_point = *maxpt;
                } else {
                    ncthis->_intersection_point = _seg->start();
                    ncthis->_other_point = _seg->end();
                }
                ncthis->_result = SEGMENT;
                return _result;
            } else {
                if (minpt->y() > start2.y()) {
                    ncthis->_result = NO;
                    return _result;
                }
                if (minpt->y() == start2.y()) {
                    ncthis->_intersection_point = *minpt;
                    ncthis->_result = POINT;
                    return _result;
                }
                if (maxpt->y() > start2.y()) {
                    ncthis->_intersection_point = start2;
                    ncthis->_other_point = *maxpt;
                } else {
                    ncthis->_intersection_point = _seg->start();
                    ncthis->_other_point = _seg->end();
                }
                ncthis->_result = SEGMENT;
                return _result;
            }
        } 
        }
    default:
        CGAL_kernel_assertion(false); // should not be reached:
        return _result;
    }

}

#endif // CGAL_CFG_RETURN_TYPE_BUG_2

    bool                intersection(CGAL_Point_2<R> &result) const;
    bool                intersection(CGAL_Segment_2<R> &result) const;
protected:
    CGAL_Ray_2<R> const *   _ray;
    CGAL_Segment_2<R> const *  _seg;
    bool                    _known;
    Intersection_results    _result;
    CGAL_Point_2<R>         _intersection_point, _other_point;
};

template <class R>
inline bool CGAL_do_intersect(
    const CGAL_Ray_2<R> &p1,
    const CGAL_Segment_2<R> &p2)
{
    typedef CGAL_Ray_2_Segment_2_pair<R> pair_t;
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
CGAL_Ray_2_Segment_2_pair<R>::CGAL_Ray_2_Segment_2_pair()
{
    _ray = 0;
    _seg = 0;
    _known = false;
}

template <class R>
CGAL_Ray_2_Segment_2_pair<R>::CGAL_Ray_2_Segment_2_pair(
    CGAL_Ray_2<R> const *ray, CGAL_Segment_2<R> const *seg)
{
    _ray = ray;
    _seg = seg;
    _known = false;
}

#ifndef CGAL_CFG_RETURN_TYPE_BUG_2
template <class R>
CGAL_Ray_2_Segment_2_pair<R>::Intersection_results
CGAL_Ray_2_Segment_2_pair<R>::intersection_type() const
{
    if (_known)
        return _result;
    // The non const this pointer is used to cast away const.
    CGAL_Ray_2_Segment_2_pair<R> *ncthis =
                (CGAL_Ray_2_Segment_2_pair<R> *) this;
    ncthis->_known = true;
//    if (!CGAL_do_overlap(_ray->bbox(), _seg->bbox()))
//        return NO;
    const CGAL_Line_2<R> &l1 = _ray->supporting_line();
    const CGAL_Line_2<R> &l2 = _seg->supporting_line();
    CGAL_Line_2_Line_2_pair<R> linepair(&l1, &l2);
    switch ( linepair.intersection_type()) {
    case CGAL_Line_2_Line_2_pair<R>::NO:
        ncthis->_result = NO;
        return _result;
    case CGAL_Line_2_Line_2_pair<R>::POINT:
        linepair.intersection(ncthis->_intersection_point);
        ncthis->_result = (_ray->collinear_has_on(_intersection_point)
                && _seg->collinear_has_on(_intersection_point) )
            ? POINT :  NO;
        return _result;
    case CGAL_Line_2_Line_2_pair<R>::LINE: {
        typedef typename R::RT RT;
        const CGAL_Point_2<R> &start1 = _seg->start();
        const CGAL_Point_2<R> &end1 = _seg->end();
        const CGAL_Point_2<R> &start2 = _ray->start();
        const CGAL_Point_2<R> *minpt,  *maxpt;
        CGAL_Vector_2<R> diff1 = end1-start1;
        if (CGAL_abs(diff1.x()) > CGAL_abs(diff1.y())) {
            typedef typename R::FT FT;
            if (start1.x() < end1.x()) {
                minpt = &start1;
                maxpt = &end1;
            } else {
                minpt = &end1;
                maxpt = &start1;
            }
            if (_ray->direction().vector().x() > FT(0)) {
                if (maxpt->x() < start2.x()) {
                    ncthis->_result = NO;
                    return _result;
                }
                if (maxpt->x() == start2.x()) {
                    ncthis->_intersection_point = *maxpt;
                    ncthis->_result = POINT;
                    return _result;
                }
                if (minpt->x() < start2.x()) {
                    ncthis->_intersection_point = start2;
                    ncthis->_other_point = *maxpt;
                } else {
                    ncthis->_intersection_point = _seg->start();
                    ncthis->_other_point = _seg->end();
                }
                ncthis->_result = SEGMENT;
                return _result;
            } else {
                if (minpt->x() > start2.x()) {
                    ncthis->_result = NO;
                    return _result;
                }
                if (minpt->x() == start2.x()) {
                    ncthis->_intersection_point = *minpt;
                    ncthis->_result = POINT;
                    return _result;
                }
                if (maxpt->x() > start2.x()) {
                    ncthis->_intersection_point = start2;
                    ncthis->_other_point = *maxpt;
                } else {
                    ncthis->_intersection_point = _seg->start();
                    ncthis->_other_point = _seg->end();
                }
                ncthis->_result = SEGMENT;
                return _result;
            }
        } else {
            typedef typename R::FT FT;
            if (start1.y() < end1.y()) {
                minpt = &start1;
                maxpt = &end1;
            } else {
                minpt = &end1;
                maxpt = &start1;
            }
            if (_ray->direction().vector().y() > FT(0)) {
                if (maxpt->y() < start2.y()) {
                    ncthis->_result = NO;
                    return _result;
                }
                if (maxpt->y() == start2.y()) {
                    ncthis->_intersection_point = *maxpt;
                    ncthis->_result = POINT;
                    return _result;
                }
                if (minpt->y() < start2.y()) {
                    ncthis->_intersection_point = start2;
                    ncthis->_other_point = *maxpt;
                } else {
                    ncthis->_intersection_point = _seg->start();
                    ncthis->_other_point = _seg->end();
                }
                ncthis->_result = SEGMENT;
                return _result;
            } else {
                if (minpt->y() > start2.y()) {
                    ncthis->_result = NO;
                    return _result;
                }
                if (minpt->y() == start2.y()) {
                    ncthis->_intersection_point = *minpt;
                    ncthis->_result = POINT;
                    return _result;
                }
                if (maxpt->y() > start2.y()) {
                    ncthis->_intersection_point = start2;
                    ncthis->_other_point = *maxpt;
                } else {
                    ncthis->_intersection_point = _seg->start();
                    ncthis->_other_point = _seg->end();
                }
                ncthis->_result = SEGMENT;
                return _result;
            }
        } 
        }
    default:
        CGAL_kernel_assertion(false); // should not be reached:
        return _result;
    }

}

#endif // CGAL_CFG_RETURN_TYPE_BUG_2

template <class R>
bool
CGAL_Ray_2_Segment_2_pair<R>::intersection(CGAL_Point_2<R> &result) const
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
CGAL_Ray_2_Segment_2_pair<R>::intersection(CGAL_Segment_2<R> &result) const
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
CGAL_intersection(const CGAL_Ray_2<R> &ray, const CGAL_Segment_2<R>&seg)
{
    typedef CGAL_Ray_2_Segment_2_pair<R> is_t;
    is_t ispair(&ray, &seg);
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
class CGAL_Segment_2_Ray_2_pair: public CGAL_Ray_2_Segment_2_pair<R> {
public:
    CGAL_Segment_2_Ray_2_pair(
            CGAL_Segment_2<R> const *seg,
            CGAL_Ray_2<R> const *ray) :
                                CGAL_Ray_2_Segment_2_pair<R>(ray, seg) {}
};

template <class R>
inline bool CGAL_do_intersect(
    const CGAL_Segment_2<R> &p1,
    const CGAL_Ray_2<R> &p2)
{
    typedef CGAL_Segment_2_Ray_2_pair<R> pair_t;
    pair_t pair(&p1, &p2);
    return pair.intersection_type() != pair_t::NO;
}

template <class R>
inline CGAL_Object
CGAL_intersection(const CGAL_Segment_2<R> &seg, const CGAL_Ray_2<R> &ray)
{
    return CGAL_intersection(ray, seg);
}

#endif
