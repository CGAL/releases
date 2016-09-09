// Source: Segment_2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_SEGMENT_2_H
#define CGAL_SEGMENT_2_H

#include <CGAL/SegmentC2.h>
#include <CGAL/Line_2.h>

template<class R>
class CGAL_Segment_2 : public R::Segment_2
{
public:
  CGAL_Segment_2()     // doesn't the default constructor the same ???
    : R::Segment_2()   // does the handle stuff
  {}

  ~CGAL_Segment_2()
  {}

  CGAL_Segment_2(const CGAL_Segment_2<R>  &s)
    : R::Segment_2((R::Segment_2&)s)  // does the handle stuff
  {
    CGAL_kernel_precondition(s.is_defined());
  }

  CGAL_Segment_2(const CGAL_Point_2<R> &sp, const CGAL_Point_2<R> &ep)
    :  R::Segment_2(sp,ep)
  {
    CGAL_kernel_precondition(sp.is_defined() && ep.is_defined());
 }


  // conversion from implementation class object to interface class object
  CGAL_Segment_2(const R::Segment_2  &s)
    : R::Segment_2(s)  // does the handle stuff
  {
    CGAL_kernel_precondition(s.is_defined());
  }

  CGAL_Segment_2<R>   &operator=(const CGAL_Segment_2<R> &s)
  {
    CGAL_kernel_precondition(s.is_defined());
    R::Segment_2::operator=(s);
    return *this;
  }

  bool                 is_horizontal() const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Segment_2::is_horizontal();
  }

  bool                 is_vertical() const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Segment_2::is_vertical();
  }

  bool                 is_on(const CGAL_Point_2<R> &p) const
  {
    CGAL_kernel_precondition(is_defined() && p.is_defined());
    return R::Segment_2::is_on(p);
  }

  bool                 collinear_is_on(const CGAL_Point_2<R> &p) const
  {
    CGAL_kernel_precondition(is_defined() && p.is_defined());
    return R::Segment_2::collinear_is_on(p);
  }


  bool                 operator==(const CGAL_Segment_2<R> &s) const
  {
    CGAL_kernel_precondition(is_defined() && s.is_defined());
    return R::Segment_2::operator==(s);
  }

  bool                 operator!=(const CGAL_Segment_2<R> &s) const
  {
    return !(*this == s);
  }

  bool                 identical(const CGAL_Segment_2<R> &s) const
  {
    CGAL_kernel_precondition(s.is_defined());
    return PTR == s.PTR ;
  }


  CGAL_Point_2<R>     start() const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Segment_2::start();
  }

  CGAL_Point_2<R>     end() const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Segment_2::end();
  }

  CGAL_Point_2<R>     vertex(int i) const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Segment_2::vertex(i);
  }

  CGAL_Point_2<R>     operator[](int i) const
  {
    CGAL_kernel_precondition(is_defined());
    return vertex(i);
  }


  R::RT                 squared_length() const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Segment_2::squared_length();
  }


  CGAL_Direction_2<R> direction() const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Segment_2::direction();
  }


  CGAL_Segment_2<R>  opposite() const
  {
    CGAL_kernel_precondition(is_defined());
    return CGAL_Segment_2<R>(end(),start());
  }

  // this makes use of the constructor of the interface class
  // taking an object of the implemetation class as argument.

  CGAL_Segment_2<R>       transform(const CGAL_Aff_transformation_2<R> &t) const
  {
    CGAL_kernel_precondition(is_defined() && t.is_defined());
    return  CGAL_Segment_2<R>(R::Segment_2::transform(t));
  }


  CGAL_Line_2<R>      supporting_line() const
  {
    CGAL_kernel_precondition(is_defined());
    return CGAL_Line_2<R>(R::Segment_2::supporting_line());
  }

  bool                 is_degenerate() const
  {
    CGAL_kernel_precondition(is_defined());
    return R::Segment_2::is_degenerate();
  }

  CGAL_Bbox_2            bbox() const
  {
    CGAL_kernel_precondition(is_defined());
    return start().bbox() + end().bbox();
  }

#ifdef CGAL_CHECK_PRECONDITIONS
  bool             is_defined() const
  {
    return (PTR == NULL)? false : true;
  }
#endif

};




#ifdef CGAL_IO

template < class R >
ostream &operator<<(ostream &os, const CGAL_Segment_2<R> &s)
{
  CGAL_kernel_precondition(s.is_defined());
  os << "Segment_2(" << s.start() <<  ", " << s.end() << ")";
  return os;
}

#endif


#endif
