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


// Source: Line_3.h
// Author: Andreas Fabri

#ifndef CGAL_Line_3_H
#define CGAL_Line_3_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/LineH3.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/LineC3.h>
#endif // CGAL_CARTESIAN_H

#include <CGAL/Segment_3.h>
#include <CGAL/Point_3.h>
#include <CGAL/Ray_3.h>

template <class _R>
class CGAL_Line_3 : public _R::Line_3
{
public:
  typedef  _R   R;
private:

public:
                      CGAL_Line_3()
                        : R::Line_3()
                      {}

                      CGAL_Line_3(const CGAL_Line_3<R>  &l)
                        : R::Line_3((R::Line_3&)l)
                      {}

                      CGAL_Line_3(const CGAL_Point_3<R> &p,
                                  const CGAL_Point_3<R> &q)
                        : R::Line_3(p,q)
                      {}

                      // conversion impl -> interface class
                      CGAL_Line_3(const R::Line_3 &l)
                        : R::Line_3(l)
                      {}

                      CGAL_Line_3(const CGAL_Segment_3<R> &s)
                        : R::Line_3((R::Segment_3&)s)
                      {}

                      CGAL_Line_3(const CGAL_Ray_3<R> &r)
                        : R::Line_3((R::Ray_3&)r)
                      {}

                      CGAL_Line_3(const CGAL_Point_3<R> &p,
                                  const CGAL_Direction_3<R> &d)
                        : R::Line_3((R::Point_3&)p, (R::Direction_3&)d)
                      {}


  CGAL_Line_3<R>      &operator=(const CGAL_Line_3<R> &l)
  {
    R::Line_3::operator=(l);
    return *this;
  }

  bool                 operator==(const CGAL_Line_3<R> &l) const
  {
    return R::Line_3::operator==(l);
  }

  bool                 operator!=(const CGAL_Line_3<R> &l) const
  {
    return !(*this == l);
  }

  int                  id() const
  {
    return (int) PTR;
  }

  CGAL_Plane_3<R>     perpendicular_plane(const CGAL_Point_3<R> &p) const
  {
    return R::Line_3::perpendicular_plane(p);
  }

  CGAL_Line_3<R>      opposite() const
  {
    return R::Line_3::opposite();
  }

  CGAL_Point_3<R>     point() const
  {
    return R::Line_3::point();
  }

  CGAL_Point_3<R>     point(int i) const
  {
    return R::Line_3::point(i);
  }

  CGAL_Point_3<R>     projection(const CGAL_Point_3<R> &p) const
  {
    return R::Line_3::projection(p);
  }

  CGAL_Direction_3<R> direction() const
  {
    return R::Line_3::direction();
  }

  bool                 has_on(const CGAL_Point_3<R> &p) const
  {
    return R::Line_3::has_on(p);
  }

  bool                 is_degenerate() const
  {
    return R::Line_3::is_degenerate();
  }

  CGAL_Line_3<R>         transform(const CGAL_Aff_transformation_3<R> &t) const
  {
    return  R::Line_3::transform(t);
  }
};

#ifndef CGAL_NO_OSTREAM_INSERT_LINE_3
template < class R >
ostream &operator<<(ostream &os, const CGAL_Line_3<R> &l)
{
  return os << (const R::Line_3&)l;
}
#endif // CGAL_NO_OSTREAM_INSERT_LINE_3

#ifndef CGAL_NO_ISTREAM_EXTRACT_LINE_3
template < class R >
istream &operator>>(istream &is, CGAL_Line_3<R> &p)
{
  is >> (R::Line_3&)p;
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_LINE_3


#include <CGAL/Plane_3.h>

#endif // CGAL_Line_3_H
