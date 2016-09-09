// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// source        : webS2/S2.lw
// file          : include/CGAL/SimpleCartesian/distance_predicatesS2.h
// package       : S2 (1.7)
// revision      : 1.6
// revision_date : 27 Jun 2000
// author(s)     : Stefan Schirra
//                 based on code by
//                 Andreas Fabri and
//                 Herve Brönnimann
//
// coordinator   : MPI, Saarbrücken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================


#ifndef CGAL_DISTANCE_PREDICATESS2_H
#define CGAL_DISTANCE_PREDICATESS2_H

#include <CGAL/predicates/kernel_ftC2.h>

CGAL_BEGIN_NAMESPACE

template <class FT >
inline
Comparison_result
cmp_dist_to_point(const PointS2<FT>& p,
                  const PointS2<FT>& q,
                  const PointS2<FT>& r)
{
  return cmp_dist_to_pointC2(p.x(),p.y(),q.x(),q.y(),r.x(),r.y());
}

template <class FT>
inline
bool
has_larger_dist_to_point(const PointS2<FT>& p,
                         const PointS2<FT>& q,
                         const PointS2<FT>& r)
{
  return has_larger_dist_to_pointC2(p.x(),p.y(),q.x(),q.y(),r.x(),r.y());
}

template <class FT>
inline
bool
has_smaller_dist_to_point(const PointS2<FT>& p,
                          const PointS2<FT>& q,
                          const PointS2<FT>& r)
{
  return has_smaller_dist_to_pointC2(p.x(),p.y(),q.x(),q.y(),r.x(),r.y());
}
template <class FT>
inline
Comparison_result
cmp_signed_dist_to_line(const LineS2<FT>&  l,
                        const PointS2<FT>& p,
                        const PointS2<FT>& q)
{
  return cmp_signed_dist_to_directionC2
           (l.a(),l.b(),p.x(),p.y(),q.x(),q.y());
}

template <class FT>
inline
bool
has_larger_signed_dist_to_line(const LineS2<FT>&  l,
                               const PointS2<FT>& p,
                               const PointS2<FT>& q)
{
  return has_larger_signed_dist_to_directionC2
           (l.a(),l.b(),p.x(),p.y(),q.x(),q.y());
}

template <class FT>
inline
bool
has_smaller_signed_dist_to_line(const LineS2<FT>&  l,
                                const PointS2<FT>& p,
                                const PointS2<FT>& q)
{
  return has_smaller_signed_dist_to_directionC2
           (l.a(),l.b(),p.x(),p.y(),q.x(),q.y());
}
template <class FT>
inline
Comparison_result
cmp_signed_dist_to_line(const PointS2<FT>& p,
                        const PointS2<FT>& q,
                        const PointS2<FT>& r,
                        const PointS2<FT>& s)
{
  return cmp_signed_dist_to_lineC2
           (p.x(),p.y(),q.x(),q.y(),r.x(),r.y(),s.x(),s.y());
}

template <class FT>
inline
bool
has_smaller_signed_dist_to_line(const PointS2<FT>& p,
                                const PointS2<FT>& q,
                                const PointS2<FT>& r,
                                const PointS2<FT>& s)
{
  return has_smaller_signed_dist_to_lineC2
           (p.x(),p.y(),q.x(),q.y(),r.x(),r.y(),s.x(),s.y());
}

template <class FT>
inline
bool
has_larger_signed_dist_to_line(const PointS2<FT>& p,
                               const PointS2<FT>& q,
                               const PointS2<FT>& r,
                               const PointS2<FT>& s)
{
  return has_larger_signed_dist_to_lineC2
           (p.x(),p.y(),q.x(),q.y(),r.x(),r.y(),s.x(),s.y());
}


CGAL_END_NAMESPACE

#endif //CGAL_DISTANCE_PREDICATESS2_H
