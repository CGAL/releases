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


// Source: Triangle_3.h
// Author: Andreas Fabri

#ifndef CGAL_TRIANGLE_3_H
#define CGAL_TRIANGLE_3_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED


#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/TriangleH3.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/TriangleC3.h>
#endif // CGAL_CARTESIAN_H

#include <CGAL/Plane_3.h>

template <class _R>
  class CGAL_Triangle_3 : public _R::Triangle_3
{
public:
  typedef  _R   R;
private:

public:
    CGAL_Triangle_3()
      : R::Triangle_3()
    {}

    CGAL_Triangle_3(const CGAL_Triangle_3<R> &t)
      : R::Triangle_3(t)
    {}

    CGAL_Triangle_3(const R::Triangle_3 &t)
      : R::Triangle_3(t)
    {}

    CGAL_Triangle_3(const CGAL_Point_3<R> &p,
                    const CGAL_Point_3<R> &q,
                    const CGAL_Point_3<R> &r)
      : R::Triangle_3(p,q,r)
    {}


  CGAL_Triangle_3<R>  &operator=(const CGAL_Triangle_3<R> &t)
  {
    R::Triangle_3::operator=(t);
    return *this;
  }

  bool                operator==(const CGAL_Triangle_3<R> &t) const
  {
    return R::Triangle_3::operator==(t);
  }

  bool                operator!=(const CGAL_Triangle_3<R> &t) const
    {
      return !(*this == t);
    }

  int                 id() const
    {
      return (int) PTR ;
    }

  CGAL_Plane_3<R>       supporting_plane() const
  {
    return CGAL_Plane_3<R>(R::Triangle_3::supporting_plane());
  }

  CGAL_Triangle_3<R>  transform(const R::Aff_transformation_3 &t) const
  {
    return  CGAL_Triangle_3<R>(R::Triangle_3::transform(t));
  }

  bool                has_on(const CGAL_Point_3<R> &p) const
  {
    return R::Triangle_3::has_on(p);
  }

  bool                is_degenerate() const
  {
    return R::Triangle_3::is_degenerate();
  }


  CGAL_Point_3<R>     vertex(int i) const
  {
    return R::Triangle_3::vertex(i);
  }

  CGAL_Point_3<R>     operator[](int i) const
    {
      return vertex(i);
    }

  CGAL_Bbox_3          bbox() const
    {
      return vertex(0).bbox() + vertex(1).bbox() + vertex(2).bbox();
    }
};

#ifndef CGAL_NO_OSTREAM_INSERT_TRIANGLE_3
template < class R >
ostream &operator<<(ostream &os, const CGAL_Triangle_3<R> &t)
{
    return os << (const R::Triangle_3&)t;
}
#endif // CGAL_NO_OSTREAM_INSERT_TRIANGLE_3

#ifndef CGAL_NO_ISTREAM_EXTRACT_TRIANGLE_3
template < class R >
istream &operator>>(istream &is, CGAL_Triangle_3<R> &t)
{
    return is >> (R::Triangle_3&)t;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_TRIANGLE_3





#endif
