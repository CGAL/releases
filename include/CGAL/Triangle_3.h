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

// Source: Triangle_3.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_TRIANGLE_3_H
#define CGAL_TRIANGLE_3_H


#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/TriangleH3.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/TriangleC3.h>
#endif // CGAL_CARTESIAN_H

#include <CGAL/Plane_3.h>

template <class R >
  class CGAL_Triangle_3 : public R::Triangle_3
{
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



#endif
