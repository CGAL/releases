// Copyright (c) 1999,2000,2001,2002,2003  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source: /CVSROOT/CGAL/Packages/H2/include/CGAL/Homogeneous/Homogeneous_base.h,v $
// $Revision: 1.10 $ $Date: 2003/10/21 12:16:09 $
// $Name: current_submission $
//
// Author(s)     : Stefan Schirra, Sylvain Pion

#ifndef CGAL_HOMOGENEOUS_BASE_H
#define CGAL_HOMOGENEOUS_BASE_H

#define CGAL_REP_CLASS_DEFINED

#include <CGAL/basic.h>
#include <CGAL/basic_classes.h>

#include <CGAL/Homogeneous/Aff_transformationH2.h>
#include <CGAL/Homogeneous/CircleH2.h>
#include <CGAL/Homogeneous/DirectionH2.h>
#include <CGAL/Homogeneous/Iso_rectangleH2.h>
#include <CGAL/Homogeneous/LineH2.h>
#include <CGAL/Homogeneous/PointH2.h>
#include <CGAL/Homogeneous/RayH2.h>
#include <CGAL/Homogeneous/SegmentH2.h>
#include <CGAL/Homogeneous/TriangleH2.h>
#include <CGAL/Homogeneous/VectorH2.h>
#include <CGAL/Homogeneous/Data_accessorH2.h>
#include <CGAL/ConicHPA2.h>

#include <CGAL/Homogeneous/Aff_transformationH3.h>
#include <CGAL/Homogeneous/DirectionH3.h>
#include <CGAL/Homogeneous/Iso_cuboidH3.h>
#include <CGAL/Homogeneous/LineH3.h>
#include <CGAL/Homogeneous/PlaneH3.h>
#include <CGAL/Homogeneous/PointH3.h>
#include <CGAL/Homogeneous/RayH3.h>
#include <CGAL/Homogeneous/SegmentH3.h>
#include <CGAL/Homogeneous/SphereH3.h>
#include <CGAL/Homogeneous/TetrahedronH3.h>
#include <CGAL/Homogeneous/TriangleH3.h>
#include <CGAL/Homogeneous/VectorH3.h>

#include <CGAL/Homogeneous/basic_constructionsH2.h>
#include <CGAL/Homogeneous/distance_predicatesH2.h>
#include <CGAL/Homogeneous/predicates_on_directionsH2.h>
#include <CGAL/Homogeneous/predicates_on_linesH2.h>
#include <CGAL/Homogeneous/predicates_on_pointsH2.h>
#include <CGAL/Homogeneous/predicates_on_segmentsH2.h>
#include <CGAL/Homogeneous/predicates_on_rtH2.h>

#include <CGAL/Homogeneous/basic_constructionsH3.h>
#include <CGAL/Homogeneous/distance_predicatesH3.h>
#include <CGAL/Homogeneous/orientation_predicatesH3.h>
#include <CGAL/Homogeneous/predicates_on_pointsH3.h>
#include <CGAL/Homogeneous/predicates_on_pointsH2.h>

#include <CGAL/representation_tags.h>
#include <CGAL/Homogeneous/function_objects.h>

CGAL_BEGIN_NAMESPACE

template < typename K_ >
struct Homogeneous_base
{
    typedef K_                                      Kernel;

    typedef Homogeneous_tag                         Rep_tag;
    typedef Homogeneous_tag                         Kernel_tag;

    typedef CGAL::Object                            Object_2;
    typedef CGAL::Object                            Object_3;

    typedef PointH2<Kernel>                         Point_2;
    typedef VectorH2<Kernel>                        Vector_2;
    typedef DirectionH2<Kernel>                     Direction_2;
    typedef SegmentH2<Kernel>                       Segment_2;
    typedef LineH2<Kernel>                          Line_2;
    typedef RayH2<Kernel>                           Ray_2;
    typedef CircleH2<Kernel>                        Circle_2;
    typedef TriangleH2<Kernel>                      Triangle_2;
    typedef Iso_rectangleH2<Kernel>                 Iso_rectangle_2;
    typedef Aff_transformationH2<Kernel>            Aff_transformation_2;

    typedef PointH3<Kernel>                         Point_3;
    typedef VectorH3<Kernel>                        Vector_3;
    typedef DirectionH3<Kernel>                     Direction_3;
    typedef SegmentH3<Kernel>                       Segment_3;
    typedef PlaneH3<Kernel>                         Plane_3;
    typedef LineH3<Kernel>                          Line_3;
    typedef RayH3<Kernel>                           Ray_3;
    typedef TriangleH3<Kernel>                      Triangle_3;
    typedef TetrahedronH3<Kernel>                   Tetrahedron_3;
    typedef Iso_cuboidH3<Kernel>                    Iso_cuboid_3;
    typedef SphereH3<Kernel>                        Sphere_3;
    typedef Aff_transformationH3<Kernel>            Aff_transformation_3;

    typedef Cartesian_coordinate_iterator_2<Kernel>
                                 Cartesian_const_iterator_2;
    typedef Cartesian_coordinate_iterator_3<Kernel>
                                 Cartesian_const_iterator_3;

    // Undocumented stuff.
    typedef Data_accessorH2<Kernel>                 Data_accessor_2;
    typedef ConicHPA2<Point_2, Data_accessor_2>     Conic_2; 
    // Functors types and access functions.
#define CGAL_Kernel_pred(Y,Z) typedef HomogeneousKernelFunctors::Y<Kernel> Y; \
                              Y Z() const { return Y(); }
#define CGAL_Kernel_cons(Y,Z) CGAL_Kernel_pred(Y,Z)

#include <CGAL/Kernel/interface_macros.h>

};

CGAL_END_NAMESPACE

#endif // CGAL_HOMOGENEOUS_BASE_H
