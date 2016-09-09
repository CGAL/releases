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
// file          : include/CGAL/Plane_3.h
// package       : _3 (3.31)
// revision      : $Revision: 1.10 $
// revision_date : $Date: 2002/01/23 12:30:07 $
// author(s)     : Andreas Fabri, Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 
#ifndef CGAL_PLANE_3_H
#define CGAL_PLANE_3_H

CGAL_BEGIN_NAMESPACE

template <class R_>
class Plane_3 : public R_::Kernel_base::Plane_3
{
  typedef typename R_::RT                    RT;
  typedef typename R_::Point_3               Point_3;
  typedef typename R_::Direction_3           Direction_3;
  typedef typename R_::Vector_3              Vector_3;
  typedef typename R_::Segment_3             Segment_3;
  typedef typename R_::Line_3                Line_3;
  typedef typename R_::Ray_3                 Ray_3;
  typedef typename R_::Kernel_base::Plane_3  RPlane_3;
public:
  typedef          R_                       R;

  Plane_3()
      : RPlane_3() {}

  Plane_3(const CGAL::Plane_3<R>& p)
      : RPlane_3(p) {}

  Plane_3(const RPlane_3& p)
      : RPlane_3(p) {}

  Plane_3(const Point_3& p, const Point_3& q, const Point_3& r)
    : RPlane_3(p,q,r) {}

  Plane_3(const Point_3& p, const Direction_3& d)
    : RPlane_3(p,d) {}

  Plane_3(const Point_3& p, const Vector_3& v)
    : RPlane_3(p,v) {}

  Plane_3(const RT& a, const RT& b, const RT& c, const RT& d)
    : RPlane_3(a,b,c,d) {}

  Plane_3(const Line_3& l, const Point_3& p)
    : RPlane_3(l,p) {}

  Plane_3(const Segment_3& s, const Point_3& p)
    : RPlane_3(s,p) {}

  Plane_3(const Ray_3& r, const Point_3& p)
    : RPlane_3(r,p) {}
};

#ifndef CGAL_NO_OSTREAM_INSERT_PLANE_3
template < class R >
std::ostream&
operator<<(std::ostream& os, const Plane_3<R>& p)
{
  typedef typename  R::Kernel_base::Plane_3  RPlane_3;
  return os << static_cast<const RPlane_3&>(p);
}
#endif // CGAL_NO_OSTREAM_INSERT_PLANE_3

#ifndef CGAL_NO_ISTREAM_EXTRACT_PLANE_3
template < class R >
std::istream&
operator>>(std::istream& is, Plane_3<R>& t)
{
  typedef typename  R::Kernel_base::Plane_3  RPlane_3;
  return is >> static_cast<RPlane_3&>(t);
}
#endif // CGAL_NO_ISTREAM_EXTRACT_PLANE_3

CGAL_END_NAMESPACE

#endif // CGAL_PLANE_3_H
