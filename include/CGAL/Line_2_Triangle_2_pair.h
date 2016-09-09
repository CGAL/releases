
#ifndef CGAL_LINE_2_TRIANGLE_2_PAIR_H
#define CGAL_LINE_2_TRIANGLE_2_PAIR_H

#include <CGAL/Line_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Point_2.h>

template <class R>
class CGAL_Line_2_Triangle_2_pair {
public:
    enum Intersection_results {NO, POINT, SEGMENT};
    CGAL_Line_2_Triangle_2_pair() ;
    CGAL_Line_2_Triangle_2_pair(CGAL_Line_2<R> const *line,
                            CGAL_Triangle_2<R> const *trian);
    ~CGAL_Line_2_Triangle_2_pair() {}
    Intersection_results intersection_type() const;
    void                intersection(CGAL_Point_2<R> &result) const;
    void                intersection(CGAL_Segment_2<R> &result) const;
protected:
    CGAL_Line_2<R> const*_line;
    CGAL_Triangle_2<R> const *  _trian;
    bool                    _known;
    Intersection_results     _result;
    CGAL_Point_2<R>         _intersection_point;
    CGAL_Point_2<R>         _other_point;
};


#include <CGAL/Straight_2.h>
#include <CGAL/utils.h>
#include <CGAL/number_utils.h>

template <class R>
CGAL_Line_2_Triangle_2_pair<R>::
CGAL_Line_2_Triangle_2_pair()
{
    _known = false;
    _line = 0;
    _trian = 0;
}

template <class R>
CGAL_Line_2_Triangle_2_pair<R>::
CGAL_Line_2_Triangle_2_pair(CGAL_Line_2<R> const *line,
                            CGAL_Triangle_2<R> const *trian)
{
    _known = false;
    _line = line;
    _trian = trian;
}

template <class R>
CGAL_Line_2_Triangle_2_pair<R>::Intersection_results
CGAL_Line_2_Triangle_2_pair<R>::intersection_type() const
{
    if (_known)
        return _result;
// The non const this pointer is used to cast away const.
    CGAL_Line_2_Triangle_2_pair<R> *ncthis =
                (CGAL_Line_2_Triangle_2_pair<R> *) this;
    ncthis->_known = true;
    CGAL__Straight_2<R> straight(*_line);
CGAL_Line_2<R> l(_trian->vertex(0), _trian->vertex(1));
if (l.where_is(_trian->vertex(2)) == CGAL_LEFT) {
//    if (_trian->is_counterclockwise()) {
        straight.cut_right_off(
            CGAL_Line_2<R>(_trian->vertex(0), _trian->vertex(1)));
        straight.cut_right_off(
            CGAL_Line_2<R>(_trian->vertex(1), _trian->vertex(2)));
        straight.cut_right_off(
            CGAL_Line_2<R>(_trian->vertex(2), _trian->vertex(0)));
    } else {
        straight.cut_right_off(
            CGAL_Line_2<R>(_trian->vertex(2), _trian->vertex(1)));
        straight.cut_right_off(
            CGAL_Line_2<R>(_trian->vertex(1), _trian->vertex(0)));
        straight.cut_right_off(
            CGAL_Line_2<R>(_trian->vertex(0), _trian->vertex(2)));
    }
    switch (straight.current_state()) {
    case CGAL__Straight_2<R>::EMPTY:
        ncthis->_result = NO;
        return _result;
    case CGAL__Straight_2<R>::POINT: {
        straight.current(ncthis->_intersection_point);
        ncthis->_result = POINT;
        return _result;
        }
    case CGAL__Straight_2<R>::SEGMENT: {
        CGAL_Segment_2<R> seg;
        straight.current(seg);
        ncthis->_intersection_point = seg.start();
        ncthis->_other_point = seg.end();
        ncthis->_result = SEGMENT;
        return _result;
        }
    default:  // should not happen.
        CGAL_kernel_assertion(false);
        ncthis->_result = NO;
        return _result;
    }
}

template <class R>
void
CGAL_Line_2_Triangle_2_pair<R>::
intersection(CGAL_Point_2<R> &result) const
{
    CGAL_kernel_assertion(_known);
    CGAL_kernel_assertion(_result == POINT);
    result = _intersection_point;
}

template <class R>
void
CGAL_Line_2_Triangle_2_pair<R>::
intersection(CGAL_Segment_2<R> &result) const
{
    CGAL_kernel_assertion(_known);
    CGAL_kernel_assertion(_result == SEGMENT);
    result = CGAL_Segment_2<R>(_intersection_point, _other_point);
}


#endif
