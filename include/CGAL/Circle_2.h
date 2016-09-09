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

// Source: Circle_2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_CIRCLE_2_H
#define CGAL_CIRCLE_2_H


#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/CircleH2.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/CircleC2.h>
#endif // CGAL_CARTESIAN_H

#include <CGAL/Point_2.h>

template <class R >
  class CGAL_Circle_2 : public R::Circle_2
{
public:
    CGAL_Circle_2()
      : R::Circle_2()
    {}

    CGAL_Circle_2(const CGAL_Circle_2<R> &t)
      : R::Circle_2((R::Circle_2&)t)
    {}

    CGAL_Circle_2(const R::Circle_2 &t)
      : R::Circle_2(t)
    {}

    CGAL_Circle_2(const CGAL_Point_2<R> &center,
                  const R::FT &squared_radius,
                  const CGAL_Orientation &orientation)
      : R::Circle_2(center, squared_radius, orientation)
    {}

    CGAL_Circle_2(const CGAL_Point_2<R> &center,
                  const R::FT &squared_radius)
      : R::Circle_2(center, squared_radius)
    {}

    CGAL_Circle_2(const CGAL_Point_2<R> &p,
                  const CGAL_Point_2<R> &q,
                  const CGAL_Point_2<R> &r)
      : R::Circle_2(p,q,r)
    {}

    CGAL_Circle_2(const CGAL_Point_2<R> & center,
                  const CGAL_Point_2<R> & p)
      : R::Circle_2(center, p)
    {}

    CGAL_Circle_2(const CGAL_Point_2<R> & center,
                  const CGAL_Point_2<R> & p,
                  const CGAL_Orientation& o)
      : R::Circle_2(center, p, o)
    {}


  CGAL_Circle_2<R>  &operator=(const CGAL_Circle_2<R> &t)
    {
      R::Circle_2::operator=(t);
      return *this;
    }

  bool                operator==(const CGAL_Circle_2<R> &t) const
    {
      return R::Circle_2::operator==(t);
    }

  bool                operator!=(const CGAL_Circle_2<R> &t) const
    {
      return !(*this == t);
    }

  int                 id() const
    {
      return (int)PTR;
    }

  CGAL_Point_2<R>     center() const
    {
      return R::Circle_2::center();
    }

  R::FT     squared_radius() const
    {
      return R::Circle_2::squared_radius();
    }

  CGAL_Orientation orientation() const
    {
      return R::Circle_2::orientation();
    }


  CGAL_Circle_2<R>
            orthogonal_transform(const CGAL_Aff_transformation_2<R> &t) const
  {
    return  R::Circle_2::orthogonal_transform(t);
  }

/*
  CGAL_Circle_2<R>  transform(const CGAL_Aff_transformation_2<R> &t) const
  {
    return  R::Circle_2::transform(t);
  }
*/

  CGAL_Oriented_side           oriented_side(const CGAL_Point_2<R> &p) const
    {
      return R::Circle_2::oriented_side(p);
    }

  CGAL_Bounded_side           bounded_side(const CGAL_Point_2<R> &p) const
    {
      return R::Circle_2::bounded_side(p);
    }

  bool                has_on_boundary(const CGAL_Point_2<R> &p) const
    {
      return R::Circle_2::has_on_boundary(p);
    }

  bool                has_on_positive_side(const CGAL_Point_2<R> &p) const
    {
      return R::Circle_2::has_on_positive_side(p);
    }

  bool                has_on_negative_side(const CGAL_Point_2<R> &p) const
    {
      return R::Circle_2::has_on_negative_side(p);
    }

  bool                has_on_bounded_side(const CGAL_Point_2<R> &p) const
    {
      return R::Circle_2::has_on_bounded_side(p);
    }

  bool                has_on_unbounded_side(const CGAL_Point_2<R> &p) const
    {
      return R::Circle_2::has_on_unbounded_side(p);
    }

  bool                is_degenerate() const
    {
      return R::Circle_2::is_degenerate();
    }

  CGAL_Circle_2<R>     opposite() const
    {
      return CGAL_Circle_2<R>(center(),
                              squared_radius(),
                              CGAL_opposite(orientation()));
    }

  CGAL_Bbox_2           bbox() const
    {
      return R::Circle_2::bbox();
    }
};



#endif  // CGAL_CIRCLE_2_H
