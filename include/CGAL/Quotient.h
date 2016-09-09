// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/Quotient.h
// author(s)     :
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


#ifndef CGAL_QUOTIENT_H
#define CGAL_QUOTIENT_H

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif // CGAL_BASIC_H
#ifndef CGAL_PROTECT_CTYPE_H
#include <ctype.h>
#define CGAL_PROTECT_CTYPE_H
#endif // CGAL_PROTECT_CTYPE_H
#ifndef CGAL_IO_IO_TAGS_H
#include <CGAL/IO/io_tags.h>
#endif // CGAL_IO_IO_TAGS_H

template <class NT> class CGAL_Quotient;
CGAL_TEMPLATE_NULL class CGAL_Quotient<int>;

template <class NT>
double
CGAL_to_double(const CGAL_Quotient<NT>& q);

template <class NT>
CGAL_KERNEL_INLINE
bool
CGAL_is_valid(const CGAL_Quotient<NT>& q);

template <class NT>
CGAL_KERNEL_INLINE
bool
CGAL_is_finite(const CGAL_Quotient<NT>& q);

template <class NT>
CGAL_KERNEL_INLINE
NT
CGAL_numerator(const CGAL_Quotient<NT>& q);

template <class NT>
CGAL_KERNEL_INLINE
NT
CGAL_denominator(const CGAL_Quotient<NT>& q);

template <class NT>
inline
CGAL_Quotient_tag
CGAL_number_type_tag(const CGAL_Quotient<NT>& q);

template < class NT >
inline
CGAL_io_Operator
CGAL_io_tag(const CGAL_Quotient<NT>&);

template <class NT>
CGAL_KERNEL_INLINE
CGAL_Comparison_result
quotient_cmp(const CGAL_Quotient<NT>& q, const CGAL_Quotient<NT>& r);

template <class NT>
CGAL_KERNEL_INLINE
CGAL_Quotient<NT>
operator+ (const CGAL_Quotient<NT>& q, const CGAL_Quotient<NT>& r);

template <class NT>
CGAL_KERNEL_INLINE
CGAL_Quotient<NT>
operator+ (const NT& q, const CGAL_Quotient<NT>& r);

template <class NT>
CGAL_KERNEL_INLINE
CGAL_Quotient<NT>
operator+ (const CGAL_Quotient<NT>& q, const NT& r);

template <class NT>
CGAL_KERNEL_INLINE
CGAL_Quotient<NT>
operator- (const CGAL_Quotient<NT>& q, const CGAL_Quotient<NT>& r);

template <class NT>
CGAL_KERNEL_INLINE
CGAL_Quotient<NT>
operator- (const NT& q, const CGAL_Quotient<NT>& r);

template <class NT>
CGAL_KERNEL_INLINE
CGAL_Quotient<NT>
operator- (const CGAL_Quotient<NT>& q, const NT& r);

template <class NT>
CGAL_KERNEL_INLINE
CGAL_Quotient<NT>
operator* (const CGAL_Quotient<NT>& q, const CGAL_Quotient<NT>& r);

template <class NT>
CGAL_KERNEL_INLINE
CGAL_Quotient<NT>
operator* (const NT& q, const CGAL_Quotient<NT>& r);

template <class NT>
CGAL_KERNEL_INLINE
CGAL_Quotient<NT>
operator* (const CGAL_Quotient<NT>& q, const NT& r);

template <class NT>
CGAL_KERNEL_INLINE
CGAL_Quotient<NT>
operator/ (const CGAL_Quotient<NT>& q, const CGAL_Quotient<NT>& r);

template <class NT>
CGAL_KERNEL_INLINE
CGAL_Quotient<NT>
operator/ (const NT& q, const CGAL_Quotient<NT>& r);

template <class NT>
CGAL_KERNEL_INLINE
CGAL_Quotient<NT>
operator/ (const CGAL_Quotient<NT>& q, const NT& r);

template <class NT>
inline
CGAL_Quotient<NT>
operator- (const CGAL_Quotient<NT>&);

template <class NT>
CGAL_KERNEL_INLINE
bool
operator==(const CGAL_Quotient<NT>& q, const CGAL_Quotient<NT>& r);

template <class NT>
CGAL_KERNEL_INLINE
bool
operator==(const CGAL_Quotient<NT>& q, const NT& a);

template <class NT>
CGAL_KERNEL_INLINE
bool
operator==(const NT& n, const CGAL_Quotient<NT>& q);

template <class NT>
CGAL_KERNEL_INLINE
bool
operator< (const CGAL_Quotient<NT>& q, const CGAL_Quotient<NT>& r);

template <class NT>
CGAL_KERNEL_INLINE
bool
operator< (const CGAL_Quotient<NT>& q, const NT& r);

template <class NT>
CGAL_KERNEL_INLINE
bool
operator< (const NT& q, const CGAL_Quotient<NT>& r);

#ifdef CGAL_PROVIDE_STL_PROVIDED_REL_OPS
template <class NT>
CGAL_KERNEL_INLINE
bool
operator!=(const CGAL_Quotient<NT>& q, const CGAL_Quotient<NT>& r);

template <class NT>
CGAL_KERNEL_INLINE
bool
operator!=(const CGAL_Quotient<NT>& q, const NT& a);

template <class NT>
CGAL_KERNEL_INLINE
bool
operator!=(const NT& n, const CGAL_Quotient<NT>& q);

template <class NT>
CGAL_KERNEL_INLINE
bool
operator<=(const CGAL_Quotient<NT>& q, const CGAL_Quotient<NT>& r);

template <class NT>
CGAL_KERNEL_INLINE
bool
operator<=(const CGAL_Quotient<NT>& q, const NT& r);

template <class NT>
CGAL_KERNEL_INLINE
bool
operator<=(const NT& q, const CGAL_Quotient<NT>& r);

template <class NT>
CGAL_KERNEL_INLINE
bool
operator> (const CGAL_Quotient<NT>& q, const CGAL_Quotient<NT>& r);

template <class NT>
CGAL_KERNEL_INLINE
bool
operator> (const CGAL_Quotient<NT>& q, const NT& r);

template <class NT>
CGAL_KERNEL_INLINE
bool
operator> (const NT& q, const CGAL_Quotient<NT>& r);

template <class NT>
CGAL_KERNEL_INLINE
bool operator>=(const CGAL_Quotient<NT>& q, const CGAL_Quotient<NT>& r);

template <class NT>
CGAL_KERNEL_INLINE
bool
operator>=(const CGAL_Quotient<NT>& q, const NT& r);

template <class NT>
CGAL_KERNEL_INLINE
bool
operator>=(const NT& q, const CGAL_Quotient<NT>& r);
#endif // CGAL_PROVIDE_STL_PROVIDED_REL_OPS

template <class NT>
istream&
operator>>(istream& in, CGAL_Quotient<NT>& q);

template <class NT>
ostream&
operator<<(ostream& out, const CGAL_Quotient<NT>& q);

template <class NT>
CGAL_KERNEL_INLINE
NT
CGAL_quotient_truncation(const CGAL_Quotient<NT>& r);

template <class NT>
NT
CGAL_gcd(const NT& , const NT&);

template <class NT>
class CGAL_Quotient
{
public:
  CGAL_Quotient() : num( NT(0) ), den( NT(1) ) {}
  CGAL_Quotient(const NT& n) : num(n), den( NT(1) ) {}
  CGAL_Quotient(int i) : num(NT(i)), den( NT(1) ) {}
  CGAL_Quotient(const NT& n, const NT& d) : num(n), den(d)
  { CGAL_kernel_precondition( d!= NT(0) ); }
  CGAL_Quotient(const CGAL_Quotient<NT>& r) : num(r.num), den(r.den) {}

  ~CGAL_Quotient() {}

  friend CGAL_Comparison_result
         quotient_cmp CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<NT>& q,
                                           const CGAL_Quotient<NT>& r);
  friend double
         CGAL_to_double CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<NT>& q);
  friend bool
         CGAL_is_valid CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<NT>& q);
  friend bool
         CGAL_is_finite CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<NT>& q);
  friend NT
         CGAL_numerator CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<NT>& q);
  friend NT
         CGAL_denominator CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<NT>& q);

  friend
  NT
  CGAL_quotient_truncation CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<NT>& r);


  NT            numerator() const;
  NT            denominator() const;


  CGAL_Quotient<NT>& operator+= (const CGAL_Quotient<NT>& r);
  CGAL_Quotient<NT>& operator-= (const CGAL_Quotient<NT>& r);
  CGAL_Quotient<NT>& operator*= (const CGAL_Quotient<NT>& r);
  CGAL_Quotient<NT>& operator/= (const CGAL_Quotient<NT>& r);
  CGAL_Quotient<NT>& operator+= (const NT& r);
  CGAL_Quotient<NT>& operator-= (const NT& r);
  CGAL_Quotient<NT>& operator*= (const NT& r);
  CGAL_Quotient<NT>& operator/= (const NT& r);


  friend CGAL_Quotient<NT>
         operator+ CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<NT>& q,
                                        const CGAL_Quotient<NT>& r);
  friend CGAL_Quotient<NT>
         operator- CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<NT>& q,
                                        const CGAL_Quotient<NT>& r);
  friend CGAL_Quotient<NT>
         operator* CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<NT>& q,
                                        const CGAL_Quotient<NT>& r);
  friend CGAL_Quotient<NT>
         operator/ CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<NT>& q,
                                        const CGAL_Quotient<NT>& r);
  friend CGAL_Quotient<NT>
         operator- CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<NT>&);
  friend CGAL_Quotient<NT>
         operator+ CGAL_NULL_TMPL_ARGS (const NT& q,
                                        const CGAL_Quotient<NT>& r);
  friend CGAL_Quotient<NT>
         operator+ CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<NT>& q,
                                        const NT& r);
  friend CGAL_Quotient<NT>
         operator- CGAL_NULL_TMPL_ARGS (const NT& q,
                                        const CGAL_Quotient<NT>& r);
  friend CGAL_Quotient<NT>
         operator- CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<NT>& q,
                                        const NT& r);
  friend CGAL_Quotient<NT>
         operator* CGAL_NULL_TMPL_ARGS (const NT& q,
                                        const CGAL_Quotient<NT>& r);
  friend CGAL_Quotient<NT>
         operator* CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<NT>& q,
                                        const NT& r);
  friend CGAL_Quotient<NT>
         operator/ CGAL_NULL_TMPL_ARGS (const NT& q,
                                        const CGAL_Quotient<NT>& r);
  friend CGAL_Quotient<NT>
         operator/ CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<NT>& q,
                                        const NT& r);

  friend bool
         operator== CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<NT>& q,
                                         const CGAL_Quotient<NT>& r);
  friend bool
         operator<  CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<NT>& q,
                                         const CGAL_Quotient<NT>& r);
  friend bool
         operator== CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<NT>& q,
                                         const NT& a);
  friend bool
         operator== CGAL_NULL_TMPL_ARGS (const NT& n,
                                         const CGAL_Quotient<NT>& q);
  friend bool
         operator<  CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<NT>& q,
                                         const NT& r);
  friend bool
         operator<  CGAL_NULL_TMPL_ARGS (const NT& q,
                                         const CGAL_Quotient<NT>& r);
#ifdef CGAL_PROVIDE_STL_PROVIDED_REL_OPS
  friend bool
         operator!= CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<NT>& q,
                                         const CGAL_Quotient<NT>& r);
  friend bool
         operator<= CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<NT>& q,
                                         const CGAL_Quotient<NT>& r);
  friend bool
         operator>  CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<NT>& q,
                                         const CGAL_Quotient<NT>& r);
  friend bool
         operator>= CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<NT>& q,
                                         const CGAL_Quotient<NT>& r);
#endif // CGAL_PROVIDE_STL_PROVIDED_REL_OPS
#ifdef CGAL_PROVIDE_STL_PROVIDED_REL_OPS
  friend bool
         operator!= CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<NT>& q,
                                         const NT& a);
  friend bool
         operator!= CGAL_NULL_TMPL_ARGS (const NT& n,
                                         const CGAL_Quotient<NT>& q);
  friend bool
         operator<= CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<NT>& q,
                                         const NT& r);
  friend bool
         operator<= CGAL_NULL_TMPL_ARGS (const NT& q,
                                         const CGAL_Quotient<NT>& r);
  friend bool
         operator>  CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<NT>& q,
                                         const NT& r);
  friend bool
         operator>  CGAL_NULL_TMPL_ARGS (const NT& q,
                                         const CGAL_Quotient<NT>& r);
  friend bool
         operator>= CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<NT>& q,
                                         const NT& r);
  friend bool
         operator>= CGAL_NULL_TMPL_ARGS (const NT& q,
                                         const CGAL_Quotient<NT>& r);
#endif // CGAL_PROVIDE_STL_PROVIDED_REL_OPS
/*
  friend istream&
         operator>> CGAL_NULL_TMPL_ARGS (istream& in, CGAL_Quotient<NT>& q);
*/

  CGAL_Quotient<NT>&    normalize();

protected:
  NT   num;
  NT   den;

};


#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#include <CGAL/Quotient.C>
#endif // CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION

CGAL_TEMPLATE_NULL
class CGAL_Quotient<int>
{
public:
  CGAL_Quotient() : num( 0 ), den( 1 ) {}
  CGAL_Quotient(int i) : num( i ), den( 1 ) {}
  CGAL_Quotient(const int& n, const int& d) : num(n), den(d)
  { CGAL_kernel_precondition( d!= 0 ); }
  CGAL_Quotient(const CGAL_Quotient<int>& r) : num(r.num), den(r.den) {}
  ~CGAL_Quotient() {}

friend double
       CGAL_to_double CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<int>& q);
friend bool
       CGAL_is_valid CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<int>& q);
friend bool
       CGAL_is_finite CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<int>& q);
friend int
       CGAL_numerator CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<int>& q);
friend int
       CGAL_denominator CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<int>& q);

friend
int
CGAL_quotient_truncation CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<int>& r);

/*
friend
ostream&
operator<< CGAL_NULL_TMPL_ARGS (ostream& out, const CGAL_Quotient<int>& q);

friend
istream&
operator>> CGAL_NULL_TMPL_ARGS (istream& in, CGAL_Quotient<int>& q);
*/


  int                 numerator() const
                      { return num; }
  int                 denominator() const
                      { return den; }
  CGAL_Quotient<int>& normalize()
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
                        int ggt = CGAL_gcd(num, den);
                        if (ggt != 1 )
                        {
                            num /= ggt;
                            den /= ggt;
                        }
                        return (*this);
                      }


  CGAL_Quotient<int>& operator+= (const CGAL_Quotient<int>& r)
                      {
                        num = num * r.den + r.num * den;
                        den *= r.den;
                        return (*this);
                      }
  CGAL_Quotient<int>& operator-= (const CGAL_Quotient<int>& r)
                      {
                        num = num * r.den - r.num * den;
                        den *= r.den;
                        return (*this);
                      }
  CGAL_Quotient<int>& operator*= (const CGAL_Quotient<int>& r)
                      {
                        num *= r.num;
                        den *= r.den;
                        return (*this);
                      }
  CGAL_Quotient<int>& operator/= (const CGAL_Quotient<int>& r)
                      {
                        CGAL_kernel_precondition( r.num != 0 );
                        num *= r.den;
                        den *= r.num;
                        return (*this);
                      }
  CGAL_Quotient<int>& operator+= (const int& r)
                      {
                        num = num + r * den;
                        return (*this);
                      }
  CGAL_Quotient<int>& operator-= (const int& r)
                      {
                        num = num - r * den;
                        return (*this);
                      }
  CGAL_Quotient<int>& operator*= (const int& r)
                      {
                        num *= r ;
                        return (*this);
                      }
  CGAL_Quotient<int>& operator/= (const int& r)
                      {
                        CGAL_kernel_precondition( r != 0 );
                        den *= r ;
                        return (*this);
                      }

friend CGAL_Quotient<int>
       operator+ CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<int>& q,
                                      const CGAL_Quotient<int>& r);
friend CGAL_Quotient<int>
       operator- CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<int>& q,
                                      const CGAL_Quotient<int>& r);
friend CGAL_Quotient<int>
       operator* CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<int>& q,
                                      const CGAL_Quotient<int>& r);
friend CGAL_Quotient<int>
       operator/ CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<int>& q,
                                      const CGAL_Quotient<int>& r);
friend CGAL_Quotient<int>
       operator- CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<int>&);
friend CGAL_Quotient<int>
       operator+ CGAL_NULL_TMPL_ARGS (const int& q,
                                      const CGAL_Quotient<int>& r);
friend CGAL_Quotient<int>
       operator+ CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<int>& q,
                                      const int& r);
friend CGAL_Quotient<int>
       operator- CGAL_NULL_TMPL_ARGS (const int& q,
                                      const CGAL_Quotient<int>& r);
friend CGAL_Quotient<int>
       operator- CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<int>& q,
                                      const int& r);
friend CGAL_Quotient<int>
       operator* CGAL_NULL_TMPL_ARGS (const int& q,
                                      const CGAL_Quotient<int>& r);
friend CGAL_Quotient<int>
       operator* CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<int>& q,
                                      const int& r);
friend CGAL_Quotient<int>
       operator/ CGAL_NULL_TMPL_ARGS (const int& q,
                                      const CGAL_Quotient<int>& r);
friend CGAL_Quotient<int>
       operator/ CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<int>& q,
                                      const int& r);
friend CGAL_Comparison_result
       quotient_cmp CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<int>& q,
                                         const CGAL_Quotient<int>& r);
friend bool
       operator== CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<int>& q,
                                       const CGAL_Quotient<int>& r);
friend bool
       operator<  CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<int>& q,
                                       const CGAL_Quotient<int>& r);
friend bool
       operator== CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<int>& q,
                                       const int& a);
friend bool
       operator== CGAL_NULL_TMPL_ARGS (const int& n,
                                       const CGAL_Quotient<int>& q);
friend bool
       operator<  CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<int>& q,
                                       const int& r);
friend bool
       operator<  CGAL_NULL_TMPL_ARGS (const int& q,
                                       const CGAL_Quotient<int>& r);
#ifdef CGAL_PROVIDE_STL_PROVIDED_REL_OPS
friend bool
       operator!= CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<int>& q,
                                       const CGAL_Quotient<int>& r);
friend bool
       operator<= CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<int>& q,
                                       const CGAL_Quotient<int>& r);
friend bool
       operator>  CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<int>& q,
                                       const CGAL_Quotient<int>& r);
friend bool
       operator>= CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<int>& q,
                                       const CGAL_Quotient<int>& r);
#endif // CGAL_PROVIDE_STL_PROVIDED_REL_OPS
#ifdef CGAL_PROVIDE_STL_PROVIDED_REL_OPS
friend bool
       operator!= CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<int>& q,
                                       const int& a);
friend bool
       operator!= CGAL_NULL_TMPL_ARGS (const int& n,
                                       const CGAL_Quotient<int>& q);
friend bool
       operator<= CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<int>& q,
                                       const int& r);
friend bool
       operator<= CGAL_NULL_TMPL_ARGS (const int& q,
                                       const CGAL_Quotient<int>& r);
friend bool
       operator>  CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<int>& q,
                                       const int& r);
friend bool
       operator>  CGAL_NULL_TMPL_ARGS (const int& q,
                                       const CGAL_Quotient<int>& r);
friend bool
       operator>= CGAL_NULL_TMPL_ARGS (const CGAL_Quotient<int>& q,
                                       const int& r);
friend bool
       operator>= CGAL_NULL_TMPL_ARGS (const int& q,
                                       const CGAL_Quotient<int>& r);
#endif // CGAL_PROVIDE_STL_PROVIDED_REL_OPS

protected:
  int num;
  int den;

};


#endif // CGAL_QUOTIENT_H
