
//  Copyright CGAL 1996
//
//  cgal@cs.ruu.nl
//
//  This file is part of an internal release of the CGAL kernel.
//  The code herein may be used and/or copied only in accordance
//  with the terms and conditions stipulated in the agreement
//  under which the code has been supplied or with the written
//  permission of the CGAL Project.
//
//  Look at http://www.cs.ruu.nl/CGAL/ for more information.
//  Please send any bug reports and comments to cgal@cs.ruu.nl
//
//  The code comes WITHOUT ANY WARRANTY; without even the implied
//  warranty of FITNESS FOR A PARTICULAR PURPOSE.
//


// Source: predicates_on_directionH2.h
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL_PREDICATES_ON_DIRECTIONSH2_H
#define CGAL_PREDICATES_ON_DIRECTIONSH2_H

#include <CGAL/PVDH2.h>
#include <CGAL/predicates_on_pointsH2.h>

template <class FT, class RT>
CGAL_Comparison_result
CGAL_compare_angles_with_x_axis(const CGAL_DirectionH2<FT,RT>& d1,
                                const CGAL_DirectionH2<FT,RT>& d2)
{
 CGAL_kernel_precondition( (
        (CGAL_Comparison_result)CGAL_COUNTERCLOCKWISE == CGAL_LARGER
      &&(CGAL_Comparison_result)CGAL_COLLINEAR        == CGAL_EQUAL
      &&(CGAL_Comparison_result)CGAL_CLOCKWISE        == CGAL_SMALLER ) );

 CGAL_PointH2<FT,RT>   p1 = CGAL_ORIGIN + d1.vector();
 CGAL_PointH2<FT,RT>   p2 = CGAL_ORIGIN + d2.vector();

 CGAL_kernel_precondition( p1.hw() >  RT(0)   );
 CGAL_kernel_precondition( p2.hw() >  RT(0)   );

 int       x_sign1 = CGAL_sign( p1.hx() );
 int       x_sign2 = CGAL_sign( p2.hx() );
 int       y_sign1 = CGAL_sign( p1.hy() );
 int       y_sign2 = CGAL_sign( p2.hy() );

 if ( y_sign1 * y_sign2 < 0)
 {
    return (y_sign1 > 0) ? CGAL_SMALLER : CGAL_LARGER;
 }

 CGAL_PointH2<FT,RT>   origin( RT(0)  , RT(0)   );

 if ( y_sign1 * y_sign2 > 0)
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

 if ( b1 )
 {
    return  b2 ? CGAL_EQUAL : CGAL_SMALLER;
 }
 if ( b2 )
 {
    return  b1 ? CGAL_EQUAL : CGAL_LARGER;
 }
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
