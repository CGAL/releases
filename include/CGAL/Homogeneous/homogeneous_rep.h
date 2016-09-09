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
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/Homogeneous/homogeneous_rep.h
// package       : H2 (2.67)
// revision      : $Revision: 1.11 $
// revision_date : $Date: 2002/03/22 12:47:08 $
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_HOMOGENEOUS_REP_H
#define CGAL_HOMOGENEOUS_REP_H

#include <CGAL/Handle_for.h>
#include <CGAL/Handle_for_virtual.h>
#include <CGAL/Twotuple.h>
#include <CGAL/Threetuple.h>
#include <CGAL/Fourtuple.h>
#include <CGAL/utility.h>

#include <CGAL/Quotient.h>

#include <CGAL/representation_tags.h>
#include <CGAL/Kernel/function_objects.h>

#include <CGAL/ConicHPA2.h>

CGAL_BEGIN_NAMESPACE

template <class R_, class RT_, class FT_>
class Homogeneous_base
{
  public:
    typedef RT_                                     RT;
    typedef FT_                                     FT;

    typedef CGAL::Object                            Object_2;
    typedef CGAL::Object                            Object_3;

    typedef PointH2< R_ >                           Point_2;
    typedef VectorH2< R_ >                          Vector_2;
    typedef DirectionH2< R_ >                       Direction_2;
    typedef SegmentH2< R_ >                         Segment_2;
    typedef LineH2< R_ >                            Line_2;
    typedef RayH2< R_ >                             Ray_2;
    typedef CircleH2< R_ >                          Circle_2;
    typedef Data_accessorH2<R_>                     Data_accessor_2;
    typedef ConicHPA2<Point_2,Data_accessor_2>      Conic_2;
    typedef TriangleH2< R_ >                        Triangle_2;
    typedef Iso_rectangleH2< R_ >                   Iso_rectangle_2;
    typedef Aff_transformationH2< R_ >              Aff_transformation_2;

    typedef PointH3< R_ >                            Point_3;
    typedef VectorH3< R_ >                           Vector_3;
    typedef DirectionH3< R_ >                        Direction_3;
    typedef SegmentH3< R_ >                          Segment_3;
    typedef PlaneH3< R_ >                            Plane_3;
    typedef LineH3< R_ >                             Line_3;
    typedef RayH3< R_ >                              Ray_3;
    typedef TriangleH3< R_ >                         Triangle_3;
    typedef TetrahedronH3< R_ >                      Tetrahedron_3;
    typedef Iso_cuboidH3< R_ >                       Iso_cuboid_3;
    typedef SphereH3< R_ >                           Sphere_3;
    typedef Aff_transformationH3< R_ >               Aff_transformation_3;
};

template <class RT_, class FT_ = Quotient<RT_> >
class Homogeneous
  : public Homogeneous_base< Homogeneous<RT_,FT_>, RT_, FT_ >
{
  public:
    typedef Homogeneous< RT_, FT_ >                 R;
    typedef RT_                                     RT;
    typedef FT_                                     FT;

    typedef Homogeneous_tag                         Rep_tag;
    typedef Homogeneous_base< R, RT_, FT_ >         Kernel_base;

    typedef typename Kernel_base::Object_2              Object_2;
    typedef typename Kernel_base::Object_3              Object_3;

    typedef CGAL::Point_2< R >                     Point_2;
    typedef CGAL::Vector_2< R >                    Vector_2;
    typedef CGAL::Direction_2< R >                 Direction_2;
    typedef CGAL::Segment_2< R >                   Segment_2;
    typedef CGAL::Line_2< R >                      Line_2;
    typedef CGAL::Ray_2< R >                       Ray_2;
    typedef CGAL::Circle_2< R >                    Circle_2;
    typedef CGAL::Conic_2< R >                     Conic_2;
    typedef CGAL::Triangle_2< R >                  Triangle_2;
    typedef CGAL::Iso_rectangle_2< R >             Iso_rectangle_2;
    typedef CGAL::Aff_transformation_2< R >        Aff_transformation_2;

    typedef CGAL::Point_3< R >                     Point_3;
    typedef CGAL::Vector_3< R >                    Vector_3;
    typedef CGAL::Direction_3< R >                 Direction_3;
    typedef CGAL::Segment_3< R >                   Segment_3;
    typedef CGAL::Plane_3< R >                     Plane_3;
    typedef CGAL::Line_3< R >                      Line_3;
    typedef CGAL::Ray_3< R >                       Ray_3;
    typedef CGAL::Triangle_3< R >                  Triangle_3;
    typedef CGAL::Tetrahedron_3< R >               Tetrahedron_3;
    typedef CGAL::Iso_cuboid_3< R >                Iso_cuboid_3;
    typedef CGAL::Sphere_3< R >                    Sphere_3;
    typedef CGAL::Aff_transformation_3< R >        Aff_transformation_3;

    typedef Data_accessorH2<R>                     Data_accessor_2;

    typedef CGAL::Handle_for< Threetuple<RT> >       Point_handle_2;
    typedef CGAL::Handle_for< Threetuple<RT> >       Vector_handle_2;
    typedef CGAL::Handle_for< Threetuple<RT> >       Direction_handle_2;
    typedef CGAL::Handle_for< Twotuple<Point_2> >    Ray_handle_2;
    typedef CGAL::Handle_for< Threetuple<Point_2> >  Triangle_handle_2;
    typedef CGAL::Handle_for< Triple<Point_2, FT, Orientation> >
	                                             Circle_handle_2;
    typedef CGAL::Handle_for< Twotuple<Point_2> >
	                                             Iso_rectangle_handle_2;
    typedef CGAL::Handle_for< Threetuple<RT> >       Line_handle_2;
    typedef CGAL::Handle_for< Twotuple<Point_2> > Segment_handle_2;
    typedef CGAL::Handle_for_virtual< Aff_transformation_rep_baseH2<R> >
			                           Aff_transformation_handle_2;

    typedef CGAL::Handle_for< Fourtuple<RT> >        Point_handle_3;
    typedef CGAL::Handle_for< Fourtuple<RT> >        Vector_handle_3;
    typedef CGAL::Handle_for< Fourtuple<RT> >        Direction_handle_3;
    typedef CGAL::Handle_for< Fourtuple<RT> >        Plane_handle_3;
    typedef CGAL::Handle_for< std::pair<Point_3, Direction_3> > Ray_handle_3;
    typedef CGAL::Handle_for< std::pair<Point_3, Direction_3> > Line_handle_3;
    typedef CGAL::Handle_for< Triple<Point_3, FT, Orientation> >
	                                             Sphere_handle_3;
    typedef CGAL::Handle_for< Fourtuple<Point_3> >   Tetrahedron_handle_3;
    typedef CGAL::Handle_for< Twotuple<Point_3> >    Segment_handle_3;
    typedef CGAL::Handle_for< Threetuple<Point_3> >  Triangle_handle_3;
    typedef CGAL::Handle_for< Twotuple<Point_3> >    Iso_cuboid_handle_3;
    typedef CGAL::Handle_for_virtual< Aff_transformation_rep_baseH3<R> >
			                           Aff_transformation_handle_3;

    static
    FT
    make_FT(const RT & num, const RT& denom)
    { return FT(num, denom); }

    static
    FT
    make_FT(const RT & num)
    { return FT(num); }

    static
    RT
    FT_numerator(const FT &r)
    { return r.numerator(); }

    static
    RT
    FT_denominator(const FT &r)
    { return r.denominator(); }

#include <CGAL/Kernel_traits_common.h>

};

CGAL_END_NAMESPACE

#endif // CGAL_HOMOGENEOUS_REP_H
