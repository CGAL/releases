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


// Source: Z.h
// Author: Andreas Fabri

#ifndef CGAL_Z_H
#define CGAL_Z_H


#include<CGAL/_Z.h>

class CGAL_Z;

class CGAL_Z : public CGAL_Handle
{
public:
  CGAL_Z();


  CGAL_Z(const CGAL_Z &z);

  CGAL_Z(mpz_t z);


  CGAL_Z(int i);

  CGAL_Z(double d);

  CGAL_Z(char* str);
  CGAL_Z(char* str, int base);

  ~CGAL_Z();

  CGAL_Z &operator=(const CGAL_Z &z);

  bool operator==(const CGAL_Z &z) const;
  bool operator==(int i) const;

  bool operator!=(const CGAL_Z &z) const;
  bool operator!=(int i) const;

  bool operator<(const CGAL_Z &z) const;
  bool operator<(int i) const;

  bool operator<=(const CGAL_Z &z) const;
  bool operator<=(int i) const;

  bool operator>(const CGAL_Z &z) const;
  bool operator>(int i) const;

  bool operator>=(const CGAL_Z &z) const;
  bool operator>=(int i) const;

  CGAL_Z operator-() const;

  CGAL_Z operator+(const CGAL_Z &z) const;
  CGAL_Z operator+(int i) const;

  CGAL_Z operator-(const CGAL_Z &z) const;
  CGAL_Z operator-(int i) const;

  CGAL_Z operator*(const CGAL_Z &z) const;
  CGAL_Z operator*(int i) const;

  CGAL_Z operator/(const CGAL_Z &z) const;
  CGAL_Z operator/(int i) const;

  CGAL__Z* ptr() const;
  double to_double() const;
  int sign() const;

};


inline  CGAL__Z* CGAL_Z::ptr() const
  {
    return (CGAL__Z*) PTR;
  }


inline CGAL_Z::CGAL_Z()
  {
    PTR = new CGAL__Z();
  }

inline CGAL_Z::CGAL_Z(const CGAL_Z &z)
  : CGAL_Handle((CGAL_Handle&)z)
  {}

inline CGAL_Z::CGAL_Z(mpz_t z)
  {
    PTR = new CGAL__Z(z);
  }

inline CGAL_Z::CGAL_Z(int i)
  {
    PTR = new CGAL__Z(i);
  }

inline CGAL_Z::CGAL_Z(double d)
  {
    PTR = new CGAL__Z(d);
  }

inline CGAL_Z::CGAL_Z(char* str)
  {
    PTR = new CGAL__Z(str);
  }

inline CGAL_Z::CGAL_Z(char* str, int base)
  {
    PTR = new CGAL__Z(str, base);
  }

inline CGAL_Z::~CGAL_Z()
  {}

inline CGAL_Z &CGAL_Z::operator=(const CGAL_Z &z)
  {
    CGAL_Handle::operator=(z);
    return *this;
  }

inline  bool CGAL_Z::operator==(const CGAL_Z &z) const
  {
    return ( mpz_cmp(ptr()->mpZ, z.ptr()->mpZ) == 0 );
  }


inline  bool CGAL_Z::operator<(const CGAL_Z &z) const
  {
    return ( mpz_cmp(ptr()->mpZ, z.ptr()->mpZ) < 0 );
  }


inline  bool CGAL_Z::operator<(int i) const
  {
    return ( mpz_cmp_si(ptr()->mpZ, i) < 0 );
  }


inline  bool CGAL_Z::operator<=(const CGAL_Z &z) const
  {
    return ( mpz_cmp(ptr()->mpZ, z.ptr()->mpZ) <= 0 );
  }


inline  bool CGAL_Z::operator<=(int i) const
  {
    return ( mpz_cmp_si(ptr()->mpZ, i) <= 0 );
  }

inline  bool CGAL_Z::operator>(const CGAL_Z &z) const
  {
    return ( mpz_cmp(ptr()->mpZ, z.ptr()->mpZ) > 0 );
  }

inline  bool CGAL_Z::operator>(int i) const
  {
    return ( mpz_cmp_si(ptr()->mpZ, i) > 0 );
  }


inline  bool CGAL_Z::operator>=(const CGAL_Z &z) const
  {
    return ( mpz_cmp(ptr()->mpZ, z.ptr()->mpZ) >= 0 );
  }


inline  bool CGAL_Z::operator>=(int i) const
  {
    return ( mpz_cmp_si(ptr()->mpZ, i) >= 0 );
  }

inline  bool CGAL_Z::operator!=(const CGAL_Z &z) const
  {
    return ! (*this == z);
  }

inline  bool CGAL_Z::operator==(int i) const
  {
    return ( mpz_cmp_si(ptr()->mpZ, i) == 0 );
  }

inline  bool CGAL_Z::operator!=(int i) const
  {
    return ! (*this == i);
  }


inline  CGAL_Z CGAL_Z::operator-() const
  {
    mpz_t res;
    mpz_init(res);
    mpz_neg(res, ptr()->mpZ);
    return CGAL_Z(res);
  }

inline  CGAL_Z CGAL_Z::operator+(const CGAL_Z &z) const
  {
    mpz_t res;
    mpz_init(res);
    mpz_add(res, ptr()->mpZ, z.ptr()->mpZ);
    return CGAL_Z(res);
  }

inline  CGAL_Z CGAL_Z::operator+(int i) const
  {
    if (i>0) {
      mpz_t res;
      mpz_init(res);
      mpz_add_ui(res, ptr()->mpZ, i);
      return CGAL_Z(res);
    }
    return *this + CGAL_Z(i);
  }


inline  CGAL_Z CGAL_Z::operator-(const CGAL_Z &z) const
  {
    mpz_t res;
    mpz_init(res);
    mpz_sub(res, ptr()->mpZ, z.ptr()->mpZ);
    return CGAL_Z(res);
  }

inline  CGAL_Z CGAL_Z::operator-(int i) const
  {
    if (i>0) {
      mpz_t res;
      mpz_init(res);
      mpz_sub_ui(res, ptr()->mpZ, i);
      return CGAL_Z(res);
    }
    return *this - CGAL_Z(i);
  }

inline  CGAL_Z CGAL_Z::operator*(const CGAL_Z &z) const
  {
    mpz_t res;
    mpz_init(res);
    mpz_mul(res, ptr()->mpZ, z.ptr()->mpZ);
    return CGAL_Z(res);
  }

inline  CGAL_Z CGAL_Z::operator*(int i) const
  {
    if (i>0) {
      mpz_t res;
      mpz_init(res);
      mpz_mul_ui(res, ptr()->mpZ, i);
      return CGAL_Z(res);
    }
    return *this * CGAL_Z(i);
  }

inline CGAL_Z CGAL_Z::operator/(const CGAL_Z &z) const
  {
    mpz_t res;
    mpz_init(res);
    mpz_tdiv_q(res, ptr()->mpZ, z.ptr()->mpZ);
    return CGAL_Z(res);
  }

inline CGAL_Z CGAL_Z::operator/(int i) const
  {
    if (i>0) {
      mpz_t res;
      mpz_init(res);
      mpz_tdiv_q_ui(res, ptr()->mpZ, i);
      return CGAL_Z(res);
    }
    return *this / CGAL_Z(i);
  }


inline  double CGAL_Z::to_double() const
  {
    return mpz_get_d(ptr()->mpZ);
  }

inline  int CGAL_Z::sign() const
  {
    return mpz_sgn(ptr()->mpZ);
  }



inline CGAL_Z operator+(int i, const CGAL_Z &z)
  {
    return z + i;
  }

inline CGAL_Z operator-(int i, const CGAL_Z &z)
  {
    return CGAL_Z(i) - z;
  }

inline CGAL_Z operator*(int i, const CGAL_Z &z)
  {
    return z * i;
  }

inline double CGAL_to_double(const CGAL_Z &z)
{
  return z.to_double();
}

inline int CGAL_sign(const CGAL_Z &z)
{
  return z.sign();
}

inline bool CGAL_is_valid(const CGAL_Z &)
{
  return true;
}

inline bool CGAL_is_finite(const CGAL_Z &)
{
  return true;
}

inline
CGAL_Number_tag
CGAL_number_type_tag(const CGAL_Z &z)
{
  return CGAL_Number_tag();
}

/*
inline
CGAL_io_Operator
CGAL_io_tag(const CGAL_Z &)
{
  return CGAL_io_Operator(); 
}
*/

inline CGAL_Z CGAL_sqrt(const CGAL_Z &z)
{
  mpz_t res;
  mpz_init(res);
  mpz_sqrt(res, z.ptr()->mpZ);
  return CGAL_Z(res);
}

inline CGAL_Z CGAL_gcd(const CGAL_Z &z1, const CGAL_Z &z2)
{
  mpz_t res;
  mpz_init(res);
  mpz_gcd(res, z1.ptr()->mpZ, z2.ptr()->mpZ);
  return CGAL_Z(res);
}

inline CGAL_Z CGAL_gcd(const CGAL_Z &z, int i)
{
  if (i > 0) {
    mpz_t res;
    mpz_init(res);
    mpz_gcd_ui(res, z.ptr()->mpZ, i);
    return CGAL_Z(res);
  }
  return CGAL_gcd(z, CGAL_Z(i));
}

inline CGAL_Z CGAL_exact_division(const CGAL_Z &z1, const CGAL_Z &z2)
{
  mpz_t res;
  mpz_init(res);
  mpz_divexact(res, z1.ptr()->mpZ, z2.ptr()->mpZ);
#ifdef CGAL_CHECK_POSTCONDITIONS
  mpz_t prod;
  mpz_init(prod);
  mpz_mul(prod, res, z2.ptr()->mpZ);
  CGAL_kernel_postcondition_msg(mpz_cmp(prod, z1.ptr()->mpZ) == 0,
                                "CGAL_exact_division failed\n");
#endif // CGAL_CHECK_POSTCONDITIONS
  return CGAL_Z(res);
}


#endif // CGAL_Z_H
