
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

#ifndef CGAL_LINE_2_LINE_2_INTERSECTION_H
#define CGAL_LINE_2_LINE_2_INTERSECTION_H

#include <CGAL/Line_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/utils.h>
#include <CGAL/number_utils.h>

template <class R>
class CGAL_Line_2_Line_2_pair {
public:
    enum Intersection_results {NO, POINT, LINE};
    CGAL_Line_2_Line_2_pair() ;
    CGAL_Line_2_Line_2_pair(CGAL_Line_2<R> const *line1,
                            CGAL_Line_2<R> const *line2);
    ~CGAL_Line_2_Line_2_pair() {}

#ifndef CGAL_WORKAROUND_005
    Intersection_results intersection_type() const;

#else
    Intersection_results intersection_type() const
{
    typedef R::RT RT;
    if (_known)
        return _result;
    RT nom1, nom2, denom;
    // The non const this pointer is used to cast away const.
    CGAL_Line_2_Line_2_pair<R> *ncthis = (CGAL_Line_2_Line_2_pair<R> *) this;
    ncthis->_known = true;
    denom = _line1->a()*_line2->b() - _line2->a()*_line1->b();
    if (denom == RT(0)) {
        if (RT(0) == (_line1->a()*_line2->c() - _line2->a()*_line1->c()) &&
            RT(0) == (_line1->b()*_line2->c() - _line2->b()*_line1->c()))
            ncthis->_result = LINE;
        else
            ncthis->_result = NO;
        return _result;
    }
    nom1 = (_line1->b()*_line2->c() - _line2->b()*_line1->c());
    if (!CGAL_is_finite(nom1)) {
        ncthis->_result = NO;
        return _result;
    }
    nom2 = (_line2->a()*_line1->c() - _line1->a()*_line2->c());
    if (!CGAL_is_finite(nom2)) {
        ncthis->_result = NO;
        return _result;
    }
    R dummyR;
    if (!construct_if_finite(ncthis->_intersection_point,
                            nom1, nom2, denom, dummyR)){
        ncthis->_result = NO;
        return _result;
    }
    ncthis->_result = POINT;
    return _result;
}

#endif // CGAL_WORKAROUND_005

    bool                intersection(CGAL_Point_2<R> &result) const;
    bool                intersection(CGAL_Line_2<R> &result) const;
protected:
    CGAL_Line_2<R> const*   _line1;
    CGAL_Line_2<R> const *  _line2;
    bool                    _known;
    Intersection_results    _result;
    CGAL_Point_2<R>         _intersection_point;
};

template <class R>
inline bool CGAL_do_intersect(
    const CGAL_Line_2<R> &p1,
    const CGAL_Line_2<R> &p2)
{
    typedef CGAL_Line_2_Line_2_pair<R> pair_t;
    pair_t pair(&p1, &p2);
    return pair.intersection_type() == pair_t::NO;
}

#include <CGAL/Object.h>

template <class R>
CGAL_Object
CGAL_intersection(const CGAL_Line_2<R> &line1, const CGAL_Line_2<R> &line2)
{
    typedef CGAL_Line_2_Line_2_pair<R> is_t;
    is_t linepair(&line1, &line2);
    switch (linepair.intersection_type()) {
    case is_t::NO:
    default:
        return CGAL_Object();
    case is_t::POINT: {
        CGAL_Point_2<R> pt;
        linepair.intersection(pt);
        return CGAL_Object(new CGAL_Wrapper< CGAL_Point_2<R> >(pt));
    }
    case is_t::LINE:
        return CGAL_Object(new CGAL_Wrapper< CGAL_Line_2<R> >(line1));
    }
}



template <class R, class POINT, class RT>
bool construct_if_finite(POINT &pt, RT x, RT y, RT w, R &)
{
    typedef R::FT FT;
    CGAL_kernel_precondition(CGAL_is_finite(x)
                             && CGAL_is_finite(y)
                             && w != RT(0));

    if (!CGAL_is_finite(FT(x)/FT(w)) || !CGAL_is_finite(FT(y)/FT(w)))
        return false;
    pt = POINT(x, y, w);
    return true;
}

template <class R>
CGAL_Line_2_Line_2_pair<R>::CGAL_Line_2_Line_2_pair()
{
    _line1 = 0;
    _line2 = 0;
    _known = false;
}

template <class R>
CGAL_Line_2_Line_2_pair<R>::CGAL_Line_2_Line_2_pair(
    CGAL_Line_2<R> const *line1, CGAL_Line_2<R> const *line2)
{
    _line1 = line1;
    _line2 = line2;
    _known = false;
}

#ifndef CGAL_WORKAROUND_005
template <class R>
CGAL_Line_2_Line_2_pair<R>::Intersection_results
CGAL_Line_2_Line_2_pair<R>::intersection_type() const
{
    typedef R::RT RT;
    if (_known)
        return _result;
    RT nom1, nom2, denom;
    // The non const this pointer is used to cast away const.
    CGAL_Line_2_Line_2_pair<R> *ncthis = (CGAL_Line_2_Line_2_pair<R> *) this;
    ncthis->_known = true;
    denom = _line1->a()*_line2->b() - _line2->a()*_line1->b();
    if (denom == RT(0)) {
        if (RT(0) == (_line1->a()*_line2->c() - _line2->a()*_line1->c()) &&
            RT(0) == (_line1->b()*_line2->c() - _line2->b()*_line1->c()))
            ncthis->_result = LINE;
        else
            ncthis->_result = NO;
        return _result;
    }
    nom1 = (_line1->b()*_line2->c() - _line2->b()*_line1->c());
    if (!CGAL_is_finite(nom1)) {
        ncthis->_result = NO;
        return _result;
    }
    nom2 = (_line2->a()*_line1->c() - _line1->a()*_line2->c());
    if (!CGAL_is_finite(nom2)) {
        ncthis->_result = NO;
        return _result;
    }
    R dummyR;
    if (!construct_if_finite(ncthis->_intersection_point,
                            nom1, nom2, denom, dummyR)){
        ncthis->_result = NO;
        return _result;
    }
    ncthis->_result = POINT;
    return _result;
}

#endif // CGAL_WORKAROUND_005

template <class R>
bool
CGAL_Line_2_Line_2_pair<R>::intersection(CGAL_Point_2<R> &pt) const
{
    if (!_known)
        intersection_type();
    if (_result != POINT)
        return false;
    pt = _intersection_point;
    return true;
}

template <class R>
bool
CGAL_Line_2_Line_2_pair<R>::intersection(CGAL_Line_2<R> &l) const
{
    if (!_known)
        intersection_type();
    if (_result != LINE)
        return false;
    l = *_line1;
    return true;
}


#endif
