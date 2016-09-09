// Source: Line_2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_Line_2_H
#define CGAL_Line_2_H

#include <CGAL/LineC2.h>
#include <CGAL/Ordertype_2.h>
#include <CGAL/Vector_2.h>

template < class R >
class CGAL_Line_2 : public R::Line_2
{
public:
  CGAL_Line_2()
    : R::Line_2()
  {}

  ~CGAL_Line_2()
  {}

  CGAL_Line_2(const CGAL_Line_2  &l)
    : R::Line_2(l)
  {
    CGAL_kernel_precondition(l.is_defined());
  }

  CGAL_Line_2(const CGAL_Point_2<R> &p, const CGAL_Point_2<R> &q)
    : R::Line_2(p,q)
  {
    CGAL_kernel_precondition(p.is_defined() && q.is_defined());
  }

  CGAL_Line_2(const R::RT &a, const R::RT &b, const R::RT &c)
    : R::Line_2(a,b,c)
  {}

  CGAL_Line_2(const R::Line_2 &l)  // conversion impl -> interface class
    : R::Line_2(l)
  {
    CGAL_kernel_precondition(l.is_defined());
  }

  CGAL_Line_2(const CGAL_Segment_2<R> &s)
    : R::Line_2(s)
  {
    CGAL_kernel_precondition(s.is_defined());
  }

  CGAL_Line_2(const CGAL_Ray_2<R> &r)
    : R::Line_2(r)
  {
    CGAL_kernel_precondition(r.is_defined());
  }

  CGAL_Line_2(const CGAL_Point_2<R> &p, const CGAL_Direction_2<R> &d)
    : R::Line_2(p,d)
  {
    CGAL_kernel_precondition(p.is_defined() && d.is_defined());
  }


  //                  operator CGAL_Line_2<double>() const;

  CGAL_Line_2<R> &operator=(const CGAL_Line_2<R> &l)
  {
    CGAL_kernel_precondition(l.is_defined());
    R::Line_2::operator=(l);
    return *this;
  }

  bool operator==(const CGAL_Line_2<R> &l) const
  {
    CGAL_kernel_precondition(l.is_defined());
    return R::Line_2::operator==(l);
  }

  bool operator!=(const CGAL_Line_2<R> &l) const
  {
    return !(*this == l);
  }

  bool identical(const CGAL_Line_2<R> &l) const
  {
    CGAL_kernel_precondition(l.is_defined());
    return ( PTR == l.PTR );
  }

  R::RT a() const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Line_2::a();
  }

  R::RT b() const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Line_2::b();
  }

  R::RT c() const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Line_2::c();
  }


  R::RT x_at_y(const R::RT &y) const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Line_2::x_at_y(y);
  }

  R::RT y_at_x(const R::RT &x) const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Line_2::y_at_x(x);
  }

  CGAL_Line_2<R> perpendicular(const CGAL_Point_2<R> &p) const
  {
    CGAL_kernel_precondition(is_defined() && p.is_defined());
    return CGAL_Line_2<R>(R::Line_2::perpendicular(p));
  }

  CGAL_Line_2<R> opposite() const
  {
    CGAL_kernel_precondition(is_defined());
    return CGAL_Line_2<R>(R::Line_2::opposite());
  }

  CGAL_Point_2<R> point() const
  {
    return R::Line_2::point();
  }

  CGAL_Point_2<R> projection(const CGAL_Point_2<R> &p) const
  {
    CGAL_kernel_precondition(is_defined() && p.is_defined());
    return R::Line_2::projection(p);
  }


  CGAL_Direction_2<R> direction() const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Line_2::direction();
  }

  bool is_on(const CGAL_Point_2<R> &p) const
  {
    CGAL_kernel_precondition(is_defined() && p.is_defined());
    return R::Line_2::is_on(p);
  }

  CGAL_Side where_is(const CGAL_Point_2<R> &p) const
  {
    CGAL_kernel_precondition(is_defined() && p.is_defined());
    return R::Line_2::where_is(p);
  }

  bool is_horizontal() const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Line_2::is_horizontal();
  }

  bool is_vertical() const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Line_2::is_vertical();
  }

  bool is_degenerate() const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Line_2::is_degenerate();
  }

  CGAL_Line_2<R> transform(const CGAL_Aff_transformation_2<R> &t) const
  {
    CGAL_kernel_precondition(is_defined() && t.is_defined());
    return  CGAL_Line_2<R>(R::Line_2::transform(t));
  }

#ifdef CGAL_CHECK_PRECONDITIONS
  bool             is_defined() const
  {
    return (PTR == NULL)? false : true;
  }
#endif

};



#ifdef CGAL_IO

#include <stream.h>

template < class R >
ostream &operator<<(ostream &os, const CGAL_Line_2<R> &l)
{
    CGAL_kernel_precondition(l.is_defined());
  os << "Line_2(" << l.a() << ", "<< l.b() << ", " << l.c() << ")";
  return os;
}

#endif


#endif
