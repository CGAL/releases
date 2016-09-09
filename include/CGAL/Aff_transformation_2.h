// Source: Aff_transformation_2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_AFF_TRANSFORMATION_2_H
#define CGAL_AFF_TRANSFORMATION_2_H

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/Aff_transformationH2.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/Aff_transformationC2.h>
#endif // CGAL_CARTESIAN_H

template < class R >
class CGAL_Aff_transformation_2 : public R::Aff_transformation_2
{
public:
  // default constructor
  CGAL_Aff_transformation_2()
    : R::Aff_transformation_2()
  {}

  // copy constructor
  CGAL_Aff_transformation_2(const CGAL_Aff_transformation_2<R> &t)
    : R::Aff_transformation_2(t)
  {}

  // up cast constructor
  CGAL_Aff_transformation_2(const R::Aff_transformation_2 &t)
    : R::Aff_transformation_2(t)
  {}

  // Translation:
  CGAL_Aff_transformation_2(const CGAL_Translation tag,
                            const CGAL_Vector_2<R> &v)
    : R::Aff_transformation_2(tag, v)
  {}

  // Rational Rotation:
  CGAL_Aff_transformation_2(const CGAL_Rotation tag,
                            const CGAL_Direction_2<R> &d,
                            const R::RT &num,
                            const R::RT &den = R::RT(1))
    : R::Aff_transformation_2(tag, R::Direction_2(d), num, den)
  {}

  CGAL_Aff_transformation_2(const CGAL_Rotation tag,
                            const R::RT &sine,
                            const R::RT &cosine,
                            const R::RT &denominator = R::RT(1))
    : R::Aff_transformation_2(tag, sine, cosine, denominator)
  {}

  // Scaling:
  CGAL_Aff_transformation_2(const CGAL_Scaling tag,
                            const R::RT &s,
                            const R::RT &w= R::RT(1))
    : R::Aff_transformation_2(tag, s, w)
  {}

  // The general case:
  CGAL_Aff_transformation_2(const R::RT & m11,
                            const R::RT & m12,
                            const R::RT & m13,

                            const R::RT & m21,
                            const R::RT & m22,
                            const R::RT & m23,

                            const R::RT &w= R::RT(1))
    : R::Aff_transformation_2(m11, m12, m13,
                              m21, m22, m23,
                              w)
  {}

  CGAL_Aff_transformation_2(const R::RT & m11, const R::RT & m12,
                            const R::RT & m21, const R::RT & m22,
                            const R::RT &w = R::RT(1))
    : R::Aff_transformation_2(m11, m12,
                              m21, m22,
                              w)
  {}

  ~CGAL_Aff_transformation_2()
  {}

  CGAL_Point_2<R>     transform(const CGAL_Point_2<R> &p) const
  {
    return R::Aff_transformation_2::transform(p);
  }

  CGAL_Point_2<R>     operator()(const CGAL_Point_2<R> &p) const
  {
    return transform(p);
  }

  CGAL_Vector_2<R>    transform(const CGAL_Vector_2<R> &v) const
  {
    return R::Aff_transformation_2::transform(v);
  }

  CGAL_Vector_2<R>    operator()(const CGAL_Vector_2<R> &v) const
  {
    return transform(v);
  }

  CGAL_Direction_2<R> transform(const CGAL_Direction_2<R> &d) const
  {
    return R::Aff_transformation_2::transform(d);
  }

  CGAL_Direction_2<R> operator()(const CGAL_Direction_2<R> &d) const
  {
    return transform(d);
  }

#ifdef TRANSFORM
  CGAL_Line_2<R>      transform(const CGAL_Line_2<R> &l) const
  {
    return R::Aff_transformation_2::transform(l);
  }

  CGAL_Line_2<R>      operator()(const CGAL_Line_2<R> &l) const
  {
    return transform(l);
  }


  CGAL_Ray_2<R>       transform(const CGAL_Ray_2<R> &r) const
  {
    return R::Aff_transformation_2::transform(r);
  }

  CGAL_Ray_2<R>       operator()(const CGAL_Ray_2<R> &r) const
  {
    return transform(r);
  }


  CGAL_Segment_2<R>   transform(const CGAL_Segment_2<R> &s) const
  {
    return R::Aff_transformation_2::transform(s);
  }

  CGAL_Segment_2<R>   operator()(const CGAL_Segment_2<R> &s) const
  {
    return transform(s);
  }


  CGAL_Triangle_2<R>  transform(const CGAL_Triangle_2<R> &t) const
  {
    return R::Aff_transformation_2::transform(t);
  }

  CGAL_Triangle_2<R>  operator()(const CGAL_Triangle_2<R> &t) const
  {
    return transform(t);
  }
#endif // TRANSFORM

  CGAL_Aff_transformation_2<R>  inverse() const
  {
    return R::Aff_transformation_2::inverse();
  }

  bool                 is_odd() const
  {
    return !is_even();
  }
  //#ifdef COMPOSE
  CGAL_Aff_transformation_2<R> operator*(
                                const CGAL_Aff_transformation_2<R> &t) const
  {
    return R::Aff_transformation_2::operator*(t);
  }
  //#endif // COMPOSE
};



#endif // CGAL_AFF_TRANSFORMATION_2_H
