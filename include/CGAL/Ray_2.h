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

// Source:Ray_2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_RAY_2_H
#define CGAL_RAY_2_H

#include <CGAL/Segment_2.h>

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/RayH2.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/RayC2.h>
#endif // CGAL_CARTESIAN_H

template < class R >
class CGAL_Ray_2 : public R::Ray_2
{
public:
    CGAL_Ray_2()
      : R::Ray_2()
  {}

  ~CGAL_Ray_2()
  {}

  CGAL_Ray_2(const CGAL_Ray_2<R> &r)
    : R::Ray_2((const R::Ray_2&)r)
  {

  }

  CGAL_Ray_2(const R::Ray_2 &r)
    : R::Ray_2(r)
  {

  }

  CGAL_Ray_2(const CGAL_Point_2<R> &sp,
             const CGAL_Point_2<R> &secondp)
    : R::Ray_2(sp, secondp)
  {}

  CGAL_Ray_2(const CGAL_Point_2<R> &sp,
             const CGAL_Direction_2<R> &d)
    : R::Ray_2(sp, d)
  {}


  CGAL_Ray_2<R> &operator=(const CGAL_Ray_2<R> &r)
  {


    R::Ray_2::operator=(r);
    return *this;
  }

  bool operator==(const CGAL_Ray_2<R> &r) const
  {
    return R::Ray_2::operator==(r);
  }

  bool operator!=(const CGAL_Ray_2<R> &r) const
  {
    return !(*this == r);
  }

  int id() const
  {
    return (int) PTR ;
  }

  CGAL_Point_2<R> start() const
  {
    return R::Ray_2::start();
  }

  CGAL_Point_2<R> source() const
  {
    return R::Ray_2::source();
  }

  CGAL_Point_2<R> second_point() const
  {
    return R::Ray_2::second_point();
  }

  CGAL_Point_2<R> point(int i) const
  {
    return R::Ray_2::point(i);
  }

  CGAL_Direction_2<R> direction() const
  {
    return R::Ray_2::direction();
  }

  CGAL_Line_2<R> supporting_line() const
  {
    return R::Ray_2::supporting_line();
  }

  CGAL_Ray_2<R> opposite() const
  {
    return R::Ray_2::opposite();
  }


  CGAL_Ray_2<R> transform(const CGAL_Aff_transformation_2<R> &t) const
  {
    return R::Ray_2::transform(t);
  }


  bool is_horizontal() const
  {
    return R::Ray_2::is_horizontal();
  }

  bool is_vertical() const
  {
    return R::Ray_2::is_vertical();
  }

  bool is_degenerate() const
  {
    return R::Ray_2::is_degenerate();
  }

  bool has_on(const CGAL_Point_2<R> &p) const
  {
    return R::Ray_2::has_on(p);
  }
};


#endif  // CGAL_RAY_2_H
