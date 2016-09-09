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
// file          : src/optimisation_basic.C
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

#include <CGAL/Optimisation/basic.h>

CGAL_BEGIN_NAMESPACE

// Function implementations
// ========================

// is_valid failure function
// -------------------------
bool
_optimisation_is_valid_fail( CGAL::Verbose_ostream& verr,
                             const char*            message)
{
    verr << "FAILED." << std::endl;
    verr << "  --> " << message << std::endl;
    verr << "  object is NOT valid!" << std::endl;
    return( false);
}

CGAL_END_NAMESPACE

// ===== EOF ==================================================================
