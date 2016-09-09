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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/Cartesian/distance_predicates_2.h
// package       : Cartesian_kernel (6.24)
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2001/07/23 17:31:11 $
// author(s)     : Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_DISTANCE_PREDICATES_2_H
#define CGAL_CARTESIAN_DISTANCE_PREDICATES_2_H

#include <CGAL/Cartesian/redefine_names_2.h>
#include <CGAL/predicates/kernel_ftC2.h>

CGAL_BEGIN_NAMESPACE

template <class R >
inline
Comparison_result
compare_distance_to_point(const PointC2<R CGAL_CTAG>& p,
                          const PointC2<R CGAL_CTAG>& q,
                          const PointC2<R CGAL_CTAG>& r)
{
  return cmp_dist_to_pointC2(p.x(), p.y(), q.x(), q.y(), r.x(), r.y());
}

template <class R>
inline
bool
has_larger_distance_to_point(const PointC2<R CGAL_CTAG>& p,
                             const PointC2<R CGAL_CTAG>& q,
                             const PointC2<R CGAL_CTAG>& r)
{
  return has_larger_dist_to_pointC2(p.x(), p.y(), q.x(), q.y(), r.x(), r.y());
}

template <class R>
inline
bool
has_smaller_distance_to_point(const PointC2<R CGAL_CTAG>& p,
                              const PointC2<R CGAL_CTAG>& q,
                              const PointC2<R CGAL_CTAG>& r)
{
  return has_smaller_dist_to_pointC2(p.x(), p.y(), q.x(), q.y(), r.x(), r.y());
}

template <class R>
inline
Comparison_result
compare_signed_distance_to_line(const LineC2<R CGAL_CTAG>&  l,
                                const PointC2<R CGAL_CTAG>& p,
                                const PointC2<R CGAL_CTAG>& q)
{
  return cmp_signed_dist_to_directionC2(l.a(), l.b(), p.x(), p.y(),
                                        q.x(), q.y());
}

template <class R>
inline
bool
has_larger_signed_distance_to_line(const LineC2<R CGAL_CTAG>&  l,
                                   const PointC2<R CGAL_CTAG>& p,
                                   const PointC2<R CGAL_CTAG>& q)
{
  return has_larger_signed_dist_to_directionC2(l.a(), l.b(), p.x(), p.y(),
                                               q.x(), q.y());
}

template <class R>
inline
bool
has_smaller_signed_distance_to_line(const LineC2<R CGAL_CTAG>&  l,
                                    const PointC2<R CGAL_CTAG>& p,
                                    const PointC2<R CGAL_CTAG>& q)
{
  return has_smaller_signed_dist_to_directionC2(l.a(), l.b(), p.x(), p.y(),
                                                q.x(), q.y());
}

template <class R>
inline
Comparison_result
compare_signed_distance_to_line(const PointC2<R CGAL_CTAG>& p,
                                const PointC2<R CGAL_CTAG>& q,
                                const PointC2<R CGAL_CTAG>& r,
                                const PointC2<R CGAL_CTAG>& s)
{
  return cmp_signed_dist_to_lineC2(p.x(), p.y(), q.x(), q.y(),
                                   r.x(), r.y(), s.x(), s.y());
}

template <class R>
inline
bool
has_smaller_signed_distance_to_line(const PointC2<R CGAL_CTAG>& p,
                                    const PointC2<R CGAL_CTAG>& q,
                                    const PointC2<R CGAL_CTAG>& r,
                                    const PointC2<R CGAL_CTAG>& s)
{
  return has_smaller_signed_dist_to_lineC2(p.x(), p.y(), q.x(), q.y(),
                                           r.x(), r.y(), s.x(), s.y());
}

template <class R>
inline
bool
has_larger_signed_distance_to_line(const PointC2<R CGAL_CTAG>& p,
                                   const PointC2<R CGAL_CTAG>& q,
                                   const PointC2<R CGAL_CTAG>& r,
                                   const PointC2<R CGAL_CTAG>& s)
{
  return has_larger_signed_dist_to_lineC2(p.x(), p.y(), q.x(), q.y(),
                                          r.x(), r.y(), s.x(), s.y());
}

#ifndef CGAL_NO_DEPRECATED_CODE
template <class R >
inline
Comparison_result
cmp_dist_to_point(const PointC2<R CGAL_CTAG>& p,
                  const PointC2<R CGAL_CTAG>& q,
                  const PointC2<R CGAL_CTAG>& r)
{
  return cmp_dist_to_pointC2(p.x(), p.y(), q.x(), q.y(), r.x(), r.y());
}

template <class R>
inline
bool
has_larger_dist_to_point(const PointC2<R CGAL_CTAG>& p,
                         const PointC2<R CGAL_CTAG>& q,
                         const PointC2<R CGAL_CTAG>& r)
{
  return has_larger_dist_to_pointC2(p.x(), p.y(), q.x(), q.y(), r.x(), r.y());
}

template <class R>
inline
bool
has_smaller_dist_to_point(const PointC2<R CGAL_CTAG>& p,
                          const PointC2<R CGAL_CTAG>& q,
                          const PointC2<R CGAL_CTAG>& r)
{
  return has_smaller_dist_to_pointC2(p.x(), p.y(), q.x(), q.y(), r.x(), r.y());
}

template <class R>
inline
Comparison_result
cmp_signed_dist_to_line(const LineC2<R CGAL_CTAG>&  l,
                        const PointC2<R CGAL_CTAG>& p,
                        const PointC2<R CGAL_CTAG>& q)
{
  return cmp_signed_dist_to_directionC2(l.a(), l.b(), p.x(), p.y(),
                                        q.x(), q.y());
}

template <class R>
inline
bool
has_larger_signed_dist_to_line(const LineC2<R CGAL_CTAG>&  l,
                               const PointC2<R CGAL_CTAG>& p,
                               const PointC2<R CGAL_CTAG>& q)
{
  return has_larger_signed_dist_to_directionC2(l.a(), l.b(), p.x(), p.y(),
                                               q.x(), q.y());
}

template <class R>
inline
bool
has_smaller_signed_dist_to_line(const LineC2<R CGAL_CTAG>&  l,
                                const PointC2<R CGAL_CTAG>& p,
                                const PointC2<R CGAL_CTAG>& q)
{
  return has_smaller_signed_dist_to_directionC2(l.a(), l.b(), p.x(), p.y(),
                                                q.x(), q.y());
}

template <class R>
inline
Comparison_result
cmp_signed_dist_to_line(const PointC2<R CGAL_CTAG>& p,
                        const PointC2<R CGAL_CTAG>& q,
                        const PointC2<R CGAL_CTAG>& r,
                        const PointC2<R CGAL_CTAG>& s)
{
  return cmp_signed_dist_to_lineC2(p.x(), p.y(), q.x(), q.y(),
                                   r.x(), r.y(), s.x(), s.y());
}

template <class R>
inline
bool
has_smaller_signed_dist_to_line(const PointC2<R CGAL_CTAG>& p,
                                const PointC2<R CGAL_CTAG>& q,
                                const PointC2<R CGAL_CTAG>& r,
                                const PointC2<R CGAL_CTAG>& s)
{
  return has_smaller_signed_dist_to_lineC2(p.x(), p.y(), q.x(), q.y(),
                                           r.x(), r.y(), s.x(), s.y());
}

template <class R>
inline
bool
has_larger_signed_dist_to_line(const PointC2<R CGAL_CTAG>& p,
                               const PointC2<R CGAL_CTAG>& q,
                               const PointC2<R CGAL_CTAG>& r,
                               const PointC2<R CGAL_CTAG>& s)
{
  return has_larger_signed_dist_to_lineC2(p.x(), p.y(), q.x(), q.y(),
                                          r.x(), r.y(), s.x(), s.y());
}
#endif

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_DISTANCE_PREDICATES_2_H
