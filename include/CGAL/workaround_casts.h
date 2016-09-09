// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/workaround_casts.h
// author(s)     : Sven Schönherr 
//
// email         : cgal@cs.uu.nl
//
// ============================================================================

#ifndef CGAL_WORKAROUND_CASTS_H
#define CGAL_WORKAROUND_CASTS_H 1

// workaround for C++-style casts
#if defined( CGAL_CFG_NO_STATIC_CAST)
#  define  CGAL_static_cast(type,expr)  (type)( expr)
#else
#  define  CGAL_static_cast(type,expr)  static_cast< type >(expr)
#endif // CGAL_CFG_NO_STATIC_CAST

#if defined( CGAL_CFG_NO_CONST_CAST)
#  define  CGAL_const_cast(type,expr)  (type)( expr)
#else
#  define  CGAL_const_cast(type,expr)  const_cast< type >(expr)
#endif // CGAL_CFG_NO_CONST_CAST

#if defined( CGAL_CFG_NO_DYNAMIC_CAST)
#  define  CGAL_dynamic_cast(type,expr)  (type)( expr)
#else
#  define  CGAL_dynamic_cast(type,expr)  dynamic_cast< type >(expr)
#endif // CGAL_CFG_NO_DYNAMIC_CAST

#if defined( CGAL_CFG_NO_REINTERPRET_CAST)
#  define  CGAL_reinterpret_cast(type,expr)  (type)( expr)
#else
#  define  CGAL_reinterpret_cast(type,expr)  reinterpret_cast< type >(expr)
#endif // CGAL_CFG_NO_REINTERPRET_CAST

#endif // CGAL_WORKAROUND_CASTS_H

// ===== EOF ==================================================================
