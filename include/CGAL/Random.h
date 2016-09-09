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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Random_numbers/include/CGAL/Random.h $
// $Id: Random.h 58591 2010-09-10 09:10:02Z afabri $
// 
//
// Author(s)     : Sven Schoenherr <sven@inf.ethz.ch>, Sylvain Pion, Andreas Fabri

#ifndef CGAL_RANDOM_H
#define CGAL_RANDOM_H

#include <string>
#include <utility>
#include <CGAL/basic.h>

#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_smallint.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/uniform_01.hpp>
#include <boost/random/variate_generator.hpp>


namespace CGAL {

class Random {
  public:
    // types

 struct State {
    std::string rng;
    unsigned int random_value, val, seed;

    State()
    {}

    State(std::string rng, 
          unsigned int random_value, 
          unsigned int val, 
          unsigned int seed)
      : rng(rng), random_value(random_value), val(val), seed(seed)
    {}
 };
    // creation
    Random( );
    Random( unsigned int  seed);

    // seed
    unsigned int get_seed ( ) const;
    
    // operations
    bool get_bool( )
  {
    return( static_cast< bool>( rng() & 1));
  }


  template <typename IntType>
  IntType
  uniform_smallint(IntType lower, IntType upper)
  {
    // uniform_smallint has a closed interval, CGAL a halfopen
    boost::uniform_smallint<IntType> dist(lower,upper-1);
    boost::variate_generator<boost::rand48&, boost::uniform_smallint<IntType> > generator(rng,dist);
    
    return generator();
  }

  template <typename IntType>
  IntType
  uniform_smallint(IntType lower)
  {
    return uniform_smallint<IntType>(lower,9);
  }

  template <typename IntType>
  IntType
  uniform_smallint()
  {
    return uniform_smallint<IntType>(0,9);
  }

  template <typename IntType>
  IntType
  uniform_int(IntType lower, IntType upper)
  {
    // uniform_int has a closed interval, CGAL a halfopen
    boost::uniform_int<IntType> dist(lower,upper);
    boost::variate_generator<boost::rand48&, boost::uniform_int<IntType> > generator(rng,dist);
    
    return generator();
  }


  template <typename IntType>
  IntType
  uniform_int(IntType lower)
  {
    return uniform_int<IntType>(lower,9);
  }

  template <typename IntType>
  IntType
  uniform_int()
  {
    return uniform_int<IntType>(0,9);
  }
 

  
  template <typename IntType>
  IntType
  operator () (IntType upper)
  {
    return uniform_int<IntType>(0, upper-1);
  }
 
  int
  get_int(int lower, int upper)
  {
    return uniform_int<int>(lower,upper-1);
  }


  template <typename RealType>
  RealType
  uniform_real( RealType lower, RealType upper)
  {
    // uniform_real as well as CGAL have a halfopen interval
    boost::uniform_real<RealType> dist(lower,upper);
    boost::variate_generator<boost::rand48&, boost::uniform_real<RealType> > generator(rng,dist);
    
    return generator();
  }


  template <typename RealType>
  RealType
  uniform_real( RealType lower)
  {
    return uniform_real<RealType>(lower, 1.0);
  }


  template <typename RealType>
  RealType
  uniform_real()
  {
    return uniform_real<RealType>(0.0, 1.0);
  }


  template <typename RealType>
  RealType
  uniform_01()
  {
    // uniform_01 as well as CGAL have a halfopen interval
    boost::uniform_01<RealType> dist;
    boost::variate_generator<boost::rand48&, boost::uniform_01<RealType> > generator(rng,dist);
    
    return generator();
  }


  double
  get_double( double lower = 0.0, double upper = 1.0)
  {
    return uniform_real<double>(lower, upper);
  }

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

    
  bool    operator==(Random rd) const
  {
    return (rng == rd.rng) 
      && (random_value == rd.random_value)
      && (val == rd.val)
      && (seed == rd.seed);
  }

  private:
    // data members
    unsigned int random_value; // Current 15 bits random value.
    unsigned int val; // random_value shifted by used bits.
    unsigned int seed; 
    boost::rand48 rng;
};

// Global variables
// ================
extern  Random  default_random;

} //namespace CGAL

#endif // CGAL_RANDOM_H


