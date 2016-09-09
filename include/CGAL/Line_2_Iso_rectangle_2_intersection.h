
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
// file          : include/CGAL/Line_2_Iso_rectangle_2_intersection.h
// package       : Intersections_2 (2.1.2)
// source        : intersection_2_2.fw
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : Saarbruecken
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_LINE_2_ISO_RECTANGLE_2_INTERSECTION_H
#define CGAL_LINE_2_ISO_RECTANGLE_2_INTERSECTION_H

#ifndef CGAL_LINE_2_H
#include <CGAL/Line_2.h>
#endif // CGAL_LINE_2_H
#ifndef CGAL_ISO_RECTANGLE_2_H
#include <CGAL/Iso_rectangle_2.h>
#endif // CGAL_ISO_RECTANGLE_2_H

CGAL_BEGIN_NAMESPACE

template <class R>
class Line_2_Iso_rectangle_2_pair {
public:
    enum Intersection_results {NO, POINT, SEGMENT};
    Line_2_Iso_rectangle_2_pair() ;
    Line_2_Iso_rectangle_2_pair(Line_2<R> const *pt,
                            Iso_rectangle_2<R> const *iso);
    ~Line_2_Iso_rectangle_2_pair() {}
#ifndef CGAL_CFG_RETURN_TYPE_BUG_2
  Intersection_results intersection_type() const;
#else
  Intersection_results intersection_type() const
{
    typedef Line_2<R> line_t;
    if (_known)
        return _result;
// The non const this pointer is used to cast away const.
    Line_2_Iso_rectangle_2_pair<R> *ncthis =
                (Line_2_Iso_rectangle_2_pair<R> *) this;
    ncthis->_known = true;
    typedef typename R::FT FT;
    typedef typename R::RT RT;
    bool all_values = true;
    int i;
    for (i=0; i< _ref_point.dimension(); i++) {
        if (_dir.homogeneous(i) == RT(0)) {
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
            if (_dir.homogeneous(i) > RT(0)) {
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

#endif // CGAL_CFG_RETURN_TYPE_BUG_2
    bool                intersection(Point_2<R> &result) const;
    bool                intersection(Segment_2<R> &result) const;
protected:
    Point_2<R>             _ref_point;
    Vector_2<R>            _dir;
    Point_2<R>             _isomin;
    Point_2<R>             _isomax;
    bool                        _known;
    Intersection_results        _result;
    typename R::FT              _min, _max;
};

template <class R>
inline bool do_intersect(
    const Line_2<R> &p1,
    const Iso_rectangle_2<R> &p2)
{
    typedef Line_2_Iso_rectangle_2_pair<R> pair_t;
    pair_t pair(&p1, &p2);
    return pair.intersection_type() != pair_t::NO;
}

CGAL_END_NAMESPACE



#ifndef CGAL_LINE_2_H
#include <CGAL/Line_2.h>
#endif // CGAL_LINE_2_H
#ifndef CGAL_UTILS_H
#include <CGAL/utils.h>
#endif // CGAL_UTILS_H
#ifndef CGAL_NUMBER_UTILS_H
#include <CGAL/number_utils.h>
#endif // CGAL_NUMBER_UTILS_H

CGAL_BEGIN_NAMESPACE

template <class R>
Line_2_Iso_rectangle_2_pair<R>::
Line_2_Iso_rectangle_2_pair()
{
    _known = false;
}

template <class R>
Line_2_Iso_rectangle_2_pair<R>::
Line_2_Iso_rectangle_2_pair(Line_2<R> const *line,
                            Iso_rectangle_2<R> const *iso)
{
    _known = false;
    _ref_point = line->point();
    _dir = line->direction().vector();
    _isomin = iso->min();
    _isomax = iso->max();
}

#ifndef CGAL_CFG_RETURN_TYPE_BUG_2
template <class R>
Line_2_Iso_rectangle_2_pair<R>::Intersection_results
Line_2_Iso_rectangle_2_pair<R>::intersection_type() const
{
    typedef Line_2<R> line_t;
    if (_known)
        return _result;
// The non const this pointer is used to cast away const.
    Line_2_Iso_rectangle_2_pair<R> *ncthis =
                (Line_2_Iso_rectangle_2_pair<R> *) this;
    ncthis->_known = true;
    typedef typename R::FT FT;
    typedef typename R::RT RT;
    bool all_values = true;
    int i;
    for (i=0; i< _ref_point.dimension(); i++) {
        if (_dir.homogeneous(i) == RT(0)) {
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
            if (_dir.homogeneous(i) > RT(0)) {
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
Line_2_Iso_rectangle_2_pair<R>::
intersection(Point_2<R> &result) const
{
    if (!_known)
        intersection_type();
    if (_result != POINT)
        return false;
    result = _ref_point + _dir * _min;
    return true;
}

template <class R>
bool
Line_2_Iso_rectangle_2_pair<R>::
intersection(Segment_2<R> &result) const
{
    if (!_known)
        intersection_type();
    if (_result != SEGMENT)
        return false;
    result = Segment_2<R>(_ref_point + _dir*_min, _ref_point + _dir*_max);
    return true;
}

CGAL_END_NAMESPACE



#ifndef CGAL_OBJECT_H
#include <CGAL/Object.h>
#endif // CGAL_OBJECT_H

CGAL_BEGIN_NAMESPACE

template <class R>
Object
intersection(const Line_2<R> &line, const Iso_rectangle_2<R>&iso)
{
    typedef Line_2_Iso_rectangle_2_pair<R> is_t;
    is_t ispair(&line, &iso);
    switch (ispair.intersection_type()) {
    case is_t::NO:
    default:
        return Object();
    case is_t::POINT: {
        Point_2<R> ipt;
        ispair.intersection(ipt);
        return Object(new Wrapper< Point_2<R> >(ipt));
    }
    case is_t::SEGMENT: {
        Segment_2<R> iseg;
        ispair.intersection(iseg);
        return Object(new Wrapper< Segment_2<R> >(iseg));
    }
    }
}

template <class R>
class Iso_rectangle_2_Line_2_pair
: public Line_2_Iso_rectangle_2_pair<R> {
public:
    Iso_rectangle_2_Line_2_pair(
            Iso_rectangle_2<R> const *iso,
            Line_2<R> const *line) :
                        Line_2_Iso_rectangle_2_pair<R>(line, iso) {}
};

template <class R>
inline bool do_intersect(
    const Iso_rectangle_2<R> &p1,
    const Line_2<R> &p2)
{
    typedef Iso_rectangle_2_Line_2_pair<R> pair_t;
    pair_t pair(&p1, &p2);
    return pair.intersection_type() != pair_t::NO;
}

template <class R>
inline Object
intersection(const Iso_rectangle_2<R>&iso, const Line_2<R>&line)
{
    return intersection(line, iso);
}

CGAL_END_NAMESPACE

#endif
