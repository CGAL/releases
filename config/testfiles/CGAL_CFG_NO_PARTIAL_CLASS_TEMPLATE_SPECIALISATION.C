// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium

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
// date          : 21 Apr 1998
//
// file          : config/testfiles/CGAL_CFG_NO_PARTIAL_CLASS_TEMPLATE_SPECIALISATION.C
// package       : Configuration (2.32)
// author(s)     : various
// coordinator   : Utrecht University
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

// CGAL_CFG_NO_PARTIAL_CLASS_TEMPLATE_SPECIALISATION.C
// ---------------------------------------------------------------------

//| If a compiler doesn't support partial specialisation of class templates,
//| the flag CGAL_CFG_NO_PARTIAL_CLASS_TEMPLATE_SPECIALISATION is set.

template < class T >
struct B {
  T a;
};

template < class T >
struct C {
  T b;
};

template < class T >
struct C< B < T > > {
  int c;
};

int
main()
{
  C< int > t1;
  C< B< int > > t2;
  t1.b = 1;
  t2.c = 1;
  return 0;
}

// EOF //
