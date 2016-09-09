
// Copyright (c) 2000  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source: /CVSROOT/CGAL/Packages/Intersections_2/include/CGAL/Ray_2_Line_2_intersection.h,v $
// $Revision: 1.8 $ $Date: 2003/10/21 12:16:51 $
// $Name: current_submission $
//
// Author(s)     : Geert-Jan Giezeman


#ifndef CGAL_RAY_2_LINE_2_INTERSECTION_H
#define CGAL_RAY_2_LINE_2_INTERSECTION_H

#include <CGAL/Line_2.h>
#include <CGAL/Ray_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/utils.h>
#include <CGAL/number_utils.h>
#include <CGAL/Object.h>
#include <CGAL/Line_2_Line_2_intersection.h>

CGAL_BEGIN_NAMESPACE

namespace CGALi {

template <class K>
class Ray_2_Line_2_pair {
public:
    enum Intersection_results {NO, POINT, RAY};
    Ray_2_Line_2_pair() ;
    Ray_2_Line_2_pair(typename K::Ray_2 const *ray,
		      typename K::Line_2 const *line);
    ~Ray_2_Line_2_pair() {}

#ifndef CGAL_CFG_RETURN_TYPE_BUG_2
    Intersection_results intersection_type() const;
#else
    Intersection_results intersection_type() const
{
    if (_known)
        return _result;
    // The non const this pointer is used to cast away const.
    _known = true;
    const typename K::Line_2 &l1 = _ray->supporting_line();
    Line_2_Line_2_pair<K> linepair(&l1, _line);
    switch ( linepair.intersection_type()) {
    case Line_2_Line_2_pair<K>::NO:
        _result = NO;
        break;
    case Line_2_Line_2_pair<K>::POINT:
        linepair.intersection(_intersection_point);
        _result = (_ray->collinear_has_on(_intersection_point) ) ?
                POINT : NO;
        break;
    case Line_2_Line_2_pair<K>::LINE:
        _result = RAY;
        break;
    }
    return _result;
}

#endif // CGAL_CFG_RETURN_TYPE_BUG_2

    bool                intersection(typename K::Point_2 &result) const;
    bool                intersection(typename K::Ray_2 &result) const;
protected:
    typename K::Ray_2 const *   _ray;
    typename K::Line_2 const *  _line;
    mutable bool                    _known;
    mutable Intersection_results    _result;
    mutable typename K::Point_2         _intersection_point;
};

template <class K>
inline bool do_intersect(
    const typename CGAL_WRAP(K)::Ray_2 &p1,
    const typename CGAL_WRAP(K)::Line_2 &p2)
{
    typedef Ray_2_Line_2_pair<K> pair_t;
    pair_t pair(&p1, &p2);
    return pair.intersection_type() != pair_t::NO;
}



template <class K>
Object
intersection(const typename CGAL_WRAP(K)::Ray_2 &ray,
	     const typename CGAL_WRAP(K)::Line_2 &line,
	     const K& k)
{
    typedef Ray_2_Line_2_pair<K> is_t;
    is_t ispair(&ray, &line);
    switch (ispair.intersection_type()) {
    case is_t::NO:
    default:
        return Object();
    case is_t::POINT: {
        typename K::Point_2 pt;
        ispair.intersection(pt);
        return make_object(pt);
    }
    case is_t::RAY: {
        return make_object(ray);
    }
    }
}


template <class K>
inline
Object
intersection(const typename CGAL_WRAP(K)::Line_2 &line,
	     const typename CGAL_WRAP(K)::Ray_2 &ray,
	     const K& k)
{
  return CGALi::intersection(ray, line, k);
}


template <class K>
class Line_2_Ray_2_pair: public Ray_2_Line_2_pair<K> {
public:
    Line_2_Ray_2_pair(typename K::Line_2 const *line,
		      typename K::Ray_2 const *ray) :
      Ray_2_Line_2_pair<K>(ray, line) {}
};

template <class K>
inline bool do_intersect(
    const typename CGAL_WRAP(K)::Line_2 &p1,
    const typename CGAL_WRAP(K)::Ray_2 &p2,
    const K& k)
{
    typedef Line_2_Ray_2_pair<K> pair_t;
    pair_t pair(&p1, &p2);
    return pair.intersection_type() != pair_t::NO;
}



template <class K>
Ray_2_Line_2_pair<K>::Ray_2_Line_2_pair()
{
    _ray = 0;
    _line = 0;
    _known = false;
}

template <class K>
Ray_2_Line_2_pair<K>::Ray_2_Line_2_pair(
    typename K::Ray_2 const *ray, typename K::Line_2 const *line)
{
    _ray = ray;
    _line = line;
    _known = false;
}

#ifndef CGAL_CFG_RETURN_TYPE_BUG_2
template <class K>
typename Ray_2_Line_2_pair<K>::Intersection_results
Ray_2_Line_2_pair<K>::intersection_type() const
{
    if (_known)
        return _result;
    // The non const this pointer is used to cast away const.
    _known = true;
    const typename K::Line_2 &l1 = _ray->supporting_line();
    Line_2_Line_2_pair<K> linepair(&l1, _line);
    switch ( linepair.intersection_type()) {
    case Line_2_Line_2_pair<K>::NO:
        _result = NO;
        break;
    case Line_2_Line_2_pair<K>::POINT:
        linepair.intersection(_intersection_point);
        _result = (_ray->collinear_has_on(_intersection_point) ) ?
                POINT : NO;
        break;
    case Line_2_Line_2_pair<K>::LINE:
        _result = RAY;
        break;
    }
    return _result;
}

#endif // CGAL_CFG_RETURN_TYPE_BUG_2

template <class K>
bool
Ray_2_Line_2_pair<K>::intersection(typename K::Point_2 &result) const
{
    if (!_known)
        intersection_type();
    if (_result != POINT)
        return false;
    result = _intersection_point;
    return true;
}

template <class K>
bool
Ray_2_Line_2_pair<K>::intersection(typename K::Ray_2 &result) const
{
    if (!_known)
        intersection_type();
    if (_result != RAY)
        return false;
    result = *_ray;
    return true;
}
} // namespace CGALi

template <class K>
inline bool do_intersect(const Line_2<K> &p1, const Ray_2<K> &p2)
{
  return CGALi::do_intersect(p1, p2, K());
}

template <class K>
inline bool do_intersect(const Ray_2<K> &p2, const Line_2<K> &p1)
{
  return CGALi::do_intersect(p1, p2, K());
}

template <class K>
inline Object
intersection(const Line_2<K> &line, const Ray_2<K> &ray)
{
    return CGALi::intersection(ray, line, K());
}

template <class K>
inline Object
intersection(const Ray_2<K> &ray, const Line_2<K> &line)
{
    return CGALi::intersection(ray, line, K());
}
CGAL_END_NAMESPACE



#endif
