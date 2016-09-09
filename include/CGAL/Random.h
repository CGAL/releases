/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/


// file  : include/CGAL/Random.h
// source: web/Random.aw
// author: Sven Schönherr
// $Revision: 1.8 $
// $Date: 1997/06/11 16:15:11 $

#ifndef CGAL_RANDOM_H
#define CGAL_RANDOM_H

// Class declaration
// =================
class CGAL_Random;

// Class interface
// ===============
// includes
#ifndef CGAL_BASIC_H
#  include <CGAL/basic.h>
#endif

class CGAL_Random {
  public:
    // types
    typedef  unsigned short  Seed[3];                   // 48 Bits
    
    // creation
    CGAL_Random( );
    CGAL_Random( Seed seed);
    CGAL_Random( long init);
    
    // operations
    bool    get_bool  ( );
    int     get_int   ( int lower, int upper);
    double  get_double( double lower = 0.0, double upper = 1.0);
    
    int     operator () ( int upper);
    
    // seed functions
    void       save_seed( Seed      & seed) const;
    void    restore_seed( Seed const& seed);
    
    // equality test
    bool  operator == ( CGAL_Random const& rnd) const;

  private:
    // data members
    unsigned short  _seed[3];                           // 48 Bits
};

// Global variables
// ================
extern  CGAL_Random  CGAL_random;

// ============================================================================

// Class implementation (inline functions)
// =======================================
// operations
#include <stdlib.h>

inline
bool
CGAL_Random::
get_bool( )
{
    return( CGAL_static_cast( bool, ( erand48( _seed) >= 0.5)));
}

inline
int
CGAL_Random::
get_int( int lower, int upper)
{
    return( lower + CGAL_static_cast( int,
              CGAL_static_cast( double, upper-lower) * erand48( _seed)));
}

inline
double
CGAL_Random::
get_double( double lower, double upper)
{
    return( lower + ( upper-lower) * erand48( _seed));
}

inline
int
CGAL_Random::
operator () ( int upper)
{
    return( get_int( 0, upper));
}

inline
bool
CGAL_Random::
operator == ( CGAL_Random const& rnd) const
{
    return( CGAL_static_cast( bool,
                ( _seed[ 0] == rnd._seed[ 0]) &&
                ( _seed[ 1] == rnd._seed[ 1]) &&
                ( _seed[ 2] == rnd._seed[ 2]) ) );
}

#endif // CGAL_RANDOM_H

// ===== EOF ==================================================================
