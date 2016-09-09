// ======================================================================
//
// Copyright (c) 2001 The CGAL Consortium

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
// file          : include/compilers/vc7/stl_config.h
// package       : Stl_port (1.33)
// author(s)     : ?
// coordinator   : ?
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
//----------------------------------------------------------------------//
//             STLport fix for MSVC
//----------------------------------------------------------------------//
#ifndef CGAL_STL_CONFIGVC7

#ifdef _MSC_VER
#if _MSC_VER < 1300
#error "this is not MSVC 7.0 !"
#else  // VC7

// <NBulteau@jouve.fr> : suppressed "truncated debug info" warning
#   pragma warning(disable:4786)

// decorated name length exceeded warning only once.
#   pragma warning(once:4503)

# include <iterator> // including iterator-traits fixes from vc7/ dir
#define __STL_BEGIN_NAMESPACE namespace std {
#define __STL_END_NAMESPACE }
#endif //VC7
#else  // not _MSC_VER
#error "this is not MSVC !"
#endif // _MSC_VER

#endif // CGAL_STL_CONFIGVC7
