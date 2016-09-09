 

#ifndef CGAL_Ray_2_Ray_2_pair_H
#define CGAL_Ray_2_Ray_2_pair_H

#include <CGAL/Ray_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/utils.h>
#include <CGAL/number_utils.h>

template <class R>
class CGAL_Ray_2_Ray_2_pair {
public:
    enum Intersection_results {NO, POINT, SEGMENT, RAY};
    CGAL_Ray_2_Ray_2_pair() ;
    CGAL_Ray_2_Ray_2_pair(CGAL_Ray_2<R> const *ray1,
                            CGAL_Ray_2<R> const *ray2);
    ~CGAL_Ray_2_Ray_2_pair() {}

#ifndef CGAL_WORKAROUND_005
    Intersection_results intersection_type() const;
#else
    Intersection_results intersection_type() const
 
{
    if (_known)
        return _result;
    // The non const this pointer is used to cast away const.
    CGAL_Ray_2_Ray_2_pair<R> *ncthis =
                (CGAL_Ray_2_Ray_2_pair<R> *) this;
    ncthis->_known = true;
//    if (!do_overlap(_ray1->bbox(), _ray2->bbox()))
//        return NO;
    const CGAL_Line_2<R> &l1 = _ray1->supporting_line();
    const CGAL_Line_2<R> &l2 = _ray2->supporting_line();
    CGAL_Line_2_Line_2_pair<R> linepair(&l1, &l2);
    switch ( linepair.intersection_type()) {
    case CGAL_Line_2_Line_2_pair<R>::NO:
        ncthis->_result = NO;
        return _result;
    case CGAL_Line_2_Line_2_pair<R>::POINT:
        linepair.intersection(ncthis->_intersection_point);
        ncthis->_result = (_ray1->collinear_is_on(_intersection_point)
                && _ray2->collinear_is_on(_intersection_point) )
            ? POINT :  NO;
        return _result;
    case CGAL_Line_2_Line_2_pair<R>::LINE:
        
 
        {
        typedef R::RT RT;
        const CGAL_Vector_2<R> &dir1 = _ray1->direction().vector();
        const CGAL_Vector_2<R> &dir2 = _ray2->direction().vector();
        if (CGAL_abs(dir1.x()) > CGAL_abs(dir1.y())) {
            
 
            if (dir1.x() > 0) {
                if (dir2.x() > 0) {
                    ncthis->_intersection_point =
                            (_ray1->start().x() < _ray2->start().x())
                            ? _ray2->start() : _ray1->start();
                    ncthis->_result = RAY;
                    return _result;
                } else {
                    if (_ray1->start().x() > _ray2->start().x()) {
                        ncthis->_result = NO;
                        return _result;
                    }
                    if (_ray1->start().x() == _ray2->start().x()) {
                        ncthis->_intersection_point = _ray1->start();
                        ncthis->_result = POINT;
                        return _result;
                    }
                    ncthis->_result = SEGMENT;
                    return _result;
                }
            } else {
                if (dir2.x() < 0) {
                    ncthis->_intersection_point =
                            (_ray1->start().x() > _ray2->start().x())
                            ? _ray2->start() : _ray1->start();
                    ncthis->_result = RAY;
                    return _result;
                } else {
                    if (_ray1->start().x() < _ray2->start().x()) {
                        ncthis->_result = NO;
                        return _result;
                    }
                    if (_ray1->start().x() == _ray2->start().x()) {
                        ncthis->_intersection_point = _ray1->start();
                        ncthis->_result = POINT;
                        return _result;
                    }
                    ncthis->_result = SEGMENT;
                    return _result;
                }
            }
            
 
            
        } else {
            
 
            if (dir1.y() > 0) {
                if (dir2.y() > 0) {
                    ncthis->_intersection_point =
                            (_ray1->start().y() < _ray2->start().y())
                            ? _ray2->start() : _ray1->start();
                    ncthis->_result = RAY;
                    return _result;
                } else {
                    if (_ray1->start().y() > _ray2->start().y()) {
                        ncthis->_result = NO;
                        return _result;
                    }
                    if (_ray1->start().y() == _ray2->start().y()) {
                        ncthis->_intersection_point = _ray1->start();
                        ncthis->_result = POINT;
                        return _result;
                    }
                    ncthis->_result = SEGMENT;
                    return _result;
                }
            } else {
                if (dir2.y() < 0) {
                    ncthis->_intersection_point =
                            (_ray1->start().y() > _ray2->start().y())
                            ? _ray2->start() : _ray1->start();
                    ncthis->_result = RAY;
                    return _result;
                } else {
                    if (_ray1->start().y() < _ray2->start().y()) {
                        ncthis->_result = NO;
                        return _result;
                    }
                    if (_ray1->start().y() == _ray2->start().y()) {
                        ncthis->_intersection_point = _ray1->start();
                        ncthis->_result = POINT;
                        return _result;
                    }
                    ncthis->_result = SEGMENT;
                    return _result;
                }
            }
            
 
            
        }
        } 
 
          
    default:
        CGAL_kernel_assertion(false); // should not be reached:
        return _result;
    }
}
 

#endif // CGAL_WORKAROUND_005

    void                intersection(CGAL_Point_2<R> &result) const;
    void                intersection(CGAL_Segment_2<R> &result) const;
    void                intersection(CGAL_Ray_2<R> &result) const;
protected:
    CGAL_Ray_2<R> const*    _ray1;
    CGAL_Ray_2<R> const *   _ray2;
    bool                    _known;
    Intersection_results    _result;
    CGAL_Point_2<R>         _intersection_point, _other_point;
};

 


#include <CGAL/Line_2.h>
#include <CGAL/Line_2_Line_2_pair.h>

template <class R>
CGAL_Ray_2_Ray_2_pair<R>::CGAL_Ray_2_Ray_2_pair()
{
    _ray1 = 0;
    _ray2 = 0;
    _known = false;
}

template <class R>
CGAL_Ray_2_Ray_2_pair<R>::CGAL_Ray_2_Ray_2_pair(
    CGAL_Ray_2<R> const *ray1, CGAL_Ray_2<R> const *ray2)
{
    _ray1 = ray1;
    _ray2 = ray2;
    _known = false;
}

#ifndef CGAL_WORKAROUND_005
template <class R>
CGAL_Ray_2_Ray_2_pair<R>::Intersection_results
CGAL_Ray_2_Ray_2_pair<R>::intersection_type() const
 
{
    if (_known)
        return _result;
    // The non const this pointer is used to cast away const.
    CGAL_Ray_2_Ray_2_pair<R> *ncthis =
                (CGAL_Ray_2_Ray_2_pair<R> *) this;
    ncthis->_known = true;
//    if (!do_overlap(_ray1->bbox(), _ray2->bbox()))
//        return NO;
    const CGAL_Line_2<R> &l1 = _ray1->supporting_line();
    const CGAL_Line_2<R> &l2 = _ray2->supporting_line();
    CGAL_Line_2_Line_2_pair<R> linepair(&l1, &l2);
    switch ( linepair.intersection_type()) {
    case CGAL_Line_2_Line_2_pair<R>::NO:
        ncthis->_result = NO;
        return _result;
    case CGAL_Line_2_Line_2_pair<R>::POINT:
        linepair.intersection(ncthis->_intersection_point);
        ncthis->_result = (_ray1->collinear_is_on(_intersection_point)
                && _ray2->collinear_is_on(_intersection_point) )
            ? POINT :  NO;
        return _result;
    case CGAL_Line_2_Line_2_pair<R>::LINE:
        
 
        {
        typedef R::RT RT;
        const CGAL_Vector_2<R> &dir1 = _ray1->direction().vector();
        const CGAL_Vector_2<R> &dir2 = _ray2->direction().vector();
        if (CGAL_abs(dir1.x()) > CGAL_abs(dir1.y())) {
            
 
            if (dir1.x() > 0) {
                if (dir2.x() > 0) {
                    ncthis->_intersection_point =
                            (_ray1->start().x() < _ray2->start().x())
                            ? _ray2->start() : _ray1->start();
                    ncthis->_result = RAY;
                    return _result;
                } else {
                    if (_ray1->start().x() > _ray2->start().x()) {
                        ncthis->_result = NO;
                        return _result;
                    }
                    if (_ray1->start().x() == _ray2->start().x()) {
                        ncthis->_intersection_point = _ray1->start();
                        ncthis->_result = POINT;
                        return _result;
                    }
                    ncthis->_result = SEGMENT;
                    return _result;
                }
            } else {
                if (dir2.x() < 0) {
                    ncthis->_intersection_point =
                            (_ray1->start().x() > _ray2->start().x())
                            ? _ray2->start() : _ray1->start();
                    ncthis->_result = RAY;
                    return _result;
                } else {
                    if (_ray1->start().x() < _ray2->start().x()) {
                        ncthis->_result = NO;
                        return _result;
                    }
                    if (_ray1->start().x() == _ray2->start().x()) {
                        ncthis->_intersection_point = _ray1->start();
                        ncthis->_result = POINT;
                        return _result;
                    }
                    ncthis->_result = SEGMENT;
                    return _result;
                }
            }
            
 
            
        } else {
            
 
            if (dir1.y() > 0) {
                if (dir2.y() > 0) {
                    ncthis->_intersection_point =
                            (_ray1->start().y() < _ray2->start().y())
                            ? _ray2->start() : _ray1->start();
                    ncthis->_result = RAY;
                    return _result;
                } else {
                    if (_ray1->start().y() > _ray2->start().y()) {
                        ncthis->_result = NO;
                        return _result;
                    }
                    if (_ray1->start().y() == _ray2->start().y()) {
                        ncthis->_intersection_point = _ray1->start();
                        ncthis->_result = POINT;
                        return _result;
                    }
                    ncthis->_result = SEGMENT;
                    return _result;
                }
            } else {
                if (dir2.y() < 0) {
                    ncthis->_intersection_point =
                            (_ray1->start().y() > _ray2->start().y())
                            ? _ray2->start() : _ray1->start();
                    ncthis->_result = RAY;
                    return _result;
                } else {
                    if (_ray1->start().y() < _ray2->start().y()) {
                        ncthis->_result = NO;
                        return _result;
                    }
                    if (_ray1->start().y() == _ray2->start().y()) {
                        ncthis->_intersection_point = _ray1->start();
                        ncthis->_result = POINT;
                        return _result;
                    }
                    ncthis->_result = SEGMENT;
                    return _result;
                }
            }
            
 
            
        }
        } 
 
          
    default:
        CGAL_kernel_assertion(false); // should not be reached:
        return _result;
    }
}
 

#endif // CGAL_WORKAROUND_005

template <class R>
void
CGAL_Ray_2_Ray_2_pair<R>::intersection(CGAL_Point_2<R> &result) const
{
    CGAL_kernel_assertion(_known);
    CGAL_kernel_assertion(_result == POINT);
    result = _intersection_point;
}

template <class R>
void
CGAL_Ray_2_Ray_2_pair<R>::intersection(CGAL_Segment_2<R> &result) const
{
    CGAL_kernel_assertion(_known);
    CGAL_kernel_assertion(_result == RAY);
    result = CGAL_Segment_2<R>(_ray1->start(), _ray2->start());
}

template <class R>
void
CGAL_Ray_2_Ray_2_pair<R>::intersection(CGAL_Ray_2<R> &result) const
{
    CGAL_kernel_assertion(_known);
    CGAL_kernel_assertion(_result == RAY);
    result = CGAL_Ray_2<R>(_intersection_point, _ray1->direction());
}

 


#endif
