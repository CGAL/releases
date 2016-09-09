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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// release       : CGAL-1.1
// release_date  : 1998, July 24
//
// file          : include/CGAL/dd_geo/chull_traits_3.h
// package       : Convex_hull_3 (1.1.3)
// source        : chull_traits.lw
// revision      : 1.1.3
// revision_date : 23 Jul 1998
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_CHULL_TRAITS_3_H
#define CGAL_CHULL_TRAITS_3_H

#include <CGAL/Point_3.h>
#include <CGAL/Vector_3.h>
#include <CGAL/Plane_3.h>
#include <CGAL/Ray_3.h>
#include <CGAL/Triangle_3.h>
#include <CGAL/Tetrahedron_3.h>
#include <CGAL/predicates_on_points_3.h>
#include <LEDA/array.h>

template <class _R>
class CGAL_chull_traits_3
{
  public:
    typedef _R                                     R;
    typedef typename _R::RT                        RT;
    typedef CGAL_Point_3<_R>                       POINT;
    typedef POINT                                  IPOINT;
    typedef CGAL_Plane_3<_R>                       PLANE;
    typedef CGAL_Vector_3<_R>                      VECTOR;
    typedef CGAL_Ray_3<_R>                         IRAY;

  static int
    side(const CGAL_Plane_3<_R>& pl, 
         const CGAL_Point_3<_R>& p)
    { return (int)pl.oriented_side(p); }

  static bool
    affinely_independent(const leda_array<CGAL_Point_3<_R> >& A)
    {
      int a = A.size();
      if (a > 4)
          return false;
      if (a == 4) 
          return !CGAL_coplanar( A[0], A[1], A[2], A[3] );
      if (a == 3) 
          return !CGAL_collinear( A[0], A[1], A[2] );
      if (a == 2)
          return (A[0] != A[1] );  
      return true;
    }
    
  static bool
    contained_in_simplex(const leda_array<CGAL_Point_3<_R> >& A,
                         const CGAL_Point_3<_R> p)
    {
      int a = A.size();
      CGAL_assertion( a <= 4 );
      if (a == 4)
      {
          CGAL_Tetrahedron_3<_R> t( A[0], A[1], A[2], A[3] );
          return !t.has_on_unbounded_side(p);
      }
      if (a == 3)
      {
          CGAL_Triangle_3<_R> t( A[0], A[1], A[2] );
          return t.has_on(p);
      }
      if (a == 2)
      {
          CGAL_Segment_3<_R> s( A[0], A[1] );
          return s.has_on(p);
      }
      if (a == 1)
      {
          return ( A[0] == p);
      }
      return false; // should be unreachable !
    }
    
  static bool
    contained_in_affine_hull(const leda_array<CGAL_Point_3<_R> >& A,
                             const CGAL_Point_3<_R> p)
    {
      int a = A.size();
      CGAL_assertion( affinely_independent(A) );
      if (a == 3)
          return CGAL_coplanar( p, A[0], A[1], A[2] );
      if (a == 2)
          return CGAL_collinear( p, A[0], A[1] );
      if (a == 1)
          return ( p == A[0] );
      return false;
    }
    
  static CGAL_Vector_3<_R>
    normal(const CGAL_Plane_3<_R>& pl)
    { return pl.orthogonal_vector(); }

  static CGAL_Vector_3<_R>
    to_vector(const CGAL_Point_3<_R>& p)
    { return p - CGAL_ORIGIN; }

  static CGAL_Vector_3<_R>
    zero_vector(int i)
    { 
      CGAL_assertion( i == 3 );
      return CGAL_Vector_3<_R>(RT(0),RT(0),RT(0)); 
    }

  static CGAL_Point_3<_R>
    to_ipoint(const CGAL_Vector_3<_R>& v)
    { return CGAL_ORIGIN + v; }

  static CGAL_Plane_3<_R>
    hyperplane_through_points(const leda_array<CGAL_Point_3<_R> >& A,
                              const CGAL_Point_3<_R>& p,
                              int side)
    {
      int a = A.size();
      CGAL_assertion( a <= 3 );
      CGAL_Plane_3<_R> pl;
      if (a == 3)
      {
         pl = CGAL_Plane_3<_R>( A[0], A[1], A[2] );
      }
      if (a == 2)
      {
         CGAL_Point_3<_R> hp =
              A[0] + CGAL_cross_product( p - A[0], A[1] - A[0] );
         pl = CGAL_Plane_3<_R>( A[0], A[1], hp );
      }
      if (a == 1)
      {
          pl = CGAL_Plane_3<_R>( A[0], A[0] - p);
      }
      if (side != 0)
      {
          if ( (int)pl.oriented_side(p) !=  side ) { pl = pl.opposite(); }
      }
      return pl;
    }

  static bool
    intersection(const CGAL_Plane_3<_R>& pl, 
                 const CGAL_Ray_3<_R>& r,
                 CGAL_Point_3<_R>& ip)
    {
      CGAL_Object res = CGAL_intersection(pl, r);
      return CGAL_assign(ip, res);
    }

  static int
    orientation( const CGAL_Point_3<_R>& p1, 
                 const CGAL_Point_3<_R>& p2,
                 const CGAL_Point_3<_R>& p3, 
                 const CGAL_Point_3<_R>& p4)
    { return (int)CGAL_orientation(p1,p2,p3,p4); }
};

#endif // CGAL_CHULL_TRAITS_3_H
