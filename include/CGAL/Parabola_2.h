 
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
    CGAL_kernel_precondition(l.is_defined());
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
    CGAL_kernel_precondition(l.is_defined());
  }


  CGAL_Parabola_2<R> &operator=(const CGAL_Parabola_2<R> &l)
  {
    CGAL_kernel_precondition(l.is_defined());
    R::Parabola_2::operator=(l);
    return *this;
  }

  bool operator==(const CGAL_Parabola_2<R> &l) const
  {
    CGAL_kernel_precondition(l.is_defined());
    return R::Parabola_2::operator==(l);
  }

  bool operator!=(const CGAL_Parabola_2<R> &l) const
  {
    return !(*this == l);
  }

  bool identical(const CGAL_Parabola_2<R> &l) const
  {
    CGAL_kernel_precondition(l.is_defined());
    return ( PTR == l.PTR );
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
    CGAL_kernel_precondition(is_defined());
    return R::Parabola_2::curvature();
  }


  CGAL_Parabola_2<R> opposite() const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Parabola_2::opposite();
  }

  CGAL_Point_2<R> operator()(const R::FT &lambda) const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Parabola_2::operator()(lambda);
  }

  int lambdas_at_x(const R::FT &x,
                   R::FT &lambda1,
                   R::FT &lambda2) const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Parabola_2::lambdas_at_x(x, lambda1, lambda2);
  }


  int lambdas_at_y(const R::FT &y,
                   R::FT &lambda1,
                   R::FT &lambda2) const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Parabola_2::lambdas_at_y(y, lambda1, lambda2);
  }

  R::FT x_at_lambda(const R::FT &lambda) const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Parabola_2::x_at_lambda(lambda);
  }

  R::FT y_at_lambda(const R::FT &lambda) const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Parabola_2::y_at_lambda(lambda);
  }

  CGAL_Point_2<R> projection(const CGAL_Point_2<R> &p) const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Parabola_2::projection(p);
  }

  CGAL_Point_2<R> projection(const CGAL_Point_2<R> &p, R::FT &lambda) const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Parabola_2::projection(p, lambda);
  }

  bool is_on(const CGAL_Point_2<R> &p) const
  {
    CGAL_kernel_precondition(is_defined() && p.is_defined());
    return R::Parabola_2::is_on(p);
  }

  bool is_degenerate() const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Parabola_2::is_degenerate();
  }
  /*
  CGAL_Parabola_2<R> transform(const CGAL_Aff_transformation_2<R> &t) const
  {
    CGAL_kernel_precondition(is_defined() && t.is_defined());
    return  CGAL_Parabola_2<R>(R::Parabola_2::transform(t));
  }
  */

#ifdef CGAL_CHECK_PRECONDITIONS
  bool             is_defined() const
  {
    return (PTR == NULL)? false : true;
  }
#endif

};
 



#endif  // CGAL_PARABOLA_2_H
