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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Cartesian_kernel/include/CGAL/Cartesian/Direction_3.h $
// $Id: Direction_3.h 49589 2009-05-26 07:54:52Z spion $
// 
//
// Author(s)     : Andreas Fabri

#ifndef CGAL_CARTESIAN_DIRECTION_3_H
#define CGAL_CARTESIAN_DIRECTION_3_H

#include <CGAL/array.h>
#include <CGAL/Handle_for.h>

CGAL_BEGIN_NAMESPACE

template < class R_ >
class DirectionC3
{
  typedef typename R_::FT                   FT;
  typedef typename R_::Vector_3             Vector_3;
  typedef typename R_::Line_3               Line_3;
  typedef typename R_::Ray_3                Ray_3;
  typedef typename R_::Segment_3            Segment_3;
  typedef typename R_::Direction_3          Direction_3;

  typedef cpp0x::array<FT, 3>               Rep;
  typedef typename R_::template Handle<Rep>::type  Base;

  Base base;

public:

  typedef R_                                R;

  DirectionC3() {}

  explicit DirectionC3(const Vector_3 &v)
    : base(CGAL::make_array(v.x(), v.y(), v.z())) {}
  // { *this = v.direction(); }

  explicit DirectionC3(const Line_3 &l)
  { *this = l.rep().direction(); }

  explicit DirectionC3(const Ray_3 &r)
  { *this = r.direction(); }

  explicit DirectionC3(const Segment_3 &s)
  { *this = s.direction(); }

  DirectionC3(const FT &x, const FT &y, const FT &z)
    : base(CGAL::make_array(x, y, z)) {}

  typename R::Boolean   operator==(const DirectionC3 &d) const;
  typename R::Boolean   operator!=(const DirectionC3 &d) const;

  Vector_3       to_vector() const;
  Vector_3       vector() const { return to_vector(); }

  const FT & dx() const
  {
      return get(base)[0];
  }
  const FT & dy() const
  {
      return get(base)[1];
  }
  const FT & dz() const
  {
      return get(base)[2];
  }

  const FT & hdx() const
  {
      return dx();
  }
  const FT & hdy() const
  {
      return dy();
  }
  const FT & hdz() const
  {
      return dz();
  }
  FT hw() const
  {
      return FT(1);
  }
};

template < class R >
inline
typename R::Boolean
DirectionC3<R>::operator==(const DirectionC3<R> &d) const
{
  if (CGAL::identical(base, d.base))
      return true;
  return equal_directionC3(dx(), dy(), dz(), d.dx(), d.dy(), d.dz());
}

template < class R >
inline
typename R::Boolean
DirectionC3<R>::operator!=(const DirectionC3<R> &d) const
{
  return !(*this == d);
}

template < class R >
inline
typename DirectionC3<R>::Vector_3
DirectionC3<R>::to_vector() const
{
  return Vector_3(dx(), dy(), dz());
}

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_DIRECTION_3_H
