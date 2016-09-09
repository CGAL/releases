// Source: Point_2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_POINT_2_H
#define CGAL_POINT_2_H

#include <CGAL/PointC2.h>
#include <CGAL/Vector_2.h>
#include <CGAL/Aff_transformation_2.h>
template < class R >
class CGAL_Point_2 : public R::Point_2
{

#ifdef CGAL_WORKAROUND_001
friend  CGAL_Point_2<R> operator+(const CGAL_Origin &o,
                                  const CGAL_Vector_2<R> &v);
friend  CGAL_Point_2<R> operator-(const CGAL_Origin &o,
                                  const CGAL_Vector_2<R> &v);
#else
friend inline CGAL_Point_2<R> operator+(const CGAL_Origin &o,
                                        const CGAL_Vector_2<R> &v);
friend inline CGAL_Point_2<R> operator-(const CGAL_Origin &o,
                                        const CGAL_Vector_2<R> &v);
#endif // CGAL_WORKAROUND_001

public:
  CGAL_Point_2()
  {}

  CGAL_Point_2(const CGAL_Origin &o)
    : R::Point_2(o)
  {}

  CGAL_Point_2(const CGAL_Point_2<R> &p)
    : R::Point_2(p)
  {}

  CGAL_Point_2(const R::Point_2 &p)
    : R::Point_2(p)
  {}

  CGAL_Point_2(const R::RT &hx, const R::RT &hy, const R::RT &hw = R::RT(1.0))
    : R::Point_2(hx, hy, hw)
  {}

  // operator CGAL_Point_2<double>() const;

  CGAL_Point_2<R> &operator=(const CGAL_Point_2<R> &p)
  {
    R::Point_2::operator=(p);
    return *this;
  }

  bool operator==(const CGAL_Point_2<R> &p) const
  {
    return R::Point_2::operator==(p);
  }

  bool operator!=(const CGAL_Point_2<R> &p) const
  {
    return !(*this == p);
  }

  bool identical(const CGAL_Point_2<R> &p) const
  {
    return ( PTR == p.PTR );
  }

  R::RT hx() const
  {
    return R::Point_2::hx();
  }

  R::RT hy() const
  {
    return R::Point_2::hy();
  }

  R::RT hw() const
  {
    return R::Point_2::hw();
  }
  R::FT x() const
  {
    return R::Point_2::x();
  }

  R::FT y() const
  {
    return R::Point_2::y();
  }

  R::RT homogeneous(int i) const
  {
    return R::Point_2::homogeneous(i);
  }

  R::FT cartesian(int i) const
  {
    return R::Point_2::cartesian(i);
  }

  R::FT operator[](int i) const
  {
    return cartesian(i);
  }

  int dimension() const
  {
    return 2;
  }

  CGAL_Bbox_2       bbox() const
  {
    return R::Point_2::bbox();
  }

  CGAL_Point_2<R> transform(const CGAL_Aff_transformation_base_2<R> &t) const
  {
    return R::Point_2::transform(t);
  }

  void decrease_count(){ R::Point_2::decrease_count();}
private:

  CGAL_Point_2(const R::Vector_2 &v)
    : R::Point_2(v)
  {}
};


template < class R >
inline CGAL_Point_2<R> operator+(const CGAL_Point_2<R> &p,
                                  const CGAL_Vector_2<R> &v)
{
  CGAL_kernel_precondition(p.is_defined() && v.is_defined());
  return CGAL_Point_2<R>(p.x() + v.x(), p.y() + v.y()) ;
}

template < class R >
inline CGAL_Point_2<R> operator-(const CGAL_Point_2<R> &p,
                                  const CGAL_Vector_2<R> &v)
{
  CGAL_kernel_precondition(p.is_defined() && v.is_defined());
  return CGAL_Point_2<R>(p.x() - v.x(), p.y() - v.y()) ;
}

template < class R >
inline CGAL_Point_2<R> operator+(const CGAL_Origin &,
                                  const CGAL_Vector_2<R> &v)
{
  CGAL_kernel_precondition(v.is_defined());
  return CGAL_Point_2<R>(v) ;
}


template < class R >
inline CGAL_Point_2<R> operator-(const CGAL_Origin &,
                                  const CGAL_Vector_2<R> &v)
{
  CGAL_kernel_precondition(v.is_defined());
  return CGAL_Point_2<R>(-v) ;
}

template < class R >
inline CGAL_Vector_2<R> operator-(const CGAL_Point_2<R> &p,
                                   const CGAL_Point_2<R> &q)
{
  CGAL_kernel_precondition(p.is_defined() && q.is_defined());
  return CGAL_Vector_2<R>(p.x() - + q.x(), p.y() - q.y()) ;
}

template < class R >
inline CGAL_Vector_2<R> operator-(const CGAL_Point_2<R> &p,
                                   const CGAL_Origin &)
{
  CGAL_kernel_precondition(p.is_defined());
  return CGAL_Vector_2<R>(p) ;
}

template < class R >
inline CGAL_Vector_2<R> operator-(const CGAL_Origin &,
                                   const CGAL_Point_2<R> &p)
{
  CGAL_kernel_precondition(p.is_defined());
  return CGAL_Vector_2<R>(-p.x(), -p.y()) ;
}




#ifdef CGAL_IO

#include <stream.h>
template < class R >
ostream &operator<<(ostream &os, CGAL_Point_2<R> &p)
{
  CGAL_kernel_precondition(p.is_defined());
  os << "Point_2(" << p.x() << ", " << p.y() << ")";
  return os;
}

#endif

#endif
