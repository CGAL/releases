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
// file          : include/CGAL/Quotient.C
// package       : Number_types (2.1.5)
// revision      : 2.1.5
// revision_date : 09 May 1999 
//
// author(s)     :
//
//  The template class Quotient<NT> is based on the LEDA class
//  leda_rational written by Stefan Naeher and Christian Uhrig.
//  It is basically a templated version with restricted functionality
//  of the version of rational in LEDA release 3.3.
//  The modification was done by Stefan.Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : cgal@cs.uu.nl
//
// ======================================================================


#include <CGAL/Quotient.h>

#ifndef CGAL_QUOTIENT_C
#define CGAL_QUOTIENT_C

CGAL_BEGIN_NAMESPACE

template <class NT>
CGAL_KERNEL_MEDIUM_INLINE
Quotient<NT>&
Quotient<NT>::normalize()
{
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
  NT ggt = gcd(num, den);
  if (ggt != NT(1) )
  {
      num /= ggt;
      den /= ggt;
  }
  return (*this);
}

template <class NT>
CGAL_KERNEL_INLINE
Quotient<NT>&
Quotient<NT>::operator+= (const Quotient<NT>& r)
{
    num = num * r.den + r.num * den;
    den *= r.den;
    return (*this);
}

template <class NT>
CGAL_KERNEL_INLINE
Quotient<NT>&
Quotient<NT>::operator-= (const Quotient<NT>& r)
{
    num = num * r.den - r.num * den;
    den *= r.den;
    return (*this);
}

template <class NT>
CGAL_KERNEL_INLINE
Quotient<NT>&
Quotient<NT>::operator*= (const Quotient<NT>& r)
{
    num *= r.num;
    den *= r.den;
    return (*this);
}

template <class NT>
CGAL_KERNEL_INLINE
Quotient<NT>&
Quotient<NT>::operator/= (const Quotient<NT>& r)
{
    CGAL_kernel_precondition( r.num != NT(0) );
    num *= r.den;
    den *= r.num;
    return (*this);
}
template <class NT>
CGAL_KERNEL_INLINE
Quotient<NT>&
Quotient<NT>::operator+= (const NT& r)
{
    num = num + r * den;
    return (*this);
}

template <class NT>
CGAL_KERNEL_INLINE
Quotient<NT>&
Quotient<NT>::operator-= (const NT& r)
{
    num = num - r * den;
    return (*this);
}

template <class NT>
CGAL_KERNEL_INLINE
Quotient<NT>&
Quotient<NT>::operator*= (const NT& r)
{
    num *= r ;
    return (*this);
}

template <class NT>
CGAL_KERNEL_INLINE
Quotient<NT>&
Quotient<NT>::operator/= (const NT& r)
{
    CGAL_kernel_precondition( r != NT(0) );
    den *= r ;
    return (*this);
}
template <class NT>
CGAL_KERNEL_MEDIUM_INLINE
Comparison_result
quotient_cmp(const Quotient<NT>& x, const Quotient<NT>& y)
{
    // In contrast to LEDA class rational, no assumptions
    // on the sign of  den  are made

    // code assumes that SMALLER == - 1;
    CGAL_kernel_precondition( SMALLER == (Comparison_result)(-1) );

    int xsign = CGAL::sign(x.num) * CGAL::sign(x.den) ;
    int ysign = CGAL::sign(y.num) * CGAL::sign(y.den) ;
    if (xsign == 0) return (Comparison_result) -ysign;
    if (ysign == 0) return (Comparison_result)  xsign;
    // now (x != 0) && (y != 0)
    int diff = xsign - ysign;
    if (diff == 0)
    {
        int msign = CGAL::sign(x.den) * CGAL::sign(y.den);
        NT leftop  = x.num * y.den * NT(msign);
        NT rightop = y.num * x.den * NT(msign);
        if (leftop < rightop)
        {
            return SMALLER;
        }
        else
        {
            return (rightop < leftop) ? LARGER : EQUAL;
        }
    }
    else
    {
        return (xsign < ysign) ? SMALLER : LARGER;
    }
}

template <class NT>
std::ostream&
operator<<(std::ostream& s, const Quotient<NT>& r)
{
   s << r.numerator() << "/" << r.denominator();
   return s;
}

template <class NT>
std::istream&
operator>>(std::istream& in, Quotient<NT>& r)
{
  /* format  num/den  or simply  num  */

  char c = 0;

  while (in.get(c) && isspace(c));
  if ( !in ) return in;
  in.putback(c);

  NT num;
  NT den(1);
  in >> num;

  while (in.get(c) && isspace(c));
  if (( in ) && ( c == '/'))
  {
      while (in.get(c) && isspace(c));
      CGAL_kernel_assertion( in );
      in.putback(c);
      in >> den;
  }
  else
  {
      in.putback(c);
      if ( in.eof() ) in.clear();
  }
  r = Quotient<NT>( num, den);
  return in;
}

template <class NT>
inline
io_Operator
io_tag(const Quotient<NT>&)
{ return io_Operator(); }
template <class NT>
inline
NT
Quotient<NT>::numerator() const
{ return num; }

template <class NT>
inline
NT
Quotient<NT>::denominator() const
{ return den; }
template <class NT>
CGAL_KERNEL_INLINE
Quotient<NT>
operator+(const Quotient<NT>& x, const Quotient<NT>& y)
{
  Quotient<NT> z = x;
  return z += y;
}

template <class NT>
CGAL_KERNEL_INLINE
Quotient<NT>
operator-(const Quotient<NT>& x, const Quotient<NT>& y)
{
/*
  Quotient<NT> z = x;
  return z -= y;
*/
  return (Quotient<NT>(x) -= y);
}

template <class NT>
CGAL_KERNEL_INLINE
Quotient<NT>
operator*(const Quotient<NT>& x, const Quotient<NT>& y)
{
  Quotient<NT> z = x;
  return z *= y;
}

template <class NT>
CGAL_KERNEL_INLINE
Quotient<NT>
operator/(const Quotient<NT>& x, const Quotient<NT>& y)
{
  Quotient<NT> z = x;
  return z /= y;
}

template <class NT>
inline
Quotient<NT>
operator-(const Quotient<NT>& x)
{ return Quotient<NT>(-x.num,x.den); }

template <class NT>
CGAL_KERNEL_INLINE
Quotient<NT>
operator+(const NT& x, const Quotient<NT>& y)
{
  Quotient<NT> z(x);
  return z += y;
}

template <class NT>
CGAL_KERNEL_INLINE
Quotient<NT>
operator+(const Quotient<NT>& x, const NT& y)
{
  Quotient<NT> z = x;
  return z += y;
}

template <class NT>
CGAL_KERNEL_INLINE
Quotient<NT>
operator-(const NT& x, const Quotient<NT>& y)
{
  Quotient<NT> z(x);
  return z -= y;
}

template <class NT>
CGAL_KERNEL_INLINE
Quotient<NT>
operator-(const Quotient<NT>& x, const NT& y)
{
  Quotient<NT> z = x;
  return z -= y;
}

template <class NT>
CGAL_KERNEL_INLINE
Quotient<NT>
operator*(const NT& x, const Quotient<NT>& y)
{
  Quotient<NT> z(x);
  return z *= y;
}

template <class NT>
CGAL_KERNEL_INLINE
Quotient<NT>
operator*(const Quotient<NT>& x, const NT& y)
{
  Quotient<NT> z = x;
  return z *= y;
}

template <class NT>
CGAL_KERNEL_INLINE
Quotient<NT>
operator/(const NT& x, const Quotient<NT>& y)
{
  Quotient<NT> z(x) ;
  return z /= y;
}

template <class NT>
CGAL_KERNEL_INLINE
Quotient<NT>
operator/(const Quotient<NT>& x, const NT& y)
{
  Quotient<NT> z = x;
  return z /= y;
}
template <class NT>
CGAL_KERNEL_INLINE
NT
quotient_truncation(const Quotient<NT>& r)
{ return (r.num / r.den); }

template <class NT>
CGAL_KERNEL_INLINE
bool
operator==(const Quotient<NT>& x, const Quotient<NT>& y)
{ return x.num * y.den == x.den * y.num; }

template <class NT>
CGAL_KERNEL_INLINE
bool
operator<(const Quotient<NT>& x, const Quotient<NT>& y)
{
  return quotient_cmp(x,y) == SMALLER; // < 0
}
template <class NT>
CGAL_KERNEL_INLINE
bool
operator==(const Quotient<NT>& x, const NT& y)
{ return x.den * y == x.num; }

template <class NT>
CGAL_KERNEL_INLINE
bool
operator==(const NT& x, const Quotient<NT>& y)
{ return y.den * x == y.num; }

template <class NT>
CGAL_KERNEL_INLINE
bool
operator<(const Quotient<NT>& x, const NT& y)
{
  return quotient_cmp(x,Quotient<NT>(y)) == SMALLER; // < 0
}

template <class NT>
CGAL_KERNEL_INLINE
bool
operator<(const NT& x, const Quotient<NT>& y)
{
  return quotient_cmp(Quotient<NT>(x),y) == SMALLER; // < 0
}
#ifndef CGAL_NO_STL_PROVIDED_REL_OPS
template <class NT>
CGAL_KERNEL_INLINE
bool
operator!=(const Quotient<NT>& x, const Quotient<NT>& y)
{ return x.num * y.den != x.den * y.num; }

template <class NT>
CGAL_KERNEL_INLINE
bool
operator<=(const Quotient<NT>& x, const Quotient<NT>& y)
{
  return quotient_cmp(x,y) != LARGER; // <= 0
}

template <class NT>
CGAL_KERNEL_INLINE
bool
operator>(const Quotient<NT>& x, const Quotient<NT>& y)
{
  return  quotient_cmp(x,y) == LARGER; // > 0
}

template <class NT>
CGAL_KERNEL_INLINE
bool
operator>=(const Quotient<NT>& x, const Quotient<NT>& y)
{
  return quotient_cmp(x,y) != SMALLER; // >= 0
}
#endif // CGAL_NO_STL_PROVIDED_REL_OPS
#ifndef CGAL_NO_STL_PROVIDED_REL_OPS
template <class NT>
CGAL_KERNEL_INLINE
bool
operator!=(const Quotient<NT>& x, const NT& y)
{ return x.den * y != x.num; }

template <class NT>
CGAL_KERNEL_INLINE
bool
operator!=(const NT& x, const Quotient<NT>& y)
{ return y.den * x != y.num; }

template <class NT>
CGAL_KERNEL_INLINE
bool
operator<=(const Quotient<NT>& x, const NT& y)
{
  return quotient_cmp(x,Quotient<NT>(y)) != LARGER; // <= 0
}

template <class NT>
CGAL_KERNEL_INLINE
bool
operator<=(const NT& x, const Quotient<NT>& y)
{
  return quotient_cmp(Quotient<NT>(x),y) != LARGER; // <= 0
}

template <class NT>
CGAL_KERNEL_INLINE
bool
operator>(const Quotient<NT>& x, const NT& y)
{
  return  quotient_cmp(x,Quotient<NT>(y)) == LARGER; // > 0
}

template <class NT>
CGAL_KERNEL_INLINE
bool
operator>(const NT& x, const Quotient<NT>& y)
{
  return  quotient_cmp(Quotient<NT>(x),y) == LARGER; // > 0
}

template <class NT>
CGAL_KERNEL_INLINE
bool
operator>=(const Quotient<NT>& x, const NT& y)
{
  return quotient_cmp(x,Quotient<NT>(y)) != SMALLER; // >= 0
}

template <class NT>
CGAL_KERNEL_INLINE
bool
operator>=(const NT& x, const Quotient<NT>& y)
{
  return quotient_cmp(Quotient<NT>(x),y) != SMALLER; // >= 0
}
#endif // CGAL_NO_STL_PROVIDED_REL_OPS

template <class NT>
double
to_double(const Quotient<NT>& q)   /* TODO */
{
  if (q.num == NT(0) )
  {
      return 0;
  }

  double nd = CGAL::to_double( q.num );

  if (q.den == NT(1) )
  {
      return nd;
  }

  double dd = CGAL::to_double( q.den );

  if ( is_finite( q.den )&&(is_finite( q.num )) )
  {
      return nd/dd ;
  }
  if ( abs(q.num) > abs(q.den) )
  {
      NT  nt_div = q.num / q.den;
      double divd = CGAL::to_double(nt_div);
      if ( divd >= ldexp(1.0,53) )
      {
          return divd;
      }
  }
  if ( abs(q.num) < abs(q.den) )
  {
      return 1.0 / CGAL::to_double( NT(1) / q );
  }
  return nd/dd ;
}

template <class NT>
CGAL_KERNEL_INLINE
bool
is_valid(const Quotient<NT>& q)
{ return is_valid(q.num) && is_valid(q.den) ; }

template <class NT>
CGAL_KERNEL_INLINE
bool
is_finite(const Quotient<NT>& q)
{ return (is_finite(q.num))&&(is_finite(q.den)) ; }

template <class NT>
CGAL_KERNEL_INLINE
NT
denominator(const Quotient<NT>& q)
{ return q.den ; }

template <class NT>
CGAL_KERNEL_INLINE
NT
numerator(const Quotient<NT>& q)
{ return q.num ; }

template <class NT>
inline
Quotient_tag
number_type_tag(const Quotient<NT>& q)
{ return Quotient_tag(); }

template <class NT>
NT
gcd(const NT&, const NT&)
{ return NT(1); }

CGAL_END_NAMESPACE


#endif  // CGAL_QUOTIENT_C
