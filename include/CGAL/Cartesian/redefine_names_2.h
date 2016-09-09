// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

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
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/Cartesian/redefine_names_2.h
// package       : C2 (4.4)
// revision      : $Revision: 1.9 $
// revision_date : $Date: 2000/08/23 14:35:37 $
// author(s)     : Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_REDEFINE_NAMES_2_H
#define CGAL_CARTESIAN_REDEFINE_NAMES_2_H

#ifndef CGAL_CFG_NO_ADVANCED_KERNEL

// The following defines allow to keep a uniform presentation in
// Point_2.h for both advanced and non-advanced kernels. This is a
// temporary situation. When the non-advanced kernel disappears, all
// classes ...C2 should be renamed ..._2 and this will be it for this
// file. Meanwhile, this hack allows to have both versions at once.

// In Lutz' and Michael's design, PointC2<R> becomes
// Point_2<R,Cartesian_tag>, hence the following defines.

#define PointC2 Point_2
#define VectorC2 Vector_2
#define DirectionC2 Direction_2
#define LineC2 Line_2
#define RayC2 Ray_2
#define SegmentC2 Segment_2
#define TriangleC2 Triangle_2
#define CircleC2 Circle_2
#define Iso_rectangleC2 Iso_rectangle_2
#define Aff_transformationC2 Aff_transformation_2
#define Data_accessorC2 Data_accessor_2

// There is one more problem in unifying the two designs
// We must also take care of the declarations in .C files
// Specifically, in Lutz' and Michael's design, functions are defined as
// PointC2<R,Cartesian_tag>::function() {}
// and in Stefan's design, their definition looks like
// PointC2<R>::function() {}
// We unify this with PointC2<R CGAL_CTAG >::function
#define CGAL_CTAG   , Cartesian_tag

// This is the mark of a partial specialization.  Used by all kernel classes.
#define CGAL_ADVANCED_KERNEL_PARTIAL_SPEC <R_,Cartesian_tag>

#else

#define CGAL_CTAG

#define CGAL_ADVANCED_KERNEL_PARTIAL_SPEC

// Note that it was not possible to keep the opposite (changing the
// Point_2 into PointC2 for Stefan's design) because it would also
// change "typename R::Point_2" into "typename R::PointC2" inside the
// classes definition. A successful hack would then have to analyze
// which Point_2 is intended, hence too complicated.

#endif

#endif // CGAL_CARTESIAN_REDEFINE_NAMES_2_H
