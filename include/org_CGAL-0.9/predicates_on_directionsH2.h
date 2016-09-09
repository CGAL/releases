/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/


// Source: predicates_on_directionH2.h
// Author: Stefan Schirra

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

 const RT RT0 = RT(0);

 CGAL_PointH2<FT,RT>   p1 = CGAL_ORIGIN + d1.vector();
 CGAL_PointH2<FT,RT>   p2 = CGAL_ORIGIN + d2.vector();

 CGAL_kernel_precondition( p1.hw() >  RT0   );
 CGAL_kernel_precondition( p2.hw() >  RT0   );

 int       x_sign1 = CGAL_sign( p1.hx() );
 int       x_sign2 = CGAL_sign( p2.hx() );
 int       y_sign1 = CGAL_sign( p1.hy() );
 int       y_sign2 = CGAL_sign( p2.hy() );

 if ( y_sign1 * y_sign2 < 0)
 {
    return (y_sign1 > 0) ? CGAL_SMALLER : CGAL_LARGER;
 }

 CGAL_PointH2<FT,RT>   origin( RT0  , RT0   );

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
