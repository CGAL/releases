// ============================================================================
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
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/Ray_2_Bbox_2_intersection.h
// author(s)     : Geert-Jan Giezeman
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


#ifndef CGAL_RAY_2_BBOX_2_INTERSECTION_H
#define CGAL_RAY_2_BBOX_2_INTERSECTION_H

#ifndef CGAL_BBOX_2_H
#include <CGAL/Bbox_2.h>
#endif // CGAL_BBOX_2_H
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
class CGAL_Ray_2_Bbox_2_pair {
public:
    typedef CGAL_Cartesian<double> Rcart;
    enum Intersection_results {NO, POINT, SEGMENT};
    CGAL_Ray_2_Bbox_2_pair() ;
    CGAL_Ray_2_Bbox_2_pair(CGAL_Ray_2<R> const *ray, CGAL_Bbox_2 const *box) ;

#ifndef CGAL_CFG_RETURN_TYPE_BUG_2
  Intersection_results intersection_type() const;

#else
  Intersection_results intersection_type() const
{
    if (_known)
        return _result;
    CGAL_Ray_2_Bbox_2_pair<R> *ncthis = (CGAL_Ray_2_Bbox_2_pair<R> *) this;
    ncthis->_known = true;
    bool to_infinity = true;
// first on x value
    if (_dir.x() == 0.0) {
        if (_ref_point.x() < _box->xmin()) {
            ncthis->_result = NO;
            return _result;
        }
        if (_ref_point.x() > _box->xmax()) {
            ncthis->_result = NO;
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
            ncthis->_min = newmin;
        if (to_infinity) {
            ncthis->_max = newmax;
        } else {
            if (newmax < _max)
                ncthis->_max = newmax;
        }
        if (_max < _min){
            ncthis->_result = NO;
            return _result;
        }
        to_infinity = false;
    }
// now on y value
    if (_dir.y() == 0.0) {
        if (_ref_point.y() < _box->ymin()) {
            ncthis->_result = NO;
            return _result;
        }
        if (_ref_point.y() > _box->ymax()) {
            ncthis->_result = NO;
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
            ncthis->_min = newmin;
        if (to_infinity) {
            ncthis->_max = newmax;
        } else {
            if (newmax < _max)
                ncthis->_max = newmax;
        }
        if (_max < _min) {
            ncthis->_result = NO;
            return _result;
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

    bool                       intersection(
                                    CGAL_Point_2< Rcart > &result) const;
    bool                       intersection(
                                    CGAL_Segment_2< Rcart > &result) const;
protected:
    CGAL_Ray_2< Rcart >        _ray;
    CGAL_Bbox_2 const *        _box;
    bool                       _known;
    Intersection_results       _result;
    CGAL_Point_2< Rcart >      _ref_point;
    CGAL_Vector_2< Rcart >     _dir;
    double                     _min,
                               _max;
};

template <class R>
inline bool CGAL_do_intersect(
    const CGAL_Ray_2<R> &ray,
    const CGAL_Bbox_2 &box)
{
    typedef CGAL_Ray_2_Bbox_2_pair<R> pair_t;
    pair_t pair(&ray, &box);
    return pair.intersection_type() != pair_t::NO;
}



template <class R>
CGAL_Ray_2_Bbox_2_pair<R>::CGAL_Ray_2_Bbox_2_pair()
{
    _known = false;
    _box = 0;
}

template <class R>
CGAL_Ray_2_Bbox_2_pair<R>::
CGAL_Ray_2_Bbox_2_pair(CGAL_Ray_2<R> const *ray, CGAL_Bbox_2 const *box)
{
    _known = false;
    _box = box;
// convert the ray to a ray parametrised by doubles.
    CGAL_Point_2<R> const &start(ray->start());
    CGAL_Vector_2<R> const &dir(ray->direction().vector());
    _ref_point = CGAL_Point_2< Rcart >
                ( CGAL_to_double(start.x()), CGAL_to_double(start.y()));
    double dx = CGAL_to_double(dir.x());
    double dy = CGAL_to_double(dir.y());
    _dir = CGAL_Vector_2< Rcart > (dx, dy);
    _min = 0;
}

#ifndef CGAL_CFG_RETURN_TYPE_BUG_2
template <class R>
CGAL_Ray_2_Bbox_2_pair<R>::Intersection_results
CGAL_Ray_2_Bbox_2_pair<R>::intersection_type() const
{
    if (_known)
        return _result;
    CGAL_Ray_2_Bbox_2_pair<R> *ncthis = (CGAL_Ray_2_Bbox_2_pair<R> *) this;
    ncthis->_known = true;
    bool to_infinity = true;
// first on x value
    if (_dir.x() == 0.0) {
        if (_ref_point.x() < _box->xmin()) {
            ncthis->_result = NO;
            return _result;
        }
        if (_ref_point.x() > _box->xmax()) {
            ncthis->_result = NO;
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
            ncthis->_min = newmin;
        if (to_infinity) {
            ncthis->_max = newmax;
        } else {
            if (newmax < _max)
                ncthis->_max = newmax;
        }
        if (_max < _min){
            ncthis->_result = NO;
            return _result;
        }
        to_infinity = false;
    }
// now on y value
    if (_dir.y() == 0.0) {
        if (_ref_point.y() < _box->ymin()) {
            ncthis->_result = NO;
            return _result;
        }
        if (_ref_point.y() > _box->ymax()) {
            ncthis->_result = NO;
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
            ncthis->_min = newmin;
        if (to_infinity) {
            ncthis->_max = newmax;
        } else {
            if (newmax < _max)
                ncthis->_max = newmax;
        }
        if (_max < _min) {
            ncthis->_result = NO;
            return _result;
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
bool CGAL_Ray_2_Bbox_2_pair<R>::
intersection(CGAL_Segment_2< CGAL_Cartesian<double> > &seg) const
{
    if (!_known)
        intersection_type();
    if (_result != SEGMENT)
        return false;
    CGAL_Point_2< Rcart > p1(_ref_point + _min*_dir);
    CGAL_Point_2< Rcart > p2(_ref_point + _max*_dir);
    seg = CGAL_Segment_2< Rcart >(p1, p2);
    return true;
}

template <class R>
bool CGAL_Ray_2_Bbox_2_pair<R>::
intersection(CGAL_Point_2< CGAL_Cartesian<double> > &pt) const
{
    if (!_known)
        intersection_type();
    if (_result != POINT)
        return false;
    pt = CGAL_Point_2< Rcart >(_ref_point + _min*_dir);
    return true;
}


template <class R>
class CGAL_Bbox_2_Ray_2_pair: public CGAL_Ray_2_Bbox_2_pair<R> {
public:
    CGAL_Bbox_2_Ray_2_pair() {}
    CGAL_Bbox_2_Ray_2_pair(CGAL_Bbox_2 const *box, CGAL_Ray_2<R> const *ray)
                :CGAL_Ray_2_Bbox_2_pair<R> (ray, box){}
};

template <class R>
inline bool CGAL_do_intersect(
    const CGAL_Bbox_2 &box,
    const CGAL_Ray_2<R> &ray)
{
    typedef CGAL_Bbox_2_Ray_2_pair<R> pair_t;
    pair_t pair(&box, &ray);
    return pair.intersection_type() != pair_t::NO;
}


#endif
