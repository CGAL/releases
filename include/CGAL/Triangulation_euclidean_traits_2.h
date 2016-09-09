// ======================================================================
//
// Copyright (c) 1997  The CGAL Consortium

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
// file          : include/CGAL/Triangulation_euclidean_traits_2.h
// package       : Triangulation_2 (5.18)
// source        : $RCSfile: Triangulation_euclidean_traits_2.h,v $
// revision      : $Revision: 1.20 $
// revision_date : $Date: 2001/06/14 15:06:46 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_EUCLIDEAN_TRAITS_2_H
#define CGAL_TRIANGULATION_EUCLIDEAN_TRAITS_2_H

#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Line_2.h>
#include <CGAL/Direction_2.h>
#include <CGAL/Ray_2.h>
#include <CGAL/predicates_on_points_2.h>
#include <CGAL/basic_constructions_2.h>
#include <CGAL/distance_predicates_2.h>

#include <CGAL/triangulation_assertions.h>
#include <CGAL/Triangulation_short_names_2.h>
#include <CGAL/Segment_2_Segment_2_intersection.h>

CGAL_BEGIN_NAMESPACE 

template < class R >
class Triangulation_euclidean_traits_2 {
public:
  typedef R Rep;
  typedef Point_2<R>  Point_2;
  typedef Segment_2<R> Segment_2;
  typedef Triangle_2<R> Triangle_2;
  typedef Line_2<R> Line_2;
  typedef Direction_2<R> Direction_2;
  typedef Ray_2<R> Ray_2;

  typedef typename R::Compare_x_2                Compare_x_2;
  typedef typename R::Compare_y_2                Compare_y_2;
  typedef typename R::Orientation_2              Orientation_2;
  typedef typename R::Side_of_oriented_circle_2  Side_of_oriented_circle_2;
  typedef typename R::Construct_circumcenter_2   Construct_circumcenter_2;
  typedef typename R::Construct_bisector_2       Construct_bisector_2;
  //typedef typename R::Construct_midpoint         Construct_midpoint;
  typedef typename R::Compare_distance_2         Compare_distance_2;
  typedef typename R::Construct_segment_2        Construct_segment_2;
  typedef typename R::Construct_triangle_2       Construct_triangle_2;
  //typedef typename R::Construct_direction_2      Construct_direction_2;
  typedef typename R::Construct_ray_2            Construct_ray_2;
  typedef typename R::Construct_direction_of_line_2
                                           Construct_direction_of_line_2;

  // for compatibility with previous versions
  typedef Point_2      Point;
  typedef Segment_2    Segment;
  typedef Triangle_2   Triangle;
  typedef Ray_2        Ray;
  typedef Line_2       Line;
  typedef Direction_2  Direction;

  Triangulation_euclidean_traits_2() {}
  Triangulation_euclidean_traits_2(const Triangulation_euclidean_traits_2 &) {}
  Triangulation_euclidean_traits_2 &operator=
      (const Triangulation_euclidean_traits_2 &)
  {return *this;}
 
  Compare_x_2
  compare_x_2_object() const
    { return Compare_x_2();}

  Compare_y_2
  compare_y_2_object() const
    { return Compare_y_2();}
  
  Orientation_2
  orientation_2_object() const
    { return Orientation_2();}

  Side_of_oriented_circle_2
  side_of_oriented_circle_2_object() const
    {return Side_of_oriented_circle_2();}
 
  Construct_circumcenter_2
  construct_circumcenter_2_object() const
    { return Construct_circumcenter_2();}

  Construct_bisector_2
  construct_bisector_2_object() const
    {return Construct_bisector_2();}
  
 //  Construct_midpoint
//   construct_midpoint_object() const
//     {return Construct_midpoint();}


  Compare_distance_2
  compare_distance_2_object() const
    {return Compare_distance_2();}

  Construct_direction_of_line_2
  construct_direction_of_line_2_object() const
    {return  Construct_direction_of_line_2();}

  Construct_segment_2  construct_segment_2_object() const
    {return Construct_segment_2();}

  Construct_triangle_2  construct_triangle_2_object() const
    {return Construct_triangle_2();}

//   Construct_direction_2  construct_direction_2_object() const
//     {return Construct_direction_2();}

  Construct_ray_2  construct_ray_2_object() const
    {return Construct_ray_2();}

};

CGAL_END_NAMESPACE 

#endif // CGAL_TRIANGULATION_EUCLIDEAN_TRAITS_2_H
