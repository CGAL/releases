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


// Source: predicates_on_linesH2.h
// Author: Stefan Schirra

#ifndef CGAL_PREDICATES_ON_LINESH2_H
#define CGAL_PREDICATES_ON_LINESH2_H

#include <CGAL/PointH2.h>
#include <CGAL/LineH2.h>
#include <CGAL/predicates_on_pointsH2.h>


template <class FT, class RT>
CGAL_Comparison_result
CGAL_compare_x(const CGAL_PointH2<FT,RT> &p,
               const CGAL_LineH2<FT,RT> &l1,
               const CGAL_LineH2<FT,RT> &l2)
{
 CGAL_PointH2<FT,RT> ip = CGAL_gp_linear_intersection( l1, l2 );
 return CGAL_compare_x( p, ip );
}


template <class FT, class RT>
CGAL_Comparison_result
CGAL_compare_x(const CGAL_LineH2<FT,RT> &l1,
               const CGAL_LineH2<FT,RT> &l2,
               const CGAL_LineH2<FT,RT> &h1,
               const CGAL_LineH2<FT,RT> &h2)
{
 CGAL_PointH2<FT,RT> lip = CGAL_gp_linear_intersection( l1, l2 );
 CGAL_PointH2<FT,RT> hip = CGAL_gp_linear_intersection( h1, h2 );
 return CGAL_compare_x( lip, hip );
}


template <class FT, class RT>
CGAL_Comparison_result
CGAL_compare_y(const CGAL_PointH2<FT,RT> &p,
               const CGAL_LineH2<FT,RT> &l1,
               const CGAL_LineH2<FT,RT> &l2)
{
 CGAL_PointH2<FT,RT> ip = CGAL_gp_linear_intersection( l1, l2 );
 return CGAL_compare_y( p, ip );
}


template <class FT, class RT>
CGAL_Comparison_result
CGAL_compare_y(const CGAL_LineH2<FT,RT> &l1,
               const CGAL_LineH2<FT,RT> &l2,
               const CGAL_LineH2<FT,RT> &h1,
               const CGAL_LineH2<FT,RT> &h2)
{
 CGAL_PointH2<FT,RT> lip = CGAL_gp_linear_intersection( l1, l2 );
 CGAL_PointH2<FT,RT> hip = CGAL_gp_linear_intersection( h1, h2 );
 return CGAL_compare_y( lip, hip );
}
template <class FT, class RT>
CGAL_Comparison_result
CGAL_compare_y_at_x(const CGAL_PointH2<FT,RT> &p,
                    const CGAL_LineH2<FT,RT> &h)
{
 CGAL_kernel_precondition( ! h.is_vertical() );
 CGAL_Oriented_side ors = h.oriented_side( p );
 if ( h.b() < RT(0) )
 {
    ors = CGAL_opposite( ors );
 }
 if ( ors == CGAL_ON_POSITIVE_SIDE )
 {
    return CGAL_LARGER;
 }
 return ( ors == CGAL_ON_NEGATIVE_SIDE ) ? CGAL_SMALLER : CGAL_EQUAL;
}


template <class FT, class RT>
CGAL_Comparison_result
CGAL_compare_y_at_x(const CGAL_PointH2<FT,RT> &p,
                    const CGAL_LineH2<FT,RT> &h1,
                    const CGAL_LineH2<FT,RT> &h2)
{
 return CGAL_compare(h1.y_at_x( p.x() ), h2.y_at_x( p.x() ));
}


template <class FT, class RT>
CGAL_Comparison_result
CGAL_compare_y_at_x(const CGAL_LineH2<FT,RT> &l1,
                    const CGAL_LineH2<FT,RT> &l2,
                    const CGAL_LineH2<FT,RT> &h)
{
 return CGAL_compare_y_at_x( CGAL_gp_linear_intersection( l1, l2 ), h);
}


template <class FT, class RT>
CGAL_Comparison_result
CGAL_compare_y_at_x(const CGAL_LineH2<FT,RT> &l1,
                    const CGAL_LineH2<FT,RT> &l2,
                    const CGAL_LineH2<FT,RT> &h1,
                    const CGAL_LineH2<FT,RT> &h2)
{
 return CGAL_compare_y_at_x( CGAL_gp_linear_intersection( l1, l2 ), h1, h2 );
}


#endif  // CGAL_PREDICATES_ON_LINESH2_H
