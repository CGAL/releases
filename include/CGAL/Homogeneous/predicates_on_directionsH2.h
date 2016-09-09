// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.4
// release_date  : 2002, May 16
// 
// file          : include/CGAL/Homogeneous/predicates_on_directionsH2.h
// package       : H2 (2.67)
// revision      : $Revision: 1.1 $
// revision_date : $Date: 2001/10/16 16:02:30 $
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

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
