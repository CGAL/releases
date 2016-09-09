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


// Source: Line_2.h
// Author: Andreas Fabri

#ifndef CGAL_LINE_2_H
#define CGAL_LINE_2_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/LineH2.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/LineC2.h>
#endif // CGAL_CARTESIAN_H

#include <CGAL/predicates_on_points_2.h>
#include <CGAL/Vector_2.h>

template <class _R>
class CGAL_Line_2 : public _R::Line_2
{
public:
  typedef  _R   R;
private:

public:
  CGAL_Line_2()
    : R::Line_2()
  {}

  ~CGAL_Line_2()
  {}

  CGAL_Line_2(const CGAL_Line_2<R>  &l)
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


  CGAL_Line_2(const CGAL_Segment_2<R>& s)
    : R::Line_2(s)
  {}

  CGAL_Line_2(const CGAL_Ray_2<R>& r)
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



#ifndef CGAL_NO_OSTREAM_INSERT_LINE_2
template < class R >
ostream &operator<<(ostream &os, const CGAL_Line_2<R> &l)
{
    return os << (const R::Line_2&)l;
}
#endif // CGAL_NO_OSTREAM_INSERT_LINE_2

#ifndef CGAL_NO_ISTREAM_EXTRACT_LINE_2
template < class R >
istream &operator>>(istream &is, CGAL_Line_2<R> &p)
{
    return is >> (R::Line_2&)p;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_LINE_2




#include <CGAL/Segment_2.h>
#include <CGAL/Ray_2.h>


#endif  // CGAL_LINE_2_H
