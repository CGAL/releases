// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-1.1
// release_date  : 1998, July 24
// 
// source        : Segment_2.fw
// file          : include/CGAL/Segment_2.h
// package       : _2 (1.2.2)
// revision      : 1.2.2
// revision_date : 27 Jan 1998 
// author(s)     : Andreas Fabri
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : cgal@cs.uu.nl
//
// ======================================================================
 

#ifndef CGAL_SEGMENT_2_H
#define CGAL_SEGMENT_2_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#ifndef CGAL_SEGMENTH2_H
#include <CGAL/SegmentH2.h>
#endif // CGAL_SEGMENTH2_H
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#ifndef CGAL_SEGMENTC2_H
#include <CGAL/SegmentC2.h>
#endif // CGAL_SEGMENTC2_H
#endif // CGAL_CARTESIAN_H

#ifndef CGAL_LINE_2_H
#include <CGAL/Line_2.h>
#endif // CGAL_LINE_2_H

template <class _R>
class CGAL_Segment_2 : public _R::Segment_2
{
public:
  typedef  _R                               R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Segment_2             Segment_2;

  CGAL_Segment_2()     // doesn't the default constructor do the same ???
    : Segment_2()  // does the handle stuff
  {}

  ~CGAL_Segment_2()
  {}

  CGAL_Segment_2(const CGAL_Segment_2<R>  &s)
    : Segment_2((Segment_2&)s)  // does the handle stuff
  {}

  CGAL_Segment_2(const CGAL_Point_2<R> &sp, const CGAL_Point_2<R> &ep)
    :  Segment_2(sp,ep)
  {}


  // conversion from implementation class object to interface class object
  CGAL_Segment_2(const Segment_2  &s)
    : Segment_2(s)  // does the handle stuff
  {}

  CGAL_Segment_2<R>   &operator=(const CGAL_Segment_2<R> &s)
  {
    Segment_2::operator=(s);
    return *this;
  }

  bool                 is_horizontal() const
  {
      return Segment_2::is_horizontal();
  }

  bool                 is_vertical() const
  {
      return Segment_2::is_vertical();
  }

  bool                 has_on(const CGAL_Point_2<R> &p) const
  {
    return Segment_2::has_on(p);
  }

  bool                 collinear_has_on(const CGAL_Point_2<R> &p) const
  {
    return Segment_2::collinear_has_on(p);
  }


  bool                 operator==(const CGAL_Segment_2<R> &s) const
  {
    return Segment_2::operator==(s);
  }

  bool                 operator!=(const CGAL_Segment_2<R> &s) const
  {
    return !(*this == s);
  }

  int                  id() const
  {
    return (int) PTR  ;
  }


  CGAL_Point_2<R>     start() const
  {
    return Segment_2::start();
  }

  CGAL_Point_2<R>     end() const
  {
    return Segment_2::end();
  }

  CGAL_Point_2<R>     source() const
  {
    return Segment_2::source();
  }

  CGAL_Point_2<R>     target() const
  {
    return Segment_2::target();
  }

  CGAL_Point_2<R>     min() const
  {
    return Segment_2::min();
  }

  CGAL_Point_2<R>     max() const
  {
    return Segment_2::max();
  }

  CGAL_Point_2<R>     vertex(int i) const
  {
    return Segment_2::vertex(i);
  }

  CGAL_Point_2<R>     operator[](int i) const
  {
      return vertex(i);
  }


  FT                 squared_length() const
  {
    return Segment_2::squared_length();
  }


  CGAL_Direction_2<R> direction() const
  {
    return Segment_2::direction();
  }


  CGAL_Segment_2<R>  opposite() const
  {
    return CGAL_Segment_2<R>(target(),source());
  }

  // this makes use of the constructor of the interface class
  // taking an object of the implemetation class as argument.

  CGAL_Segment_2<R>   transform(const CGAL_Aff_transformation_2<R> &t) const
  {
    return  Segment_2::transform(t);
  }


  CGAL_Line_2<R>      supporting_line() const
  {
    return Segment_2::supporting_line();
  }

  bool                 is_degenerate() const
  {
    return Segment_2::is_degenerate();
  }

  CGAL_Bbox_2            bbox() const
  {
    return source().bbox() + target().bbox();
  }
};

#ifndef CGAL_NO_OSTREAM_INSERT_SEGMENT_2
template < class R>
ostream &
operator<<(ostream &os, const CGAL_Segment_2<R> &s)
{
  typedef typename  R::Segment_2       Segment_2;
  return os << (const Segment_2&)s;
}
#endif // CGAL_NO_OSTREAM_INSERT_SEGMENT_2

#ifndef CGAL_NO_ISTREAM_EXTRACT_SEGMENT_2
template < class R>
istream &
operator>>(istream &is, CGAL_Segment_2<R> &s)
{
  typedef typename  R::Segment_2       Segment_2;
  return is >> (Segment_2&)s;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_SEGMENT_2


#endif //  CGAL_SEGMENT_2_H
