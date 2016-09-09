// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/distance_predicatesC3.h
// package       : C3 (2.1.5)
// source        : web/distance_predicatesC3.fw
// revision      : $Revision: 1.3 $
// revision_date : $Date: 1999/03/11 18:09:56 $
// author(s)     : Herve.Bronnimann
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef DISTANCE_PREDICATESC3_H
#define DISTANCE_PREDICATESC3_H

#ifndef CGAL_POINTC3_H
#include <CGAL/PointC3.h>
#endif
#ifndef CGAL_PLANEC3_H
#include <CGAL/PlaneC3.h>
#endif
#ifndef CGAL_PREDICATES_ON_FTC3_H
#include <CGAL/predicates_on_ftC3.h>
#endif

CGAL_BEGIN_NAMESPACE

template < class FT >
CGAL_KERNEL_LARGE_INLINE
Comparison_result
cmp_dist_to_point(const PointC3<FT> &p,
                  const PointC3<FT> &q,
                  const PointC3<FT> &r)
{
  return cmp_dist_to_pointC3(p.x(),p.y(),p.z(),
                             q.x(),q.y(),q.z(),
                             r.x(),r.y(),r.z());
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
bool
has_larger_dist_to_point(const PointC3<FT> &p,
                         const PointC3<FT> &q,
                         const PointC3<FT> &r)
{
  return has_larger_dist_to_pointC3(p.x(),p.y(),p.z(),
                                    q.x(),q.y(),q.z(),
                                    r.x(),r.y(),r.z());
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
bool
has_smaller_dist_to_point(const PointC3<FT> &p,
                          const PointC3<FT> &q,
                          const PointC3<FT> &r)
{
  return has_smaller_dist_to_pointC3(p.x(),p.y(),p.z(),
                                     q.x(),q.y(),q.z(),
                                     r.x(),r.y(),r.z());
}
template < class FT >
CGAL_KERNEL_LARGE_INLINE
Comparison_result
cmp_signed_dist_to_plane(const PlaneC3<FT> &h,
                         const PointC3<FT> &p,
                         const PointC3<FT> &q)
{
  return cmp_signed_dist_to_directionC3(h.a(),h.b(),h.c(),
                                        p.x(),p.y(),p.z(),
                                        q,x(),q.y(),q.z());
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
bool
has_larger_signed_dist_to_plane(const PlaneC3<FT> &h,
                                const PointC3<FT> &p,
                                const PointC3<FT> &q)
{
  return has_larger_signed_dist_to_directionC3(h.a(),h.b(),h.c(),
                                               p.x(),p.y(),p.z(),
                                               q,x(),q.y(),q.z());
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
bool
has_smaller_signed_dist_to_plane(const PlaneC3<FT> &h,
                                 const PointC3<FT> &p,
                                 const PointC3<FT> &q)
{
  return has_smaller_signed_dist_to_directionC3(h.a(),h.b(),h.c(),
                                                p.x(),p.y(),p.z(),
                                                q,x(),q.y(),q.z());
}
template < class FT >
CGAL_KERNEL_LARGE_INLINE
Comparison_result
cmp_signed_dist_to_plane(const PointC3<FT> &hp,
                         const PointC3<FT> &hq,
                         const PointC3<FT> &hr,
                         const PointC3<FT> &p,
                         const PointC3<FT> &q)
{
  return cmp_signed_dist_to_planeC3(hp.x(),hp.y(),hp.z(),
                                    hq.x(),hq.y(),hq.z(),
                                    hr.x(),hr.y(),hr.z(),
                                    p.x(),p.y(),p.z(),
                                    q,x(),q.y(),q.z());
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
bool
has_larger_signed_dist_to_plane(const PointC3<FT> &hp,
                                const PointC3<FT> &hq,
                                const PointC3<FT> &hr,
                                const PointC3<FT> &p,
                                const PointC3<FT> &q)
{
  return has_larger_signed_dist_to_planeC3(hp.x(),hp.y(),hp.z(),
                                           hq.x(),hq.y(),hq.z(),
                                           hr.x(),hr.y(),hr.z(),
                                           p.x(),p.y(),p.z(),
                                           q,x(),q.y(),q.z());
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
bool
has_smaller_signed_dist_to_plane(const PointC3<FT> &hp,
                                 const PointC3<FT> &hq,
                                 const PointC3<FT> &hr,
                                 const PointC3<FT> &p,
                                 const PointC3<FT> &q)
{
  return has_smaller_signed_dist_to_planeC3(hp.x(),hp.y(),hp.z(),
                                            hq.x(),hq.y(),hq.z(),
                                            hr.x(),hr.y(),hr.z(),
                                            p.x(),p.y(),p.z(),
                                            q,x(),q.y(),q.z());
}


CGAL_END_NAMESPACE

#endif // DISTANCE_PREDICATESC3_H
