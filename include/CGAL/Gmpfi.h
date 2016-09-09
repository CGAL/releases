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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.6-branch/Number_types/include/CGAL/Gmpfi.h $
// $Id: Gmpfi.h 53708 2010-01-20 16:38:53Z lrineau $
// 
// Author: Luis Pe�aranda <luis.penaranda@loria.fr>

#ifndef CGAL_GMPFI_H
#define CGAL_GMPFI_H

#include <CGAL/number_type_basic.h>
#include <CGAL/mpfi_coercion_traits.h>

namespace CGAL{

template <>
struct Algebraic_structure_traits<Gmpfi>:
public Algebraic_structure_traits_base<Gmpfi,Field_with_kth_root_tag>{

        typedef Tag_false       Is_exact;
        typedef Tag_true        Is_numerical_sensitive;
        typedef Uncertain<bool> Boolean;

        struct Is_zero:
        public std::unary_function<Type,Boolean>{
                Boolean operator()(const Type &x)const{
                        return x.is_zero();
                }
        };

        struct Is_one:
        public std::unary_function<Type,Boolean>{
                Boolean operator()(const Type &x)const{
                        return x.is_one();
                }
        };

        struct Square:
        public std::unary_function<Type,Type>{
                Type operator()(const Type &x)const{
                        return x.square();
                };
        };

        struct Is_square:
        public std::binary_function<Type,Type&,Boolean>{
                Boolean operator()(const Type &x)const{
                        return x.is_square();
                };
                Boolean operator()(const Type &x,Type &y)const{
                        return x.is_square(y);
                };
        };

        struct Sqrt:
        public std::unary_function<Type,Type>{
                Type operator()(const Type &x)const{
                        return x.sqrt();
                };
        };

        struct Kth_Root:
        public std::binary_function<int,Type,Type>{
                Type operator()(int k,const Type &x)const{
                        return (k==3?x.cbrt():x.kthroot(k));
                };
        };

        struct Divides:
        public std::binary_function<Type,Type,Boolean>{
                Boolean operator()(const Type &d,const Type &n)const{
                        return !(d.is_zero());
                };
                Boolean operator()(const Type &d,const Type &n,Type &c)const{
                        return d.divides(n,c);
                };
        };
};

template <>
class Real_embeddable_traits<Gmpfi>:
public INTERN_RET::Real_embeddable_traits_base<Gmpfi,CGAL::Tag_true>{

        typedef Algebraic_structure_traits<Type>        AST;

        public:

        typedef Tag_true                        Is_real_embeddable;
        typedef Uncertain<bool>                 Boolean;
        typedef Uncertain<Comparison_result>    Comparison_result;
        typedef Uncertain<CGAL::Sign>           Sign;
 
        typedef AST::Is_zero    Is_zero;

        struct Is_finite:
        public std::unary_function<Type,Boolean>{
                inline Boolean operator()(const Type &x)const{
                        return(x.is_number());
                };
        };

        struct Abs:
        public std::unary_function<Type,Type>{
                inline Type operator()(const Type &x)const{
                        return x.abs();
                };
        };

        struct Sgn:
        public std::unary_function<Type,Sign>{
                inline Sign operator()(const Type &x)const{
                        return x.sign();
                };
        };

        struct Is_positive:
        public std::unary_function<Type,Boolean>{
                inline Boolean operator()(const Type &x)const{
                        return x.is_positive();
                };
        };

        struct Is_negative:
        public std::unary_function<Type,Boolean>{
                inline Boolean operator()(const Type &x)const{
                        return x.is_negative();
                };
        };

        struct Compare:
        public std::binary_function<Type,Type,Comparison_result>{
                inline Comparison_result operator()
                        (const Type &x,const Type &y)const{
                                return x.compare(y);
                        };
        };

        struct To_double:
        public std::unary_function<Type,double>{
                inline double operator()(const Type &x)const{
                        return x.to_double();
                };
        };

        struct To_interval:
        public std::unary_function<Type,std::pair<double,double> >{
                inline std::pair<double,double> operator()(const Type &x)const{
                                return x.to_interval();
                        };
                };
};

}

#include <CGAL/GMP/Gmpfi_type.h>

#endif  // CGAL_GMPFI_H

// vim: tabstop=8: softtabstop=8: smarttab: shiftwidth=8: expandtab
