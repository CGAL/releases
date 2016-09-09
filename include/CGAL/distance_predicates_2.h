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
// source        : distance_predicates_2.fw
// file          : include/CGAL/distance_predicates_2.h
// package       : _2 (2.1.2)
// revision      : 2.1.2
// revision_date : 09 May 1999 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_DISTANCE_PREDICATES_2_H
#define CGAL_DISTANCE_PREDICATES_2_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#ifndef CGAL_DISTANCE_PREDICATESH2_H
#include <CGAL/distance_predicatesH2.h>
#endif // CGAL_DISTANCE_PREDICATESH2_H
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#ifndef CGAL_DISTANCE_PREDICATESC2_H
#include <CGAL/distance_predicatesC2.h>
#endif // CGAL_DISTANCE_PREDICATESC2_H
#endif // CGAL_CARTESIAN_H

#ifndef CGAL_POINT_2_H
#include <CGAL/Point_2.h>
#endif // CGAL_POINT_2_H
#ifndef CGAL_LINE_2_H
#include <CGAL/Line_2.h>
#endif // CGAL_LINE_2_H

CGAL_BEGIN_NAMESPACE


template < class R >
inline
Comparison_result
cmp_dist_to_point(const Point_2<R>& p,
                  const Point_2<R>& q,
                  const Point_2<R>& r)
{
  typedef typename  R::Point_2    RPoint_2;
  return cmp_dist_to_point((const RPoint_2& )p,
                           (const RPoint_2& )q,
                           (const RPoint_2& )r );
}

template < class R >
inline
bool
has_larger_dist_to_point(const Point_2<R>& p,
                         const Point_2<R>& q,
                         const Point_2<R>& r)
{
  typedef typename  R::Point_2    RPoint_2;
  return has_larger_dist_to_point((const RPoint_2& )p,
                                  (const RPoint_2& )q,
                                  (const RPoint_2& )r );
}

template < class R >
inline
bool
has_smaller_dist_to_point(const Point_2<R>& p,
                               const Point_2<R>& q,
                               const Point_2<R>& r)
{
  typedef typename  R::Point_2    RPoint_2;
  return has_smaller_dist_to_point((const RPoint_2& )p,
                                        (const RPoint_2& )q,
                                        (const RPoint_2& )r );
}

template < class R >
inline
Comparison_result
cmp_signed_dist_to_line(const Line_2<R>&  l,
                        const Point_2<R>& p,
                        const Point_2<R>& q)
{
  typedef typename  R::Point_2    RPoint_2;
  typedef typename  R::Line_2     RLine_2 ;
  return cmp_signed_dist_to_line((const RLine_2& )l,
                                      (const RPoint_2& )p,
                                      (const RPoint_2& )q );
}

template < class R >
inline
bool
has_larger_signed_dist_to_line(const Line_2<R>&  l,
                                    const Point_2<R>& p,
                                    const Point_2<R>& q)
{
  typedef typename  R::Point_2    RPoint_2;
  typedef typename  R::Line_2     RLine_2 ;
  return has_larger_signed_dist_to_line((const RLine_2& )l,
                                             (const RPoint_2& )p,
                                             (const RPoint_2& )q );
}

template < class R >
inline
bool
has_smaller_signed_dist_to_line(const Line_2<R>&  l,
                                     const Point_2<R>& p,
                                     const Point_2<R>& q)
{
  typedef typename  R::Point_2    RPoint_2;
  typedef typename  R::Line_2     RLine_2 ;
  return has_smaller_signed_dist_to_line((const RLine_2& )l,
                                              (const RPoint_2& )p,
                                              (const RPoint_2& )q );
}

template < class R >
inline
Comparison_result
cmp_signed_dist_to_line(const Point_2<R>& p,
                             const Point_2<R>& q,
                             const Point_2<R>& r,
                             const Point_2<R>& s)
{
  typedef typename  R::Point_2    RPoint_2;
  return cmp_signed_dist_to_line((const RPoint_2& )p,
                                      (const RPoint_2& )q,
                                      (const RPoint_2& )r,
                                      (const RPoint_2& )s );
}

template < class R >
inline
bool
has_smaller_signed_dist_to_line(const Point_2<R>& p,
                                     const Point_2<R>& q,
                                     const Point_2<R>& r,
                                     const Point_2<R>& s)
{
  typedef typename  R::Point_2    RPoint_2;
  return has_smaller_signed_dist_to_line((const RPoint_2& )p,
                                              (const RPoint_2& )q,
                                              (const RPoint_2& )r,
                                              (const RPoint_2& )s );
}

template < class R >
inline
bool
has_larger_signed_dist_to_line(const Point_2<R>& p,
                                    const Point_2<R>& q,
                                    const Point_2<R>& r,
                                    const Point_2<R>& s)
{
  typedef typename  R::Point_2    RPoint_2;
  return has_larger_signed_dist_to_line((const RPoint_2& )p,
                                             (const RPoint_2& )q,
                                             (const RPoint_2& )r,
                                             (const RPoint_2& )s );
}

CGAL_END_NAMESPACE


#endif //CGAL_DISTANCE_PREDICATES_2_H
