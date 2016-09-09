// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.3
// release_date  : 2001, August 13
// 
// file          : include/CGAL/Segment_3.h
// package       : _3 (3.23)
// revision      : $Revision: 1.7 $
// revision_date : $Date: 2001/06/27 14:49:53 $
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_SEGMENT_3_H
#define CGAL_SEGMENT_3_H

#include <CGAL/Line_3.h>

CGAL_BEGIN_NAMESPACE

template <class R_>
class Segment_3 : public R_::Segment_3_base
{
public:
  typedef          R_                       R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Segment_3_base  RSegment_3;

  Segment_3() : RSegment_3()
  {}
  Segment_3(const CGAL::Segment_3<R>& s) : RSegment_3(s)
  {}
  Segment_3(const CGAL::Point_3<R>& sp, const CGAL::Point_3<R>& ep)
    : RSegment_3(sp,ep)
  {}
  Segment_3(const RSegment_3&  s) : RSegment_3(s)
  {}

  CGAL::Point_3<R>     start() const
  { return RSegment_3::start(); }
  CGAL::Point_3<R>     end() const
  { return RSegment_3::end(); }
  CGAL::Point_3<R>     source() const
  { return RSegment_3::source(); }
  CGAL::Point_3<R>     target() const
  { return RSegment_3::target(); }
  CGAL::Point_3<R>     min() const
  { return RSegment_3::min(); }
  CGAL::Point_3<R>     max() const
  { return RSegment_3::max(); }
  CGAL::Point_3<R>     vertex(int i) const
  { return RSegment_3::vertex(i); }
  CGAL::Point_3<R>     operator[](int i) const
  { return vertex(i); }
  CGAL::Direction_3<R> direction() const
  { return RSegment_3::direction(); }
  CGAL::Segment_3<R>  opposite() const
  { return CGAL::Segment_3<R>(target(),source()); }
  CGAL::Segment_3<R>  transform(const CGAL::Aff_transformation_3<R>& t) const
  { return RSegment_3::transform(t); }
  CGAL::Line_3<R>     supporting_line() const
  { return RSegment_3::supporting_line(); }
};

#ifndef CGAL_NO_OSTREAM_INSERT_SEGMENT_3
template < class R>
std::ostream&
operator<<(std::ostream& os, const Segment_3<R>& s)
{
  typedef typename  R::Segment_3_base  RSegment_3;
  return os << static_cast<const RSegment_3&>(s);
}
#endif // CGAL_NO_OSTREAM_INSERT_SEGMENT_3

#ifndef CGAL_NO_ISTREAM_EXTRACT_SEGMENT_3
template < class R>
std::istream&
operator>>(std::istream& is, Segment_3<R>& s)
{
  typedef typename  R::Segment_3_base  RSegment_3;
  return is >> static_cast<RSegment_3&>(s);
}
#endif // CGAL_NO_ISTREAM_EXTRACT_SEGMENT_3

CGAL_END_NAMESPACE

#endif // CGAL_SEGMENT_3_H
