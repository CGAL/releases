
// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/Segment_2_Line_2_intersection.h
// package       : Intersections_2 (2.11.3)
// source        : intersection_2_1.fw
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : Saarbruecken
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================


#ifndef CGAL_SEGMENT_2_LINE_2_INTERSECTION_H
#define CGAL_SEGMENT_2_LINE_2_INTERSECTION_H

#include <CGAL/Line_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/utils.h>
#include <CGAL/number_utils.h>

CGAL_BEGIN_NAMESPACE

template <class R>
class Segment_2_Line_2_pair {
public:
    enum Intersection_results {NO, POINT, SEGMENT};
    Segment_2_Line_2_pair() ;
    Segment_2_Line_2_pair(Segment_2<R> const *seg,
                            Line_2<R> const *line);
    ~Segment_2_Line_2_pair() {}

#ifndef CGAL_CFG_RETURN_TYPE_BUG_2
    Intersection_results intersection_type() const;
#else
    Intersection_results intersection_type() const
{
    if (_known)
        return _result;
    // The non const this pointer is used to cast away const.
    _known = true;
    const Line_2<R> &l1 = _seg->supporting_line();
    Line_2_Line_2_pair<R> linepair(&l1, _line);
    switch ( linepair.intersection_type()) {
    case Line_2_Line_2_pair<R>::NO:
        _result = NO;
        break;
    case Line_2_Line_2_pair<R>::POINT:
        linepair.intersection(_intersection_point);
        _result = (_seg->collinear_has_on(_intersection_point) )
                ? POINT : NO;
        break;
    case Line_2_Line_2_pair<R>::LINE:
        _result = SEGMENT;
        break;
    }
    return _result;
}

#endif // CGAL_CFG_RETURN_TYPE_BUG_2

    bool                intersection(Point_2<R> &result) const;
    bool                intersection(Segment_2<R> &result) const;
protected:
    Segment_2<R> const*_seg;
    Line_2<R> const *  _line;
    mutable bool                    _known;
    mutable Intersection_results     _result;
    mutable Point_2<R>         _intersection_point;
};

template <class R>
inline bool do_intersect(
    const Segment_2<R> &p1,
    const Line_2<R> &p2)
{
    typedef Segment_2_Line_2_pair<R> pair_t;
    pair_t pair(&p1, &p2);
    return pair.intersection_type() != pair_t::NO;
}

CGAL_END_NAMESPACE

#include <CGAL/Object.h>

CGAL_BEGIN_NAMESPACE

template <class R>
Object
intersection(const Segment_2<R> &seg, const Line_2<R> &line)
{
    typedef Segment_2_Line_2_pair<R> is_t;
    is_t ispair(&seg, &line);
    switch (ispair.intersection_type()) {
    case is_t::NO:
    default:
        return Object();
    case is_t::POINT: {
        Point_2<R> pt;
        ispair.intersection(pt);
        return make_object(pt);
    }
    case is_t::SEGMENT:
        return make_object(seg);
    }
}

template <class R>
class Line_2_Segment_2_pair: public Segment_2_Line_2_pair<R> {
public:
    Line_2_Segment_2_pair(
            Line_2<R> const *line,
            Segment_2<R> const *seg) :
                                Segment_2_Line_2_pair<R>(seg, line) {}
};

template <class R>
inline bool do_intersect(
    const Line_2<R> &p1,
    const Segment_2<R> &p2)
{
    typedef Line_2_Segment_2_pair<R> pair_t;
    pair_t pair(&p1, &p2);
    return pair.intersection_type() != pair_t::NO;
}

template <class R>
inline Object
intersection(const Line_2<R> &line, const Segment_2<R> &seg)
{
    return intersection(seg, line);
}

CGAL_END_NAMESPACE


#include <CGAL/Line_2_Line_2_intersection.h>

CGAL_BEGIN_NAMESPACE

template <class R>
Segment_2_Line_2_pair<R>::Segment_2_Line_2_pair()
{
    _seg = 0;
    _line = 0;
    _known = false;
}

template <class R>
Segment_2_Line_2_pair<R>::Segment_2_Line_2_pair(
    Segment_2<R> const *seg, Line_2<R> const *line)
{
    _seg = seg;
    _line = line;
    _known = false;
}

#ifndef CGAL_CFG_RETURN_TYPE_BUG_2
template <class R>
typename Segment_2_Line_2_pair<R>::Intersection_results
Segment_2_Line_2_pair<R>::intersection_type() const
{
    if (_known)
        return _result;
    // The non const this pointer is used to cast away const.
    _known = true;
    const Line_2<R> &l1 = _seg->supporting_line();
    Line_2_Line_2_pair<R> linepair(&l1, _line);
    switch ( linepair.intersection_type()) {
    case Line_2_Line_2_pair<R>::NO:
        _result = NO;
        break;
    case Line_2_Line_2_pair<R>::POINT:
        linepair.intersection(_intersection_point);
        _result = (_seg->collinear_has_on(_intersection_point) )
                ? POINT : NO;
        break;
    case Line_2_Line_2_pair<R>::LINE:
        _result = SEGMENT;
        break;
    }
    return _result;
}

#endif // CGAL_CFG_RETURN_TYPE_BUG_2

template <class R>
bool
Segment_2_Line_2_pair<R>::intersection(Point_2<R> &result) const
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
Segment_2_Line_2_pair<R>::intersection(Segment_2<R> &result) const
{
    if (!_known)
        intersection_type();
    if (_result != SEGMENT)
        return false;
    result = *_seg;
    return true;
}

CGAL_END_NAMESPACE



#endif
