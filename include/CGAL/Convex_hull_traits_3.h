// Copyright (c) 2001  Max-Planck-Institute Saarbrucken (Germany).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source: /CVSROOT/CGAL/Packages/Convex_hull_3/include/CGAL/Convex_hull_traits_3.h,v $
// $Revision: 1.11 $ $Date: 2003/09/18 10:20:28 $
// $Name: current_submission $
//
// Author(s)     : Susan Hert <hert@mpi-sb.mpg.de>

#ifndef CGAL_CONVEX_HULL_TRAITS_3_H
#define CGAL_CONVEX_HULL_TRAITS_3_H

#include <CGAL/Polyhedron_3.h>
#include <CGAL/Convex_hull_projective_xy_traits_2.h>
#include <CGAL/Convex_hull_projective_xz_traits_2.h>
#include <CGAL/Convex_hull_projective_yz_traits_2.h>


namespace CGAL {

template <class T>
class Max_coordinate_3 
{
public:

    int operator()(const T& v)
    {
      if (CGAL_NTS abs(v.x()) >= CGAL_NTS abs(v.y()))
      {
         if (CGAL_NTS abs(v.x()) >= CGAL_NTS abs(v.z())) return 0;
         return 2;
      }
      else
      {
         if (CGAL_NTS abs(v.y()) >= CGAL_NTS abs(v.z())) return 1;
         return 2;
      }
    }
};

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
  typedef CGAL::Polyhedron_3<R>                  Polyhedron_3;
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
  typedef CGAL::Max_coordinate_3<Vector_3>             Max_coordinate_3;

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

  Max_coordinate_3  
  max_coordinate_3_object() const
  { return Max_coordinate_3(); }
};

} // namespace CGAL

#endif // CGAL_CONVEX_HULL_TRAITS_3_H


