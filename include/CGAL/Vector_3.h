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
// source        : Vector_3.fw
// file          : include/CGAL/Vector_3.h
// package       : _3 (2.1.2)
// revision      : 2.1.2
// revision_date : 21 May 1999 
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : cgal@cs.uu.nl
//
// ======================================================================
 

#ifndef CGAL_VECTOR_3_H
#define CGAL_VECTOR_3_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifndef CGAL_POINT_3_H
#include <CGAL/Point_3.h>
#endif // CGAL_POINT_3_H
#ifndef CGAL_DIRECTION_3_H
#include <CGAL/Direction_3.h>
#endif // CGAL_DIRECTION_3_H

#ifdef VECTOR_WRAPPER
#ifndef VECTOR_3_RFT_WRAPPER_H
#include <CGAL/Vector_3_rft_wrapper.h>
#endif // VECTOR_3_RFT_WRAPPER_H
#endif // VECTOR_WRAPPER

CGAL_BEGIN_NAMESPACE

template <class T> class Quotient;
template <class _R>
class Vector_3 : public _R::Vector_3
{
public:
  typedef          _R                       R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Vector_3              RVector_3;

// #ifdef WORKAROUND_001
friend Vector_3<R>
       inline
       operator- CGAL_NULL_TMPL_ARGS (const Point_3<R>& p,
                                      const Origin& o);

friend Vector_3<R>
       Direction_3<R>::vector() const;
/*
#else
friend inline Vector_3<R> operator-(const Point_3<R>& p,
                                         const Origin& o);

//friend inline Vector_3<R> Direction_3<R>::vector() const;
friend class Direction_3<R>;
#endif  // WORKAROUND_001
*/

  Vector_3()
  {}
  Vector_3(const Vector_3<R>& v)
    : RVector_3( (const RVector_3& )v )
  {}
  Vector_3(const RVector_3&  v) : RVector_3(v)
  {}
  Vector_3(const Null_vector& v) : RVector_3(v)
  {}
  Vector_3(const RT& x, const RT& y, const RT& z)
    : RVector_3(x, y, z)
  {}
  Vector_3(const RT& x, const RT& y, const RT& z, const RT& w)
    : RVector_3(x, y, z, w)
  {}

  Vector_3<R>& operator=(const Vector_3<R>& v)
  {
    RVector_3::operator=(v);
    return *this;
  }
  bool operator==(const Vector_3<R>& v) const
  { return RVector_3::operator==(v); }
  bool operator!=(const Vector_3<R>& v) const
  { return !(*this == v); }
  bool operator==(const Null_vector& v) const
  { return RVector_3::operator==(v); }
  bool operator!=(const Null_vector& v) const
  { return !(*this == v); }
  int id() const    /* XXX */
  { return (int) PTR ; }
  RT hx() const
  { return RVector_3::hx(); }
  RT hy() const
  { return RVector_3::hy(); }
  RT hz() const
  { return RVector_3::hz(); }
  RT hw() const
  { return RVector_3::hw(); }
  FT x() const
  { return RVector_3::x(); }
  FT y() const
  { return RVector_3::y(); }
  FT z() const
  { return RVector_3::z(); }
  RT homogeneous(int i) const
  { return RVector_3::homogeneous(i); }
  FT cartesian(int i) const
  { return RVector_3::cartesian(i); }
  FT operator[](int i) const
  { return cartesian(i); }
  int dimension() const
  { return 3; }
  Vector_3<R> operator+(const Vector_3<R>& w) const
  { return (const RVector_3& )(*this) + (const RVector_3& )(w); }
  Vector_3<R> operator-(const Vector_3<R>& w) const
  { return (const RVector_3& )(*this) - (const RVector_3& )(w); }
  Vector_3<R> operator-() const
  { return RVector_3::operator-(); }
  FT operator*(const Vector_3<R>& w) const
  { return (const RVector_3& )(*this) * (const RVector_3& )(w); }

#ifndef VECTOR_WRAPPER
  Vector_3<R> operator*(const RT& c) const
  { return c * (const RVector_3& )(*this) ; }
  Vector_3<R> operator*(const Quotient<RT>& q) const
  {
    return (q.numerator() * (const RVector_3& )(*this)) /
            q.denominator();
  }
  Vector_3<R> operator/(const Quotient<RT>& q) const
  {
    return (q.denominator() * (const RVector_3& )(*this)) /
            q.numerator();
  }
#endif // VECTOR_WRAPPER

  Vector_3<R> operator/(const RT& c) const
  { return (const RVector_3& )(*this) / c; }
  Direction_3<R> direction() const
  { return RVector_3::direction(); }
  Vector_3<R> transform(const Aff_transformation_3<R>& t) const
  { return RVector_3::transform(t); }

private:
  Vector_3(const Point_3<R>& p) : RVector_3(p)
  {}
  Vector_3(const Direction_3<R>& d) : RVector_3(d)
  {}
};

template < class R >
No_number_tag number_type_tag(const Vector_3<R>& )
{
  return No_number_tag();
}

#ifdef VECTOR_WRAPPER
template <class T, class R>
_Vector_3_rft_wrapper<R>
multiply(const Quotient<T>& q,
              const Vector_3<R>& w,
              const Quotient_tag&)
{
  typedef typename  R::Vector_3       RVector_3;
  return _Vector_3_rft_wrapper<R>(
                 Vector_3<R>((q.numerator() * (const RVector_3& )(w))
                                  / q.denominator()));
}

template < class R >
_Vector_3_rft_wrapper<R>
multiply(const Vector_3<R>& v,
              const Vector_3<R>& w,
              const No_number_tag&)
{
  typedef typename  R::Vector_3       RVector_3;
  return _Vector_3_rft_wrapper<R>((const RVector_3& )(v)
                                     * (const RVector_3& )(w));
}

template < class T, class R >
_Vector_3_rft_wrapper<R>
multiply(const T& n,
              const Vector_3<R>& w,
              const Number_tag&)
{
  typedef typename  R::Vector_3       RVector_3;
  typedef typename  R::RT             RT;
  return _Vector_3_rft_wrapper<R>(
                 Vector_3<R>(RT(n) * (const RVector_3& )(w)));
}

template <class T, class R>
_Vector_3_rft_wrapper<R>
operator*(const T& t, const Vector_3<R>& w)
{
  return multiply(t, w, number_type_tag(t));
}
#endif // VECTOR_WRAPPER

#ifndef NO_OSTREAM_INSERT_VECTOR_3
template < class R >
std::ostream&
operator<<(std::ostream& os, const Vector_3<R>& v)
{
  typedef typename  R::Vector_3    RVector_3;
  return os << (const RVector_3& )v;
}
#endif // NO_OSTREAM_INSERT_VECTOR_3

#ifndef NO_ISTREAM_EXTRACT_VECTOR_3
template < class R >
std::istream&
operator>>(std::istream& is, Vector_3<R>& p)
{
  typedef typename  R::Vector_3    RVector_3;
  return is >> (RVector_3& )p;
}
#endif // NO_ISTREAM_EXTRACT_VECTOR_3


template<class R>
inline
Vector_3<R>
cross_product(const Vector_3<R>& v,const Vector_3<R>& w)
{
  typedef typename  R::Vector_3      RVector_3;
  return cross_product((const RVector_3& )v,(const RVector_3& )w);
}

CGAL_END_NAMESPACE


#endif // CGAL_VECTOR_3_H
