 

#ifndef CGAL_LINE_2_LINE_2_PAIR_H
#define CGAL_LINE_2_LINE_2_PAIR_H

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

    void                intersection(CGAL_Point_2<R> &result) const;
    void                intersection(CGAL_Line_2<R> &result) const;
protected:
    CGAL_Line_2<R> const*   _line1;
    CGAL_Line_2<R> const *  _line2;
    bool                    _known;
    Intersection_results    _result;
    CGAL_Point_2<R>         _intersection_point;
};

 


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
void
CGAL_Line_2_Line_2_pair<R>::intersection(CGAL_Point_2<R> &pt) const
{
    CGAL_kernel_assertion(_known);
    CGAL_kernel_assertion(_result == POINT);
    pt = _intersection_point;
}

template <class R>
void
CGAL_Line_2_Line_2_pair<R>::intersection(CGAL_Line_2<R> &l) const
{
    CGAL_kernel_assertion(_known);
    CGAL_kernel_assertion(_result == LINE);
    l = *_line1;
}
 


#endif
