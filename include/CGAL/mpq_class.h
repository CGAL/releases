// Copyright (c) 2002,2003  Utrecht University (The Netherlands),
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Number_types/include/CGAL/mpq_class.h $
// $Id: mpq_class.h 45748 2008-09-25 09:13:21Z hemmer $
//
//
// Author(s)     : Sylvain Pion, Michael Hemmer

#ifndef CGAL_MPQ_CLASS_H
#define CGAL_MPQ_CLASS_H

#include <CGAL/number_type_basic.h>
#include <CGAL/gmpxx_coercion_traits.h>
#include <CGAL/mpz_class.h> // for GCD in Type traits

// This file gathers the necessary adaptors so that the following
// C++ number types that come with GMP can be used by CGAL :
// - mpq_class

// Note that GMP++ use the expression template mechanism, which makes things
// a little bit complicated in order to make square(x+y) work for example.
// Reading gmpxx.h shows that ::__gmp_expr<T, T> is the mp[zqf]_class proper,
// while ::__gmp_expr<T, U> is the others "expressions".

#define CGAL_CHECK_GMP_EXPR                                             \
    BOOST_STATIC_ASSERT(                                                \
            (::boost::is_same< ::__gmp_expr< T , T >,Type>::value ));

CGAL_BEGIN_NAMESPACE


// AST for mpq_class
template<>
class Algebraic_structure_traits< mpq_class  >
  : public Algebraic_structure_traits_base< mpq_class , Field_tag >  {
  public:
    typedef mpq_class           Type;
    typedef Field_tag           Algebraic_category;
    typedef Tag_true            Is_exact;
    typedef Tag_false           Is_numerical_sensitive;

    struct Is_zero: public std::unary_function< mpq_class , bool > {
        template <class T, class U>
        bool operator()( const ::__gmp_expr< T , U >& x) const {
            CGAL_CHECK_GMP_EXPR;
            return ::sgn(x) == 0;
        }
    };

    struct Is_one: public std::unary_function< mpq_class , bool > {
        template <typename T, typename U>
        bool operator()( const ::__gmp_expr< T , U >& x) const {
            CGAL_CHECK_GMP_EXPR;
            return x == 1;
        }
    };

    struct Simplify: public std::unary_function< mpq_class , void > {
        template <typename T, typename U>
        void operator()( ::__gmp_expr< T, U>& x) const {
            CGAL_CHECK_GMP_EXPR;
          //TODO: cast x to (mpq_class)??
          x.canonicalize();
        }

        template <class T, class U>
        bool operator()( const ::__gmp_expr< T ,U >& x) const {
            CGAL_CHECK_GMP_EXPR;
            return x.canonicalize();
        }
    };

    struct Square: public std::unary_function< mpq_class , mpq_class > {
        template <typename T, typename U>
        mpq_class operator()( const ::__gmp_expr< T , U >& x) const {
            CGAL_CHECK_GMP_EXPR;
            return x*x;
        }
    };

    struct Unit_part: public std::unary_function< mpq_class , mpq_class > {
        template <typename T, typename U>
        mpq_class operator()( const ::__gmp_expr< T , U >& x) const {
            CGAL_CHECK_GMP_EXPR;
            return( x == mpq_class(0)) ? mpq_class(1) : x;
        }
    };

    struct Integral_division
        : public std::binary_function< mpq_class , mpq_class, mpq_class > {
        template <typename T,  typename U1, typename U2>
        mpq_class operator()(
                const ::__gmp_expr< T , U1 >& x,
                const ::__gmp_expr< T , U2 > & y) const {
            CGAL_CHECK_GMP_EXPR;
            mpq_class result = x / y;
            CGAL_precondition_msg( result * y == x,
            "'x' must be divisible by 'y' in "
            "Algebraic_structure_traits<mpq_class>::Integral_div()(x,y)" );
            return result;
        }
        CGAL_IMPLICIT_INTEROPERABLE_BINARY_OPERATOR( Type )
    };

    class Is_square
        : public std::binary_function< mpq_class, mpq_class&, bool > {
    public:
        template <typename T , typename U >
        bool operator()(
                const ::__gmp_expr< T , U >& x_,
                mpq_class& y ) const {
            CGAL_CHECK_GMP_EXPR;
            mpq_class x( x_ );
            y = mpq_class (::sqrt( x.get_num() ), ::sqrt( x.get_den() )) ;

            return y*y == x;
        }

        template < typename T, typename U >
        bool operator()( const ::__gmp_expr< T , U >& x ) const {
            CGAL_CHECK_GMP_EXPR;
            mpq_class y;
            return operator()(x,y);
        }
    };
};

// RET for mpq_class

template < >
class Real_embeddable_traits< mpq_class >
  : public INTERN_RET::Real_embeddable_traits_base< mpq_class , CGAL::Tag_true > {
  public:

    struct Is_zero: public std::unary_function< mpq_class , bool > {
        template <typename T, typename U>
        bool operator()( const ::__gmp_expr< T , U >& x) const {
            CGAL_CHECK_GMP_EXPR;
            return ::sgn(x) == 0;
        }
    };
    struct Is_finite: public std::unary_function<mpq_class,bool> {
        template <typename T, typename U>
        bool operator()( const ::__gmp_expr< T , U >&) const {
            CGAL_CHECK_GMP_EXPR;
            return true;
        }
    };

    struct Is_positive: public std::unary_function< mpq_class , bool > {
        template <typename T, typename U>
        bool operator()( const ::__gmp_expr< T , U >& x) const {
            CGAL_CHECK_GMP_EXPR;
            return ::sgn(x) > 0;
        }
    };

    struct Is_negative: public std::unary_function< mpq_class , bool > {
        template <typename T, typename U>
        bool operator()( const ::__gmp_expr< T , U >& x) const {
            CGAL_CHECK_GMP_EXPR;
            return ::sgn(x) < 0;
        }
    };

    struct Abs: public std::unary_function< mpq_class , mpq_class > {
        template <typename T, typename U>
        mpq_class operator()( const ::__gmp_expr< T , U >& x) const {
            CGAL_CHECK_GMP_EXPR;
            return ::abs(x);
        }
    };

    struct Sgn
        : public std::unary_function< mpq_class, ::CGAL::Sign > {
    public:
        template <typename T, typename U>
        ::CGAL::Sign
        operator()( const ::__gmp_expr< T , U >& x ) const {
            CGAL_CHECK_GMP_EXPR;
            return (::CGAL::Sign) ::sgn( x );
        }
    };

    struct Compare
        : public std::binary_function< mpq_class, mpq_class, Comparison_result>
    {
        template <typename T, typename U1, typename U2>
        Comparison_result operator()(
                const ::__gmp_expr< T , U1 >& x,
                const ::__gmp_expr< T , U2 >& y ) const {
            CGAL_CHECK_GMP_EXPR;
            // cmp returns any int value, not just -1/0/1...
            return (Comparison_result) CGAL_NTS sign( ::cmp(x, y) );
        }
        CGAL_IMPLICIT_INTEROPERABLE_BINARY_OPERATOR_WITH_RT
        ( Type, Comparison_result)
    };

    struct To_double
        : public std::unary_function< mpq_class, double > {
        template < typename T , typename U >
        double operator()( const ::__gmp_expr< T , U >& x ) const {
            CGAL_CHECK_GMP_EXPR;
            return mpq_class(x).get_d();
        }
    };

    struct To_interval

        : public std::unary_function< mpq_class, std::pair< double, double > > {
        template < typename T, typename U >
        std::pair<double, double>
        operator()( const ::__gmp_expr< T , U >& x_ ) const {
            CGAL_CHECK_GMP_EXPR;
            mpq_class x = mpq_class(x_);
            mpfr_t y;
            mpfr_init2 (y, 53); /* Assume IEEE-754 */
            mpfr_set_q (y, x.get_mpq_t(), GMP_RNDD);
            double i = mpfr_get_d (y, GMP_RNDD); /* EXACT but can overflow */
            mpfr_set_q (y, x.get_mpq_t(), GMP_RNDU);
            double s = mpfr_get_d (y, GMP_RNDU); /* EXACT but can overflow */
            mpfr_clear (y);
            return std::pair<double, double>(i, s);
        }
    };
};

/*! \ingroup NiX_Fraction_traits_spec
 *  \brief Specialization of Fraction_traits for mpq_class
 */
template <>
class Fraction_traits< mpq_class > {
public:
    typedef mpq_class Type;

    typedef ::CGAL::Tag_true Is_fraction;
    typedef mpz_class Numerator_type;
    typedef mpz_class Denominator_type;

    typedef Algebraic_structure_traits< mpz_class >::Gcd Common_factor;

    class Decompose {
    public:
        typedef mpq_class first_argument_type;
        typedef mpz_class& second_argument_type;
        typedef mpz_class& third_argument_type;
        void operator () (
                const mpq_class& rat,
                mpz_class& num,
                mpz_class& den) {
            num = rat.get_num();
            den = rat.get_den();
        }
    };

    class Compose {
    public:
        typedef mpz_class first_argument_type;
        typedef mpz_class second_argument_type;
        typedef mpq_class result_type;
        mpq_class operator ()(
                const mpz_class& num ,
                const mpz_class& den ) {
            mpq_class result(num, den);
            result.canonicalize();
            return result;
        }
    };
};

CGAL_END_NAMESPACE

#undef CGAL_CHECK_GMP_EXPR

#endif // CGAL_MPQ_CLASS_H
