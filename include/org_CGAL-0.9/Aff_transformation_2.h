/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/


// Source: Aff_transformation_2.h
// Author: Andreas Fabri

#ifndef CGAL_AFF_TRANSFORMATION_2_H
#define CGAL_AFF_TRANSFORMATION_2_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_WORKAROUND_015
#define CGAL_NO_LINE_TRANSFORM_IN_AT
#endif // CGAL_WORKAROUND_015

#include <CGAL/Line_2.h>

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/Aff_transformationH2.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/Aff_transformationC2.h>
#endif // CGAL_CARTESIAN_H



template <class _R>
class CGAL_Aff_transformation_2 : public _R::Aff_transformation_2
{
public:
  typedef  _R   R;
private:

public:
  // default constructor
  CGAL_Aff_transformation_2()
    : R::Aff_transformation_2()
  {}

  // copy constructor
  CGAL_Aff_transformation_2(const CGAL_Aff_transformation_2<R> &t)
    : R::Aff_transformation_2(t)
  {}

  // up cast constructor
  CGAL_Aff_transformation_2(const R::Aff_transformation_2 &t)
    : R::Aff_transformation_2(t)
  {}

  // Translation:
  CGAL_Aff_transformation_2(const CGAL_Translation tag,
                            const CGAL_Vector_2<R> &v)
    : R::Aff_transformation_2(tag, v)
  {}

  // Rational Rotation:
  CGAL_Aff_transformation_2(const CGAL_Rotation tag,
                            const CGAL_Direction_2<R> &d,
                            const R::RT &num,
                            const R::RT &den = R::RT(1))
    : R::Aff_transformation_2(tag, R::Direction_2(d), num, den)
  {}

  CGAL_Aff_transformation_2(const CGAL_Rotation tag,
                            const R::RT &sin,
                            const R::RT &cos,
                            const R::RT &den = R::RT(1))
    : R::Aff_transformation_2(tag, sin, cos, den)
  {}

  // Scaling:
  CGAL_Aff_transformation_2(const CGAL_Scaling tag,
                            const R::RT &s,
                            const R::RT &w= R::RT(1))
    : R::Aff_transformation_2(tag, s, w)
  {}

  // The general case:
  CGAL_Aff_transformation_2(const R::RT & m11,
                            const R::RT & m12,
                            const R::RT & m13,

                            const R::RT & m21,
                            const R::RT & m22,
                            const R::RT & m23,

                            const R::RT &w= R::RT(1))
    : R::Aff_transformation_2(m11, m12, m13,
                              m21, m22, m23,
                              w)
  {}

  CGAL_Aff_transformation_2(const R::RT & m11, const R::RT & m12,
                            const R::RT & m21, const R::RT & m22,
                            const R::RT &w = R::RT(1))
    : R::Aff_transformation_2(m11, m12,
                              m21, m22,
                              w)
  {}

  ~CGAL_Aff_transformation_2()
  {}

  CGAL_Aff_transformation_2<R>& operator=(const CGAL_Aff_transformation_2<R>& t)
  {
    R::Aff_transformation_2::operator=(t);
    return *this;
  }


  CGAL_Point_2<R>     transform(const CGAL_Point_2<R> &p) const
  {
    return R::Aff_transformation_2::transform(p);
  }

  CGAL_Point_2<R>     operator()(const CGAL_Point_2<R> &p) const
  {
    return transform(p);
  }

  CGAL_Vector_2<R>    transform(const CGAL_Vector_2<R> &v) const
  {
    return R::Aff_transformation_2::transform(v);
  }

  CGAL_Vector_2<R>    operator()(const CGAL_Vector_2<R> &v) const
  {
    return transform(v);
  }

  CGAL_Direction_2<R> transform(const CGAL_Direction_2<R> &d) const
  {
    return R::Aff_transformation_2::transform(d);
  }

  CGAL_Direction_2<R> operator()(const CGAL_Direction_2<R> &d) const
  {
    return transform(d);
  }


  CGAL_Line_2<R> transform(const CGAL_Line_2<R> &l) const
  {
#ifndef CGAL_NO_LINE_TRANSFORM_IN_AT
    return R::Aff_transformation_2::transform(l);
#else
    return
      ((const R::Line_2&)l).transform((const R::Aff_transformation_2&)(*this));
#endif // CGAL_NO_LINE_TRANSFORM_IN_AT
  }

  CGAL_Line_2<R> operator()(const CGAL_Line_2<R> &l) const
  {
    return transform(l);
  }



  CGAL_Aff_transformation_2<R>  inverse() const
  {
    return R::Aff_transformation_2::inverse();
  }

  bool                 is_even() const
  {
    return R::Aff_transformation_2::is_even();
  }

  bool                 is_odd() const
  {
    return !is_even();
  }

  CGAL_Aff_transformation_2<R> operator*(
                              const CGAL_Aff_transformation_2<R> &t) const
  {
    return R::Aff_transformation_2::operator*(t);
  }
};

#ifndef CGAL_NO_OSTREAM_INSERT_AFF_TRANSFORMATION_2
template < class R >
ostream &operator<<(ostream &os, const CGAL_Aff_transformation_2<R> &t)
{
    return os << (const R::Aff_transformation_2&)t;
}
#endif // CGAL_NO_OSTREAM_INSERT_AFF_TRANSFORMATION_2

#ifndef CGAL_NO_ISTREAM_EXTRACT_AFF_TRANSFORMATION_2
template < class R >
istream &operator>>(istream &is, CGAL_Aff_transformation_2<R> &t)
{
    return is >> (R::Aff_transformation_2&)t;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_AFF_TRANSFORMATION_2




#endif // CGAL_AFF_TRANSFORMATION_2_H
