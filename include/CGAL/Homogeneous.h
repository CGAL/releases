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
// 
// release       : CGAL-2.4
// release_date  : 2002, May 16
// 
// file          : include/CGAL/Homogeneous.h
// package       : H2 (2.67)
// revision      : $Revision: 1.7 $
// revision_date : $Date: 2002/03/20 15:37:46 $
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_HOMOGENEOUS_H
#define CGAL_HOMOGENEOUS_H

#define CGAL_REP_CLASS_DEFINED

#include <CGAL/basic.h>
#include <CGAL/Quotient.h>
#include <CGAL/user_classes.h>
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

#include <CGAL/Homogeneous/homogeneous_rep.h>

#include <CGAL/iterator_traits_pointer_specs_for_homogeneous_kernel.h>

#endif // CGAL_HOMOGENEOUS_H
