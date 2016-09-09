// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.0
// release_date  : 1999, June 03
// 
// source        : Quotient.fw
// file          : include/CGAL/Quotient.h
// package       : Number_types (2.1.5)
// revision      : 2.1.5
// revision_date : 09 May 1999 
//
// author(s)     :
//
// The template class Quotient<NT> is based on the LEDA class
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
#include <cctype>
#ifndef IO_IO_TAGS_H
#include <CGAL/IO/io_tags.h>
#endif // IO_IO_TAGS_H

CGAL_BEGIN_NAMESPACE

template <class NT> class Quotient;
CGAL_TEMPLATE_NULL class Quotient<int>;

template <class NT>
double
to_double(const Quotient<NT>& q);

template <class NT>
CGAL_KERNEL_INLINE
bool
is_valid(const Quotient<NT>& q);

template <class NT>
CGAL_KERNEL_INLINE
bool
is_finite(const Quotient<NT>& q);

template <class NT>
CGAL_KERNEL_INLINE
NT
numerator(const Quotient<NT>& q);

template <class NT>
CGAL_KERNEL_INLINE
NT
denominator(const Quotient<NT>& q);

template <class NT>
inline
Quotient_tag
number_type_tag(const Quotient<NT>& q);

template < class NT >
inline
io_Operator
io_tag(const Quotient<NT>&);

template <class NT>
CGAL_KERNEL_MEDIUM_INLINE
Comparison_result
quotient_cmp(const Quotient<NT>& q, const Quotient<NT>& r);

template <class NT>
CGAL_KERNEL_INLINE
Quotient<NT>
operator+ (const Quotient<NT>& q, const Quotient<NT>& r);

template <class NT>
CGAL_KERNEL_INLINE
Quotient<NT>
operator+ (const NT& q, const Quotient<NT>& r);

template <class NT>
CGAL_KERNEL_INLINE
Quotient<NT>
operator+ (const Quotient<NT>& q, const NT& r);

template <class NT>
CGAL_KERNEL_INLINE
Quotient<NT>
operator- (const Quotient<NT>& q, const Quotient<NT>& r);

template <class NT>
CGAL_KERNEL_INLINE
Quotient<NT>
operator- (const NT& q, const Quotient<NT>& r);

template <class NT>
CGAL_KERNEL_INLINE
Quotient<NT>
operator- (const Quotient<NT>& q, const NT& r);

template <class NT>
CGAL_KERNEL_INLINE
Quotient<NT>
operator* (const Quotient<NT>& q, const Quotient<NT>& r);

template <class NT>
CGAL_KERNEL_INLINE
Quotient<NT>
operator* (const NT& q, const Quotient<NT>& r);

template <class NT>
CGAL_KERNEL_INLINE
Quotient<NT>
operator* (const Quotient<NT>& q, const NT& r);

template <class NT>
CGAL_KERNEL_INLINE
Quotient<NT>
operator/ (const Quotient<NT>& q, const Quotient<NT>& r);

template <class NT>
CGAL_KERNEL_INLINE
Quotient<NT>
operator/ (const NT& q, const Quotient<NT>& r);

template <class NT>
CGAL_KERNEL_INLINE
Quotient<NT>
operator/ (const Quotient<NT>& q, const NT& r);

template <class NT>
inline
Quotient<NT>
operator- (const Quotient<NT>&);

template <class NT>
CGAL_KERNEL_INLINE
bool
operator==(const Quotient<NT>& q, const Quotient<NT>& r);

template <class NT>
CGAL_KERNEL_INLINE
bool
operator==(const Quotient<NT>& q, const NT& a);

template <class NT>
CGAL_KERNEL_INLINE
bool
operator==(const NT& n, const Quotient<NT>& q);

template <class NT>
CGAL_KERNEL_INLINE
bool
operator< (const Quotient<NT>& q, const Quotient<NT>& r);

template <class NT>
CGAL_KERNEL_INLINE
bool
operator< (const Quotient<NT>& q, const NT& r);

template <class NT>
CGAL_KERNEL_INLINE
bool
operator< (const NT& q, const Quotient<NT>& r);

#ifndef CGAL_NO_STL_PROVIDED_REL_OPS
template <class NT>
CGAL_KERNEL_INLINE
bool
operator!=(const Quotient<NT>& q, const Quotient<NT>& r);

template <class NT>
CGAL_KERNEL_INLINE
bool
operator<=(const Quotient<NT>& q, const Quotient<NT>& r);

template <class NT>
CGAL_KERNEL_INLINE
bool
operator> (const Quotient<NT>& q, const Quotient<NT>& r);

template <class NT>
CGAL_KERNEL_INLINE
bool
operator>=(const Quotient<NT>& q, const Quotient<NT>& r);
#endif // CGAL_NO_STL_PROVIDED_REL_OPS

#ifndef CGAL_NO_STL_PROVIDED_REL_OPS
template <class NT>
CGAL_KERNEL_INLINE
bool
operator!=(const Quotient<NT>& q, const NT& a);

template <class NT>
CGAL_KERNEL_INLINE
bool
operator!=(const NT& n, const Quotient<NT>& q);

template <class NT>
CGAL_KERNEL_INLINE
bool
operator<=(const Quotient<NT>& q, const NT& r);

template <class NT>
CGAL_KERNEL_INLINE
bool
operator<=(const NT& q, const Quotient<NT>& r);

template <class NT>
CGAL_KERNEL_INLINE
bool
operator> (const Quotient<NT>& q, const NT& r);

template <class NT>
CGAL_KERNEL_INLINE
bool
operator> (const NT& q, const Quotient<NT>& r);

template <class NT>
CGAL_KERNEL_INLINE
bool
operator>=(const Quotient<NT>& q, const NT& r);

template <class NT>
CGAL_KERNEL_INLINE
bool
operator>=(const NT& q, const Quotient<NT>& r);
#endif // CGAL_NO_STL_PROVIDED_REL_OPS

template <class NT>
std::istream&
operator>>(std::istream& in, Quotient<NT>& q);

template <class NT>
std::ostream&
operator<<(std::ostream& out, const Quotient<NT>& q);

template <class NT>
CGAL_KERNEL_INLINE
NT
quotient_truncation(const Quotient<NT>& r);

template <class NT>
NT
gcd(const NT& , const NT&);

template <class NT>
class Quotient
{
public:
  Quotient() : num( NT(0) ), den( NT(1) ) {}
  Quotient(const NT& n) : num(n), den( NT(1) ) {}
  Quotient(int i) : num(NT(i)), den( NT(1) ) {}
  Quotient(const NT& n, const NT& d) : num(n), den(d)
  { CGAL_kernel_precondition( d!= NT(0) ); }
  Quotient(const Quotient<NT>& r) : num(r.num), den(r.den) {}

  ~Quotient() {}

  friend CGAL_KERNEL_MEDIUM_INLINE
         Comparison_result
         quotient_cmp CGAL_NULL_TMPL_ARGS (const Quotient<NT>& q,
                                           const Quotient<NT>& r);
  friend double
         to_double CGAL_NULL_TMPL_ARGS (const Quotient<NT>& q);

  friend CGAL_KERNEL_INLINE
         bool
         is_valid CGAL_NULL_TMPL_ARGS (const Quotient<NT>& q);

  friend CGAL_KERNEL_INLINE
         bool
         is_finite CGAL_NULL_TMPL_ARGS (const Quotient<NT>& q);

  friend CGAL_KERNEL_INLINE
         NT
         numerator CGAL_NULL_TMPL_ARGS (const Quotient<NT>& q);

  friend CGAL_KERNEL_INLINE
         NT
         denominator CGAL_NULL_TMPL_ARGS (const Quotient<NT>& q);

  friend CGAL_KERNEL_INLINE
  NT
  quotient_truncation CGAL_NULL_TMPL_ARGS (const Quotient<NT>& r);


  NT            numerator() const;
  NT            denominator() const;


  Quotient<NT>& operator+= (const Quotient<NT>& r);
  Quotient<NT>& operator-= (const Quotient<NT>& r);
  Quotient<NT>& operator*= (const Quotient<NT>& r);
  Quotient<NT>& operator/= (const Quotient<NT>& r);
  Quotient<NT>& operator+= (const NT& r);
  Quotient<NT>& operator-= (const NT& r);
  Quotient<NT>& operator*= (const NT& r);
  Quotient<NT>& operator/= (const NT& r);


  friend CGAL_KERNEL_INLINE
         Quotient<NT>
         operator+ CGAL_NULL_TMPL_ARGS (const Quotient<NT>& q,
                                        const Quotient<NT>& r);
  friend CGAL_KERNEL_INLINE
         Quotient<NT>
         operator- CGAL_NULL_TMPL_ARGS (const Quotient<NT>& q,
                                        const Quotient<NT>& r);
  friend CGAL_KERNEL_INLINE
         Quotient<NT>
         operator* CGAL_NULL_TMPL_ARGS (const Quotient<NT>& q,
                                        const Quotient<NT>& r);
  friend CGAL_KERNEL_INLINE
         Quotient<NT>
         operator/ CGAL_NULL_TMPL_ARGS (const Quotient<NT>& q,
                                        const Quotient<NT>& r);
  friend inline
         Quotient<NT>
         operator- CGAL_NULL_TMPL_ARGS (const Quotient<NT>&);

  friend CGAL_KERNEL_INLINE
         Quotient<NT>
         operator+ CGAL_NULL_TMPL_ARGS (const NT& q,
                                        const Quotient<NT>& r);
  friend CGAL_KERNEL_INLINE
         Quotient<NT>
         operator+ CGAL_NULL_TMPL_ARGS (const Quotient<NT>& q,
                                        const NT& r);
  friend CGAL_KERNEL_INLINE
         Quotient<NT>
         operator- CGAL_NULL_TMPL_ARGS (const NT& q,
                                        const Quotient<NT>& r);
  friend CGAL_KERNEL_INLINE
         Quotient<NT>
         operator- CGAL_NULL_TMPL_ARGS (const Quotient<NT>& q,
                                        const NT& r);
  friend CGAL_KERNEL_INLINE
         Quotient<NT>
         operator* CGAL_NULL_TMPL_ARGS (const NT& q,
                                        const Quotient<NT>& r);
  friend CGAL_KERNEL_INLINE
         Quotient<NT>
         operator* CGAL_NULL_TMPL_ARGS (const Quotient<NT>& q,
                                        const NT& r);
  friend CGAL_KERNEL_INLINE
         Quotient<NT>
         operator/ CGAL_NULL_TMPL_ARGS (const NT& q,
                                        const Quotient<NT>& r);
  friend CGAL_KERNEL_INLINE
         Quotient<NT>
         operator/ CGAL_NULL_TMPL_ARGS (const Quotient<NT>& q,
                                        const NT& r);

  friend CGAL_KERNEL_INLINE
         bool
         operator== CGAL_NULL_TMPL_ARGS (const Quotient<NT>& q,
                                         const Quotient<NT>& r);
  friend CGAL_KERNEL_INLINE
         bool
         operator<  CGAL_NULL_TMPL_ARGS (const Quotient<NT>& q,
                                         const Quotient<NT>& r);
  friend CGAL_KERNEL_INLINE
         bool
         operator== CGAL_NULL_TMPL_ARGS (const Quotient<NT>& q,
                                         const NT& a);
  friend CGAL_KERNEL_INLINE
         bool
         operator== CGAL_NULL_TMPL_ARGS (const NT& n,
                                         const Quotient<NT>& q);
  friend CGAL_KERNEL_INLINE
         bool
         operator<  CGAL_NULL_TMPL_ARGS (const Quotient<NT>& q,
                                         const NT& r);
  friend CGAL_KERNEL_INLINE
         bool
         operator<  CGAL_NULL_TMPL_ARGS (const NT& q,
                                         const Quotient<NT>& r);
#ifndef CGAL_NO_STL_PROVIDED_REL_OPS
  friend CGAL_KERNEL_INLINE
         bool
         operator!= CGAL_NULL_TMPL_ARGS (const Quotient<NT>& q,
                                         const Quotient<NT>& r);
  friend CGAL_KERNEL_INLINE
         bool
         operator<= CGAL_NULL_TMPL_ARGS (const Quotient<NT>& q,
                                         const Quotient<NT>& r);
  friend CGAL_KERNEL_INLINE
         bool
         operator>  CGAL_NULL_TMPL_ARGS (const Quotient<NT>& q,
                                         const Quotient<NT>& r);
  friend CGAL_KERNEL_INLINE
         bool
         operator>= CGAL_NULL_TMPL_ARGS (const Quotient<NT>& q,
                                         const Quotient<NT>& r);
#endif // CGAL_NO_STL_PROVIDED_REL_OPS
#ifndef CGAL_NO_STL_PROVIDED_REL_OPS
  friend CGAL_KERNEL_INLINE
         bool
         operator!= CGAL_NULL_TMPL_ARGS (const Quotient<NT>& q,
                                         const NT& a);
  friend CGAL_KERNEL_INLINE
         bool
         operator!= CGAL_NULL_TMPL_ARGS (const NT& n,
                                         const Quotient<NT>& q);
  friend CGAL_KERNEL_INLINE
         bool
         operator<= CGAL_NULL_TMPL_ARGS (const Quotient<NT>& q,
                                         const NT& r);
  friend CGAL_KERNEL_INLINE
         bool
         operator<= CGAL_NULL_TMPL_ARGS (const NT& q,
                                         const Quotient<NT>& r);
  friend CGAL_KERNEL_INLINE
         bool
         operator>  CGAL_NULL_TMPL_ARGS (const Quotient<NT>& q,
                                         const NT& r);
  friend CGAL_KERNEL_INLINE
         bool
         operator>  CGAL_NULL_TMPL_ARGS (const NT& q,
                                         const Quotient<NT>& r);
  friend CGAL_KERNEL_INLINE
         bool
         operator>= CGAL_NULL_TMPL_ARGS (const Quotient<NT>& q,
                                         const NT& r);
  friend CGAL_KERNEL_INLINE
         bool
         operator>= CGAL_NULL_TMPL_ARGS (const NT& q,
                                         const Quotient<NT>& r);
#endif // CGAL_NO_STL_PROVIDED_REL_OPS
/*
  friend std::istream&
         operator>> CGAL_NULL_TMPL_ARGS (std::istream& in, Quotient<NT>& q);
*/

  Quotient<NT>&    normalize();

protected:
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

#ifndef CGAL_NO_QUOTIENT_INT_FRIENDS
friend double
       to_double CGAL_NULL_TMPL_ARGS (const Quotient<int>& q);
friend CGAL_KERNEL_INLINE
       bool
       is_valid CGAL_NULL_TMPL_ARGS (const Quotient<int>& q);
friend CGAL_KERNEL_INLINE
       bool
       is_finite CGAL_NULL_TMPL_ARGS (const Quotient<int>& q);
friend CGAL_KERNEL_INLINE
       int
       numerator CGAL_NULL_TMPL_ARGS (const Quotient<int>& q);
friend CGAL_KERNEL_INLINE
       int
       denominator CGAL_NULL_TMPL_ARGS (const Quotient<int>& q);

friend CGAL_KERNEL_INLINE
       int
       quotient_truncation CGAL_NULL_TMPL_ARGS
                                            (const Quotient<int>& r);

/*
friend
std::ostream&
operator<< CGAL_NULL_TMPL_ARGS (std::ostream& out, const Quotient<int>& q);

friend
std::istream&
operator>> CGAL_NULL_TMPL_ARGS (std::istream& in, Quotient<int>& q);
*/

#endif // CGAL_NO_QUOTIENT_INT_FRIENDS

  int                 numerator() const
                      { return num; }
  int                 denominator() const
                      { return den; }
  Quotient<int>& normalize()
                      {
                        if (num == den)
                        {
                            num = den = 1;
                            return (*this);
                        }
                        if (-num == den)
                        {
                            num = -1;
                            den =  1;
                            return (*this);
                        }
                        int ggt = gcd(num, den);
                        if (ggt != 1 )
                        {
                            num /= ggt;
                            den /= ggt;
                        }
                        return (*this);
                      }


  Quotient<int>& operator+= (const Quotient<int>& r)
                      {
                        num = num * r.den + r.num * den;
                        den *= r.den;
                        return (*this);
                      }
  Quotient<int>& operator-= (const Quotient<int>& r)
                      {
                        num = num * r.den - r.num * den;
                        den *= r.den;
                        return (*this);
                      }
  Quotient<int>& operator*= (const Quotient<int>& r)
                      {
                        num *= r.num;
                        den *= r.den;
                        return (*this);
                      }
  Quotient<int>& operator/= (const Quotient<int>& r)
                      {
                        CGAL_kernel_precondition( r.num != 0 );
                        num *= r.den;
                        den *= r.num;
                        return (*this);
                      }
  Quotient<int>& operator+= (const int& r)
                      {
                        num = num + r * den;
                        return (*this);
                      }
  Quotient<int>& operator-= (const int& r)
                      {
                        num = num - r * den;
                        return (*this);
                      }
  Quotient<int>& operator*= (const int& r)
                      {
                        num *= r ;
                        return (*this);
                      }
  Quotient<int>& operator/= (const int& r)
                      {
                        CGAL_kernel_precondition( r != 0 );
                        den *= r ;
                        return (*this);
                      }

#ifndef CGAL_NO_QUOTIENT_INT_FRIENDS
friend CGAL_KERNEL_INLINE
       Quotient<int>
       operator+ CGAL_NULL_TMPL_ARGS (const Quotient<int>& q,
                                      const Quotient<int>& r);
friend CGAL_KERNEL_INLINE
       Quotient<int>
       operator- CGAL_NULL_TMPL_ARGS (const Quotient<int>& q,
                                      const Quotient<int>& r);
friend CGAL_KERNEL_INLINE
       Quotient<int>
       operator* CGAL_NULL_TMPL_ARGS (const Quotient<int>& q,
                                      const Quotient<int>& r);
friend CGAL_KERNEL_INLINE
       Quotient<int>
       operator/ CGAL_NULL_TMPL_ARGS (const Quotient<int>& q,
                                      const Quotient<int>& r);
friend inline
       Quotient<int>
       operator- CGAL_NULL_TMPL_ARGS (const Quotient<int>&);
friend CGAL_KERNEL_INLINE
       Quotient<int>
       operator+ CGAL_NULL_TMPL_ARGS (const int& q,
                                      const Quotient<int>& r);
friend CGAL_KERNEL_INLINE
       Quotient<int>
       operator+ CGAL_NULL_TMPL_ARGS (const Quotient<int>& q,
                                      const int& r);
friend CGAL_KERNEL_INLINE
       Quotient<int>
       operator- CGAL_NULL_TMPL_ARGS (const int& q,
                                      const Quotient<int>& r);
friend CGAL_KERNEL_INLINE
       Quotient<int>
       operator- CGAL_NULL_TMPL_ARGS (const Quotient<int>& q,
                                      const int& r);
friend CGAL_KERNEL_INLINE
       Quotient<int>
       operator* CGAL_NULL_TMPL_ARGS (const int& q,
                                      const Quotient<int>& r);
friend CGAL_KERNEL_INLINE
       Quotient<int>
       operator* CGAL_NULL_TMPL_ARGS (const Quotient<int>& q,
                                      const int& r);
friend CGAL_KERNEL_INLINE
       Quotient<int>
       operator/ CGAL_NULL_TMPL_ARGS (const int& q,
                                      const Quotient<int>& r);
friend CGAL_KERNEL_INLINE
       Quotient<int>
       operator/ CGAL_NULL_TMPL_ARGS (const Quotient<int>& q,
                                      const int& r);
friend CGAL_KERNEL_MEDIUM_INLINE
       Comparison_result
       quotient_cmp CGAL_NULL_TMPL_ARGS (const Quotient<int>& q,
                                         const Quotient<int>& r);
friend CGAL_KERNEL_INLINE
       bool
       operator== CGAL_NULL_TMPL_ARGS (const Quotient<int>& q,
                                       const Quotient<int>& r);
friend CGAL_KERNEL_INLINE
       bool
       operator<  CGAL_NULL_TMPL_ARGS (const Quotient<int>& q,
                                       const Quotient<int>& r);
friend CGAL_KERNEL_INLINE
       bool
       operator== CGAL_NULL_TMPL_ARGS (const Quotient<int>& q,
                                       const int& a);
friend CGAL_KERNEL_INLINE
       bool
       operator== CGAL_NULL_TMPL_ARGS (const int& n,
                                       const Quotient<int>& q);
friend CGAL_KERNEL_INLINE
       bool
       operator<  CGAL_NULL_TMPL_ARGS (const Quotient<int>& q,
                                       const int& r);
friend CGAL_KERNEL_INLINE
       bool
       operator<  CGAL_NULL_TMPL_ARGS (const int& q,
                                       const Quotient<int>& r);
#ifndef CGAL_NO_STL_PROVIDED_REL_OPS
friend CGAL_KERNEL_INLINE
       bool
       operator!= CGAL_NULL_TMPL_ARGS (const Quotient<int>& q,
                                       const Quotient<int>& r);
friend CGAL_KERNEL_INLINE
       bool
       operator<= CGAL_NULL_TMPL_ARGS (const Quotient<int>& q,
                                       const Quotient<int>& r);
friend CGAL_KERNEL_INLINE
       bool
       operator>  CGAL_NULL_TMPL_ARGS (const Quotient<int>& q,
                                       const Quotient<int>& r);
friend CGAL_KERNEL_INLINE
       bool
       operator>= CGAL_NULL_TMPL_ARGS (const Quotient<int>& q,
                                       const Quotient<int>& r);
#endif // CGAL_NO_STL_PROVIDED_REL_OPS
#ifndef CGAL_NO_STL_PROVIDED_REL_OPS
friend CGAL_KERNEL_INLINE
       bool
       operator!= CGAL_NULL_TMPL_ARGS (const Quotient<int>& q,
                                       const int& a);
friend CGAL_KERNEL_INLINE
       bool
       operator!= CGAL_NULL_TMPL_ARGS (const int& n,
                                       const Quotient<int>& q);
friend CGAL_KERNEL_INLINE
       bool
       operator<= CGAL_NULL_TMPL_ARGS (const Quotient<int>& q,
                                       const int& r);
friend CGAL_KERNEL_INLINE
       bool
       operator<= CGAL_NULL_TMPL_ARGS (const int& q,
                                       const Quotient<int>& r);
friend CGAL_KERNEL_INLINE
       bool
       operator>  CGAL_NULL_TMPL_ARGS (const Quotient<int>& q,
                                       const int& r);
friend CGAL_KERNEL_INLINE
       bool
       operator>  CGAL_NULL_TMPL_ARGS (const int& q,
                                       const Quotient<int>& r);
friend CGAL_KERNEL_INLINE
       bool
       operator>= CGAL_NULL_TMPL_ARGS (const Quotient<int>& q,
                                       const int& r);
friend CGAL_KERNEL_INLINE
       bool
       operator>= CGAL_NULL_TMPL_ARGS (const int& q,
                                       const Quotient<int>& r);
#endif // CGAL_NO_STL_PROVIDED_REL_OPS

#endif // CGAL_NO_QUOTIENT_INT_FRIENDS
#ifndef CGAL_NO_QUOTIENT_INT_FRIENDS
protected:
#else
public:
#endif // CGAL_NO_QUOTIENT_INT_FRIENDS
  int num;
  int den;

};

CGAL_END_NAMESPACE


#ifdef CGAL_INTERVAL_ARITHMETIC_H
#include <CGAL/Interval_arithmetic/IA_Quotient.h>
#endif // CGAL_INTERVAL_ARITHMETIC_H

#endif // CGAL_QUOTIENT_H
