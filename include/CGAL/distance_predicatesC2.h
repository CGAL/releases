// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/distance_predicatesC2.h
// package       : C2 (1.7)
// source        : web/distance_predicatesC2.fw
// revision      : $Revision: 1.10 $
// revision_date : $Date: 1999/01/04 06:54:15 $
// author(s)     : Herve.Bronnimann
//
// coordinator   : INRIA Sophia-Antipolis
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_DISTANCE_PREDICATESC2_H
#define CGAL_DISTANCE_PREDICATESC2_H

#ifndef CGAL_PREDICATES_ON_FTC2_H
#include <CGAL/predicates_on_ftC2.h>
#endif // CGAL_PREDICATES_ON_FTC2_H

template <class FT >
inline
CGAL_Comparison_result
CGAL_cmp_dist_to_point(const CGAL_PointC2<FT>& p,
                       const CGAL_PointC2<FT>& q,
                       const CGAL_PointC2<FT>& r)
{
  return CGAL_cmp_dist_to_pointC2(p.x(),p.y(),q.x(),q.y(),r.x(),r.y());
}

template <class FT>
inline
bool
CGAL_has_larger_dist_to_point(const CGAL_PointC2<FT>& p,
                              const CGAL_PointC2<FT>& q,
                              const CGAL_PointC2<FT>& r)
{
  return CGAL_has_larger_dist_to_pointC2(p.x(),p.y(),q.x(),q.y(),r.x(),r.y());
}

template <class FT>
inline
bool
CGAL_has_smaller_dist_to_point(const CGAL_PointC2<FT>& p,
                               const CGAL_PointC2<FT>& q,
                               const CGAL_PointC2<FT>& r)
{
  return CGAL_has_smaller_dist_to_pointC2(p.x(),p.y(),q.x(),q.y(),r.x(),r.y());
}
template <class FT>
inline
CGAL_Comparison_result
CGAL_cmp_signed_dist_to_line(const CGAL_LineC2<FT>&  l,
                             const CGAL_PointC2<FT>& p,
                             const CGAL_PointC2<FT>& q)
{
  return CGAL_cmp_signed_dist_to_lineC2
           (l.a(),l.b(),l.c(),p.x(),p.y(),q.x(),q.y());
}

template <class FT>
inline
bool
CGAL_has_larger_signed_dist_to_line(const CGAL_LineC2<FT>&  l,
                                    const CGAL_PointC2<FT>& p,
                                    const CGAL_PointC2<FT>& q)
{
  return CGAL_has_larger_signed_dist_to_lineC2
           (l.a(),l.b(),l.c(),p.x(),p.y(),q.x(),q.y());
}

template <class FT>
inline
bool
CGAL_has_smaller_signed_dist_to_line(const CGAL_LineC2<FT>&  l,
                                     const CGAL_PointC2<FT>& p,
                                     const CGAL_PointC2<FT>& q)
{
  return CGAL_has_smaller_signed_dist_to_lineC2
           (l.a(),l.b(),l.c(),p.x(),p.y(),q.x(),q.y());
}
template <class FT>
inline
CGAL_Comparison_result
CGAL_cmp_signed_dist_to_line(const CGAL_PointC2<FT>& p,
                             const CGAL_PointC2<FT>& q,
                             const CGAL_PointC2<FT>& r,
                             const CGAL_PointC2<FT>& s)
{
  return CGAL_cmp_signed_dist_to_lineC2
           (p.x(),p.y(),q.x(),q.y(),r.x(),r.y(),s.x(),s.y());
}

template <class FT>
inline
bool
CGAL_has_smaller_signed_dist_to_line(const CGAL_PointC2<FT>& p,
                                     const CGAL_PointC2<FT>& q,
                                     const CGAL_PointC2<FT>& r,
                                     const CGAL_PointC2<FT>& s)
{
  return CGAL_has_smaller_signed_dist_to_lineC2
           (p.x(),p.y(),q.x(),q.y(),r.x(),r.y(),s.x(),s.y());
}

template <class FT>
inline
bool
CGAL_has_larger_signed_dist_to_line(const CGAL_PointC2<FT>& p,
                                    const CGAL_PointC2<FT>& q,
                                    const CGAL_PointC2<FT>& r,
                                    const CGAL_PointC2<FT>& s)
{
  return CGAL_has_larger_signed_dist_to_lineC2
           (p.x(),p.y(),q.x(),q.y(),r.x(),r.y(),s.x(),s.y());
}


#endif //CGAL_DISTANCE_PREDICATESC2_H
