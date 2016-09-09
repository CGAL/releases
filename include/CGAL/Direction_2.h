// Source: Direction_2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_DIRECTION_2_H
#define CGAL_DIRECTION_2_H

#include <CGAL/DirectionC2.h>
#include <CGAL/Vector_2.h>

template < class R >
class CGAL_Direction_2 : public R::Direction_2
{
public:
  CGAL_Direction_2()
  {}

  CGAL_Direction_2(const CGAL_Direction_2<R> &d)
    : R::Direction_2(d)
  {}

  CGAL_Direction_2(const R::Direction_2 &d)
    : R::Direction_2(d)
  {}

  CGAL_Direction_2(const R::Vector_2 &v)
    : R::Direction_2(v)
  {}

  CGAL_Direction_2(const R::FT &x, const R::FT &y, const R::FT &w = R::FT(1.0))
    :  R::Direction_2(x,y,w)
  {}

  // operator CGAL_Direction_2<double>() const;

  CGAL_Direction_2<R> &operator=(const CGAL_Direction_2<R> &d)
  {
    R::Direction_2::operator=(d);
    return *this;
  }


  bool operator==(const CGAL_Direction_2<R> &d) const
  {
    return R::Direction_2::operator==(d);
  }

  bool operator!=(const CGAL_Direction_2<R> &d) const
  {
    return !(*this == d);
  }

  bool operator>=(const CGAL_Direction_2<R> &d) const
  {
    return R::Direction_2::operator>=(d);
  }

  bool operator<=(const CGAL_Direction_2<R> &d) const
  {
    return R::Direction_2::operator<=(d);
  }

  bool operator>(const CGAL_Direction_2<R> &d) const
  {
    return R::Direction_2::operator>(d);
  }

  bool operator<(const CGAL_Direction_2<R> &d) const
  {
    return R::Direction_2::operator<(d);
  }

  bool counterclockwise_in_between(const CGAL_Direction_2<R> &d1,
                                   const CGAL_Direction_2<R> &d2) const
  {
    return R::Direction_2::counterclockwise_in_between(d1,d2);
  }

  bool identical(const CGAL_Direction_2<R> &d) const
  {
    return ( PTR == d.PTR );
  }

  CGAL_Vector_2<R> vector() const
  {
    return R::Direction_2::vector();
  }

  CGAL_Direction_2<R> transform(const CGAL_Aff_transformation_base_2<R> &t) const
  {
    return R::Direction_2::transform(t);
  }

  CGAL_Direction_2<R> operator-() const
  {
    return R::Direction_2::operator-();
  }

  // public but hidden
  R::FT x() const
  {
    return R::Direction_2::x();
  }

  R::FT y() const
  {
    return R::Direction_2::y();
  }

#ifdef CGAL_KERNEL_PRECONDITION
  bool is_defined() const
  {
    return R::Direction_2::is_defined();
  }
#endif

};



#ifdef CGAL_IO

#include <stream.h>

template < class R >
ostream &operator<<(ostream &os, CGAL_Direction_2<R> &d)
{
  CGAL_Vector_2<R> v = d.vector();
  os << "Direction_2(" << v.x() << ", " << v.y() << ")";
  return os;
}

#endif


#endif
