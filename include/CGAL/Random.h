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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/Random.h
// package       : Random (1.12)
// chapter       : $CGAL_Chapter: Random Sources and Geometric Object Genera. $
//
// source        : web/Random/Random.aw
// revision      : $Revision: 1.15 $
// revision_date : $Date: 1998/05/15 09:33:52 $
// author(s)     : Sven Schönherr
//
// coordinator   : INRIA Sophia-Antipolis (<Herve.Bronnimann>)
//
// implementation: Random Numbers Generator
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

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
#ifndef CGAL_PROTECT_STDLIB_H
#  include <stdlib.h>
#endif

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
