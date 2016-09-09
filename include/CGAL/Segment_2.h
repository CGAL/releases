// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.0
// release_date  : 1999, June 03
// 
// source        : Segment_2.fw
// file          : include/CGAL/Segment_2.h
// package       : _2 (2.1.2)
// revision      : 2.1.2
// revision_date : 09 May 1999 
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

CGAL_BEGIN_NAMESPACE

template <class _R>
class Segment_2 : public _R::Segment_2
{
public:
  typedef  _R                               R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Segment_2             RSegment_2;

  Segment_2()     // doesn't the default constructor do the same ???
    : RSegment_2()  // does the handle stuff
  {}

  ~Segment_2()
  {}

  Segment_2(const Segment_2<R>& s)
    : RSegment_2((RSegment_2&)s)  // does the handle stuff
  {}

  Segment_2(const Point_2<R> &sp, const Point_2<R> &ep)
    :  RSegment_2(sp,ep)
  {}


  // conversion from implementation class object to interface class object
  Segment_2(const RSegment_2& s)
    : RSegment_2(s)  // does the handle stuff
  {}

  Segment_2<R>& operator=(const Segment_2<R> &s)
  {
    RSegment_2::operator=(s);
    return *this;
  }

  bool  is_horizontal() const
  { return RSegment_2::is_horizontal(); }

  bool  is_vertical() const
  { return RSegment_2::is_vertical(); }

  bool  has_on(const Point_2<R> &p) const
  { return RSegment_2::has_on(p); }

  bool  collinear_has_on(const Point_2<R> &p) const
  { return RSegment_2::collinear_has_on(p); }


  bool  operator==(const Segment_2<R> &s) const
  { return RSegment_2::operator==(s); }

  bool  operator!=(const Segment_2<R> &s) const
  { return !(*this == s); }

  int  id() const
  { return (int) PTR  ; }


  Point_2<R>     start() const
  { return RSegment_2::start(); }

  Point_2<R>     end() const
  { return RSegment_2::end(); }

  Point_2<R>     source() const
  { return RSegment_2::source(); }

  Point_2<R>     target() const
  { return RSegment_2::target(); }

  Point_2<R>     min() const
  { return RSegment_2::min(); }

  Point_2<R>     max() const
  { return RSegment_2::max(); }

  Point_2<R>     vertex(int i) const
  { return RSegment_2::vertex(i); }

  Point_2<R>     point(int i) const
  { return RSegment_2::vertex(i); }

  Point_2<R>     operator[](int i) const
  { return vertex(i); }

  FT                 squared_length() const
  { return RSegment_2::squared_length(); }

  Direction_2<R> direction() const
  { return RSegment_2::direction(); }

  Segment_2<R>  opposite() const
  { return Segment_2<R>(target(),source()); }

  // this makes use of the constructor of the interface class
  // taking an object of the implemetation class as argument.

  Segment_2<R>   transform(const Aff_transformation_2<R> &t) const
  { return  RSegment_2::transform(t); }


  Line_2<R>      supporting_line() const
  { return RSegment_2::supporting_line(); }

  bool                is_degenerate() const
  { return RSegment_2::is_degenerate(); }

  Bbox_2         bbox() const
  { return source().bbox() + target().bbox(); }

};

#ifndef NO_OSTREAM_INSERT_SEGMENT_2
template < class R>
std::ostream &
operator<<(std::ostream &os, const Segment_2<R> &s)
{
  typedef typename  R::Segment_2       RSegment_2;
  return os << (const RSegment_2&)s;
}
#endif // NO_OSTREAM_INSERT_SEGMENT_2

#ifndef NO_ISTREAM_EXTRACT_SEGMENT_2
template < class R>
std::istream &
operator>>(std::istream &is, Segment_2<R> &s)
{
  typedef typename  R::Segment_2       RSegment_2;
  return is >> (RSegment_2&)s;
}
#endif // NO_ISTREAM_EXTRACT_SEGMENT_2

CGAL_END_NAMESPACE


#endif //  CGAL_SEGMENT_2_H
