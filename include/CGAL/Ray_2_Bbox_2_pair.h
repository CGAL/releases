 

#ifndef CGAL_RAY_2_BBOX_2_PAIR_H
#define CGAL_RAY_2_BBOX_2_PAIR_H

#include <CGAL/cartesian.h>
#include <CGAL/Bbox_2.h>
#include <CGAL/Ray_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/utils.h>
#include <CGAL/number_utils.h>

template <class R>
class CGAL_Ray_2_Bbox_2_pair {
public:
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

    void                       intersection(
                                    CGAL_Point_2< C<double> > &result) const;
    void                       intersection(
                                    CGAL_Segment_2< C<double> > &result) const;
protected:
    CGAL_Ray_2< C<double> >    _ray;
    CGAL_Bbox_2 const *        _box;
    bool                       _known;
    Intersection_results       _result;
    CGAL_Point_2< C<double> >  _ref_point;
    CGAL_Vector_2< C<double> > _dir;
    double                     _min,
                               _max;
};

 


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
    _ref_point = CGAL_Point_2< C<double> >
                ( CGAL_to_double(start.x()), CGAL_to_double(start.y()));
//    double dx = CGAL_to_double(dir.hx())/CGAL_to_double(dir.hw());
//    double dy = CGAL_to_double(dir.hy())/CGAL_to_double(dir.hw());
    double dx = CGAL_to_double(dir.x());
    double dy = CGAL_to_double(dir.y());
    _dir = CGAL_Vector_2< C<double> > (dx, dy);
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
void CGAL_Ray_2_Bbox_2_pair<R>::
intersection(CGAL_Segment_2< C<double> > &seg) const
{
    CGAL_kernel_assertion(_known == true);
    CGAL_kernel_assertion(_result == SEGMENT);
    CGAL_Point_2< C<double> > p1(_ref_point + _min*_dir);
    CGAL_Point_2< C<double> > p2(_ref_point + _max*_dir);
    seg = CGAL_Segment_2< C<double> >(p1, p2);
}

template <class R>
void CGAL_Ray_2_Bbox_2_pair<R>::
intersection(CGAL_Point_2< C<double> > &pt) const
{
    CGAL_kernel_assertion(_known == true);
    CGAL_kernel_assertion(_result == POINT);
    pt = CGAL_Point_2< C<double> >(_ref_point + _min*_dir);
}
 


#endif
