 
// Source: Vector_2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_VECTOR_2_H
#define CGAL_VECTOR_2_H


#include <CGAL/Point_2.h>
#include <CGAL/Direction_2.h>

 
template < class R >
class CGAL_Vector_2 : public R::Vector_2
{
#ifdef CGAL_WORKAROUND_001
friend CGAL_Vector_2<R> operator-(const CGAL_Point_2<R> &p,
                                  const CGAL_Origin &o);
#else
friend inline CGAL_Vector_2<R> operator-(const CGAL_Point_2<R> &p,
                                         const CGAL_Origin &o);
#endif  // CGAL_WORKAROUND_001

public:
  CGAL_Vector_2()
  {}

  CGAL_Vector_2(const CGAL_Vector_2<R> &v)
    : R::Vector_2((const R::Vector_2&)v)
  {}

  CGAL_Vector_2(const R::Vector_2 &v)
    : R::Vector_2(v)
  {}

  CGAL_Vector_2(const R::RT &x, const R::RT &y)
    : R::Vector_2(x,y)
  {}

  CGAL_Vector_2(const R::RT &x, const R::RT &y, const R::RT &w)
    : R::Vector_2(x,y,w)
  {}



  CGAL_Vector_2<R> &operator=(const CGAL_Vector_2<R> &v)
  {
    R::Vector_2::operator=(v);
    return *this;
  }


  bool operator==(const CGAL_Vector_2<R> &v) const
  {
    return R::Vector_2::operator==(v);
  }

  bool operator!=(const CGAL_Vector_2<R> &v) const
  {
    return !(*this == v);
  }

  bool identical(const CGAL_Vector_2<R> &v) const
  {
    return ( PTR == v.PTR );
  }

  R::RT hx() const
  {
    return R::Vector_2::hx();
  }

  R::RT hy() const
  {
    return R::Vector_2::hy();
  }

  R::RT hw() const
  {
    return R::Vector_2::hw();
  }

  R::FT x() const
  {
    return R::Vector_2::x();
  }

  R::FT y() const
  {
    return R::Vector_2::y();
  }

  R::RT homogeneous(int i) const
  {
    return R::Vector_2::homogeneous(i);
  }

  R::FT cartesian(int i) const
  {
    return R::Vector_2::cartesian(i);
  }

  R::FT operator[](int i) const
  {
    return cartesian(i);
  }

  int dimension() const
  {
    return 2;
  }


  CGAL_Vector_2<R> operator+(const CGAL_Vector_2 &w) const
  {
    return (const R::Vector_2&)(*this) + (const R::Vector_2&)(w);
  }

  CGAL_Vector_2<R> operator-(const CGAL_Vector_2 &w) const
  {
    return (const R::Vector_2&)(*this) - (const R::Vector_2&)(w);
  }

  CGAL_Vector_2<R> operator-() const
  {
    return R::Vector_2::operator-();
  }

  R::FT operator*(const CGAL_Vector_2 &w) const
  {
    return (const R::Vector_2&)(*this) * (const R::Vector_2&)(w);
  }

  CGAL_Vector_2<R> operator*(const R::RT &c) const
  {
    return (const R::Vector_2&)(*this) * R::RT(c);

  }

  CGAL_Vector_2<R> operator/(const R::RT &c) const
  {
    return (const R::Vector_2&)(*this) / R::RT(c);
  }

  CGAL_Direction_2<R> direction() const
  {
    return R::Vector_2::direction();
  }

  CGAL_Vector_2<R> transform(const CGAL_Aff_transformation_2<R> &t) const
  {
    return R::Vector_2::transform(t);
  }


#ifdef CGAL_CHECK_PRECONDITIONS
  bool                 is_defined() const
  {
    return R::Vector_2::is_defined();
  }
#endif

private:
  CGAL_Vector_2(const CGAL_Point_2<R> &p)
    : R::Vector_2(p)
  {}

  CGAL_Vector_2(const CGAL_Direction_2<R> &d)
    : R::Vector_2(d)
  {}

};
 


 
#ifdef CGAL_WORKAROUND_007

#ifdef CGAL_CARTESIAN_H
template <class FT>
CGAL_Vector_2< C<FT> > operator*(const FT &c,
                                 const CGAL_Vector_2< C<FT> > &w)
{
  return c * (const C<FT>::Vector_2&)(w);
}
#endif // CGAL_CARTESIAN_H


#ifdef CGAL_HOMOGENEOUS_H
template <class FT, class RT>
CGAL_Vector_2< H<FT,RT> > operator*(const RT &c,
                                    const CGAL_Vector_2< H<FT,RT> > &w)
{
  return c * (const H<FT,RT>::Vector_2&)(w);
}
#endif // CGAL_HOMOGENEOUS_H

#else

template < class RT, class R >
CGAL_Vector_2<R> operator*(const RT &c, const CGAL_Vector_2<R> &w)
{
  return R::RT(c) * (const R::Vector_2&)(w) ;
}
#endif // CGAL_WORKAROUND_007
 


#endif
