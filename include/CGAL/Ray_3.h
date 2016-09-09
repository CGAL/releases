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

// Source:Ray_3.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_Ray_3_H
#define CGAL_Ray_3_H

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/RayH3.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/RayC3.h>
#endif // CGAL_CARTESIAN_H

template < class R >
  class CGAL_Ray_3 : public R::Ray_3
{
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


#include <CGAL/Line_3.h>

#endif
