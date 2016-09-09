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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.4
// release_date  : 2002, May 16
// 
// file          : include/CGAL/Line_3.h
// package       : _3 (3.31)
// revision      : $Revision: 1.10 $
// revision_date : $Date: 2002/01/23 12:30:06 $
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_LINE_3_H
#define CGAL_LINE_3_H

CGAL_BEGIN_NAMESPACE

template <class R_>
class Line_3 : public R_::Kernel_base::Line_3
{
  typedef typename R_::RT                    RT;
  typedef typename R_::Point_3               Point_3;
  typedef typename R_::Ray_3                 Ray_3;
  typedef typename R_::Segment_3             Segment_3;
  typedef typename R_::Direction_3           Direction_3;
  typedef typename R_::Kernel_base::Line_3  RLine_3;
public:
  typedef          R_                       R;

  Line_3() : RLine_3()
  {}

  Line_3(const CGAL::Line_3<R>  & l)
      : RLine_3( static_cast<const RLine_3&>(l)) {}

  Line_3(const Point_3 & p, const Point_3 & q)
      : RLine_3(p,q) {}

  // conversion impl -> interface class
  Line_3(const RLine_3& l)
      : RLine_3(l) {}

  Line_3(const Segment_3 & s)
      : RLine_3( s ) {}

  Line_3(const Ray_3 & r)
      : RLine_3( r ) {}

  Line_3(const Point_3 & p, const Direction_3 & d)
      : RLine_3( p, d ) {}
};

#ifndef CGAL_NO_OSTREAM_INSERT_LINE_3
template < class R >
std::ostream&
operator<<(std::ostream& os, const Line_3<R>& l)
{
  typedef typename  R::Kernel_base::Line_3  RLine_3;
  return os << static_cast<const RLine_3&>(l);
}
#endif // CGAL_NO_OSTREAM_INSERT_LINE_3

#ifndef CGAL_NO_ISTREAM_EXTRACT_LINE_3
template < class R >
std::istream&
operator>>(std::istream & is, Line_3<R> & p)
{
  typedef typename  R::Kernel_base::Line_3  RLine_3;
  is >> static_cast<RLine_3&>(p);
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_LINE_3

CGAL_END_NAMESPACE

#endif // CGAL_LINE_3_H
