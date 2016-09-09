/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/


// Source: Segment_3.h
// Author: Andreas Fabri

#ifndef CGAL_SEGMENT_3_H
#define CGAL_SEGMENT_3_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/SegmentH3.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/SegmentC3.h>
#endif // CGAL_CARTESIAN_H

#include <CGAL/Line_3.h>

template<class R>
class CGAL_Segment_3 : public R::Segment_3
{
public:
  CGAL_Segment_3()     // doesn't the default constructor the same ???
    : R::Segment_3()   // does the handle stuff
  {}

  CGAL_Segment_3(const CGAL_Segment_3<R>  &s)
    : R::Segment_3(s)  // does the handle stuff
  {}

  CGAL_Segment_3(const CGAL_Point_3<R> &sp, const CGAL_Point_3<R> &ep)
    :  R::Segment_3(sp,ep)
  {}

  // conversion from implementation class object to interface class object
  CGAL_Segment_3(const R::Segment_3  &s)
    : R::Segment_3(s)  // does the handle stuff
  {}

  CGAL_Segment_3<R>   &operator=(const CGAL_Segment_3<R> &s)
  {
    R::Segment_3::operator=(s);
    return *this;
  }

  bool                 has_on(const CGAL_Point_3<R> &p) const
  {
    return R::Segment_3::has_on(p);
  }

  bool                 operator==(const CGAL_Segment_3<R> &s) const
  {
    return R::Segment_3::operator==(s);
  }

  bool                 operator!=(const CGAL_Segment_3<R> &s) const
  {
    return !(*this == s);
  }

  int                  id() const
  {
    return (int) PTR ;
  }


  CGAL_Point_3<R>     start() const
  {
    return R::Segment_3::start();
  }

  CGAL_Point_3<R>     end() const
  {
    return R::Segment_3::end();
  }

  CGAL_Point_3<R>     source() const
  {
    return R::Segment_3::source();
  }

  CGAL_Point_3<R>     target() const
  {
    return R::Segment_3::target();
  }

  CGAL_Point_3<R>     min() const
  {
    return R::Segment_3::min();
  }

  CGAL_Point_3<R>     max() const
  {
    return R::Segment_3::max();
  }

  CGAL_Point_3<R>     vertex(int i) const
  {
    return R::Segment_3::vertex(i);
  }

  CGAL_Point_3<R>     operator[](int i) const
  {
    return vertex(i);
  }


  R::FT                 squared_length() const
  {
    return R::Segment_3::squared_length();
  }


  CGAL_Direction_3<R> direction() const
  {
    return R::Segment_3::direction();
  }

  CGAL_Segment_3<R>  opposite() const
  {
    return CGAL_Segment_3<R>(target(),source());
  }

  // this makes use of the constructor of the interface class
  // taking an object of the implemetation class as argument.


  CGAL_Segment_3<R>      transform(const CGAL_Aff_transformation_3<R> &t) const
  {
    return  R::Segment_3::transform(t);
  }


  CGAL_Line_3<R>      supporting_line() const
  {
    return R::Segment_3::supporting_line();
  }

  bool                 is_degenerate() const
  {
    return R::Segment_3::is_degenerate();
  }

  CGAL_Bbox_3            bbox() const
  {
    return source().bbox() + target().bbox();
  }
};


#ifndef CGAL_NO_OSTREAM_INSERT_SEGMENT_3
template < class R >
ostream &operator<<(ostream &os, const CGAL_Segment_3<R> &s)
{
    return os << (const R::Segment_3&)s;
}
#endif // CGAL_NO_OSTREAM_INSERT_SEGMENT_3

#ifndef CGAL_NO_ISTREAM_EXTRACT_SEGMENT_3
template < class R >
istream &operator>>(istream &is, CGAL_Segment_3<R> &s)
{
    return is >> (R::Segment_3&)s;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_SEGMENT_3



#endif // CGAL_SEGMENT_3_H
