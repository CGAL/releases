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
// source        : Vector_2.fw
// file          : include/CGAL/Vector_2.h
// package       : _2 (2.1.2)
// revision      : 2.1.2
// revision_date : 09 May 1999 
// author(s)     : Andreas Fabri
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : cgal@cs.uu.nl
//
// ======================================================================
 

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

#ifdef VECTOR_WRAPPER
#ifndef VECTOR_2_RFT_WRAPPER_H
#include <CGAL/Vector_2_rft_wrapper.h>
#endif // VECTOR_2_RFT_WRAPPER_H
#endif // VECTOR_WRAPPER

CGAL_BEGIN_NAMESPACE

template <class T> class Quotient;
template <class _R>
class Vector_2 : public _R::Vector_2
{
public:
  typedef  _R   R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Vector_2              RVector_2;

friend inline
       Vector_2<R>
       operator- CGAL_NULL_TMPL_ARGS (const Point_2<R> &p,
                                      const Origin &o);

  Vector_2()
  {}

  Vector_2(const Vector_2<R> &v)
    : RVector_2((const RVector_2&)v)
  {}

  Vector_2(const RVector_2& v)
    : RVector_2(v)
  {}

  Vector_2(const Null_vector &v)
    : RVector_2(v)
  {}

  Vector_2(const RT &x, const RT &y)
    : RVector_2(x,y)
  {}

  Vector_2(const RT &x, const RT &y, const RT &w)
    : RVector_2(x,y,w)
  {}



  Vector_2<R> &operator=(const Vector_2<R> &v)
  {
    RVector_2::operator=(v);
    return *this;
  }

#ifdef VECTOR_WRAPPER
  Vector_2<R> &operator=(const _Vector_2_rft_wrapper<R> &wrapper)
  {
    RVector_2::operator=((const Vector_2<R>&)wrapper);
    return *this;
  }

  bool operator==(const _Vector_2_rft_wrapper<R> &wrapper) const
  {
    return RVector_2::operator==((const Vector_2<R>&)wrapper);
  }

  bool operator!=(const _Vector_2_rft_wrapper<R> &wrapper) const
  {
    return !(*this == (const Vector_2<R>&)wrapper);
  }

#endif // VECTOR_WRAPPER

  bool operator==(const Vector_2<R> &v) const
  {
    return RVector_2::operator==(v);
  }

  bool operator!=(const Vector_2<R> &v) const
  {
    return !(*this == v);
  }

  bool operator==(const Null_vector &v) const
  {
    return RVector_2::operator==(v);
  }

  bool operator!=(const Null_vector &v) const
  {
    return !(*this == v);
  }

  int  id() const
  {
    return (int) PTR ;
  }

  RT hx() const
  {
    return RVector_2::hx();
  }

  RT hy() const
  {
    return RVector_2::hy();
  }

  RT hw() const
  {
    return RVector_2::hw();
  }

  FT x() const
  {
    return RVector_2::x();
  }

  FT y() const
  {
    return RVector_2::y();
  }

  RT homogeneous(int i) const
  {
    return RVector_2::homogeneous(i);
  }

  FT cartesian(int i) const
  {
    return RVector_2::cartesian(i);
  }

  FT operator[](int i) const
  {
    return cartesian(i);
  }


  int dimension() const
  {
    return 2;
  }


  Vector_2<R> operator+(const Vector_2<R> &w) const
  {
    return (const RVector_2&)(*this) + (const RVector_2&)(w);
  }

  Vector_2<R> operator-(const Vector_2<R> &w) const
  {
    return (const RVector_2&)(*this) - (const RVector_2&)(w);
  }

  Vector_2<R> operator-() const
  {
    return RVector_2::operator-();
  }

  FT operator*(const Vector_2<R> &w) const
  {
    return (const RVector_2&)(*this) * (const RVector_2&)(w);
  }

#ifndef VECTOR_WRAPPER
  Vector_2<R> operator*(const RT &c) const
  {
    return c * (const RVector_2&)(*this);
  }


  Vector_2<R> operator*(const Quotient<RT> &q) const
  {
    return (q.numerator() * (const RVector_2&)(*this)) /
           q.denominator();
  }

  Vector_2<R> operator/(const Quotient<RT> &q) const
  {
    return (q.denominator() * (const RVector_2&)(*this)) /
           q.numerator();
  }
#endif // VECTOR_WRAPPER

  Vector_2<R> operator/(const RT &c) const
  {
    return (const RVector_2&)(*this) / c;
  }

  Direction_2<R> direction() const
  {
    return RVector_2::direction();
  }

  Vector_2<R> perpendicular(const Orientation &o) const
  {
    return RVector_2::perpendicular(o);
  }

  Vector_2<R> transform(const Aff_transformation_2<R> &t) const
  {
    return RVector_2::transform(t);
  }

private:
  Vector_2(const Point_2<R> &p)
    : RVector_2(p)
  {}

  Vector_2(const Direction_2<R> &d)
    : RVector_2(d)
  {}
};

template < class R >
No_number_tag
number_type_tag(const Vector_2<R> &)
{ return No_number_tag(); }
#ifdef VECTOR_WRAPPER
template <class T, class R>
_Vector_2_rft_wrapper<R>
multiply(const Quotient<T> &q,
              const Vector_2<R> &w,
              const Quotient_tag&)
{
  return _Vector_2_rft_wrapper<R>(
                 Vector_2<R>((q.numerator() * (const R::(RVector_2&))(w))
                                  / q.denominator()));
}

template < class R >
_Vector_2_rft_wrapper<R>
multiply(const Vector_2<R> &v,
              const Vector_2<R> &w,
              const No_number_tag&)
{
  return _Vector_2_rft_wrapper<R>((const R::(RVector_2&))(v)
                                     * (const R::(RVector_2&))(w));
}

template < class T, class R >
_Vector_2_rft_wrapper<R>
multiply(const T &n,
              const Vector_2<R> &w,
              const Number_tag&)
{
  return _Vector_2_rft_wrapper<R>(
                 Vector_2<R>(R::RT(n) * (const R::(RVector_2&))(w)));
}

template <class T, class R>
_Vector_2_rft_wrapper<R>
operator*(const T &t, const Vector_2<R> &w)
{
  return multiply(t, w, number_type_tag(t));
}
#endif // VECTOR_WRAPPER
#ifndef NO_OSTREAM_INSERT_VECTOR_2
template < class R >
std::ostream &
operator<<(std::ostream &os, const Vector_2<R> &v)
{
  typedef typename  R::Vector_2       RVector_2;
  return os << (const RVector_2&)v;
}
#endif // NO_OSTREAM_INSERT_VECTOR_2

#ifndef NO_ISTREAM_EXTRACT_VECTOR_2
template < class R >
std::istream &
operator>>(std::istream &is, Vector_2<R> &p)
{
  typedef typename  R::Vector_2       RVector_2;
  return is >> (RVector_2&)p;
}
#endif // NO_ISTREAM_EXTRACT_VECTOR_2

CGAL_END_NAMESPACE


#endif // CGAL_VECTOR_2_H
