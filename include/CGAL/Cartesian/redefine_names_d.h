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
// file          : include/CGAL/Cartesian/redefine_names_d.h
// package       : Cd (1.5)
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2000/06/27 14:32:34 $
// author(s)     : Hervé Brönnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_REDEFINE_NAMES_D_H
#define CGAL_CARTESIAN_REDEFINE_NAMES_D_H

#ifndef CGAL_CFG_NO_ADVANCED_KERNEL

// The following defines allow to keep a uniform presentation in
// Point_d.h for both advanced and non-advanced kernels. This is a
// temporary situation. When the non-advanced kernel disappears, all
// classes ...Cd should be renamed ..._d and this will be it for this
// file. Meanwhile, this hack allows to have both versions at once.

// In Lutz' and Michael's design, PointCd<R> becomes
// Point_d<R,Cartesian_tag>, hence the following defines.

#define PointCd Point_d
#define VectorCd Vector_d
#define DirectionCd Direction_d
#define PlaneCd Plane_d
#define LineCd Line_d
#define RayCd Ray_d
#define SegmentCd Segment_d
#define TriangleCd Triangle_d
#define TetrahedronCd Tetrahedron_d
#define SimplexCd Simplex_d
#define Aff_transformationCd Aff_transformation_d
#define Data_accessorCd Data_accessor_d

// There is one more problem in unifying the two designs
// We must also take care of the declarations in .C files
// Specifically, in Lutz' and Michael's design, functions are defined as
// PointCd<R,Cartesian_tag>::function() {}
// and in Stefan's design, their definition looks like
// PointCd<R>::function() {}
// We unify this with PointCd<R CGAL_CTAG >::function
#define CGAL_CTAG   , Cartesian_tag

#else

#define CGAL_CTAG   

// Note that it was not possible to keep the opposite (changing the
// Point_d into PointCd for Stefan's design) because it would also
// change "typename R::Point_d" into "typename R::PointCd" inside the
// classes definition. A successful hack would then have to analyze
// which Point_d is intended, hence too complicated.

#endif

#endif // CGAL_CARTESIAN_REDEFINE_NAMES_D_H
