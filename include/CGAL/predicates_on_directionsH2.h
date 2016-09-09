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
// source        : geometric_predicates.fw
// file          : include/CGAL/predicates_on_directionsH2.h
// package       : H2 (1.3.1)
// revision      : 1.3.1
// revision_date : 02 Jan 1999 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_PREDICATES_ON_DIRECTIONSH2_H
#define CGAL_PREDICATES_ON_DIRECTIONSH2_H

#ifndef CGAL_PVDH2_H
#include <CGAL/PVDH2.h>
#endif // CGAL_PVDH2_H
#ifndef CGAL_PREDICATES_ON_POINTSH2_H
#include <CGAL/predicates_on_pointsH2.h>
#endif // CGAL_PREDICATES_ON_POINTSH2_H

template <class FT, class RT>
CGAL_KERNEL_LARGE_INLINE
CGAL_Comparison_result
CGAL_compare_angles_with_x_axis(const CGAL_DirectionH2<FT,RT>& d1,
                                const CGAL_DirectionH2<FT,RT>& d2)
{
  CGAL_kernel_precondition( (
        (CGAL_Comparison_result)CGAL_COUNTERCLOCKWISE == CGAL_LARGER
      &&(CGAL_Comparison_result)CGAL_COLLINEAR        == CGAL_EQUAL
      &&(CGAL_Comparison_result)CGAL_CLOCKWISE        == CGAL_SMALLER ) );

  const RT RT0(0);

  CGAL_PointH2<FT,RT>   p1 = CGAL_ORIGIN + d1.vector();
  CGAL_PointH2<FT,RT>   p2 = CGAL_ORIGIN + d2.vector();

  CGAL_kernel_precondition( RT0 < p1.hw() );
  CGAL_kernel_precondition( RT0 < p2.hw() );

  int       x_sign1 = (int)CGAL_sign( p1.hx() );
  int       x_sign2 = (int)CGAL_sign( p2.hx() );
  int       y_sign1 = (int)CGAL_sign( p1.hy() );
  int       y_sign2 = (int)CGAL_sign( p2.hy() );

  if ( y_sign1 * y_sign2 < 0)
  {
      return (0 < y_sign1 ) ? CGAL_SMALLER : CGAL_LARGER;
  }

  CGAL_PointH2<FT,RT>   origin( RT0  , RT0   );

  if ( 0 < y_sign1 * y_sign2 )
  {
      return ( (CGAL_Comparison_result) CGAL_orientation(origin, p2, p1) );

      // Precondition on the enums:
      // CGAL_COUNTERCLOCKWISE == CGAL_LARGER   ( ==  1 )
      // CGAL_COLLINEAR        == CGAL_EQUAL    ( ==  0 )
      // CGAL_CLOCKWISE        == CGAL_SMALLER  ( == -1 )
  }

  // ( y_sign1 * y_sign2 == 0 )

  bool b1 = (y_sign1 == 0) && (x_sign1 >= 0);
  bool b2 = (y_sign2 == 0) && (x_sign2 >= 0);

  if ( b1 ) { return  b2 ? CGAL_EQUAL : CGAL_SMALLER; }
  if ( b2 ) { return  b1 ? CGAL_EQUAL : CGAL_LARGER; }
  if ( y_sign1 == y_sign2 )  // == 0
  {
      return CGAL_EQUAL;
  }
  else
  {
      return (CGAL_orientation(origin, p1, p2) == CGAL_COUNTERCLOCKWISE) ?
                                   (CGAL_Comparison_result) CGAL_SMALLER :
                                   (CGAL_Comparison_result) CGAL_LARGER;
  }
}


#endif // CGAL_PREDICATES_ON_DIRECTIONSH2_H
