// Copyright (c) 1999  Utrecht University (The Netherlands),
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
// $Source: /CVSROOT/CGAL/Packages/H2/include/CGAL/Homogeneous/predicates_on_directionsH2.h,v $
// $Revision: 1.4 $ $Date: 2003/10/21 12:16:14 $
// $Name: current_submission $
//
// Author(s)     : Stefan Schirra
 

#ifndef CGAL_PREDICATES_ON_DIRECTIONSH2_H
#define CGAL_PREDICATES_ON_DIRECTIONSH2_H

#include <CGAL/Homogeneous/PointH2.h>
#include <CGAL/Homogeneous/VectorH2.h>
#include <CGAL/Homogeneous/DirectionH2.h>
#include <CGAL/Homogeneous/predicates_on_pointsH2.h>

CGAL_BEGIN_NAMESPACE

template < class R >
CGAL_KERNEL_LARGE_INLINE
Comparison_result
compare_angle_with_x_axis(const DirectionH2<R>& d1,
                          const DirectionH2<R>& d2)
{
  typedef typename R::RT  RT;
  CGAL_kernel_precondition(
        static_cast<int>(COUNTERCLOCKWISE) == static_cast<int>(LARGER)
     && static_cast<int>(COLLINEAR)        == static_cast<int>(EQUAL)
     && static_cast<int>(CLOCKWISE)        == static_cast<int>(SMALLER) );

  const RT RT0(0);

  VectorH2<R> dirvec1(d1.x(), d1.y());      // Added
  PointH2<R>   p1 = CGAL::ORIGIN + dirvec1; // Added
  VectorH2<R> dirvec2(d2.x(), d2.y());      // Added
  PointH2<R>   p2 = ORIGIN + dirvec2;       // Added
//  PointH2<R>   p1 = ORIGIN + d1.vector(); // Commented out
//  PointH2<R>   p2 = ORIGIN + d2.vector(); // Commented out

  CGAL_kernel_precondition( RT0 < p1.hw() );
  CGAL_kernel_precondition( RT0 < p2.hw() );

  int       x_sign1 = static_cast<int>(CGAL_NTS sign( p1.hx() ));
  int       x_sign2 = static_cast<int>(CGAL_NTS sign( p2.hx() ));
  int       y_sign1 = static_cast<int>(CGAL_NTS sign( p1.hy() ));
  int       y_sign2 = static_cast<int>(CGAL_NTS sign( p2.hy() ));

  if ( y_sign1 * y_sign2 < 0)
  {
      return (0 < y_sign1 ) ? SMALLER : LARGER;
  }

  PointH2<R>   origin( RT0  , RT0   );

  if ( 0 < y_sign1 * y_sign2 )
  {
      return static_cast<Comparison_result>(static_cast<int>(
		  orientation(origin, p2, p1)));

      // Precondition on the enums:
      // COUNTERCLOCKWISE == LARGER   ( ==  1 )
      // COLLINEAR        == EQUAL    ( ==  0 )
      // CLOCKWISE        == SMALLER  ( == -1 )
  }

  // ( y_sign1 * y_sign2 == 0 )

  bool b1 = (y_sign1 == 0) && (x_sign1 >= 0);
  bool b2 = (y_sign2 == 0) && (x_sign2 >= 0);

  if ( b1 ) { return  b2 ? EQUAL : SMALLER; }
  if ( b2 ) { return  b1 ? EQUAL : LARGER; }
  if ( y_sign1 == y_sign2 )  // == 0
  {
      return EQUAL;
  }
  else
  {
      return (orientation(origin, p1, p2) == COUNTERCLOCKWISE) ?
                                   static_cast<Comparison_result>(SMALLER) :
                                   static_cast<Comparison_result>(LARGER);
  }
}

CGAL_END_NAMESPACE

#endif // CGAL_PREDICATES_ON_DIRECTIONSH2_H
