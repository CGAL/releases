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


// Source: Direction_2.h
// Author: Andreas Fabri

#ifndef CGAL_DIRECTION_2_H
#define CGAL_DIRECTION_2_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/DirectionH2.h>
#endif  // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/DirectionC2.h>
#endif // CGAL_CARTESIAN_H

#include <CGAL/Vector_2.h>

template <class _R>
class CGAL_Direction_2 : public _R::Direction_2
{
public:
  typedef  _R   R;
private:

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


  R::RT delta(int i) const
  {
    return R::Direction_2::delta(i);
  }

  R::RT dx() const
  {
    return R::Direction_2::dx();
  }

  R::RT dy() const
  {
    return R::Direction_2::dy();
  }
};


#ifndef CGAL_NO_OSTREAM_INSERT_DIRECTION_2
template < class R >
ostream &operator<<(ostream &os, const CGAL_Direction_2<R> &d)
{
    return os << (const R::Direction_2&)d;
}

#endif // CGAL_NO_OSTREAM_INSERT_DIRECTION_2

#ifndef CGAL_NO_ISTREAM_EXTRACT_DIRECTION_2
template < class R >
istream &operator>>(istream &is, CGAL_Direction_2<R> &p)
{
    return is >> (R::Direction_2&)p;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_DIRECTION_2



#endif // CGAL_DIRECTION_2_H
