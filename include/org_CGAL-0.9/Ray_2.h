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


// Source:Ray_2.h
// Author: Andreas Fabri

#ifndef CGAL_RAY_2_H
#define CGAL_RAY_2_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#include <CGAL/Segment_2.h>

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/RayH2.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/RayC2.h>
#endif // CGAL_CARTESIAN_H

template <class _R>
class CGAL_Ray_2 : public _R::Ray_2
{
public:
  typedef  _R   R;
private:

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

#ifndef CGAL_NO_OSTREAM_INSERT_RAY_2
template < class R >
ostream &operator<<(ostream &os, const CGAL_Ray_2<R> &r)
{
    return os << (const R::Ray_2&)r;
}
#endif // CGAL_NO_OSTREAM_INSERT_RAY_2

#ifndef CGAL_NO_ISTREAM_EXTRACT_RAY_2
template < class R >
istream &operator>>(istream &is, CGAL_Ray_2<R> &r)
{
    return is >> (R::Ray_2&)r;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_RAY_2



#endif  // CGAL_RAY_2_H
