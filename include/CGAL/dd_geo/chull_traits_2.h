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
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/dd_geo/chull_traits_2.h
// package       : Convex_hull_3 (1.1.3)
// source        : chull_traits.lw
// revision      : 1.1.3
// revision_date : 23 Jul 1998
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_CHULL_TRAITS_2_H
#define CGAL_CHULL_TRAITS_2_H

#include <CGAL/Point_2.h>
#include <CGAL/Vector_2.h>
#include <CGAL/Line_2.h>
#include <CGAL/Ray_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/predicates_on_points_2.h>
#include <LEDA/array.h>
#include <LEDA/point.h>

template <class _R>
class CGAL_chull_traits_2
{
  public:
    typedef _R                                     R;
    typedef typename _R::RT                        RT;
    typedef CGAL_Point_2<_R>                       POINT;
    typedef POINT                                  IPOINT;
    typedef CGAL_Line_2<_R>                        PLANE;
    typedef CGAL_Vector_2<_R>                      VECTOR;
    typedef CGAL_Ray_2<_R>                         IRAY;

  static int
    side(const CGAL_Line_2<_R>& pl, 
         const CGAL_Point_2<_R>& p)
    { return (int)pl.oriented_side(p); }

  static bool
    affinely_independent(const leda_array<CGAL_Point_2<_R> >& A)
    {
      int a = A.size();
      if (a > 3)
          return false;
      if (a == 3)
          return !CGAL_collinear( A[0], A[1], A[2] );
      if (a == 2)
          return (A[0] != A[1] );  
      return true;
    }
    
  static bool
    contained_in_simplex(const leda_array<CGAL_Point_2<_R> >& A,
                         const CGAL_Point_2<_R> p)
    {
      int a = A.size();
      CGAL_assertion( a <= 3 );
      if (a == 3)
      {
          CGAL_Triangle_2<_R> t( A[0], A[1], A[2] );
          return !t.has_on_unbounded_side(p);
      }
      if (a == 2)
      {
          CGAL_Segment_2<_R> s( A[0], A[1] );
          return s.has_on(p);
      }
      if (a == 1)
      {
          return ( A[0] == p);
      }
    }
    
  static bool
    contained_in_affine_hull(const leda_array<CGAL_Point_2<_R> >& A,
                             const CGAL_Point_2<_R> p)
    {
      int a = A.size();
      CGAL_assertion( affinely_independent(A) );
      if (a >  2)
          return true;
      if (a == 2)
          return CGAL_collinear( p, A[0], A[1] );
      if (a == 1)
          return ( p == A[0] );
      return false;
    }
    
  static CGAL_Vector_2<_R>
    normal(const CGAL_Line_2<_R>& l)
    { return CGAL_Vector_2<_R>( l.a(), l.b(), l.c() ); }

  static CGAL_Vector_2<_R>
    to_vector(const CGAL_Point_2<_R>& p)
    { return p - CGAL_ORIGIN; }

  static CGAL_Vector_2<_R>
    zero_vector(int i)
    { 
      CGAL_assertion( i == 2 );
      return CGAL_Vector_2<_R>(RT(0), RT(0) ); 
    }

  static CGAL_Point_2<_R>
    to_ipoint(const CGAL_Vector_2<_R>& v)
    { return CGAL_ORIGIN + v; }

  static CGAL_Line_2<_R>
    hyperplane_through_points(const leda_array<CGAL_Point_2<_R> >& A,
                              const CGAL_Point_2<_R>& p,
                              int side)
    {
      int a = A.size();
      CGAL_assertion( a <= 2 );
      CGAL_Line_2<_R> l;
      if (a == 2)
      {
          l = CGAL_Line_2<_R>( A[0], A[1] );
      }
      if (a == 1)
      {
          l = CGAL_Line_2<_R>( A[0], A[0] + (CGAL_ORIGIN - p) );
      }
      if (side != 0)
      {
          if ( (int)l.oriented_side(p) !=  side ) { l = l.opposite(); }
      }
      return l;
    }

  static bool
    intersection(const CGAL_Line_2<_R>& l, 
                 const CGAL_Ray_2<_R>& r,
                 CGAL_Point_2<_R>& ip)
    {
      CGAL_Object res = CGAL_intersection(l, r);
      return CGAL_assign(ip, res);
    }
  static int
    orientation( const CGAL_Point_2<_R>& p1, 
                 const CGAL_Point_2<_R>& p2,
                 const CGAL_Point_2<_R>& p3 )
    { return (int)CGAL_orientation(p1,p2,p3); }

  static leda_point
    to_d2_point( const CGAL_Point_2<_R>& p )
    {
      return leda_point( CGAL_to_double( p.x() ),
                         CGAL_to_double( p.y() ) );
    }
};

#endif // CGAL_CHULL_TRAITS_2_H
