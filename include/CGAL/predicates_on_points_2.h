// ============================================================================
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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/predicates_on_points_2.h
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// email         : cgal@cs.uu.nl
//
// ============================================================================
 

#ifndef CGAL_PREDICATES_ON_POINTS_2_H
#define CGAL_PREDICATES_ON_POINTS_2_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#ifndef CGAL_PREDICATES_ON_POINTSH2_H
#include <CGAL/predicates_on_pointsH2.h>
#endif // CGAL_PREDICATES_ON_POINTSH2_H
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#ifndef CGAL_PREDICATES_ON_POINTSC2_H
#include <CGAL/predicates_on_pointsC2.h>
#endif // CGAL_PREDICATES_ON_POINTSC2_H
#endif // CGAL_CARTESIAN_H

#ifndef CGAL_POINT_2_H
#include <CGAL/Point_2.h>
#endif // CGAL_POINT_2_H

template < class R >
inline
bool CGAL_x_equal(const CGAL_Point_2<R> &p,
                  const CGAL_Point_2<R> &q)
{
  typedef typename R::Point_2   Point_2;
  return CGAL_x_equal((const Point_2&)p, (const Point_2&)q);
}

template < class R >
inline
bool CGAL_y_equal(const CGAL_Point_2<R> &p,
                  const CGAL_Point_2<R> &q)
{
  typedef typename R::Point_2   Point_2;
  return CGAL_y_equal((const Point_2&)p, (const Point_2&)q);
}


template < class R >
inline
CGAL_Comparison_result CGAL_compare_x(const CGAL_Point_2<R> &p,
                                      const CGAL_Point_2<R> &q)
{
  typedef typename R::Point_2   Point_2;
  return CGAL_compare_x((const Point_2&)p, (const Point_2&)q);
}

template < class R >
inline
CGAL_Comparison_result CGAL_compare_y(const CGAL_Point_2<R> &p,
                                      const CGAL_Point_2<R> &q)
{
  typedef typename R::Point_2   Point_2;
  return CGAL_compare_y((const Point_2&)p, (const Point_2&)q);
}

template < class R >
inline
CGAL_Comparison_result
CGAL_compare_deltax_deltay(const CGAL_Point_2<R>& p,
                           const CGAL_Point_2<R>& q,
                           const CGAL_Point_2<R>& r,
                           const CGAL_Point_2<R>& s)
{
  typedef typename R::Point_2   Point_2;
  return CGAL_compare_deltax_deltay((const Point_2&)p,
                                    (const Point_2&)q,
                                    (const Point_2&)r,
                                    (const Point_2&)s);
}

template < class R >
inline
CGAL_Comparison_result
CGAL_compare_lexicographically_xy(const CGAL_Point_2<R>& p,
                                  const CGAL_Point_2<R>& q)
{
  typedef typename R::Point_2   Point_2;
  return  CGAL_compare_lexicographically_xy((const Point_2&)p,
                                            (const Point_2&)q);
}

template < class R >
inline
bool
CGAL_lexicographically_xy_smaller_or_equal(const CGAL_Point_2<R>& p,
                                           const CGAL_Point_2<R>& q)
{
  typedef typename R::Point_2   Point_2;
  return CGAL_lexicographically_xy_smaller_or_equal((const Point_2&)p,
                                                    (const Point_2&)q);
}

template < class R >
inline
bool
CGAL_lexicographically_xy_smaller(const CGAL_Point_2<R>& p,
                                  const CGAL_Point_2<R>& q)
{
  typedef typename R::Point_2   Point_2;
 return CGAL_lexicographically_xy_smaller((const Point_2&)p,
                                          (const Point_2&)q);
}

template < class R >
inline
bool
CGAL_lexicographically_xy_larger_or_equal(const CGAL_Point_2<R>& p,
                                          const CGAL_Point_2<R>& q)
{
  typedef typename R::Point_2   Point_2;
 return !CGAL_lexicographically_xy_smaller((const Point_2&)p,
                                           (const Point_2&)q);
}

template < class R >
inline
bool
CGAL_lexicographically_xy_larger(const CGAL_Point_2<R>& p,
                                 const CGAL_Point_2<R>& q)
{
  typedef typename R::Point_2   Point_2;
  return !CGAL_lexicographically_xy_smaller_or_equal((const Point_2&)p,
                                                     (const Point_2&)q);
}


template < class R >
inline
CGAL_Comparison_result
CGAL_compare_lexicographically_yx(const CGAL_Point_2<R>& p,
                                  const CGAL_Point_2<R>& q)
{
  typedef typename R::Point_2   Point_2;
  return  CGAL_compare_lexicographically_yx((const Point_2&)p,
                                            (const Point_2&)q);
}

template < class R >
inline
bool
CGAL_lexicographically_yx_smaller_or_equal(const CGAL_Point_2<R>& p,
                                           const CGAL_Point_2<R>& q)
{
  typedef typename R::Point_2   Point_2;
  return CGAL_lexicographically_yx_smaller_or_equal((const Point_2&)p,
                                                    (const Point_2&)q);
}

template < class R >
inline
bool
CGAL_lexicographically_yx_smaller(const CGAL_Point_2<R>& p,
                                  const CGAL_Point_2<R>& q)
{
  typedef typename R::Point_2   Point_2;
 return CGAL_lexicographically_yx_smaller((const Point_2&)p,
                                          (const Point_2&)q);
}

template < class R >
inline
bool
CGAL_lexicographically_yx_larger_or_equal(const CGAL_Point_2<R>& p,
                                          const CGAL_Point_2<R>& q)
{
  typedef typename R::Point_2   Point_2;
 return !CGAL_lexicographically_yx_smaller((const Point_2&)p,
                                           (const Point_2&)q);
}

template < class R >
inline
bool
CGAL_lexicographically_yx_larger(const CGAL_Point_2<R>& p,
                                 const CGAL_Point_2<R>& q)
{
  typedef typename R::Point_2   Point_2;
  return !CGAL_lexicographically_yx_smaller_or_equal((const Point_2&)p,
                                                     (const Point_2&)q);
}

template < class R >
inline
bool
CGAL_are_ordered_along_line(const CGAL_Point_2<R> &p,
                            const CGAL_Point_2<R> &q,
                            const CGAL_Point_2<R> &r)
{
  typedef typename R::Point_2   Point_2;
  return CGAL_are_ordered_along_line((const Point_2&)p,
                                     (const Point_2&)q,
                                     (const Point_2&)r);
}

template < class R >
inline
bool
CGAL_collinear_are_ordered_along_line(const CGAL_Point_2<R> &p,
                                      const CGAL_Point_2<R> &q,
                                      const CGAL_Point_2<R> &r)
{
  typedef typename R::Point_2   Point_2;
  return CGAL_collinear_are_ordered_along_line((const Point_2&)p,
                                               (const Point_2&)q,
                                               (const Point_2&)r);
}

template < class R >
inline
bool
CGAL_are_strictly_ordered_along_line(const CGAL_Point_2<R> &p,
                            const CGAL_Point_2<R> &q,
                            const CGAL_Point_2<R> &r)
{
  typedef typename R::Point_2   Point_2;
  return CGAL_are_strictly_ordered_along_line((const Point_2&)p,
                                              (const Point_2&)q,
                                              (const Point_2&)r);
}
template < class R >
inline
bool
CGAL_collinear_are_strictly_ordered_along_line(const CGAL_Point_2<R> &p,
                                      const CGAL_Point_2<R> &q,
                                      const CGAL_Point_2<R> &r)
{
  typedef typename R::Point_2   Point_2;
  return
  CGAL_collinear_are_strictly_ordered_along_line((const Point_2&)p,
                                                 (const Point_2&)q,
                                                 (const Point_2&)r);
}
template < class R >
inline
bool
CGAL_collinear(const CGAL_Point_2<R> &p,
               const CGAL_Point_2<R> &q,
               const CGAL_Point_2<R> &r)
{
  typedef typename R::Point_2   Point_2;
  return (CGAL_collinear((const Point_2&)p,
                         (const Point_2&)q,
                         (const Point_2&)r));
}

template < class R >
inline
bool
CGAL_leftturn(const CGAL_Point_2<R> &p,
              const CGAL_Point_2<R> &q,
              const CGAL_Point_2<R> &r)
{
  typedef typename R::Point_2   Point_2;
  return CGAL_leftturn((const Point_2&)p,
                       (const Point_2&)q,
                       (const Point_2&)r);
}

template < class R >
inline
bool
CGAL_rightturn(const CGAL_Point_2<R> &p,
               const CGAL_Point_2<R> &q,
               const CGAL_Point_2<R> &r)
{
  typedef typename R::Point_2   Point_2;
  return CGAL_rightturn((const Point_2&)p,
                        (const Point_2&)q,
                        (const Point_2&)r);
}

template < class R >
inline
bool
CGAL_rightturn(const CGAL_Origin &o,
               const CGAL_Point_2<R> &q,
               const CGAL_Point_2<R> &r)
{
  typedef typename R::Point_2   Point_2;
  return CGAL_rightturn(o, (const Point_2&)q, (const Point_2&)r);
}

template < class R >
inline
CGAL_Orientation
CGAL_orientation(const CGAL_Point_2<R> &p,
                 const CGAL_Point_2<R>&q,
                 const CGAL_Point_2<R> &r)
{
  typedef typename R::Point_2   Point_2;
  return CGAL_orientation((const Point_2&)p,
                          (const Point_2&)q,
                          (const Point_2&)r);
}

template <class R >
inline
CGAL_Oriented_side
CGAL_side_of_oriented_circle(const CGAL_Point_2<R> &p,
                             const CGAL_Point_2<R> &q,
                             const CGAL_Point_2<R> &r,
                             const CGAL_Point_2<R> &test)
{
  typedef typename R::Point_2   Point_2;
  return CGAL_side_of_oriented_circle((const Point_2&)p,
                                      (const Point_2&)q,
                                      (const Point_2&)r,
                                      (const Point_2&)test);
}

template <class R >
inline
CGAL_Bounded_side
CGAL_side_of_bounded_circle(const CGAL_Point_2<R> &p,
                            const CGAL_Point_2<R> &q,
                            const CGAL_Point_2<R> &r,
                            const CGAL_Point_2<R> &test)
{
  typedef typename R::Point_2   Point_2;
  return CGAL_side_of_bounded_circle((const Point_2&)p,
                                     (const Point_2&)q,
                                     (const Point_2&)r,
                                     (const Point_2&)test);
}


#endif  // CGAL_PREDICATES_ON_POINTS_2_H