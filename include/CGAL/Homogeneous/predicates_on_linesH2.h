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
// file          : include/CGAL/Homogeneous/predicates_on_linesH2.h
// package       : H2 (2.67)
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2002/01/07 17:45:13 $
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 
#ifndef CGAL_PREDICATES_ON_LINESH2_H
#define CGAL_PREDICATES_ON_LINESH2_H

#include <CGAL/Homogeneous/PointH2.h>
#include <CGAL/Homogeneous/LineH2.h>
#include <CGAL/Homogeneous/predicates_on_pointsH2.h>
#include <CGAL/Homogeneous/basic_constructionsH2.h>

CGAL_BEGIN_NAMESPACE

template <class R>
CGAL_KERNEL_INLINE
Comparison_result
compare_x(const PointH2<R>& p,
          const LineH2<R>& l1,
          const LineH2<R>& l2)
{
  PointH2<R> ip = gp_linear_intersection( l1, l2 );
  return compare_x( p, ip );
}

template <class R>
CGAL_KERNEL_INLINE
Comparison_result
compare_x(const LineH2<R>& l1,
          const LineH2<R>& l2,
          const LineH2<R>& h1,
          const LineH2<R>& h2)
{
  PointH2<R> lip = gp_linear_intersection( l1, l2 );
  PointH2<R> hip = gp_linear_intersection( h1, h2 );
  return compare_x( lip, hip );
}

template < class R >
inline
Comparison_result
compare_x(const Line_2<R> &l,
	  const Line_2<R> &h1,
	  const Line_2<R> &h2)
{
    return compare_x(l, h1, l, h2);
}

template <class R>
CGAL_KERNEL_INLINE
Comparison_result
compare_y(const PointH2<R>& p,
          const LineH2<R>& l1,
          const LineH2<R>& l2)
{
  PointH2<R> ip = gp_linear_intersection( l1, l2 );
  return compare_y( p, ip );
}

template <class R>
CGAL_KERNEL_INLINE
Comparison_result
compare_y(const LineH2<R>& l1,
          const LineH2<R>& l2,
          const LineH2<R>& h1,
          const LineH2<R>& h2)
{
  PointH2<R> lip = gp_linear_intersection( l1, l2 );
  PointH2<R> hip = gp_linear_intersection( h1, h2 );
  return compare_y( lip, hip );
}

template < class R >
inline
Comparison_result
compare_y(const Line_2<R> &l,
	  const Line_2<R> &h1,
	  const Line_2<R> &h2)
{
    return compare_y(l, h1, l, h2);
}

template <class R>
CGAL_KERNEL_MEDIUM_INLINE
Comparison_result
compare_y_at_x(const PointH2<R>& p,
               const LineH2<R>& h)
{
  typedef typename R::RT RT;
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

template <class R>
CGAL_KERNEL_INLINE
Comparison_result
compare_y_at_x(const PointH2<R>& p,
               const LineH2<R>& h1,
               const LineH2<R>& h2)
{ return CGAL_NTS compare(h1.y_at_x( p.x() ), h2.y_at_x( p.x() )); }

template <class R>
CGAL_KERNEL_INLINE
Comparison_result
compare_y_at_x(const LineH2<R>& l1,
               const LineH2<R>& l2,
               const LineH2<R>& h)
{ return compare_y_at_x( gp_linear_intersection( l1, l2 ), h); }

template <class R>
CGAL_KERNEL_INLINE
Comparison_result
compare_y_at_x(const LineH2<R>& l1,
               const LineH2<R>& l2,
               const LineH2<R>& h1,
               const LineH2<R>& h2)
{ return compare_y_at_x( gp_linear_intersection( l1, l2 ), h1, h2 ); }

template <class R>
CGAL_KERNEL_MEDIUM_INLINE
Comparison_result
compare_x_at_y(const PointH2<R>& p,
               const LineH2<R>& h)
{
  typedef typename R::RT RT;
  CGAL_kernel_precondition( ! h.is_horizontal() );
  Oriented_side ors = h.oriented_side( p );
  if ( h.a() < RT(0) )
  {
      ors = opposite( ors );
  }
  if ( ors == ON_POSITIVE_SIDE )
  {
      return LARGER;
  }
  return ( ors == ON_NEGATIVE_SIDE ) ? SMALLER : EQUAL;
}

template <class R>
CGAL_KERNEL_INLINE
Comparison_result
compare_x_at_y(const PointH2<R>& p,
               const LineH2<R>& h1,
               const LineH2<R>& h2)
{ return CGAL_NTS compare(h1.x_at_y( p.y() ), h2.x_at_y( p.y() )); }


template <class R>
CGAL_KERNEL_INLINE
Comparison_result
compare_x_at_y(const LineH2<R>& l1,
               const LineH2<R>& l2,
               const LineH2<R>& h)
{ return compare_x_at_y( gp_linear_intersection( l1, l2 ), h); }

template <class R>
CGAL_KERNEL_INLINE
Comparison_result
compare_x_at_y(const LineH2<R>& l1,
               const LineH2<R>& l2,
               const LineH2<R>& h1,
               const LineH2<R>& h2)
{ return compare_x_at_y( gp_linear_intersection( l1, l2 ), h1, h2 ); }

template <class R>
CGAL_KERNEL_MEDIUM_INLINE
Comparison_result
compare_slopes(const LineH2<R>& l1, const LineH2<R>& l2)
{
   if (l1.is_horizontal())
     return l2.is_vertical() ? 
         SMALLER : Comparison_result(CGAL_NTS sign(l2.a() * l2.b()));
   if (l2.is_horizontal()) 
     return l1.is_vertical() ? 
         LARGER : Comparison_result(- CGAL_NTS sign(l1.a() * l1.b()));
   if (l1.is_vertical()) return l2.is_vertical() ? EQUAL : LARGER;
   if (l2.is_vertical()) return SMALLER;
   int l1_sign = CGAL_NTS sign(-l1.a() * l1.b());
   int l2_sign = CGAL_NTS sign(-l2.a() * l2.b());

   if (l1_sign < l2_sign) return SMALLER;
   if (l1_sign > l2_sign) return LARGER;

   if (l1_sign > 0)
     return Comparison_result(
             CGAL_NTS sign ( CGAL_NTS abs(l1.a() * l2.b()) -
                             CGAL_NTS abs(l2.a() * l1.b()) ) );

   return Comparison_result(
            CGAL_NTS sign ( CGAL_NTS abs(l2.a() * l1.b()) -
                            CGAL_NTS abs(l1.a() * l2.b()) ) );
}

CGAL_END_NAMESPACE

#endif  // CGAL_PREDICATES_ON_LINESH2_H
