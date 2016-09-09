// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : config/testfiles/CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION.C
// package       : Configuration (1.21)
// source        :
// revision      : 1.11
// revision_date : 29 Mar 1998
// author(s)     : various
//
// coordinator   : Utrecht University
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

// CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION.C
// ---------------------------------------------------------------------
// A short test program to evaluate a C++ compiler whether it is able
// locate template implementation files with suffix .C  automatically.
// This program is used by cgal_configure.
// The following documentation will be pasted in the generated configfile.
// ---------------------------------------------------------------------

//| When template implementation files are not included in the source files,
//| a compiler may attempt to find the unincluded template bodies
//| automatically. For example, suppose that the following conditions are
//| all true.
//|
//| - template entity ABC::f is declared in file xyz.h
//| - an instantiation of ABC::f is required in a compilation
//| - no definition of ABC::f appears in the source code processed by the
//|   compilation
//| 
//| In this case, the compiler may look to see if the source file xyz.n exists,
//| where n is .c, .C, .cpp, .CPP, .cxx, .CXX, or .cc. If this feature is
//| missing, the flag CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION is set.

#include "template.h"

int main()
{
  A<float> a;
  float f = a.square(1.2);

  return 0;
}

// EOF //
