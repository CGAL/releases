// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

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
// file          : include/CGAL/Cartesian/redefine_names_3.h
// package       : Cartesian_kernel (6.24)
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2000/10/19 15:44:29 $
// author(s)     : Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_REDEFINE_NAMES_3_H
#define CGAL_CARTESIAN_REDEFINE_NAMES_3_H

#ifndef CGAL_CFG_NO_ADVANCED_KERNEL

// The following defines allow to keep a uniform presentation in
// Point_3.h for both advanced and non-advanced kernels. This is a
// temporary situation. When the non-advanced kernel disappears, all
// classes ...C3 should be renamed ..._3 and this will be it for this
// file. Meanwhile, this hack allows to have both versions at once.

// In Lutz' and Michael's design, PointC3<R> becomes
// Point_3<R,Cartesian_tag>, hence the following defines.

#define PointC3 Point_3
#define VectorC3 Vector_3
#define DirectionC3 Direction_3
#define LineC3 Line_3
#define PlaneC3 Plane_3
#define RayC3 Ray_3
#define SegmentC3 Segment_3
#define SphereC3 Sphere_3
#define TriangleC3 Triangle_3
#define TetrahedronC3 Tetrahedron_3
#define Iso_cuboidC3 Iso_cuboid_3
#define Aff_transformationC3 Aff_transformation_3
#define Data_accessorC3 Data_accessor_3

// There is one more problem in unifying the two designs
// We must also take care of the declarations in .C files
// Specifically, in Lutz' and Michael's design, functions are defined as
// PointC3<R,Cartesian_tag>::function() {}
// and in Stefan's design, their definition looks like
// PointC3<R>::function() {}
// We unify this with PointC3<R CGAL_CTAG >::function
#define CGAL_CTAG   , Cartesian_tag

// This is the mark of a partial specialization.  Used by all kernel classes.
#define CGAL_ADVANCED_KERNEL_PARTIAL_SPEC <R_,Cartesian_tag>

#else

#define CGAL_CTAG
#define CGAL_ADVANCED_KERNEL_PARTIAL_SPEC

// Note that it was not possible to keep the opposite (changing the
// Point_3 into PointC3 for Stefan's design) because it would also
// change "typename R::Point_3" into "typename R::PointC3" inside the
// classes definition. A successful hack would then have to analyze
// which Point_3 is intended, hence too complicated.

#endif

#endif // CGAL_CARTESIAN_REDEFINE_NAMES_3_H
