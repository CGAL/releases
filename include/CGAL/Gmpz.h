// ======================================================================
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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-1.2
// release_date  : 1999, January 18
// 
// source        : Gmpz.fw
// file          : include/CGAL/Gmpz.h
// package       : Number_types (1.6)
// revision      : 1.6
// revision_date : 13 Jan 1999 
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
//
// email         : cgal@cs.uu.nl
//
// ======================================================================
 

#ifndef CGAL_GMPZ_H
#define CGAL_GMPZ_H


#include<CGAL/basic.h>
#include<gmp.h>

class CGAL_Gmpz_rep : public CGAL_Rep
{
public:
  mpz_t  mpZ;

  CGAL_Gmpz_rep()
  // { mpz_init_set_si(mpZ, 0); }
  { mpz_init(mpZ); }

  CGAL_Gmpz_rep(mpz_t  z)
  { mpz_init_set(mpZ, z); }

  CGAL_Gmpz_rep(int si)
  { mpz_init_set_si(mpZ, si); }

  CGAL_Gmpz_rep(long li)
  { mpz_init_set_si(mpZ, li); }

  CGAL_Gmpz_rep(unsigned long li)
  { mpz_init_set_ui(mpZ, li); }

  CGAL_Gmpz_rep(double d)
  { mpz_init_set_d(mpZ, d); }

  CGAL_Gmpz_rep(char* str)
  { mpz_init_set_str(mpZ, str, 10); }

  CGAL_Gmpz_rep(char* str, int base)
  { mpz_init_set_str(mpZ, str, base); }

  ~CGAL_Gmpz_rep()
  { mpz_clear(mpZ); }
};


class CGAL_Gmpz;

class CGAL_Gmpz : public CGAL_Handle
{
public:
  CGAL_Gmpz();

  CGAL_Gmpz(const CGAL_Gmpz &z);

  CGAL_Gmpz(mpz_t z);

  CGAL_Gmpz(int i);

  CGAL_Gmpz(long l);

  CGAL_Gmpz(unsigned long l);

  CGAL_Gmpz(double d);

  CGAL_Gmpz(char* str);
  CGAL_Gmpz(char* str, int base);

  CGAL_Gmpz(CGAL_Gmpz_rep* R);

  ~CGAL_Gmpz();

  CGAL_Gmpz &operator=(const CGAL_Gmpz &z);

  bool operator==(const CGAL_Gmpz &z) const;
  bool operator==(int i) const;

  bool operator!=(const CGAL_Gmpz &z) const;
  bool operator!=(int i) const;

  bool operator<(const CGAL_Gmpz &z) const;
  bool operator<(int i) const;

  bool operator<=(const CGAL_Gmpz &z) const;
  bool operator<=(int i) const;

  bool operator>(const CGAL_Gmpz &z) const;
  bool operator>(int i) const;

  bool operator>=(const CGAL_Gmpz &z) const;
  bool operator>=(int i) const;

  CGAL_Gmpz operator-() const;

  CGAL_Gmpz operator+(const CGAL_Gmpz &z) const;
  CGAL_Gmpz operator+(int i) const;

  CGAL_Gmpz operator-(const CGAL_Gmpz &z) const;
  CGAL_Gmpz operator-(int i) const;

  CGAL_Gmpz operator*(const CGAL_Gmpz &z) const;
  CGAL_Gmpz operator*(int i) const;

  CGAL_Gmpz operator/(const CGAL_Gmpz &z) const;
  CGAL_Gmpz operator/(int i) const;

  CGAL_Gmpz& operator+=(const CGAL_Gmpz &z);
  CGAL_Gmpz operator+=(int i);

  CGAL_Gmpz& operator-=(const CGAL_Gmpz &z);
  CGAL_Gmpz operator-=(int i);

  CGAL_Gmpz& operator*=(const CGAL_Gmpz &z);
  CGAL_Gmpz operator*=(int i);

  CGAL_Gmpz& operator/=(const CGAL_Gmpz &z);
  CGAL_Gmpz operator/=(int i);

  size_t approximate_decimal_length() const;

  CGAL_Gmpz_rep* ptr() const;
  double to_double() const;
  CGAL_Sign sign() const;
};


inline
CGAL_Gmpz_rep*
CGAL_Gmpz::ptr() const
{ return (CGAL_Gmpz_rep*) PTR; }

inline   // CGAL_KERNEL_CTOR_INLINE
CGAL_Gmpz::CGAL_Gmpz()
{ PTR = new CGAL_Gmpz_rep(0); }

inline   // CGAL_KERNEL_CTOR_INLINE
CGAL_Gmpz::CGAL_Gmpz(const CGAL_Gmpz &z)
  : CGAL_Handle((CGAL_Handle&)z)
{}

inline   // CGAL_KERNEL_CTOR_INLINE
CGAL_Gmpz::CGAL_Gmpz(mpz_t z)
{ cout << "OLD construction called"; PTR = new CGAL_Gmpz_rep(z); }

inline   // CGAL_KERNEL_CTOR_INLINE
CGAL_Gmpz::CGAL_Gmpz(int i)
{ PTR = new CGAL_Gmpz_rep(i); }

inline   // CGAL_KERNEL_CTOR_INLINE
CGAL_Gmpz::CGAL_Gmpz(long l)
{ PTR = new CGAL_Gmpz_rep(l); }

inline   // CGAL_KERNEL_CTOR_INLINE
CGAL_Gmpz::CGAL_Gmpz(unsigned long l)
{ PTR = new CGAL_Gmpz_rep(l); }

inline   // CGAL_KERNEL_CTOR_INLINE
CGAL_Gmpz::CGAL_Gmpz(double d)
{ PTR = new CGAL_Gmpz_rep(d); }

inline   // CGAL_KERNEL_CTOR_INLINE
CGAL_Gmpz::CGAL_Gmpz(char* str)
{ PTR = new CGAL_Gmpz_rep(str); }

inline   // CGAL_KERNEL_CTOR_INLINE
CGAL_Gmpz::CGAL_Gmpz(char* str, int base)
{ PTR = new CGAL_Gmpz_rep(str, base); }

inline   // CGAL_KERNEL_CTOR_INLINE
CGAL_Gmpz::CGAL_Gmpz(CGAL_Gmpz_rep* R)
{ PTR = R; }

inline
CGAL_Gmpz::~CGAL_Gmpz()
{}

inline
CGAL_Gmpz &
CGAL_Gmpz::operator=(const CGAL_Gmpz &z)
{
  CGAL_Handle::operator=(z);
  return *this;
}

inline
bool
CGAL_Gmpz::operator==(const CGAL_Gmpz &z) const
{ return ( mpz_cmp(ptr()->mpZ, z.ptr()->mpZ) == 0 ); }

inline
bool
CGAL_Gmpz::operator<(const CGAL_Gmpz &z) const
{ return ( mpz_cmp(ptr()->mpZ, z.ptr()->mpZ) < 0 ); }

inline
bool
CGAL_Gmpz::operator<(int i) const
{ return ( mpz_cmp_si(ptr()->mpZ, i) < 0 ); }

inline
bool            /* XXX */
CGAL_Gmpz::operator<=(const CGAL_Gmpz &z) const
{ return ( mpz_cmp(ptr()->mpZ, z.ptr()->mpZ) <= 0 ); }


inline
bool
CGAL_Gmpz::operator<=(int i) const
{ return ( mpz_cmp_si(ptr()->mpZ, i) <= 0 ); }

inline
bool             /* XXX */
CGAL_Gmpz::operator>(const CGAL_Gmpz &z) const
{ return ( mpz_cmp(ptr()->mpZ, z.ptr()->mpZ) > 0 ); }

inline
bool
CGAL_Gmpz::operator>(int i) const
{ return ( mpz_cmp_si(ptr()->mpZ, i) > 0 ); }

inline
bool             /* XXX */
CGAL_Gmpz::operator>=(const CGAL_Gmpz &z) const
{ return ( mpz_cmp(ptr()->mpZ, z.ptr()->mpZ) >= 0 ); }

inline
bool
CGAL_Gmpz::operator>=(int i) const
{ return ( mpz_cmp_si(ptr()->mpZ, i) >= 0 ); }

inline
bool             /* XXX */
CGAL_Gmpz::operator!=(const CGAL_Gmpz &z) const
{ return ! (*this == z); }

inline
bool
CGAL_Gmpz::operator==(int i) const
{ return ( mpz_cmp_si(ptr()->mpZ, i) == 0 ); }

inline
bool
CGAL_Gmpz::operator!=(int i) const
{ return ! (*this == i); }

inline
CGAL_Gmpz
CGAL_Gmpz::operator-() const
{
    CGAL_Gmpz_rep* Res = new CGAL_Gmpz_rep();
    mpz_neg(Res->mpZ, ptr()->mpZ);
    return CGAL_Gmpz(Res);
}

inline
CGAL_Gmpz
CGAL_Gmpz::operator+(const CGAL_Gmpz &z) const
{
    CGAL_Gmpz_rep* Res = new CGAL_Gmpz_rep();
    mpz_add(Res->mpZ, ptr()->mpZ, z.ptr()->mpZ);
    return CGAL_Gmpz(Res);
}

inline
CGAL_Gmpz
CGAL_Gmpz::operator+(int i) const
{
    if (i>0)
    {
        CGAL_Gmpz_rep* Res = new CGAL_Gmpz_rep();
        mpz_add_ui(Res->mpZ, ptr()->mpZ, i);
        return CGAL_Gmpz(Res);
    }
    return *this + CGAL_Gmpz(i);
}

inline
CGAL_Gmpz&
CGAL_Gmpz::operator+=(const CGAL_Gmpz &z)
{
    *this = *this + z;
    return *this;
}

inline
CGAL_Gmpz
CGAL_Gmpz::operator+=(int i)
{
    *this = *this + CGAL_Gmpz(i);
    return *this;
}

inline
CGAL_Gmpz
CGAL_Gmpz::operator-(const CGAL_Gmpz &z) const
{
    CGAL_Gmpz_rep* Res = new CGAL_Gmpz_rep();
    mpz_sub(Res->mpZ, ptr()->mpZ, z.ptr()->mpZ);
    return CGAL_Gmpz(Res);
}

inline
CGAL_Gmpz CGAL_Gmpz::operator-(int i) const
{
    if (i>0)
    {
        CGAL_Gmpz_rep* Res = new CGAL_Gmpz_rep();
        mpz_sub_ui(Res->mpZ, ptr()->mpZ, i);
        return CGAL_Gmpz(Res);
    }
    return *this - CGAL_Gmpz(i);
}

inline
CGAL_Gmpz&
CGAL_Gmpz::operator-=(const CGAL_Gmpz &z)
{
    *this = *this - z;
    return *this;
}

inline
CGAL_Gmpz
CGAL_Gmpz::operator-=(int i)
{
    *this = *this - CGAL_Gmpz(i);
    return *this;
}

inline
CGAL_Gmpz
CGAL_Gmpz::operator*(const CGAL_Gmpz &z) const
{
    CGAL_Gmpz_rep* Res = new CGAL_Gmpz_rep();
    mpz_mul(Res->mpZ, ptr()->mpZ, z.ptr()->mpZ);
    return CGAL_Gmpz(Res);
}

inline
CGAL_Gmpz
CGAL_Gmpz::operator*(int i) const
{
    if (i>0)
    {
        CGAL_Gmpz_rep* Res = new CGAL_Gmpz_rep();
        mpz_mul_ui(Res->mpZ, ptr()->mpZ, i);
        return CGAL_Gmpz(Res);
    }
    return *this * CGAL_Gmpz(i);
}

inline
CGAL_Gmpz&
CGAL_Gmpz::operator*=(const CGAL_Gmpz &z)
{
    *this = *this * z;
    return *this;
}

inline
CGAL_Gmpz
CGAL_Gmpz::operator*=(int i)
{
    *this = *this * CGAL_Gmpz(i);
    return *this;
}

inline
CGAL_Gmpz
CGAL_Gmpz::operator/(const CGAL_Gmpz &z) const
{
    CGAL_Gmpz_rep* Res = new CGAL_Gmpz_rep();
    mpz_tdiv_q(Res->mpZ, ptr()->mpZ, z.ptr()->mpZ);
    return CGAL_Gmpz(Res);
}

inline
CGAL_Gmpz
CGAL_Gmpz::operator/(int i) const
{
    if (i>0)
    {
        CGAL_Gmpz_rep* Res = new CGAL_Gmpz_rep();
        mpz_tdiv_q_ui(Res->mpZ, ptr()->mpZ, i);
        return CGAL_Gmpz(Res);
    }
    return *this / CGAL_Gmpz(i);
}

inline
CGAL_Gmpz&
CGAL_Gmpz::operator/=(const CGAL_Gmpz &z)
{
    *this = *this / z;
    return *this;
}

inline
CGAL_Gmpz
CGAL_Gmpz::operator/=(int i)
{
    *this = *this / CGAL_Gmpz(i);
    return *this;
}

inline
double
CGAL_Gmpz::to_double() const
{ return mpz_get_d(ptr()->mpZ); }

inline
CGAL_io_Operator
CGAL_io_tag(const CGAL_Gmpz&)
{ return CGAL_io_Operator(); }

inline
CGAL_Sign
CGAL_Gmpz::sign() const
{ return (CGAL_Sign)mpz_sgn(ptr()->mpZ); }

inline
CGAL_Gmpz
operator+(int i, const CGAL_Gmpz &z)
{ return z + i; }

inline
CGAL_Gmpz
operator-(int i, const CGAL_Gmpz &z)
{ return CGAL_Gmpz(i) - z; }

inline
CGAL_Gmpz
operator*(int i, const CGAL_Gmpz &z)
{ return z * i; }

inline
double
CGAL_to_double(const CGAL_Gmpz &z)
{ return z.to_double(); }

inline
CGAL_Number_tag
CGAL_number_type_tag(const CGAL_Gmpz& )
{ return CGAL_Number_tag(); }

inline
CGAL_Sign
CGAL_sign(const CGAL_Gmpz &z)
{ return z.sign(); }

inline
bool
CGAL_is_valid(const CGAL_Gmpz &)
{ return true; }

inline
bool
CGAL_is_finite(const CGAL_Gmpz &)
{ return true; }

inline
CGAL_Gmpz
CGAL_sqrt(const CGAL_Gmpz &z)
{
  CGAL_Gmpz_rep* Res = new CGAL_Gmpz_rep();
  mpz_sqrt(Res->mpZ, z.ptr()->mpZ);
  return CGAL_Gmpz(Res);
}

inline
CGAL_Gmpz
CGAL_gcd(const CGAL_Gmpz &z1, const CGAL_Gmpz &z2)
{
  CGAL_Gmpz_rep* Res = new CGAL_Gmpz_rep();
  mpz_gcd(Res->mpZ, z1.ptr()->mpZ, z2.ptr()->mpZ);
  return CGAL_Gmpz(Res);
}

inline
CGAL_Gmpz
CGAL_gcd(const CGAL_Gmpz &z, int i)
{
  if (i > 0)
  {
      CGAL_Gmpz_rep* Res = new CGAL_Gmpz_rep();
      mpz_gcd_ui(Res->mpZ, z.ptr()->mpZ, i);
      return CGAL_Gmpz(Res);
  }
  return CGAL_gcd(z, CGAL_Gmpz(i));
}

inline
CGAL_Gmpz
CGAL_exact_division(const CGAL_Gmpz &z1,
                    const CGAL_Gmpz &z2)
{
  CGAL_Gmpz_rep* Res = new CGAL_Gmpz_rep();
  mpz_divexact(Res->mpZ, z1.ptr()->mpZ, z2.ptr()->mpZ);
#ifdef CGAL_CHECK_POSTCONDITIONS
  mpz_t prod;
  mpz_init(prod);
  mpz_mul(prod, Res->mpZ, z2.ptr()->mpZ);
  CGAL_kernel_postcondition_msg(mpz_cmp(prod, z1.ptr()->mpZ) == 0,
                                "CGAL_exact_division failed\n");
  mpz_clear( prod);
#endif // CGAL_CHECK_POSTCONDITIONS
  return CGAL_Gmpz(Res);
}

inline
size_t
CGAL_Gmpz::approximate_decimal_length() const
{ return mpz_sizeinbase(ptr()->mpZ,10); }

inline
ostream&
operator<<(ostream& os, const CGAL_Gmpz &z)
{
  char *str = new char [mpz_sizeinbase(z.ptr()->mpZ,10) + 2];
  str = mpz_get_str(str, 10, z.ptr()->mpZ);
  os << str ;
  delete str;
  return os;
}

inline
istream&
operator>>(istream& is, CGAL_Gmpz &z)
{
  int negative = 0;
  const int null = '0';
  char c;

  while (is.get(c) && isspace(c))
  {}

  if (c == '-')
  {
        negative = 1;
        while (is.get(c) && isspace(c))
        {}
  }
  if (isdigit(c))
  {
        z = c - '0';
        while (is.get(c) && isdigit(c))
        {
            z = 10*z + (c-null);
        }
  }
  if (is)
  {
        is.putback(c);
  }
  if (CGAL_sign(z) != (CGAL_Sign)0 && negative)
  {
        z = -z;
  }
  return is;
}

#ifdef CGAL_INTERVAL_ARITHMETIC_H
#include <CGAL/Interval_arithmetic/IA_Gmpz.h>
#endif // CGAL_INTERVAL_ARITHMETIC_H

#endif // CGAL_GMPZ_H
