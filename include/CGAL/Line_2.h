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
// file          : include/CGAL/Line_2.h
// package       : _2 (3.32)
// revision      : $Revision: 1.11 $
// revision_date : $Date: 2002/01/23 12:28:30 $
// author(s)     : Andreas Fabri
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_LINE_2_H
#define CGAL_LINE_2_H

CGAL_BEGIN_NAMESPACE

template <class R_>
class Line_2 : public R_::Kernel_base::Line_2
{
  typedef typename R_::RT                    RT;
  typedef typename R_::Point_2               Point_2;
  typedef typename R_::Segment_2             Segment_2;
  typedef typename R_::Ray_2                 Ray_2;
  typedef typename R_::Direction_2           Direction_2;
  typedef typename R_::Kernel_base::Line_2  RLine_2;
public:
  typedef  R_   R;

  Line_2()
    : RLine_2() {}

  Line_2(const CGAL::Line_2<R>  &l)
    : RLine_2(static_cast<const RLine_2&>(l)) {}

  Line_2(const Point_2 &p, const Point_2 &q)
    : RLine_2(p,q) {}

  Line_2(const RT &a, const RT &b, const RT &c)
    : RLine_2(a,b,c) {}

  Line_2(const RLine_2& l)  // conversion impl -> interface class
    : RLine_2(l) {}

  Line_2(const Segment_2& s)
    : RLine_2(s) {}

  Line_2(const Ray_2& r)
    : RLine_2(r) {}

  Line_2(const Point_2 &p, const Direction_2 &d)
    : RLine_2(p,d) {}
};

#ifndef CGAL_NO_OSTREAM_INSERT_LINE_2
template < class R >
std::ostream &
operator<<(std::ostream &os, const Line_2<R> &l)
{
  typedef typename  R::Kernel_base::Line_2  RLine_2;
  return os << static_cast<const RLine_2&>(l);
}
#endif // CGAL_NO_OSTREAM_INSERT_LINE_2

#ifndef CGAL_NO_ISTREAM_EXTRACT_LINE_2
template < class R >
std::istream &
operator>>(std::istream &is, Line_2<R> &p)
{
  typedef typename  R::Kernel_base::Line_2  RLine_2;
  return is >> static_cast<RLine_2&>(p);
}
#endif // CGAL_NO_ISTREAM_EXTRACT_LINE_2

CGAL_END_NAMESPACE

#endif  // CGAL_LINE_2_H
