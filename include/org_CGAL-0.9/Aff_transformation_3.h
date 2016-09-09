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


// Source: Aff_transformation_3.h
// Author: Andreas Fabri
//         Stefan Schirra

#ifndef CGAL_AFF_TRANSFORMATION_3_H
#define CGAL_AFF_TRANSFORMATION_3_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_WORKAROUND_015
#define CGAL_NO_PLANE_TRANSFORM_IN_AT
#endif // CGAL_WORKAROUND_015

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/Aff_transformationH3.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/Aff_transformationC3.h>
#endif // CGAL_CARTESIAN_H

#include <CGAL/Point_3.h>
#include <CGAL/Vector_3.h>
#include <CGAL/Direction_3.h>
#include <CGAL/Plane_3.h>


template <class _R>
class CGAL_Aff_transformation_3 : public _R::Aff_transformation_3
{
public:
  typedef  _R   R;
private:

public:
  // default constructor
  CGAL_Aff_transformation_3()
    : R::Aff_transformation_3()
  {}

  // copy constructor
  CGAL_Aff_transformation_3(const CGAL_Aff_transformation_3<R> &t)
    : R::Aff_transformation_3(t)
  {}

  // up cast constructor
  CGAL_Aff_transformation_3(const R::Aff_transformation_3 &t)
    : R::Aff_transformation_3(t)
  {}

  // Translation:
  CGAL_Aff_transformation_3(const CGAL_Translation tag,
                            const CGAL_Vector_3<R> &v)
    : R::Aff_transformation_3(tag, v)
  {}

  // Scaling:
  CGAL_Aff_transformation_3(const CGAL_Scaling tag,
                            const R::RT &s,
                            const R::RT &w= R::RT(1.0))
    : R::Aff_transformation_3(tag, s, w)
  {}

  // The general case:
  CGAL_Aff_transformation_3(
     const R::RT & m11, const R::RT & m12, const R::RT & m13, const R::RT & m14,
     const R::RT & m21, const R::RT & m22, const R::RT & m23, const R::RT & m24,
     const R::RT & m31, const R::RT & m32, const R::RT & m33, const R::RT & m34,
                                                     const R::RT &w= R::RT(1.0))
    : R::Aff_transformation_3(m11, m12, m13, m14,
                              m21, m22, m23, m24,
                              m31, m32, m33, m34,
                              w)
  {}

  CGAL_Aff_transformation_3(
     const R::RT & m11, const R::RT & m12, const R::RT & m13,
     const R::RT & m21, const R::RT & m22, const R::RT & m23,
     const R::RT & m31, const R::RT & m32, const R::RT & m33,
                                                    const R::RT &w= R::RT(1.0))
    : R::Aff_transformation_3(m11, m12, m13,
                              m21, m22, m23,
                              m31, m32, m33,
                              w)
  {}

  ~CGAL_Aff_transformation_3()
  {}

  CGAL_Point_3<R>     transform(const CGAL_Point_3<R> &p) const
  {
    return R::Aff_transformation_3::transform(p);
  }

  CGAL_Point_3<R>     operator()(const CGAL_Point_3<R> &p) const
  {
    return R::Aff_transformation_3::transform(p);
  }

  CGAL_Vector_3<R>    transform(const CGAL_Vector_3<R> &v) const
  {
    return R::Aff_transformation_3::transform(v);
  }

  CGAL_Vector_3<R>    operator()(const CGAL_Vector_3<R> &v) const
  {
    return R::Aff_transformation_3::transform(v);
  }

  CGAL_Direction_3<R> transform(const CGAL_Direction_3<R> &d) const
  {
    return R::Aff_transformation_3::transform(d);
  }

  CGAL_Direction_3<R> operator()(const CGAL_Direction_3<R> &d) const
  {
    return R::Aff_transformation_3::transform(d);
  }

  CGAL_Plane_3<R>     transform(const CGAL_Plane_3<R> &pl) const
  {
#ifndef CGAL_NO_PLANE_TRANSFORM_IN_AT
    return R::Aff_transformation_3::transform(pl);
#else
    return
     ((const R::Plane_3&)pl).transform((const R::Aff_transformation_3&)(*this));
#endif // CGAL_NO_PLANE_TRANSFORM_IN_AT
  }

  CGAL_Plane_3<R>     operator()(const CGAL_Plane_3<R> &pl) const
  {
#ifndef CGAL_NO_PLANE_TRANSFORM_IN_AT
    return R::Aff_transformation_3::transform(pl);
#else
    return
     ((const R::Plane_3&)pl).transform((const R::Aff_transformation_3&)(*this));
#endif // CGAL_NO_PLANE_TRANSFORM_IN_AT
  }



  CGAL_Aff_transformation_3<R>  inverse() const
  {
    return R::Aff_transformation_3::inverse();
  }

  bool                is_even() const
  {
    return R::Aff_transformation_3::is_even();
  }

  bool                is_odd() const
  {
    return !is_even();
  }

  CGAL_Aff_transformation_3<R> operator*(const CGAL_Aff_transformation_3<R> &t)
                                                                           const
  {
    return (R::Aff_transformation_3&)(*this) * (R::Aff_transformation_3&)t;
  }
};


#ifndef CGAL_NO_OSTREAM_INSERT_AFF_TRANSFORMATION_3
template < class R >
ostream &operator<<(ostream &os, const CGAL_Aff_transformation_3<R> &t)
{
    return os << (const R::Aff_transformation_3&)t;
}
#endif // CGAL_NO_OSTREAM_INSERT_AFF_TRANSFORMATION_3

#ifndef CGAL_NO_ISTREAM_EXTRACT_AFF_TRANSFORMATION_3
template < class R >
istream &operator>>(istream &is, CGAL_Aff_transformation_3<R> &t)
{
    return is >> (R::Aff_transformation_3&)t;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_AFF_TRANSFORMATION_3




#endif // CGAL_AFF_TRANSFORMATION_3_H
