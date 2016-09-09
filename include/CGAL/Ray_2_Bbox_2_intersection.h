
// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/Ray_2_Bbox_2_intersection.h
// package       : Intersections_2 (2.6.3)
// source        : intersection_2_1.fw
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : Saarbruecken
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================


#ifndef CGAL_RAY_2_BBOX_2_INTERSECTION_H
#define CGAL_RAY_2_BBOX_2_INTERSECTION_H

#include <CGAL/Cartesian.h>
#include <CGAL/Bbox_2.h>
#include <CGAL/Ray_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/utils.h>
#include <CGAL/number_utils.h>

CGAL_BEGIN_NAMESPACE

template <class R>
class Ray_2_Bbox_2_pair {
public:
    typedef Cartesian<double> Rcart;
    enum Intersection_results {NO, POINT, SEGMENT};
    Ray_2_Bbox_2_pair() ;
    Ray_2_Bbox_2_pair(Ray_2<R> const *ray, Bbox_2 const *box) ;

#ifndef CGAL_CFG_RETURN_TYPE_BUG_2
  Intersection_results intersection_type() const;

#else
  Intersection_results intersection_type() const
{
    if (_known)
        return _result;
    _known = true;
    bool to_infinity = true;
// first on x value
    if (_dir.x() == 0.0) {
        if (_ref_point.x() < _box->xmin()) {
            _result = NO;
            return _result;
        }
        if (_ref_point.x() > _box->xmax()) {
            _result = NO;
            return _result;
        }
    } else {
        double newmin, newmax;
        if (_dir.x() > 0.0) {
            newmin = (_box->xmin()-_ref_point.x())/_dir.x();
            newmax = (_box->xmax()-_ref_point.x())/_dir.x();
        } else {
            newmin = (_box->xmax()-_ref_point.x())/_dir.x();
            newmax = (_box->xmin()-_ref_point.x())/_dir.x();
        }
        if (newmin > _min)
            _min = newmin;
        if (to_infinity) {
            _max = newmax;
        } else {
            if (newmax < _max)
                _max = newmax;
        }
        if (_max < _min){
            _result = NO;
            return _result;
        }
        to_infinity = false;
    }
// now on y value
    if (_dir.y() == 0.0) {
        if (_ref_point.y() < _box->ymin()) {
            _result = NO;
            return _result;
        }
        if (_ref_point.y() > _box->ymax()) {
            _result = NO;
            return _result;
        }
    } else {
        double newmin, newmax;
        if (_dir.y() > 0.0) {
            newmin = (_box->ymin()-_ref_point.y())/_dir.y();
            newmax = (_box->ymax()-_ref_point.y())/_dir.y();
        } else {
            newmin = (_box->ymax()-_ref_point.y())/_dir.y();
            newmax = (_box->ymin()-_ref_point.y())/_dir.y();
        }
        if (newmin > _min)
            _min = newmin;
        if (to_infinity) {
            _max = newmax;
        } else {
            if (newmax < _max)
                _max = newmax;
        }
        if (_max < _min) {
            _result = NO;
            return _result;
        }
        to_infinity = false;
    }
    CGAL_kernel_assertion(!to_infinity);
    if (_max == _min) {
        _result = POINT;
        return _result;
    }
    _result = SEGMENT;
    return _result;
}

#endif // CGAL_CFG_RETURN_TYPE_BUG_2

    bool                       intersection(
                                    Point_2< Rcart > &result) const;
    bool                       intersection(
                                    Segment_2< Rcart > &result) const;
protected:
    Ray_2< Rcart >        _ray;
    Bbox_2 const *        _box;
    mutable bool                       _known;
    mutable Intersection_results       _result;
    mutable Point_2< Rcart >      _ref_point;
    mutable Vector_2< Rcart >     _dir;
    mutable double                     _min,
                               _max;
};

template <class R>
inline bool do_intersect(
    const Ray_2<R> &ray,
    const Bbox_2 &box)
{
    typedef Ray_2_Bbox_2_pair<R> pair_t;
    pair_t pair(&ray, &box);
    return pair.intersection_type() != pair_t::NO;
}

CGAL_END_NAMESPACE



CGAL_BEGIN_NAMESPACE

template <class R>
Ray_2_Bbox_2_pair<R>::Ray_2_Bbox_2_pair()
{
    _known = false;
    _box = 0;
}

template <class R>
Ray_2_Bbox_2_pair<R>::
Ray_2_Bbox_2_pair(Ray_2<R> const *ray, Bbox_2 const *box)
{
    _known = false;
    _box = box;
// convert the ray to a ray parametrised by doubles.
    Point_2<R> const &start=ray->start();
    Vector_2<R> const &dir=ray->direction().to_vector();
    _ref_point = Point_2< Rcart >
                ( to_double(start.x()), to_double(start.y()));
    double dx = to_double(dir.x());
    double dy = to_double(dir.y());
    _dir = Vector_2< Rcart > (dx, dy);
    _min = 0;
}

#ifndef CGAL_CFG_RETURN_TYPE_BUG_2
template <class R>
Ray_2_Bbox_2_pair<R>::Intersection_results
Ray_2_Bbox_2_pair<R>::intersection_type() const
{
    if (_known)
        return _result;
    _known = true;
    bool to_infinity = true;
// first on x value
    if (_dir.x() == 0.0) {
        if (_ref_point.x() < _box->xmin()) {
            _result = NO;
            return _result;
        }
        if (_ref_point.x() > _box->xmax()) {
            _result = NO;
            return _result;
        }
    } else {
        double newmin, newmax;
        if (_dir.x() > 0.0) {
            newmin = (_box->xmin()-_ref_point.x())/_dir.x();
            newmax = (_box->xmax()-_ref_point.x())/_dir.x();
        } else {
            newmin = (_box->xmax()-_ref_point.x())/_dir.x();
            newmax = (_box->xmin()-_ref_point.x())/_dir.x();
        }
        if (newmin > _min)
            _min = newmin;
        if (to_infinity) {
            _max = newmax;
        } else {
            if (newmax < _max)
                _max = newmax;
        }
        if (_max < _min){
            _result = NO;
            return _result;
        }
        to_infinity = false;
    }
// now on y value
    if (_dir.y() == 0.0) {
        if (_ref_point.y() < _box->ymin()) {
            _result = NO;
            return _result;
        }
        if (_ref_point.y() > _box->ymax()) {
            _result = NO;
            return _result;
        }
    } else {
        double newmin, newmax;
        if (_dir.y() > 0.0) {
            newmin = (_box->ymin()-_ref_point.y())/_dir.y();
            newmax = (_box->ymax()-_ref_point.y())/_dir.y();
        } else {
            newmin = (_box->ymax()-_ref_point.y())/_dir.y();
            newmax = (_box->ymin()-_ref_point.y())/_dir.y();
        }
        if (newmin > _min)
            _min = newmin;
        if (to_infinity) {
            _max = newmax;
        } else {
            if (newmax < _max)
                _max = newmax;
        }
        if (_max < _min) {
            _result = NO;
            return _result;
        }
        to_infinity = false;
    }
    CGAL_kernel_assertion(!to_infinity);
    if (_max == _min) {
        _result = POINT;
        return _result;
    }
    _result = SEGMENT;
    return _result;
}

#endif // CGAL_CFG_RETURN_TYPE_BUG_2

template <class R>
bool Ray_2_Bbox_2_pair<R>::
intersection(Segment_2< Cartesian<double> > &seg) const
{
    if (!_known)
        intersection_type();
    if (_result != SEGMENT)
        return false;
    Point_2< Rcart > p1(_ref_point + _min*_dir);
    Point_2< Rcart > p2(_ref_point + _max*_dir);
    seg = Segment_2< Rcart >(p1, p2);
    return true;
}

template <class R>
bool Ray_2_Bbox_2_pair<R>::
intersection(Point_2< Cartesian<double> > &pt) const
{
    if (!_known)
        intersection_type();
    if (_result != POINT)
        return false;
    pt = Point_2< Rcart >(_ref_point + _min*_dir);
    return true;
}

CGAL_END_NAMESPACE



CGAL_BEGIN_NAMESPACE

template <class R>
class Bbox_2_Ray_2_pair: public Ray_2_Bbox_2_pair<R> {
public:
    Bbox_2_Ray_2_pair() {}
    Bbox_2_Ray_2_pair(Bbox_2 const *box, Ray_2<R> const *ray)
                :Ray_2_Bbox_2_pair<R> (ray, box){}
};

template <class R>
inline bool do_intersect(
    const Bbox_2 &box,
    const Ray_2<R> &ray)
{
    typedef Bbox_2_Ray_2_pair<R> pair_t;
    pair_t pair(&box, &ray);
    return pair.intersection_type() != pair_t::NO;
}

CGAL_END_NAMESPACE

#endif
