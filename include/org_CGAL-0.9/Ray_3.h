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


// Source:Ray_3.h
// Author: Andreas Fabri

#ifndef CGAL_Ray_3_H
#define CGAL_Ray_3_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/RayH3.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/RayC3.h>
#endif // CGAL_CARTESIAN_H

template <class _R>
  class CGAL_Ray_3 : public _R::Ray_3
{
public:
  typedef  _R   R;
private:

public:
                      CGAL_Ray_3()
                        : R::Ray_3()
                      {}

                      CGAL_Ray_3(const CGAL_Ray_3<R> &r)
                        : R::Ray_3(r)
                      {}

                      CGAL_Ray_3(const R::Ray_3 &r)
                        : R::Ray_3(r)
                      {}

                      CGAL_Ray_3(const CGAL_Point_3<R> &sp,
                                const CGAL_Point_3<R> &secondp)
                        : R::Ray_3(sp, secondp)
                      {}

                      CGAL_Ray_3(const CGAL_Point_3<R> &sp,
                                const CGAL_Direction_3<R> &d)
                        : R::Ray_3(sp, d)
                      {}

  CGAL_Ray_3<R>       &operator=(const CGAL_Ray_3<R> &r)
    {
      R::Ray_3::operator=(r);
      return *this;
    }

  bool                 operator==(const CGAL_Ray_3<R> &r) const
    {
      return R::Ray_3::operator==(r);
    }

  bool                 operator!=(const CGAL_Ray_3<R> &r) const
    {
      return !(*this == r);
    }

  int                  id() const
    {
      return (int)  PTR ;
    }

  CGAL_Point_3<R>     start() const
    {
      return R::Ray_3::start();
    }

  CGAL_Point_3<R>     source() const
    {
      return R::Ray_3::source();
    }


  CGAL_Point_3<R>     second_point() const
    {
      return R::Ray_3::second_point();
    }

  CGAL_Point_3<R>     point(int i) const
    {
      return R::Ray_3::point(i);
    }

  CGAL_Direction_3<R> direction() const
    {
      return R::Ray_3::direction();
    }


  CGAL_Line_3<R>      supporting_line() const
    {
      return R::Ray_3::supporting_line();
    }

  CGAL_Ray_3<R>       opposite() const
    {
      return R::Ray_3::opposite();
    }


  CGAL_Ray_3<R>       transform(const CGAL_Aff_transformation_3<R> &t) const
  {
    return  R::Ray_3::transform(t);
  }


  bool                 is_degenerate() const
    {
      return R::Ray_3::is_degenerate();
    }

  bool                 has_on(const CGAL_Point_3<R> &p) const
    {
      return R::Ray_3::has_on(p);
    }

};

#ifndef CGAL_NO_OSTREAM_INSERT_RAY_3
template < class R >
ostream &operator<<(ostream &os, const CGAL_Ray_3<R> &r)
{
    return os << (const R::Ray_3&)r;
}
#endif // CGAL_NO_OSTREAM_INSERT_RAY_3

#ifndef CGAL_NO_ISTREAM_EXTRACT_RAY_3
template < class R >
istream &operator>>(istream &is, CGAL_Ray_3<R> &r)
{
    return is >> (R::Ray_3&)r;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_RAY_3



#include <CGAL/Line_3.h>

#endif
