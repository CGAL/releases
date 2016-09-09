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

// Source: Triangle_2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_TRIANGLE_2_H
#define CGAL_TRIANGLE_2_H


#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/TriangleH2.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/TriangleC2.h>
#endif // CGAL_CARTESIAN_H

#include <CGAL/Point_2.h>

template <class R >
  class CGAL_Triangle_2 : public R::Triangle_2
{
public:
    CGAL_Triangle_2()
      : R::Triangle_2()
    {}

    CGAL_Triangle_2(const CGAL_Triangle_2<R> &t)
      : R::Triangle_2((R::Triangle_2&)t)
    {}

    CGAL_Triangle_2(const R::Triangle_2 &t)
      : R::Triangle_2(t)
    {}

    CGAL_Triangle_2(const CGAL_Point_2<R> &p,
                    const CGAL_Point_2<R> &q,
                    const CGAL_Point_2<R> &r)
      : R::Triangle_2(p,q,r)
    {}


  CGAL_Triangle_2<R>  &operator=(const CGAL_Triangle_2<R> &t)
    {
      R::Triangle_2::operator=(t);
      return *this;
    }

  bool                operator==(const CGAL_Triangle_2<R> &t) const
    {
      return R::Triangle_2::operator==(t);
    }

  bool                operator!=(const CGAL_Triangle_2<R> &t) const
    {
      return !(*this == t);
    }

  int                id() const
    {
      return (int) PTR;
    }


  CGAL_Point_2<R>     vertex(int i) const
    {
      return R::Triangle_2::vertex(i);
    }

  CGAL_Point_2<R>     operator[](int i) const
    {
      return vertex(i);
    }


  CGAL_Triangle_2<R>  transform(const CGAL_Aff_transformation_2<R> &t) const
  {
    return  R::Triangle_2::transform(t);
  }

  CGAL_Triangle_2<R>  opposite() const
  {
    return  CGAL_Triangle_2<R>(vertex(0), vertex(2), vertex(1));
  }

  CGAL_Orientation  orientation() const
    {
      return R::Triangle_2::orientation();
    }

  CGAL_Oriented_side           oriented_side(const CGAL_Point_2<R> &p) const
    {
      return R::Triangle_2::oriented_side(p);
    }

  CGAL_Bounded_side           bounded_side(const CGAL_Point_2<R> &p) const
    {
      return R::Triangle_2::bounded_side(p);
    }

  bool                has_on_boundary(const CGAL_Point_2<R> &p) const
    {
      return R::Triangle_2::has_on_boundary(p);
    }

  bool                has_on_positive_side(const CGAL_Point_2<R> &p) const
    {
      return R::Triangle_2::has_on_positive_side(p);
    }

  bool                has_on_negative_side(const CGAL_Point_2<R> &p) const
    {
      return R::Triangle_2::has_on_negative_side(p);
    }

  bool                has_on_unbounded_side(const CGAL_Point_2<R> &p) const
    {
      return R::Triangle_2::has_on_unbounded_side(p);
    }

  bool                has_on_bounded_side(const CGAL_Point_2<R> &p) const
    {
      return R::Triangle_2::has_on_bounded_side(p);
    }

  bool                is_degenerate() const
    {
      return R::Triangle_2::is_degenerate();
    }

  CGAL_Bbox_2           bbox() const
    {
      return vertex(0).bbox() + vertex(1).bbox() + vertex(2).bbox();
    }
};



#endif
