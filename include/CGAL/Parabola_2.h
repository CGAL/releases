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

// Source: Parabola_2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_PARABOLA_2_H
#define CGAL_PARABOLA_2_H

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/ParabolaH2.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/ParabolaC2.h>
#endif // CGAL_CARTESIAN_H

#include <CGAL/Vector_2.h>

template < class R >
class CGAL_Parabola_2 : public R::Parabola_2
{
public:
  CGAL_Parabola_2()
    : R::Parabola_2()
  {}


  ~CGAL_Parabola_2()
  {}

  CGAL_Parabola_2(const CGAL_Parabola_2  &l)
    : R::Parabola_2((R::Parabola_2&)l)
  {

  }

  CGAL_Parabola_2(const CGAL_Point_2<R> &p,
                  const CGAL_Vector_2<R> &v,
                  const R::RT &c)
    : R::Parabola_2(p, v, c)
  {}


  CGAL_Parabola_2(const CGAL_Line_2<R> &l, const CGAL_Point_2<R> &p)
    : R::Parabola_2(l,p)
  {}


  CGAL_Parabola_2(const R::Parabola_2 &l) // conversion impl -> interface class
    : R::Parabola_2(l)
  {

  }


  CGAL_Parabola_2<R> &operator=(const CGAL_Parabola_2<R> &l)
  {

    R::Parabola_2::operator=(l);
    return *this;
  }

  bool operator==(const CGAL_Parabola_2<R> &l) const
  {

    return R::Parabola_2::operator==(l);
  }

  bool operator!=(const CGAL_Parabola_2<R> &l) const
  {
    return !(*this == l);
  }

  int id() const
  {
    return (int) PTR ;
  }

  CGAL_Point_2<R> base() const
  {
    return R::Parabola_2::base();
  }

  CGAL_Point_2<R> focus() const
  {
    return R::Parabola_2::focus();
  }

  CGAL_Line_2<R> director() const
  {
    return R::Parabola_2::director();
  }

  CGAL_Vector_2<R> vector() const
  {
    return R::Parabola_2::vector();
  }

  R::RT curvature() const
  {
    return R::Parabola_2::curvature();
  }


  CGAL_Parabola_2<R> opposite() const
  {
    return R::Parabola_2::opposite();
  }

  CGAL_Point_2<R> operator()(const R::FT &lambda) const
  {
    return R::Parabola_2::operator()(lambda);
  }

  int lambdas_at_x(const R::FT &x,
                   R::FT &lambda1,
                   R::FT &lambda2) const
  {
    return R::Parabola_2::lambdas_at_x(x, lambda1, lambda2);
  }


  int lambdas_at_y(const R::FT &y,
                   R::FT &lambda1,
                   R::FT &lambda2) const
  {
    return R::Parabola_2::lambdas_at_y(y, lambda1, lambda2);
  }

  R::FT x_at_lambda(const R::FT &lambda) const
  {
    return R::Parabola_2::x_at_lambda(lambda);
  }

  R::FT y_at_lambda(const R::FT &lambda) const
  {
    return R::Parabola_2::y_at_lambda(lambda);
  }

  CGAL_Point_2<R> projection(const CGAL_Point_2<R> &p) const
  {
    return R::Parabola_2::projection(p);
  }

  CGAL_Point_2<R> projection(const CGAL_Point_2<R> &p, R::FT &lambda) const
  {
    return R::Parabola_2::projection(p, lambda);
  }

  CGAL_Oriented_side oriented_side(const CGAL_Point_2<R> &p) const
  {
    return R::Parabola_2::oriented_side(p);
  }

  bool has_on_positive_side(const CGAL_Point_2<R> &p) const
  {
    return R::Parabola_2::has_on_positive_side(p);
  }

  bool has_on_negative_side(const CGAL_Point_2<R> &p) const
  {
    return R::Parabola_2::has_on_negative_side(p);
  }

  bool has_on_boundary(const CGAL_Point_2<R> &p) const
  {
    return R::Parabola_2::has_on_boundary(p);
  }

  bool is_degenerate() const
  {
      return R::Parabola_2::is_degenerate();
  }

  CGAL_Parabola_2<R> transform(const CGAL_Aff_transformation_2<R> &t) const
  {
    return  R::Parabola_2::transform(t);
  }

};



#endif  // CGAL_PARABOLA_2_H
