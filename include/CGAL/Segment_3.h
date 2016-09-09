// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
// source        : Segment_3.fw
// file          : include/CGAL/Segment_3.h
// package       : _3 (1.3)
// revision      : 1.3
// revision_date : 15 May 1998 
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : cgal@cs.uu.nl
//
// ======================================================================
 

#ifndef CGAL_SEGMENT_3_H
#define CGAL_SEGMENT_3_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#ifndef CGAL_SEGMENTH3_H
#include <CGAL/SegmentH3.h>
#endif // CGAL_SEGMENTH3_H
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#ifndef CGAL_SEGMENTC3_H
#include <CGAL/SegmentC3.h>
#endif // CGAL_SEGMENTC3_H
#endif // CGAL_CARTESIAN_H

#ifndef CGAL_LINE_3_H
#include <CGAL/Line_3.h>
#endif // CGAL_LINE_3_H

template <class _R>
class CGAL_Segment_3 : public _R::Segment_3
{
public:
  typedef          _R                       R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Segment_3             Segment_3;

  CGAL_Segment_3() : Segment_3()
  {}
  CGAL_Segment_3(const CGAL_Segment_3<_R>& s) : Segment_3(s)
  {}
  CGAL_Segment_3(const CGAL_Point_3<_R>& sp, const CGAL_Point_3<_R>& ep)
    :  Segment_3(sp,ep)
  {}
  CGAL_Segment_3(const Segment_3 & s) : Segment_3(s)
  {}

  CGAL_Segment_3<_R>&   operator=(const CGAL_Segment_3<_R>& s)
  {
    Segment_3::operator=(s);
    return *this;
  }
  bool                 has_on(const CGAL_Point_3<_R>& p) const
  { return Segment_3::has_on(p); }
  bool                 operator==(const CGAL_Segment_3<_R>& s) const
  { return Segment_3::operator==(s); }
  bool                 operator!=(const CGAL_Segment_3<_R>& s) const
  { return !(*this == s); }
  int                  id() const   /* XXX */
  { return (int) PTR ; }
  CGAL_Point_3<_R>     start() const
  { return Segment_3::start(); }
  CGAL_Point_3<_R>     end() const
  { return Segment_3::end(); }
  CGAL_Point_3<_R>     source() const
  { return Segment_3::source(); }
  CGAL_Point_3<_R>     target() const
  { return Segment_3::target(); }
  CGAL_Point_3<_R>     min() const
  { return Segment_3::min(); }
  CGAL_Point_3<_R>     max() const
  { return Segment_3::max(); }
  CGAL_Point_3<_R>     vertex(int i) const
  { return Segment_3::vertex(i); }
  CGAL_Point_3<_R>     operator[](int i) const
  { return vertex(i); }
  FT                   squared_length() const
  { return Segment_3::squared_length(); }
  CGAL_Direction_3<_R> direction() const
  { return Segment_3::direction(); }
  CGAL_Segment_3<_R>  opposite() const
  { return CGAL_Segment_3<_R>(target(),source()); }
  CGAL_Segment_3<_R>  transform(const CGAL_Aff_transformation_3<_R>& t) const
  { return Segment_3::transform(t); }
  CGAL_Line_3<_R>     supporting_line() const
  { return Segment_3::supporting_line(); }
  bool                is_degenerate() const
  { return Segment_3::is_degenerate(); }
  CGAL_Bbox_3         bbox() const
  { return source().bbox() + target().bbox(); }
};


#ifndef CGAL_NO_OSTREAM_INSERT_SEGMENT_3
template < class R>
ostream&
operator<<(ostream& os, const CGAL_Segment_3<R>& s)
{
  typedef typename  R::Segment_3    Segment_3;
  return os << (const Segment_3&)s;
}
#endif // CGAL_NO_OSTREAM_INSERT_SEGMENT_3

#ifndef CGAL_NO_ISTREAM_EXTRACT_SEGMENT_3
template < class R>
istream&
operator>>(istream& is, CGAL_Segment_3<R>& s)
{
  typedef typename  R::Segment_3    Segment_3;
  return is >> (Segment_3&)s;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_SEGMENT_3



#endif // CGAL_SEGMENT_3_H
