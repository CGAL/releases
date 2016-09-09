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
// file          : include/CGAL/Homogeneous.h
// package       : H2 (2.37)
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2001/06/20 12:24:00 $
// author(s)     : Stefan Schirra
//
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
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
#include <CGAL/homogeneous_classes.h>
#include <CGAL/basic_classes.h>

#include <CGAL/Aff_transformationH2.h>
#include <CGAL/CircleH2.h>
#include <CGAL/DirectionH2.h>
#include <CGAL/Iso_rectangleH2.h>
#include <CGAL/LineH2.h>
#include <CGAL/PointH2.h>
#include <CGAL/RayH2.h>
#include <CGAL/SegmentH2.h>
#include <CGAL/TriangleH2.h>
#include <CGAL/VectorH2.h>
#include <CGAL/Data_accessorH2.h>

#include <CGAL/basic_constructionsH2.h>
#include <CGAL/distance_predicatesH2.h>
#include <CGAL/predicates_on_directionsH2.h>
#include <CGAL/predicates_on_linesH2.h>
#include <CGAL/predicates_on_pointsH2.h>
#include <CGAL/predicates_on_rtH2.h>

#include <CGAL/Aff_transformationH3.h>
#include <CGAL/DirectionH3.h>
#include <CGAL/Iso_cuboidH3.h>
#include <CGAL/LineH3.h>
#include <CGAL/PlaneH3.h>
#include <CGAL/PointH3.h>
#include <CGAL/RayH3.h>
#include <CGAL/SegmentH3.h>
#include <CGAL/SphereH3.h>
#include <CGAL/TetrahedronH3.h>
#include <CGAL/TriangleH3.h>
#include <CGAL/VectorH3.h>

#include <CGAL/homogeneous_rep.h>

#include <CGAL/basic_constructionsH3.h>
#include <CGAL/distance_predicatesH3.h>
#include <CGAL/orientation_predicatesH3.h>
#include <CGAL/predicates_on_pointsH3.h>
#include <CGAL/predicates_on_pointsH2.h>

#include <CGAL/iterator_traits_pointer_specs_for_homogeneous_kernel.h>

#endif // CGAL_HOMOGENEOUS_H
