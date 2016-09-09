// Copyright (c) 1997-2001  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Random_numbers/include/CGAL/Random.h $
// $Id: Random.h 46871 2008-11-13 14:40:48Z gaertner $
// 
//
// Author(s)     : Sven Schoenherr <sven@inf.ethz.ch>, Sylvain Pion

#ifndef CGAL_RANDOM_H
#define CGAL_RANDOM_H

#include <utility>
#include <CGAL/basic.h>

CGAL_BEGIN_NAMESPACE

class Random {
  public:
    // types
    typedef std::pair<unsigned int, unsigned int> State;

    // creation
    Random( );
    Random( unsigned int  seed);

    // seed
    unsigned int get_seed ( ) const;
    
    // operations
    bool    get_bool  ( );
    int     get_int   ( int lower, int upper);
    double  get_double( double lower = 0.0, double upper = 1.0);

    // state 
    void save_state( State& state) const;
    void restore_state( const State& state);

    // Computes a random int value smaller than 2^b.
    // It's supposed to be fast, useful for randomized algorithms.
    // The distribution is not perfectly flat, but this is a sacrifice against
    // efficiency.
    template <int b>
    int get_bits()
    {
	CGAL_assertion(0<b && b<16);
        if (val == 0) {
            random_value = (421U * random_value + 2073U) % 32749U;
            val = random_value;
        }
        int ret = val & ((1<<b)-1);
        val >>= 1; // Shifting by b would be slightly better, but is slower.
        return ret;
    }

    int     operator () ( int upper);

  bool    operator==(Random rd) const
  {
    return 
      rd.rand_max_plus_1 == rand_max_plus_1 &&
      rd.random_value == random_value &&
      rd.val == val;
  }
  private:
    // data members
    const double  rand_max_plus_1;
    unsigned int random_value; // Current 15 bits random value.
    unsigned int val; // random_value shifted by used bits.
    unsigned int seed; 
};

// Global variables
// ================
extern  Random  default_random;

CGAL_END_NAMESPACE

// ============================================================================

// Class implementation (inline functions)
// =======================================
// includes
#  include <cstdlib>

CGAL_BEGIN_NAMESPACE

// operations
inline
bool
Random::
get_bool( )
{
    return( static_cast< bool>( std::rand() & 1));
}

inline
int
Random::
get_int( int lower, int upper)
{
    return( lower + static_cast< int>(
      ( static_cast< double>( upper) - lower) * 
      std::rand() / rand_max_plus_1));
}

inline
double
Random::
get_double( double lower, double upper)
{
    return( lower + ( ( upper-lower) * 
		      std::rand() / rand_max_plus_1));
}

inline
int
Random::
operator () ( int upper)
{
    return( get_int( 0, upper));
}

CGAL_END_NAMESPACE

#endif // CGAL_RANDOM_H

// ===== EOF ==================================================================
