// ======================================================================
//
// Copyright (c) 2000,2001 The CGAL Consortium

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
// file          : include/CGAL/Cartesian.h
// package       : Cartesian_kernel (6.59)
// revision      : $Revision: 1.29 $
// revision_date : $Date: 2002/03/20 15:35:25 $
// author(s)     : Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_H
#define CGAL_CARTESIAN_H

#define CGAL_REP_CLASS_DEFINED
#define CGAL_CARTESIAN_CLASS_DEFINED

#include <CGAL/basic.h>
#include <CGAL/Handle_for_virtual.h>
#include <CGAL/basic_classes.h>
#include <CGAL/user_classes.h>

#include <CGAL/Twotuple.h>
#include <CGAL/Threetuple.h>
#include <CGAL/utility.h>

#include <CGAL/Cartesian/Point_2.h>
#include <CGAL/Cartesian/Vector_2.h>
#include <CGAL/Cartesian/Direction_2.h>
#include <CGAL/Cartesian/Line_2.h>
#include <CGAL/Cartesian/Ray_2.h>
#include <CGAL/Cartesian/Segment_2.h>
#include <CGAL/Cartesian/Triangle_2.h>
#include <CGAL/Cartesian/Circle_2.h>
#include <CGAL/Cartesian/Iso_rectangle_2.h>
#include <CGAL/Cartesian/Aff_transformation_2.h>
#include <CGAL/Cartesian/Data_accessor_2.h>
#include <CGAL/ConicCPA2.h>

#include <CGAL/Cartesian/global_operators_2.h>
#include <CGAL/Cartesian/predicates_on_points_2.h>
#include <CGAL/Cartesian/predicates_on_directions_2.h>
#include <CGAL/Cartesian/predicates_on_lines_2.h>
#include <CGAL/Cartesian/predicates_on_segments_2.h>
#include <CGAL/Cartesian/distance_predicates_2.h>

#include <CGAL/Cartesian/basic_constructions_2.h>

#include <CGAL/Kernel/function_objects.h>

#include <CGAL/Cartesian/Point_3.h>
#include <CGAL/Cartesian/Vector_3.h>
#include <CGAL/Cartesian/Direction_3.h>
#include <CGAL/Cartesian/Line_3.h>
#include <CGAL/Cartesian/Plane_3.h>
#include <CGAL/Cartesian/Ray_3.h>
#include <CGAL/Cartesian/Segment_3.h>
#include <CGAL/Cartesian/Triangle_3.h>
#include <CGAL/Cartesian/Tetrahedron_3.h>
#include <CGAL/Cartesian/Iso_cuboid_3.h>
#include <CGAL/Cartesian/Sphere_3.h>
#include <CGAL/Cartesian/Aff_transformation_3.h>

#include <CGAL/Cartesian/global_operators_3.h>
#include <CGAL/Cartesian/predicates_on_points_3.h>
#include <CGAL/Cartesian/predicates_on_planes_3.h>
#include <CGAL/Cartesian/distance_predicates_3.h>

#include <CGAL/Cartesian/basic_constructions_3.h>

#include <CGAL/representation_tags.h>

CGAL_BEGIN_NAMESPACE

template< class R, class FT_ >
struct Cartesian_base
{
    typedef FT_                                         RT;
    typedef FT_                                         FT;
    typedef Cartesian_tag                               Rep_tag;
    typedef Cartesian_tag                               Kernel_tag;

    typedef CGAL::Object                                Object_2;
    typedef CGAL::Object                                Object_3;

    typedef PointC2<R>                                  Point_2;
    typedef VectorC2<R>                                 Vector_2;
    typedef DirectionC2<R>                              Direction_2;
    typedef SegmentC2<R>                                Segment_2;
    typedef LineC2<R>                                   Line_2;
    typedef RayC2<R>                                    Ray_2;
    typedef TriangleC2<R>                               Triangle_2;
    typedef CircleC2<R>                                 Circle_2;
    typedef Iso_rectangleC2<R>                          Iso_rectangle_2;
    typedef Aff_transformationC2<R>                     Aff_transformation_2;
    typedef Data_accessorC2<R>                          Data_accessor_2;
    typedef ConicCPA2<Point_2,Data_accessor_2>          Conic_2;

    typedef PointC3<R>                                  Point_3;
    typedef VectorC3<R>                                 Vector_3;
    typedef DirectionC3<R>                              Direction_3;
    typedef LineC3<R>                                   Line_3;
    typedef PlaneC3<R>                                  Plane_3;
    typedef RayC3<R>                                    Ray_3;
    typedef SegmentC3<R>                                Segment_3;
    typedef TriangleC3<R>                               Triangle_3;
    typedef TetrahedronC3<R>                            Tetrahedron_3;
    typedef Iso_cuboidC3<R>                             Iso_cuboid_3;
    typedef SphereC3<R>                                 Sphere_3;
    typedef Aff_transformationC3<R>                     Aff_transformation_3;
  
};


template< class FT_ >
struct Cartesian
  : public Cartesian_base< Cartesian<FT_>, FT_ >
{
    // Number types and representation tag (to avoid ambiguity)
    typedef FT_                                           RT;
    typedef FT_                                           FT;
    typedef Cartesian_tag                                 Rep_tag;
    typedef Cartesian_tag                                 Kernel_tag;

    typedef Cartesian<FT>                                 Self;
    typedef Cartesian_base<Self,FT>                       Kernel_base;

    // Now CGAL::Point_2<R> is only a wrapper around CGAL::PointC2<R>
    // It is necessary to redefine here the classes to ensure that
    // Cartesian<FT>::Point_2 is exactly CGAL::Point_2< Cartesian<FT> >

    typedef typename Kernel_base::Object_2                Object_2;
    typedef typename Kernel_base::Object_3                Object_3;          

    // Note: necessary to qualify Point_2 by CGAL:: to disambiguate between
    // Point_2 in the current scope (nested within CGAL) and
    // CGAL::Point_2< R > (which is in the CGAL namespace)

    typedef CGAL::Point_2<Self>                           Point_2;
    typedef CGAL::Vector_2<Self>                          Vector_2;
    typedef CGAL::Direction_2<Self>                       Direction_2;
    typedef CGAL::Line_2<Self>                            Line_2;
    typedef CGAL::Ray_2<Self>                             Ray_2;
    typedef CGAL::Segment_2<Self>                         Segment_2;
    typedef CGAL::Triangle_2<Self>                        Triangle_2;
    typedef CGAL::Circle_2<Self>                          Circle_2;
    typedef CGAL::Iso_rectangle_2<Self>                   Iso_rectangle_2;
    typedef CGAL::Aff_transformation_2<Self>              Aff_transformation_2;

    typedef Data_accessorC2<Self>                         Data_accessor_2;
    typedef CGAL::Conic_2<Self>                           Conic_2;

    typedef CGAL::Point_3<Self>                           Point_3;
    typedef CGAL::Vector_3<Self>                          Vector_3;
    typedef CGAL::Direction_3<Self>                       Direction_3;
    typedef CGAL::Line_3<Self>                            Line_3;
    typedef CGAL::Plane_3<Self>                           Plane_3;
    typedef CGAL::Ray_3<Self>                             Ray_3;
    typedef CGAL::Segment_3<Self>                         Segment_3;
    typedef CGAL::Triangle_3<Self>                        Triangle_3;
    typedef CGAL::Tetrahedron_3<Self>                     Tetrahedron_3;
    typedef CGAL::Sphere_3<Self>                          Sphere_3;
    typedef CGAL::Iso_cuboid_3<Self>                      Iso_cuboid_3;
    typedef CGAL::Aff_transformation_3<Self>              Aff_transformation_3;

    // The typedefs that allow to specify the handle of each type.

    typedef CGAL::Handle_for<CGAL::Twotuple<FT> >	Point_handle_2;
    typedef CGAL::Handle_for<CGAL::Twotuple<FT> >	Vector_handle_2;
    typedef CGAL::Handle_for<CGAL::Twotuple<FT> >	Direction_handle_2;
    typedef CGAL::Handle_for<CGAL::Threetuple<FT> >	Line_handle_2;
    typedef CGAL::Handle_for<CGAL::Twotuple<Point_2> >  Ray_handle_2;
    typedef CGAL::Handle_for<CGAL::Twotuple<Point_2> >  Segment_handle_2;
    typedef CGAL::Handle_for<Triple<Point_2, FT, Orientation> >
	                                                Circle_handle_2;
    typedef CGAL::Handle_for<CGAL::Threetuple<Point_2> >    Triangle_handle_2;
    typedef CGAL::Handle_for<CGAL::Twotuple<Point_2> >  Iso_rectangle_handle_2;
    typedef CGAL::Handle_for_virtual< Aff_transformation_rep_baseC2<Self> >
			                           Aff_transformation_handle_2;

    typedef CGAL::Handle_for<CGAL::Threetuple<FT> >	Point_handle_3;
    typedef CGAL::Handle_for<CGAL::Threetuple<FT> >	Vector_handle_3;
    typedef CGAL::Handle_for<CGAL::Threetuple<FT> >	Direction_handle_3;
    typedef CGAL::Handle_for<std::pair<Point_3, Direction_3> >
	                                                Line_handle_3;
    typedef CGAL::Handle_for<CGAL::Fourtuple<FT> >	Plane_handle_3;
    typedef CGAL::Handle_for<CGAL::Twotuple<Point_3> >  Ray_handle_3;
    typedef CGAL::Handle_for<CGAL::Twotuple<Point_3> >  Segment_handle_3;
    typedef CGAL::Handle_for<Triple<Point_3, FT,Orientation> > Sphere_handle_3;
    typedef CGAL::Handle_for<CGAL::Threetuple<Point_3> > Triangle_handle_3;
    typedef CGAL::Handle_for<CGAL::Fourtuple<Point_3> > Tetrahedron_handle_3;
    typedef CGAL::Handle_for<CGAL::Twotuple<Point_3> >  Iso_cuboid_handle_3;
    typedef CGAL::Handle_for_virtual< Aff_transformation_rep_baseC3<Self> >
			                           Aff_transformation_handle_3;

    // TODO: cleanup
    static   FT make_FT(const RT & num, const RT& denom) { return num/denom;}
    static   FT make_FT(const RT & num)                  { return num;}
    static   RT FT_numerator(const FT &r)                { return r;}
    static   RT FT_denominator(const FT &)               { return RT(1);}

#include <CGAL/Kernel_traits_common.h>

};

CGAL_END_NAMESPACE

#include <CGAL/iterator_traits_pointer_specs_for_cartesian_kernel.h>

#endif // CGAL_CARTESIAN_H
