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
// file          : include/CGAL/Point_2.h
// package       : _2 (3.32)
// revision      : $Revision: 1.11 $
// revision_date : $Date: 2002/01/23 12:28:31 $
// author(s)     : Andreas Fabri, Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_POINT_2_H
#define CGAL_POINT_2_H

class Origin;

CGAL_BEGIN_NAMESPACE

template <class R_>
class Point_2 : public R_::Kernel_base::Point_2
{
  typedef typename R_::RT                    RT;
  typedef typename R_::Vector_2       Vector_2;
  typedef typename R_::Kernel_base::Point_2  RPoint_2;
public:
  typedef  R_   R;

  Point_2()
  {}

  Point_2(const Origin& o)
    : RPoint_2(o)
  {}

  Point_2(const CGAL::Point_2<R>& p)
    : RPoint_2(static_cast<const RPoint_2&>(p))
  {}

  Point_2(const RPoint_2& p)
    : RPoint_2(p)
  {}

  Point_2(const RT& hx, const RT& hy)
    : RPoint_2(hx, hy)
  {}

  Point_2(const RT& hx, const RT& hy, const RT& hw)
    : RPoint_2(hx, hy, hw)
  {}
};

#ifndef CGAL_NO_OSTREAM_INSERT_POINT_2
template < class R >
std::ostream&
operator<<(std::ostream& os, const Point_2<R>& p)
{
  typedef typename  R::Kernel_base::Point_2  RPoint_2;
  return os << static_cast<const RPoint_2&>(p);
}
#endif // CGAL_NO_OSTREAM_INSERT_POINT_2

#ifndef CGAL_NO_ISTREAM_EXTRACT_POINT_2
template < class R >
std::istream&
operator>>(std::istream& is, Point_2<R>& p)
{
  typedef typename  R::Kernel_base::Point_2  RPoint_2;
  return is >> static_cast<RPoint_2&>(p);
}
#endif // CGAL_NO_ISTREAM_EXTRACT_POINT_2

CGAL_END_NAMESPACE

#endif // CGAL_POINT_2_H
