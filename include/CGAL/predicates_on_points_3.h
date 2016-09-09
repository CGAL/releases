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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-1.1
// release_date  : 1998, July 24
// 
// source        : predicates_on_points_3.fw
// file          : include/CGAL/predicates_on_points_3.h
// package       : _3 (1.3)
// revision      : 1.3
// revision_date : 15 May 1998 
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : cgal@cs.uu.nl
//
// ======================================================================
 

#ifndef CGAL_PREDICATES_ON_POINTS_3_H
#define CGAL_PREDICATES_ON_POINTS_3_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#ifndef CGAL_PREDICATES_ON_POINTSH3_H
#include <CGAL/predicates_on_pointsH3.h>
#endif // CGAL_PREDICATES_ON_POINTSH3_H
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#ifndef CGAL_PREDICATES_ON_POINTSC3_H
#include <CGAL/predicates_on_pointsC3.h>
#endif // CGAL_PREDICATES_ON_POINTSC3_H
#endif // CGAL_CARTESIAN_H

#ifndef CGAL_POINT_3_H
#include <CGAL/Point_3.h>
#endif // CGAL_POINT_3_H

template < class R >
inline
CGAL_Comparison_result
CGAL_compare_lexicographically_xyz( const CGAL_Point_3<R> &p,
                                    const CGAL_Point_3<R> &q)
{
  typedef typename  R::Point_3    Point_3;
  return CGAL_compare_lexicographically_xyz((const Point_3&)p,
                                            (const Point_3&)q);
}

template < class R >
inline
bool
CGAL_lexicographically_xyz_smaller_or_equal(const CGAL_Point_3<R> &p,
                                            const CGAL_Point_3<R> &q)
{
  typedef typename  R::Point_3    Point_3;
  return ( !( CGAL_compare_lexicographically_xyz((const Point_3&)p,
                                                 (const Point_3&)q)
              == CGAL_LARGER ) );
}

template < class R >
inline
bool
CGAL_lexicographically_xyz_smaller(const CGAL_Point_3<R> &p,
                                   const CGAL_Point_3<R> &q)
{
  typedef typename  R::Point_3    Point_3;
  return ( CGAL_compare_lexicographically_xyz((const Point_3&)p,
                                              (const Point_3&)q)
           == CGAL_SMALLER );
}

template < class R >
inline
CGAL_Comparison_result
CGAL_compare_x(const CGAL_Point_3<R> &p, const CGAL_Point_3<R> &q)
{
  typedef typename  R::Point_3    Point_3;
  return CGAL_compare_x((const Point_3&)p, (const Point_3&)q);
}


template < class R >
inline
CGAL_Comparison_result
CGAL_compare_y(const CGAL_Point_3<R> &p, const CGAL_Point_3<R> &q)
{
  typedef typename  R::Point_3    Point_3;
  return CGAL_compare_y((const Point_3&)p, (const Point_3&)q);
}


template < class R >
inline
CGAL_Comparison_result
CGAL_compare_z(const CGAL_Point_3<R> &p, const CGAL_Point_3<R> &q)
{
  typedef typename  R::Point_3    Point_3;
  return CGAL_compare_z((const Point_3&)p, (const Point_3&)q);
}

template < class R >
inline
bool
CGAL_x_equal(const CGAL_Point_3<R> &p,
             const CGAL_Point_3<R> &q)
{
  typedef typename  R::Point_3    Point_3;
  return CGAL_x_equal((const Point_3&)p, (const Point_3&)q);
}

template < class R >
inline
bool
CGAL_y_equal(const CGAL_Point_3<R> &p,
             const CGAL_Point_3<R> &q)
{
  typedef typename  R::Point_3    Point_3;
  return CGAL_y_equal((const Point_3&)p, (const Point_3&)q);
}

template < class R >
inline
bool
CGAL_z_equal(const CGAL_Point_3<R> &p,
             const CGAL_Point_3<R> &q)
{
  typedef typename  R::Point_3    Point_3;
  return CGAL_z_equal((const Point_3&)p, (const Point_3&)q);
}

template < class R >
inline
bool
CGAL_coplanar(const CGAL_Point_3<R> &p,
              const CGAL_Point_3<R> &q,
              const CGAL_Point_3<R> &r,
              const CGAL_Point_3<R> &s)
{
  typedef typename  R::Point_3    Point_3;
  return ( CGAL_coplanar((const Point_3&)p, (const Point_3&)q,
                         (const Point_3&)r, (const Point_3&)s) );
}

template < class R >
inline
bool
CGAL_collinear(const CGAL_Point_3<R> &p,
               const CGAL_Point_3<R> &q,
               const CGAL_Point_3<R> &r)
{
  typedef typename  R::Point_3    Point_3;
  return (CGAL_collinear((const Point_3&)p,
                         (const Point_3&)q,
                         (const Point_3&)r));
}

template < class R >
inline
bool
CGAL_are_ordered_along_line(const CGAL_Point_3<R> &p,
                            const CGAL_Point_3<R> &q,
                            const CGAL_Point_3<R> &r)
{
  typedef typename  R::Point_3    Point_3;
  return (CGAL_are_ordered_along_line((const Point_3&)p,
                                      (const Point_3&)q,
                                      (const Point_3&)r));
}

template < class R >
inline
bool
CGAL_collinear_are_ordered_along_line(const CGAL_Point_3<R> &p,
                                      const CGAL_Point_3<R> &q,
                                      const CGAL_Point_3<R> &r)
{
  typedef typename  R::Point_3    Point_3;
  return CGAL_collinear_are_ordered_along_line((const Point_3&)p,
                                               (const Point_3&)q,
                                               (const Point_3&)r
                                              );
}

template < class R >
inline
bool
CGAL_are_strictly_ordered_along_line(const CGAL_Point_3<R> &p,
                                     const CGAL_Point_3<R> &q,
                                     const CGAL_Point_3<R> &r)
{
  typedef typename  R::Point_3    Point_3;
  return (CGAL_are_strictly_ordered_along_line((const Point_3&)p,
                                               (const Point_3&)q,
                                               (const Point_3&)r));
}

template < class R >
inline
bool
CGAL_collinear_are_strictly_ordered_along_line(const CGAL_Point_3<R> &p,
                                               const CGAL_Point_3<R> &q,
                                               const CGAL_Point_3<R> &r)
{
  typedef typename  R::Point_3    Point_3;
  return CGAL_collinear_are_strictly_ordered_along_line((const Point_3&)p,
                                                        (const Point_3&)q,
                                                        (const Point_3&)r
                                              );
}

template < class R >
inline
CGAL_Orientation
CGAL_orientation(const CGAL_Point_3<R> &p,
                 const CGAL_Point_3<R> &q,
                 const CGAL_Point_3<R> &r,
                 const CGAL_Point_3<R> &s)
{
  typedef typename  R::Point_3    Point_3;
  return CGAL_orientation((const Point_3&)p, (const Point_3&)q,
                          (const Point_3&)r, (const Point_3&)s);
}

template <class R >
inline
CGAL_Bounded_side
CGAL_side_of_bounded_sphere( const CGAL_Point_3<R> &p,
                             const CGAL_Point_3<R> &q,
                             const CGAL_Point_3<R> &r,
                             const CGAL_Point_3<R> &s,
                             const CGAL_Point_3<R> &test)
{
  typedef typename  R::Point_3    Point_3;
  return CGAL_side_of_bounded_sphere((const Point_3&)p,
                                     (const Point_3&)q,
                                     (const Point_3&)r,
                                     (const Point_3&)s,
                                     (const Point_3&)test);
}

template <class R >
inline
CGAL_Oriented_side
CGAL_side_of_oriented_sphere( const CGAL_Point_3<R> &p,
                              const CGAL_Point_3<R> &q,
                              const CGAL_Point_3<R> &r,
                              const CGAL_Point_3<R> &s,
                              const CGAL_Point_3<R> &test)
{
  typedef typename  R::Point_3    Point_3;
  return CGAL_side_of_oriented_sphere((const Point_3&)p,
                                      (const Point_3&)q,
                                      (const Point_3&)r,
                                      (const Point_3&)s,
                                      (const Point_3&)test);
}


#endif // CGAL_PREDICATES_ON_POINTS_3_H
