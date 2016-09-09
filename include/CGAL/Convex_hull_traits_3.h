// ======================================================================
//
// Copyright (c) 2001 The CGAL Consortium

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
// file          : include/CGAL/Convex_hull_traits_3.h
// package       : Convex_hull_3 (2.28)
// chapter       : Convex Hulls and Extreme Points
//
// revision      : $Revision: 1.7 $
// revision_date : $Date: 2001/07/18 15:44:35 $
//
// author(s)     : Susan Hert
//
// coordinator   : MPI (Susan Hert)
//
// implementation: 3D convex hull traits class
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CONVEX_HULL_TRAITS_3_H
#define CGAL_CONVEX_HULL_TRAITS_3_H

#include <CGAL/Polyhedron_3.h>
#include <CGAL/Convex_hull_projective_xy_traits_2.h>
#include <CGAL/Convex_hull_projective_xz_traits_2.h>
#include <CGAL/Convex_hull_projective_yz_traits_2.h>


namespace CGAL {

// without this we get an internal compiler error on bcc
#if defined(__BORLANDC__)
template <class R_, class Polyhedron_ = CGAL::Polyhedron_3<R_> >
#else
template <class R_>
#endif
class Convex_hull_traits_3 
{
 public:  
  typedef R_                                     R;
  typedef typename R::Point_3                    Point_3;
  typedef typename R::Segment_3                  Segment_3;
  typedef typename R::Triangle_3                 Triangle_3;
  typedef typename R::Plane_3                    Plane_3;
  typedef typename R::Vector_3                   Vector_3;

#if defined(__BORLANDC__)
  typedef Polyhedron_                            Polyhedron_3;
#else
  typedef Polyhedron_3<R>                        Polyhedron_3;
#endif

  typedef typename R::Construct_segment_3        Construct_segment_3;
  typedef typename R::Construct_ray_3            Construct_ray_3;
  typedef typename R::Construct_plane_3          Construct_plane_3;
  typedef typename R::Construct_vector_3         Construct_vector_3;
  typedef typename R::Construct_triangle_3       Construct_triangle_3;
  typedef typename R::Construct_centroid_3       Construct_centroid_3;
  typedef typename R::Construct_orthogonal_vector_3
                                                 Construct_orthogonal_vector_3;

  typedef typename R::Collinear_3                Collinear_3;
  typedef typename R::Coplanar_3                 Coplanar_3;
  typedef typename R::Less_distance_to_point_3   Less_distance_to_point_3;
  typedef typename R::Has_on_positive_side_3     Has_on_positive_side_3;

  typedef typename R::Less_signed_distance_to_plane_3
                                               Less_signed_distance_to_plane_3;

  // required for degenerate case of all points coplanar
  typedef Convex_hull_projective_xy_traits_2<Point_3>  Traits_xy;
  typedef Convex_hull_projective_xz_traits_2<Point_3>  Traits_xz;
  typedef Convex_hull_projective_yz_traits_2<Point_3>  Traits_yz;

  // for postcondition checking 
  typedef typename R::Ray_3                      Ray_3; 

  typedef typename R::Has_on_3                   Has_on_3;
  typedef typename R::Oriented_side_3            Oriented_side_3;
  typedef typename R::Intersect_3                Intersect_3;

  Construct_segment_3
  construct_segment_3_object() const
  { return Construct_segment_3(); }

  Construct_ray_3
  construct_ray_3_object() const
  { return Construct_ray_3(); }

  Construct_plane_3
  construct_plane_3_object() const
  { return Construct_plane_3(); }

  Construct_triangle_3
  construct_triangle_3_object() const
  { return Construct_triangle_3(); }

  Construct_vector_3
  construct_vector_3_object() const
  { return Construct_vector_3(); }

  Construct_centroid_3  
  construct_centroid_3_object() const
  { return Construct_centroid_3(); }

  Construct_orthogonal_vector_3
  construct_orthogonal_vector_3_object() const
  { return Construct_orthogonal_vector_3(); }

  Collinear_3
  collinear_3_object() const
  { return Collinear_3(); }

  Coplanar_3
  coplanar_3_object() const
  { return Coplanar_3(); }
 
  Has_on_3
  has_on_3_object() const
  { return Has_on_3(); }

  Less_distance_to_point_3
  less_distance_to_point_3_object() const
  { return Less_distance_to_point_3(); }

  Has_on_positive_side_3
  has_on_positive_side_3_object() const
  { return Has_on_positive_side_3(); }

  Oriented_side_3
  oriented_side_3_object() const
  { return Oriented_side_3(); }

  Intersect_3
  intersect_3_object() const
  { return Intersect_3(); }

  Less_signed_distance_to_plane_3  
  less_signed_distance_to_plane_3_object() const
  { return Less_signed_distance_to_plane_3(); }
};

} // namespace CGAL

#endif // CGAL_CONVEX_HULL_TRAITS_3_H


