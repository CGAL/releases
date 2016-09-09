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

// Source: Vector_2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_VECTOR_2_H
#define CGAL_VECTOR_2_H


#include <CGAL/Point_2.h>
#include <CGAL/Direction_2.h>

#ifdef CGAL_VECTOR_WRAPPER
#include <CGAL/Vector_2_rft_wrapper.h>
#endif // CGAL_VECTOR_WRAPPER

template < class R >
class CGAL_Vector_2 : public R::Vector_2
{
#ifdef CGAL_WORKAROUND_001
friend CGAL_Vector_2<R> operator-(const CGAL_Point_2<R> &p,
                                  const CGAL_Origin &o);
#else
friend inline CGAL_Vector_2<R> operator-(const CGAL_Point_2<R> &p,
                                         const CGAL_Origin &o);
#endif  // CGAL_WORKAROUND_001

public:
  CGAL_Vector_2()
  {}

  CGAL_Vector_2(const CGAL_Vector_2<R> &v)
    : R::Vector_2((const R::Vector_2&)v)
  {}

  CGAL_Vector_2(const R::Vector_2 &v)
    : R::Vector_2(v)
  {}

  CGAL_Vector_2(const CGAL_Null_vector &v)
    : R::Vector_2(v)
  {}

  CGAL_Vector_2(const R::RT &x, const R::RT &y)
    : R::Vector_2(x,y)
  {}

  CGAL_Vector_2(const R::RT &x, const R::RT &y, const R::RT &w)
    : R::Vector_2(x,y,w)
  {}



  CGAL_Vector_2<R> &operator=(const CGAL_Vector_2<R> &v)
  {
    R::Vector_2::operator=(v);
    return *this;
  }

#ifdef CGAL_VECTOR_WRAPPER
  CGAL_Vector_2<R> &operator=(const CGAL__Vector_2_rft_wrapper<R> &wrapper)
  {
    R::Vector_2::operator=((const CGAL_Vector_2<R>&)wrapper);
    return *this;
  }

  bool operator==(const CGAL__Vector_2_rft_wrapper<R> &wrapper) const
  {
    return R::Vector_2::operator==((const CGAL_Vector_2<R>&)wrapper);
  }

  bool operator!=(const CGAL__Vector_2_rft_wrapper<R> &wrapper) const
  {
    return !(*this == (const CGAL_Vector_2<R>&)wrapper);
  }

#endif // CGAL_VECTOR_WRAPPER

  bool operator==(const CGAL_Vector_2<R> &v) const
  {
    return R::Vector_2::operator==(v);
  }

  bool operator!=(const CGAL_Vector_2<R> &v) const
  {
    return !(*this == v);
  }

  bool operator==(const CGAL_Null_vector &v) const
  {
    return R::Vector_2::operator==(v);
  }

  bool operator!=(const CGAL_Null_vector &v) const
  {
    return !(*this == v);
  }

  int  id() const
  {
    return (int) PTR ;
  }

  R::RT hx() const
  {
    return R::Vector_2::hx();
  }

  R::RT hy() const
  {
    return R::Vector_2::hy();
  }

  R::RT hw() const
  {
    return R::Vector_2::hw();
  }

  R::FT x() const
  {
    return R::Vector_2::x();
  }

  R::FT y() const
  {
    return R::Vector_2::y();
  }

  R::RT homogeneous(int i) const
  {
    return R::Vector_2::homogeneous(i);
  }

  R::FT cartesian(int i) const
  {
    return R::Vector_2::cartesian(i);
  }

  R::FT operator[](int i) const
  {
    return cartesian(i);
  }


  int dimension() const
  {
    return 2;
  }


  CGAL_Vector_2<R> operator+(const CGAL_Vector_2 &w) const
  {
    return (const R::Vector_2&)(*this) + (const R::Vector_2&)(w);
  }

  CGAL_Vector_2<R> operator-(const CGAL_Vector_2 &w) const
  {
    return (const R::Vector_2&)(*this) - (const R::Vector_2&)(w);
  }

  CGAL_Vector_2<R> operator-() const
  {
    return R::Vector_2::operator-();
  }

  R::FT operator*(const CGAL_Vector_2 &w) const
  {
    return (const R::Vector_2&)(*this) * (const R::Vector_2&)(w);
  }

#ifndef CGAL_VECTOR_WRAPPER
  CGAL_Vector_2<R> operator*(const R::RT &c) const
  {
    return c * (const R::Vector_2&)(*this);
  }


  CGAL_Vector_2<R> operator*(const CGAL_Quotient<R::RT> &q) const
  {
    return (q.numerator() * (const R::Vector_2&)(*this)) /
           q.denominator();
  }
#endif // CGAL_VECTOR_WRAPPER

  CGAL_Vector_2<R> operator/(const R::RT &c) const
  {
    return (const R::Vector_2&)(*this) / c;
  }

  CGAL_Direction_2<R> direction() const
  {
    return R::Vector_2::direction();
  }

  CGAL_Vector_2<R> perpendicular(const CGAL_Orientation &o) const
  {
    return R::Vector_2::perpendicular(o);
  }

  CGAL_Vector_2<R> transform(const CGAL_Aff_transformation_2<R> &t) const
  {
    return R::Vector_2::transform(t);
  }


private:
  CGAL_Vector_2(const CGAL_Point_2<R> &p)
    : R::Vector_2(p)
  {}

  CGAL_Vector_2(const CGAL_Direction_2<R> &d)
    : R::Vector_2(d)
  {}

};


template < class R >
CGAL_No_number_tag CGAL_number_type_tag(const CGAL_Vector_2<R> &)
{
  return CGAL_No_number_tag();
}
#ifdef CGAL_VECTOR_WRAPPER
template <class T, class R>
CGAL__Vector_2_rft_wrapper<R> CGAL_multiply(const CGAL_Quotient<T> &q,
                                           const CGAL_Vector_2<R> &w,
                                           const CGAL_Quotient_tag&)
{
  return CGAL__Vector_2_rft_wrapper<R>(
                 CGAL_Vector_2<R>((q.numerator() * (const R::Vector_2&)(w))
                                  / q.denominator()));
}

template < class R >
CGAL__Vector_2_rft_wrapper<R> CGAL_multiply(const CGAL_Vector_2<R> &v,
                                           const CGAL_Vector_2<R> &w,
                                           const CGAL_No_number_tag&)
{
  return CGAL__Vector_2_rft_wrapper<R>((const R::Vector_2&)(v)
                                      * (const R::Vector_2&)(w));
}

template < class T, class R >
CGAL__Vector_2_rft_wrapper<R> CGAL_multiply(const T &n,
                                           const CGAL_Vector_2<R> &w,
                                           const CGAL_Number_tag&)
{
  return CGAL__Vector_2_rft_wrapper<R>(
                 CGAL_Vector_2<R>(R::RT(n) * (const R::Vector_2&)(w)));
}

template <class T, class R>
CGAL__Vector_2_rft_wrapper<R> operator*(const T &t,
                                       const CGAL_Vector_2<R> &w)
{
  return CGAL_multiply(t, w, CGAL_number_type_tag(t));
}
#endif // CGAL_VECTOR_WRAPPER


#endif
