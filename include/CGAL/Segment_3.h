//  Copyright CGAL 1996
//
//  cgal@cs.ruu.nl
//
//  This file is part of an internal release of the CGAL kernel.
//  The code herein may be used and/or copied only in accordance
//  with the terms and conditions stipulated in the agreement
//  under which the code has been supplied or with the written
//  permission of the CGAL Project.
//
//  Look at http://www.cs.ruu.nl/CGAL/ for more information.
//  Please send any bug reports and comments to cgal@cs.ruu.nl
//
//  The code comes WITHOUT ANY WARRANTY; without even the implied
//  warranty of FITNESS FOR A PARTICULAR PURPOSE.
//

// Source: Segment_3.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_SEGMENT_3_H
#define CGAL_SEGMENT_3_H

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



#endif // CGAL_SEGMENT_3_H
