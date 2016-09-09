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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Cartesian_kernel/include/CGAL/Cartesian/Sphere_3.h $
// $Id: Sphere_3.h 50112 2009-06-26 14:15:56Z sloriot $
// 
//
// Author(s)     : Herve Bronnimann

#ifndef CGAL_CARTESIAN_SPHERE_3_H
#define CGAL_CARTESIAN_SPHERE_3_H

#include <CGAL/Handle_for.h>
#include <CGAL/Interval_nt.h>
#include <boost/tuple/tuple.hpp>

CGAL_BEGIN_NAMESPACE

template <class R_>
class SphereC3
{
  typedef typename R_::FT                   FT;
  typedef typename R_::Point_3              Point_3;
  typedef typename R_::Vector_3             Vector_3;
  typedef typename R_::Sphere_3             Sphere_3;
  typedef typename R_::Circle_3             Circle_3;

  typedef boost::tuple<Point_3, FT, Orientation>   Rep;
  typedef typename R_::template Handle<Rep>::type  Base;

  Base base;

public:
  typedef R_                                     R;

  SphereC3() {}

  SphereC3(const Point_3 &center, const FT &squared_radius,
           const Orientation &o = COUNTERCLOCKWISE)
  {
    CGAL_kernel_precondition( (squared_radius >= FT(0)) &
                              (o != COLLINEAR) );

    base = Rep(center, squared_radius, o);
  }

  // Sphere passing through and oriented by p,q,r,s
  SphereC3(const Point_3 &p, const Point_3 &q,
           const Point_3 &r, const Point_3 &s)
  {
    Orientation orient = make_certain(CGAL::orientation(p, q, r, s));
    Point_3 center = circumcenter(p, q, r, s);
    FT      squared_radius = squared_distance(p, center);

    base = Rep(center, squared_radius, orient);
  }

  // Sphere with great circle passing through p,q,r, oriented by o
  SphereC3(const Point_3 &p, const Point_3 &q, const Point_3 &r,
	   const Orientation &o = COUNTERCLOCKWISE)
  {
    CGAL_kernel_precondition(o != COLLINEAR);

    Point_3 center = circumcenter(p, q, r);
    FT      squared_radius = squared_distance(p, center);

    base = Rep(center, squared_radius, o);
  }

  // Sphere with diameter pq and orientation o
  SphereC3(const Point_3 &p, const Point_3 &q,
           const Orientation &o = COUNTERCLOCKWISE)
  {
    CGAL_kernel_precondition(o != COLLINEAR);

    Point_3 center = midpoint(p, q);
    FT      squared_radius = squared_distance(p, center);

    base = Rep(center, squared_radius, o);
  }

  explicit SphereC3(const Point_3 &center,
           const Orientation& o = COUNTERCLOCKWISE)
  {
    CGAL_kernel_precondition(o != COLLINEAR);

    base = Rep(center, FT(0), o);
  }

  typename R::Boolean   operator==(const SphereC3 &) const;
  typename R::Boolean   operator!=(const SphereC3 &) const;

  const Point_3 & center() const
  {
      return get(base).get<0>();
  }
  const FT & squared_radius() const
  {
      // Returns the square of the radius (instead of the radius itself,
      // which would require square roots)
      return get(base).get<1>();
  }
  Orientation orientation() const
  {
      return get(base).get<2>();
  }

  // A circle is degenerate if its (squared) radius is null or negative
  typename R::Boolean   is_degenerate() const;

  // Returns a circle with opposite orientation
  Sphere_3 opposite() const;

  typename R_::Oriented_side  oriented_side(const Point_3 &p) const;
  //! precond: ! x.is_degenerate() (when available)
  // Returns R::ON_POSITIVE_SIDE, R::ON_ORIENTED_BOUNDARY or
  // R::ON_NEGATIVE_SIDE
  typename R::Boolean   has_on(const Circle_3 &p) const;
  typename R::Boolean   has_on(const Point_3 &p) const;
  typename R::Boolean   has_on_boundary(const Point_3 &p) const;
  typename R::Boolean   has_on_positive_side(const Point_3 &p) const;
  typename R::Boolean   has_on_negative_side(const Point_3 &p) const;

  typename R_::Bounded_side bounded_side(const Point_3 &p) const;
  //! precond: ! x.is_degenerate() (when available)
  // Returns R::ON_BOUNDED_SIDE, R::ON_BOUNDARY or R::ON_UNBOUNDED_SIDE
  typename R::Boolean   has_on_bounded_side(const Point_3 &p) const;
  typename R::Boolean   has_on_unbounded_side(const Point_3 &p) const;
};

template < class R >
CGAL_KERNEL_INLINE
typename R::Boolean
SphereC3<R>::operator==(const SphereC3<R> &t) const
{
  if (CGAL::identical(base, t.base))
      return true;
  return center() == t.center() &&
         squared_radius() == t.squared_radius() &&
         orientation() == t.orientation();
}

template < class R >
inline
typename R::Boolean
SphereC3<R>::operator!=(const SphereC3<R> &t) const
{
  return !(*this == t);
}

template < class R >
CGAL_KERNEL_MEDIUM_INLINE
typename R::Oriented_side
SphereC3<R>::
oriented_side(const typename SphereC3<R>::Point_3 &p) const
{
  return enum_cast<Oriented_side>(bounded_side(p)) * orientation();
}

template < class R >
CGAL_KERNEL_INLINE
typename R::Bounded_side
SphereC3<R>::
bounded_side(const typename SphereC3<R>::Point_3 &p) const
{
  return enum_cast<Bounded_side>(compare(squared_radius(),
                                         squared_distance(center(), p)));
}

template < class R >
inline
typename R::Boolean
SphereC3<R>::
has_on(const typename SphereC3<R>::Circle_3 &c) const
{
  typedef typename SphereC3<R>::Point_3 Point_3;
  typedef typename SphereC3<R>::FT      FT;
  Point_3 proj = c.supporting_plane().projection(center());
  if(!(proj == c.center())) return false;
  const FT d2 = squared_distance(center(),c.center());
  return ((squared_radius() - d2) == c.squared_radius());
}

template < class R >
inline
typename R::Boolean
SphereC3<R>::
has_on(const typename SphereC3<R>::Point_3 &p) const
{
  return has_on_boundary(p);
}

template < class R >
inline
typename R::Boolean
SphereC3<R>::
has_on_boundary(const typename SphereC3<R>::Point_3 &p) const
{
    // FIXME: it's a predicate...
  return squared_distance(center(),p) == squared_radius();
  // NB: J'ai aussi trouve ailleurs :
  // return oriented_side(p)==ON_ORIENTED_BOUNDARY;
  // a voir...
}

template < class R >
CGAL_KERNEL_INLINE
typename R::Boolean
SphereC3<R>::
has_on_negative_side(const typename SphereC3<R>::Point_3 &p) const
{
  if (orientation() == COUNTERCLOCKWISE)
    return has_on_unbounded_side(p);
  return has_on_bounded_side(p);
  // NB: J'ai aussi trouve ailleurs :
  // return oriented_side(p)==ON_NEGATIVE_SIDE;
}

template < class R >
CGAL_KERNEL_INLINE
typename R::Boolean
SphereC3<R>::
has_on_positive_side(const typename SphereC3<R>::Point_3 &p) const
{
  if (orientation() == COUNTERCLOCKWISE)
    return has_on_bounded_side(p);
  return has_on_unbounded_side(p);
  // NB: J'ai aussi trouve ailleurs :
  // return oriented_side(p)==ON_POSITIVE_SIDE;
}

template < class R >
inline
typename R::Boolean
SphereC3<R>::
has_on_bounded_side(const typename SphereC3<R>::Point_3 &p) const
{
    // FIXME: it's a predicate...
  return squared_distance(center(),p) < squared_radius();
  // NB: J'ai aussi trouve ailleurs :
  // return bounded_side(p)==ON_BOUNDED_SIDE;
}

template < class R >
inline
typename R::Boolean
SphereC3<R>::
has_on_unbounded_side(const typename SphereC3<R>::Point_3 &p) const
{
    // FIXME: it's a predicate...
  return squared_distance(center(),p) > squared_radius();
  // NB: J'ai aussi trouve ailleurs :
  // return bounded_side(p)==ON_UNBOUNDED_SIDE;
}

template < class R >
inline
typename R::Boolean
SphereC3<R>::
is_degenerate() const
{
    // FIXME: it's a predicate (?)
  return CGAL_NTS is_zero(squared_radius());
}

template < class R >
inline
typename SphereC3<R>::Sphere_3
SphereC3<R>::opposite() const
{
  return SphereC3<R>(center(), squared_radius(),
                               CGAL::opposite(orientation()) );
}

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_SPHERE_3_H
