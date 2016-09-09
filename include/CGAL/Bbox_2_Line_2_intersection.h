
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
// file          : include/CGAL/Bbox_2_Line_2_intersection.h
// package       : Intersections_2 (2.1.2)
// source        : intersection_2_1.fw
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : MPI, Saarbruecken
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_BBOX_2_LINE_2_INTERSECTION_H
#define CGAL_BBOX_2_LINE_2_INTERSECTION_H

#ifndef CGAL_BBOX_2_H
#include <CGAL/Bbox_2.h>
#endif // CGAL_BBOX_2_H
#ifndef CGAL_LINE_2_H
#include <CGAL/Line_2.h>
#endif // CGAL_LINE_2_H
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

CGAL_BEGIN_NAMESPACE

template <class R>
class Bbox_2_Line_2_pair {
public:
    typedef Cartesian<double> Rcart;
    enum Intersection_results {NO, POINT, SEGMENT};
    Bbox_2_Line_2_pair() ;
    Bbox_2_Line_2_pair(Bbox_2 const *bbox,
                            Line_2<R> const *line);
    ~Bbox_2_Line_2_pair() {}

#ifndef CGAL_CFG_RETURN_TYPE_BUG_2
  Intersection_results intersection_type() const;

#else

  Intersection_results intersection_type() const
{
    if (_known)
        return _result;
    // The non const this pointer is used to cast away const.
    Bbox_2_Line_2_pair<R> *ncthis = (Bbox_2_Line_2_pair<R> *) this;
    ncthis->_known = true;
    const Point_2< Cartesian<double> > &ref_point = _line.point();
    const Vector_2< Cartesian<double> > &dir =
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

#endif // CGAL_CFG_RETURN_TYPE_BUG_2

    bool intersection(Point_2< Rcart > &result) const;
    bool intersection(Segment_2< Rcart > &result) const;
protected:
    Bbox_2 const *      _bbox;
    Line_2< Rcart > _line;
    bool                     _known;
    Intersection_results     _result;
    double                   _min, _max;
};

template <class R>
inline bool do_intersect(
    const Bbox_2 &box,
    const Line_2<R> &line)
{
    typedef Bbox_2_Line_2_pair<R> pair_t;
    pair_t pair(&box, &line);
    return pair.intersection_type() != pair_t::NO;
}

CGAL_END_NAMESPACE



CGAL_BEGIN_NAMESPACE

template <class R>
Bbox_2_Line_2_pair<R>::Bbox_2_Line_2_pair()
{
    _bbox = 0;
    _known = false;
}

template <class R>
Bbox_2_Line_2_pair<R>::Bbox_2_Line_2_pair(
    Bbox_2 const *bbox, Line_2<R> const *line)
{
    _bbox = bbox;
    _line = Line_2< Rcart >(to_double(line->a()),
            to_double(line->b()), to_double(line->c()));
    _known = false;
}

#ifndef CGAL_CFG_RETURN_TYPE_BUG_2
template <class R>
Bbox_2_Line_2_pair<R>::Intersection_results
Bbox_2_Line_2_pair<R>::intersection_type() const
{
    if (_known)
        return _result;
    // The non const this pointer is used to cast away const.
    Bbox_2_Line_2_pair<R> *ncthis = (Bbox_2_Line_2_pair<R> *) this;
    ncthis->_known = true;
    const Point_2< Cartesian<double> > &ref_point = _line.point();
    const Vector_2< Cartesian<double> > &dir =
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

#endif // CGAL_CFG_RETURN_TYPE_BUG_2

template <class R>
bool
Bbox_2_Line_2_pair<R>::intersection(
    Segment_2< Cartesian<double> > &seg) const
{
    if (!_known)
        intersection_type();
    if (_result != SEGMENT)
        return false;
    Point_2< Cartesian<double> > p1(_line.point()
                + _min*_line.direction().vector());
    Point_2< Cartesian<double> > p2(_line.point()
                + _max*_line.direction().vector());
    seg = Segment_2< Cartesian<double> >(p1, p2);
    return true;
}

template <class R>
bool
Bbox_2_Line_2_pair<R>::intersection(
    Point_2< Cartesian<double> > &pt) const
{
    if (!_known)
        intersection_type();
    if (_result != POINT)
        return false;
    pt = (_line.point() + _min*_line.direction().vector());
    return true;
}

CGAL_END_NAMESPACE



CGAL_BEGIN_NAMESPACE

template <class R>
class Line_2_Bbox_2_pair: public Bbox_2_Line_2_pair<R> {
public:
    Line_2_Bbox_2_pair(
            Line_2<R> const *line,
            Bbox_2 const *bbox) :
                                Bbox_2_Line_2_pair<R>(bbox, line) {}
};

template <class R>
inline bool do_intersect(
    const Line_2<R> &line,
    const Bbox_2 &box)
{
    typedef Line_2_Bbox_2_pair<R> pair_t;
    pair_t pair(&line, &box);
    return pair.intersection_type() != pair_t::NO;
}

CGAL_END_NAMESPACE

#endif
