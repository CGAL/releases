// ======================================================================
//
// Copyright (c) 1997-2000 The CGAL Consortium

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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/Convex_hull_d_traits_3.h
// package       : Kernel_d (0.9.47)
// chapter       : Basic
//
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2001/06/28 09:32:16 $
//
// author(s)     : Michael Seel
// coordinator   : Susan Hert
//
// implementation: D3 kernel traits for Convex_hull_d
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CONVEX_HULL_D_TRAITS_3_H
#define CONVEX_HULL_D_TRAITS_3_H

#include <CGAL/Point_3.h>
#include <CGAL/Vector_3.h>
#include <CGAL/Plane_3.h>
#include <CGAL/Ray_3.h>
#include <CGAL/Triangle_3.h>
#include <CGAL/Tetrahedron_3.h>
#include <CGAL/predicates_on_points_3.h>
#include <CGAL/intersection_3.h>
#include <vector>

CGAL_BEGIN_NAMESPACE

#if defined(_MSC_VER) || defined(__BORLANDC__) 
#define CGAL_SIMPLE_INTERFACE
#endif

template <class R_> struct Convex_hull_d_traits_3
{
    typedef R_                    R;
    typedef typename R_::RT       RT;
    typedef typename R_::FT       FT;
    typedef typename R_::Point_3  Point_d;
    typedef typename R_::Plane_3  Hyperplane_d;
    typedef typename R_::Vector_3 Vector_d;
    typedef typename R_::Ray_3    Ray_d;

  typedef typename R::Oriented_side_3 Oriented_side_d;
  Oriented_side_d oriented_side_d_object() const
  { return Oriented_side_d(); }

  typedef typename R::Has_on_positive_side_3 Has_on_positive_side_d;
  Has_on_positive_side_d has_on_positive_side_d_object() const
  { return Has_on_positive_side_d(); }

  struct Orientation_d {
    template <class I>
    Orientation operator()(I s, I e) {
#ifndef CGAL_SIMPLE_INTERFACE
      std::vector<Point_d> A(s,e);
#else
      std::vector<Point_d> A; while (s!=e) A.push_back(*s++);
#endif
      CGAL_assertion(A.size()==4);
      return orientation(A[0],A[1],A[2],A[3]);
    }
  };
  Orientation_d orientation_d_object() const
  { return Orientation_d(); }

  struct Affinely_independent_d {
    template <class I>
    bool operator()(I s, I e)
    { 
#ifndef CGAL_SIMPLE_INTERFACE
      std::vector<Point_d> A(s,e);
#else
      std::vector<Point_d> A; while (s!=e) A.push_back(*s++);
#endif
      int a = A.size();
      if (a > 4)
        return false;
      if (a == 4) 
        return !coplanar( A[0], A[1], A[2], A[3] );
      if (a == 3) 
        return !collinear( A[0], A[1], A[2] );
      if (a == 2)
        return (A[0] != A[1] );  
      return true;
    }
  };
  Affinely_independent_d affinely_independent_d_object() const
  { return Affinely_independent_d(); }

  struct Contained_in_simplex_d {
    template <class I>
    bool operator()(I s, I e, const Point_d& p)
    { 
#ifndef CGAL_SIMPLE_INTERFACE
      std::vector<Point_d> A(s,e);
#else
      std::vector<Point_d> A; while (s!=e) A.push_back(*s++);
#endif
      int a = A.size();
      CGAL_assertion( a <= 4 );
      if (a == 4) {
        Tetrahedron_3<R_> t( A[0], A[1], A[2], A[3] );
        return !t.has_on_unbounded_side(p);
      } else if (a == 3) {
        Triangle_3<R_> t( A[0], A[1], A[2] );
        return t.has_on(p);
      } else if (a == 2) {
        Segment_3<R_> s( A[0], A[1] );
        return s.has_on(p);
      } else if (a == 1) {
        return ( A[0] == p);
      } 
      return false; // should be unreachable !
    }
  };
  Contained_in_simplex_d contained_in_simplex_d_object() const
  { return Contained_in_simplex_d(); }
 
  struct Contained_in_affine_hull_d {
    template <class I>
    bool operator()(I s, I e, const Point_d& p)
    { 
#ifndef CGAL_SIMPLE_INTERFACE
      std::vector<Point_d> A(s,e);
#else
      std::vector<Point_d> A; while (s!=e) A.push_back(*s++);
#endif
      int a = A.size();
      Affinely_independent_d affinely_independent;
      CGAL_assertion( affinely_independent(s,e) );
      if (a == 3)
        return coplanar( p, A[0], A[1], A[2] );
      if (a == 2)
        return collinear( p, A[0], A[1] );
      if (a == 1)
        return ( p == A[0] );
      return false;
    }
  };
  Contained_in_affine_hull_d contained_in_affine_hull_d_object() const
  { return Contained_in_affine_hull_d(); }

  struct Component_accessor_d {
    template <typename C>
    int dimension(const C& c) const { return c.dimension(); }
    template <typename C>
    RT homogeneous(const C& c, int i) { return c.homogeneous(i); }
    template <typename C>
    FT cartesian(const C& c, int i) { return c.cartesian(i); }
  };
  Component_accessor_d component_accessor_d_object() const
  { return Component_accessor_d(); }

  struct Orthogonal_vector_d {
    Vector_d operator()(const Hyperplane_d& h) const
    { return h.orthogonal_vector(); }
  };
  Orthogonal_vector_d orthogonal_vector_d_object() const
  { return Orthogonal_vector_d(); }

  struct Point_to_vector_d {
    Vector_d operator()(const Point_d& p) const
    { return p-CGAL::ORIGIN; }
  };
  Point_to_vector_d point_to_vector_d_object() const
  { return Point_to_vector_d(); }

  struct Vector_to_point_d {
    Point_d operator()(const Vector_d& v) const
    { return CGAL::ORIGIN+v; }
  };
  Vector_to_point_d vector_to_point_d_object() const
  { return Vector_to_point_d(); }

  struct Construct_vector_d {
    Vector_d operator()(int, Null_vector) const
    { return Vector_d(NULL_VECTOR); }
  };
  Construct_vector_d construct_vector_d_object() const
  { return Construct_vector_d(); }

  struct Construct_hyperplane_d {
    template <class I>
    Hyperplane_d operator()(I s, I e, const Point_d& p, 
                            Oriented_side side)
    { 
#ifndef CGAL_SIMPLE_INTERFACE
      std::vector<Point_d> A(s,e);
#else
      std::vector<Point_d> A; while (s!=e) A.push_back(*s++);
#endif
      int a = A.size(); CGAL_assertion( a <= 3 );
      Plane_3<R_> pl;
      if (a == 3) {
        pl = Plane_3<R_>( A[0], A[1], A[2] );
      }
      if (a == 2) {
        Point_3<R_> hp =
              A[0] + cross_product( p - A[0], A[1] - A[0] );
        pl = Plane_3<R_>( A[0], A[1], hp );
      }
      if (a == 1) {
        pl = Plane_3<R_>( A[0], A[0] - p);
      }
      if (side != 0) {
        if ( pl.oriented_side(p) !=  side ) { pl = pl.opposite(); }
      }
      return pl;
    }
  };
  Construct_hyperplane_d construct_hyperplane_d_object() const
  { return Construct_hyperplane_d(); }

  typedef typename R::Intersect_2 Intersect_d;
  Intersect_d intersect_d_object() const 
  { return Intersect_d(); }

};

CGAL_END_NAMESPACE

#endif //CONVEX_HULL_D_TRAITS_3_H


