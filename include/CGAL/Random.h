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
// file          : include/CGAL/Random.h
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

#ifndef CGAL_RANDOM_H
#define CGAL_RANDOM_H

// includes
#ifndef CGAL_BASIC_H
#  include <CGAL/basic.h>
#endif

CGAL_BEGIN_NAMESPACE

// Class declaration
// =================
class Random;

// Class interface
// ===============
class Random {
  public:
    // types
    typedef  unsigned short  State[3];                  // 48 Bits
    
    // creation
    Random( );
    Random( long seed);
    Random( State state);
    
    // operations
    bool    get_bool  ( );
    int     get_int   ( int lower, int upper);
    double  get_double( double lower = 0.0, double upper = 1.0);
    
    int     operator () ( int upper);
    
    // state functions
    void       save_state(       State& state) const;
    void    restore_state( const State& state);
    
    // equality test
    bool  operator == ( const Random& rnd) const;

  private:
    // data members
    unsigned short  _state[3];                          // 48 Bits
};

// Global variables
// ================
extern  Random  default_random;

CGAL_END_NAMESPACE

// ============================================================================

// Class implementation (inline functions)
// =======================================
// includes
#ifndef CGAL_PROTECT_CSTDLIB
#  include <cstdlib>
#  define CGAL_PROTECT_CSTDLIB
#endif

CGAL_BEGIN_NAMESPACE

// operations
inline
bool
Random::
get_bool( )
{
    return( CGAL_static_cast( bool, ( erand48( _state) >= 0.5)));
}

inline
int
Random::
get_int( int lower, int upper)
{
    return( lower + CGAL_static_cast( int,
        CGAL_static_cast( double, upper-lower) * erand48( _state)));
}

inline
double
Random::
get_double( double lower, double upper)
{
    return( lower + ( upper-lower) * erand48( _state));
}

inline
int
Random::
operator () ( int upper)
{
    return( get_int( 0, upper));
}

inline
bool
Random::
operator == ( const Random& rnd) const
{
    return( CGAL_static_cast( bool,
                ( _state[ 0] == rnd._state[ 0]) &&
                ( _state[ 1] == rnd._state[ 1]) &&
                ( _state[ 2] == rnd._state[ 2]) ) );
}

CGAL_END_NAMESPACE

#endif // CGAL_RANDOM_H

// ===== EOF ==================================================================
