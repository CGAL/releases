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

// Source: Direction_2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_DIRECTION_2_H
#define CGAL_DIRECTION_2_H

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/DirectionH2.h>
#endif  // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/DirectionC2.h>
#endif // CGAL_CARTESIAN_H

#include <CGAL/Vector_2.h>

template < class R >
class CGAL_Direction_2 : public R::Direction_2
{
public:
  CGAL_Direction_2()
  {}

  CGAL_Direction_2(const CGAL_Direction_2<R> &d)
    : R::Direction_2((const R::Direction_2&)d)
  {}


  CGAL_Direction_2(const R::Direction_2 &d)
    : R::Direction_2(d)
  {}


  CGAL_Direction_2(const R::Vector_2 &v)
    : R::Direction_2(v)
  {}

  CGAL_Direction_2(const R::RT &x, const R::RT &y)
    :  R::Direction_2(x,y)
  {}

  CGAL_Direction_2<R> &operator=(const CGAL_Direction_2<R> &d)
  {
    R::Direction_2::operator=(d);
    return *this;
  }


  bool operator==(const CGAL_Direction_2<R> &d) const
  {
    return R::Direction_2::operator==(d);
  }

  bool operator!=(const CGAL_Direction_2<R> &d) const
  {
    return !(*this == d);
  }

  bool operator>=(const CGAL_Direction_2<R> &d) const
  {
    return R::Direction_2::operator>=(d);
  }

  bool operator<=(const CGAL_Direction_2<R> &d) const
  {
    return R::Direction_2::operator<=(d);
  }

  bool operator>(const CGAL_Direction_2<R> &d) const
  {
    return R::Direction_2::operator>(d);
  }

  bool operator<(const CGAL_Direction_2<R> &d) const
  {
    return R::Direction_2::operator<(d);
  }

  bool counterclockwise_in_between(const CGAL_Direction_2<R> &d1,
                                   const CGAL_Direction_2<R> &d2) const
  {
    return R::Direction_2::counterclockwise_in_between(d1,d2);
  }

  int id() const
  {
    return (int)PTR;
  }

  CGAL_Vector_2<R> vector() const
  {
    return (CGAL_Vector_2<R>)R::Direction_2::vector();
  }

  CGAL_Direction_2<R> transform(const CGAL_Aff_transformation_2<R> &t) const
  {
    return R::Direction_2::transform((const R::Aff_transformation_2&)(t));
  }

  CGAL_Direction_2<R> operator-() const
  {
    return R::Direction_2::operator-();
  }


  R::FT delta(int i) const
  {
    return R::Direction_2::delta(i);
  }

  R::FT dx() const
  {
    return R::Direction_2::dx();
  }

  R::FT dy() const
  {
    return R::Direction_2::dy();
  }
};


#endif // CGAL_DIRECTION_2_H
