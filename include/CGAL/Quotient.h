// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
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
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.3
// release_date  : 2001, August 13
// 
// file          : include/CGAL/Quotient.h
// package       : Number_types (4.30)
// revision      : $Revision: 1.8 $
// revision_date : $Date: 2001/06/20 22:19:04 $
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
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_QUOTIENT_H
#define CGAL_QUOTIENT_H

#include <CGAL/basic.h>

#ifndef CGAL_CFG_NO_LOCALE
#  include <locale>
#else
#  include <cctype>
#endif

#include <CGAL/IO/io_tags.h>

CGAL_BEGIN_NAMESPACE

template <class NumberType> class Quotient;

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

  template <class T>
  Quotient(const T& n) : num(n), den( NT(1) ) {}

  Quotient(const NT& n, const NT& d) : num(n), den(d)
  { CGAL_kernel_precondition( d!= NT(0) ); }
  
  Quotient(const Quotient<NT>& r) : num(r.num), den(r.den) {}
  
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

template <class RT>
Interval_base
to_interval (const Quotient<RT>& z)
{
  return Interval_nt<>(CGAL::to_interval(z.numerator())) /
         Interval_nt<>(CGAL::to_interval(z.denominator()));
}

CGAL_END_NAMESPACE

#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#include <CGAL/Quotient.C>
#endif // CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION

#include <CGAL/iterator_traits_pointer_specs_for_cartesian_quotient.h>

#endif // CGAL_QUOTIENT_H
