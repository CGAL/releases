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
// file          : include/CGAL/Line_2.h
// package       : _2 (3.19)
// revision      : $Revision: 1.9 $
// revision_date : $Date: 2001/06/27 14:51:31 $
// author(s)     : Andreas Fabri
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_LINE_2_H
#define CGAL_LINE_2_H

#include <CGAL/Segment_2.h>
#include <CGAL/Ray_2.h>

CGAL_BEGIN_NAMESPACE

template <class R_>
class Line_2 : public R_::Line_2_base
{
public:
  typedef  R_   R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Line_2_base  RLine_2;

  Line_2()
    : RLine_2()
  {}

  Line_2(const CGAL::Line_2<R>  &l)
    : RLine_2(static_cast<const RLine_2&>(l))
  {}

  Line_2(const CGAL::Point_2<R> &p, const CGAL::Point_2<R> &q)
    : RLine_2(p,q)
  {}

  Line_2(const RT &a, const RT &b, const RT &c)
    : RLine_2(a,b,c)
  {}

  Line_2(const RLine_2& l)  // conversion impl -> interface class
    : RLine_2(l)
  {}

  Line_2(const CGAL::Segment_2<R>& s)
    : RLine_2(s)
  {}

  Line_2(const CGAL::Ray_2<R>& r)
    : RLine_2(r)
  {}

  Line_2(const CGAL::Point_2<R> &p, const CGAL::Direction_2<R> &d)
    : RLine_2(p,d)
  {}

  CGAL::Line_2<R> perpendicular(const CGAL::Point_2<R> &p) const
  {
    return RLine_2::perpendicular(p);
  }

  CGAL::Line_2<R> opposite() const
  {
    return RLine_2::opposite();
  }

  CGAL::Point_2<R> point(int i) const
  {
    return RLine_2::point(i);
  }

  CGAL::Point_2<R> projection(const CGAL::Point_2<R> &p) const
  {
    return RLine_2::projection(p);
  }

  CGAL::Point_2<R> point() const
  {
    return RLine_2::point();
  }

  CGAL::Direction_2<R> direction() const
  {
    return RLine_2::direction();
  }

  CGAL::Line_2<R> transform(const CGAL::Aff_transformation_2<R> &t) const
  {
    return  RLine_2::transform(t);
  }
};

#ifndef CGAL_NO_OSTREAM_INSERT_LINE_2
template < class R >
std::ostream &
operator<<(std::ostream &os, const Line_2<R> &l)
{
  typedef typename  R::Line_2_base  RLine_2;
  return os << static_cast<const RLine_2&>(l);
}
#endif // CGAL_NO_OSTREAM_INSERT_LINE_2

#ifndef CGAL_NO_ISTREAM_EXTRACT_LINE_2
template < class R >
std::istream &
operator>>(std::istream &is, Line_2<R> &p)
{
  typedef typename  R::Line_2_base  RLine_2;
  return is >> static_cast<RLine_2&>(p);
}
#endif // CGAL_NO_ISTREAM_EXTRACT_LINE_2

CGAL_END_NAMESPACE

#endif  // CGAL_LINE_2_H
