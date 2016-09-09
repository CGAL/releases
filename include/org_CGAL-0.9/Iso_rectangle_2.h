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


// Source: Iso_rectangle_2.h
// Author: Andreas Fabri

#ifndef CGAL_ISO_RECTANGLE_2_H
#define CGAL_ISO_RECTANGLE_2_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/Iso_rectangleH2.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/Iso_rectangleC2.h>
#endif // CGAL_CARTESIAN_H

#include <CGAL/Point_2.h>

template <class _R>
class CGAL_Iso_rectangle_2 : public _R::Iso_rectangle_2
{
public:
  typedef  _R   R;
private:

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

#ifndef CGAL_NO_OSTREAM_INSERT_ISO_RECTANGLE_2
template < class R >
ostream &operator<<(ostream &os, const CGAL_Iso_rectangle_2<R> &r)
{
    return  os << (const R::Iso_rectangle_2&)r;
}
#endif // CGAL_NO_OSTREAM_INSERT_ISO_RECTANGLE_2

#ifndef CGAL_NO_ISTREAM_EXTRACT_ISO_RECTANGLE_2
template < class R >
istream &operator>>(istream &is, CGAL_Iso_rectangle_2<R> &r)
{
  is >> (R::Iso_rectangle_2&)r;
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_ISO_RECTANGLE_2





#endif
