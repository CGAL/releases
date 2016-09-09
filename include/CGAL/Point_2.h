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
// file          : include/CGAL/Point_2.h
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// email         : cgal@cs.uu.nl
//
// ============================================================================
 

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

template <class _R>
class CGAL_Point_2 : public _R::Point_2
{
public:
  typedef  _R   R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Point_2               Point_2;
  typedef typename R::Vector_2              Vector_2;


friend  CGAL_Point_2<R>
        operator+ CGAL_NULL_TMPL_ARGS (const CGAL_Origin &o,
                                       const CGAL_Vector_2<R> &v);
friend  CGAL_Point_2<R>
        operator- CGAL_NULL_TMPL_ARGS (const CGAL_Origin &o,
                                       const CGAL_Vector_2<R> &v);

  CGAL_Point_2()
  {}

  CGAL_Point_2(const CGAL_Origin &o)
    : Point_2(o)
  {}

  CGAL_Point_2(const CGAL_Point_2<R> &p)
    : Point_2((Point_2&)p)
  {}

  CGAL_Point_2(const Point_2 &p)
    : Point_2(p)
  {}

  CGAL_Point_2(const RT &hx, const RT &hy)
    : Point_2(hx, hy)
  {}

  CGAL_Point_2(const RT &hx, const RT &hy, const RT &hw)
    : Point_2(hx, hy, hw)
  {}

  CGAL_Point_2<R> &operator=(const CGAL_Point_2<R> &p)
  {
    Point_2::operator=(p);
    return *this;
  }

  bool operator==(const CGAL_Point_2<R> &p) const
  {
    return Point_2::operator==(p);
  }

  bool operator!=(const CGAL_Point_2<R> &p) const
  {
    return !(*this == p);
  }

  int id() const
  {
    return (int) PTR;
  }

  RT hx() const
  {
    return Point_2::hx();
  }

  RT hy() const
  {
    return Point_2::hy();
  }

  RT hw() const
  {
    return Point_2::hw();
  }
  FT x() const
  {
    return Point_2::x();
  }

  FT y() const
  {
    return Point_2::y();
  }

  RT homogeneous(int i) const
  {
    return Point_2::homogeneous(i);
  }

  FT cartesian(int i) const
  {
    return Point_2::cartesian(i);
  }

  FT operator[](int i) const
  {
    return cartesian(i);
  }

  int dimension() const
  {
    return 2;
  }

  CGAL_Bbox_2       bbox() const
  {
    return Point_2::bbox();
  }

  CGAL_Point_2<R> transform(const CGAL_Aff_transformation_2<R> &t) const
  {
    return Point_2::transform(t);
  }

private:

  CGAL_Point_2(const Vector_2 &v)
    : Point_2(v)
  {}
};

#ifndef CGAL_NO_OSTREAM_INSERT_POINT_2
template < class R >
ostream &
operator<<(ostream &os, const CGAL_Point_2<R> &p)
{
  typedef typename  R::Point_2    Point_2;
  return os << (const Point_2&)p;
}
#endif // CGAL_NO_OSTREAM_INSERT_POINT_2

#ifndef CGAL_NO_ISTREAM_EXTRACT_POINT_2
template < class R >
istream &
operator>>(istream &is, CGAL_Point_2<R> &p)
{
  typedef typename  R::Point_2    Point_2;
  return is >> (Point_2&)p;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_POINT_2

template <class R>
inline
CGAL_Point_2<R>
operator+(const CGAL_Origin &o, const CGAL_Vector_2<R> &v);

template <class R>
inline
CGAL_Point_2<R>
operator-(const CGAL_Origin &o, const CGAL_Vector_2<R> &v);

template < class R >
inline
CGAL_Vector_2<R>
operator-(const CGAL_Point_2<R> &p, const CGAL_Origin &);


#ifndef CGAL_AFF_TRANSFORMATION_2_H
#include <CGAL/Aff_transformation_2.h>
#endif // CGAL_AFF_TRANSFORMATION_2_H

template < class R >
inline
CGAL_Point_2<R> operator+(const CGAL_Point_2<R> &p,
                          const CGAL_Vector_2<R> &v)
{
  typedef typename  R::Point_2     Point_2;
  typedef typename  R::Vector_2    Vector_2;
  return CGAL_Point_2<R>((const Point_2&)p + (const Vector_2&)v) ;
}

#ifdef CGAL_VECTOR_WRAPPER
template < class R >
inline
CGAL_Point_2<R> operator+(const CGAL_Point_2<R> &p,
                          const CGAL__Vector_2_rft_wrapper<R> &wrapper)
{
  typedef typename  R::Point_2     Point_2;
  typedef typename  R::Vector_2    Vector_2;
  return CGAL_Point_2<R>((const Point_2&)p +
                      (const Vector_2&)((const CGAL_Vector_2<R>&)wrapper)) ;
}

template < class R >
inline
CGAL_Point_2<R> operator-(const CGAL_Point_2<R> &p,
                          const CGAL__Vector_2_rft_wrapper<R> &wrapper)
{
  typedef typename  R::Point_2     Point_2;
  typedef typename  R::Vector_2    Vector_2;
  return CGAL_Point_2<R>((const Point_2&)p -
                      (const Vector_2&)((const CGAL_Vector_2<R>&)wrapper)) ;
}
#endif // CGAL_VECTOR_WRAPPER

template < class R >
inline
CGAL_Point_2<R> operator-(const CGAL_Point_2<R> &p,
                          const CGAL_Vector_2<R> &v)
{
  typedef typename  R::Point_2     Point_2;
  typedef typename  R::Vector_2    Vector_2;
  return CGAL_Point_2<R>((const Point_2&)p - (const Vector_2&)v) ;
}

template < class R >
inline
CGAL_Point_2<R> operator+(const CGAL_Origin &,
                          const CGAL_Vector_2<R> &v)
{
  return CGAL_Point_2<R>(v) ;
}


template < class R >
inline
CGAL_Point_2<R> operator-(const CGAL_Origin &,
                          const CGAL_Vector_2<R> &v)
{
  return CGAL_Point_2<R>(-v) ;
}

template < class R >
inline
CGAL_Vector_2<R> operator-(const CGAL_Point_2<R> &p,
                           const CGAL_Point_2<R> &q)
{
  typedef typename  R::Point_2     Point_2;
  return CGAL_Vector_2<R>((const Point_2&)p - (const Point_2&)q) ;
}

template < class R >
inline
CGAL_Vector_2<R> operator-(const CGAL_Point_2<R> &p,
                           const CGAL_Origin &)
{
  return CGAL_Vector_2<R>(p) ;
}

template < class R >
inline
CGAL_Vector_2<R> operator-(const CGAL_Origin &,
                           const CGAL_Point_2<R> &p)
{
  typedef typename  R::Point_2     Point_2;
  return CGAL_Vector_2<R>(CGAL_ORIGIN - (const Point_2&)p) ;
}



#endif // CGAL_POINT_2_H
