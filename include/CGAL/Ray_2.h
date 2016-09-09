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
// file          : include/CGAL/Ray_2.h
// package       : _2 (3.32)
// revision      : $Revision: 1.10 $
// revision_date : $Date: 2002/01/23 12:28:31 $
// author(s)     : Andreas Fabri
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_RAY_2_H
#define CGAL_RAY_2_H

CGAL_BEGIN_NAMESPACE

template <class R_>
class Ray_2 : public R_::Kernel_base::Ray_2
{
  typedef typename R_::RT                    RT;
  typedef typename R_::Point_2               Point_2;
  typedef typename R_::Direction_2           Direction_2;
  typedef typename R_::Kernel_base::Ray_2  RRay_2;
public:
  typedef  R_   R;

  Ray_2()
    : RRay_2() {}

  Ray_2(const CGAL::Ray_2<R> &r)
    : RRay_2(static_cast<const RRay_2&>(r)) {}

  Ray_2(const RRay_2& r)
    : RRay_2(r) {}

  Ray_2(const Point_2 &sp, const Point_2 &secondp)
    : RRay_2(sp, secondp) {}

  Ray_2(const Point_2 &sp, const Direction_2 &d)
    : RRay_2(sp, d) {}
};

#ifndef CGAL_NO_OSTREAM_INSERT_RAY_2
template < class R >
std::ostream &
operator<<(std::ostream &os, const Ray_2<R> &r)
{
  typedef typename  R::Kernel_base::Ray_2  RRay_2;
  return os << static_cast<const RRay_2&>(r);
}
#endif // CGAL_NO_OSTREAM_INSERT_RAY_2

#ifndef CGAL_NO_ISTREAM_EXTRACT_RAY_2
template < class R >
std::istream &
operator>>(std::istream &is, Ray_2<R> &r)
{
  typedef typename  R::Kernel_base::Ray_2  RRay_2;
  return is >> static_cast<RRay_2&>(r);
}
#endif // CGAL_NO_ISTREAM_EXTRACT_RAY_2

CGAL_END_NAMESPACE

#endif  // CGAL_RAY_2_H
