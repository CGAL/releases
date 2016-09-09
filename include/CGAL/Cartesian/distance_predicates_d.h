// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/Cartesian/distance_predicates_d.h
// package       : Cd (1.5)
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2000/06/27 14:32:33 $
// author(s)     : Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_DISTANCE_PREDICATES_D_H
#define CGAL_CARTESIAN_DISTANCE_PREDICATES_D_H

#include <CGAL/Cartesian/redefine_names_d.h>
#include <CGAL/Cartesian/Point_d.h>
#include <CGAL/Cartesian/Plane_d.h>
#include <CGAL/predicates/kernel_ftCd.h>

CGAL_BEGIN_NAMESPACE

template < class R >
CGAL_KERNEL_LARGE_INLINE
Comparison_result
cmp_dist_to_point(const PointCd<R CGAL_CTAG> &p,
                  const PointCd<R CGAL_CTAG> &q,
                  const PointCd<R CGAL_CTAG> &r)
{
  return cmp_dist_to_pointCd(p.begin(),p.end(),
                             q.begin(),q.end(),
                             r.begin(),r.end());
}

template < class R >
CGAL_KERNEL_LARGE_INLINE
bool
has_larger_dist_to_point(const PointCd<R CGAL_CTAG> &p,
                         const PointCd<R CGAL_CTAG> &q,
                         const PointCd<R CGAL_CTAG> &r)
{
  return has_larger_dist_to_pointCd(p.begin(),p.end(),
                                    q.begin(),q.end(),
                                    r.begin(),r.end());
}

template < class R >
CGAL_KERNEL_LARGE_INLINE
bool
has_smaller_dist_to_point(const PointCd<R CGAL_CTAG> &p,
                          const PointCd<R CGAL_CTAG> &q,
                          const PointCd<R CGAL_CTAG> &r)
{
  return has_smaller_dist_to_pointCd(p.begin(),p.end(),
                                     q.begin(),q.end(),
                                     r.begin(),r.end());
}

template < class R >
CGAL_KERNEL_LARGE_INLINE
Comparison_result
cmp_signed_dist_to_plane(const PlaneCd<R CGAL_CTAG> &h,
                         const PointCd<R CGAL_CTAG> &p,
                         const PointCd<R CGAL_CTAG> &q)
{
  return cmp_signed_dist_to_directionCd(h.begin(),h.end(),
                                        p.begin(),p.end(),
                                        q.begin(),q.end());
}

template < class R >
CGAL_KERNEL_LARGE_INLINE
bool
has_larger_signed_dist_to_plane(const PlaneCd<R CGAL_CTAG> &h,
                                const PointCd<R CGAL_CTAG> &p,
                                const PointCd<R CGAL_CTAG> &q)
{
  return has_larger_signed_dist_to_directionCd(h.begin(),h.end(),
                                               p.begin(),p.end(),
                                               q.begin(),q.end());
}

template < class R >
CGAL_KERNEL_LARGE_INLINE
bool
has_smaller_signed_dist_to_plane(const PlaneCd<R CGAL_CTAG> &h,
                                 const PointCd<R CGAL_CTAG> &p,
                                 const PointCd<R CGAL_CTAG> &q)
{
  return has_smaller_signed_dist_to_directionCd(h.begin(),h.end(),
                                                p.begin(),p.end(),
                                                q.begin(),q.end());
}

template < class R, class ForwardIterator >
CGAL_KERNEL_LARGE_INLINE
Comparison_result
cmp_signed_dist_to_plane(const ForwardIterator &first,
                         const ForwardIterator &last, 
                         const PointCd<R CGAL_CTAG> &p,
                         const PointCd<R CGAL_CTAG> &q)
{
  return cmp_signed_dist_to_planeCd(first, last,
                                    p.begin(),p.end(),
                                    q.begin(),q.end());
}

template < class R, class ForwardIterator >
CGAL_KERNEL_LARGE_INLINE
bool
has_larger_signed_dist_to_plane(const ForwardIterator &first,
                                const ForwardIterator &last, 
                                const PointCd<R CGAL_CTAG> &p,
                                const PointCd<R CGAL_CTAG> &q)
{
  return has_larger_signed_dist_to_planeCd(first, last,
                                           p.begin(),p.end(),
                                           q.begin(),q.end());
}

template < class R, class ForwardIterator >
CGAL_KERNEL_LARGE_INLINE
bool
has_smaller_signed_dist_to_plane(const ForwardIterator &first,
                                 const ForwardIterator &last, 
                                 const PointCd<R CGAL_CTAG> &p,
                                 const PointCd<R CGAL_CTAG> &q)
{
  return has_smaller_signed_dist_to_planeCd(first, last,
                                            p.begin(),p.end(),
                                            q.begin(),q.end());
}

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_DISTANCE_PREDICATES_3_H
