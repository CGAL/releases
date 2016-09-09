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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Cartesian_kernel/include/CGAL/Cartesian/Ray_2.h $
// $Id: Ray_2.h 49057 2009-04-30 14:03:52Z spion $
// 
//
// Author(s)     : Andreas Fabri, Herve Bronnimann

#ifndef CGAL_CARTESIAN_RAY_2_H
#define CGAL_CARTESIAN_RAY_2_H

#include <CGAL/array.h>

CGAL_BEGIN_NAMESPACE

template < class R_ >
class RayC2
{
  typedef typename R_::FT                   FT;
  typedef typename R_::Point_2              Point_2;
  typedef typename R_::Ray_2                Ray_2;

  typedef cpp0x::array<Point_2, 2>          Rep;
  typedef typename R_::template Handle<Rep>::type  Base;

  Base base;

public:
  typedef R_                                     R;

  RayC2() 
  {}

  RayC2(const Point_2 &sp, const Point_2 &secondp)
    : base(CGAL::make_array(sp, secondp)) 
  {}


  const Point_2&
  source() const
  {
    return get(base)[0];
  }

  const Point_2 &
  second_point() const
  {
    return get(base)[1];
  }

  typename R_::Boolean   is_degenerate() const
  {
    return source() == second_point();
  }

};

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_RAY_2_H
