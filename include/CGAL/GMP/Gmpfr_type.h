// Copyright (c) 2007-2009 Inria Lorraine (France). All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.6-branch/Number_types/include/CGAL/GMP/Gmpfr_type.h $
// $Id: Gmpfr_type.h 53524 2009-12-22 15:20:05Z penarand $
// 
// Author: Luis Pe�aranda <luis.penaranda@loria.fr>

// TODO:
//      - add constructor from (integer,exponent)
//      - move version check to main cmake script (when moving to the trunk)

#ifndef CGAL_GMPFR_TYPE_H
#define CGAL_GMPFR_TYPE_H

//#if( ( ! defined(MPFR_VERSION) ) || ( MPFR_VERSION<MPFR_VERSION_NUM(2,2,0) ) )
//#error "Gmpfr requires MPFR 2.2.0 or newer"
//#else

#include <gmp.h>
#include <mpfr.h>
#include <boost/operators.hpp>
#include <CGAL/Handle_for.h>
#include <CGAL/GMP/Gmpz_type.h>
#include <CGAL/GMP/Gmpq_type.h>
#include <CGAL/GMP/Gmpzf_type.h>
#include <string>
#include <limits>
#include <CGAL/Uncertain.h>

namespace CGAL{

class Gmpfr;

bool operator<(const Gmpfr&,const Gmpfr&);
bool operator==(const Gmpfr&,const Gmpfr&);

bool operator<(const Gmpfr&,long);
bool operator>(const Gmpfr&,long);
bool operator==(const Gmpfr&,long);

bool operator<(const Gmpfr&,unsigned long);
bool operator>(const Gmpfr&,unsigned long);
bool operator==(const Gmpfr&,unsigned long);

bool operator<(const Gmpfr&,int);
bool operator>(const Gmpfr&,int);
bool operator==(const Gmpfr&,int);

bool operator<(const Gmpfr&,double);
bool operator>(const Gmpfr&,double);
bool operator==(const Gmpfr&,double);

bool operator<(const Gmpfr&,long double);
bool operator>(const Gmpfr&,long double);
bool operator==(const Gmpfr&,long double);

bool operator<(const Gmpfr&,const Gmpz&);
bool operator>(const Gmpfr&,const Gmpz&);
bool operator==(const Gmpfr&,const Gmpz&);

bool operator<(const Gmpfr&,const Gmpq&);
bool operator>(const Gmpfr&,const Gmpq&);
bool operator==(const Gmpfr&,const Gmpq&);

struct Gmpfr_rep{
        mpfr_t floating_point_number;
        bool clear_on_destruction;
        Gmpfr_rep():clear_on_destruction(true){}
        ~Gmpfr_rep(){
                if(clear_on_destruction)
                        mpfr_clear(floating_point_number);
        }
};

namespace internal{
        template <>
        struct Minmax_traits<mp_rnd_t>{
                static const mp_rnd_t min=GMP_RNDN;
                static const mp_rnd_t max=GMP_RND_MAX;
        };
} // namespace internal

class Gmpfr:
#ifdef CGAL_GMPFR_NO_REFCOUNT
        Gmpfr_rep,
#else
        Handle_for<Gmpfr_rep>,
#endif
        boost::ordered_euclidian_ring_operators1<Gmpfr,
        boost::ordered_euclidian_ring_operators2<Gmpfr,long,
        boost::ordered_euclidian_ring_operators2<Gmpfr,unsigned long,
        boost::ordered_euclidian_ring_operators2<Gmpfr,int,
        boost::totally_ordered2<Gmpfr,double,
        boost::totally_ordered2<Gmpfr,long double,
        boost::ordered_euclidian_ring_operators2<Gmpfr,Gmpz,
        boost::ordered_euclidian_ring_operators2<Gmpfr,Gmpq
        > > > > > > > >
{
        private:

        typedef Handle_for<Gmpfr_rep>   Base;

        static inline Uncertain<mp_rnd_t> _gmp_rnd(std::float_round_style r){
                switch(r){
                        case std::round_toward_infinity: return GMP_RNDU;
                        case std::round_toward_neg_infinity: return GMP_RNDD;
                        case std::round_toward_zero: return GMP_RNDZ;
                        case std::round_to_nearest: return GMP_RNDN;
                        default: return Uncertain<mp_rnd_t>::indeterminate();
                }
        };

        static inline std::float_round_style _cgal_rnd(mp_rnd_t r){
                switch(r){
                        case GMP_RNDU: return std::round_toward_infinity;
                        case GMP_RNDD: return std::round_toward_neg_infinity;
                        case GMP_RNDZ: return std::round_toward_zero;
                        case GMP_RNDN: return std::round_to_nearest;
                        default: return std::round_indeterminate;
                }
        };

        public:

        typedef mp_prec_t               Precision_type;

        // access

        inline
        mpfr_srcptr fr()const{
#ifdef CGAL_GMPFR_NO_REFCOUNT
                return floating_point_number;
#else
                return Ptr()->floating_point_number;
#endif
        }

        inline
        mpfr_ptr fr(){
#ifdef CGAL_GMPFR_NO_REFCOUNT
                return floating_point_number;
#else
                return ptr()->floating_point_number;
#endif
        }

        inline
        void dont_clear_on_destruction(){
#ifdef CGAL_GMPFR_NO_REFCOUNT
                clear_on_destruction=false;
#else
                ptr()->clear_on_destruction=false;
#endif
        }

        // construction

        Gmpfr(){
                mpfr_init(fr());
        }

        Gmpfr(mpfr_srcptr f){
                mpfr_custom_init_set(
                        fr(),
                        mpfr_custom_get_kind(f),
                        mpfr_custom_get_exp(f),
                        mpfr_get_prec(f),
                        mpfr_custom_get_mantissa(f));
                dont_clear_on_destruction();
                CGAL_assertion((mpfr_nan_p(f)!=0 && mpfr_nan_p(fr())!=0) ||
                               (mpfr_unordered_p(f,fr())==0 &&
                                mpfr_equal_p(f,fr())!=0));
        }

        Gmpfr(mpfr_srcptr f,
              std::float_round_style r,
              Gmpfr::Precision_type p=Gmpfr::get_default_precision()){
                mpfr_init2(fr(),p);
                mpfr_set(fr(),f,_gmp_rnd(r));
                CGAL_assertion(mpfr_get_prec(fr())<mpfr_get_prec(f) ||
                               mpfr_equal_p(fr(),f)!=0);
        }

        Gmpfr(mpfr_srcptr f,Gmpfr::Precision_type p){
                mpfr_init2(fr(),p);
                mpfr_set(fr(),f,mpfr_get_default_rounding_mode());
                CGAL_assertion(p<mpfr_get_prec(f) || mpfr_equal_p(fr(),f)!=0);
        }

        Gmpfr(Gmpzf f,
              std::float_round_style r=Gmpfr::get_default_rndmode(),
              Gmpfr::Precision_type p=Gmpfr::get_default_precision()){
                mpfr_init2(fr(),p);
                mpfr_set_z(fr(),f.man(),_gmp_rnd(r));
                mpfr_mul_2si(fr(),fr(),f.exp(),_gmp_rnd(r));
        }

        Gmpfr(Gmpzf f,Gmpfr::Precision_type p){
                mpfr_init2(fr(),p);
                mpfr_set_z(fr(),f.man(),mpfr_get_default_rounding_mode());
                mpfr_mul_2si(fr(),
                             fr(),
                             f.exp(),
                             mpfr_get_default_rounding_mode());
        }

#define _GMPFR_CONSTRUCTOR_FROM_TYPE(_type,_fun) \
        Gmpfr(_type x, \
              std::float_round_style r=Gmpfr::get_default_rndmode(), \
              Gmpfr::Precision_type p=Gmpfr::get_default_precision()){ \
                mpfr_init2(fr(),p); \
                _fun(fr(),x,_gmp_rnd(r)); \
        } \
        Gmpfr(_type x,Gmpfr::Precision_type p){ \
                mpfr_init2(fr(),p); \
                _fun(fr(),x,mpfr_get_default_rounding_mode()); \
        }

#define _GMPFR_CONSTRUCTOR_FROM_OBJECT(_class,_member,_fun) \
        Gmpfr(const _class &x, \
              std::float_round_style r=Gmpfr::get_default_rndmode(), \
              Gmpfr::Precision_type p=Gmpfr::get_default_precision()){ \
                mpfr_init2(fr(),p); \
                _fun(fr(),x._member,_gmp_rnd(r)); \
        } \
        Gmpfr(const _class &z,Gmpfr::Precision_type p){ \
                mpfr_init2(fr(),p); \
                _fun(fr(),z._member,mpfr_get_default_rounding_mode()); \
        }

        _GMPFR_CONSTRUCTOR_FROM_TYPE(int,mpfr_set_si);
        _GMPFR_CONSTRUCTOR_FROM_TYPE(long,mpfr_set_si);
        _GMPFR_CONSTRUCTOR_FROM_TYPE(unsigned,mpfr_set_ui);
        _GMPFR_CONSTRUCTOR_FROM_TYPE(unsigned long,mpfr_set_ui);
        _GMPFR_CONSTRUCTOR_FROM_TYPE(double,mpfr_set_d);
        _GMPFR_CONSTRUCTOR_FROM_TYPE(long double,mpfr_set_ld);
        _GMPFR_CONSTRUCTOR_FROM_OBJECT(Gmpz,mpz(),mpfr_set_z);
        _GMPFR_CONSTRUCTOR_FROM_OBJECT(Gmpq,mpq(),mpfr_set_q);

#undef _GMPFR_CONSTRUCTOR_FROM_TYPE
#undef _GMPFR_CONSTRUCTOR_FROM_OBJECT

        // When Gmpfr is refence counted, we inherit the assignment
        // operator and the copy constructor from Handle_for.
#ifdef CGAL_GMPFR_NO_REFCOUNT
        Gmpfr& operator=(const Gmpfr &a){
                if(get_precision()!=a.get_precision())
                        set_precision(a.get_precision());
                mpfr_set(fr(),a.fr(),mpfr_get_default_rounding_mode());
                return *this;
        }

        Gmpfr(const Gmpfr &a){
                mpfr_init2(fr(),a.get_precision());
                mpfr_set(fr(),a.fr(),GMP_RNDN);
        }
#endif

        Gmpfr(
              const Gmpfr &a,
              std::float_round_style r,
              Gmpfr::Precision_type p=Gmpfr::get_default_precision()){
#ifndef CGAL_GMPFR_NO_REFCOUNT
                if(p==a.get_precision()){
                        Gmpfr temp(a);
                        dont_clear_on_destruction();
                        swap(temp);
                }else
#endif
                {
                        mpfr_init2(fr(),p);
                        mpfr_set(fr(),a.fr(),_gmp_rnd(r));
                }
        }

        Gmpfr(const Gmpfr &a,Gmpfr::Precision_type p){
#ifndef CGAL_GMPFR_NO_REFCOUNT
                if(p==a.get_precision()){
                        Gmpfr temp(a);
                        dont_clear_on_destruction();
                        swap(temp);
                }else
#endif
                {
                        mpfr_init2(fr(),p);
                        mpfr_set(fr(),a.fr(),mpfr_get_default_rounding_mode());
                }
        }

        // default rounding mode

        static std::float_round_style get_default_rndmode();
        static std::float_round_style set_default_rndmode(std::float_round_style);

        // default precision

        static Gmpfr::Precision_type get_default_precision();
        static Gmpfr::Precision_type
                set_default_precision(Gmpfr::Precision_type);

        // precision of a single Gmpfr object

        Gmpfr::Precision_type get_precision()const;
        Gmpfr round(Gmpfr::Precision_type,std::float_round_style)const;

        // mpfr global inexact flags

        static void clear_flags();
        static bool underflow_flag();
        static bool overflow_flag();
        static bool nan_flag();
        static bool inex_flag();
        static bool erange_flag();

        // arithmetics

        Gmpfr operator+()const;
        Gmpfr operator-()const;

#define _GMPFR_DECLARE_OPERATORS(_type) \
        Gmpfr& operator+=(_type); \
        Gmpfr& operator-=(_type); \
        Gmpfr& operator*=(_type); \
        Gmpfr& operator/=(_type);

        _GMPFR_DECLARE_OPERATORS(const Gmpfr&)
        Gmpfr& operator%=(const Gmpfr&);
        _GMPFR_DECLARE_OPERATORS(long)
        _GMPFR_DECLARE_OPERATORS(unsigned long)
        _GMPFR_DECLARE_OPERATORS(int)
        _GMPFR_DECLARE_OPERATORS(const Gmpz&)
        _GMPFR_DECLARE_OPERATORS(const Gmpq&)

#undef _GMPFR_DECLARE_OPERATORS

#define _GMPFR_DECLARE_STATIC_FUNCTION(_f,_t1,_t2) \
        static Gmpfr _f (_t1,_t2,std::float_round_style=Gmpfr::get_default_rndmode()); \
        static Gmpfr _f (_t1, \
                         _t2, \
                         Gmpfr::Precision_type, \
                         std::float_round_style=Gmpfr::get_default_rndmode());

#define _GMPFR_DECLARE_STATIC_FUNCTIONS(_t2) \
        _GMPFR_DECLARE_STATIC_FUNCTION(add,const Gmpfr&,_t2) \
        _GMPFR_DECLARE_STATIC_FUNCTION(sub,const Gmpfr&,_t2) \
        _GMPFR_DECLARE_STATIC_FUNCTION(mul,const Gmpfr&,_t2) \
        _GMPFR_DECLARE_STATIC_FUNCTION(div,const Gmpfr&,_t2)

        _GMPFR_DECLARE_STATIC_FUNCTIONS(const Gmpfr&)
        _GMPFR_DECLARE_STATIC_FUNCTIONS(long)
        _GMPFR_DECLARE_STATIC_FUNCTIONS(unsigned long)
        _GMPFR_DECLARE_STATIC_FUNCTIONS(int)
        _GMPFR_DECLARE_STATIC_FUNCTIONS(const Gmpz&)
        _GMPFR_DECLARE_STATIC_FUNCTIONS(const Gmpq&)

#undef _GMPFR_DECLARE_STATIC_FUNCTION
#undef _GMPFR_DECLARE_STATIC_FUNCTIONS

#define _GMPFR_DECLARE_NO_ARGUMENT_FUNCTION(_f) \
        Gmpfr _f (std::float_round_style=Gmpfr::get_default_rndmode()) const; \
        Gmpfr _f (Gmpfr::Precision_type,\
                  std::float_round_style=Gmpfr::get_default_rndmode()) const;

        _GMPFR_DECLARE_NO_ARGUMENT_FUNCTION(abs)
        _GMPFR_DECLARE_NO_ARGUMENT_FUNCTION(sqrt)
        _GMPFR_DECLARE_NO_ARGUMENT_FUNCTION(cbrt)
        Gmpfr kthroot
                (int,std::float_round_style=Gmpfr::get_default_rndmode()) const;
        Gmpfr kthroot
                (int,
                 Gmpfr::Precision_type,
                 std::float_round_style=Gmpfr::get_default_rndmode()) const;
        _GMPFR_DECLARE_NO_ARGUMENT_FUNCTION(square)

#undef _GMPFR_DECLARE_NO_ARGUMENT_FUNCTION

        // comparison and query functions

        bool is_zero()const;
        bool is_one()const;
        bool is_nan()const;
        bool is_inf()const;
        bool is_number()const;
        Sign sign()const;
        bool is_square()const;
        bool is_square(Gmpfr&)const;
        Comparison_result compare(const Gmpfr&)const;

        // conversion functions

        double to_double(std::float_round_style=Gmpfr::get_default_rndmode())const;
        std::pair<double,double> to_interval()const;
        std::pair<double,long>
                to_double_exp(std::float_round_style=Gmpfr::get_default_rndmode())const;
        std::pair<std::pair<double,double>,long> to_interval_exp()const;
        std::pair<Gmpz,long> to_integer_exp()const;
        Gmpq to_fraction()const;
};




// --------------
// implementation
// --------------

// default rounding mode, handled by mpfr
inline
std::float_round_style Gmpfr::get_default_rndmode(){
        return _cgal_rnd(mpfr_get_default_rounding_mode());
}

inline
std::float_round_style Gmpfr::set_default_rndmode(std::float_round_style rnd_mode){
        std::float_round_style old_rnd_mode=Gmpfr::get_default_rndmode();
        mpfr_set_default_rounding_mode(_gmp_rnd(rnd_mode));
        return old_rnd_mode;
}

// default precision, handled by mpfr
inline
Gmpfr::Precision_type Gmpfr::get_default_precision(){
        return mpfr_get_default_prec();
}

inline
Gmpfr::Precision_type Gmpfr::set_default_precision(Gmpfr::Precision_type prec){
        Gmpfr::Precision_type old_prec=Gmpfr::get_default_precision();
        CGAL_assertion(prec>=MPFR_PREC_MIN&&prec<=MPFR_PREC_MAX);
        mpfr_set_default_prec(prec);
        return old_prec;
}

// precision of a single Gmpfr object

inline
Gmpfr::Precision_type Gmpfr::get_precision()const{
        return mpfr_get_prec(fr());
}

inline
Gmpfr Gmpfr::round(Gmpfr::Precision_type p,std::float_round_style r)const{
        return Gmpfr(*this,r,p);
}

// mpfr global inexact flags

inline
void Gmpfr::clear_flags(){
        mpfr_clear_flags();
}

inline
bool Gmpfr::underflow_flag(){
        return mpfr_underflow_p()!=0;
}

inline
bool Gmpfr::overflow_flag(){
        return mpfr_overflow_p()!=0;
}

inline
bool Gmpfr::nan_flag(){
        return mpfr_nanflag_p()!=0;
}

inline
bool Gmpfr::inex_flag(){
        return mpfr_inexflag_p()!=0;
}

inline
bool Gmpfr::erange_flag(){
        return mpfr_erangeflag_p()!=0;
}

// arithmetics

inline
Gmpfr Gmpfr::operator+()const{
        return(*this);
}

inline
Gmpfr Gmpfr::operator-()const{
        Gmpfr result(0,get_precision());
        mpfr_neg(result.fr(),fr(),GMP_RNDN);
        return result;
}

// _GMPFR_MEMBER_PREC returns the precision to be used to operate between
// *this and a number of another type or class. Currently, the maximum of
// *this' precision and the default precision is returned.
#define _GMPFR_MEMBER_PREC() \
        (get_precision()>Gmpfr::get_default_precision()? \
         get_precision(): \
         Gmpfr::get_default_precision())

// _GMPFR_MEMBER_PREC_2 returns the precision for the operation between Gmpfr
// objects *this and _b. Currently, it is the maximum of the precisions of
// *this and _b and the default precision.
// TODO: maybe we can rewrite this define optimally, maybe with an inline
#define _GMPFR_MEMBER_PREC_2(_b) \
        ( get_precision() >= mpfr_get_prec(_b.fr()) ? \
                ( get_precision()>(Gmpfr::get_default_precision())? \
                        get_precision():(Gmpfr::get_default_precision())): \
                ( mpfr_get_prec(_b.fr())>(Gmpfr::get_default_precision())? \
                        mpfr_get_prec(_b.fr()): \
                        (Gmpfr::get_default_precision())) \
        )

// _GMPFR_OBJECT_BINARY_OPERATOR defines an overloaded binary operator of
// the Gmpfr class, where the second parameter of the operator is an
// object. It behaves differently when the Gmpfr class is reference-counted
// or not.
#ifdef CGAL_GMPFR_NO_REFCOUNT
#define _GMPFR_OBJECT_BINARY_OPERATOR(_op,_class,_member,_fun) \
        inline \
        Gmpfr& Gmpfr::_op(const _class &b){ \
                if(get_precision()>=Gmpfr::get_default_precision()) { \
                        _fun(fr(), \
                             fr(), \
                             b._member, \
                             mpfr_get_default_rounding_mode()); \
                }else{ \
                        Gmpfr _temp(0,Gmpfr::get_default_precision()); \
                        _fun(_temp.fr(), \
                             fr(), \
                             b._member, \
                             mpfr_get_default_rounding_mode()); \
                        mpfr_swap(_temp.fr(),fr()); \
                } \
                return *this; \
        }
#else
#define _GMPFR_OBJECT_BINARY_OPERATOR(_op,_class,_member,_fun) \
        inline \
        Gmpfr& Gmpfr::_op(const _class &b){ \
                if(unique()){ \
                        if(get_precision()>Gmpfr::get_default_precision()) { \
                                _fun(fr(), \
                                     fr(), \
                                     b._member, \
                                     mpfr_get_default_rounding_mode()); \
                        }else{ \
                                Gmpfr _temp(0,Gmpfr::get_default_precision()); \
                                _fun(_temp.fr(), \
                                     fr(), \
                                     b._member, \
                                     mpfr_get_default_rounding_mode()); \
                                swap(_temp); \
                        } \
                }else{ \
                        Gmpfr result(0,_GMPFR_MEMBER_PREC()); \
                        _fun(result.fr(), \
                             fr(), \
                             b._member, \
                             mpfr_get_default_rounding_mode()); \
                        swap(result); \
                } \
                return *this; \
        }
#endif

// _GMPFR_GMPFR_BINARY_OPERATOR is analogous to
// _GMPFR_OBJECT_BINARY_OPERATOR, and it is used when the second operand is
// another Gmpfr. The difference is the computation of the operation
// precision.
#ifdef CGAL_GMPFR_NO_REFCOUNT
#define _GMPFR_GMPFR_BINARY_OPERATOR(_op,_fun) \
        inline \
        Gmpfr& Gmpfr::_op(const Gmpfr &b){ \
                Gmpfr::Precision_type _p=_GMPFR_MEMBER_PREC_2(b); \
                if(_p==get_precision()) { \
                        _fun(fr(), \
                             fr(), \
                             b.fr(), \
                             mpfr_get_default_rounding_mode()); \
                }else{ \
                        Gmpfr _temp(0,_p); \
                        _fun(_temp.fr(), \
                             fr(), \
                             b.fr(), \
                             mpfr_get_default_rounding_mode()); \
                        mpfr_swap(_temp.fr(),fr()); \
                } \
                return *this; \
        }
#else
#define _GMPFR_GMPFR_BINARY_OPERATOR(_op,_fun) \
        inline \
        Gmpfr& Gmpfr::_op(const Gmpfr &b){ \
                Gmpfr::Precision_type _p=_GMPFR_MEMBER_PREC_2(b); \
                if(unique()&&(_p==get_precision())){ \
                        _fun(fr(), \
                             fr(), \
                             b.fr(), \
                             mpfr_get_default_rounding_mode()); \
                }else{ \
                        Gmpfr result(0,_p); \
                        _fun(result.fr(), \
                             fr(), \
                             b.fr(), \
                             mpfr_get_default_rounding_mode()); \
                        swap(result); \
                } \
                return *this; \
        }
#endif

// _GMPFR_TYPE_BINARY_OPERATOR is analogous to the
// _GMPFR_OBJECT_BINARY_OPERATOR, where the second parameter is a type
// instead of an object.
#ifdef CGAL_GMPFR_NO_REFCOUNT
#define _GMPFR_TYPE_BINARY_OPERATOR(_op,_type,_fun) \
        inline \
        Gmpfr& Gmpfr::_op(_type x){ \
                if(get_precision()>=Gmpfr::get_default_precision()) { \
                        _fun(fr(),fr(),x,mpfr_get_default_rounding_mode()); \
                }else{ \
                        Gmpfr _temp(0,Gmpfr::get_default_precision()); \
                        _fun(_temp.fr(), \
                             fr(), \
                             x, \
                             mpfr_get_default_rounding_mode()); \
                        mpfr_swap(_temp.fr(),fr()); \
                } \
                return *this; \
        }
#else
#define _GMPFR_TYPE_BINARY_OPERATOR(_op,_type,_fun) \
        inline \
        Gmpfr& Gmpfr::_op(_type x){ \
                if(unique()){ \
                        if(get_precision()>Gmpfr::get_default_precision()) { \
                                _fun(fr(), \
                                     fr(), \
                                     x, \
                                     mpfr_get_default_rounding_mode()); \
                        }else{ \
                                Gmpfr _temp(0,Gmpfr::get_default_precision()); \
                                _fun(_temp.fr(), \
                                     fr(), \
                                     x, \
                                     mpfr_get_default_rounding_mode()); \
                                swap(_temp); \
                        } \
                }else{ \
                        Gmpfr result(0,_GMPFR_MEMBER_PREC()); \
                        _fun(result.fr(), \
                             fr(), \
                             x, \
                             mpfr_get_default_rounding_mode()); \
                        swap(result); \
                } \
                return *this; \
        }
#endif

_GMPFR_GMPFR_BINARY_OPERATOR(operator+=,mpfr_add)
_GMPFR_GMPFR_BINARY_OPERATOR(operator-=,mpfr_sub)
_GMPFR_GMPFR_BINARY_OPERATOR(operator*=,mpfr_mul)
_GMPFR_GMPFR_BINARY_OPERATOR(operator/=,mpfr_div)
#if(defined(MPFR_VERSION)&&(MPFR_VERSION>=MPFR_VERSION_NUM(2,3,0)))
_GMPFR_GMPFR_BINARY_OPERATOR(operator%=,mpfr_remainder)
#else
//#  warning "Gmpfr::operator%= is optimized in MPFR 2.3.0."
inline
Gmpfr& Gmpfr::operator%=(const Gmpfr &b){
        Gmpfr::Precision_type _p=_GMPFR_MEMBER_PREC_2(b);
        Gmpfr result(*this,_p);
        result/=b;
        mpfr_trunc(result.fr(),result.fr());
        result*=b;
        result-=*this;
        mpfr_neg(result.fr(),result.fr(),GMP_RNDN);
#  ifdef CGAL_GMPFR_NO_REFCOUNT
        mpfr_swap(result.fr(),fr());
#  else
        if(unique())
                mpfr_swap(result.fr(),fr());
        else
                swap(result);
#  endif
        return *this;
}
#endif

_GMPFR_TYPE_BINARY_OPERATOR(operator+=,long,mpfr_add_si)
_GMPFR_TYPE_BINARY_OPERATOR(operator-=,long,mpfr_sub_si)
_GMPFR_TYPE_BINARY_OPERATOR(operator*=,long,mpfr_mul_si)
_GMPFR_TYPE_BINARY_OPERATOR(operator/=,long,mpfr_div_si)

_GMPFR_TYPE_BINARY_OPERATOR(operator+=,unsigned long,mpfr_add_ui)
_GMPFR_TYPE_BINARY_OPERATOR(operator-=,unsigned long,mpfr_sub_ui)
_GMPFR_TYPE_BINARY_OPERATOR(operator*=,unsigned long,mpfr_mul_ui)
_GMPFR_TYPE_BINARY_OPERATOR(operator/=,unsigned long,mpfr_div_ui)

_GMPFR_TYPE_BINARY_OPERATOR(operator+=,int,mpfr_add_si)
_GMPFR_TYPE_BINARY_OPERATOR(operator-=,int,mpfr_sub_si)
_GMPFR_TYPE_BINARY_OPERATOR(operator*=,int,mpfr_mul_si)
_GMPFR_TYPE_BINARY_OPERATOR(operator/=,int,mpfr_div_si)

_GMPFR_OBJECT_BINARY_OPERATOR(operator+=,Gmpz,mpz(),mpfr_add_z)
_GMPFR_OBJECT_BINARY_OPERATOR(operator-=,Gmpz,mpz(),mpfr_sub_z)
_GMPFR_OBJECT_BINARY_OPERATOR(operator*=,Gmpz,mpz(),mpfr_mul_z)
_GMPFR_OBJECT_BINARY_OPERATOR(operator/=,Gmpz,mpz(),mpfr_div_z)

_GMPFR_OBJECT_BINARY_OPERATOR(operator+=,Gmpq,mpq(),mpfr_add_q)
_GMPFR_OBJECT_BINARY_OPERATOR(operator-=,Gmpq,mpq(),mpfr_sub_q)
_GMPFR_OBJECT_BINARY_OPERATOR(operator*=,Gmpq,mpq(),mpfr_mul_q)
_GMPFR_OBJECT_BINARY_OPERATOR(operator/=,Gmpq,mpq(),mpfr_div_q)

#undef _GMPFR_OBJECT_BINARY_OPERATOR
#undef _GMPFR_GMPFR_BINARY_OPERATOR
#undef _GMPFR_TYPE_BINARY_OPERATOR

// the static arithmetic functions are defined in a separate file
#include <CGAL/GMP/Gmpfr_type_static.h>

#define _GMPFR_ARITHMETIC_FUNCTION(_name,_fun) \
        Gmpfr Gmpfr::_name (std::float_round_style r)const{ \
                Gmpfr result(0,_GMPFR_MEMBER_PREC()); \
                _fun(result.fr(),fr(),_gmp_rnd(r)); \
                return result; \
        } \
        Gmpfr Gmpfr::_name (Gmpfr::Precision_type p, \
                            std::float_round_style r)const{ \
                CGAL_assertion(p>=MPFR_PREC_MIN&&p<=MPFR_PREC_MAX); \
                Gmpfr result(0,p); \
                _fun(result.fr(),fr(),_gmp_rnd(r)); \
                return result; \
        }

_GMPFR_ARITHMETIC_FUNCTION(abs,mpfr_abs)
_GMPFR_ARITHMETIC_FUNCTION(sqrt,mpfr_sqrt)
_GMPFR_ARITHMETIC_FUNCTION(cbrt,mpfr_cbrt)

Gmpfr Gmpfr::kthroot(int k,std::float_round_style r)const{
        Gmpfr result(0,_GMPFR_MEMBER_PREC());
        mpfr_root(result.fr(),fr(),k,_gmp_rnd(r));
        return result;
}

Gmpfr Gmpfr::kthroot(int k,
                     Gmpfr::Precision_type p,
                     std::float_round_style r)const{
        CGAL_assertion(p>=MPFR_PREC_MIN&&p<=MPFR_PREC_MAX);
        Gmpfr result(0,p);
        mpfr_root(result.fr(),fr(),k,_gmp_rnd(r));
        return result;
}

_GMPFR_ARITHMETIC_FUNCTION(square,mpfr_sqr)

#undef _GMPFR_ARITHMETIC_FUNCTION
#undef _GMPFR_MEMBER_PREC
#undef _GMPFR_MEMBER_PREC_2

// comparison and query functions

inline
bool Gmpfr::is_zero()const{
        return mpfr_zero_p(fr())!=0;
}

inline
bool Gmpfr::is_one()const{
        return mpfr_cmp_ui(fr(),1)==0;
}

inline
bool Gmpfr::is_nan()const{
        return mpfr_nan_p(fr())!=0;
}

inline
bool Gmpfr::is_inf()const{
        return mpfr_inf_p(fr())!=0;
}

inline
bool Gmpfr::is_number()const{
        return mpfr_number_p(fr())!=0;
}

inline
Sign Gmpfr::sign()const{
        int s=mpfr_sgn(fr());
        return(s==0?ZERO:(s>0?POSITIVE:NEGATIVE));
}

inline
bool Gmpfr::is_square()const{
        Sign s=sign();
        if(s==NEGATIVE)
                return false;
        if(s==ZERO)
                return true;
        std::pair<Gmpz,long> r=Gmpfr::to_integer_exp();
        if(r.second%2)
                r.first=r.first*2;
        return mpz_perfect_square_p(r.first.mpz())!=0;
}

inline
bool Gmpfr::is_square(Gmpfr &y)const{
        bool ret=is_square();
        if(ret)
                y=sqrt();
        return ret;
}

inline
Comparison_result Gmpfr::compare(const Gmpfr& b)const{
        int c=mpfr_cmp(fr(),b.fr());
        return(c?(c>0?LARGER:SMALLER):EQUAL);
}

// conversion functions

inline
double Gmpfr::to_double(std::float_round_style r)const{
        return mpfr_get_d(fr(),_gmp_rnd(r));
}

inline
std::pair<double,double>Gmpfr::to_interval()const{
        return std::make_pair(
                        mpfr_get_d(fr(),GMP_RNDD),
                        mpfr_get_d(fr(),GMP_RNDU));
}

inline
std::pair<double,long> Gmpfr::to_double_exp(std::float_round_style r)const{
        long e;
        double d=mpfr_get_d_2exp(&e,fr(),_gmp_rnd(r));
        return std::make_pair(d,e);
}

inline
std::pair<std::pair<double,double>,long> Gmpfr::to_interval_exp()const{
        long e1,e2;
        double d_low=mpfr_get_d_2exp(&e1,fr(),GMP_RNDD);
        double d_upp=mpfr_get_d_2exp(&e2,fr(),GMP_RNDU);
        CGAL_assertion(e1==e2);
        return std::make_pair(std::make_pair(d_low,d_upp),e1);
}

inline
std::pair<Gmpz,long> Gmpfr::to_integer_exp()const{
        if(is_zero())
                return std::make_pair(Gmpz(0),0);
        Gmpz z;
        long e=mpfr_get_z_exp(z.mpz(),fr());
        CGAL_assertion_msg(mpfr_get_emin()<=e && mpfr_get_emax()>=e,
                           "exponent out of range");
        if(mpz_sgn(z.mpz())!=0&&mpz_tstbit(z.mpz(),0)==0){
                unsigned long firstone=mpz_scan1(z.mpz(),0);
                CGAL_assertion(mpz_divisible_2exp_p(z.mpz(),firstone)!=0);
                Gmpz d(1);
                mpz_mul_2exp(d.mpz(),d.mpz(),firstone);
                CGAL_assertion(mpz_divisible_p(z.mpz(),d.mpz())!=0);
                mpz_divexact(z.mpz(),z.mpz(),d.mpz());
                e+=firstone;
                CGAL_assertion(mpfr_get_emax()>=e);
        }
        CGAL_assertion_code(Gmpfr::Precision_type p=mpz_sizeinbase(z.mpz(),2);)
        CGAL_assertion_code(if(MPFR_PREC_MIN>p) p=MPFR_PREC_MIN;)
        CGAL_assertion_code(Gmpfr test(z,p);)
        CGAL_assertion_code(mpfr_mul_2si(test.fr(),test.fr(),e,GMP_RNDN);)
        CGAL_assertion_msg(mpfr_equal_p(test.fr(),fr())!=0,"conversion error");
        return std::make_pair(z,e);
}

inline
Gmpq Gmpfr::to_fraction()const{
        std::pair<Gmpz,long> p=this->to_integer_exp();
        Gmpq q(p.first);
        CGAL_assertion(mpz_cmp(p.first.mpz(),mpq_numref(q.mpq()))==0);
        CGAL_assertion(mpz_cmp_ui(mpq_denref(q.mpq()),(unsigned long)1)==0);
        if(p.second<0){
                mpz_mul_2exp(mpq_denref(q.mpq()),
                             mpq_denref(q.mpq()),
                             (unsigned long)(-p.second));
        }else{
                mpz_mul_2exp(mpq_numref(q.mpq()),
                             mpq_numref(q.mpq()),
                             (unsigned long)(p.second));
        }
        mpq_canonicalize(q.mpq());
        CGAL_assertion_msg(mpz_sizeinbase(mpq_denref(q.mpq()),2)==
                           mpz_scan1(mpq_denref(q.mpq()),0)+1,
                           "denominator is not a power of 2");
        CGAL_assertion_msg(mpfr_cmp_q(fr(),q.mpq())==0,"conversion error");
        return q;
}


// input/output

// This function was based on the Gmpq's one. It reads a number in the form
// MeE, where M and E are integers. The read number is M.2^E. The number
// may contain spaces between integers and the 'e', but not in the middle
// of the numbers.
inline
std::istream& operator>>(std::istream& is,Gmpfr &f){
        std::istream::int_type c;
        std::ios::fmtflags old_flags = is.flags();

        is.unsetf(std::ios::skipws);
        gmpz_eat_white_space(is);

        // 1. read the mantissa, it starts in +, - or a digit and ends in e
        Gmpz mant(0);           // the mantissa of the number
        Gmpz exp(0);            // the exponent of the number
        bool neg_mant=false;    // true iff the mantissa is negative
        bool neg_exp=false;     // true iff the exponent is negative
        c=is.peek();
        switch(c){
                case '-':
                        neg_mant=true;
                        is.get();
                        gmpz_eat_white_space(is);
                        break;
                case '+':
                        is.get();
                        gmpz_eat_white_space(is);
                        break;
                case 'n':       // this is NaN
                        is.get();
                        if(is.get()=='a'&&is.get()=='n'){
                                f=Gmpfr();
                                return is;
                        }
                        else
                                goto invalid_number;
                default:
                        if(c!='i'&&(c<'0'||c>'9')){     // invalid number
                                invalid_number:
                                is.setstate(std::ios_base::failbit);
                                is.flags(old_flags);
                                return is;
                        }
        }

        // at this point, we have the sign of the number and we are ready
        // to read the mantissa
        c=is.get();
        if(c=='i'){     // infinity comes
                if(is.get()=='n'&&is.get()=='f'){
                        f=Gmpfr();
                        mpfr_set_inf(f.fr(),neg_mant?-1:1);
                        return is;
                }
                else
                        goto invalid_number;
        }

        while(c>='0'&&c<='9'){
                mant=10*mant+(c-'0');
                c=is.get();
        }
        is.putback(c);
        gmpz_eat_white_space(is);

        switch(c=is.get()){
                case 'e':
                        break;
                default:
                        is.setstate(std::ios_base::failbit);
                        is.flags(old_flags);
                        return is;
        }
        c=is.peek();
        switch(c){
                case '-':
                        neg_exp=true;
                        is.get();
                        gmpz_eat_white_space(is);
                        break;
                case '+':
                        is.get();
                        gmpz_eat_white_space(is);
                        break;
                default:
                        if(c<'0'||c>'9')
                                goto invalid_number;
        }
        gmpz_eat_white_space(is);
        while((c=is.get())>='0'&&c<='9')
                exp=10*exp+(c-'0');
        is.putback(c);
        if(mpz_sizeinbase(exp.mpz(),2)>8*sizeof(mp_exp_t))
                mpfr_set_erangeflag();

        // we have now both exponent and mantissa
        f=Gmpfr(mant,
                mpz_sizeinbase(mant.mpz(),2)>MPFR_PREC_MIN?
                mpz_sizeinbase(mant.mpz(),2):
                MPFR_PREC_MIN);
        mpfr_mul_2si(f.fr(),
                     f.fr(),
                     (neg_exp?-1:1)*mpz_get_ui(exp.mpz()),
                     GMP_RNDN);

        // this expensive assertion checks that we didn't lose bits when
        // multiplying or dividing by 2^exp
        CGAL_expensive_assertion_code( \
                Gmpfr g(mpz_sizeinbase(mant.mpz(),2)); \
                mpfr_div_2si( \
                        g.fr(), \
                        f.fr, \
                        neg_exp?-mpz_get_ui(exp.mpz()):mpz_get_ui(exp.mpz()),
                        GMP_RNDN);)
        CGAL_expensive_assertion(g==mant);

        return is;
}

inline
std::ostream& operator<<(std::ostream& os,const Gmpfr &a){
        if(a.is_nan())
                return os<<"nan";
        if(a.is_inf())
                return os<<(a<0?"-inf":"+inf");
        std::pair<Gmpz,long> ie=a.to_integer_exp();
        os<<ie.first<<'e'<<ie.second;
        return os;
}

// comparisons

inline
bool operator<(const Gmpfr &a,const Gmpfr &b){
        return mpfr_less_p(a.fr(),b.fr())!=0;
}

inline
bool operator==(const Gmpfr &a,const Gmpfr &b){
        return mpfr_equal_p(a.fr(),b.fr())!=0;
}

inline
bool operator<(const Gmpfr &a,long b){
        return(mpfr_cmp_si(a.fr(),b)<0);
}

inline
bool operator>(const Gmpfr &a,long b){
        return(mpfr_cmp_si(a.fr(),b)>0);
}

inline
bool operator==(const Gmpfr &a,long b){
        return !mpfr_cmp_si(a.fr(),b);
}

inline
bool operator<(const Gmpfr &a,unsigned long b){
        return(mpfr_cmp_ui(a.fr(),b)<0);
}

inline
bool operator>(const Gmpfr &a,unsigned long b){
        return(mpfr_cmp_ui(a.fr(),b)>0);
}

inline
bool operator==(const Gmpfr &a,unsigned long b){
        return !mpfr_cmp_ui(a.fr(),b);
}

inline
bool operator<(const Gmpfr &a,int b){
        return(mpfr_cmp_si(a.fr(),b)<0);
}

inline
bool operator>(const Gmpfr &a,int b){
        return(mpfr_cmp_si(a.fr(),b)>0);
}

inline
bool operator==(const Gmpfr &a,int b){
        return !mpfr_cmp_si(a.fr(),b);
}

inline
bool operator<(const Gmpfr &a,double b){
        return(mpfr_cmp_d(a.fr(),b)<0);
}

inline
bool operator>(const Gmpfr &a,double b){
        return(mpfr_cmp_d(a.fr(),b)>0);
}

inline
bool operator==(const Gmpfr &a,double b){
        return !mpfr_cmp_d(a.fr(),b);
}

inline
bool operator<(const Gmpfr &a,long double b){
        return(mpfr_cmp_ld(a.fr(),b)<0);
}

inline
bool operator>(const Gmpfr &a,long double b){
        return(mpfr_cmp_ld(a.fr(),b)>0);
}

inline
bool operator==(const Gmpfr &a,long double b){
        return !mpfr_cmp_ld(a.fr(),b);
}

inline
bool operator<(const Gmpfr &a,const Gmpz &b){
        return(mpfr_cmp_z(a.fr(),b.mpz())<0);
}

inline
bool operator>(const Gmpfr &a,const Gmpz &b){
        return(mpfr_cmp_z(a.fr(),b.mpz())>0);
}

inline
bool operator==(const Gmpfr &a,const Gmpz &b){
        return !mpfr_cmp_z(a.fr(),b.mpz());
}

inline
bool operator<(const Gmpfr &a,const Gmpq &b){
        return(mpfr_cmp_q(a.fr(),b.mpq())<0);
}

inline
bool operator>(const Gmpfr &a,const Gmpq &b){
        return(mpfr_cmp_q(a.fr(),b.mpq())>0);
}

inline
bool operator==(const Gmpfr &a,const Gmpq &b){
        return !mpfr_cmp_q(a.fr(),b.mpq());
}

inline
Gmpfr min BOOST_PREVENT_MACRO_SUBSTITUTION(const Gmpfr& x,const Gmpfr& y){
        return (x<=y)?x:y;
}

inline
Gmpfr max BOOST_PREVENT_MACRO_SUBSTITUTION(const Gmpfr& x,const Gmpfr& y){
        return (x>=y)?x:y;
}

} // namespace CGAL 

//#endif  // version check
#endif  // CGAL_GMPFR_TYPE_H

// vim: tabstop=8: softtabstop=8: smarttab: shiftwidth=8: expandtab
