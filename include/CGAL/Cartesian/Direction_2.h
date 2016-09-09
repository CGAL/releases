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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Cartesian_kernel/include/CGAL/Cartesian/Direction_2.h $
// $Id: Direction_2.h 49057 2009-04-30 14:03:52Z spion $
// 
//
// Author(s)     : Andreas Fabri, Herve Bronnimann

#ifndef CGAL_CARTESIAN_DIRECTION_2_H
#define CGAL_CARTESIAN_DIRECTION_2_H

#include <CGAL/array.h>
#include <CGAL/Handle_for.h>

CGAL_BEGIN_NAMESPACE

template < class R_ >
class DirectionC2
{
  typedef DirectionC2<R_>                   Self;
  typedef typename R_::FT                   FT;
  typedef FT                                RT;
  typedef typename R_::Point_2              Point_2;
  typedef typename R_::Vector_2             Vector_2;
  typedef typename R_::Line_2               Line_2;
  typedef typename R_::Ray_2                Ray_2;
  typedef typename R_::Segment_2            Segment_2;
  typedef typename R_::Direction_2          Direction_2;

  typedef cpp0x::array<FT, 2>               Rep;
  typedef typename R_::template Handle<Rep>::type  Base;

  Base base;

public:

  typedef R_                                     R;

  DirectionC2() {}
 
  DirectionC2(const FT &x, const FT &y)
    : base(CGAL::make_array(x, y)) {}

  bool operator==(const DirectionC2 &d) const;
  bool operator!=(const DirectionC2 &d) const;

  Vector_2 to_vector() const;

  const RT & dx() const
  {
      return get(base)[0];
  }
  const RT & dy() const
  {
      return get(base)[1];
  }
};

template < class R >
inline
bool
DirectionC2<R>::operator==(const DirectionC2<R> &d) const
{
  if (CGAL::identical(base, d.base))
      return true;
  return equal_direction(*this, d);
}

template < class R >
inline
bool
DirectionC2<R>::operator!=(const DirectionC2<R> &d) const
{
  return !( *this == d );
}


template < class R >
inline
typename DirectionC2<R>::Vector_2
DirectionC2<R>::to_vector() const
{
  return Vector_2(dx(), dy());
}

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_DIRECTION_2_H
