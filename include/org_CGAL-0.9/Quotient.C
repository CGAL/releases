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


#ifndef CGAL_QUOTIENT_C
#define CGAL_QUOTIENT_C

template <class NT>
NT
CGAL_gcd(const NT&, const NT&)
{
  return NT(1);
}

template <class NT>
double
CGAL_to_double(const CGAL_Quotient<NT>& q)
{
 if (q.num == NT(0) )
 {
    return 0;
 }

 double nd = CGAL_to_double( q.num );

 if (q.den == NT(1) )
 {
    return nd;
 }

 double dd = CGAL_to_double( q.den );

 if ( CGAL_is_finite( q.den )&&(CGAL_is_finite( q.num )) )
 {
    return nd/dd ;
 }
 if ( CGAL_abs(q.num) > CGAL_abs(q.den) )
 {
    NT  nt_div = q.num / q.den;
    double divd = CGAL_to_double(nt_div);
    if ( divd >= ldexp(1.0,53) )
    {
        return divd;
    }
 }
 if ( CGAL_abs(q.num) < CGAL_abs(q.den) )
 {
    return 1.0 / CGAL_to_double( NT(1) / q );
 }
 return nd/dd ;
}

template <class NT>
bool
CGAL_is_valid(const CGAL_Quotient<NT>& q)
{
 return CGAL_is_valid(q.num) && CGAL_is_valid(q.den) ;
}

template <class NT>
bool
CGAL_is_finite(const CGAL_Quotient<NT>& q)
{
 return (CGAL_is_finite(q.num))&&(CGAL_is_finite(q.den)) ;
}

template <class NT>
NT
CGAL_denominator(const CGAL_Quotient<NT>& q)
{
 return q.den ;
}

template <class NT>
NT
CGAL_numerator(const CGAL_Quotient<NT>& q)
{
 return q.num ;
}

template <class NT>
CGAL_Quotient_tag
CGAL_number_type_tag(const CGAL_Quotient<NT>& q)
{
 return CGAL_Quotient_tag();
}

template <class NT>
CGAL_Quotient<NT> &
CGAL_Quotient<NT>::normalize()
{
  // divides numerator and denominator by their greatest common divisor

  if (num == den)
  {
      num = den = NT(1);
      return (*this);
  }
  if (-num == den)
  {
      num = NT(-1);
      den = NT( 1);
      return (*this);
  }
  NT ggt = CGAL_gcd(num, den);
  if (ggt != NT(1) )
  {
      num /= ggt;
      den /= ggt;
  }
  return (*this);
}

// Arithmetic Operators

template <class NT>
CGAL_Quotient<NT>&
CGAL_Quotient<NT>::operator+= (const CGAL_Quotient<NT>& r)
{
    num = num * r.den + r.num * den;
    den *= r.den;
    return (*this);
}

template <class NT>
CGAL_Quotient<NT>&
CGAL_Quotient<NT>::operator+= (const NT& r)
{
    num = num + r * den;
    return (*this);
}

template <class NT>
CGAL_Quotient<NT>&
CGAL_Quotient<NT>::operator-= (const CGAL_Quotient<NT>& r)
{
    num = num * r.den - r.num * den;
    den *= r.den;
    return (*this);
}

template <class NT>
CGAL_Quotient<NT>&
CGAL_Quotient<NT>::operator-= (const NT& r)
{
    num = num - r * den;
    return (*this);
}

template <class NT>
CGAL_Quotient<NT>&
CGAL_Quotient<NT>::operator*= (const CGAL_Quotient<NT>& r)
{
    num *= r.num;
    den *= r.den;
    return (*this);
}

template <class NT>
CGAL_Quotient<NT>&
CGAL_Quotient<NT>::operator*= (const NT& r)
{
    num *= r ;
    return (*this);
}

template <class NT>
CGAL_Quotient<NT>&
CGAL_Quotient<NT>::operator/= (const CGAL_Quotient<NT>& r)
{
    CGAL_kernel_precondition( r.num != NT(0) );
    num *= r.den;
    den *= r.num;
    return (*this);
}

template <class NT>
CGAL_Quotient<NT>&
CGAL_Quotient<NT>::operator/= (const NT& r)
{
    CGAL_kernel_precondition( r != NT(0) );
    den *= r ;
    return (*this);
}

// Assignment Operator

template <class NT>
CGAL_Quotient<NT>&
CGAL_Quotient<NT>::operator= (const CGAL_Quotient<NT>& r)
{
    if (this == &r) return *this; // to handle r = r correctly
    num = r.num;
    den = r.den;
    return *this;
}

template <class NT>
CGAL_Comparison_result
quotient_cmp(const CGAL_Quotient<NT>& x, const CGAL_Quotient<NT>& y)
{
    // In contrast to LEDA class rational, no assumptions
    // on the sign of  den  are made

    // code assumes that CGAL_SMALLER == - 1;
    CGAL_kernel_precondition( CGAL_SMALLER == (CGAL_Comparison_result)(-1) );

    int xsign = CGAL_sign(x.num) * CGAL_sign(x.den) ;
    int ysign = CGAL_sign(y.num) * CGAL_sign(y.den) ;
    if (xsign == 0) return (CGAL_Comparison_result) -ysign;
    if (ysign == 0) return (CGAL_Comparison_result)  xsign;
    // now (x != 0) && (y != 0)
    int diff = xsign - ysign;
    if (diff == 0)
    {
        int msign = CGAL_sign(x.den) * CGAL_sign(y.den);
        NT leftop  = x.num * y.den * NT(msign);
        NT rightop = y.num * x.den * NT(msign);
        if (leftop < rightop)
        {
            return CGAL_SMALLER;
        }
        else
        {
            return (rightop < leftop) ? CGAL_LARGER : CGAL_EQUAL;
        }
    }
    else
    {
        return (xsign < ysign) ? CGAL_SMALLER : CGAL_LARGER;
    }
}


// friend functions

template <class NT>
ostream&
operator<< (ostream& s, const CGAL_Quotient<NT>& r)
{
   s << r.num << "/" << r.den;
   return s;
}

template <class NT>
istream&
operator>> (istream& in, CGAL_Quotient<NT>& r)
{
   char c;
   while (in.get(c) && isspace(c));
   if (in) in.putback(c);

   NT num;
   NT den(1);

   in >> num;

   while (in.get(c) && isspace(c));

   CGAL_kernel_assertion( (!in) || (c == '/') );

   while (in.get(c) && isspace(c));
   if (in) in.putback(c);
   if (in) in >> den;

   r = CGAL_Quotient<NT>(num, den);
   return in;
}

template <class NT>
NT
CGAL_Quotient<NT>::numerator() const
{
  return num;
}

template <class NT>
NT
CGAL_Quotient<NT>::denominator() const
{
  return den;
}

template <class NT>
CGAL_Quotient<NT>
operator+(const CGAL_Quotient<NT>& x, const CGAL_Quotient<NT>& y)
{
  CGAL_Quotient<NT> z = x;
  return z += y;
}

template <class NT>
CGAL_Quotient<NT>
operator+(const NT& x, const CGAL_Quotient<NT>& y)
{
  CGAL_Quotient<NT> z(x);
  return z += y;
}

template <class NT>
CGAL_Quotient<NT>
operator+(const CGAL_Quotient<NT>& x, const NT& y)
{
  CGAL_Quotient<NT> z = x;
  return z += y;
}


template <class NT>
CGAL_Quotient<NT>
operator-(const CGAL_Quotient<NT>& x, const CGAL_Quotient<NT>& y)
{
  CGAL_Quotient<NT> z = x;
  return z -= y;
}

template <class NT>
CGAL_Quotient<NT>
operator-(const NT& x, const CGAL_Quotient<NT>& y)
{
  CGAL_Quotient<NT> z(x);
  return z -= y;
}

template <class NT>
CGAL_Quotient<NT>
operator-(const CGAL_Quotient<NT>& x, const NT& y)
{
  CGAL_Quotient<NT> z = x;
  return z -= y;
}


template <class NT>
CGAL_Quotient<NT>
operator*(const CGAL_Quotient<NT>& x, const CGAL_Quotient<NT>& y)
{
  CGAL_Quotient<NT> z = x;
  return z *= y;
}

template <class NT>
CGAL_Quotient<NT>
operator*(const NT& x, const CGAL_Quotient<NT>& y)
{
  CGAL_Quotient<NT> z(x);
  return z *= y;
}

template <class NT>
CGAL_Quotient<NT>
operator*(const CGAL_Quotient<NT>& x, const NT& y)
{
  CGAL_Quotient<NT> z = x;
  return z *= y;
}


template <class NT>
CGAL_Quotient<NT>
operator/(const CGAL_Quotient<NT>& x, const CGAL_Quotient<NT>& y)
{
  CGAL_Quotient<NT> z = x;
  return z /= y;
}

template <class NT>
CGAL_Quotient<NT>
operator/(const NT& x, const CGAL_Quotient<NT>& y)
{
  CGAL_Quotient<NT> z(x) ;
  return z /= y;
}

template <class NT>
CGAL_Quotient<NT>
operator/(const CGAL_Quotient<NT>& x, const NT& y)
{
  CGAL_Quotient<NT> z = x;
  return z /= y;
}


template <class NT>
CGAL_Quotient<NT>
operator-(const CGAL_Quotient<NT>& x)
{
  return CGAL_Quotient<NT>(-x.num,x.den);
}

//template <class NT>
//int
//quotient_sign(const CGAL_Quotient<NT>& r)
//{
  //return sign(r.num) * sign(r.den);
//}

template <class NT>
NT
CGAL_quotient_truncation(const CGAL_Quotient<NT>& r)
{
   return (r.num / r.den);
}

// comparison operators

template <class NT>
bool
operator==(const CGAL_Quotient<NT>& x, const CGAL_Quotient<NT>& y)
{
  return x.num * y.den == x.den * y.num;
}

template <class NT>
bool
operator==(const CGAL_Quotient<NT>& x, const NT& y)
{
  return x.den * y == x.num;
}

template <class NT>
bool
operator==(const NT& x, const CGAL_Quotient<NT>& y)
{
  return y.den * x == y.num;
}

template <class NT>
bool
operator!=(const CGAL_Quotient<NT>& x, const CGAL_Quotient<NT>& y)
{
  return x.num * y.den != x.den * y.num;
}

template <class NT>
bool
operator!=(const CGAL_Quotient<NT>& x, const NT& y)
{
  return x.den * y != x.num;
}

template <class NT>
bool
operator!=(const NT& x, const CGAL_Quotient<NT>& y)
{
  return y.den * x != y.num;
}

template <class NT>
bool
operator<(const CGAL_Quotient<NT>& x, const CGAL_Quotient<NT>& y)
{
  return quotient_cmp(x,y) == CGAL_SMALLER; // < 0
}

template <class NT>
bool
operator<(const CGAL_Quotient<NT>& x, const NT& y)
{
  return quotient_cmp(x,CGAL_Quotient<NT>(y)) == CGAL_SMALLER; // < 0
}

template <class NT>
bool
operator<(const NT& x, const CGAL_Quotient<NT>& y)
{
  return quotient_cmp(CGAL_Quotient<NT>(x),y) == CGAL_SMALLER; // < 0
}

template <class NT>
bool
operator<=(const CGAL_Quotient<NT>& x, const CGAL_Quotient<NT>& y)
{
  return quotient_cmp(x,y) != CGAL_LARGER; // <= 0
}

template <class NT>
bool
operator<=(const CGAL_Quotient<NT>& x, const NT& y)
{
  return quotient_cmp(x,CGAL_Quotient<NT>(y)) != CGAL_LARGER; // <= 0
}

template <class NT>
bool
operator<=(const NT& x, const CGAL_Quotient<NT>& y)
{
  return quotient_cmp(CGAL_Quotient<NT>(x),y) != CGAL_LARGER; // <= 0
}

template <class NT>
bool
operator>(const CGAL_Quotient<NT>& x, const CGAL_Quotient<NT>& y)
{
  return  quotient_cmp(x,y) == CGAL_LARGER; // > 0
}

template <class NT>
bool
operator>(const CGAL_Quotient<NT>& x, const NT& y)
{
  return  quotient_cmp(x,CGAL_Quotient<NT>(y)) == CGAL_LARGER; // > 0
}

template <class NT>
bool
operator>(const NT& x, const CGAL_Quotient<NT>& y)
{
  return  quotient_cmp(CGAL_Quotient<NT>(x),y) == CGAL_LARGER; // > 0
}

template <class NT>
bool
operator>=(const CGAL_Quotient<NT>& x, const CGAL_Quotient<NT>& y)
{
  return quotient_cmp(x,y) != CGAL_SMALLER; // >= 0
}

template <class NT>
bool
operator>=(const CGAL_Quotient<NT>& x, const NT& y)
{
  return quotient_cmp(x,CGAL_Quotient<NT>(y)) != CGAL_SMALLER; // >= 0
}

template <class NT>
bool
operator>=(const NT& x, const CGAL_Quotient<NT>& y)
{
  return quotient_cmp(CGAL_Quotient<NT>(x),y) != CGAL_SMALLER; // >= 0
}


#endif  // CGAL_QUOTIENT_C
