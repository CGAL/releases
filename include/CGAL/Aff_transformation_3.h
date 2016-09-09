//  Copyright CGAL 1996
//
//  cgal@cs.ruu.nl
//
//  This file is part of an internal release of the CGAL kernel.
//  The code herein may be used and/or copied only in accordance
//  with the terms and conditions stipulated in the agreement
//  under which the code has been supplied or with the written
//  permission of the CGAL Project.
//
//  Look at http://www.cs.ruu.nl/CGAL/ for more information.
//  Please send any bug reports and comments to cgal@cs.ruu.nl
//
//  The code comes WITHOUT ANY WARRANTY; without even the implied
//  warranty of FITNESS FOR A PARTICULAR PURPOSE.
//

// Source: Aff_transformation_3.h
// Author: Andreas.Fabri@sophia.inria.fr
//         Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL_AFF_TRANSFORMATION_3_H
#define CGAL_AFF_TRANSFORMATION_3_H

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


template < class R >
class CGAL_Aff_transformation_3 : public R::Aff_transformation_3
{
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



#endif // CGAL_AFF_TRANSFORMATION_3_H
