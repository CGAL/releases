// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// file          : include/CGAL/Planar_map_2/Trapezoidal_decomposition_2_misc.h
// package       : pm (4.20)
// source        : 
// revision      : 
// revision_date : 
// author(s)     : Oren Nechushtan
//                 Iddo Hanniel
//
//
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// Chapter       : 
// email         : cgal@cs.uu.nl
//
// ======================================================================
#ifndef CGAL_TRAPEZOIDAL_DECOMPOSITION_2_MISC_H
#define CGAL_TRAPEZOIDAL_DECOMPOSITION_2_MISC_H

#ifndef CGAL_PM_TENTUPLE_H
#include <CGAL/Planar_map_2/Pm_tentuple.h>
#endif
#ifndef CGAL_TWOTUPLE_H
#include <CGAL/Twotuple.h>
#endif
//#ifndef CGAL_PREDICATE_OBJECTS_ON_POINTS_2_H
//#include <CGAL/predicate_objects_on_points_2.h>
//#endif
#ifndef CGAL_PLANAR_MAP_MISC_H
#include <CGAL/Planar_map_2/Planar_map_misc.h>
#endif

#ifndef CGAL_PM_DAG_H
#include <CGAL/Planar_map_2/Pm_DAG.h>
#endif

#define CGAL_TRAPEZOIDAL_DECOMPOSITION_2_DELETE_SIGNATURE 0xffffffff
#define CGAL_TRAPEZOIDAL_DECOMPOSITION_2_LEFT_UNBOUNDED 0x1
#define CGAL_TRAPEZOIDAL_DECOMPOSITION_2_RIGHT_UNBOUNDED 0x2
#define CGAL_TRAPEZOIDAL_DECOMPOSITION_2_BOTTOM_UNBOUNDED 0x4
#define CGAL_TRAPEZOIDAL_DECOMPOSITION_2_TOP_UNBOUNDED 0x8
#define CGAL_TRAPEZOIDAL_DECOMPOSITION_2_TOTALLY_UNBOUNDED \
	(CGAL_TRAPEZOIDAL_DECOMPOSITION_2_LEFT_UNBOUNDED| \
	CGAL_TRAPEZOIDAL_DECOMPOSITION_2_RIGHT_UNBOUNDED| \
	CGAL_TRAPEZOIDAL_DECOMPOSITION_2_BOTTOM_UNBOUNDED| \
	CGAL_TRAPEZOIDAL_DECOMPOSITION_2_TOP_UNBOUNDED) 
#define CGAL_TRAPEZOIDAL_DECOMPOSITION_2_BOUNDED 0

#endif



















