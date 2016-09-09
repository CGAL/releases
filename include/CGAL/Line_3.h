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
// file          : include/CGAL/Line_3.h
// package       : _3 (3.23)
// revision      : $Revision: 1.8 $
// revision_date : $Date: 2001/06/27 14:49:52 $
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_LINE_3_H
#define CGAL_LINE_3_H

#include <CGAL/Segment_3.h>
#include <CGAL/Point_3.h>
#include <CGAL/Ray_3.h>
#include <CGAL/Plane_3.h>

CGAL_BEGIN_NAMESPACE

template <class R_>
class Line_3 : public R_::Line_3_base
{
public:
  typedef          R_                       R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Line_3_base  RLine_3;

  Line_3() : RLine_3()
  {}

  Line_3(const CGAL::Line_3<R>  & l)
      : RLine_3( static_cast<const RLine_3&>(l))
  {}

  Line_3(const CGAL::Point_3<R> & p, const CGAL::Point_3<R> & q)
      : RLine_3(p,q)
  {}

  // conversion impl -> interface class
  Line_3(const RLine_3&  l) : RLine_3(l)
  {}

  Line_3(const CGAL::Segment_3<R> & s) : RLine_3( s )
  {}

  Line_3(const CGAL::Ray_3<R> & r) : RLine_3( r )
  {}

  Line_3(const CGAL::Point_3<R> & p, const CGAL::Direction_3<R> & d)
      : RLine_3( p, d )
  {}

  CGAL::Plane_3<R>     perpendicular_plane(const CGAL::Point_3<R> & p) const
  { return RLine_3::perpendicular_plane(p); }

  CGAL::Line_3<R>      opposite() const
  { return RLine_3::opposite(); }

  CGAL::Point_3<R>     point() const
  { return RLine_3::point(); }

  CGAL::Point_3<R>     point(int i) const
  { return RLine_3::point(i); }

  CGAL::Point_3<R>     projection(const CGAL::Point_3<R>& p) const
  { return RLine_3::projection(p); }

  CGAL::Direction_3<R> direction() const
  { return RLine_3::direction(); }

  CGAL::Line_3<R>      transform(const CGAL::Aff_transformation_3<R> & t) const
  { return RLine_3::transform(t); }
};

#ifndef CGAL_NO_OSTREAM_INSERT_LINE_3
template < class R >
std::ostream&
operator<<(std::ostream& os, const Line_3<R>& l)
{
  typedef typename  R::Line_3_base  RLine_3;
  return os << static_cast<const RLine_3&>(l);
}
#endif // CGAL_NO_OSTREAM_INSERT_LINE_3

#ifndef CGAL_NO_ISTREAM_EXTRACT_LINE_3
template < class R >
std::istream&
operator>>(std::istream & is, Line_3<R> & p)
{
  typedef typename  R::Line_3_base  RLine_3;
  is >> static_cast<RLine_3&>(p);
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_LINE_3

CGAL_END_NAMESPACE

#endif // CGAL_LINE_3_H
