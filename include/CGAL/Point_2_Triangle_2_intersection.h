
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

#ifndef CGAL_POINT_2_TRIANGLE_2_INTERSECTION_H
#define CGAL_POINT_2_TRIANGLE_2_INTERSECTION_H

#include <CGAL/Point_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Point_2.h>

template <class R>
class CGAL_Point_2_Triangle_2_pair {
public:
    enum Intersection_results {NO, POINT};
    CGAL_Point_2_Triangle_2_pair() ;
    CGAL_Point_2_Triangle_2_pair(CGAL_Point_2<R> const *pt,
                            CGAL_Triangle_2<R> const *trian);
    ~CGAL_Point_2_Triangle_2_pair() {}
#ifdef CGAL_WORKAROUND_005
    Intersection_results intersection_type() const
    {
        typedef CGAL_Line_2<R> line_t;
        if (_known)
            return _result;
    // The non const this pointer is used to cast away const.
        CGAL_Point_2_Triangle_2_pair<R> *ncthis =
                    (CGAL_Point_2_Triangle_2_pair<R> *) this;
        ncthis->_known = true;
        if (_trian->has_on_unbounded_side(*_pt)) {
            ncthis->_result = NO;
        } else {
            ncthis->_result = POINT;
        }
        return _result;
    /*
        line_t l(_trian->vertex(0), _trian->vertex(1));
        if (l.has_on_positive_side(_trian->vertex(2))) {
            for (int i=0; i<3; i++) {
                if (line_t(_trian->vertex(i), _trian->vertex(i+1)).
                                    has_on_negative_side(*_pt)) {
                    ncthis->_result = NO;
                    return _result;
                }
            }
        } else {
            for (int i=0; i<3; i++)
                if(line_t(_trian->vertex(i), _trian->vertex(i-1)).
                                    has_on_negative_side(*_pt)){
                    ncthis->_result = NO;
                    return _result;
                }
        }
    */
    }
    
#else
    Intersection_results intersection_type() const;
#endif // CGAL_WORKAROUND_005
    bool                intersection(CGAL_Point_2<R> &result) const;
protected:
    CGAL_Point_2<R> const *    _pt;
    CGAL_Triangle_2<R> const * _trian;
    bool                       _known;
    Intersection_results       _result;
    CGAL_Point_2<R>            _intersection_point;
    CGAL_Point_2<R>            _other_point;
};

template <class R>
inline bool CGAL_do_intersect(
    const CGAL_Point_2<R> &p1,
    const CGAL_Triangle_2<R> &p2)
{
    typedef CGAL_Point_2_Triangle_2_pair<R> pair_t;
    pair_t pair(&p1, &p2);
    return pair.intersection_type() == pair_t::NO;
}



#include <CGAL/Line_2.h>
#include <CGAL/utils.h>
#include <CGAL/number_utils.h>
#include <CGAL/Straight_2.h>

template <class R>
CGAL_Point_2_Triangle_2_pair<R>::
CGAL_Point_2_Triangle_2_pair()
{
    _known = false;
    _pt = 0;
    _trian = 0;
}

template <class R>
CGAL_Point_2_Triangle_2_pair<R>::
CGAL_Point_2_Triangle_2_pair(CGAL_Point_2<R> const *pt,
                            CGAL_Triangle_2<R> const *trian)
{
    _known = false;
    _pt = pt;
    _trian = trian;
}

#ifndef CGAL_WORKAROUND_005
template <class R>
CGAL_Point_2_Triangle_2_pair<R>::Intersection_results
CGAL_Point_2_Triangle_2_pair<R>::intersection_type() const
{
    typedef CGAL_Line_2<R> line_t;
    if (_known)
        return _result;
// The non const this pointer is used to cast away const.
    CGAL_Point_2_Triangle_2_pair<R> *ncthis =
                (CGAL_Point_2_Triangle_2_pair<R> *) this;
    ncthis->_known = true;
    if (_trian->has_on_unbounded_side(*_pt)) {
        ncthis->_result = NO;
    } else {
        ncthis->_result = POINT;
    }
    return _result;
/*
    line_t l(_trian->vertex(0), _trian->vertex(1));
    if (l.has_on_positive_side(_trian->vertex(2))) {
        for (int i=0; i<3; i++) {
            if (line_t(_trian->vertex(i), _trian->vertex(i+1)).
                                has_on_negative_side(*_pt)) {
                ncthis->_result = NO;
                return _result;
            }
        }
    } else {
        for (int i=0; i<3; i++)
            if(line_t(_trian->vertex(i), _trian->vertex(i-1)).
                                has_on_negative_side(*_pt)){
                ncthis->_result = NO;
                return _result;
            }
    }
*/
}

#endif // CGAL_WORKAROUND_005



template <class R>
bool
CGAL_Point_2_Triangle_2_pair<R>::
intersection(CGAL_Point_2<R> &result) const
{
    if (!_known)
        intersection_type();
    if (_result != POINT)
        return false;
    result = *_pt;
    return true;
}


#include <CGAL/Object.h>

template <class R>
CGAL_Object
CGAL_intersection(const CGAL_Point_2<R> &pt, const CGAL_Triangle_2<R>&tr)
{
    typedef CGAL_Point_2_Triangle_2_pair<R> is_t;
    is_t ispair(&pt, &tr);
    switch (ispair.intersection_type()) {
    case is_t::NO:
    default:
        return CGAL_Object();
    case is_t::POINT: {
        return CGAL_Object(new CGAL_Wrapper< CGAL_Point_2<R> >(pt));
    }
    }
}

template <class R>
class CGAL_Triangle_2_Point_2_pair
: public CGAL_Point_2_Triangle_2_pair<R> {
public:
    CGAL_Triangle_2_Point_2_pair(
            CGAL_Triangle_2<R> const *trian,
            CGAL_Point_2<R> const *pt) :
                        CGAL_Point_2_Triangle_2_pair<R>(pt, trian) {}
};

template <class R>
inline bool CGAL_do_intersect(
    const CGAL_Triangle_2<R> &p1,
    const CGAL_Point_2<R> &p2)
{
    typedef CGAL_Triangle_2_Point_2_pair<R> pair_t;
    pair_t pair(&p1, &p2);
    return pair.intersection_type() == pair_t::NO;
}

template <class R>
inline CGAL_Object
CGAL_intersection(const CGAL_Triangle_2<R> &tr, const CGAL_Point_2<R> &pt)
{
    return CGAL_intersection(pt, tr);
}

#endif
