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
// file          : include/CGAL/Optimisation/debug.h
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
// implementation: debug macro for optimisation algorithms
// ======================================================================

#ifndef CGAL_OPTIMISATION_DEBUG_H
#define CGAL_OPTIMISATION_DEBUG_H

// macro definitions
// =================

// debug
// -----
#if (    defined( CGAL_OPTIMISATION_NO_DEBUG) \
      || defined( CGAL_NO_DEGUG) || defined( NDEBUG))
#  define  CGAL_optimisation_debug  if ( 0)
#else
#  define  CGAL_optimisation_debug  if ( 1)
#endif // optimisation debug

#endif // CGAL_OPTIMISATION_DEBUG_H

// ===== EOF ==================================================================
