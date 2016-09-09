// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : include/CGAL/Kernel/Construction_objects_2.h
// package       : Cartesian_basic (3.3.7)
// revision      : $Revision: 1.3 $
// revision_date : $Date: 1999/11/22 13:44:12 $
// author(s)     : Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_KERNEL_CONSTRUCTION_OBJECTS_2_H
#define CGAL_KERNEL_CONSTRUCTION_OBJECTS_2_H

#include <CGAL/predicate_objects_on_points_2.h>
#include <CGAL/Kernel/function_objects.h>

CGAL_BEGIN_NAMESPACE

template < class R >
class Kernel_construction_objects_2
{
public:
typedef typename R::FT                         FT;
typedef typename R::RT                         RT;
typedef typename R::Point_2                    Point_2;
typedef typename R::Vector_2                   Vector_2;
typedef typename R::Direction_2                Direction_2;
typedef typename R::Segment_2                  Segment_2;
typedef typename R::Line_2                     Line_2;
typedef typename R::Ray_2                      Ray_2;
typedef typename R::Triangle_2                 Triangle_2;
typedef typename R::Circle_2                   Circle_2;
typedef typename R::Iso_rectangle_2            Iso_rectangle_2;
typedef typename R::Aff_transformation_2       Aff_transformation_2;

typedef CGALi::Construct<Point_2>              Construct_point_2;
typedef CGALi::Construct<Vector_2>             Construct_vector_2;
typedef CGALi::Construct<Direction_2>          Construct_direction_2;
typedef CGALi::Construct<Segment_2>            Construct_segment_2;
typedef CGALi::Construct<Line_2>               Construct_line_2;
typedef CGALi::Construct<Ray_2>                Construct_ray_2;
typedef CGALi::Construct<Circle_2>             Construct_circle_2;
typedef CGALi::Construct<Triangle_2>           Construct_triangle_2;
typedef CGALi::Construct<Aff_transformation_2> Construct_aff_transformation_2;

Construct_point_2 
construct_point_2_object() const { return Construct_point_2(); }
Construct_vector_2
construct_vector_2_object() const { return Construct_vector_2(); }
Construct_direction_2
construct_direction_2_object() const { return Construct_direction_2(); }
Construct_segment_2
construct_segment_2_object() const { return Construct_segment_2(); }
Construct_line_2
construct_line_2_object() const { return Construct_line_2(); }
Construct_ray_2
construct_ray_2_object() const { return Construct_ray_2(); }
Construct_circle_2
construct_circle_2() const { return Construct_circle_2(); }
Construct_triangle_2
construct_triangle_2_object() const { return Construct_triangle_2(); }
Construct_aff_transformation_2
construct_aff_transformation_2_object() const { return Construct_aff_transformation_2(); }

typedef CGALi::Call_point_to_get<Point_2>              Construct_point_on_2;
Construct_point_on_2
construct_point_on_2_object() const { return Construct_point_on_2(); }

typedef CGALi::Call_second_point_to_get<Point_2>       Construct_second_point_on_2;
Construct_second_point_on_2
construct_second_point_on_2_object() const { return Construct_second_point_on_2(); }

typedef CGALi::Call_perpendicular_to_get<Vector_2>     Construct_perpendicular_vector_2;
Construct_perpendicular_vector_2
construct_perpendicular_vector_2_object() const { return Construct_perpendicular_vector_2(); }

typedef CGALi::Call_perpendicular_to_get<Direction_2>  Construct_perpendicular_direction_2;
Construct_perpendicular_direction_2
construct_perpendicular_direction_2_object() const { return Construct_perpendicular_direction_2(); }

typedef CGALi::Call_perpendicular_to_get<Line_2>       Construct_perpendicular_line_2;
Construct_perpendicular_line_2
construct_perpendicular_line_2_object() const { return Construct_perpendicular_line_2(); }

typedef CGALi::p_Midpoint<Point_2>                     Construct_midpoint_2;
Construct_midpoint_2
construct_midpoint_2_object() const { return Construct_midpoint_2(); }

typedef CGALi::p_Circumcenter<Point_2>                 Construct_circumcenter_2;
Construct_circumcenter_2
construct_circumcenter_2_object() const { return Construct_circumcenter_2(); }

typedef CGALi::pl_Bisector<Point_2, Line_2>            Construct_bisector_2;
Construct_bisector_2
construct_bisector_2_object() const { return Construct_bisector_2(); }

typedef CGALi::Intersect                               Intersect_2;
Intersect_2
intersect_2_object() const { return Intersect_2(); }

typedef CGALi::Call_y_at_x_to_get<FT>                  Compute_y_at_x;
Compute_y_at_x
compute_y_at_x_object() const { return Compute_y_at_x(); }

typedef CGALi::Call_squared_length_to_get<FT>          Compute_squared_length;
Compute_squared_length
Compute_squared_length_object() const { return Compute_squared_length(); }
};

CGAL_END_NAMESPACE

// This macro is provided for convenience in defining the Kernel
// function objects inside a new representation class.
// See Cartesian_2.h and Cartesian.h

#define CGAL_UNPACK_KERNEL_CONSTRUCTION_OBJECTS_2(CO) \
typedef CO::Construct_point_2              Construct_point_2; \
typedef CO::Construct_vector_2             Construct_vector_2; \
typedef CO::Construct_direction_2          Construct_direction_2; \
typedef CO::Construct_segment_2            Construct_segment_2; \
typedef CO::Construct_line_2               Construct_line_2; \
typedef CO::Construct_ray_2                Construct_ray_2; \
typedef CO::Construct_circle_2             Construct_circle_2; \
typedef CO::Construct_triangle_2           Construct_triangle_2; \
typedef CO::Construct_aff_transformation_2 Construct_aff_transformation_2; \
 \
Construct_point_2  \
construct_point_2_object() const { return Construct_point_2(); } \
Construct_vector_2 \
construct_vector_2_object() const { return Construct_vector_2(); } \
Construct_direction_2 \
construct_direction_2_object() const { return Construct_direction_2(); } \
Construct_segment_2 \
construct_segment_2_object() const { return Construct_segment_2(); } \
Construct_line_2 \
construct_line_2_object() const { return Construct_line_2(); } \
Construct_ray_2 \
construct_ray_2_object() const { return Construct_ray_2(); } \
Construct_circle_2 \
construct_circle_2() const { return Construct_circle_2(); } \
Construct_triangle_2 \
construct_triangle_2_object() const { return Construct_triangle_2(); } \
Construct_aff_transformation_2 \
construct_aff_transformation_2_object() const { return Construct_aff_transformation_2(); } \
 \
typedef CO::Construct_point_on_2     Construct_point_on_2; \
Construct_point_on_2 \
construct_point_on_2_object() const { return Construct_point_on_2(); } \
 \
typedef CO::Construct_second_point_on_2   Construct_second_point_on_2; \
Construct_second_point_on_2 \
construct_second_point_on_2_object() const { return Construct_second_point_on_2(); } \
 \
typedef CO::Construct_perpendicular_vector_2    Construct_perpendicular_vector_2; \
Construct_perpendicular_vector_2 \
construct_perpendicular_vector_2_object() const { return Construct_perpendicular_vector_2(); } \
 \
typedef CO::Construct_perpendicular_direction_2  Construct_perpendicular_direction_2; \
Construct_perpendicular_direction_2 \
construct_perpendicular_direction_2_object() const { return Construct_perpendicular_direction_2(); } \
 \
typedef CO::Construct_perpendicular_line_2    Construct_perpendicular_line_2; \
Construct_perpendicular_line_2 \
construct_perpendicular_line_2_object() const { return Construct_perpendicular_line_2(); } \
 \
typedef CO::Construct_midpoint_2   Construct_midpoint_2; \
Construct_midpoint_2 \
construct_midpoint_2_object() const { return Construct_midpoint_2(); } \
 \
typedef CO::Construct_circumcenter_2    Construct_circumcenter_2; \
Construct_circumcenter_2 \
construct_circumcenter_2_object() const { return Construct_circumcenter_2(); } \
 \
typedef CO::Construct_bisector_2    Construct_bisector_2; \
Construct_bisector_2 \
construct_bisector_2_object() const { return Construct_bisector_2(); } \
 \
typedef CO::Intersect_2       Intersect_2; \
Intersect_2 \
intersect_2_object() const { return Intersect_2(); } \
 \
typedef CO::Compute_y_at_x   Compute_y_at_x; \
Compute_y_at_x \
compute_y_at_x_object() const { return Compute_y_at_x(); } \
 \
typedef CO::Compute_squared_length    Compute_squared_length; \
Compute_squared_length \
Compute_squared_length_object() const { return Compute_squared_length(); }

#endif // CGAL_KERNEL_CONSTRUCTION_OBJECTS_2_H
