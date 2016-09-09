// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.0
// release_date  : 1999, June 03
// 
// source        : geometric_predicates.fw
// file          : include/CGAL/predicates_on_directionsH2.h
// package       : H2 (2.1.3)
// revision      : 2.1.3
// revision_date : 21 May 1999 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_PREDICATES_ON_DIRECTIONSH2_H
#define CGAL_PREDICATES_ON_DIRECTIONSH2_H

#ifndef PVDH2_H
#include <CGAL/PVDH2.h>
#endif // PVDH2_H
#ifndef CGAL_PREDICATES_ON_POINTSH2_H
#include <CGAL/predicates_on_pointsH2.h>
#endif // CGAL_PREDICATES_ON_POINTSH2_H

CGAL_BEGIN_NAMESPACE

template <class FT, class RT>
CGAL_KERNEL_LARGE_INLINE
Comparison_result
compare_angles_with_x_axis(const DirectionH2<FT,RT>& d1,
                                const DirectionH2<FT,RT>& d2)
{
  CGAL_kernel_precondition( (
        (Comparison_result)COUNTERCLOCKWISE == LARGER
      &&(Comparison_result)COLLINEAR        == EQUAL
      &&(Comparison_result)CLOCKWISE        == SMALLER ) );

  const RT RT0(0);

  CGAL::VectorH2<FT,RT> dirvec1(d1.x(), d1.y());      // Added
  CGAL::PointH2<FT,RT>   p1 = CGAL::ORIGIN + dirvec1; // Added
  CGAL::VectorH2<FT,RT> dirvec2(d2.x(), d2.y());      // Added
  PointH2<FT,RT>   p2 = ORIGIN + dirvec2;             // Added
//  PointH2<FT,RT>   p1 = ORIGIN + d1.vector(); // Commented out
//  PointH2<FT,RT>   p2 = ORIGIN + d2.vector(); // Commented out

  CGAL_kernel_precondition( RT0 < p1.hw() );
  CGAL_kernel_precondition( RT0 < p2.hw() );

  int       x_sign1 = (int)CGAL::sign( p1.hx() );
  int       x_sign2 = (int)CGAL::sign( p2.hx() );
  int       y_sign1 = (int)CGAL::sign( p1.hy() );
  int       y_sign2 = (int)CGAL::sign( p2.hy() );

  if ( y_sign1 * y_sign2 < 0)
  {
      return (0 < y_sign1 ) ? SMALLER : LARGER;
  }

  PointH2<FT,RT>   origin( RT0  , RT0   );

  if ( 0 < y_sign1 * y_sign2 )
  {
      return ( (Comparison_result) orientation(origin, p2, p1) );

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
                                   (Comparison_result) SMALLER :
                                   (Comparison_result) LARGER;
  }
}

CGAL_END_NAMESPACE


#endif // CGAL_PREDICATES_ON_DIRECTIONSH2_H
