// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/Trapezoidal_map_2_misc.h
// package       : pm (3.07)
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
#ifndef CGAL_TRAPEZOIDAL_MAP_2_MISC_H
#define CGAL_TRAPEZOIDAL_MAP_2_MISC_H

#ifndef CGAL_PM_CONFIG_H
#include <CGAL/Pm_config.h>
#endif

#ifndef CGAL_PM_TENTUPLE_H
#include <CGAL/Pm_tentuple.h>
#endif
#ifndef CGAL_TWOTUPLE_H
#include <CGAL/Twotuple.h>
#endif
//#ifndef CGAL_PREDICATE_OBJECTS_ON_POINTS_2_H
//#include <CGAL/predicate_objects_on_points_2.h>
//#endif
#ifndef CGAL_PLANAR_MAP_MISC_H
#include <CGAL/Planar_map_misc.h>
#endif

#ifndef CGAL_PM_DAG_H
#include <CGAL/Pm_DAG.h>
#endif

#define CGAL_TRAPEZOIDAL_MAP_2_DELETE_SIGNATURE 0xffffffff
#define CGAL_TRAPEZOIDAL_MAP_2_LEFT_UNBOUNDED 0x1
#define CGAL_TRAPEZOIDAL_MAP_2_RIGHT_UNBOUNDED 0x2
#define CGAL_TRAPEZOIDAL_MAP_2_BOTTOM_UNBOUNDED 0x4
#define CGAL_TRAPEZOIDAL_MAP_2_TOP_UNBOUNDED 0x8
#define CGAL_TRAPEZOIDAL_MAP_2_TOTALLY_UNBOUNDED \
	(CGAL_TRAPEZOIDAL_MAP_2_LEFT_UNBOUNDED| \
	CGAL_TRAPEZOIDAL_MAP_2_RIGHT_UNBOUNDED| \
	CGAL_TRAPEZOIDAL_MAP_2_BOTTOM_UNBOUNDED| \
	CGAL_TRAPEZOIDAL_MAP_2_TOP_UNBOUNDED) 
#define CGAL_TRAPEZOIDAL_MAP_2_BOUNDED 0

#endif



















