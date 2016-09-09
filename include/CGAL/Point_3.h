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
// source        : Point_3.fw
// file          : include/CGAL/Point_3.h
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
 

#ifndef CGAL_POINT_3_H
#define CGAL_POINT_3_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#ifndef CGAL_POINTH3_H
#include <CGAL/PointH3.h>
#endif // CGAL_POINTH3_H
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#ifndef CGAL_POINTC3_H
#include <CGAL/PointC3.h>
#endif // CGAL_POINTC3_H
#endif // CGAL_CARTESIAN_H

#ifndef CGAL_VECTOR_3_H
#include <CGAL/Vector_3.h>
#endif // CGAL_VECTOR_3_H

template <class _R>
class CGAL_Point_3 : public _R::Point_3
{
public:
  typedef          _R                       R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Point_3               Point_3;
  typedef typename R::Vector_3              Vector_3;

// #ifdef CGAL_WORKAROUND_001
friend  CGAL_Point_3<R>
        operator+ CGAL_NULL_TMPL_ARGS (const CGAL_Origin& o,
                                       const CGAL_Vector_3<R>& v);
friend  CGAL_Point_3<R>
        operator- CGAL_NULL_TMPL_ARGS (const CGAL_Origin& o,
                                       const CGAL_Vector_3<R>& v);
/*
#else
friend inline CGAL_Point_3<R> operator+(const CGAL_Origin& o,
                                        const CGAL_Vector_3<R>& v);
friend inline CGAL_Point_3<R> operator-(const CGAL_Origin& o,
                                        const CGAL_Vector_3<R>& v);
#endif // CGAL_WORKAROUND_001
*/

public:
  CGAL_Point_3()
  {}
  CGAL_Point_3(const CGAL_Origin& o) : Point_3(o)
  {}
  CGAL_Point_3(const CGAL_Point_3<R>& p) : Point_3( (const Point_3&)p )
  {}
  CGAL_Point_3(const Point_3& p) : Point_3(p)
  {}
  CGAL_Point_3(const RT& hx, const RT& hy, const RT& hz)
    : Point_3(hx, hy, hz)
  {}
  CGAL_Point_3(const RT& hx, const RT& hy, const RT& hz, const RT& hw)
    : Point_3(hx, hy, hz, hw)
  {}

  CGAL_Point_3<R>& operator=(const CGAL_Point_3<R>& p)
  {
    Point_3::operator=(p);
    return *this;
  }

  bool operator==(const CGAL_Point_3<R>& p) const
  { return Point_3::operator==(p); }

  bool operator!=(const CGAL_Point_3<R>& p) const
  { return !(*this == p); }

  int id() const               /* XXX */
  { return (int) PTR ; }

  RT hx() const
  { return Point_3::hx(); }

  RT hy() const
  { return Point_3::hy(); }

  RT hz() const
  { return Point_3::hz(); }

  RT hw() const
  { return Point_3::hw(); }

  FT x() const
  { return Point_3::x(); }

  FT y() const
  { return Point_3::y(); }

  FT z() const
  { return Point_3::z(); }

  RT homogeneous(int i) const
  { return Point_3::homogeneous(i); }

  FT cartesian(int i) const
  { return Point_3::cartesian(i); }

  FT operator[](int i) const
  { return cartesian(i); }

  int dimension() const
  { return 3; }

  CGAL_Bbox_3       bbox() const
  { return Point_3::bbox(); }

  CGAL_Point_3<R> transform(const CGAL_Aff_transformation_3<R>& t) const
  { return Point_3::transform(t); }

private:
  CGAL_Point_3(const Vector_3& v) : Point_3(v)
  {}
};


#ifndef CGAL_AFF_TRANSFORMATION_3_H
#include <CGAL/Aff_transformation_3.h>
#endif // CGAL_AFF_TRANSFORMATION_3_H

template < class R >
inline
CGAL_Point_3<R> operator+(const CGAL_Point_3<R>& p,
                          const CGAL_Vector_3<R>& v)
{
  typedef typename  R::Point_3       Point_3;
  typedef typename  R::Vector_3      Vector_3;
  return CGAL_Point_3<R>((const Point_3&)p + (const Vector_3&)v) ;
}

#ifdef CGAL_VECTOR_WRAPPER
template < class R >
inline
CGAL_Point_3<R> operator+(const CGAL_Point_3<R>& p,
                          const CGAL__Vector_3_rft_wrapper<R>& wrapper)
{
  typedef typename  R::Point_3       Point_3;
  typedef typename  R::Vector_3      Vector_3;
  return CGAL_Point_3<R>((const Point_3&)p +
                      (const Vector_3&)((const CGAL_Vector_3<R>&)wrapper)) ;
}

template < class R >
inline
CGAL_Point_3<R> operator-(const CGAL_Point_3<R>& p,
                          const CGAL__Vector_3_rft_wrapper<R>& wrapper)
{
  typedef typename  R::Point_3       Point_3;
  typedef typename  R::Vector_3      Vector_3;
  return CGAL_Point_3<R>((const Point_3&)p -
                      (const Vector_3&)((const CGAL_Vector_3<R>&)wrapper)) ;
}
#endif // CGAL_VECTOR_WRAPPER

template < class R >
inline
CGAL_Point_3<R> operator-(const CGAL_Point_3<R>& p,
                          const CGAL_Vector_3<R>& v)
{
  typedef typename  R::Point_3       Point_3;
  typedef typename  R::Vector_3      Vector_3;
  return CGAL_Point_3<R>((const Point_3&)p - (const Vector_3&)v) ;
}

template < class R >
inline
CGAL_Point_3<R> operator+(const CGAL_Origin& ,
                          const CGAL_Vector_3<R>& v)
{ return CGAL_Point_3<R>(v) ; }

template < class R >
inline
CGAL_Point_3<R> operator-(const CGAL_Origin& ,
                          const CGAL_Vector_3<R>& v)
{ return CGAL_Point_3<R>(-v) ; }

template < class R >
inline
CGAL_Vector_3<R> operator-(const CGAL_Point_3<R>& p,
                           const CGAL_Point_3<R>& q)
{
  typedef typename  R::Point_3       Point_3;
  return CGAL_Vector_3<R>((const Point_3&)p - (const Point_3&)q) ;
}

template < class R >
inline
CGAL_Vector_3<R> operator-(const CGAL_Point_3<R>& p,
                           const CGAL_Origin& )
{ return CGAL_Vector_3<R>(p) ; }

template < class R >
inline
CGAL_Vector_3<R> operator-(const CGAL_Origin& ,
                           const CGAL_Point_3<R>& p)
{
  typedef typename  R::Point_3       Point_3;
  return CGAL_Vector_3<R>(CGAL_ORIGIN - (const Point_3&)p) ;
}


#ifndef CGAL_NO_OSTREAM_INSERT_POINT_3

template < class R >
ostream&
operator<<(ostream& os, const CGAL_Point_3<R>& p)
{
  typedef typename  R::Point_3      Point_3;
  return os << (const Point_3&)p;
}
#endif // CGAL_NO_OSTREAM_INSERT_POINT_3

#ifndef CGAL_NO_ISTREAM_EXTRACT_POINT_3
template < class R >
istream& operator>>(istream& is, CGAL_Point_3<R>& p)
{
  typedef typename  R::Point_3      Point_3;
  return is >> (Point_3&)p;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_POINT_3

#endif // CGAL_POINT_3_H
