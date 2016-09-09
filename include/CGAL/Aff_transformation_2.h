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
// file          : include/CGAL/Aff_transformation_2.h
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// email         : cgal@cs.uu.nl
//
// ============================================================================
 

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

template <class _R>
class CGAL_Aff_transformation_2 : public _R::Aff_transformation_2
{
public:
  typedef  _R                               R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Line_2                Line_2;
  typedef typename R::Direction_2           Direction_2;
  typedef typename R::Aff_transformation_2  Aff_transformation_2;

  // default constructor
  CGAL_Aff_transformation_2()
    : Aff_transformation_2()
  {}

  // copy constructor
  CGAL_Aff_transformation_2(const CGAL_Aff_transformation_2<R> &t)
    : Aff_transformation_2(t)
  {}

  // up cast constructor
  CGAL_Aff_transformation_2(const Aff_transformation_2 &t)
    : Aff_transformation_2(t)
  {}

  // Translation:
  CGAL_Aff_transformation_2(const CGAL_Translation tag,
                            const CGAL_Vector_2<R> &v)
    : Aff_transformation_2(tag, v)
  {}

  // Rational Rotation:
  CGAL_Aff_transformation_2(const CGAL_Rotation tag,
                            const CGAL_Direction_2<R> &d,
                            const RT &num,
                            const RT &den = RT(1))
    : Aff_transformation_2(tag, Direction_2(d), num, den)
  {}

  CGAL_Aff_transformation_2(const CGAL_Rotation tag,
                            const RT &sin,
                            const RT &cos,
                            const RT &den = RT(1))
    : Aff_transformation_2(tag, sin, cos, den)
  {}

  // Scaling:
  CGAL_Aff_transformation_2(const CGAL_Scaling tag,
                            const RT &s,
                            const RT &w= RT(1))
    : Aff_transformation_2(tag, s, w)
  {}

  // The general case:
  CGAL_Aff_transformation_2(const RT & m11,
                            const RT & m12,
                            const RT & m13,

                            const RT & m21,
                            const RT & m22,
                            const RT & m23,

                            const RT &w= RT(1))
    : Aff_transformation_2(m11, m12, m13,
                           m21, m22, m23,
                                     w)
  {}

  CGAL_Aff_transformation_2(const RT & m11, const RT & m12,
                            const RT & m21, const RT & m22,
                            const RT &w = RT(1))
    : Aff_transformation_2(m11, m12,
                           m21, m22,
                                     w)
  {}

  ~CGAL_Aff_transformation_2()
  {}

  CGAL_Aff_transformation_2<R>& operator=(const CGAL_Aff_transformation_2<R>& t)
  {
    Aff_transformation_2::operator=(t);
    return *this;
  }


  CGAL_Point_2<R>     transform(const CGAL_Point_2<R> &p) const
                      { return Aff_transformation_2::transform(p); }

  CGAL_Point_2<R>     operator()(const CGAL_Point_2<R> &p) const
                      { return transform(p); }

  CGAL_Vector_2<R>    transform(const CGAL_Vector_2<R> &v) const
                      { return Aff_transformation_2::transform(v); }

  CGAL_Vector_2<R>    operator()(const CGAL_Vector_2<R> &v) const
                      { return transform(v); }

  CGAL_Direction_2<R> transform(const CGAL_Direction_2<R> &d) const
                      { return Aff_transformation_2::transform(d); }

  CGAL_Direction_2<R> operator()(const CGAL_Direction_2<R> &d) const
                      { return transform(d); }

  CGAL_Line_2<R>      transform(const CGAL_Line_2<R> &l) const
  {
#ifndef CGAL_NO_LINE_TRANSFORM_IN_AT
                        return Aff_transformation_2::transform(l);
#else
                        return
      ((const Line_2&)l).transform((const Aff_transformation_2&)(*this));
#endif // CGAL_NO_LINE_TRANSFORM_IN_AT
                      }

  CGAL_Line_2<R>      operator()(const CGAL_Line_2<R> &l) const
                      { return transform(l); }


  CGAL_Aff_transformation_2<R>
                      inverse() const
                      { return Aff_transformation_2::inverse(); }

  bool                is_even() const
                      { return Aff_transformation_2::is_even(); }

  bool                is_odd() const
                      { return !is_even(); }

  CGAL_Aff_transformation_2<R>
                      operator*(const CGAL_Aff_transformation_2<R> &t) const
                      { return Aff_transformation_2::operator*(t); }

  FT          cartesian(int i, int j) const
              { return Aff_transformation_2::cartesian(i,j); }
  RT          homogeneous(int i, int j) const
              { return Aff_transformation_2::homogeneous(i,j); }
  FT          m(int i, int j) const
              { return Aff_transformation_2::m(i,j); }
  RT          hm(int i, int j) const
              { return Aff_transformation_2::hm(i,j); }
  
};

#ifndef CGAL_NO_OSTREAM_INSERT_AFF_TRANSFORMATION_2
template < class R >
ostream &
operator<<(ostream &os, const CGAL_Aff_transformation_2<R> &t)
{
  typedef typename  R::Aff_transformation_2   Aff_transformation_2;
  return os << (const Aff_transformation_2&)t;
}
#endif // CGAL_NO_OSTREAM_INSERT_AFF_TRANSFORMATION_2

#ifndef CGAL_NO_ISTREAM_EXTRACT_AFF_TRANSFORMATION_2
template < class R >
istream &
operator>>(istream &is, CGAL_Aff_transformation_2<R> &t)
{
  typedef typename  R::Aff_transformation_2   Aff_transformation_2;
  return is >> (Aff_transformation_2&)t;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_AFF_TRANSFORMATION_2


#endif // CGAL_AFF_TRANSFORMATION_2_H
