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

// Source: Iso_rectangle_2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_ISO_RECTANGLE_2_H
#define CGAL_ISO_RECTANGLE_2_H

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/Iso_rectangleH2.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/Iso_rectangleC2.h>
#endif // CGAL_CARTESIAN_H

#include <CGAL/Point_2.h>

template <class R>
class CGAL_Iso_rectangle_2 : public R::Iso_rectangle_2
{
public:
  CGAL_Iso_rectangle_2()
    : R::Iso_rectangle_2()
  {}

  CGAL_Iso_rectangle_2(const CGAL_Iso_rectangle_2<R> &r)
    : R::Iso_rectangle_2(r)
  {}

  CGAL_Iso_rectangle_2(const R::Iso_rectangle_2 &r)
    : R::Iso_rectangle_2(r)
  {}

  CGAL_Iso_rectangle_2(const CGAL_Point_2<R> &p,
                       const CGAL_Point_2<R> &q)
    : R::Iso_rectangle_2(p,q)
  {}


  CGAL_Iso_rectangle_2<R>  &operator=(const CGAL_Iso_rectangle_2<R> &r)
  {
    R::Iso_rectangle_2::operator=(r);
    return *this;
  }

  bool  operator==(const CGAL_Iso_rectangle_2<R> &r) const
  {
    return  vertex(0) == r.vertex(0) && vertex(2) == r.vertex(2);
  }

  bool operator!=(const CGAL_Iso_rectangle_2<R> &r) const
  {
    return !(*this == r);
  }

  int id() const
  {
    return (int)PTR;
  }

  CGAL_Point_2<R> min() const
  {
    return R::Iso_rectangle_2::min();
  }

  CGAL_Point_2<R> max() const
  {
    return R::Iso_rectangle_2::max();
  }

  R::FT xmin() const
  {
    return R::Iso_rectangle_2::xmin();
  }

  R::FT ymin() const
  {
    return R::Iso_rectangle_2::ymin();
  }

  R::FT xmax() const
  {
    return R::Iso_rectangle_2::xmax();
  }

  R::FT ymax() const
  {
    return R::Iso_rectangle_2::ymax();
  }

  CGAL_Point_2<R> vertex(int i) const
  {
    return R::Iso_rectangle_2::vertex(i);
  }

  CGAL_Point_2<R> operator[](int i) const
  {
    return vertex(i);
  }

  CGAL_Bounded_side bounded_side(const CGAL_Point_2<R> &p) const
    {
      return R::Iso_rectangle_2::bounded_side(p);
    }

  bool has_on_boundary(const CGAL_Point_2<R> &p) const
    {
      return R::Iso_rectangle_2::has_on_boundary(p);
    }

  bool has_on_bounded_side(const CGAL_Point_2<R> &p) const
    {
      return R::Iso_rectangle_2::has_on_bounded_side(p);
    }

  bool has_on_unbounded_side(const CGAL_Point_2<R> &p) const
    {
      return R::Iso_rectangle_2::has_on_unbounded_side(p);
    }

  bool is_degenerate() const
  {
    return R::Iso_rectangle_2::is_degenerate();
  }

  CGAL_Iso_rectangle_2<R> transform(const CGAL_Aff_transformation_2<R> &t) const
  {
    return  R::Iso_rectangle_2::transform(t);
  }

};




#endif
