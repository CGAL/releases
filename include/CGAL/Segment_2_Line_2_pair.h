 

#ifndef CGAL_SEGMENT_2_LINE_2_PAIR_H
#define CGAL_SEGMENT_2_LINE_2_PAIR_H

#include <CGAL/Line_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/utils.h>
#include <CGAL/number_utils.h>

template <class R>
class CGAL_Segment_2_Line_2_pair {
public:
    enum Intersection_results {NO, POINT, SEGMENT};
    CGAL_Segment_2_Line_2_pair() ;
    CGAL_Segment_2_Line_2_pair(CGAL_Segment_2<R> const *seg,
                            CGAL_Line_2<R> const *line);
    ~CGAL_Segment_2_Line_2_pair() {}

#ifndef CGAL_WORKAROUND_005
    Intersection_results intersection_type() const;
#else
    Intersection_results intersection_type() const
 
{
    if (_known)
        return _result;
    // The non const this pointer is used to cast away const.
    CGAL_Segment_2_Line_2_pair<R> *ncthis =
            (CGAL_Segment_2_Line_2_pair<R> *) this;
    ncthis->_known = true;
    const CGAL_Line_2<R> &l1 = _seg->supporting_line();
    CGAL_Line_2_Line_2_pair<R> linepair(&l1, _line);
    switch ( linepair.intersection_type()) {
    case CGAL_Line_2_Line_2_pair<R>::NO:
        ncthis->_result = NO;
        break;
    case CGAL_Line_2_Line_2_pair<R>::POINT:
        linepair.intersection(ncthis->_intersection_point);
        ncthis->_result = (_seg->collinear_is_on(_intersection_point) )
                ? POINT : NO;
        break;
    case CGAL_Line_2_Line_2_pair<R>::LINE:
        ncthis->_result = SEGMENT;
        break;
    }
    return _result;
}
 

#endif // CGAL_WORKAROUND_005

    void                intersection(CGAL_Point_2<R> &result) const;
    void                intersection(CGAL_Segment_2<R> &result) const;
protected:
    CGAL_Segment_2<R> const*_seg;
    CGAL_Line_2<R> const *  _line;
    bool                    _known;
    Intersection_results     _result;
    CGAL_Point_2<R>         _intersection_point;
};

 

#include <CGAL/Line_2_Line_2_pair.h>

template <class R>
CGAL_Segment_2_Line_2_pair<R>::CGAL_Segment_2_Line_2_pair()
{
    _seg = 0;
    _line = 0;
    _known = false;
}

template <class R>
CGAL_Segment_2_Line_2_pair<R>::CGAL_Segment_2_Line_2_pair(
    CGAL_Segment_2<R> const *seg, CGAL_Line_2<R> const *line)
{
    _seg = seg;
    _line = line;
    _known = false;
}

#ifndef CGAL_WORKAROUND_005
template <class R>
CGAL_Segment_2_Line_2_pair<R>::Intersection_results
CGAL_Segment_2_Line_2_pair<R>::intersection_type() const
 
{
    if (_known)
        return _result;
    // The non const this pointer is used to cast away const.
    CGAL_Segment_2_Line_2_pair<R> *ncthis =
            (CGAL_Segment_2_Line_2_pair<R> *) this;
    ncthis->_known = true;
    const CGAL_Line_2<R> &l1 = _seg->supporting_line();
    CGAL_Line_2_Line_2_pair<R> linepair(&l1, _line);
    switch ( linepair.intersection_type()) {
    case CGAL_Line_2_Line_2_pair<R>::NO:
        ncthis->_result = NO;
        break;
    case CGAL_Line_2_Line_2_pair<R>::POINT:
        linepair.intersection(ncthis->_intersection_point);
        ncthis->_result = (_seg->collinear_is_on(_intersection_point) )
                ? POINT : NO;
        break;
    case CGAL_Line_2_Line_2_pair<R>::LINE:
        ncthis->_result = SEGMENT;
        break;
    }
    return _result;
}
 

#endif // CGAL_WORKAROUND_005

template <class R>
void
CGAL_Segment_2_Line_2_pair<R>::intersection(CGAL_Point_2<R> &result) const
{
    CGAL_kernel_assertion(_known);
    CGAL_kernel_assertion(_result == POINT);
    result = _intersection_point;
}

template <class R>
void
CGAL_Segment_2_Line_2_pair<R>::intersection(CGAL_Segment_2<R> &result) const
{
    CGAL_kernel_assertion(_known);
    CGAL_kernel_assertion(_result == SEGMENT);
    result = *_seg;
}
 


#endif
