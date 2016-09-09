
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

#ifndef CGAL_RAY_2_BBOX_2_INTERSECTION_H
#define CGAL_RAY_2_BBOX_2_INTERSECTION_H

#include <CGAL/Bbox_2.h>
#include <CGAL/Ray_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/utils.h>
#include <CGAL/number_utils.h>

template <class R>
class CGAL_Ray_2_Bbox_2_pair {
public:
    typedef CGAL_Cartesian<double> CGAL_Cartesian<double>;
    enum Intersection_results {NO, POINT, SEGMENT};
    CGAL_Ray_2_Bbox_2_pair() ;
    CGAL_Ray_2_Bbox_2_pair(CGAL_Ray_2<R> const *ray, CGAL_Bbox_2 const *box) ;

#ifndef CGAL_WORKAROUND_005
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

#endif // CGAL_WORKAROUND_005

    bool               intersection(
                         CGAL_Point_2< CGAL_Cartesian<double> > &result) const;
    bool               intersection(
                        CGAL_Segment_2< CGAL_Cartesian<double> > &result) const;
protected:
    CGAL_Ray_2< CGAL_Cartesian<double> >        _ray;
    CGAL_Bbox_2 const *        _box;
    bool                       _known;
    Intersection_results       _result;
    CGAL_Point_2< CGAL_Cartesian<double> >      _ref_point;
    CGAL_Vector_2< CGAL_Cartesian<double> >     _dir;
    double                     _min,
                               _max;
};

template <class R>
inline bool do_intersect(
    const CGAL_Ray_2<R> &ray,
    const CGAL_Bbox_2 &box)
{
    typedef CGAL_Ray_2_Bbox_2_pair<R> pair_t;
    pair_t pair(&ray, &box);
    return pair.intersection_type() == pair_t::NO;
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
    _ref_point = CGAL_Point_2< CGAL_Cartesian<double> >
                ( CGAL_to_double(start.x()), CGAL_to_double(start.y()));
//    double dx = CGAL_to_double(dir.hx())/CGAL_to_double(dir.hw());
//    double dy = CGAL_to_double(dir.hy())/CGAL_to_double(dir.hw());
    double dx = CGAL_to_double(dir.x());
    double dy = CGAL_to_double(dir.y());
    _dir = CGAL_Vector_2< CGAL_Cartesian<double> > (dx, dy);
    _min = 0;
}

#ifndef CGAL_WORKAROUND_005
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

#endif // CGAL_WORKAROUND_005

template <class R>
bool CGAL_Ray_2_Bbox_2_pair<R>::
intersection(CGAL_Segment_2< CGAL_Cartesian<double> > &seg) const
{
    if (!_known)
        intersection_type();
    if (_result != SEGMENT)
        return false;
    CGAL_Point_2< CGAL_Cartesian<double> > p1(_ref_point + _min*_dir);
    CGAL_Point_2< CGAL_Cartesian<double> > p2(_ref_point + _max*_dir);
    seg = CGAL_Segment_2< CGAL_Cartesian<double> >(p1, p2);
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
    pt = CGAL_Point_2< CGAL_Cartesian<double> >(_ref_point + _min*_dir);
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
inline bool do_intersect(
    const CGAL_Bbox_2 &box,
    const CGAL_Ray_2<R> &ray)
{
    typedef CGAL_Bbox_2_Ray_2_pair<R> pair_t;
    pair_t pair(&box, &ray);
    return pair.intersection_type() == pair_t::NO;
}


#endif
