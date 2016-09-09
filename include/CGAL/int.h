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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/Number_types/include/CGAL/int.h $
// $Id: int.h 37955 2007-04-05 13:02:19Z spion $
//
//
// Author(s)     : Stefan Schirra, Michael Hemmer


#ifndef CGAL_INT_H
#define CGAL_INT_H

#include <CGAL/number_type_basic.h>

CGAL_BEGIN_NAMESPACE

namespace INTERN_INT {
    template< class Type >
    class Is_square_per_double_conversion
      : public Binary_function< Type, Type&,
                                bool > {
      public:
        bool operator()( const Type& x,
                         Type& y ) const {
          y = (Type) CGAL_CLIB_STD::sqrt( (double)x );
          return x == y * y;
        }
        bool operator()( const Type& x ) const {
            Type y =
                (Type) CGAL_CLIB_STD::sqrt( (double)x );
            return x == y * y;
        }

    };
} // INTERN_INT

// int
template<> class Algebraic_structure_traits< int >
  : public Algebraic_structure_traits_base< int, Euclidean_ring_tag > {

  public:
    typedef Tag_true            Is_exact;
    typedef Tag_false           Is_numerical_sensitive;

    typedef INTERN_AST::Div_per_operator< Type >  Div;
    typedef INTERN_AST::Mod_per_operator< Type >  Mod;

    typedef INTERN_INT::
       Is_square_per_double_conversion< Type > Is_square;
};

template <> class Real_embeddable_traits< int >
  : public Real_embeddable_traits_base< int > {
  public:

    typedef INTERN_RET::To_double_by_conversion< Type >
                                                                      To_double;
    typedef INTERN_RET::To_interval_by_conversion< Type >
                                                                    To_interval;
};

// long

template<> class Algebraic_structure_traits< long int >
  : public Algebraic_structure_traits_base< long int,
                                            Euclidean_ring_tag > {

  public:
    typedef Tag_true            Is_exact;
    typedef Tag_false           Is_numerical_sensitive;

    typedef INTERN_AST::Div_per_operator< Type >  Div;
    typedef INTERN_AST::Mod_per_operator< Type >  Mod;

    typedef INTERN_INT::
       Is_square_per_double_conversion< Type > Is_square;
};

template <> class Real_embeddable_traits< long int >
  : public Real_embeddable_traits_base< long int > {
  public:

    typedef INTERN_RET::To_double_by_conversion< Type >
                                                                      To_double;
    typedef INTERN_RET::To_interval_by_conversion< Type >
                                                                    To_interval;
};

// short

template<> class Algebraic_structure_traits< short int >
  : public Algebraic_structure_traits_base< short int,
                                            Euclidean_ring_tag > {

  public:
    typedef Tag_true            Is_exact;
    typedef Tag_false           Is_numerical_sensitive;

    // Explicitly defined functors which have no support for implicit
    //  interoperability. This is nescessary because of the implicit conversion
    //  to int for binary operations between short ints.
    class Integral_division
      : public Binary_function< Type, Type,
                                Type > {
      public:
        Type operator()( const Type& x,
                                        const Type& y) const {
          Algebraic_structure_traits<Type>::Div actual_div;
          CGAL_precondition_msg( actual_div( x, y) * y == x,
                  "'x' must be divisible by 'y' in "
                  "Algebraic_structure_traits<...>::Integral_div()(x,y)" );
          return actual_div( x, y);
        }
    };

    class Gcd
      : public Binary_function< Type, Type,
                                Type > {
      public:
        Type operator()( const Type& x,
                                        const Type& y) const {
          Algebraic_structure_traits<Type>::Mod mod;
          Algebraic_structure_traits<Type>::Unit_part unit_part;
          Algebraic_structure_traits<Type>::Integral_division integral_div;
          // First: the extreme cases and negative sign corrections.
          if (x == Type(0)) {
              if (y == Type(0))
                  return Type(0);
              return integral_div( y, unit_part(y) );
          }
          if (y == Type(0))
              return integral_div(x, unit_part(x) );
          Type u = integral_div( x, unit_part(x) );
          Type v = integral_div( y, unit_part(y) );
          // Second: assuming mod is the most expensive op here, we don't compute it
          // unnecessarily if u < v
          if (u < v) {
              v = mod(v,u);
              // maintain invariant of v > 0 for the loop below
              if ( v == Type(0) )
                  return u;
          }

          Type w;
          do {
              w = mod(u,v);
              if ( w == Type(0))
                  return v;
              u = mod(v,w);
              if ( u == Type(0))
                  return w;
              v = mod(w,u);
          } while (v != Type(0));
          return u;
        }
    };

    class Div_mod {
      public:
        typedef Type    first_argument_type;
        typedef Type    second_argument_type;
        typedef Type&   third_argument_type;
        typedef Type&   fourth_argument_type;
        typedef Arity_tag< 4 >         Arity;
        typedef void  result_type;
        void operator()( const Type& x,
                         const Type& y,
                         Type& q, Type& r) const {
          q = x / y;
          r = x % y;
          return;
        }
    };

    // based on \c Div_mod.
    class Div
      : public Binary_function< Type, Type,
                                Type > {
      public:
        Type operator()( const Type& x,
                                        const Type& y) const {
          return x / y;
        };
    };

    // based on \c Div_mod.
    class Mod
      : public Binary_function< Type, Type,
                                Type > {
      public:
        Type operator()( const Type& x,
                                        const Type& y) const {
          return x % y;
        };
    };

    typedef INTERN_INT::
       Is_square_per_double_conversion< Type > Is_square;
};

template <> class Real_embeddable_traits< short int >
  : public Real_embeddable_traits_base< short int > {
  public:

    typedef INTERN_RET::To_double_by_conversion< Type >
                                                                      To_double;
    typedef INTERN_RET::To_interval_by_conversion< Type >
                                                                    To_interval;
};

// Note : "long long" support is in <CGAL/long_long.h>

CGAL_END_NAMESPACE

#endif // CGAL_INT_H
