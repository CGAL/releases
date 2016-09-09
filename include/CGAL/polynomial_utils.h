// Copyright (c) 2008 Max-Planck-Institute Saarbruecken (Germany).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.4-branch/Polynomial/include/CGAL/polynomial_utils.h $
// $Id: polynomial_utils.h 47306 2008-12-09 12:47:45Z hemmer $
// 
//
// Author(s)     : Michael Hemmer <hemmer@mpi-inf.mpg.de> 
//              
// ============================================================================

#include <CGAL/basic.h>
#include <CGAL/Polynomial_traits_d.h>

#ifndef CGAL_POLYNOMIAL_UTILS_H
#define CGAL_POLYNOMIAL_UTILS_H

#define CGAL_UNARY_POLY_FUNCTION(functor,function)                      \
  template <typename Polynomial_d>  inline                              \
  typename Polynomial_traits_d<Polynomial_d>::functor::result_type      \
  function(const Polynomial_d& p){                                      \
    typedef Polynomial_traits_d<Polynomial_d> PT;                       \
    return typename PT::functor()(p);                                   \
  }   

#define CGAL_UNARY_POLY_FUNCTION_INDEX(functor,function)                \
  CGAL_UNARY_POLY_FUNCTION(functor,function);                           \
  template <typename Polynomial_d>  inline                              \
  typename Polynomial_traits_d<Polynomial_d>::functor::result_type      \
  function(const Polynomial_d& p, int index ){                          \
    typedef Polynomial_traits_d<Polynomial_d> PT;                       \
    typename PT::functor fo;                                            \
    return fo(p,index);                                                 \
  }      

#define CGAL_BINARY_POLY_FUNCTION(functor,function)                     \
  template <typename Polynomial_d>  inline                              \
  typename Polynomial_traits_d<Polynomial_d>::functor::result_type      \
  function(const Polynomial_d& p,                                       \
      const typename Polynomial_traits_d<Polynomial_d>::                \
      functor::second_argument_type& second                             \
  ){                                                                    \
    typedef Polynomial_traits_d<Polynomial_d> PT;                       \
    return typename PT::functor()(p,second);                            \
  }  

#define CGAL_BINARY_POLY_FUNCTION_INDEX(functor,function)               \
  CGAL_BINARY_POLY_FUNCTION(functor,function)                           \
  template <typename Polynomial_d>  inline                              \
  typename Polynomial_traits_d<Polynomial_d>::functor::result_type      \
  function(const Polynomial_d& p,                                       \
      const typename Polynomial_traits_d<Polynomial_d>::                \
      functor::second_argument_type& second,                            \
      int index                                                         \
  ){                                                                    \
    typedef Polynomial_traits_d<Polynomial_d> PT;                       \
    return typename PT::functor()(p,second,index);                      \
  }  

CGAL_BEGIN_NAMESPACE

// GetCoefficient
// GetInnermostCoefficient
// ConstructCoefficientConstIteratorRange
// ConstructInnermostCoefficientConstIteratorRange
// Swap
// Move

// Degree
CGAL_UNARY_POLY_FUNCTION_INDEX(Degree,degree);
// TotalDegree
CGAL_UNARY_POLY_FUNCTION(Total_degree,total_degree);
// DegreeVector
CGAL_UNARY_POLY_FUNCTION(Degree_vector,degree_vector);
// LeadingCoefficient
CGAL_UNARY_POLY_FUNCTION(Leading_coefficient,leading_coefficient);
// InnermostLeadingCoefficient
CGAL_UNARY_POLY_FUNCTION(
    Innermost_leading_coefficient,
    innermost_leading_coefficient);

// Canonicalize
CGAL_UNARY_POLY_FUNCTION(Canonicalize, canonicalize);
// Differentiate
CGAL_UNARY_POLY_FUNCTION_INDEX(Differentiate, differentiate);

// Evaluate
CGAL_BINARY_POLY_FUNCTION(Evaluate,evaluate);
// EvaluateHomogeneous
template <typename Polynomial_d>  inline                                 
typename Polynomial_traits_d<Polynomial_d>::Evaluate_homogeneous::result_type
evaluate_homogeneous(const Polynomial_d& p,
    const typename Polynomial_traits_d<Polynomial_d>::Coefficient_type& num, 
    const typename Polynomial_traits_d<Polynomial_d>::Coefficient_type& den){
  typedef Polynomial_traits_d<Polynomial_d> PT;                       
  return typename PT::Evaluate_homogeneous()(p,num,den);                      
}  

// Substitute
template <typename Polynomial_d, typename Input_iterator>  inline     
typename CGAL::Coercion_traits<
    typename Polynomial_traits_d<Polynomial_d>::Innermost_coefficient_type,
    typename std::iterator_traits<Input_iterator>::value_type>              
  ::Type  
substitute(const Polynomial_d& p,Input_iterator begin, Input_iterator end){
  typedef Polynomial_traits_d<Polynomial_d> PT;                       
  return typename PT::Substitute()(p,begin, end);                      
}  
// IsZeroAt
template <typename Polynomial_d, typename Input_iterator>  inline     
typename Polynomial_traits_d<Polynomial_d>::Is_zero_at::result_type
is_zero_at(const Polynomial_d& p, Input_iterator begin, Input_iterator end){
  typedef Polynomial_traits_d<Polynomial_d> PT;                       
  return typename PT::Is_zero_at()(p,begin, end);                      
}  
// SignAt
template <typename Polynomial_d, typename Input_iterator>  inline     
typename Polynomial_traits_d<Polynomial_d>::Sign_at::result_type
sign_at(const Polynomial_d& p, Input_iterator begin, Input_iterator end){
  typedef Polynomial_traits_d<Polynomial_d> PT;                       
  return typename PT::Sign_at()(p,begin, end);                      
}  

// SubstituteHomogeneous
template <typename Polynomial_d, typename Input_iterator>  inline     
typename CGAL::Coercion_traits<
    typename Polynomial_traits_d<Polynomial_d>::Innermost_coefficient_type,
    typename std::iterator_traits<Input_iterator>::value_type>              
  ::Type  
substitute_homogeneous(
    const Polynomial_d& p,Input_iterator begin, Input_iterator end){
  typedef Polynomial_traits_d<Polynomial_d> PT;                       
  return typename PT::Substitute_homogeneous()(p,begin, end);
}  
// IsZeroAtHomogeneous
template <typename Polynomial_d, typename Input_iterator>  inline     
typename Polynomial_traits_d<Polynomial_d>::Is_zero_at_homogeneous::result_type
is_zero_at_homogeneous(
    const Polynomial_d& p, Input_iterator begin, Input_iterator end){
  typedef Polynomial_traits_d<Polynomial_d> PT;                       
  return typename PT::Is_zero_at_homogeneous()(p,begin, end);
}  
// SignAtHomogeneous
template <typename Polynomial_d, typename Input_iterator>  inline     
typename Polynomial_traits_d<Polynomial_d>::Sign_at_homogeneous::result_type
sign_at_homogeneous(
    const Polynomial_d& p, Input_iterator begin, Input_iterator end){
  typedef Polynomial_traits_d<Polynomial_d> PT;                       
  return typename PT::Sign_at_homogeneous()(p,begin, end);                      
}  

// Compare // provided by number_type utils 
// CGAL_BINARY_POLY_FUNCTION(Compare,compare);

// UnivariateContent
CGAL_UNARY_POLY_FUNCTION(Univariate_content, univariate_content);
// MultivariateContent
CGAL_UNARY_POLY_FUNCTION(Multivariate_content, multivariate_content);

// SquareFreeFactorize
template <typename Polynomial_d, typename OutputIterator>  inline     
OutputIterator
square_free_factorize(const Polynomial_d& p, OutputIterator oi){
  typedef Polynomial_traits_d<Polynomial_d> PT;                       
  return typename PT::Square_free_factorize()(p,oi);                      
}  
// MakeSquareFree
CGAL_UNARY_POLY_FUNCTION(Make_square_free, make_square_free);

// PseudoDivision
// PseudoDivisionQuotient
// PseudoDivisionRemainder
template <typename Polynomial_d>  inline     
void 
pseudo_division(
    const Polynomial_d& f, const Polynomial_d& g, 
    Polynomial_d& q, Polynomial_d& r, 
    typename Polynomial_traits_d<Polynomial_d>::Coefficient_type& D){
  typedef Polynomial_traits_d<Polynomial_d> PT;                       
  typename PT::Pseudo_division()(f,g,q,r,D);                      
  return;
}  
template <typename Polynomial_d>  inline     
typename Polynomial_traits_d<Polynomial_d>::Pseudo_division_quotient::result_type
pseudo_division_quotient(const Polynomial_d& f, const Polynomial_d& g){
  typedef Polynomial_traits_d<Polynomial_d> PT;                       
  return typename PT::Pseudo_division_quotient()(f,g);                      
}  
template <typename Polynomial_d>  inline     
typename Polynomial_traits_d<Polynomial_d>::Pseudo_division_remainder::result_type
pseudo_division_remainder(const Polynomial_d& f, const Polynomial_d& g){
  typedef Polynomial_traits_d<Polynomial_d> PT;                       
  return typename PT::Pseudo_division_remainder()(f,g);                      
}  

// GcdUpToConstantFactor
CGAL_BINARY_POLY_FUNCTION(
    Gcd_up_to_constant_factor, 
    gcd_up_to_constant_factor);
// IntegralDivisionUpToConstantFactor
CGAL_BINARY_POLY_FUNCTION(
    Integral_division_up_to_constant_factor, 
    integral_division_up_to_constant_factor);
// UnivariateContentUpToConstantFactor
CGAL_UNARY_POLY_FUNCTION(
    Univariate_content_up_to_constant_factor, 
    univariate_content_up_to_constant_factor);
// SquareFreeFactorizeUpToConstantFactor
template <typename Polynomial_d, typename OutputIterator>  inline     
OutputIterator
square_free_factorize_up_to_constant_factor(
    const Polynomial_d& p, OutputIterator oi){
  typedef Polynomial_traits_d<Polynomial_d> PT;                       
  return typename PT::Square_free_factorize_up_to_constant_factor()(p,oi);
}  

// Shift
CGAL_BINARY_POLY_FUNCTION_INDEX(Shift,shift);
// Negate
CGAL_UNARY_POLY_FUNCTION_INDEX(Negate,negate);
// Invert
CGAL_UNARY_POLY_FUNCTION_INDEX(Invert,invert);
// Translate
CGAL_BINARY_POLY_FUNCTION_INDEX(Translate,translate);
// TranslateHomogeneous
template <typename Polynomial_d>  inline     
typename Polynomial_traits_d<Polynomial_d>::Translate_homogeneous::result_type
translate_homogeneous(const Polynomial_d& f,
    const typename Polynomial_traits_d<Polynomial_d>::Innermost_coefficient_type& num, 
    const typename Polynomial_traits_d<Polynomial_d>::Innermost_coefficient_type& den){
      
  typedef Polynomial_traits_d<Polynomial_d> PT;                       
  return typename PT::Translate_homogeneous()(f,num,den);                      
}  
template <typename Polynomial_d>  inline     
typename Polynomial_traits_d<Polynomial_d>::Translate_homogeneous::result_type
translate_homogeneous(const Polynomial_d& f,
    const typename Polynomial_traits_d<Polynomial_d>::Innermost_coefficient_type& num, 
    const typename Polynomial_traits_d<Polynomial_d>::Innermost_coefficient_type& den,
    int index ){
  typedef Polynomial_traits_d<Polynomial_d> PT;                       
  return typename PT::Translate_homogeneous()(f,num,den,index);
}      
// Scale
CGAL_BINARY_POLY_FUNCTION_INDEX(Scale,scale);
// ScaleHomogeneous
template <typename Polynomial_d>  inline     
typename Polynomial_traits_d<Polynomial_d>::Scale_homogeneous::result_type
scale_homogeneous(const Polynomial_d& f,
    const typename Polynomial_traits_d<Polynomial_d>::Innermost_coefficient_type& num, 
    const typename Polynomial_traits_d<Polynomial_d>::Innermost_coefficient_type& den){
      
  typedef Polynomial_traits_d<Polynomial_d> PT;                       
  return typename PT::Scale_homogeneous()(f,num,den);                      
}  
template <typename Polynomial_d>  inline     
typename Polynomial_traits_d<Polynomial_d>::Scale_homogeneous::result_type
scale_homogeneous(const Polynomial_d& f,
    const typename Polynomial_traits_d<Polynomial_d>::Innermost_coefficient_type& num, 
    const typename Polynomial_traits_d<Polynomial_d>::Innermost_coefficient_type& den,
    int index ){
  typedef Polynomial_traits_d<Polynomial_d> PT;                       
  return typename PT::Scale_homogeneous()(f,num,den,index);
}  
// Resultant
CGAL_BINARY_POLY_FUNCTION(Resultant,resultant);

// TODO: REMOVE function below 

// sign() forwarded to the sign() member function
//template <typename NT> inline 
//CGAL::Sign sign(const Polynomial<NT>& p) { return p.sign(); }

// the non-member variants of diff() etc.
template <typename NT> inline
Polynomial<NT> diff(const Polynomial<NT>& p)
{ Polynomial<NT> q(p); q.diff(); return q; }

template<typename NT> inline
Polynomial<NT> scale_up(const Polynomial<NT>& p, const NT& a)
{ Polynomial<NT> q(p); q.scale_up(a); return q; }

template<typename NT> inline
Polynomial<NT> scale_down(const Polynomial<NT>& p, const NT& b)
{ Polynomial<NT> q(p); q.scale_down(b); return q; }

template<typename NT> inline
Polynomial<NT> scale(const Polynomial<NT>& p, const NT& a, const NT& b)
{ Polynomial<NT> q(p); q.scale(a, b); return q; }

template<typename NT> inline
Polynomial<NT> translate_by_one(const Polynomial<NT>& p)
{ Polynomial<NT> q(p); q.translate_by_one(); return q; }

template<typename NT> inline
Polynomial<NT> translate(const Polynomial<NT>& p, const NT& c)
{ Polynomial<NT> q(p); q.translate(c); return q; }

template<typename NT> inline
Polynomial<NT> translate(const Polynomial<NT>& p, const NT& a, const NT& b)
{ Polynomial<NT> q(p); q.translate(a, b); return q; }

template<typename NT> inline
Polynomial<NT> reversal(const Polynomial<NT>& p)
{ Polynomial<NT> q(p); q.reversal(); return q; }


// CGALi::is_square_free (undocumented)
namespace CGALi {
template< class Polynomial > 
bool is_square_free( const Polynomial& p ) {
  return typename CGAL::Polynomial_traits_d< Polynomial>::
    Is_square_free()( p );
}

} // namespace CGALi


CGAL_END_NAMESPACE

#undef CGAL_UNARY_POLY_FUNCTION
#undef CGAL_UNARY_POLY_FUNCTION_INDEX
#undef CGAL_BINARY_POLY_FUNCTION
#undef CGAL_BINARY_POLY_FUNCTION_INDEX

#endif // CGAL_POLYNOMIAL_UTILS_H
