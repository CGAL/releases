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
// file          : include/CGAL/Ray_3.h
// package       : _3 (3.31)
// revision      : $Revision: 1.10 $
// revision_date : $Date: 2002/01/23 12:30:09 $
// author(s)     : Andreas Fabri, Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 
#ifndef CGAL_RAY_3_H
#define CGAL_RAY_3_H

CGAL_BEGIN_NAMESPACE

template <class R_>
class Ray_3 : public R_::Kernel_base::Ray_3
{
  typedef typename R_::RT                    RT;
  typedef typename R_::Point_3               Point_3;
  typedef typename R_::Direction_3           Direction_3;
  typedef typename R_::Kernel_base::Ray_3  RRay_3;
public:
  typedef          R_                       R;

  Ray_3()
      : RRay_3() {}

  Ray_3(const CGAL::Ray_3<R>& r)
      : RRay_3(r) {}

  Ray_3(const RRay_3& r)
      : RRay_3(r) {}

  Ray_3(const Point_3& sp, const Point_3& secondp)
    : RRay_3(sp, secondp) {}

  Ray_3(const Point_3& sp, const Direction_3& d)
    : RRay_3(sp, d) {}
};

#ifndef CGAL_NO_OSTREAM_INSERT_RAY_3
template < class R >
std::ostream&
operator<<(std::ostream& os, const Ray_3<R>& r)
{
  typedef typename  R::Kernel_base::Ray_3  RRay_3;
  return os << static_cast<const RRay_3&>(r);
}
#endif // CGAL_NO_OSTREAM_INSERT_RAY_3

#ifndef CGAL_NO_ISTREAM_EXTRACT_RAY_3
template < class R >
std::istream&
operator>>(std::istream& is, Ray_3<R>& r)
{
  typedef typename  R::Kernel_base::Ray_3  RRay_3;
  return is >> static_cast<RRay_3&>(r);
}
#endif // CGAL_NO_ISTREAM_EXTRACT_RAY_3

CGAL_END_NAMESPACE

#endif // CGAL_RAY_3_H
