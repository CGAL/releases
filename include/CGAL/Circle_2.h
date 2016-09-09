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
// file          : include/CGAL/Circle_2.h
// package       : _2 (3.32)
// revision      : $Revision: 1.8 $
// revision_date : $Date: 2002/01/23 12:28:29 $
// author(s)     : Andreas Fabri
//                 Sven Schoenherr
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CIRCLE_2_H
#define CGAL_CIRCLE_2_H

CGAL_BEGIN_NAMESPACE

template <class R_>
class Circle_2 : public R_::Kernel_base::Circle_2
{
  typedef typename R_::FT                    FT;
  typedef typename R_::Point_2               Point_2;
  typedef typename R_::Kernel_base::Circle_2  RCircle_2;
public:
  typedef  R_   R;

    Circle_2()
      : RCircle_2() {}

    Circle_2(const CGAL::Circle_2<R> &t)
      : RCircle_2((RCircle_2&)t) {}

    Circle_2(const RCircle_2& t)
      : RCircle_2(t) {}

    Circle_2(const Point_2 &center, const FT &squared_radius,
             const Orientation &orientation)
      : RCircle_2(center, squared_radius, orientation) {}

    Circle_2(const Point_2 &center, const FT &squared_radius)
      : RCircle_2(center, squared_radius, COUNTERCLOCKWISE) {}

    Circle_2(const Point_2 &p, const Point_2 &q, const Point_2 &r)
      : RCircle_2(p,q,r) {}

    Circle_2(const Point_2 & p, const Point_2 & q,
             const Orientation &orientation)
      : RCircle_2(p,q,orientation) {}

    Circle_2(const Point_2 & p, const Point_2 & q)
      : RCircle_2(p,q,COUNTERCLOCKWISE) {}

    Circle_2(const Point_2 & center, const Orientation& orientation)
      : RCircle_2(center,FT(0),orientation) {}

    Circle_2(const Point_2 & center)
      : RCircle_2(center,FT(0),COUNTERCLOCKWISE) {}
};

#ifndef CGAL_NO_OSTREAM_INSERT_CIRCLE_2
template < class R >
std::ostream &
operator<<(std::ostream &os, const Circle_2<R> &c)
{
  typedef typename R::Kernel_base::Circle_2  RCircle_2;
  return os << (const RCircle_2&)c;
}

#endif // CGAL_NO_OSTREAM_INSERT_CIRCLE_2

#ifndef CGAL_NO_ISTREAM_EXTRACT_CIRCLE_2
template < class R >
std::istream &
operator>>(std::istream &is, Circle_2<R> &c)
{
  typedef typename R::Kernel_base::Circle_2  RCircle_2;
  return is >> (RCircle_2&)c;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_CIRCLE_2

CGAL_END_NAMESPACE

#endif  // CGAL_CIRCLE_2_H
