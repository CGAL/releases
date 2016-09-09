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
// file          : include/CGAL/Vector_2.h
// author(s)     : Andreas Fabri
//
// email         : cgal@cs.uu.nl
//
// ============================================================================
 

#ifndef CGAL_VECTOR_2_H
#define CGAL_VECTOR_2_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifndef CGAL_POINT_2_H
#include <CGAL/Point_2.h>
#endif // CGAL_POINT_2_H
#ifndef CGAL_DIRECTION_2_H
#include <CGAL/Direction_2.h>
#endif // CGAL_DIRECTION_2_H

#ifdef CGAL_VECTOR_WRAPPER
#ifndef CGAL_VECTOR_2_RFT_WRAPPER_H
#include <CGAL/Vector_2_rft_wrapper.h>
#endif // CGAL_VECTOR_2_RFT_WRAPPER_H
#endif // CGAL_VECTOR_WRAPPER

template <class _R>
class CGAL_Vector_2 : public _R::Vector_2
{
public:
  typedef  _R   R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Vector_2              Vector_2;

friend CGAL_Vector_2<R>
       operator- CGAL_NULL_TMPL_ARGS (const CGAL_Point_2<R> &p,
                                      const CGAL_Origin &o);

  CGAL_Vector_2()
  {}

  CGAL_Vector_2(const CGAL_Vector_2<R> &v)
    : Vector_2((const Vector_2&)v)
  {}

  CGAL_Vector_2(const Vector_2 &v)
    : Vector_2(v)
  {}

  CGAL_Vector_2(const CGAL_Null_vector &v)
    : Vector_2(v)
  {}

  CGAL_Vector_2(const RT &x, const RT &y)
    : Vector_2(x,y)
  {}

  CGAL_Vector_2(const RT &x, const RT &y, const RT &w)
    : Vector_2(x,y,w)
  {}



  CGAL_Vector_2<R> &operator=(const CGAL_Vector_2<R> &v)
  {
    Vector_2::operator=(v);
    return *this;
  }

#ifdef CGAL_VECTOR_WRAPPER
  CGAL_Vector_2<R> &operator=(const CGAL__Vector_2_rft_wrapper<R> &wrapper)
  {
    Vector_2::operator=((const CGAL_Vector_2<R>&)wrapper);
    return *this;
  }

  bool operator==(const CGAL__Vector_2_rft_wrapper<R> &wrapper) const
  {
    return Vector_2::operator==((const CGAL_Vector_2<R>&)wrapper);
  }

  bool operator!=(const CGAL__Vector_2_rft_wrapper<R> &wrapper) const
  {
    return !(*this == (const CGAL_Vector_2<R>&)wrapper);
  }

#endif // CGAL_VECTOR_WRAPPER

  bool operator==(const CGAL_Vector_2<R> &v) const
  {
    return Vector_2::operator==(v);
  }

  bool operator!=(const CGAL_Vector_2<R> &v) const
  {
    return !(*this == v);
  }

  bool operator==(const CGAL_Null_vector &v) const
  {
    return Vector_2::operator==(v);
  }

  bool operator!=(const CGAL_Null_vector &v) const
  {
    return !(*this == v);
  }

  int  id() const
  {
    return (int) PTR ;
  }

  RT hx() const
  {
    return Vector_2::hx();
  }

  RT hy() const
  {
    return Vector_2::hy();
  }

  RT hw() const
  {
    return Vector_2::hw();
  }

  FT x() const
  {
    return Vector_2::x();
  }

  FT y() const
  {
    return Vector_2::y();
  }

  RT homogeneous(int i) const
  {
    return Vector_2::homogeneous(i);
  }

  FT cartesian(int i) const
  {
    return Vector_2::cartesian(i);
  }

  FT operator[](int i) const
  {
    return cartesian(i);
  }


  int dimension() const
  {
    return 2;
  }


  CGAL_Vector_2<R> operator+(const CGAL_Vector_2<R> &w) const
  {
    return (const Vector_2&)(*this) + (const Vector_2&)(w);
  }

  CGAL_Vector_2<R> operator-(const CGAL_Vector_2<R> &w) const
  {
    return (const Vector_2&)(*this) - (const Vector_2&)(w);
  }

  CGAL_Vector_2<R> operator-() const
  {
    return Vector_2::operator-();
  }

  FT operator*(const CGAL_Vector_2<R> &w) const
  {
    return (const Vector_2&)(*this) * (const Vector_2&)(w);
  }

#ifndef CGAL_VECTOR_WRAPPER
  CGAL_Vector_2<R> operator*(const RT &c) const
  {
    return c * (const Vector_2&)(*this);
  }


  CGAL_Vector_2<R> operator*(const CGAL_Quotient<RT> &q) const
  {
    return (q.numerator() * (const Vector_2&)(*this)) /
           q.denominator();
  }

  CGAL_Vector_2<R> operator/(const CGAL_Quotient<RT> &q) const
  {
    return (q.denominator() * (const Vector_2&)(*this)) /
           q.numerator();
  }
#endif // CGAL_VECTOR_WRAPPER

  CGAL_Vector_2<R> operator/(const RT &c) const
  {
    return (const Vector_2&)(*this) / c;
  }

  CGAL_Direction_2<R> direction() const
  {
    return Vector_2::direction();
  }

  CGAL_Vector_2<R> perpendicular(const CGAL_Orientation &o) const
  {
    return Vector_2::perpendicular(o);
  }

  CGAL_Vector_2<R> transform(const CGAL_Aff_transformation_2<R> &t) const
  {
    return Vector_2::transform(t);
  }

private:
  CGAL_Vector_2(const CGAL_Point_2<R> &p)
    : Vector_2(p)
  {}

  CGAL_Vector_2(const CGAL_Direction_2<R> &d)
    : Vector_2(d)
  {}
};

template < class R >
CGAL_No_number_tag
CGAL_number_type_tag(const CGAL_Vector_2<R> &)
{ return CGAL_No_number_tag(); }
#ifdef CGAL_VECTOR_WRAPPER
template <class T, class R>
CGAL__Vector_2_rft_wrapper<R>
CGAL_multiply(const CGAL_Quotient<T> &q,
              const CGAL_Vector_2<R> &w,
              const CGAL_Quotient_tag&)
{
  return CGAL__Vector_2_rft_wrapper<R>(
                 CGAL_Vector_2<R>((q.numerator() * (const R::Vector_2&)(w))
                                  / q.denominator()));
}

template < class R >
CGAL__Vector_2_rft_wrapper<R>
CGAL_multiply(const CGAL_Vector_2<R> &v,
              const CGAL_Vector_2<R> &w,
              const CGAL_No_number_tag&)
{
  return CGAL__Vector_2_rft_wrapper<R>((const R::Vector_2&)(v)
                                     * (const R::Vector_2&)(w));
}

template < class T, class R >
CGAL__Vector_2_rft_wrapper<R>
CGAL_multiply(const T &n,
              const CGAL_Vector_2<R> &w,
              const CGAL_Number_tag&)
{
  return CGAL__Vector_2_rft_wrapper<R>(
                 CGAL_Vector_2<R>(R::RT(n) * (const R::Vector_2&)(w)));
}

template <class T, class R>
CGAL__Vector_2_rft_wrapper<R>
operator*(const T &t, const CGAL_Vector_2<R> &w)
{
  return CGAL_multiply(t, w, CGAL_number_type_tag(t));
}
#endif // CGAL_VECTOR_WRAPPER
#ifndef CGAL_NO_OSTREAM_INSERT_VECTOR_2
template < class R >
ostream &
operator<<(ostream &os, const CGAL_Vector_2<R> &v)
{
  typedef typename  R::Vector_2       Vector_2;
  return os << (const Vector_2&)v;
}
#endif // CGAL_NO_OSTREAM_INSERT_VECTOR_2

#ifndef CGAL_NO_ISTREAM_EXTRACT_VECTOR_2
template < class R >
istream &
operator>>(istream &is, CGAL_Vector_2<R> &p)
{
  typedef typename  R::Vector_2       Vector_2;
  return is >> (Vector_2&)p;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_VECTOR_2


#endif
