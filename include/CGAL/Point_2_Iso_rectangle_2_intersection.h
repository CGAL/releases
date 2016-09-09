
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
// $Source: /CVSROOT/CGAL/Packages/Intersections_2/include/CGAL/Point_2_Iso_rectangle_2_intersection.h,v $
// $Revision: 1.7 $ $Date: 2003/10/21 12:16:48 $
// $Name: current_submission $
//
// Author(s)     : Geert-Jan Giezeman


#ifndef CGAL_POINT_2_ISO_RECTANGLE_2_INTERSECTION_H
#define CGAL_POINT_2_ISO_RECTANGLE_2_INTERSECTION_H

#include <CGAL/Iso_rectangle_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/Object.h>

CGAL_BEGIN_NAMESPACE

namespace CGALi {

template <class K>
inline 
bool
do_intersect(const typename CGAL_WRAP(K)::Point_2 &pt,
	     const typename CGAL_WRAP(K)::Iso_rectangle_2 &iso,
	     const K&)
{
    return !iso.has_on_unbounded_side(pt);
}

template <class K>
inline 
bool
do_intersect(const typename CGAL_WRAP(K)::Iso_rectangle_2 &iso,
	     const typename CGAL_WRAP(K)::Point_2 &pt,
	     const K&)
{
    return !iso.has_on_unbounded_side(pt);
}

template <class K>
Object
intersection(const typename CGAL_WRAP(K)::Point_2 &pt,
	     const typename CGAL_WRAP(K)::Iso_rectangle_2 &iso,
	     const K& k)
{
  if (CGALi::do_intersect(pt,iso,k)) {
    return make_object(pt);
    }
    return Object();
}


template <class K>
Object
intersection(const typename CGAL_WRAP(K)::Iso_rectangle_2 &iso,
	     const typename CGAL_WRAP(K)::Point_2 &pt,
	     const K& k)
{
  if (CGALi::do_intersect(pt,iso,k)) {
    return make_object(pt);
    }
    return Object();
}

} // namespace CGALi


template <class K>
inline 
bool
do_intersect(const Iso_rectangle_2<K> &iso,
	     const Point_2<K> &pt)
{
  return CGALi::do_intersect(pt, iso, K());
}

template <class K>
inline 
bool
do_intersect(const Point_2<K> &pt,
	     const Iso_rectangle_2<K> &iso)
{
  return CGALi::do_intersect(pt, iso, K());
}

template <class K>
inline 
Object
intersection(const Iso_rectangle_2<K> &iso,
	     const Point_2<K> &pt)
{
  return CGALi::intersection(pt, iso, K());;
}
template <class K>
inline 
Object
intersection(const Point_2<K> &pt,
	     const Iso_rectangle_2<K> &iso)
{
  return CGALi::intersection(pt, iso, K());;
}
CGAL_END_NAMESPACE

#endif
