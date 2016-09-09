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
// source        : Aff_transformation_2.fw
// file          : include/CGAL/Aff_transformation_2.h
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
 

#ifndef CGAL_AFF_TRANSFORMATION_2_H
#define CGAL_AFF_TRANSFORMATION_2_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#if defined(CGAL_CFG_INCOMPLETE_TYPE_BUG_1) && \
   !defined(CGAL_NO_LINE_TRANSFORM_IN_AT)
#define CGAL_NO_LINE_TRANSFORM_IN_AT
#endif // CGAL_CFG_INCOMPLETE_TYPE_BUG_1

#ifndef CGAL_LINE_2_H
#include <CGAL/Line_2.h>
#endif // CGAL_LINE_2_H

#ifdef CGAL_HOMOGENEOUS_H
#ifndef CGAL_AFF_TRANSFORMATIONH2_H
#include <CGAL/Aff_transformationH2.h>
#endif // CGAL_AFF_TRANSFORMATIONH2_H
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#ifndef CGAL_AFF_TRANSFORMATIONC2_H
#include <CGAL/Aff_transformationC2.h>
#endif // CGAL_AFF_TRANSFORMATIONC2_H
#endif // CGAL_CARTESIAN_H

CGAL_BEGIN_NAMESPACE

template <class _R>
class Aff_transformation_2 : public _R::Aff_transformation_2
{
public:
  typedef  _R                               R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Line_2                RLine_2;
  typedef typename R::Direction_2           RDirection_2;
  typedef typename R::Aff_transformation_2  RAff_transformation_2;

  // default constructor
  Aff_transformation_2()
    : RAff_transformation_2()
  {}

  // copy constructor
  Aff_transformation_2(const Aff_transformation_2<R> &t)
    : RAff_transformation_2(t)
  {}

  // up cast constructor
  Aff_transformation_2(const RAff_transformation_2& t)
    : RAff_transformation_2(t)
  {}

  // Translation:
  Aff_transformation_2(const Translation tag,
                       const Vector_2<R> &v)
    : RAff_transformation_2(tag, v)
  {}

  // Rational Rotation:
  Aff_transformation_2(const Rotation tag,
                       const Direction_2<R> &d,
                       const RT &num,
                       const RT &den = RT(1))
    : RAff_transformation_2(tag, RDirection_2(d), num, den)
  {}

  Aff_transformation_2(const Rotation tag,
                       const RT &sin,
                       const RT &cos,
                       const RT &den = RT(1))
    : RAff_transformation_2(tag, sin, cos, den)
  {}

  // Scaling:
  Aff_transformation_2(const Scaling tag,
                       const RT &s,
                       const RT &w= RT(1))
    : RAff_transformation_2(tag, s, w)
  {}

  // The general case:
  Aff_transformation_2(const RT & m11,
                       const RT & m12,
                       const RT & m13,

                       const RT & m21,
                       const RT & m22,
                       const RT & m23,

                       const RT &w= RT(1))
    : RAff_transformation_2(m11, m12, m13,
                            m21, m22, m23,
                                      w)
  {}

  Aff_transformation_2(const RT & m11, const RT & m12,
                       const RT & m21, const RT & m22,
                       const RT &w = RT(1))
    : RAff_transformation_2(m11, m12,
                            m21, m22,
                                      w)
  {}

  ~Aff_transformation_2()
  {}

  Aff_transformation_2<R>& operator=(const Aff_transformation_2<R>& t)
  {
    RAff_transformation_2::operator=(t);
    return *this;
  }


  Point_2<R>     transform(const Point_2<R> &p) const
                      { return RAff_transformation_2::transform(p); }

  Point_2<R>     operator()(const Point_2<R> &p) const
                      { return transform(p); }

  Vector_2<R>    transform(const Vector_2<R> &v) const
                      { return RAff_transformation_2::transform(v); }

  Vector_2<R>    operator()(const Vector_2<R> &v) const
                      { return transform(v); }

  Direction_2<R> transform(const Direction_2<R> &d) const
                      { return RAff_transformation_2::transform(d); }

  Direction_2<R> operator()(const Direction_2<R> &d) const
                      { return transform(d); }

  Line_2<R>      transform(const Line_2<R> &l) const
  {
#ifndef CGAL_NO_LINE_TRANSFORM_IN_AT
                        return RAff_transformation_2::transform(l);
#else
                        return
      ((const RLine_2&)l).transform((const RAff_transformation_2&)(*this));
#endif // CGAL_NO_LINE_TRANSFORM_IN_AT
                      }

  Line_2<R>      operator()(const Line_2<R> &l) const
                      { return transform(l); }


  Aff_transformation_2<R>
                      inverse() const
                      { return RAff_transformation_2::inverse(); }

  bool                is_even() const
                      { return RAff_transformation_2::is_even(); }

  bool                is_odd() const
                      { return !is_even(); }

  Aff_transformation_2<R>
                      operator*(const Aff_transformation_2<R> &t) const
                      { return RAff_transformation_2::operator*(t); }

  FT          cartesian(int i, int j) const
              { return RAff_transformation_2::cartesian(i,j); }
  RT          homogeneous(int i, int j) const
              { return RAff_transformation_2::homogeneous(i,j); }
  FT          m(int i, int j) const
              { return RAff_transformation_2::m(i,j); }
  RT          hm(int i, int j) const
              { return RAff_transformation_2::hm(i,j); }
  
};

#ifndef NO_OSTREAM_INSERT_AFF_TRANSFORMATION_2
template < class R >
std::ostream &
operator<<(std::ostream &os, const Aff_transformation_2<R> &t)
{
  typedef typename  R::Aff_transformation_2   RAff_transformation_2;
  return os << (const RAff_transformation_2&)t;
}
#endif // NO_OSTREAM_INSERT_AFF_TRANSFORMATION_2

#ifndef NO_ISTREAM_EXTRACT_AFF_TRANSFORMATION_2
template < class R >
std::istream &
operator>>(std::istream &is, Aff_transformation_2<R> &t)
{
  typedef typename  R::Aff_transformation_2   RAff_transformation_2;
  return is >> (RAff_transformation_2&)t;
}
#endif // NO_ISTREAM_EXTRACT_AFF_TRANSFORMATION_2

CGAL_END_NAMESPACE


#endif // CGAL_AFF_TRANSFORMATION_2_H
