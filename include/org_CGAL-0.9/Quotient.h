/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/


//  Author:
//  The template class CGAL_Quotient<NT> is based on the LEDA class
//  rational written by Stefan Naeher and Christian Uhrig.
//  It is basically a templated version with restricted functionality
//  of the version of rational in LEDA release 3.3.
//  The modification was done by Stefan Schirra


#ifndef CGAL_QUOTIENT_H
#define CGAL_QUOTIENT_H

#include <CGAL/basic.h>
#include <ctype.h>

template <class NT> class CGAL_Quotient;

template <class NT> double CGAL_to_double(const CGAL_Quotient<NT>& q);
template <class NT> bool   CGAL_is_valid(const CGAL_Quotient<NT>& q);
template <class NT> bool   CGAL_is_finite(const CGAL_Quotient<NT>& q);
template <class NT> NT     CGAL_numerator(const CGAL_Quotient<NT>& q);
template <class NT> NT     CGAL_denominator(const CGAL_Quotient<NT>& q);
template <class NT> CGAL_Quotient_tag
                           CGAL_number_type_tag(const CGAL_Quotient<NT>& q);

template <class NT>
class CGAL_Quotient
{

protected:

  NT num;
  NT den;

public:

  CGAL_Quotient() : num( NT(0) ), den( NT(1) )
    {
    }
  CGAL_Quotient(const NT& n) : num(n), den( NT(1) )
    {
    }
  CGAL_Quotient(int i) : num(NT(i)), den( NT(1) )
    {
    }
  CGAL_Quotient(const NT& n, const NT& d) : num(n), den(d)
    {
      CGAL_kernel_precondition( d!= NT(0) );
    }
  CGAL_Quotient(const CGAL_Quotient<NT>& r) : num(r.num), den(r.den)
    {
    }
  CGAL_Quotient<NT>& operator=(const CGAL_Quotient<NT>&);


 ~CGAL_Quotient()
    {
    }

  CGAL_Quotient<NT>& operator+= (const CGAL_Quotient<NT>& r);
  CGAL_Quotient<NT>& operator+= (const NT& r);
  CGAL_Quotient<NT>& operator-= (const CGAL_Quotient<NT>& r);
  CGAL_Quotient<NT>& operator-= (const NT& r);
  CGAL_Quotient<NT>& operator*= (const CGAL_Quotient<NT>& r);
  CGAL_Quotient<NT>& operator*= (const NT& r);
  CGAL_Quotient<NT>& operator/= (const CGAL_Quotient<NT>& r);
  CGAL_Quotient<NT>& operator/= (const NT& r);

// arithmetic operators

  friend CGAL_Quotient<NT> operator+ (const CGAL_Quotient<NT>& q,
                                      const CGAL_Quotient<NT>& r);
  friend CGAL_Quotient<NT> operator+ (const NT& q, const CGAL_Quotient<NT>& r);
  friend CGAL_Quotient<NT> operator+ (const CGAL_Quotient<NT>& q, const NT& r);

  friend CGAL_Quotient<NT> operator- (const CGAL_Quotient<NT>& q,
                                      const CGAL_Quotient<NT>& r);
  friend CGAL_Quotient<NT> operator- (const NT& q, const CGAL_Quotient<NT>& r);
  friend CGAL_Quotient<NT> operator- (const CGAL_Quotient<NT>& q, const NT& r);

  friend CGAL_Quotient<NT> operator* (const CGAL_Quotient<NT>& q,
                                      const CGAL_Quotient<NT>& r);
  friend CGAL_Quotient<NT> operator* (const NT& q, const CGAL_Quotient<NT>& r);
  friend CGAL_Quotient<NT> operator* (const CGAL_Quotient<NT>& q, const NT& r);

  friend CGAL_Quotient<NT> operator/ (const CGAL_Quotient<NT>& q,
                                      const CGAL_Quotient<NT>& r);
  friend CGAL_Quotient<NT> operator/ (const NT& q, const CGAL_Quotient<NT>& r);
  friend CGAL_Quotient<NT> operator/ (const CGAL_Quotient<NT>& q, const NT& r);

  friend CGAL_Quotient<NT> operator- (const CGAL_Quotient<NT>&);
  friend
  CGAL_Comparison_result
  quotient_cmp(const CGAL_Quotient<NT>& q, const CGAL_Quotient<NT>& r);
// comparison operators

  friend bool operator==(const CGAL_Quotient<NT>& q,
                         const CGAL_Quotient<NT>& r);
  friend bool operator==(const CGAL_Quotient<NT>& q, const NT& a);
  friend bool operator==(const NT& n, const CGAL_Quotient<NT>& q);

  friend bool operator!=(const CGAL_Quotient<NT>& q,
                         const CGAL_Quotient<NT>& r);
  friend bool operator!=(const CGAL_Quotient<NT>& q, const NT& a);
  friend bool operator!=(const NT& n, const CGAL_Quotient<NT>& q);

  friend bool operator< (const CGAL_Quotient<NT>& q,
                         const CGAL_Quotient<NT>& r);
  friend bool operator< (const CGAL_Quotient<NT>& q, const NT& r);
  friend bool operator< (const NT& q, const CGAL_Quotient<NT>& r);

  friend bool operator<=(const CGAL_Quotient<NT>& q,
                         const CGAL_Quotient<NT>& r);
  friend bool operator<=(const CGAL_Quotient<NT>& q, const NT& r);
  friend bool operator<=(const NT& q, const CGAL_Quotient<NT>& r);

  friend bool operator> (const CGAL_Quotient<NT>& q,
                         const CGAL_Quotient<NT>& r);
  friend bool operator> (const CGAL_Quotient<NT>& q, const NT& r);
  friend bool operator> (const NT& q, const CGAL_Quotient<NT>& r);

  friend bool operator>=(const CGAL_Quotient<NT>& q,
                         const CGAL_Quotient<NT>& r);
  friend bool operator>=(const CGAL_Quotient<NT>& q, const NT& r);
  friend bool operator>=(const NT& q, const CGAL_Quotient<NT>& r);
  NT            numerator() const;

  NT            denominator() const;
  friend double CGAL_to_double(const CGAL_Quotient<NT>& q);
  friend bool   CGAL_is_valid(const CGAL_Quotient<NT>& q);
  friend bool   CGAL_is_finite(const CGAL_Quotient<NT>& q);
  friend NT     CGAL_numerator(const CGAL_Quotient<NT>& q);
  friend NT     CGAL_denominator(const CGAL_Quotient<NT>& q);



  CGAL_Quotient<NT>& normalize();

  friend NT  CGAL_quotient_truncation(const CGAL_Quotient<NT>& r);

  friend istream& operator>>(istream& in, CGAL_Quotient<NT>& q);
  friend ostream& operator<<(ostream& out, const CGAL_Quotient<NT>& q);
};

#include <CGAL/IO/io_tags.h>
template < class NT >
inline
CGAL_io_Operator
CGAL_io_tag(const CGAL_Quotient<NT>&)
{
  return CGAL_io_Operator();
}


#ifdef CGAL_INCLUDE_TEMPLATE_CODE
#include <CGAL/Quotient.C>
#endif // CGAL_INCLUDE_TEMPLATE_CODE

#endif // CGAL_QUOTIENT_H

