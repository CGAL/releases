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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-1.1
// release_date  : 1998, July 24
// 
// source        : Vector_3.fw
// file          : include/CGAL/Vector_3.h
// package       : _3 (1.3)
// revision      : 1.3
// revision_date : 15 May 1998 
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

#ifdef CGAL_VECTOR_WRAPPER
#ifndef CGAL_VECTOR_3_RFT_WRAPPER_H
#include <CGAL/Vector_3_rft_wrapper.h>
#endif // CGAL_VECTOR_3_RFT_WRAPPER_H
#endif // CGAL_VECTOR_WRAPPER

template <class _R>
class CGAL_Vector_3 : public _R::Vector_3
{
public:
  typedef          _R                       R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Vector_3              Vector_3;

// #ifdef CGAL_WORKAROUND_001
friend CGAL_Vector_3<R>
       operator- CGAL_NULL_TMPL_ARGS (const CGAL_Point_3<R>& p,
                                      const CGAL_Origin& o);

friend CGAL_Vector_3<R>
       CGAL_Direction_3<R>::vector() const;
/*
#else
friend inline CGAL_Vector_3<R> operator-(const CGAL_Point_3<R>& p,
                                         const CGAL_Origin& o);

//friend inline CGAL_Vector_3<R> CGAL_Direction_3<R>::vector() const;
friend class CGAL_Direction_3<R>;
#endif  // CGAL_WORKAROUND_001
*/

  CGAL_Vector_3()
  {}
  CGAL_Vector_3(const CGAL_Vector_3<R>& v)
    : Vector_3( (const Vector_3&)v )
  {}
  CGAL_Vector_3(const Vector_3& v) : Vector_3(v)
  {}
  CGAL_Vector_3(const CGAL_Null_vector& v) : Vector_3(v)
  {}
  CGAL_Vector_3(const RT& x, const RT& y, const RT& z)
    : Vector_3(x, y, z)
  {}
  CGAL_Vector_3(const RT& x, const RT& y, const RT& z, const RT& w)
    : Vector_3(x, y, z, w)
  {}

  CGAL_Vector_3<R>& operator=(const CGAL_Vector_3<R>& v)
  {
    Vector_3::operator=(v);
    return *this;
  }
  bool operator==(const CGAL_Vector_3<R>& v) const
  { return Vector_3::operator==(v); }
  bool operator!=(const CGAL_Vector_3<R>& v) const
  { return !(*this == v); }
  bool operator==(const CGAL_Null_vector& v) const
  { return Vector_3::operator==(v); }
  bool operator!=(const CGAL_Null_vector& v) const
  { return !(*this == v); }
  int id() const    /* XXX */
  { return (int) PTR ; }
  RT hx() const
  { return Vector_3::hx(); }
  RT hy() const
  { return Vector_3::hy(); }
  RT hz() const
  { return Vector_3::hz(); }
  RT hw() const
  { return Vector_3::hw(); }
  FT x() const
  { return Vector_3::x(); }
  FT y() const
  { return Vector_3::y(); }
  FT z() const
  { return Vector_3::z(); }
  RT homogeneous(int i) const
  { return Vector_3::homogeneous(i); }
  FT cartesian(int i) const
  { return Vector_3::cartesian(i); }
  FT operator[](int i) const
  { return cartesian(i); }
  int dimension() const
  { return 3; }
  CGAL_Vector_3<R> operator+(const CGAL_Vector_3<R>& w) const
  { return (const Vector_3&)(*this) + (const Vector_3&)(w); }
  CGAL_Vector_3<R> operator-(const CGAL_Vector_3<R>& w) const
  { return (const Vector_3&)(*this) - (const Vector_3&)(w); }
  CGAL_Vector_3<R> operator-() const
  { return Vector_3::operator-(); }
  FT operator*(const CGAL_Vector_3<R>& w) const
  { return (const Vector_3&)(*this) * (const Vector_3&)(w); }

#ifndef CGAL_VECTOR_WRAPPER
  CGAL_Vector_3<R> operator*(const RT& c) const
  { return c * (const Vector_3&)(*this) ; }
  CGAL_Vector_3<R> operator*(const CGAL_Quotient<RT>& q) const
  {
    return (q.numerator() * (const Vector_3&)(*this)) /
            q.denominator();
  }
  CGAL_Vector_3<R> operator/(const CGAL_Quotient<RT>& q) const
  {
    return (q.denominator() * (const Vector_3&)(*this)) /
            q.numerator();
  }
#endif // CGAL_VECTOR_WRAPPER

  CGAL_Vector_3<R> operator/(const RT& c) const
  { return (const Vector_3&)(*this) / c; }
  CGAL_Direction_3<R> direction() const
  { return Vector_3::direction(); }
  CGAL_Vector_3<R> transform(const CGAL_Aff_transformation_3<R>& t) const
  { return Vector_3::transform(t); }

private:
  CGAL_Vector_3(const CGAL_Point_3<R>& p) : Vector_3(p)
  {}
  CGAL_Vector_3(const CGAL_Direction_3<R>& d) : Vector_3(d)
  {}
};

template < class R >
CGAL_No_number_tag CGAL_number_type_tag(const CGAL_Vector_3<R>& )
{
  return CGAL_No_number_tag();
}

#ifdef CGAL_VECTOR_WRAPPER
template <class T, class R>
CGAL__Vector_3_rft_wrapper<R>
CGAL_multiply(const CGAL_Quotient<T>& q,
              const CGAL_Vector_3<R>& w,
              const CGAL_Quotient_tag&)
{
  typedef typename  R::Vector_3       Vector_3;
  return CGAL__Vector_3_rft_wrapper<R>(
                 CGAL_Vector_3<R>((q.numerator() * (const Vector_3&)(w))
                                  / q.denominator()));
}

template < class R >
CGAL__Vector_3_rft_wrapper<R>
CGAL_multiply(const CGAL_Vector_3<R>& v,
              const CGAL_Vector_3<R>& w,
              const CGAL_No_number_tag&)
{
  typedef typename  R::Vector_3       Vector_3;
  return CGAL__Vector_3_rft_wrapper<R>((const Vector_3&)(v)
                                     * (const Vector_3&)(w));
}

template < class T, class R >
CGAL__Vector_3_rft_wrapper<R>
CGAL_multiply(const T& n,
              const CGAL_Vector_3<R>& w,
              const CGAL_Number_tag&)
{
  typedef typename  R::Vector_3       Vector_3;
  typedef typename  R::RT             RT;
  return CGAL__Vector_3_rft_wrapper<R>(
                 CGAL_Vector_3<R>(RT(n) * (const Vector_3&)(w)));
}

template <class T, class R>
CGAL__Vector_3_rft_wrapper<R>
operator*(const T& t, const CGAL_Vector_3<R>& w)
{
  return CGAL_multiply(t, w, CGAL_number_type_tag(t));
}
#endif // CGAL_VECTOR_WRAPPER

#ifndef CGAL_NO_OSTREAM_INSERT_VECTOR_3
template < class R >
ostream&
operator<<(ostream& os, const CGAL_Vector_3<R>& v)
{
  typedef typename  R::Vector_3    Vector_3;
  return os << (const Vector_3&)v;
}
#endif // CGAL_NO_OSTREAM_INSERT_VECTOR_3

#ifndef CGAL_NO_ISTREAM_EXTRACT_VECTOR_3
template < class R >
istream&
operator>>(istream& is, CGAL_Vector_3<R>& p)
{
  typedef typename  R::Vector_3    Vector_3;
  return is >> (Vector_3&)p;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_VECTOR_3


template<class R>
inline
CGAL_Vector_3<R>
CGAL_cross_product(const CGAL_Vector_3<R>& v,const CGAL_Vector_3<R>& w)
{
  typedef typename  R::Vector_3      Vector_3;
  return CGAL_cross_product((const Vector_3&)v,(const Vector_3&)w);
}


#endif // CGAL_VECTOR_3_H
