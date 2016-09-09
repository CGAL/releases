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

// Source: Parabola_arc_2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_PARABOLA_ARC_2_H
#define CGAL_PARABOLA_ARC_2_H

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/Parabola_arcH2.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/Parabola_arcC2.h>
#endif // CGAL_CARTESIAN_H

#include <CGAL/Parabola_2.h>

template < class R >
class CGAL_Parabola_arc_2 : public R::Parabola_arc_2
{
public:
  CGAL_Parabola_arc_2()
    : R::Parabola_arc_2()
  {}

  ~CGAL_Parabola_arc_2()
  {}

  CGAL_Parabola_arc_2(const CGAL_Parabola_arc_2  &l)
    : R::Parabola_arc_2((const R::Parabola_arc_2&)l)
  {}

//   CGAL_Parabola_arc_2(const CGAL_Parabola_2<R> &par,
//                       const CGAL_Point_2<R> &p,
//                       const CGAL_Point_2<R> &q)
//     : R::Parabola_arc_2(par, p, q)
//   {}

   CGAL_Parabola_arc_2(const CGAL_Parabola_2<R> &par,
                       const R::RT &lambda1,
                       const R::RT &lambda2)
    : R::Parabola_arc_2(par, lambda1, lambda2)
  {}

  // conversion impl -> interface class
  CGAL_Parabola_arc_2(const R::Parabola_arc_2 &l)
    : R::Parabola_arc_2(l)
  {}


  CGAL_Parabola_arc_2<R> &operator=(const CGAL_Parabola_arc_2<R> &l)
  {
    R::Parabola_arc_2::operator=(l);
    return *this;
  }

  bool operator==(const CGAL_Parabola_arc_2<R> &l) const
  {
    return R::Parabola_arc_2::operator==(l);
  }

  bool operator!=(const CGAL_Parabola_arc_2<R> &l) const
  {
    return !(*this == l);
  }

  int id() const
  {
    return (int) PTR ;
  }

  CGAL_Parabola_2<R> supporting_parabola() const
  {
    return R::Parabola_arc_2::supporting_parabola();
  }

  R::RT lambda_source() const
  {
    return R::Parabola_arc_2::lambda_source();
  }

  R::RT lambda_target() const
  {
    return R::Parabola_arc_2::lambda_target();
  }


  R::RT lambda(int i) const
  {
    return R::Parabola_arc_2::lambda(i);
  }

  CGAL_Point_2<R> source() const
  {
    return R::Parabola_arc_2::source();
  }

  CGAL_Point_2<R> target() const
  {
    return R::Parabola_arc_2::target();
  }

  CGAL_Point_2<R> vertex(int i) const
  {
    return R::Parabola_arc_2::vertex(i);
  }

  CGAL_Point_2<R> operator[](int i) const
  {
    return R::Parabola_arc_2::operator[](i);
  }

  bool is_on(const CGAL_Point_2<R> &p) const
  {
    return R::Parabola_arc_2::is_on(p);
  }

  bool is_degenerate() const
  {
    return R::Parabola_arc_2::is_degenerate();
  }

  CGAL_Parabola_arc_2<R> opposite() const
  {
    return R::Parabola_arc_2::opposite();
  }

  CGAL_Bbox_2  bbox() const
  {
    return R::Parabola_arc_2::bbox();
  }


  CGAL_Parabola_arc_2<R> transform(const CGAL_Aff_transformation_2<R> &t) const
  {
    return  R::Parabola_arc_2::transform(t);
  }
};



#endif  // CGAL_PARABOLA_ARC_2_H
