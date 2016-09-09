/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/



// Author: Geert-Jan Giezeman


#include <CGAL/Segment_2.h>
#include <CGAL/Triangle_2.h>
//#include <CGAL/Polygon_2.h>

template <class R>
struct CGAL__Pointlist_2_rec {
    CGAL__Pointlist_2_rec *next;
    CGAL_Point_2<R> point;
    CGAL_Oriented_side side;
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
#ifdef CGAL_WORKAROUND_005
    Intersection_results intersection_type() const
    {
        if (_known)
            return _result;
    // The non const this pointer is used to cast away const.
        CGAL_Triangle_2_Triangle_2_pair<R> *ncthis =
                    (CGAL_Triangle_2_Triangle_2_pair<R> *) this;
        ncthis->_known = true;
        if (!CGAL_do_overlap(_trian1->bbox(), _trian2->bbox())) {
            ncthis->_result = NO;
            return _result;
        }
        CGAL__init_list(ncthis->_pointlist, *_trian1);
        if (_trian2->is_degenerate()) {
            // CGAL__not_implemented();
            CGAL_kernel_assertion(false);
        } else {
            CGAL_Line_2<R> l(_trian2->vertex(0), _trian2->vertex(1));
            if (l.oriented_side(_trian2->vertex(2)) == CGAL_ON_POSITIVE_SIDE) {
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
    
#else
    Intersection_results intersection_type() const;
#endif // CGAL_WORKAROUND_005
    bool                intersection(CGAL_Point_2<R> &result) const;
    bool                intersection(CGAL_Segment_2<R> &result) const;
    bool                intersection(CGAL_Triangle_2<R> &result) const;
    bool                intersection(/*CGAL_Polygon_2<R> &result*/) const;
    int                 vertex_count() const;
    CGAL_Point_2<R>     vertex(int i) const;
protected:
    CGAL_Triangle_2<R> const*   _trian1;
    CGAL_Triangle_2<R> const *  _trian2;
    bool                    _known;
    Intersection_results    _result;
    CGAL__Pointlist_2<R>    _pointlist;
};

template <class R>
inline bool CGAL_do_intersect(
    const CGAL_Triangle_2<R> &p1,
    const CGAL_Triangle_2<R> &p2)
{
    typedef CGAL_Triangle_2_Triangle_2_pair<R> pair_t;
    pair_t pair(&p1, &p2);
    return pair.intersection_type() != pair_t::NO;
}



#include <CGAL/Line_2.h>
#include <CGAL/utils.h>
#include <CGAL/number_utils.h>
#include <vector.h>

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

#include <CGAL/Line_2_Line_2_intersection.h>

template <class R>
void CGAL__cut_off(CGAL__Pointlist_2<R> &list,
                const CGAL_Line_2<R> &cutter)
{
    int i;
    int add = 0;
    CGAL__Pointlist_2_rec<R> *cur, *last, *newrec;
    for (i=0, cur = list.first; i<list.size; i++, cur = cur->next) {
        cur->side = cutter.oriented_side(cur->point);
        last = cur;
    }
    for (cur = list.first, i=0; i<list.size; i++, cur = cur->next) {
        if ((cur->side == CGAL_ON_POSITIVE_SIDE
             && last->side == CGAL_ON_NEGATIVE_SIDE)
           || (cur->side == CGAL_ON_NEGATIVE_SIDE
               && last->side == CGAL_ON_POSITIVE_SIDE)) {
            // add a vertex after cur
            add++;
            CGAL_Line_2<R> l(cur->point, last->point);
            newrec = new CGAL__Pointlist_2_rec<R>;
            newrec->next = last->next;
            last->next = newrec;
            newrec->side = CGAL_ON_ORIENTED_BOUNDARY;
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
        if (cur->side == CGAL_ON_NEGATIVE_SIDE) {
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
        if (cur->side == CGAL_ON_ORIENTED_BOUNDARY) {
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

#ifndef CGAL_WORKAROUND_005
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
    if (!CGAL_do_overlap(_trian1->bbox(), _trian2->bbox())) {
        ncthis->_result = NO;
        return _result;
    }
    CGAL__init_list(ncthis->_pointlist, *_trian1);
    if (_trian2->is_degenerate()) {
        // CGAL__not_implemented();
        CGAL_kernel_assertion(false);
    } else {
        CGAL_Line_2<R> l(_trian2->vertex(0), _trian2->vertex(1));
        if (l.oriented_side(_trian2->vertex(2)) == CGAL_ON_POSITIVE_SIDE) {
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

#endif // CGAL_WORKAROUND_005


template <class R>
bool
CGAL_Triangle_2_Triangle_2_pair<R>::intersection(
        /* CGAL_Polygon_2<R> &result */) const
{
    if (!_known)
        intersection_type();
    if (_result != TRIANGLE  &&  _result != POLYGON)
        return false;
    CGAL__Pointlist_2_rec<R> *cur;
    int i;
    for (i=0, cur = _pointlist.first;
         i<_pointlist.size;
         i++, cur = cur->next) {
      cout << CGAL_to_double(cur->point.x()) << ' ';
      cout << CGAL_to_double(cur->point.y()) << ' ';
    }
    cout << endl;
    return true;
}

template <class R>
int
CGAL_Triangle_2_Triangle_2_pair<R>::vertex_count() const
{
    CGAL_kernel_assertion(_known);
    return _pointlist.size;
}

template <class R>
CGAL_Point_2<R>
CGAL_Triangle_2_Triangle_2_pair<R>::vertex(int n) const
{
    CGAL_kernel_assertion(_known);
    CGAL_kernel_assertion(n >= 0 && n < _pointlist.size);
    CGAL__Pointlist_2_rec<R> *cur;
    int k;
    for (k=0, cur = _pointlist.first;
         k < n;
         k++, cur = cur->next) {
    }
    return cur->point;
}

template <class R>
bool
CGAL_Triangle_2_Triangle_2_pair<R>::intersection(
        CGAL_Triangle_2<R> &result) const
{
    if (!_known)
        intersection_type();
    if (_result != TRIANGLE)
        return false;
    result = CGAL_Triangle_2<R>(_pointlist.first->point,
                    _pointlist.first->next->point,
                    _pointlist.first->next->next->point);
    return true;
}

template <class R>
bool
CGAL_Triangle_2_Triangle_2_pair<R>::intersection(
        CGAL_Segment_2<R> &seg) const
{
    if (!_known)
        intersection_type();
    if (_result != SEGMENT)
        return false;
    seg = CGAL_Segment_2<R>(_pointlist.first->point,
                    _pointlist.first->next->point);
    return true;
}

template <class R>
bool
CGAL_Triangle_2_Triangle_2_pair<R>::intersection(
        CGAL_Point_2<R> &pt) const
{
    if (!_known)
        intersection_type();
    if (_result != POINT)
        return false;
    pt = _pointlist.first->point;
    return true;
}



template <class R>
CGAL_Object
CGAL_intersection(const CGAL_Triangle_2<R> &tr1, const CGAL_Triangle_2<R>&tr2)
{
    typedef CGAL_Triangle_2_Triangle_2_pair<R> is_t;
    is_t ispair(&tr1, &tr2);
    switch (ispair.intersection_type()) {
    case is_t::NO:
    default:
        return CGAL_Object();
    case is_t::POINT: {
        CGAL_Point_2<R> pt;
        ispair.intersection(pt);
        return CGAL_Object(new CGAL_Wrapper< CGAL_Point_2<R> >(pt));
    }
    case is_t::SEGMENT: {
        CGAL_Segment_2<R> iseg;
        ispair.intersection(iseg);
        return CGAL_Object(new CGAL_Wrapper< CGAL_Segment_2<R> >(iseg));
    }
    case is_t::TRIANGLE: {
        CGAL_Triangle_2<R> itr;
        ispair.intersection(itr);
        return CGAL_Object(new CGAL_Wrapper< CGAL_Triangle_2<R> >(itr));
    }
    case is_t::POLYGON: {
        typedef vector<CGAL_Point_2<R> > Container;
        Container points(ispair.vertex_count());
        for (int i =0; i < ispair.vertex_count(); i++) {
            points[i] = ispair.vertex(i);
        }
        return CGAL_Object(new CGAL_Wrapper< Container >(points));
    }
    }
}

