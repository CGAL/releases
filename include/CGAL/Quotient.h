// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.1
// release_date  : 2000, January 11
// 
// source        : Quotient.fw
// file          : include/CGAL/Quotient.h
// package       : Number_types (2.7.1)
// revision      : 2.7.1
// revision_date : 04 Dec 1999 
//
// author(s)     :
//
// The template class Quotient<NumberType> is based on the LEDA class
// leda_rational written by Stefan Naeher and Christian Uhrig.
// It is basically a templated version with restricted functionality
// of the version of rational in LEDA release 3.3.
// The modification was done by Stefan.Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_QUOTIENT_H
#define CGAL_QUOTIENT_H

#ifndef CGAL_NO_STL_PROVIDED_REL_OPS
#  if ((__GNUC__ == 2) && (__GNUC_MINOR__ <= 8))
#    define CGAL_NO_STL_PROVIDED_REL_OPS
#  endif // g++ 2.8
#endif // CGAL_NO_STL_PROVIDED_REL_OPS



#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif // CGAL_BASIC_H
#ifndef CGAL_CFG_NO_LOCALE
#include <locale>
#else
#include <cctype>
#endif // CGAL_CFG_NO_LOCALE
#ifndef IO_IO_TAGS_H
#include <CGAL/IO/io_tags.h>
#endif // IO_IO_TAGS_H

CGAL_BEGIN_NAMESPACE

template <class NumberType> class Quotient;
CGAL_TEMPLATE_NULL  class Quotient<int>;

template <class NumberType>
double
to_double(const Quotient<NumberType>& q);

template <class NumberType>
CGAL_KERNEL_INLINE
bool
is_valid(const Quotient<NumberType>& q);

template <class NumberType>
CGAL_KERNEL_INLINE
bool
is_finite(const Quotient<NumberType>& q);

template <class NumberType>
CGAL_KERNEL_INLINE
NumberType
numerator(const Quotient<NumberType>& q);

template <class NumberType>
CGAL_KERNEL_INLINE
NumberType
denominator(const Quotient<NumberType>& q);

template <class NumberType>
inline
Quotient_tag
number_type_tag(const Quotient<NumberType>& q);

template < class NumberType >
inline
io_Operator
io_tag(const Quotient<NumberType>&);

template <class NumberType>
CGAL_KERNEL_MEDIUM_INLINE
Comparison_result
quotient_cmp(const Quotient<NumberType>& q, const Quotient<NumberType>& r);

template <class NumberType>
CGAL_KERNEL_INLINE
Quotient<NumberType>
operator+ (const Quotient<NumberType>& q, const Quotient<NumberType>& r);

template <class NumberType>
CGAL_KERNEL_INLINE
Quotient<NumberType>
operator+ (const NumberType& q, const Quotient<NumberType>& r);

template <class NumberType>
CGAL_KERNEL_INLINE
Quotient<NumberType>
operator+ (const Quotient<NumberType>& q, const NumberType& r);

template <class NumberType>
CGAL_KERNEL_INLINE
Quotient<NumberType>
operator- (const Quotient<NumberType>& q, const Quotient<NumberType>& r);

template <class NumberType>
CGAL_KERNEL_INLINE
Quotient<NumberType>
operator- (const NumberType& q, const Quotient<NumberType>& r);

template <class NumberType>
CGAL_KERNEL_INLINE
Quotient<NumberType>
operator- (const Quotient<NumberType>& q, const NumberType& r);

template <class NumberType>
CGAL_KERNEL_INLINE
Quotient<NumberType>
operator* (const Quotient<NumberType>& q, const Quotient<NumberType>& r);

template <class NumberType>
CGAL_KERNEL_INLINE
Quotient<NumberType>
operator* (const NumberType& q, const Quotient<NumberType>& r);

template <class NumberType>
CGAL_KERNEL_INLINE
Quotient<NumberType>
operator* (const Quotient<NumberType>& q, const NumberType& r);

template <class NumberType>
CGAL_KERNEL_INLINE
Quotient<NumberType>
operator/ (const Quotient<NumberType>& q, const Quotient<NumberType>& r);

template <class NumberType>
CGAL_KERNEL_INLINE
Quotient<NumberType>
operator/ (const NumberType& q, const Quotient<NumberType>& r);

template <class NumberType>
CGAL_KERNEL_INLINE
Quotient<NumberType>
operator/ (const Quotient<NumberType>& q, const NumberType& r);

template <class NumberType>
inline
Quotient<NumberType>
operator- (const Quotient<NumberType>&);

template <class NumberType>
CGAL_KERNEL_INLINE
bool
operator==(const Quotient<NumberType>& q, const Quotient<NumberType>& r);

template <class NumberType>
CGAL_KERNEL_INLINE
bool
operator==(const Quotient<NumberType>& q, const NumberType& a);

template <class NumberType>
CGAL_KERNEL_INLINE
bool
operator==(const NumberType& n, const Quotient<NumberType>& q);

template <class NumberType>
CGAL_KERNEL_INLINE
bool
operator< (const Quotient<NumberType>& q, const Quotient<NumberType>& r);

template <class NumberType>
CGAL_KERNEL_INLINE
bool
operator< (const Quotient<NumberType>& q, const NumberType& r);

template <class NumberType>
CGAL_KERNEL_INLINE
bool
operator< (const NumberType& q, const Quotient<NumberType>& r);

#ifndef CGAL_NO_STL_PROVIDED_REL_OPS
template <class NumberType>
CGAL_KERNEL_INLINE
bool
operator!=(const Quotient<NumberType>& q, const Quotient<NumberType>& r);

template <class NumberType>
CGAL_KERNEL_INLINE
bool
operator<=(const Quotient<NumberType>& q, const Quotient<NumberType>& r);

template <class NumberType>
CGAL_KERNEL_INLINE
bool
operator> (const Quotient<NumberType>& q, const Quotient<NumberType>& r);

template <class NumberType>
CGAL_KERNEL_INLINE
bool
operator>=(const Quotient<NumberType>& q, const Quotient<NumberType>& r);

template <class NumberType>
CGAL_KERNEL_INLINE
bool
operator!=(const Quotient<NumberType>& q, const NumberType& a);

template <class NumberType>
CGAL_KERNEL_INLINE
bool
operator!=(const NumberType& n, const Quotient<NumberType>& q);

template <class NumberType>
CGAL_KERNEL_INLINE
bool
operator<=(const Quotient<NumberType>& q, const NumberType& r);

template <class NumberType>
CGAL_KERNEL_INLINE
bool
operator<=(const NumberType& q, const Quotient<NumberType>& r);

template <class NumberType>
CGAL_KERNEL_INLINE
bool
operator> (const Quotient<NumberType>& q, const NumberType& r);

template <class NumberType>
CGAL_KERNEL_INLINE
bool
operator> (const NumberType& q, const Quotient<NumberType>& r);

template <class NumberType>
CGAL_KERNEL_INLINE
bool
operator>=(const Quotient<NumberType>& q, const NumberType& r);

template <class NumberType>
CGAL_KERNEL_INLINE
bool
operator>=(const NumberType& q, const Quotient<NumberType>& r);
#endif // CGAL_NO_STL_PROVIDED_REL_OPS

template <class NumberType>
std::istream&
operator>>(std::istream& in, Quotient<NumberType>& q);

template <class NumberType>
std::ostream&
operator<<(std::ostream& out, const Quotient<NumberType>& q);

template <class NumberType>
CGAL_KERNEL_INLINE
NumberType
quotient_truncation(const Quotient<NumberType>& r);

template <class NumberType>
NumberType
gcd(const NumberType& , const NumberType&);

template <class NumberType>
class Quotient
{
 public:
  typedef NumberType NT;
  
  Quotient() : num( NT(0) ), den( NT(1) ) {}
  
  Quotient(const NT& n) : num(n), den( NT(1) ) {}
  
  Quotient(int i) : num(NT(i)), den( NT(1) ) {}
  
  Quotient(const NT& n, const NT& d) : num(n), den(d)
  { CGAL_kernel_precondition( d!= NT(0) ); }
  
  Quotient(const Quotient<NT>& r) : num(r.num), den(r.den) {}
  
  ~Quotient() {}
  
  
  
  Quotient<NT>& operator+= (const Quotient<NT>& r);
  Quotient<NT>& operator-= (const Quotient<NT>& r);
  Quotient<NT>& operator*= (const Quotient<NT>& r);
  Quotient<NT>& operator/= (const Quotient<NT>& r);
  Quotient<NT>& operator+= (const NT& r);
  Quotient<NT>& operator-= (const NT& r);
  Quotient<NT>& operator*= (const NT& r);
  Quotient<NT>& operator/= (const NT& r);
  
  
  Quotient<NT>&    normalize();
  
  
  NT   numerator() const;
  NT   denominator() const;
  

 public:
  NT   num;
  NT   den;
  
};

CGAL_END_NAMESPACE


#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#include <CGAL/Quotient.C>
#endif // CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION

CGAL_BEGIN_NAMESPACE

CGAL_TEMPLATE_NULL
class Quotient<int>
{
 public:
  Quotient() : num( 0 ), den( 1 ) {}
  Quotient(int i) : num( i ), den( 1 ) {}
  Quotient(const int& n, const int& d) : num(n), den(d)
  { CGAL_kernel_precondition( d!= 0 ); }
  Quotient(const Quotient<int>& r) : num(r.num), den(r.den) {}
  ~Quotient() {}
  
  int
  numerator() const { return num; }
  
  int
  denominator() const { return den; }
  
  
  Quotient<int>&
  operator+= (const Quotient<int>& r)
  {
    num = num * r.den + r.num * den;
    den *= r.den;
    return (*this);
  }
  
  Quotient<int>&
  operator-= (const Quotient<int>& r)
  {
    num = num * r.den - r.num * den;
    den *= r.den;
    return (*this);
  }
  
  Quotient<int>&
  operator*= (const Quotient<int>& r)
  {
    num *= r.num;
    den *= r.den;
    return (*this);
  }
  
  Quotient<int>&
  operator/= (const Quotient<int>& r)
  {
    CGAL_kernel_precondition( r.num != 0 );
    num *= r.den;
    den *= r.num;
    return (*this);
  }
  Quotient<int>&
  operator+= (const int& r)
  {
    num = num + r * den;
    return (*this);
  }
  
  Quotient<int>&
  operator-= (const int& r)
  {
    num = num - r * den;
    return (*this);
  }
  
  Quotient<int>&
  operator*= (const int& r)
  {
    num *= r ;
    return (*this);
  }
  
  Quotient<int>&
  operator/= (const int& r)
  {
    CGAL_kernel_precondition( r != 0 );
    den *= r ;
    return (*this);
  }
  
 public:
  int num;
  int den;
  
};

CGAL_END_NAMESPACE


#ifdef CGAL_INTERVAL_ARITHMETIC_H
#include <CGAL/Interval_arithmetic/IA_Quotient.h>
#endif // CGAL_INTERVAL_ARITHMETIC_H

#include <CGAL/iterator_traits_pointer_specs_for_cartesian_quotient.h>

#endif // CGAL_QUOTIENT_H
