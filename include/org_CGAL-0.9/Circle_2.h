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


// Source: Circle_2.h
// Author: Andreas Fabri
// Modified by: Sven Schoenherr (97-05-09)

#ifndef CGAL_CIRCLE_2_H
#define CGAL_CIRCLE_2_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED


#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/CircleH2.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/CircleC2.h>
#endif // CGAL_CARTESIAN_H

#include <CGAL/Point_2.h>

template <class _R>
  class CGAL_Circle_2 : public _R::Circle_2
{
public:
  typedef  _R   R;
private:

public:
    CGAL_Circle_2()
      : R::Circle_2()
    {}

    CGAL_Circle_2(const CGAL_Circle_2<R> &t)
      : R::Circle_2((R::Circle_2&)t)
    {}

    CGAL_Circle_2(const R::Circle_2 &t)
      : R::Circle_2(t)
    {}

    CGAL_Circle_2(const CGAL_Point_2<R> &center,
                  const R::FT &squared_radius,
                  const CGAL_Orientation &orientation)
      : R::Circle_2(center, squared_radius, orientation)
    {}

    CGAL_Circle_2(const CGAL_Point_2<R> &center,
                  const R::FT &squared_radius)
      : R::Circle_2(center, squared_radius, CGAL_COUNTERCLOCKWISE)
    {}

    CGAL_Circle_2(const CGAL_Point_2<R> &p,
                  const CGAL_Point_2<R> &q,
                  const CGAL_Point_2<R> &r)
      : R::Circle_2(p,q,r)
    {}

    CGAL_Circle_2(const CGAL_Point_2<R> & p,
                  const CGAL_Point_2<R> & q,
                  const CGAL_Orientation &orientation)
      : R::Circle_2(p,q,orientation)
    {}

    CGAL_Circle_2(const CGAL_Point_2<R> & p,
                  const CGAL_Point_2<R> & q)
      : R::Circle_2(p,q,CGAL_COUNTERCLOCKWISE)
    {}

    CGAL_Circle_2(const CGAL_Point_2<R> & center,
                  const CGAL_Orientation& orientation)
      : R::Circle_2(center,R::FT(0),orientation)
    {}

    CGAL_Circle_2(const CGAL_Point_2<R> & center)
      : R::Circle_2(center,R::FT(0),CGAL_COUNTERCLOCKWISE)
    {}


  CGAL_Circle_2<R>  &operator=(const CGAL_Circle_2<R> &t)
    {
      R::Circle_2::operator=(t);
      return *this;
    }

  bool                operator==(const CGAL_Circle_2<R> &t) const
    {
      return R::Circle_2::operator==(t);
    }

  bool                operator!=(const CGAL_Circle_2<R> &t) const
    {
      return !(*this == t);
    }

  int                 id() const
    {
      return (int)PTR;
    }

  CGAL_Point_2<R>     center() const
    {
      return R::Circle_2::center();
    }

  R::FT     squared_radius() const
    {
      return R::Circle_2::squared_radius();
    }

  CGAL_Orientation orientation() const
    {
      return R::Circle_2::orientation();
    }


  CGAL_Circle_2<R>
            orthogonal_transform(const CGAL_Aff_transformation_2<R> &t) const
  {
    return  R::Circle_2::orthogonal_transform(t);
  }

/*
  CGAL_Circle_2<R>  transform(const CGAL_Aff_transformation_2<R> &t) const
  {
    return  R::Circle_2::transform(t);
  }
*/

  CGAL_Oriented_side           oriented_side(const CGAL_Point_2<R> &p) const
    {
      return R::Circle_2::oriented_side(p);
    }

  CGAL_Bounded_side           bounded_side(const CGAL_Point_2<R> &p) const
    {
      return R::Circle_2::bounded_side(p);
    }

  bool                has_on_boundary(const CGAL_Point_2<R> &p) const
    {
      return R::Circle_2::has_on_boundary(p);
    }

  bool                has_on_positive_side(const CGAL_Point_2<R> &p) const
    {
      return R::Circle_2::has_on_positive_side(p);
    }

  bool                has_on_negative_side(const CGAL_Point_2<R> &p) const
    {
      return R::Circle_2::has_on_negative_side(p);
    }

  bool                has_on_bounded_side(const CGAL_Point_2<R> &p) const
    {
      return R::Circle_2::has_on_bounded_side(p);
    }

  bool                has_on_unbounded_side(const CGAL_Point_2<R> &p) const
    {
      return R::Circle_2::has_on_unbounded_side(p);
    }

  bool                is_degenerate() const
    {
      return R::Circle_2::is_degenerate();
    }

  CGAL_Circle_2<R>     opposite() const
    {
      return CGAL_Circle_2<R>(center(),
                              squared_radius(),
                              CGAL_opposite(orientation()));
    }

  CGAL_Bbox_2           bbox() const
    {
      return R::Circle_2::bbox();
    }
};


#ifndef CGAL_NO_OSTREAM_INSERT_CIRCLE_2
template < class R >
ostream &operator<<(ostream &os, const CGAL_Circle_2<R> &c)
{
    return os << (const R::Circle_2&)c;
}

#endif // CGAL_NO_OSTREAM_INSERT_CIRCLE_2

#ifndef CGAL_NO_ISTREAM_EXTRACT_CIRCLE_2
template < class R >
istream &operator>>(istream &is, CGAL_Circle_2<R> &c)
{
    return is >> (R::Circle_2&)c;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_CIRCLE_2




#endif  // CGAL_CIRCLE_2_H
