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

// Source: Plane_3.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_PLANE_3_H
#define CGAL_PLANE_3_H

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/PlaneH3.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/PlaneC3.h>
#endif // CGAL_CARTESIAN_H

#include <CGAL/Line_3.h>
#include <CGAL/Point_2.h>

template < class R >
  class CGAL_Plane_3 : public R::Plane_3
{
public:
    CGAL_Plane_3()
      : R::Plane_3()
    {}

    CGAL_Plane_3(const CGAL_Plane_3<R> &p)
      : R::Plane_3(p)
    {}

    CGAL_Plane_3(const R::Plane_3 &p)
      : R::Plane_3(p)
    {}

    CGAL_Plane_3(const CGAL_Point_3<R> &p,
                 const CGAL_Point_3<R> &q,
                 const CGAL_Point_3<R> &r)
      : R::Plane_3(p,q,r)
    {}

    CGAL_Plane_3(const CGAL_Point_3<R> &p, const CGAL_Direction_3<R> &d)
      : R::Plane_3(p,d)
    {}

    CGAL_Plane_3(const CGAL_Point_3<R> &p, const CGAL_Vector_3<R> &v)
      : R::Plane_3(p,v)
    {}

    CGAL_Plane_3(const R::RT &a,
                 const R::RT &b,
                 const R::RT &c,
                 const R::RT &d)
      : R::Plane_3(a,b,c,d)
    {}

    CGAL_Plane_3(const CGAL_Line_3<R> &l, const CGAL_Point_3<R> &p)
      : R::Plane_3(l,p)
    {}

    CGAL_Plane_3(const CGAL_Segment_3<R> &s, const CGAL_Point_3<R> &p)
      : R::Plane_3(s,p)
    {}

    CGAL_Plane_3(CGAL_Ray_3<R> &r, const CGAL_Point_3<R> &p)
      : R::Plane_3(r,p)
    {}

 CGAL_Plane_3<R>       &operator=(const CGAL_Plane_3<R> &p)
  {
    R::Plane_3::operator=(p);
    return *this;
  }


  bool                  operator==(const CGAL_Plane_3<R> &p) const
    {
      return R::Plane_3::operator==(p);
    }

  bool                  operator!=(const CGAL_Plane_3<R> &p) const
    {
      return !(*this == p);
    }

  int                   id() const
    {
      return (int) PTR ;
    }

  R::RT a() const
    {
      return R::Plane_3::a();
    }

  R::RT                    b() const
    {
      return R::Plane_3::b();
    }

  R::RT                    c() const
    {
      return R::Plane_3::c();
    }

  R::RT                    d() const
    {
      return R::Plane_3::d();
    }


  CGAL_Line_3<R>       perpendicular_line(const CGAL_Point_3<R> &p) const
    {
      return R::Plane_3::perpendicular_line(p);
    }

  CGAL_Plane_3<R>           opposite() const
  {
    return R::Plane_3::opposite();
  }

  CGAL_Point_3<R>      point() const
    {
      return R::Plane_3::point();
    }

  CGAL_Vector_3<R>      orthogonal_vector() const
    {
      return R::Plane_3::orthogonal_vector();
    }

  CGAL_Direction_3<R>   orthogonal_direction() const
    {
      return R::Plane_3::orthogonal_direction();
    }

  CGAL_Vector_3<R>      base1() const
    {
      return R::Plane_3::base1();
    }

  CGAL_Vector_3<R>      base2() const
    {
      return R::Plane_3::base2();
    }

    /*
  CGAL_Point_3<R>       to_plane_basis(const CGAL_Point_3<R> &p) const
    {
      return R::Plane_3::to_plane_basis(p);
    }
    */

  CGAL_Point_2<R>        to_2d(const CGAL_Point_3<R> &p) const
    {
      return R::Plane_3::to_2d(p);
    }

  CGAL_Point_3<R>       to_3d(const CGAL_Point_2<R> &p) const
    {
      return R::Plane_3::to_3d(p);
    }


  CGAL_Plane_3<R>           transform( CGAL_Aff_transformation_3<R> &t) const
  {
    return  CGAL_Plane_3<R>(R::Plane_3::transform(t));
  }


  CGAL_Oriented_side             oriented_side(const CGAL_Point_3<R> &p) const
  {
    return R::Plane_3::oriented_side(p);
  }

  bool                  has_on(const  CGAL_Point_3<R> &p) const
  {
    return R::Plane_3::has_on_boundary(p);
  }

  bool                  has_on(const  CGAL_Line_3<R> &l) const
  {
    return R::Plane_3::has_on_boundary(l);
  }

  bool                  has_on_boundary(const  CGAL_Point_3<R> &p) const
  {
    return R::Plane_3::has_on_boundary(p);
  }

  bool                  has_on_boundary(const  CGAL_Line_3<R> &l) const
  {
    return R::Plane_3::has_on_boundary(l);
  }

  bool                  has_on_positive_side(const  CGAL_Point_3<R> &p) const
  {
    return R::Plane_3::has_on_positive_side(p);
  }

  bool                  has_on_negative_side(const  CGAL_Point_3<R> &p) const
  {
    return R::Plane_3::has_on_negative_side(p);
  }

  bool                  is_degenerate() const
  {
    return R::Plane_3::is_degenerate();
  }
};


#endif // CGAL_PLANE_3_H
