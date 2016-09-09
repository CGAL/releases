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


// Source: Tetrahedron_3.h
// Author: Andreas Fabri

#ifndef CGAL_TETRAHEDRON_3_H
#define CGAL_TETRAHEDRON_3_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/TetrahedronH3.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/TetrahedronC3.h>
#endif // CGAL_CARTESIAN_H

#include <CGAL/Plane_3.h>


template <class _R>
  class CGAL_Tetrahedron_3 : public _R::Tetrahedron_3
{
public:
  typedef  _R   R;
private:

public:
    CGAL_Tetrahedron_3()
      : R::Tetrahedron_3()
    {}

    CGAL_Tetrahedron_3(const CGAL_Tetrahedron_3<R> &t)
      : R::Tetrahedron_3(t)
    {}

    CGAL_Tetrahedron_3(const R::Tetrahedron_3 &t)
      : R::Tetrahedron_3(t)
    {}

    CGAL_Tetrahedron_3(const CGAL_Point_3<R> &p,
                       const CGAL_Point_3<R> &q,
                       const CGAL_Point_3<R> &r,
                       const CGAL_Point_3<R> &s)
      : R::Tetrahedron_3(p,q,r,s)
    {}

  CGAL_Tetrahedron_3<R> &operator=(const CGAL_Tetrahedron_3<R> &t)
  {
    R::Tetrahedron_3::operator=(t);
    return *this;
  }

  CGAL_Point_3<R>    vertex(int i) const
  {
    return R::Tetrahedron_3::vertex(i);
  }

  CGAL_Point_3<R>    operator[](int i) const
  {
    return vertex(i);
  }

  bool                operator==(const CGAL_Tetrahedron_3<R> &t) const
    {
      return R::Tetrahedron_3::operator==(t);
    }

  bool                operator!=(const CGAL_Tetrahedron_3<R> &t) const
    {
      return !(*this == t);
    }

  int                 id() const
    {
      return (int)PTR ;
    }

  CGAL_Bbox_3          bbox() const
    {
      return vertex(0).bbox() + vertex(1).bbox()
             + vertex(2).bbox() + vertex(3).bbox();
    }


  CGAL_Tetrahedron_3<R>  transform(const R::Aff_transformation_3 &t) const
  {
    return  CGAL_Tetrahedron_3<R>(R::Tetrahedron_3::transform(t));
  }


  CGAL_Orientation orientation() const
    {
      return R::Tetrahedron_3::orientation();
    }

  CGAL_Oriented_side  oriented_side(const CGAL_Point_3<R> &p) const
    {
      return R::Tetrahedron_3::oriented_side(p);
    }

  bool                has_on_positive_side(const CGAL_Point_3<R> &p) const
    {
      return oriented_side(p) == CGAL_ON_POSITIVE_SIDE;
    }

  bool                has_on_negative_side(const CGAL_Point_3<R> &p) const
    {
      return oriented_side(p) == CGAL_ON_NEGATIVE_SIDE;
    }

  CGAL_Bounded_side  bounded_side(const CGAL_Point_3<R> &p) const
    {
      return R::Tetrahedron_3::bounded_side(p);
    }

  bool                has_on_boundary(const CGAL_Point_3<R> &p) const
    {
      return bounded_side(p) == CGAL_ON_BOUNDARY;
    }

  bool                has_on_bounded_side(const CGAL_Point_3<R> &p) const
    {
      return bounded_side(p) == CGAL_ON_BOUNDED_SIDE;
    }

  bool                has_on_unbounded_side(const CGAL_Point_3<R> &p) const
    {
      return bounded_side(p) == CGAL_ON_UNBOUNDED_SIDE;
    }

  bool                is_degenerate() const
    {
      return R::Tetrahedron_3::is_degenerate();
    }

};

#ifndef CGAL_NO_OSTREAM_INSERT_TETRAHEDRON_3
template < class R >
ostream &operator<<(ostream &os, const CGAL_Tetrahedron_3<R> &t)
{
    return os << (const R::Tetrahedron_3&)t;
}
#endif // CGAL_NO_OSTREAM_INSERT_TETRAHEDRON_3

#ifndef CGAL_NO_ISTREAM_EXTRACT_TETRAHEDRON_3
template < class R >
istream &operator>>(istream &is, CGAL_Tetrahedron_3<R> &t)
{
    return is >> (R::Tetrahedron_3&)t;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_TETRAHEDRON_3



#endif  // CGAL_TETRAHEDRON_3_H
