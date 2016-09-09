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

// Source: Line_2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_LINE_2_H
#define CGAL_LINE_2_H

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/LineH2.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/LineC2.h>
#endif // CGAL_CARTESIAN_H

#include <CGAL/predicates_on_points_2.h>
#include <CGAL/Vector_2.h>

template < class R >
class CGAL_Line_2 : public R::Line_2
{
public:
  CGAL_Line_2()
    : R::Line_2()
  {}

  ~CGAL_Line_2()
  {}

  CGAL_Line_2(const CGAL_Line_2  &l)
    : R::Line_2((R::Line_2&)l)
  {}

  CGAL_Line_2(const CGAL_Point_2<R> &p, const CGAL_Point_2<R> &q)
    : R::Line_2(p,q)
  {}

  CGAL_Line_2(const R::RT &a, const R::RT &b, const R::RT &c)
    : R::Line_2(a,b,c)
  {}


  CGAL_Line_2(const R::Line_2 &l)  // conversion impl -> interface class
    : R::Line_2(l)
  {}


  CGAL_Line_2(const CGAL_Segment_2<R> &s)
    : R::Line_2(s)
  {}

  CGAL_Line_2(const CGAL_Ray_2<R> &r)
    : R::Line_2((const R::Ray_2&)r)
  {}

  CGAL_Line_2(const CGAL_Point_2<R> &p, const CGAL_Direction_2<R> &d)
    : R::Line_2(p,d)
  {}


  CGAL_Line_2<R> &operator=(const CGAL_Line_2<R> &l)
  {
    R::Line_2::operator=(l);
    return *this;
  }

  bool operator==(const CGAL_Line_2<R> &l) const
  {
    return R::Line_2::operator==(l);
  }

  bool operator!=(const CGAL_Line_2<R> &l) const
  {
    return !(*this == l);
  }

  int id() const
  {
    return (int) PTR;
  }

  R::RT a() const
  {
    return R::Line_2::a();
  }

  R::RT b() const
  {
    return R::Line_2::b();
  }

  R::RT c() const
  {
    return R::Line_2::c();
  }


  R::FT x_at_y(const R::FT &y) const
  {
    return R::Line_2::x_at_y(y);
  }

  R::FT y_at_x(const R::FT &x) const
  {
    return R::Line_2::y_at_x(x);
  }

  CGAL_Line_2<R> perpendicular(const CGAL_Point_2<R> &p) const
  {
    return R::Line_2::perpendicular(p);
  }

  CGAL_Line_2<R> opposite() const
  {
    return R::Line_2::opposite();
  }

  CGAL_Point_2<R> point(int i) const
  {
    return R::Line_2::point(i);
  }

  CGAL_Point_2<R> projection(const CGAL_Point_2<R> &p) const
  {
    return R::Line_2::projection(p);
  }

  CGAL_Point_2<R> point() const
  {
    return R::Line_2::point();
  }

  CGAL_Direction_2<R> direction() const
  {

    return R::Line_2::direction();
  }

  CGAL_Oriented_side oriented_side(const CGAL_Point_2<R> &p) const
  {
    return R::Line_2::oriented_side(p);
  }

  bool has_on(const CGAL_Point_2<R> &p) const
  {
    return R::Line_2::has_on_boundary(p);
  }

  bool has_on_boundary(const CGAL_Point_2<R> &p) const
  {
    return R::Line_2::has_on_boundary(p);
  }

  bool has_on_positive_side(const CGAL_Point_2<R> &p) const
  {
    return R::Line_2::has_on_positive_side(p);
  }

  bool has_on_negative_side(const CGAL_Point_2<R> &p) const
  {
    return R::Line_2::has_on_negative_side(p);
  }

  bool is_horizontal() const
  {

    return R::Line_2::is_horizontal();
  }

  bool is_vertical() const
  {

    return R::Line_2::is_vertical();
  }

  bool is_degenerate() const
  {

    return R::Line_2::is_degenerate();
  }

  CGAL_Line_2<R> transform(const CGAL_Aff_transformation_2<R> &t) const
  {
    return  R::Line_2::transform(t);
  }
};


#include <CGAL/Segment_2.h>
#include <CGAL/Ray_2.h>


#endif  // CGAL_LINE_2_H
