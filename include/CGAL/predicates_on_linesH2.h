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

// Source: predicates_on_linesH2.h
// Author: Stefan.Schirra@mpi-sb.mpg.de

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
 if ( h.b() < 0 )
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
