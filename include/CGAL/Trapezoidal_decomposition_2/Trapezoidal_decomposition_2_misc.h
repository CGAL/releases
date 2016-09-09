// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// file          : include/CGAL/Trapezoidal_decomposition_2/Trapezoidal_decomposition_2_misc.h
// package       : Trapezoidal_decomposition (1.26)
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
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_TRAPEZOIDAL_DECOMPOSITION_2_MISC_H
#define CGAL_TRAPEZOIDAL_DECOMPOSITION_2_MISC_H

#ifndef CGAL_TD_TENTUPLE_H
#include <CGAL/Trapezoidal_decomposition_2/Td_ninetuple.h>
#endif
#ifndef CGAL_TWOTUPLE_H
#include <CGAL/Twotuple.h>
#endif

#ifndef CGAL_TD_DAG_H
#include <CGAL/Td_dag.h>
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
#define CGAL_TD_DEFAULT_DEPTH_THRESHOLD 2
#define CGAL_TD_DEFAULT_SIZE_THRESHOLD 2

#ifndef _MSC_VER
#ifndef __BORLANDC__
#if !defined __GNUC__ || __GNUC__>2 || __GNUC__==2 && __GNUC_MINOR__>=95
#define CGAL_PM_FRIEND_CLASS
#endif
#endif
#endif

#endif



















