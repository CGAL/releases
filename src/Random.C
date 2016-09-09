// ======================================================================
//
// Copyright (c) 1997-2001 The CGAL Consortium

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
// file          : src/Random.C
// package       : Random_numbers (2.3.1)
// chapter       : Random Numbers Generator
//
// source        : web/Random.aw
// revision      : $Revision: 1.1.2.2 $
// revision_date : $Date: 2001/04/02 18:49:08 $
//
// author(s)     : Sven Schönherr
// coordinator   : INRIA Sophia-Antipolis
//
// implementation: Random Numbers Generator
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#include <CGAL/Random.h>

// additional includes
#ifndef CGAL_PROTECT_CTIME
#  include <ctime>
#  define CGAL_PROTECT_CTIME
#endif

CGAL_BEGIN_NAMESPACE

// Class implementation (continued)
// ================================

// constructors
Random::
Random( )
    : rand_max_plus_1( RAND_MAX+1.0)
{
    // get system's time
    time_t s;
    time( &s);
    unsigned int  seed = s;

    // initialize random numbers generator
    srand( seed);
}

Random::
Random( unsigned int  seed)
    : rand_max_plus_1( RAND_MAX+1.0)
{
    // initialize random numbers generator
    srand( seed);
}

// Global variables
// ================
Random  default_random;

CGAL_END_NAMESPACE

// ===== EOF ==================================================================
