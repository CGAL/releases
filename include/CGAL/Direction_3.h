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

// Source: Direction_3.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_DIRECTION_3_H
#define CGAL_DIRECTION_3_H

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/DirectionH3.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/DirectionC3.h>
#endif // CGAL_CARTESIAN_H

#include <CGAL/Vector_3.h>

template < class R >
class CGAL_Direction_3 : public R::Direction_3
{
public:
  CGAL_Direction_3()
  {}

  CGAL_Direction_3(const CGAL_Direction_3<R> &d)
    : R::Direction_3((R::Direction_3&)d)
  {}


  CGAL_Direction_3(const R::Direction_3 &d)
    : R::Direction_3(d)
  {}


  CGAL_Direction_3(const R::Vector_3 &v)
    : R::Direction_3(v)
  {}

  CGAL_Direction_3(const R::RT &hx, const R::RT &hy, const R::RT &hz)
    :  R::Direction_3(hx, hy, hz)
  {}

  CGAL_Direction_3<R> &operator=(const CGAL_Direction_3<R> &d)
  {
    R::Direction_3::operator=(d);
    return *this;
  }


  bool operator==(const CGAL_Direction_3<R> &d) const
  {
    return R::Direction_3::operator==(d);
  }

  bool operator!=(const CGAL_Direction_3<R> &d) const
  {
    return !(*this == d);
  }

  int id() const
  {
    return (int) PTR;
  }

  CGAL_Vector_3<R> vector() const
  {
    return (CGAL_Vector_3<R>)R::Direction_3::vector();
  }


  CGAL_Direction_3<R> transform(const CGAL_Aff_transformation_3<R> &t) const
  {
    return R::Direction_3::transform(R::Aff_transformation_3(t));
  }


  CGAL_Direction_3<R> operator-() const
  {
    return R::Direction_3::operator-();
  }

  R::RT delta(int i) const
  {
    return R::Direction_3::delta(i);
  }

  R::RT dx() const
  {
    return R::Direction_3::dx();
  }

  R::RT dy() const
  {
    return R::Direction_3::dy();
  }

  R::RT dz() const
  {
    return R::Direction_3::dz();
  }
};



#endif
