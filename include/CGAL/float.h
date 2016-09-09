// Copyright (c) 1999,2007  Utrecht University (The Netherlands),
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/Number_types/include/CGAL/float.h $
// $Id: float.h 37955 2007-04-05 13:02:19Z spion $
//
//
// Author(s)     : Geert-Jan Giezeman, Michael Hemmer


#ifndef CGAL_FLOAT_H
#define CGAL_FLOAT_H

#include <CGAL/number_type_basic.h>

#include <cmath> // std::sqrt, std::pow

#ifdef CGAL_CFG_IEEE_754_BUG
#  include <CGAL/IEEE_754_unions.h>
#endif
#ifdef __sgi
#  include <fp_class.h>
#endif

CGAL_BEGIN_NAMESPACE

#ifdef __sgi

template<>
class Is_valid< float >
  : public Unary_function< float, bool > {
  public :
    bool operator()( const float& x ) const {
      switch (fp_class_f(x)) {
      case FP_POS_NORM:
      case FP_NEG_NORM:
      case FP_POS_ZERO:
      case FP_NEG_ZERO:
      case FP_POS_INF:
      case FP_NEG_INF:
      case FP_POS_DENORM:
      case FP_NEG_DENORM:
          return true;
      case FP_SNAN:
      case FP_QNAN:
          return false;
      }
      return false; // NOT REACHED
    }
};

#elif defined CGAL_CFG_IEEE_754_BUG

#define CGAL_EXPONENT_FLOAT_MASK   0x7f800000
#define CGAL_MANTISSA_FLOAT_MASK   0x007fffff

inline
bool
is_finite_by_mask_float(unsigned int u)
{
  unsigned int e = u & CGAL_EXPONENT_FLOAT_MASK;
  return ( (e ^ CGAL_EXPONENT_FLOAT_MASK) != 0);
}

inline
bool
is_nan_by_mask_float(unsigned int u)
{
  if ( is_finite_by_mask_float(u) ) return false;
  // unsigned int m = u & CGAL_MANTISSA_FLOAT_MASK;
  return ( (u & CGAL_MANTISSA_FLOAT_MASK) != 0);
}

template<>
class Is_valid< float >
  : public Unary_function< float, bool > {
  public :
    bool operator()( const float& x ) const {
      float f = x;
      IEEE_754_float* p = reinterpret_cast<IEEE_754_float*>(&f);
      return !is_nan_by_mask_float( p->c );
    }
};

#else

template<>
class Is_valid< float >
  : public Unary_function< float, bool > {
  public :
    bool operator()( const float& x ) const {
      return (x == x);
    }
};

#endif

template <> class Algebraic_structure_traits< float >
  : public Algebraic_structure_traits_base< float,
                                            Field_with_kth_root_tag >  {
  public:
    typedef Tag_false            Is_exact;
    typedef Tag_true             Is_numerical_sensitive;

    class Sqrt
      : public Unary_function< Type, Type > {
      public:
        Type operator()( const Type& x ) const {
          return CGAL_CLIB_STD::sqrt( x );
        }
    };

    class Kth_root
      : public Binary_function<int, Type, Type> {
      public:
        Type operator()( int k,
                                        const Type& x) const {
          CGAL_precondition_msg( k > 0, "'k' must be positive for k-th roots");
          return CGAL_CLIB_STD::pow(double(x), 1.0 / double(k));
        };
    };

};

template <> class Real_embeddable_traits< float >
  : public Real_embeddable_traits_base< float > {
  public:

    typedef INTERN_RET::To_double_by_conversion< Type >
                                                                  To_double;
    typedef INTERN_RET::To_interval_by_conversion< Type >
                                                                  To_interval;
// Is_finite depends on platform
#ifdef __sgi

    class Is_finite
      : public Unary_function< Type, bool > {
      public:
        bool operator()( const Type& x ) const {
          switch (fp_class_f(x)) {
          case FP_POS_NORM:
          case FP_NEG_NORM:
          case FP_POS_ZERO:
          case FP_NEG_ZERO:
          case FP_POS_DENORM:
          case FP_NEG_DENORM:
              return true;
          case FP_SNAN:
          case FP_QNAN:
          case FP_POS_INF:
          case FP_NEG_INF:
              return false;
          }
          return false; // NOT REACHED
        }
    };

#elif defined CGAL_CFG_IEEE_754_BUG

    class Is_finite
      : public Unary_function< Type, bool > {
      public:
        bool operator()( const Type& x ) const {
          Type f = x;
          IEEE_754_float* p = reinterpret_cast<IEEE_754_float*>(&f);
          return is_finite_by_mask_float( p->c );
        }
    };
#else
    class Is_finite
      : public Unary_function< Type, bool > {
      public:
        bool operator()( const Type& x ) const {
          return (x == x) && (is_valid(x-x));
        }
    };

#endif

};

CGAL_END_NAMESPACE

#endif // CGAL_FLOAT_H
