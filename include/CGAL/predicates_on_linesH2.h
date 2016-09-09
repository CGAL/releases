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
// source        : predicates_on_linesH2.fw
// file          : include/CGAL/predicates_on_linesH2.h
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


#ifndef CGAL_PREDICATES_ON_LINESH2_H
#define CGAL_PREDICATES_ON_LINESH2_H

#ifndef CGAL_POINTH2_H
#include <CGAL/PointH2.h>
#endif // CGAL_POINTH2_H
#ifndef CGAL_LINEH2_H
#include <CGAL/LineH2.h>
#endif // CGAL_LINEH2_H
#ifndef CGAL_PREDICATES_ON_POINTSH2_H
#include <CGAL/predicates_on_pointsH2.h>
#endif // CGAL_PREDICATES_ON_POINTSH2_H
#ifndef CGAL_BASIC_CONSTRUCTIONSH2_H
#include <CGAL/basic_constructionsH2.h>
#endif // CGAL_BASIC_CONSTRUCTIONSH2_H


template <class FT, class RT>
CGAL_KERNEL_INLINE
CGAL_Comparison_result
CGAL_compare_x(const CGAL_PointH2<FT,RT> &p,
               const CGAL_LineH2<FT,RT> &l1,
               const CGAL_LineH2<FT,RT> &l2)
{
  CGAL_PointH2<FT,RT> ip = CGAL_gp_linear_intersection( l1, l2 );
  return CGAL_compare_x( p, ip );
}


template <class FT, class RT>
CGAL_KERNEL_INLINE
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
CGAL_KERNEL_INLINE
CGAL_Comparison_result
CGAL_compare_y(const CGAL_PointH2<FT,RT> &p,
               const CGAL_LineH2<FT,RT> &l1,
               const CGAL_LineH2<FT,RT> &l2)
{
  CGAL_PointH2<FT,RT> ip = CGAL_gp_linear_intersection( l1, l2 );
  return CGAL_compare_y( p, ip );
}


template <class FT, class RT>
CGAL_KERNEL_INLINE
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
CGAL_KERNEL_MEDIUM_INLINE
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
CGAL_KERNEL_INLINE
CGAL_Comparison_result
CGAL_compare_y_at_x(const CGAL_PointH2<FT,RT> &p,
                    const CGAL_LineH2<FT,RT> &h1,
                    const CGAL_LineH2<FT,RT> &h2)
{ return CGAL_compare(h1.y_at_x( p.x() ), h2.y_at_x( p.x() )); }


template <class FT, class RT>
CGAL_KERNEL_INLINE
CGAL_Comparison_result
CGAL_compare_y_at_x(const CGAL_LineH2<FT,RT> &l1,
                    const CGAL_LineH2<FT,RT> &l2,
                    const CGAL_LineH2<FT,RT> &h)
{ return CGAL_compare_y_at_x( CGAL_gp_linear_intersection( l1, l2 ), h); }


template <class FT, class RT>
CGAL_KERNEL_INLINE
CGAL_Comparison_result
CGAL_compare_y_at_x(const CGAL_LineH2<FT,RT> &l1,
                    const CGAL_LineH2<FT,RT> &l2,
                    const CGAL_LineH2<FT,RT> &h1,
                    const CGAL_LineH2<FT,RT> &h2)
{ return CGAL_compare_y_at_x( CGAL_gp_linear_intersection( l1, l2 ), h1, h2 ); }


#endif  // CGAL_PREDICATES_ON_LINESH2_H
