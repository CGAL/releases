// Copyright (c) 2006-2007 Max-Planck-Institute Saarbruecken (Germany).
// All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/Number_types/include/CGAL/CORE_BigInt.h $
// $Id: CORE_BigInt.h 38140 2007-04-16 08:57:45Z hemmer $
//
//
// Author(s)     : Michael Hemmer   <hemmer@mpi-inf.mpg.de>


#ifndef CGAL_CORE_BIGINT_H
#define CGAL_CORE_BIGINT_H

#include <CGAL/number_type_basic.h>
#include <CGAL/CORE_coercion_traits.h>

CGAL_BEGIN_NAMESPACE

//
// Algebraic structure traits
//
template <> class Algebraic_structure_traits< CORE::BigInt >
  : public Algebraic_structure_traits_base< CORE::BigInt,
                                            Euclidean_ring_tag >  {
  public:
    typedef Tag_true            Is_exact;
    typedef Tag_false           Is_numerical_sensitive;

    typedef INTERN_AST::Is_square_per_sqrt< Type >
                                                                 Is_square;

    typedef INTERN_AST::Div_per_operator< Type > Div;
    typedef INTERN_AST::Mod_per_operator< Type > Mod;

    class Sqrt
      : public Unary_function< Type, Type > {
      public:
        //! computes the largest NT not larger than the square root of \a a.
        Type operator()( const Type& x) const {
          Type result;
          mpz_sqrt(result.get_mp(), x.get_mp());
          return result;
        }
    };


    class Gcd
      : public Binary_function< Type, Type,
                                Type > {
      public:
        Type operator()( const Type& x,
                                        const Type& y) const {
          if ( x == Type(0) && y == Type(0) )
              return Type(0);
          Type result;
          mpz_gcd(result.get_mp(), x.get_mp(), y.get_mp());
          return result;
        }
    };
};

//
// Real embeddable traits
//
template <> class Real_embeddable_traits< CORE::BigInt >
  : public Real_embeddable_traits_base< CORE::BigInt > {

  public:

    class Abs
      : public Unary_function< Type, Type > {
      public:
        Type operator()( const Type& x ) const {
          return CORE::abs( x );
        }
    };

    class Sign
      : public Unary_function< Type, ::CGAL::Sign > {
      public:
        ::CGAL::Sign operator()( const Type& x ) const {
          return (::CGAL::Sign) CORE::sign( x );
        }
    };

    class Compare
      : public Binary_function< Type, Type,
                                Comparison_result > {
      public:
        Comparison_result operator()( const Type& x,
                                            const Type& y ) const {
          typedef Real_embeddable_traits<int> Int_traits;
          return Int_traits::Sign()( ::CORE::cmp(x,y));
        }
    };

    class To_double
      : public Unary_function< Type, double > {
      public:
        double operator()( const Type& x ) const {
          // this call is required to get reasonable values for the double
          // approximation
          return x.doubleValue();
        }
    };

    class To_interval
      : public Unary_function< Type, std::pair< double, double > > {
      public:
        std::pair<double, double> operator()( const Type& x_ ) const {
            CORE::Expr x(x_);
            std::pair<double,double> result;
            x.doubleInterval(result.first, result.second);
            CGAL_expensive_assertion(result.first  <= x);
            CGAL_expensive_assertion(result.second >= x);
            return result;
        }
    };
};

template<>
struct Needs_parens_as_product<CORE::BigInt>{
    bool operator()(const CORE::BigInt& x){
        return CGAL_NTS is_negative(x);
    }
};

CGAL_END_NAMESPACE

//since types are included by CORE_coercion_traits.h:
#include <CGAL/CORE_Expr.h>
#include <CGAL/CORE_BigInt.h>
#include <CGAL/CORE_BigRat.h>
#include <CGAL/CORE_BigFloat.h>

#endif // CGAL_CORE_BIGINT_H
