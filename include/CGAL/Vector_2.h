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
friend CGAL_Vector_2<R> operator-(const CGAL_Point_2<R> &p, const CGAL_Origin &o);

friend CGAL_Vector_2<R> CGAL_Direction_2<R>::vector() const;
#else
friend inline CGAL_Vector_2<R> operator-(const CGAL_Point_2<R> &p, const CGAL_Origin &o);

friend inline CGAL_Vector_2<R> CGAL_Direction_2<R>::vector() const;
#endif

public:
  CGAL_Vector_2()
  {}

  CGAL_Vector_2(const CGAL_Vector_2<R> &v)
    : R::Vector_2(v)
  {}

  CGAL_Vector_2(const R::Vector_2 &v)
    : R::Vector_2(v)
  {}

  CGAL_Vector_2(const R::FT &x, const R::FT &y, const R::FT &w = R::FT(1.0))
    : R::Vector_2(x,y,w)
  {}

  // operator CGAL_Vector_2<double>() const;

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

  R::FT x() const
  {
    return R::Vector_2::x();
  }

  R::FT y() const
  {
    return R::Vector_2::y();
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
    return R::Vector_2::operator+(w);
  }

  CGAL_Vector_2<R> operator-(const CGAL_Vector_2 &w) const
  {
    return R::Vector_2::operator-(w);
  }

  CGAL_Vector_2<R> operator-() const
  {
    return R::Vector_2::operator-();
  }

  R::FT operator*(const CGAL_Vector_2 &w) const
  {
    return R::Vector_2::operator*(w);
  }

  CGAL_Vector_2<R> operator*(const R::FT &c) const
  {
    return R::Vector_2::operator*(c);
  }

  CGAL_Vector_2<R> operator/(const R::FT &c) const
  {
    return R::Vector_2::operator/(c);
  }

  CGAL_Direction_2<R> direction() const
  {
    return R::Vector_2::direction();
  }

  CGAL_Vector_2<R> transform(const CGAL_Aff_transformation_2<R> &t) const
  {
    return R::Vector_2::transform(t);
  }


#ifdef CGAL_KERNEL_PRECONDITION
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



template < class FT, class R >
inline CGAL_Vector_2<R> operator*(const FT &c, const CGAL_Vector_2<R> &w)
{
   return c * R::Vector_2(w) ;
}





#ifdef CGAL_IO

#include <stream.h>

template < class R >
ostream &operator<<(ostream &os, CGAL_Vector_2<R> &v)
{
  CGAL_kernel_precondition(v.is_defined());
  os << "Vector_2(" << v.x() << ", " << v.y() << ")";
  return os;
}

#endif

#endif
