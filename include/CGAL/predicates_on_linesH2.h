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
// source        : predicates_on_linesH2.fw
// file          : include/CGAL/predicates_on_linesH2.h
// package       : H2 (2.1.3)
// revision      : 2.1.3
// revision_date : 21 May 1999 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
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

CGAL_BEGIN_NAMESPACE


template <class FT, class RT>
CGAL_KERNEL_INLINE
Comparison_result
compare_x(const PointH2<FT,RT> &p,
               const LineH2<FT,RT> &l1,
               const LineH2<FT,RT> &l2)
{
  PointH2<FT,RT> ip = gp_linear_intersection( l1, l2 );
  return compare_x( p, ip );
}


template <class FT, class RT>
CGAL_KERNEL_INLINE
Comparison_result
compare_x(const LineH2<FT,RT> &l1,
               const LineH2<FT,RT> &l2,
               const LineH2<FT,RT> &h1,
               const LineH2<FT,RT> &h2)
{
  PointH2<FT,RT> lip = gp_linear_intersection( l1, l2 );
  PointH2<FT,RT> hip = gp_linear_intersection( h1, h2 );
  return compare_x( lip, hip );
}
template <class FT, class RT>
CGAL_KERNEL_INLINE
Comparison_result
compare_y(const PointH2<FT,RT> &p,
               const LineH2<FT,RT> &l1,
               const LineH2<FT,RT> &l2)
{
  PointH2<FT,RT> ip = gp_linear_intersection( l1, l2 );
  return compare_y( p, ip );
}


template <class FT, class RT>
CGAL_KERNEL_INLINE
Comparison_result
compare_y(const LineH2<FT,RT> &l1,
               const LineH2<FT,RT> &l2,
               const LineH2<FT,RT> &h1,
               const LineH2<FT,RT> &h2)
{
  PointH2<FT,RT> lip = gp_linear_intersection( l1, l2 );
  PointH2<FT,RT> hip = gp_linear_intersection( h1, h2 );
  return compare_y( lip, hip );
}
template <class FT, class RT>
CGAL_KERNEL_MEDIUM_INLINE
Comparison_result
compare_y_at_x(const PointH2<FT,RT> &p,
                    const LineH2<FT,RT> &h)
{
  CGAL_kernel_precondition( ! h.is_vertical() );
  Oriented_side ors = h.oriented_side( p );
  if ( h.b() < RT(0) )
  {
      ors = opposite( ors );
  }
  if ( ors == ON_POSITIVE_SIDE )
  {
      return LARGER;
  }
  return ( ors == ON_NEGATIVE_SIDE ) ? SMALLER : EQUAL;
}

template <class FT, class RT>
CGAL_KERNEL_INLINE
Comparison_result
compare_y_at_x(const PointH2<FT,RT> &p,
                    const LineH2<FT,RT> &h1,
                    const LineH2<FT,RT> &h2)
{ return CGAL::compare(h1.y_at_x( p.x() ), h2.y_at_x( p.x() )); }


template <class FT, class RT>
CGAL_KERNEL_INLINE
Comparison_result
compare_y_at_x(const LineH2<FT,RT> &l1,
                    const LineH2<FT,RT> &l2,
                    const LineH2<FT,RT> &h)
{ return compare_y_at_x( gp_linear_intersection( l1, l2 ), h); }


template <class FT, class RT>
CGAL_KERNEL_INLINE
Comparison_result
compare_y_at_x(const LineH2<FT,RT> &l1,
                    const LineH2<FT,RT> &l2,
                    const LineH2<FT,RT> &h1,
                    const LineH2<FT,RT> &h2)
{ return compare_y_at_x( gp_linear_intersection( l1, l2 ), h1, h2 ); }

CGAL_END_NAMESPACE


#endif  // CGAL_PREDICATES_ON_LINESH2_H
