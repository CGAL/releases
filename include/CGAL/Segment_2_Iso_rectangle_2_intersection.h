
// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/Segment_2_Iso_rectangle_2_intersection.h
// package       : Intersections_2 (1.7)
// source        : intersection_2_2.fw
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : Saarbruecken
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_SEGMENT_2_BBOX_2_INTERSECTION_H
#define CGAL_SEGMENT_2_BBOX_2_INTERSECTION_H

#ifndef CGAL_ISO_RECTANGLE_2_H
#include <CGAL/Iso_rectangle_2.h>
#endif // CGAL_ISO_RECTANGLE_2_H
#ifndef CGAL_SEGMENT_2_H
#include <CGAL/Segment_2.h>
#endif // CGAL_SEGMENT_2_H
#ifndef CGAL_POINT_2_H
#include <CGAL/Point_2.h>
#endif // CGAL_POINT_2_H
#ifndef CGAL_UTILS_H
#include <CGAL/utils.h>
#endif // CGAL_UTILS_H
#ifndef CGAL_NUMBER_UTILS_H
#include <CGAL/number_utils.h>
#endif // CGAL_NUMBER_UTILS_H

template <class R>
class CGAL_Segment_2_Iso_rectangle_2_pair {
public:
    enum Intersection_results {NO, POINT, SEGMENT};
    CGAL_Segment_2_Iso_rectangle_2_pair() ;
    CGAL_Segment_2_Iso_rectangle_2_pair(CGAL_Segment_2<R> const *seg,
                          CGAL_Iso_rectangle_2<R> const *rect) ;

#ifndef CGAL_CFG_RETURN_TYPE_BUG_2
  Intersection_results intersection_type() const;

#else
  Intersection_results intersection_type() const
 {
     typedef typename R::RT RT;
     typedef typename R::FT FT;
     if (_known)
         return _result;
     CGAL_Segment_2_Iso_rectangle_2_pair<R> *ncthis =
                 (CGAL_Segment_2_Iso_rectangle_2_pair<R> *) this;
     ncthis->_known = true;
     for (int i=0; i<_ref_point.dimension(); i++) {
         if (_dir.homogeneous(i) == RT(0)) {
             if (_ref_point.cartesian(i) < _isomin.cartesian(i)) {
                 ncthis->_result = NO;
                 return _result;
             }
             if (_ref_point.cartesian(i) > _isomax.cartesian(i)) {
                 ncthis->_result = NO;
                 return _result;
             }
         } else {
             FT newmin, newmax;
             if (_dir.homogeneous(i) > RT(0)) {
                 newmin = (_isomin.cartesian(i)-_ref_point.cartesian(i)) /
                     _dir.cartesian(i);
                 newmax = (_isomax.cartesian(i)-_ref_point.cartesian(i)) /
                     _dir.cartesian(i);
             } else {
                 newmin = (_isomax.cartesian(i)-_ref_point.cartesian(i)) /
                     _dir.cartesian(i);
                 newmax = (_isomin.cartesian(i)-_ref_point.cartesian(i)) /
                     _dir.cartesian(i);
             }
             if (newmin > _min)
                 ncthis->_min = newmin;
             if (newmax < _max)
                 ncthis->_max = newmax;
             if (_max < _min) {
                 ncthis->_result = NO;
                 return _result;
             }
         }
     }
     if (_max == _min) {
         ncthis->_result = POINT;
         return _result;
     }
     ncthis->_result = SEGMENT;
     return _result;
 }
 
#endif // CGAL_CFG_RETURN_TYPE_BUG_2

    bool                       intersection(
                                    CGAL_Point_2<R> &result) const;
    bool                       intersection(
                                    CGAL_Segment_2<R> &result) const;
protected:
    bool                       _known;
    Intersection_results       _result;
    CGAL_Point_2<R>            _ref_point;
    CGAL_Vector_2<R>           _dir;
    CGAL_Point_2<R>            _isomin;
    CGAL_Point_2<R>            _isomax;
    typename R::FT              _min,
                               _max;
};

template <class R>
inline bool CGAL_do_intersect(
    const CGAL_Segment_2<R> &p1,
    const CGAL_Iso_rectangle_2<R> &p2)
{
    typedef CGAL_Segment_2_Iso_rectangle_2_pair<R> pair_t;
    pair_t pair(&p1, &p2);
    return pair.intersection_type() != pair_t::NO;
}

#ifndef CGAL_OBJECT_H
#include <CGAL/Object.h>
#endif // CGAL_OBJECT_H

template <class R>
CGAL_Object
CGAL_intersection(
    const CGAL_Segment_2<R> &seg,
    const CGAL_Iso_rectangle_2<R> &iso)
{
    typedef CGAL_Segment_2_Iso_rectangle_2_pair<R> is_t;
    is_t ispair(&seg, &iso);
    switch (ispair.intersection_type()) {
    case is_t::NO:
    default:
        return CGAL_Object();
    case is_t::POINT: {
        CGAL_Point_2<R> ipt;
        ispair.intersection(ipt);
        return CGAL_Object(new CGAL_Wrapper< CGAL_Point_2<R> >(ipt));
    }
    case is_t::SEGMENT: {
        CGAL_Segment_2<R> iseg;
        ispair.intersection(iseg);
        return CGAL_Object(new CGAL_Wrapper< CGAL_Segment_2<R> >(iseg));
    }
    }
}




template <class R>
CGAL_Segment_2_Iso_rectangle_2_pair<R>::CGAL_Segment_2_Iso_rectangle_2_pair()
{
    _known = false;
}

template <class R>
CGAL_Segment_2_Iso_rectangle_2_pair<R>::
CGAL_Segment_2_Iso_rectangle_2_pair(
        CGAL_Segment_2<R> const *seg,
        CGAL_Iso_rectangle_2<R> const *iso)
{
    _known = false;
    _isomin = iso->min();
    _isomax = iso->max();
    _ref_point = seg->source();
    _dir = seg->direction().vector();
    _min = (typename R::FT)(0);
    int main_dir = (CGAL_abs(_dir.x()) > CGAL_abs(_dir.y()) ) ? 0 : 1;
    _max = (seg->target().cartesian(main_dir)-_ref_point.cartesian(main_dir)) /
            _dir.cartesian(main_dir);
}

#ifndef CGAL_CFG_RETURN_TYPE_BUG_2
template <class R>
CGAL_Segment_2_Iso_rectangle_2_pair<R>::Intersection_results
CGAL_Segment_2_Iso_rectangle_2_pair<R>::intersection_type() const
{
    typedef typename R::RT RT;
    typedef typename R::FT FT;
    if (_known)
        return _result;
    CGAL_Segment_2_Iso_rectangle_2_pair<R> *ncthis =
                (CGAL_Segment_2_Iso_rectangle_2_pair<R> *) this;
    ncthis->_known = true;
    for (int i=0; i<_ref_point.dimension(); i++) {
        if (_dir.homogeneous(i) == RT(0)) {
            if (_ref_point.cartesian(i) < _isomin.cartesian(i)) {
                ncthis->_result = NO;
                return _result;
            }
            if (_ref_point.cartesian(i) > _isomax.cartesian(i)) {
                ncthis->_result = NO;
                return _result;
            }
        } else {
            FT newmin, newmax;
            if (_dir.homogeneous(i) > RT(0)) {
                newmin = (_isomin.cartesian(i)-_ref_point.cartesian(i)) /
                    _dir.cartesian(i);
                newmax = (_isomax.cartesian(i)-_ref_point.cartesian(i)) /
                    _dir.cartesian(i);
            } else {
                newmin = (_isomax.cartesian(i)-_ref_point.cartesian(i)) /
                    _dir.cartesian(i);
                newmax = (_isomin.cartesian(i)-_ref_point.cartesian(i)) /
                    _dir.cartesian(i);
            }
            if (newmin > _min)
                ncthis->_min = newmin;
            if (newmax < _max)
                ncthis->_max = newmax;
            if (_max < _min) {
                ncthis->_result = NO;
                return _result;
            }
        }
    }
    if (_max == _min) {
        ncthis->_result = POINT;
        return _result;
    }
    ncthis->_result = SEGMENT;
    return _result;
}

#endif // CGAL_CFG_RETURN_TYPE_BUG_2

template <class R>
bool CGAL_Segment_2_Iso_rectangle_2_pair<R>::
intersection(CGAL_Segment_2<R> &seg) const
{
    if (!_known)
        intersection_type();
    if (_result != SEGMENT)
        return false;
    CGAL_Point_2<R> p1(_ref_point + _dir*_min);
    CGAL_Point_2<R> p2(_ref_point + _dir*_max);
    seg = CGAL_Segment_2<R>(p1, p2);
    return true;
}

template <class R> bool CGAL_Segment_2_Iso_rectangle_2_pair<R>::
intersection(CGAL_Point_2<R> &pt) const
{
    if (!_known)
        intersection_type();
    if (_result != POINT)
        return false;
    pt = CGAL_Point_2<R>(_ref_point + _dir*_min);
    return true;
}


template <class R>
class CGAL_Iso_rectangle_2_Segment_2_pair:
          public CGAL_Segment_2_Iso_rectangle_2_pair<R> {
public:
    CGAL_Iso_rectangle_2_Segment_2_pair() {}
    CGAL_Iso_rectangle_2_Segment_2_pair(CGAL_Iso_rectangle_2<R> const *rect,
                               CGAL_Segment_2<R> const *seg)
                :CGAL_Segment_2_Iso_rectangle_2_pair<R> (seg, rect){}
};

template <class R>
inline bool CGAL_do_intersect(
    const CGAL_Iso_rectangle_2<R> &p1,
    const CGAL_Segment_2<R> &p2)
{
    typedef CGAL_Iso_rectangle_2_Segment_2_pair<R> pair_t;
    pair_t pair(&p1, &p2);
    return pair.intersection_type() != pair_t::NO;
}

template <class R>
inline CGAL_Object
CGAL_intersection(
    const CGAL_Iso_rectangle_2<R>&iso,
    const CGAL_Segment_2<R>&seg)
{
    return CGAL_intersection(seg, iso);
}

#endif
