 

#ifndef CGAL_SEGMENT_2_SEGMENT_2_PAIR_H
#define CGAL_SEGMENT_2_SEGMENT_2_PAIR_H

#include <CGAL/Segment_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/utils.h>
#include <CGAL/number_utils.h>

template <class R>
class CGAL_Segment_2_Segment_2_pair {
public:
    enum Intersection_results {NO, POINT, SEGMENT};
    CGAL_Segment_2_Segment_2_pair() ;
    CGAL_Segment_2_Segment_2_pair(CGAL_Segment_2<R> const *seg1,
                            CGAL_Segment_2<R> const *seg2);
    ~CGAL_Segment_2_Segment_2_pair() {}

#ifndef CGAL_WORKAROUND_005
    Intersection_results intersection_type() const;
#else
    Intersection_results intersection_type() const
 
{
    if (_known)
        return _result;
    // The non const this pointer is used to cast away const.
    CGAL_Segment_2_Segment_2_pair<R> *ncthis =
                (CGAL_Segment_2_Segment_2_pair<R> *) this;
    ncthis->_known = true;
    if (!do_overlap(_seg1->bbox(), _seg2->bbox())) {
        ncthis->_result = NO;
        return _result;
    }
    CGAL_Line_2<R> const &l1 = _seg1->supporting_line();
    CGAL_Line_2<R> const &l2 = _seg2->supporting_line();
    CGAL_Line_2_Line_2_pair<R> linepair(&l1, &l2);
    switch ( linepair.intersection_type()) {
    case CGAL_Line_2_Line_2_pair<R>::NO:
        ncthis->_result = NO;
        break;
    case CGAL_Line_2_Line_2_pair<R>::POINT:
        linepair.intersection(ncthis->_intersection_point);
        ncthis->_result = (_seg1->collinear_is_on(_intersection_point)
            && _seg2->collinear_is_on(_intersection_point)) ? POINT : NO;
        break;
    case CGAL_Line_2_Line_2_pair<R>::LINE:
        
 
        {
        typedef R::RT RT;
        CGAL_Point_2<R> const &start1 = _seg1->start();
        CGAL_Point_2<R> const &end1   = _seg1->end();
        CGAL_Point_2<R> const &start2 = _seg2->start();
        CGAL_Point_2<R> const &end2   = _seg2->end();
        CGAL_Vector_2<R> diff1 = end1-start1;
        CGAL_Point_2<R> const *minpt;
        CGAL_Point_2<R> const *maxpt;
        if (CGAL_abs(diff1.x()) > CGAL_abs(diff1.y())) {
            
 
            if (start1.x() < end1.x()) {
                minpt = &start1;
                maxpt = &end1;
            } else {
                minpt = &end1;
                maxpt = &start1;
            }
            if (start2.x() < end2.x()) {
                if (start2.x() > minpt->x()) {
                    minpt = &start2;
                }
                if (end2.x() < maxpt->x()) {
                    maxpt = &end2;
                }
            } else {
                if (end2.x() > minpt->x()) {
                    minpt = &end2;
                }
                if (start2.x() < maxpt->x()) {
                    maxpt = &start2;
                }
            }
            if (maxpt->x() < minpt->x()) {
                ncthis->_result = NO;
                return _result;
            }
            if (maxpt->x() == minpt->x()) {
                ncthis->_intersection_point = *minpt;
                ncthis->_result = POINT;
                return _result;
            }
            ncthis->_intersection_point = *minpt;
            ncthis->_other_point = *maxpt;
            ncthis->_result = SEGMENT;
            return _result; 
 
                            
        } else {
            
 
            if (start1.y() < end1.y()) {
                minpt = &start1;
                maxpt = &end1;
            } else {
                minpt = &end1;
                maxpt = &start1;
            }
            if (start2.y() < end2.y()) {
                if (start2.y() > minpt->y()) {
                    minpt = &start2;
                }
                if (end2.y() < maxpt->y()) {
                    maxpt = &end2;
                }
            } else {
                if (end2.y() > minpt->y()) {
                    minpt = &end2;
                }
                if (start2.y() < maxpt->y()) {
                    maxpt = &start2;
                }
            }
            if (maxpt->y() < minpt->y()) {
                ncthis->_result = NO;
                return _result;
            }
            if (maxpt->y() == minpt->y()) {
                ncthis->_intersection_point = *minpt;
                ncthis->_result = POINT;
                return _result;
            }
            ncthis->_intersection_point = *minpt;
            ncthis->_other_point = *maxpt;
            ncthis->_result = SEGMENT;
            return _result; 
 
                            
        }
        } 
 
          
    }
    return _result;
}
 

#endif // CGAL_WORKAROUND_005
    void                intersection(CGAL_Point_2<R> &result) const;
    void                intersection(CGAL_Segment_2<R> &result) const;
protected:
    CGAL_Segment_2<R> const*   _seg1;
    CGAL_Segment_2<R> const *  _seg2;
    bool                       _known;
    Intersection_results       _result;
    CGAL_Point_2<R>            _intersection_point, _other_point;
};

 

#include <CGAL/Line_2.h>
#include <CGAL/Line_2_Line_2_pair.h>

template <class R>
CGAL_Segment_2_Segment_2_pair<R>::CGAL_Segment_2_Segment_2_pair()
{
    _seg1 = 0;
    _seg2 = 0;
    _known = false;
}

template <class R>
CGAL_Segment_2_Segment_2_pair<R>::CGAL_Segment_2_Segment_2_pair(
    CGAL_Segment_2<R> const *seg1, CGAL_Segment_2<R> const *seg2)
{
    _seg1 = seg1;
    _seg2 = seg2;
    _known = false;
}

#ifndef CGAL_WORKAROUND_005
template <class R>
CGAL_Segment_2_Segment_2_pair<R>::Intersection_results
CGAL_Segment_2_Segment_2_pair<R>::intersection_type() const
 
{
    if (_known)
        return _result;
    // The non const this pointer is used to cast away const.
    CGAL_Segment_2_Segment_2_pair<R> *ncthis =
                (CGAL_Segment_2_Segment_2_pair<R> *) this;
    ncthis->_known = true;
    if (!do_overlap(_seg1->bbox(), _seg2->bbox())) {
        ncthis->_result = NO;
        return _result;
    }
    CGAL_Line_2<R> const &l1 = _seg1->supporting_line();
    CGAL_Line_2<R> const &l2 = _seg2->supporting_line();
    CGAL_Line_2_Line_2_pair<R> linepair(&l1, &l2);
    switch ( linepair.intersection_type()) {
    case CGAL_Line_2_Line_2_pair<R>::NO:
        ncthis->_result = NO;
        break;
    case CGAL_Line_2_Line_2_pair<R>::POINT:
        linepair.intersection(ncthis->_intersection_point);
        ncthis->_result = (_seg1->collinear_is_on(_intersection_point)
            && _seg2->collinear_is_on(_intersection_point)) ? POINT : NO;
        break;
    case CGAL_Line_2_Line_2_pair<R>::LINE:
        
 
        {
        typedef R::RT RT;
        CGAL_Point_2<R> const &start1 = _seg1->start();
        CGAL_Point_2<R> const &end1   = _seg1->end();
        CGAL_Point_2<R> const &start2 = _seg2->start();
        CGAL_Point_2<R> const &end2   = _seg2->end();
        CGAL_Vector_2<R> diff1 = end1-start1;
        CGAL_Point_2<R> const *minpt;
        CGAL_Point_2<R> const *maxpt;
        if (CGAL_abs(diff1.x()) > CGAL_abs(diff1.y())) {
            
 
            if (start1.x() < end1.x()) {
                minpt = &start1;
                maxpt = &end1;
            } else {
                minpt = &end1;
                maxpt = &start1;
            }
            if (start2.x() < end2.x()) {
                if (start2.x() > minpt->x()) {
                    minpt = &start2;
                }
                if (end2.x() < maxpt->x()) {
                    maxpt = &end2;
                }
            } else {
                if (end2.x() > minpt->x()) {
                    minpt = &end2;
                }
                if (start2.x() < maxpt->x()) {
                    maxpt = &start2;
                }
            }
            if (maxpt->x() < minpt->x()) {
                ncthis->_result = NO;
                return _result;
            }
            if (maxpt->x() == minpt->x()) {
                ncthis->_intersection_point = *minpt;
                ncthis->_result = POINT;
                return _result;
            }
            ncthis->_intersection_point = *minpt;
            ncthis->_other_point = *maxpt;
            ncthis->_result = SEGMENT;
            return _result; 
 
                            
        } else {
            
 
            if (start1.y() < end1.y()) {
                minpt = &start1;
                maxpt = &end1;
            } else {
                minpt = &end1;
                maxpt = &start1;
            }
            if (start2.y() < end2.y()) {
                if (start2.y() > minpt->y()) {
                    minpt = &start2;
                }
                if (end2.y() < maxpt->y()) {
                    maxpt = &end2;
                }
            } else {
                if (end2.y() > minpt->y()) {
                    minpt = &end2;
                }
                if (start2.y() < maxpt->y()) {
                    maxpt = &start2;
                }
            }
            if (maxpt->y() < minpt->y()) {
                ncthis->_result = NO;
                return _result;
            }
            if (maxpt->y() == minpt->y()) {
                ncthis->_intersection_point = *minpt;
                ncthis->_result = POINT;
                return _result;
            }
            ncthis->_intersection_point = *minpt;
            ncthis->_other_point = *maxpt;
            ncthis->_result = SEGMENT;
            return _result; 
 
                            
        }
        } 
 
          
    }
    return _result;
}
 

#endif // CGAL_WORKAROUND_005

template <class R>
void
CGAL_Segment_2_Segment_2_pair<R>::intersection(CGAL_Point_2<R> &result) const
{
    CGAL_kernel_assertion(_known);
    CGAL_kernel_assertion(_result == POINT);
    result = _intersection_point;
}

template <class R>
void
CGAL_Segment_2_Segment_2_pair<R>::intersection(CGAL_Segment_2<R> &result) const
{
    CGAL_kernel_assertion(_known);
    CGAL_kernel_assertion(_result == SEGMENT);
    result = CGAL_Segment_2<R>(_intersection_point, _other_point);
}

 


#endif
