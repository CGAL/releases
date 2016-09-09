// ======================================================================
//
// Copyright (c) 1997,1998 The CGAL Consortium
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
// ----------------------------------------------------------------------
//
// release       : CGAL-1.1
// release_date  : 1998, July 24
//
// file          : include/CGAL/optimisation_basic.h
// package       : Optimisation_basic (3.0)
// chapter       : $CGAL_Chapter: Geometric Optimisation $
//
// source        : web/Optimisation/optimisation_basic.aw
// revision      : $Revision: 5.1 $
// revision_date : $Date: 1998/07/02 17:55:05 $
// author(s)     : Sven Schönherr
//
// coordinator   : ETH Zürich (Bernd Gärtner)
//
// implementation: basic things for optimisation algorithms
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_OPTIMISATION_BASIC_H
#define CGAL_OPTIMISATION_BASIC_H

// Function declarations
// =====================

// is_valid failure function
// -------------------------
#ifndef CGAL_IO_VERBOSE_OSTREAM_H
#  include <CGAL/IO/Verbose_ostream.h>
#endif

bool
CGAL__optimisation_is_valid_fail( CGAL_Verbose_ostream& verr,
                                  const char*           message);

#endif // CGAL_OPTIMISATION_BASIC_H

// ===== EOF ==================================================================
