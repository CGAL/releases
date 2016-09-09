// Source:Ray_2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_Ray_2_H
#define CGAL_Ray_2_H

#include <CGAL/Segment_2.h>
#include <CGAL/RayC2.h>

template < class R >
class CGAL_Ray_2 : public R::Ray_2
{
public:
    CGAL_Ray_2()
      : R::Ray_2()
  {}

  ~CGAL_Ray_2()
  {}

  CGAL_Ray_2(const CGAL_Ray_2<R> &r)
    : R::Ray_2(r)
  {
    CGAL_kernel_precondition(r.is_defined());
  }

  CGAL_Ray_2(const R::Ray_2 &r)
    : R::Ray_2(r)
  {
    CGAL_kernel_precondition(r.is_defined());
  }

  CGAL_Ray_2(const CGAL_Point_2<R> &sp,
             const CGAL_Point_2<R> &secondp)
    : R::Ray_2(sp, secondp)
  {}

  CGAL_Ray_2(const CGAL_Point_2<R> &sp,
             const CGAL_Direction_2<R> &d)
    : R::Ray_2(sp, d)
  {}

  //                      operator CGAL_Ray_2<double>() const;

  CGAL_Ray_2<R> &operator=(const CGAL_Ray_2<R> &r)
  {
    CGAL_kernel_precondition(r.is_defined());

    R::Ray_2::operator=(r);
    return *this;
  }

  bool operator==(const CGAL_Ray_2<R> &r) const
  {
    return R::Ray_2::operator==(r);
  }

  bool operator!=(const CGAL_Ray_2<R> &r) const
  {
    return !(*this == r);
  }

  bool identical(const CGAL_Ray_2<R> &r) const
  {
    return ( PTR == r.PTR );
  }

  CGAL_Point_2<R> start() const
  {
    return R::Ray_2::start();
  }

  CGAL_Point_2<R> second_point() const
  {
    return R::Ray_2::second_point();
  }


  CGAL_Direction_2<R> direction() const
  {
    return R::Ray_2::direction();
  }

  CGAL_Line_2<R> supporting_line() const
  {
    return CGAL_Line_2<R>(R::Ray_2::supporting_line());
  }

  CGAL_Ray_2<R> opposite() const
  {
    return CGAL_Ray_2<R>(R::Ray_2::opposite());
  }

  CGAL_Ray_2<R> transform(const CGAL_Aff_transformation_base_2<R> &t) const
  {
    return  CGAL_Ray_2<R>(R::Ray_2::transform(t));
  }

  bool is_horizontal() const
    {
      return R::Ray_2::is_horizontal();
    }

  bool is_vertical() const
  {
    return R::Ray_2::is_vertical();
  }

  bool is_degenerate() const
  {
    return R::Ray_2::is_degenerate();
  }

  bool is_on(const CGAL_Point_2<R> &p) const
  {
    return R::Ray_2::is_on(p);
  }

#ifdef CGAL_KERNEL_PRECONDITION
  bool is_defined() const
  {
    return (PTR == NULL)? false : true;
  }
#endif
};



#ifdef CGAL_IO

#include <stream.h>

template < class R >
ostream &operator<<(ostream &os, CGAL_Ray_2<R> &r)
{
  os << "Ray_2(" << r.start() <<  ", " << r.direction() << ")";
  return os;
}

#endif


#endif
