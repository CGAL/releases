/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/


// Author: Geert-Jan Giezeman

#ifndef CGAL_BBOX_2_LINE_2_INTERSECTION_H
#define CGAL_BBOX_2_LINE_2_INTERSECTION_H

#include <CGAL/Bbox_2.h>
#include <CGAL/Line_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/utils.h>
#include <CGAL/number_utils.h>

template <class R>
class CGAL_Bbox_2_Line_2_pair {
public:
    typedef CGAL_Cartesian<double> Rcart;
    enum Intersection_results {NO, POINT, SEGMENT};
    CGAL_Bbox_2_Line_2_pair() ;
    CGAL_Bbox_2_Line_2_pair(CGAL_Bbox_2 const *bbox,
                            CGAL_Line_2<R> const *line);
    ~CGAL_Bbox_2_Line_2_pair() {}

#ifndef CGAL_WORKAROUND_005
  Intersection_results intersection_type() const;

#else

  Intersection_results intersection_type() const
{
    if (_known)
        return _result;
    // The non const this pointer is used to cast away const.
    CGAL_Bbox_2_Line_2_pair<R> *ncthis = (CGAL_Bbox_2_Line_2_pair<R> *) this;
    ncthis->_known = true;
    const CGAL_Point_2< CGAL_Cartesian<double> > &ref_point = _line.point();
    const CGAL_Vector_2< CGAL_Cartesian<double> > &dir =
                               _line.direction().vector();
    bool to_infinity = true;
// first on x value
    if (dir.x() == 0.0) {
        if (ref_point.x() < _bbox->xmin()) {
            ncthis->_result = NO;
            return _result;
        }
        if (ref_point.x() > _bbox->xmax()) {
            ncthis->_result = NO;
            return _result;
        }
    } else {
        double newmin, newmax;
        if (dir.x() > 0.0) {
            newmin = (_bbox->xmin()-ref_point.x())/dir.x();
            newmax = (_bbox->xmax()-ref_point.x())/dir.x();
        } else {
            newmin = (_bbox->xmax()-ref_point.x())/dir.x();
            newmax = (_bbox->xmin()-ref_point.x())/dir.x();
        }
        if (to_infinity) {
            ncthis->_min = newmin;
            ncthis->_max = newmax;
        } else {
            if (newmin > _min)
                ncthis->_min = newmin;
            if (newmax < _max)
                ncthis->_max = newmax;
            if (_max < _min) {
                ncthis->_result = NO;
                return _result;
            }
        }
        to_infinity = false;
    }
// now on y value
    if (dir.y() == 0.0) {
        if (ref_point.y() < _bbox->ymin()) {
            ncthis->_result = NO;
            return _result;
        }
        if (ref_point.y() > _bbox->ymax()) {
            ncthis->_result = NO;
            return _result;
        }
    } else {
        double newmin, newmax;
        if (dir.y() > 0.0) {
            newmin = (_bbox->ymin()-ref_point.y())/dir.y();
            newmax = (_bbox->ymax()-ref_point.y())/dir.y();
        } else {
            newmin = (_bbox->ymax()-ref_point.y())/dir.y();
            newmax = (_bbox->ymin()-ref_point.y())/dir.y();
        }
        if (to_infinity) {
            ncthis->_min = newmin;
            ncthis->_max = newmax;
        } else {
            if (newmin > _min)
                ncthis->_min = newmin;
            if (newmax < _max)
                ncthis->_max = newmax;
            if (_max < _min) {
                ncthis->_result = NO;
                return _result;
            }
        }
        to_infinity = false;
    }
    CGAL_kernel_assertion(!to_infinity);
    if (_max == _min) {
        ncthis->_result = POINT;
        return _result;
    }
    ncthis->_result = SEGMENT;
    return _result;
}

#endif // CGAL_WORKAROUND_005

    bool intersection(CGAL_Point_2< Rcart > &result) const;
    bool intersection(CGAL_Segment_2< Rcart > &result) const;
protected:
    CGAL_Bbox_2 const *      _bbox;
    CGAL_Line_2< Rcart > _line;
    bool                     _known;
    Intersection_results     _result;
    double                   _min, _max;
};

template <class R>
inline bool CGAL_do_intersect(
    const CGAL_Bbox_2 &box,
    const CGAL_Line_2<R> &line)
{
    typedef CGAL_Bbox_2_Line_2_pair<R> pair_t;
    pair_t pair(&box, &line);
    return pair.intersection_type() != pair_t::NO;
}



template <class R>
CGAL_Bbox_2_Line_2_pair<R>::CGAL_Bbox_2_Line_2_pair()
{
    _bbox = 0;
    _known = false;
}

template <class R>
CGAL_Bbox_2_Line_2_pair<R>::CGAL_Bbox_2_Line_2_pair(
    CGAL_Bbox_2 const *bbox, CGAL_Line_2<R> const *line)
{
    _bbox = bbox;
    _line = CGAL_Line_2< Rcart >(CGAL_to_double(line->a()),
            CGAL_to_double(line->b()), CGAL_to_double(line->c()));
    _known = false;
}

#ifndef CGAL_WORKAROUND_005
template <class R>
CGAL_Bbox_2_Line_2_pair<R>::Intersection_results
CGAL_Bbox_2_Line_2_pair<R>::intersection_type() const
{
    if (_known)
        return _result;
    // The non const this pointer is used to cast away const.
    CGAL_Bbox_2_Line_2_pair<R> *ncthis = (CGAL_Bbox_2_Line_2_pair<R> *) this;
    ncthis->_known = true;
    const CGAL_Point_2< CGAL_Cartesian<double> > &ref_point = _line.point();
    const CGAL_Vector_2< CGAL_Cartesian<double> > &dir =
                               _line.direction().vector();
    bool to_infinity = true;
// first on x value
    if (dir.x() == 0.0) {
        if (ref_point.x() < _bbox->xmin()) {
            ncthis->_result = NO;
            return _result;
        }
        if (ref_point.x() > _bbox->xmax()) {
            ncthis->_result = NO;
            return _result;
        }
    } else {
        double newmin, newmax;
        if (dir.x() > 0.0) {
            newmin = (_bbox->xmin()-ref_point.x())/dir.x();
            newmax = (_bbox->xmax()-ref_point.x())/dir.x();
        } else {
            newmin = (_bbox->xmax()-ref_point.x())/dir.x();
            newmax = (_bbox->xmin()-ref_point.x())/dir.x();
        }
        if (to_infinity) {
            ncthis->_min = newmin;
            ncthis->_max = newmax;
        } else {
            if (newmin > _min)
                ncthis->_min = newmin;
            if (newmax < _max)
                ncthis->_max = newmax;
            if (_max < _min) {
                ncthis->_result = NO;
                return _result;
            }
        }
        to_infinity = false;
    }
// now on y value
    if (dir.y() == 0.0) {
        if (ref_point.y() < _bbox->ymin()) {
            ncthis->_result = NO;
            return _result;
        }
        if (ref_point.y() > _bbox->ymax()) {
            ncthis->_result = NO;
            return _result;
        }
    } else {
        double newmin, newmax;
        if (dir.y() > 0.0) {
            newmin = (_bbox->ymin()-ref_point.y())/dir.y();
            newmax = (_bbox->ymax()-ref_point.y())/dir.y();
        } else {
            newmin = (_bbox->ymax()-ref_point.y())/dir.y();
            newmax = (_bbox->ymin()-ref_point.y())/dir.y();
        }
        if (to_infinity) {
            ncthis->_min = newmin;
            ncthis->_max = newmax;
        } else {
            if (newmin > _min)
                ncthis->_min = newmin;
            if (newmax < _max)
                ncthis->_max = newmax;
            if (_max < _min) {
                ncthis->_result = NO;
                return _result;
            }
        }
        to_infinity = false;
    }
    CGAL_kernel_assertion(!to_infinity);
    if (_max == _min) {
        ncthis->_result = POINT;
        return _result;
    }
    ncthis->_result = SEGMENT;
    return _result;
}

#endif // CGAL_WORKAROUND_005

template <class R>
bool
CGAL_Bbox_2_Line_2_pair<R>::intersection(
    CGAL_Segment_2< CGAL_Cartesian<double> > &seg) const
{
    if (!_known)
        intersection_type();
    if (_result != SEGMENT)
        return false;
    CGAL_Point_2< CGAL_Cartesian<double> > p1(_line.point()
                + _min*_line.direction().vector());
    CGAL_Point_2< CGAL_Cartesian<double> > p2(_line.point()
                + _max*_line.direction().vector());
    seg = CGAL_Segment_2< CGAL_Cartesian<double> >(p1, p2);
    return true;
}

template <class R>
bool
CGAL_Bbox_2_Line_2_pair<R>::intersection(
    CGAL_Point_2< CGAL_Cartesian<double> > &pt) const
{
    if (!_known)
        intersection_type();
    if (_result != POINT)
        return false;
    pt = (_line.point() + _min*_line.direction().vector());
    return true;
}


template <class R>
class CGAL_Line_2_Bbox_2_pair: public CGAL_Bbox_2_Line_2_pair<R> {
public:
    CGAL_Line_2_Bbox_2_pair(
            CGAL_Line_2<R> const *line,
            CGAL_Bbox_2 const *bbox) :
                                CGAL_Bbox_2_Line_2_pair<R>(bbox, line) {}
};

template <class R>
inline bool CGAL_do_intersect(
    const CGAL_Line_2<R> &line,
    const CGAL_Bbox_2 &box)
{
    typedef CGAL_Line_2_Bbox_2_pair<R> pair_t;
    pair_t pair(&line, &box);
    return pair.intersection_type() != pair_t::NO;
}

#endif
