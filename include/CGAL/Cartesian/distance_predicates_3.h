// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

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
// file          : include/CGAL/Cartesian/distance_predicates_3.h
// package       : Cartesian_kernel (6.59)
// revision      : $Revision: 1.5 $
// revision_date : $Date: 2002/01/23 17:59:12 $
// author(s)     : Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_DISTANCE_PREDICATES_3_H
#define CGAL_CARTESIAN_DISTANCE_PREDICATES_3_H

#include <CGAL/Cartesian/Point_3.h>
#include <CGAL/Cartesian/Plane_3.h>
#include <CGAL/predicates/kernel_ftC3.h>

CGAL_BEGIN_NAMESPACE

template < class R >
CGAL_KERNEL_LARGE_INLINE
Comparison_result
compare_distance_to_point(const PointC3<R> &p,
                          const PointC3<R> &q,
                          const PointC3<R> &r)
{
  return cmp_dist_to_pointC3(p.x(), p.y(), p.z(),
                             q.x(), q.y(), q.z(),
                             r.x(), r.y(), r.z());
}

template < class R >
CGAL_KERNEL_LARGE_INLINE
bool
has_larger_distance_to_point(const PointC3<R> &p,
                             const PointC3<R> &q,
                             const PointC3<R> &r)
{
  return has_larger_dist_to_pointC3(p.x(), p.y(), p.z(),
                                    q.x(), q.y(), q.z(),
                                    r.x(), r.y(), r.z());
}

template < class R >
CGAL_KERNEL_LARGE_INLINE
bool
has_smaller_distance_to_point(const PointC3<R> &p,
                              const PointC3<R> &q,
                              const PointC3<R> &r)
{
  return has_smaller_dist_to_pointC3(p.x(), p.y(), p.z(),
                                     q.x(), q.y(), q.z(),
                                     r.x(), r.y(), r.z());
}

template < class R >
CGAL_KERNEL_LARGE_INLINE
Comparison_result
compare_signed_distance_to_plane(const PlaneC3<R> &h,
                                 const PointC3<R> &p,
                                 const PointC3<R> &q)
{ // FIXME : probably not compiled by the test-suite.
  return cmp_signed_dist_to_directionC3(h.a(), h.b(), h.c(),
                                        p.x(), p.y(), p.z(),
                                        q.x(), q.y(), q.z());
}

template < class R >
CGAL_KERNEL_LARGE_INLINE
bool
has_larger_signed_distance_to_plane(const PlaneC3<R> &h,
                                    const PointC3<R> &p,
                                    const PointC3<R> &q)
{ // FIXME : probably not compiled by the test-suite.
  return has_larger_signed_dist_to_directionC3(h.a(), h.b(), h.c(),
                                               p.x(), p.y(), p.z(),
                                               q.x(), q.y(), q.z());
}

template < class R >
CGAL_KERNEL_LARGE_INLINE
bool
has_smaller_signed_distance_to_plane(const PlaneC3<R> &h,
                                     const PointC3<R> &p,
                                     const PointC3<R> &q)
{ // FIXME : probably not compiled by the test-suite.
  return has_smaller_signed_dist_to_directionC3(h.a(), h.b(), h.c(),
                                                p.x(), p.y(), p.z(),
                                                q.x(), q.y(), q.z());
}

template < class R >
CGAL_KERNEL_LARGE_INLINE
Comparison_result
compare_signed_distance_to_plane(const PointC3<R> &hp,
                                 const PointC3<R> &hq,
                                 const PointC3<R> &hr,
                                 const PointC3<R> &p,
                                 const PointC3<R> &q)
{ // FIXME : probably not compiled by the test-suite.
  return cmp_signed_dist_to_planeC3(hp.x(), hp.y(), hp.z(),
                                    hq.x(), hq.y(), hq.z(),
                                    hr.x(), hr.y(), hr.z(),
                                    p.x(),  p.y(),  p.z(),
                                    q.x(),  q.y(),  q.z());
}

template < class R >
CGAL_KERNEL_LARGE_INLINE
bool
has_larger_signed_distance_to_plane(const PointC3<R> &hp,
                                    const PointC3<R> &hq,
                                    const PointC3<R> &hr,
                                    const PointC3<R> &p,
                                    const PointC3<R> &q)
{ // FIXME : probably not compiled by the test-suite.
  return has_larger_signed_dist_to_planeC3(hp.x(), hp.y(), hp.z(),
                                           hq.x(), hq.y(), hq.z(),
                                           hr.x(), hr.y(), hr.z(),
                                           p.x(),  p.y(),  p.z(),
                                           q.x(),  q.y(),  q.z());
}

template < class R >
CGAL_KERNEL_LARGE_INLINE
bool
has_smaller_signed_distance_to_plane(const PointC3<R> &hp,
                                     const PointC3<R> &hq,
                                     const PointC3<R> &hr,
                                     const PointC3<R> &p,
                                     const PointC3<R> &q)
{ // FIXME : probably not compiled by the test-suite.
  return has_smaller_signed_dist_to_planeC3(hp.x(), hp.y(), hp.z(),
                                            hq.x(), hq.y(), hq.z(),
                                            hr.x(), hr.y(), hr.z(),
                                            p.x(),  p.y(),  p.z(),
                                            q.x(),  q.y(),  q.z());
}

#ifndef CGAL_NO_DEPRECATED_CODE
template < class R >
CGAL_KERNEL_LARGE_INLINE
Comparison_result
cmp_dist_to_point(const PointC3<R> &p,
                  const PointC3<R> &q,
                  const PointC3<R> &r)
{
  return cmp_dist_to_pointC3(p.x(), p.y(), p.z(),
                             q.x(), q.y(), q.z(),
                             r.x(), r.y(), r.z());
}

template < class R >
CGAL_KERNEL_LARGE_INLINE
bool
has_larger_dist_to_point(const PointC3<R> &p,
                         const PointC3<R> &q,
                         const PointC3<R> &r)
{
  return has_larger_dist_to_pointC3(p.x(), p.y(), p.z(),
                                    q.x(), q.y(), q.z(),
                                    r.x(), r.y(), r.z());
}

template < class R >
CGAL_KERNEL_LARGE_INLINE
bool
has_smaller_dist_to_point(const PointC3<R> &p,
                          const PointC3<R> &q,
                          const PointC3<R> &r)
{
  return has_smaller_dist_to_pointC3(p.x(), p.y(), p.z(),
                                     q.x(), q.y(), q.z(),
                                     r.x(), r.y(), r.z());
}

template < class R >
CGAL_KERNEL_LARGE_INLINE
Comparison_result
cmp_signed_dist_to_plane(const PlaneC3<R> &h,
                         const PointC3<R> &p,
                         const PointC3<R> &q)
{ // FIXME : probably not compiled by the test-suite.
  return cmp_signed_dist_to_directionC3(h.a(), h.b(), h.c(),
                                        p.x(), p.y(), p.z(),
                                        q.x(), q.y(), q.z());
}

template < class R >
CGAL_KERNEL_LARGE_INLINE
bool
has_larger_signed_dist_to_plane(const PlaneC3<R> &h,
                                const PointC3<R> &p,
                                const PointC3<R> &q)
{ // FIXME : probably not compiled by the test-suite.
  return has_larger_signed_dist_to_directionC3(h.a(), h.b(), h.c(),
                                               p.x(), p.y(), p.z(),
                                               q.x(), q.y(), q.z());
}

template < class R >
CGAL_KERNEL_LARGE_INLINE
bool
has_smaller_signed_dist_to_plane(const PlaneC3<R> &h,
                                 const PointC3<R> &p,
                                 const PointC3<R> &q)
{ // FIXME : probably not compiled by the test-suite.
  return has_smaller_signed_dist_to_directionC3(h.a(), h.b(), h.c(),
                                                p.x(), p.y(), p.z(),
                                                q.x(), q.y(), q.z());
}

template < class R >
CGAL_KERNEL_LARGE_INLINE
Comparison_result
cmp_signed_dist_to_plane(const PointC3<R> &hp,
                         const PointC3<R> &hq,
                         const PointC3<R> &hr,
                         const PointC3<R> &p,
                         const PointC3<R> &q)
{ // FIXME : probably not compiled by the test-suite.
  return cmp_signed_dist_to_planeC3(hp.x(), hp.y(), hp.z(),
                                    hq.x(), hq.y(), hq.z(),
                                    hr.x(), hr.y(), hr.z(),
                                    p.x(),  p.y(),  p.z(),
                                    q.x(),  q.y(),  q.z());
}

template < class R >
CGAL_KERNEL_LARGE_INLINE
bool
has_larger_signed_dist_to_plane(const PointC3<R> &hp,
                                const PointC3<R> &hq,
                                const PointC3<R> &hr,
                                const PointC3<R> &p,
                                const PointC3<R> &q)
{ // FIXME : probably not compiled by the test-suite.
  return has_larger_signed_dist_to_planeC3(hp.x(), hp.y(), hp.z(),
                                           hq.x(), hq.y(), hq.z(),
                                           hr.x(), hr.y(), hr.z(),
                                           p.x(),  p.y(),  p.z(),
                                           q.x(),  q.y(),  q.z());
}

template < class R >
CGAL_KERNEL_LARGE_INLINE
bool
has_smaller_signed_dist_to_plane(const PointC3<R> &hp,
                                 const PointC3<R> &hq,
                                 const PointC3<R> &hr,
                                 const PointC3<R> &p,
                                 const PointC3<R> &q)
{ // FIXME : probably not compiled by the test-suite.
  return has_smaller_signed_dist_to_planeC3(hp.x(), hp.y(), hp.z(),
                                            hq.x(), hq.y(), hq.z(),
                                            hr.x(), hr.y(), hr.z(),
                                            p.x(),  p.y(),  p.z(),
                                            q.x(),  q.y(),  q.z());
}

#endif

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_DISTANCE_PREDICATES_3_H
