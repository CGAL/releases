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
// file          : include/CGAL/memory.h
// package       : Kernel_basic (3.90)
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2001/10/22 12:50:23 $
// author(s)     : Michael Seel
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_MEMORY_H
#define CGAL_MEMORY_H

// This file defines the macro CGAL_ALLOCATOR(t) which is the default
// allocator used by CGAL.

#ifdef CGAL_USE_LEDA
#  include <LEDA/allocator.h>
#  define CGAL_ALLOCATOR(t) leda_allocator< t >

#else
#  include <memory>
#  define CGAL_ALLOCATOR(t) std::allocator< t >
#endif

#endif // CGAL_MEMORY_H
