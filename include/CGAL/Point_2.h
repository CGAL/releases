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
// source        : Point_2.fw
// file          : include/CGAL/Point_2.h
// package       : _2 (2.1.2)
// revision      : 2.1.2
// revision_date : 09 May 1999 
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : cgal@cs.uu.nl
//
// ======================================================================
 

#ifndef CGAL_POINT_2_H
#define CGAL_POINT_2_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#ifndef CGAL_POINTH2_H
#include <CGAL/PointH2.h>
#endif // CGAL_POINTH2_H
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#ifndef CGAL_POINTC2_H
#include <CGAL/PointC2.h>
#endif // CGAL_POINTC2_H
#endif // CGAL_CARTESIAN_H

#ifndef CGAL_VECTOR_2_H
#include <CGAL/Vector_2.h>
#endif // CGAL_VECTOR_2_H

CGAL_BEGIN_NAMESPACE

template <class _R>
class Point_2 : public _R::Point_2
{
public:
  typedef  _R   R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Point_2               RPoint_2;
  typedef typename R::Vector_2              RVector_2;


friend  inline
        Point_2<R>
        operator+ CGAL_NULL_TMPL_ARGS (const Origin &o,
                                       const Vector_2<R> &v);
friend  inline
        Point_2<R>
        operator- CGAL_NULL_TMPL_ARGS (const Origin &o,
                                       const Vector_2<R> &v);

  Point_2()
  {}

  Point_2(const Origin &o)
    : RPoint_2(o)
  {}

  Point_2(const Point_2<R> &p)
    : RPoint_2((RPoint_2&)p)
  {}

  Point_2(const RPoint_2& p)
    : RPoint_2(p)
  {}

  Point_2(const RT &hx, const RT &hy)
    : RPoint_2(hx, hy)
  {}

  Point_2(const RT &hx, const RT &hy, const RT &hw)
    : RPoint_2(hx, hy, hw)
  {}

  Point_2<R> &operator=(const Point_2<R> &p)
  {
    RPoint_2::operator=(p);
    return *this;
  }

  bool operator==(const Point_2<R> &p) const
  {
    return RPoint_2::operator==(p);
  }

  bool operator!=(const Point_2<R> &p) const
  {
    return !(*this == p);
  }

  int id() const
  {
    return (int) PTR;
  }

  RT hx() const
  {
    return RPoint_2::hx();
  }

  RT hy() const
  {
    return RPoint_2::hy();
  }

  RT hw() const
  {
    return RPoint_2::hw();
  }
  FT x() const
  {
    return RPoint_2::x();
  }

  FT y() const
  {
    return RPoint_2::y();
  }

  RT homogeneous(int i) const
  {
    return RPoint_2::homogeneous(i);
  }

  FT cartesian(int i) const
  {
    return RPoint_2::cartesian(i);
  }

  FT operator[](int i) const
  {
    return cartesian(i);
  }

  int dimension() const
  {
    return 2;
  }

  Bbox_2       bbox() const
  {
    return RPoint_2::bbox();
  }

  Point_2<R> transform(const Aff_transformation_2<R> &t) const
  {
    return RPoint_2::transform(t);
  }

private:

  Point_2(const RVector_2& v)
    : RPoint_2(v)
  {}
};

#ifndef NO_OSTREAM_INSERT_POINT_2
template < class R >
std::ostream &
operator<<(std::ostream &os, const Point_2<R> &p)
{
  typedef typename  R::Point_2    RPoint_2;
  return os << (const RPoint_2&)p;
}
#endif // NO_OSTREAM_INSERT_POINT_2

#ifndef NO_ISTREAM_EXTRACT_POINT_2
template < class R >
std::istream &
operator>>(std::istream &is, Point_2<R> &p)
{
  typedef typename  R::Point_2    RPoint_2;
  return is >> (RPoint_2&)p;
}
#endif // NO_ISTREAM_EXTRACT_POINT_2

template <class R>
inline
Point_2<R>
operator+(const Origin &o, const Vector_2<R> &v);

template <class R>
inline
Point_2<R>
operator-(const Origin &o, const Vector_2<R> &v);

template <class R>
inline
Vector_2<R>
operator-(const Point_2<R> &p, const Origin &);

CGAL_END_NAMESPACE


#ifndef CGAL_AFF_TRANSFORMATION_2_H
#include <CGAL/Aff_transformation_2.h>
#endif // CGAL_AFF_TRANSFORMATION_2_H

CGAL_BEGIN_NAMESPACE

template < class R >
inline
Point_2<R> operator+(const Point_2<R> &p,
                     const Vector_2<R> &v)
{
  typedef typename  R::Point_2     RPoint_2;
  typedef typename  R::Vector_2    RVector_2;
  return Point_2<R>((const RPoint_2&)p + (const RVector_2&)v) ;
}

#ifdef VECTOR_WRAPPER
template < class R >
inline
Point_2<R> operator+(const Point_2<R> &p,
                     const _Vector_2_rft_wrapper<R> &wrapper)
{
  typedef typename  R::Point_2     RPoint_2;
  typedef typename  R::Vector_2    RVector_2;
  return Point_2<R>((const RPoint_2&)p +
                    (const RVector_2&)((const Vector_2<R>&)wrapper)) ;
}

template < class R >
inline
Point_2<R> operator-(const Point_2<R> &p,
                     const _Vector_2_rft_wrapper<R> &wrapper)
{
  typedef typename  R::Point_2     RPoint_2;
  typedef typename  R::Vector_2    RVector_2;
  return Point_2<R>((const RPoint_2&)p -
                    (const RVector_2&)((const Vector_2<R>&)wrapper)) ;
}
#endif // VECTOR_WRAPPER

template < class R >
inline
Point_2<R> operator-(const Point_2<R> &p,
                          const Vector_2<R> &v)
{
  typedef typename  R::Point_2     RPoint_2;
  typedef typename  R::Vector_2    RVector_2;
  return Point_2<R>((const RPoint_2&)p - (const RVector_2&)v) ;
}

template < class R >
inline
Point_2<R> operator+(const Origin &,
                     const Vector_2<R> &v)
{ return Point_2<R>(v) ; }


template < class R >
inline
Point_2<R> operator-(const Origin &,
                     const Vector_2<R> &v)
{ return Point_2<R>(-v) ; }

template < class R >
inline
Vector_2<R> operator-(const Point_2<R> &p,
                           const Point_2<R> &q)
{
  typedef typename  R::Point_2     RPoint_2;
  return Vector_2<R>((const RPoint_2&)p - (const RPoint_2&)q) ;
}

template < class R >
inline
Vector_2<R> operator-(const Point_2<R> &p,
                      const Origin &)
{ return Vector_2<R>(p) ; }

template < class R >
inline
Vector_2<R> operator-(const Origin &,
                      const Point_2<R> &p)
{
  typedef typename  R::Point_2     RPoint_2;
  return Vector_2<R>(ORIGIN - (const RPoint_2&)p) ;
}


template <class R>
inline
bool
operator==(const Origin& o, const Point_2<R>& p)
{ return p == o; }

template <class R>
inline
bool
operator!=(const Origin& o, const Point_2<R>& p)
{ return p != o; }

CGAL_END_NAMESPACE


#endif // CGAL_POINT_2_H
