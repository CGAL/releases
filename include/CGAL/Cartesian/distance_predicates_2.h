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
// file          : include/CGAL/Cartesian/distance_predicates_2.h
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

#ifndef CGAL_CARTESIAN_DISTANCE_PREDICATES_2_H
#define CGAL_CARTESIAN_DISTANCE_PREDICATES_2_H

#include <CGAL/predicates/kernel_ftC2.h>

CGAL_BEGIN_NAMESPACE

template <class R >
inline
Comparison_result
compare_distance_to_point(const PointC2<R>& p,
                          const PointC2<R>& q,
                          const PointC2<R>& r)
{
  return cmp_dist_to_pointC2(p.x(), p.y(), q.x(), q.y(), r.x(), r.y());
}

template <class R>
inline
bool
has_larger_distance_to_point(const PointC2<R>& p,
                             const PointC2<R>& q,
                             const PointC2<R>& r)
{
  return has_larger_dist_to_pointC2(p.x(), p.y(), q.x(), q.y(), r.x(), r.y());
}

template <class R>
inline
bool
has_smaller_distance_to_point(const PointC2<R>& p,
                              const PointC2<R>& q,
                              const PointC2<R>& r)
{
  return has_smaller_dist_to_pointC2(p.x(), p.y(), q.x(), q.y(), r.x(), r.y());
}

template <class R>
inline
Comparison_result
compare_signed_distance_to_line(const LineC2<R>&  l,
                                const PointC2<R>& p,
                                const PointC2<R>& q)
{
  return cmp_signed_dist_to_directionC2(l.a(), l.b(), p.x(), p.y(),
                                        q.x(), q.y());
}

template <class R>
inline
bool
has_larger_signed_distance_to_line(const LineC2<R>&  l,
                                   const PointC2<R>& p,
                                   const PointC2<R>& q)
{
  return has_larger_signed_dist_to_directionC2(l.a(), l.b(), p.x(), p.y(),
                                               q.x(), q.y());
}

template <class R>
inline
bool
has_smaller_signed_distance_to_line(const LineC2<R>&  l,
                                    const PointC2<R>& p,
                                    const PointC2<R>& q)
{
  return has_smaller_signed_dist_to_directionC2(l.a(), l.b(), p.x(), p.y(),
                                                q.x(), q.y());
}

template <class R>
inline
Comparison_result
compare_signed_distance_to_line(const PointC2<R>& p,
                                const PointC2<R>& q,
                                const PointC2<R>& r,
                                const PointC2<R>& s)
{
  return cmp_signed_dist_to_lineC2(p.x(), p.y(), q.x(), q.y(),
                                   r.x(), r.y(), s.x(), s.y());
}

template <class R>
inline
bool
has_smaller_signed_distance_to_line(const PointC2<R>& p,
                                    const PointC2<R>& q,
                                    const PointC2<R>& r,
                                    const PointC2<R>& s)
{
  return has_smaller_signed_dist_to_lineC2(p.x(), p.y(), q.x(), q.y(),
                                           r.x(), r.y(), s.x(), s.y());
}

template <class R>
inline
bool
has_larger_signed_distance_to_line(const PointC2<R>& p,
                                   const PointC2<R>& q,
                                   const PointC2<R>& r,
                                   const PointC2<R>& s)
{
  return has_larger_signed_dist_to_lineC2(p.x(), p.y(), q.x(), q.y(),
                                          r.x(), r.y(), s.x(), s.y());
}

#ifndef CGAL_NO_DEPRECATED_CODE
template <class R >
inline
Comparison_result
cmp_dist_to_point(const PointC2<R>& p,
                  const PointC2<R>& q,
                  const PointC2<R>& r)
{
  return cmp_dist_to_pointC2(p.x(), p.y(), q.x(), q.y(), r.x(), r.y());
}

template <class R>
inline
bool
has_larger_dist_to_point(const PointC2<R>& p,
                         const PointC2<R>& q,
                         const PointC2<R>& r)
{
  return has_larger_dist_to_pointC2(p.x(), p.y(), q.x(), q.y(), r.x(), r.y());
}

template <class R>
inline
bool
has_smaller_dist_to_point(const PointC2<R>& p,
                          const PointC2<R>& q,
                          const PointC2<R>& r)
{
  return has_smaller_dist_to_pointC2(p.x(), p.y(), q.x(), q.y(), r.x(), r.y());
}

template <class R>
inline
Comparison_result
cmp_signed_dist_to_line(const LineC2<R>&  l,
                        const PointC2<R>& p,
                        const PointC2<R>& q)
{
  return cmp_signed_dist_to_directionC2(l.a(), l.b(), p.x(), p.y(),
                                        q.x(), q.y());
}

template <class R>
inline
bool
has_larger_signed_dist_to_line(const LineC2<R>&  l,
                               const PointC2<R>& p,
                               const PointC2<R>& q)
{
  return has_larger_signed_dist_to_directionC2(l.a(), l.b(), p.x(), p.y(),
                                               q.x(), q.y());
}

template <class R>
inline
bool
has_smaller_signed_dist_to_line(const LineC2<R>&  l,
                                const PointC2<R>& p,
                                const PointC2<R>& q)
{
  return has_smaller_signed_dist_to_directionC2(l.a(), l.b(), p.x(), p.y(),
                                                q.x(), q.y());
}

template <class R>
inline
Comparison_result
cmp_signed_dist_to_line(const PointC2<R>& p,
                        const PointC2<R>& q,
                        const PointC2<R>& r,
                        const PointC2<R>& s)
{
  return cmp_signed_dist_to_lineC2(p.x(), p.y(), q.x(), q.y(),
                                   r.x(), r.y(), s.x(), s.y());
}

template <class R>
inline
bool
has_smaller_signed_dist_to_line(const PointC2<R>& p,
                                const PointC2<R>& q,
                                const PointC2<R>& r,
                                const PointC2<R>& s)
{
  return has_smaller_signed_dist_to_lineC2(p.x(), p.y(), q.x(), q.y(),
                                           r.x(), r.y(), s.x(), s.y());
}

template <class R>
inline
bool
has_larger_signed_dist_to_line(const PointC2<R>& p,
                               const PointC2<R>& q,
                               const PointC2<R>& r,
                               const PointC2<R>& s)
{
  return has_larger_signed_dist_to_lineC2(p.x(), p.y(), q.x(), q.y(),
                                          r.x(), r.y(), s.x(), s.y());
}
#endif

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_DISTANCE_PREDICATES_2_H
