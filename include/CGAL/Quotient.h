//  Copyright CGAL 1996
//
//  cgal@cs.ruu.nl
//
//  This file is part of an internal release of the CGAL kernel.
//  The code herein may be used and/or copied only in accordance
//  with the terms and conditions stipulated in the agreement
//  under which the code has been supplied or with the written
//  permission of the CGAL Project.
//
//  Look at http://www.cs.ruu.nl/CGAL/ for more information.
//  Please send any bug reports and comments to cgal@cs.ruu.nl
//
//  The code comes WITHOUT ANY WARRANTY; without even the implied
//  warranty of FITNESS FOR A PARTICULAR PURPOSE.
//

//  Author:
//  The template class CGAL_Quotient<NT> is based on the LEDA class
//  rational written by Stefan Naeher and Christian Uhrig.
//  It is basically a templated version with restricted functionality
//  of the version of rational in LEDA release 3.3.
//  The modification was made by Stefan.Schirra@mpi-sb.mpg.de


#ifndef CGAL_QUOTIENT_H
#define CGAL_QUOTIENT_H

#include <math.h>
#include <CGAL/utils.h>
#include <CGAL/enum.h>
#include <CGAL/misc.h>
#include <CGAL/number_utils.h>
// #include <CGAL/Float.h>
#include <CGAL/Double.h>
#include <iostream.h>

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


#include <CGAL/Quotient.cc>



#endif // QUOTIENT_H
