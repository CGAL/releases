// ======================================================================
//
// Copyright (c) 1997-2000 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------
//
// release       : $CGAL_Revision: CGAL-2.2-I-51 $
// release_date  : $CGAL_Date: 2000/10/01 $
//
// file          : include/CGAL/Optimisation/basic.h
// package       : Optimisation_basic (3.8.2)
// maintainer    : Sven Schönherr <sven@inf.ethz.ch>
// chapter       : $CGAL_Chapter: Geometric Optimisation $
//
// source        : web/Optimisation_basic.aw
// revision      : $Revision: 5.8 $
// revision_date : $Date: 2000/09/05 17:05:55 $
//
// author(s)     : Sven Schönherr
// coordinator   : ETH Zürich (Bernd Gärtner <gaertner@inf.ethz.ch>)
//
// implementation: basic things for optimisation algorithms
// ======================================================================

#ifndef CGAL_OPTIMISATION_BASIC_H
#define CGAL_OPTIMISATION_BASIC_H

// includes
#ifndef CGAL_BASIC_H
#  include <CGAL/basic.h>
#endif
#ifndef CGAL_OPTIMISATION_ASSERTIONS_H
#  include <CGAL/Optimisation/assertions.h>
#endif
#ifndef CGAL_OPTIMISATION_DEBUG_H
#  include <CGAL/Optimisation/debug.h>
#endif
#ifndef CGAL_IO_VERBOSE_OSTREAM_H
#  include <CGAL/IO/Verbose_ostream.h>
#endif

CGAL_BEGIN_NAMESPACE

// Function declarations
// =====================

// is_valid failure function
// -------------------------
bool
_optimisation_is_valid_fail( CGAL::Verbose_ostream& verr,
                             const char*            message);

CGAL_END_NAMESPACE

#endif // CGAL_OPTIMISATION_BASIC_H

// ===== EOF ==================================================================
