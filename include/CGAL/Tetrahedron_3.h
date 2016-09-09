//  Copyright CGAL 1996
//
//  cgal@cs.ruu.nl
//
//  This file is part of an internal release of the CGAL kernel.
//  The code herein may be used and/or copied only in accordance
//  with the terms and conditions stipulated in the agreement
//  under which the code has been supplied or with the written
//  permission of the CGAL Project.
//
//  Look at http://www.cs.ruu.nl/CGAL/ for more information.
//  Please send any bug reports and comments to cgal@cs.ruu.nl
//
//  The code comes WITHOUT ANY WARRANTY; without even the implied
//  warranty of FITNESS FOR A PARTICULAR PURPOSE.
//

// Source: Tetrahedron_3.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_TETRAHEDRON_3_H
#define CGAL_TETRAHEDRON_3_H

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/TetrahedronH3.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/TetrahedronC3.h>
#endif // CGAL_CARTESIAN_H

#include <CGAL/Plane_3.h>


template <class R>
  class CGAL_Tetrahedron_3 : public R::Tetrahedron_3
{
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


#endif  // CGAL_TETRAHEDRON_3_H
