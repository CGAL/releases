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

// Source: Line_3.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_Line_3_H
#define CGAL_Line_3_H

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/LineH3.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/LineC3.h>
#endif // CGAL_CARTESIAN_H

#include <CGAL/Segment_3.h>
#include <CGAL/Point_3.h>
#include <CGAL/Ray_3.h>

template < class R >
class CGAL_Line_3 : public R::Line_3
{
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


#include <CGAL/Plane_3.h>

#endif // CGAL_Line_3_H
