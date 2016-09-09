
#ifndef CGAL_TRIANGLE_2_TRIANGLE_2_PAIR_H
#define CGAL_TRIANGLE_2_TRIANGLE_2_PAIR_H

#include <CGAL/Segment_2.h>
#include <CGAL/Triangle_2.h>

template <class R>
struct CGAL__Pointlist_2_rec {
    CGAL__Pointlist_2_rec *next;
    CGAL_Point_2<R> point;
    CGAL_Side side;
};

template <class R>
struct CGAL__Pointlist_2 {
    int size;
    CGAL__Pointlist_2_rec<R> *first;
    CGAL__Pointlist_2() ;
    ~CGAL__Pointlist_2() ;
};

template <class R>
class CGAL_Triangle_2_Triangle_2_pair {
public:
    enum Intersection_results {NO, POINT, SEGMENT, TRIANGLE, POLYGON};
                        CGAL_Triangle_2_Triangle_2_pair() ;
                        CGAL_Triangle_2_Triangle_2_pair(
                                CGAL_Triangle_2<R> const *trian1,
                                CGAL_Triangle_2<R> const *trian2) ;
    ~CGAL_Triangle_2_Triangle_2_pair() {}
    Intersection_results intersection_type() const;
    void                intersection(CGAL_Point_2<R> &result) const;
    void                intersection(CGAL_Segment_2<R> &result) const;
    void                intersection(CGAL_Triangle_2<R> &result) const;
    void                intersection(/*CGAL_Polygon_2<R> &result*/) const;
protected:
    CGAL_Triangle_2<R> const*   _trian1;
    CGAL_Triangle_2<R> const *  _trian2;
    bool                    _known;
    Intersection_results    _result;
    CGAL__Pointlist_2<R>    _pointlist;
};




#include <CGAL/Line_2.h>
#include <CGAL/utils.h>
#include <CGAL/number_utils.h>

template <class R>
CGAL__Pointlist_2<R>::CGAL__Pointlist_2()
{
    size = 0;
    first = 0;
}

template <class R>
CGAL__Pointlist_2<R>::~CGAL__Pointlist_2()
{
    CGAL__Pointlist_2_rec<R> *cur;
    for (int i=0; i<size; i++) {
        cur = first;
        first = cur->next;
        delete cur;
    }
}


template <class R>
void CGAL__init_list(CGAL__Pointlist_2<R> &list,
                const CGAL_Triangle_2<R> &trian)
{
    // check on degeneracies of trian.
    if (!trian.is_degenerate()) {
        list.size = 3;
        list.first = 0;
        for (int i=0; i<3; i++) {
            CGAL__Pointlist_2_rec<R> *newrec =
                        new CGAL__Pointlist_2_rec<R>;
            newrec->next = list.first;
            list.first = newrec;
            newrec->point = trian[i];
        }
    } else {
        // CGAL__not_implemented();
        CGAL_kernel_assertion(false);
    }
}

#include <CGAL/Line_2_Line_2_pair.h>

template <class R>
void CGAL__cut_off(CGAL__Pointlist_2<R> &list,
                const CGAL_Line_2<R> &cutter)
{
    int i;
    int add = 0;
    CGAL__Pointlist_2_rec<R> *cur, *last, *newrec;
    for (i=0, cur = list.first; i<list.size; i++, cur = cur->next) {
        cur->side = cutter.where_is(cur->point);
        last = cur;
    }
    for (cur = list.first, i=0; i<list.size; i++, cur = cur->next) {
        if ((cur->side == CGAL_LEFT && last->side == CGAL_RIGHT)
           || (cur->side == CGAL_RIGHT && last->side == CGAL_LEFT)) {
            // add a vertex after cur
            add++;
            CGAL_Line_2<R> l(cur->point, last->point);
            newrec = new CGAL__Pointlist_2_rec<R>;
            newrec->next = last->next;
            last->next = newrec;
            newrec->side = CGAL_ON;
            CGAL_Line_2_Line_2_pair<R> linepair(&cutter,  &l);
            CGAL_Line_2_Line_2_pair<R>::Intersection_results isr;
            isr = linepair.intersection_type();
            CGAL_kernel_assertion(isr == CGAL_Line_2_Line_2_pair<R>::POINT);
            linepair.intersection(newrec->point);
        }
        last = cur;
    }
    CGAL_kernel_assertion(add <= 2);
    CGAL__Pointlist_2_rec<R> **curpt;
    curpt = &list.first;
    while (*curpt != 0) {
        cur = *curpt;
        if (cur->side == CGAL_RIGHT) {
            add--;
            *curpt = cur->next;
            delete cur;
        } else {
            curpt = &cur->next;
        }
    }
    if (list.size == 2 && add == 1) {
        add = 0;
        cur = list.first;
        if (cur->side == CGAL_ON) {
            list.first = cur->next;
            delete cur;
        } else {
            last = cur;
            cur = cur->next;
            last->next = cur->next;
            delete cur;
        }
    }
    list.size += add;
}

template <class R>
CGAL_Triangle_2_Triangle_2_pair<R>::
CGAL_Triangle_2_Triangle_2_pair()
{
    _trian1 = 0;
    _trian2 = 0;
    _known = false;
}

template <class R>
CGAL_Triangle_2_Triangle_2_pair<R>::
CGAL_Triangle_2_Triangle_2_pair(CGAL_Triangle_2<R> const *trian1,
         CGAL_Triangle_2<R> const *trian2)
{
    _trian1 = trian1;
    _trian2 = trian2;
    _known = false;
}

template <class R>
CGAL_Triangle_2_Triangle_2_pair<R>::Intersection_results
CGAL_Triangle_2_Triangle_2_pair<R>::intersection_type() const
{
    if (_known)
        return _result;
// The non const this pointer is used to cast away const.
    CGAL_Triangle_2_Triangle_2_pair<R> *ncthis =
                (CGAL_Triangle_2_Triangle_2_pair<R> *) this;
    ncthis->_known = true;
    if (!do_overlap(_trian1->bbox(), _trian2->bbox())) {
        ncthis->_result = NO;
        return _result;
    }
    CGAL__init_list(ncthis->_pointlist, *_trian1);
    if (_trian2->is_degenerate()) {
        // CGAL__not_implemented();
        CGAL_kernel_assertion(false);
    } else {
        CGAL_Line_2<R> l(_trian2->vertex(0), _trian2->vertex(1));
        if (l.where_is(_trian2->vertex(2)) == CGAL_LEFT) {
            // counterclockwise triangle
            CGAL__cut_off(ncthis->_pointlist, l);
            l = CGAL_Line_2<R>(_trian2->vertex(1), _trian2->vertex(2));
            CGAL__cut_off(ncthis->_pointlist, l);
            l = CGAL_Line_2<R>(_trian2->vertex(2), _trian2->vertex(0));
            CGAL__cut_off(ncthis->_pointlist, l);
        } else {
            l = l.opposite();
            CGAL__cut_off(ncthis->_pointlist, l);
            l = CGAL_Line_2<R>(_trian2->vertex(0), _trian2->vertex(2));
            CGAL__cut_off(ncthis->_pointlist, l);
            l = CGAL_Line_2<R>(_trian2->vertex(2), _trian2->vertex(1));
            CGAL__cut_off(ncthis->_pointlist, l);
        }
    }
    switch (_pointlist.size) {
    case 0:
        ncthis->_result = NO;
        break;
    case 1:
        ncthis->_result = POINT;
        break;
    case 2:
        ncthis->_result = SEGMENT;
        break;
    case 3:
        ncthis->_result = TRIANGLE;
        break;
    default:
        ncthis->_result = POLYGON;
    }
    return _result;
}

template <class R>
void
CGAL_Triangle_2_Triangle_2_pair<R>::intersection(
        /* CGAL_Polygon_2<R> &result */) const
{
    CGAL_kernel_assertion(_known);
    CGAL_kernel_assertion(_result == TRIANGLE || _result == POLYGON);
    CGAL__Pointlist_2_rec<R> *cur;
    int i;
    for (i=0, cur = _pointlist.first;
         i<_pointlist.size;
         i++, cur = cur->next) {
      cout << CGAL_to_double(cur->point.x()) << ' ';
      cout << CGAL_to_double(cur->point.y()) << ' ';
    }
    cout << endl;
}

template <class R>
void
CGAL_Triangle_2_Triangle_2_pair<R>::intersection(
        CGAL_Triangle_2<R> &result) const
{
    CGAL_kernel_assertion(_known);
    CGAL_kernel_assertion(_result == TRIANGLE);
    result = CGAL_Triangle_2<R>(_pointlist.first->point,
                    _pointlist.first->next->point,
                    _pointlist.first->next->next->point);
}

template <class R>
void
CGAL_Triangle_2_Triangle_2_pair<R>::intersection(
        CGAL_Segment_2<R> &seg) const
{
    CGAL_kernel_assertion(_known);
    CGAL_kernel_assertion(_result == SEGMENT);
    seg = CGAL_Segment_2<R>(_pointlist.first->point,
                    _pointlist.first->next->point);
}

template <class R>
void
CGAL_Triangle_2_Triangle_2_pair<R>::intersection(
        CGAL_Point_2<R> &pt) const
{
    CGAL_kernel_assertion(_known);
    CGAL_kernel_assertion(_result == POINT);
    pt = _pointlist.first->point;
}



#endif
