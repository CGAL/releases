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


// Source: Direction_3.h
// Author: Andreas Fabri

#ifndef CGAL_DIRECTION_3_H
#define CGAL_DIRECTION_3_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/DirectionH3.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/DirectionC3.h>
#endif // CGAL_CARTESIAN_H

#include <CGAL/Vector_3.h>

template <class _R>
class CGAL_Direction_3 : public _R::Direction_3
{
public:
  typedef  _R   R;
private:

public:
  CGAL_Direction_3()
  {}

  CGAL_Direction_3(const CGAL_Direction_3<R>& d)
    : R::Direction_3((R::Direction_3&)d)
  {}

  CGAL_Direction_3(const R::Direction_3& d)
    : R::Direction_3(d)
  {}


  CGAL_Direction_3(const R::Vector_3& v)
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


#ifndef CGAL_NO_OSTREAM_INSERT_DIRECTION_3
template < class R >
ostream &operator<<(ostream &os, const CGAL_Direction_3<R> &d)
{
    return os << (const R::Direction_3&)d;
}
#endif // CGAL_NO_OSTREAM_INSERT_DIRECTION_3


#ifndef CGAL_NO_ISTREAM_EXTRACT_DIRECTION_3
template < class R >
istream &operator>>(istream &is, CGAL_Direction_3<R> &p)
{
    return is >> (R::Direction_3&)p;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_DIRECTION_3



#endif
