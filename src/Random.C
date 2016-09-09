// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : src/Random.C
// package       : Random_numbers (2.0.1)
// chapter       : $CGAL_Chapter: Random Numbers Generator $
//
// source        : web/Random_numbers/Random.aw
// revision      : $Revision: 2.2 $
// revision_date : $Date: 1999/03/04 16:45:35 $
// author(s)     : Sven Schönherr
//
// coordinator   : INRIA Sophia-Antipolis (<Herve.Bronnimann>)
//
// implementation: Random Numbers Generator
// email         : cgal@cs.uu.nl
//
// ======================================================================

#include <CGAL/Random.h>

// additional includes
#ifndef CGAL_PROTECT_CTIME
#  include <ctime>
#  define CGAL_PROTECT_CTIME
#endif
#ifndef CGAL_PROTECT_SYS_TIME_H
#  include <sys/time.h>
#  define CGAL_PROTECT_SYS_TIME_H
#endif

CGAL_BEGIN_NAMESPACE

// Class implementation (continued)
// ================================

// constructors
Random::
Random( )
{
    // get system's microseconds
    timeval tv;
    gettimeofday( &tv, NULL);
    unsigned long  ms = tv.tv_sec*1000000+tv.tv_usec;

    // initialize random numbers generator
    _state[ 0] = _state[ 2] = CGAL_static_cast( unsigned short, ms >> 16);
    _state[ 1] =            CGAL_static_cast( unsigned short, ms & 65535);
}

Random::
Random( long seed)
{
    // initialize random numbers generator
    _state[ 0] = _state[ 2] = CGAL_static_cast( unsigned short,seed >> 16);
    _state[ 1] =            CGAL_static_cast( unsigned short,seed & 65535);
}

Random::
Random( State state)
{
    // initialize random numbers generator
    _state[ 0] = state[ 0];
    _state[ 1] = state[ 1];
    _state[ 2] = state[ 2];
}

// state functions
void
Random::
save_state( State& state) const
{
    state[ 0] = _state[ 0];
    state[ 1] = _state[ 1];
    state[ 2] = _state[ 2];
}

void
Random::
restore_state( const State& state)
{
    _state[ 0] = state[ 0];
    _state[ 1] = state[ 1];
    _state[ 2] = state[ 2];
}

// Global variables
// ================
Random  default_random;

CGAL_END_NAMESPACE

// ===== EOF ==================================================================
