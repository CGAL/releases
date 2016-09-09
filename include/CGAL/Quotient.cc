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


#ifndef CGAL_QUOTIENT_CC
#define CGAL_QUOTIENT_CC

template <class NT>
NT
CGAL_gcd(const NT& p, const NT& q)
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
      num = den = 1;
      return (*this);
  }
  if (-num == den)
  {
      num = -1;
      den = 1;
      return (*this);
  }
  NT ggt = CGAL_gcd(num, den);
  if (ggt != 1)
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
            return (leftop > rightop) ? CGAL_LARGER : CGAL_EQUAL;
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
   // Format: "r.num / r.den"
   char c;

   do in.get(c); while (isspace(c));
   in.putback(c);

   NT rx;
   in >> rx;

   do in.get(c); while (isspace(c));

   CGAL_kernel_precondition( c == '/' );

   do in.get(c); while (isspace(c));
   in.putback(c);

   NT ry;
   in >> ry;

   r = CGAL_Quotient<NT>(rx,ry);

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


#endif  // CGAL_QUOTIENT_CC
