 
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
  {
    CGAL_kernel_precondition(l.is_defined());
  }


  CGAL_Parabola_arc_2<R> &operator=(const CGAL_Parabola_arc_2<R> &l)
  {
    CGAL_kernel_precondition(l.is_defined());
    R::Parabola_arc_2::operator=(l);
    return *this;
  }

  bool operator==(const CGAL_Parabola_arc_2<R> &l) const
  {
    CGAL_kernel_precondition(l.is_defined());
    return R::Parabola_arc_2::operator==(l);
  }

  bool operator!=(const CGAL_Parabola_arc_2<R> &l) const
  {
    return !(*this == l);
  }

  bool identical(const CGAL_Parabola_arc_2<R> &l) const
  {
    CGAL_kernel_precondition(l.is_defined());
    return ( PTR == l.PTR );
  }

  CGAL_Parabola_2<R> supporting_parabola() const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Parabola_arc_2::supporting_parabola();
  }

  R::RT lambda_start() const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Parabola_arc_2::lambda_start();
  }

  R::RT lambda_end() const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Parabola_arc_2::lambda_end();
  }


  R::RT lambda(int i) const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Parabola_arc_2::lambda(i);
  }

  CGAL_Point_2<R> start() const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Parabola_arc_2::start();
  }

  CGAL_Point_2<R> end() const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Parabola_arc_2::end();
  }

  CGAL_Point_2<R> vertex(int i) const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Parabola_arc_2::vertex(i);
  }

  CGAL_Point_2<R> operator[](int i) const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Parabola_arc_2::operator[](i);
  }

  bool is_on(const CGAL_Point_2<R> &p) const
  {
    CGAL_kernel_precondition(is_defined() && p.is_defined());
    return R::Parabola_arc_2::is_on(p);
  }

  bool is_degenerate() const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Parabola_arc_2::is_degenerate();
  }

  CGAL_Parabola_arc_2<R> opposite() const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Parabola_arc_2::opposite();
  }

  CGAL_Bbox_2  bbox() const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Parabola_arc_2::bbox();
  }

  /*
  CGAL_Parabola_arc_2<R> transform(const CGAL_Aff_transformation_2<R> &t) const
  {
    CGAL_kernel_precondition(is_defined() && t.is_defined());
    return  CGAL_Parabola_arc_2<R>(R::Parabola_arc_2::transform(t));
  }
  */

#ifdef CGAL_CHECK_PRECONDITIONS
  bool             is_defined() const
  {
    return (PTR == NULL)? false : true;
  }
#endif

};
 



#endif  // CGAL_PARABOLA_ARC_2_H
