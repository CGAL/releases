// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : src/Random.C
// author(s)     : Sven Schönherr 
//                 N.N.
//
// email         : cgal@cs.uu.nl
//
// ============================================================================

#include <CGAL/Random.h>

// Class implementation (continued)
// ================================
// constructors
#ifndef CGAL_PROTECT_SYS_TIME_H
#  include <sys/time.h>
#endif

CGAL_Random::
CGAL_Random( )
{
    // get system's microseconds
    timeval tv;
    gettimeofday( &tv, NULL);
    unsigned long  ms = tv.tv_sec*1000000+tv.tv_usec;

    // initialize random numbers generator
    _seed[ 0] = _seed[ 2] = CGAL_static_cast( unsigned short, ms >> 16);
    _seed[ 1] =             CGAL_static_cast( unsigned short, ms & 65535);
}

CGAL_Random::
CGAL_Random( Seed seed)
{
    // initialize random numbers generator
    _seed[ 0] = seed[ 0];
    _seed[ 1] = seed[ 1];
    _seed[ 2] = seed[ 2];
}

CGAL_Random::
CGAL_Random( long init)
{
    // initialize random numbers generator
    _seed[ 0] = _seed[ 2] = CGAL_static_cast( unsigned short,init >> 16);
    _seed[ 1] =             CGAL_static_cast( unsigned short,init & 65535);
}



// seed functions
void
CGAL_Random::
save_seed( Seed& seed) const
{
    seed[ 0] = _seed[ 0];
    seed[ 1] = _seed[ 1];
    seed[ 2] = _seed[ 2];
}

void
CGAL_Random::
restore_seed( Seed const& seed)
{
    _seed[ 0] = seed[ 0];
    _seed[ 1] = seed[ 1];
    _seed[ 2] = seed[ 2];
}

// Global variables
// ================
CGAL_Random  CGAL_random;

// ===== EOF ==================================================================
