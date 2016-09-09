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
// source        : predicates_on_points_2.fw
// file          : include/CGAL/predicates_on_points_2.h
// package       : _2 (2.1.2)
// revision      : 2.1.2
// revision_date : 09 May 1999 
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : cgal@cs.uu.nl
//
// ======================================================================
 

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

CGAL_BEGIN_NAMESPACE

template < class R >
inline
bool x_equal(const Point_2<R> &p,
             const Point_2<R> &q)
{
  typedef typename R::Point_2   RPoint_2;
  return x_equal((const RPoint_2&)p, (const RPoint_2&)q);
}

template < class R >
inline
bool y_equal(const Point_2<R> &p,
             const Point_2<R> &q)
{
  typedef typename R::Point_2   RPoint_2;
  return y_equal((const RPoint_2&)p, (const RPoint_2&)q);
}


template < class R >
inline
Comparison_result compare_x(const Point_2<R> &p,
                            const Point_2<R> &q)
{
  typedef typename R::Point_2   RPoint_2;
  return compare_x((const RPoint_2&)p, (const RPoint_2&)q);
}

template < class R >
inline
Comparison_result compare_y(const Point_2<R> &p,
                            const Point_2<R> &q)
{
  typedef typename R::Point_2   RPoint_2;
  return compare_y((const RPoint_2&)p, (const RPoint_2&)q);
}

template < class R >
inline
Comparison_result
compare_deltax_deltay(const Point_2<R>& p,
                      const Point_2<R>& q,
                      const Point_2<R>& r,
                      const Point_2<R>& s)
{
  typedef typename R::Point_2   RPoint_2;
  return compare_deltax_deltay((const RPoint_2&)p,
                               (const RPoint_2&)q,
                               (const RPoint_2&)r,
                               (const RPoint_2&)s);
}

template < class R >
inline
Comparison_result
compare_lexicographically_xy(const Point_2<R>& p,
                             const Point_2<R>& q)
{
  typedef typename R::Point_2   RPoint_2;
  return  compare_lexicographically_xy((const RPoint_2&)p,
                                       (const RPoint_2&)q);
}

template < class R >
inline
bool
lexicographically_xy_smaller_or_equal(const Point_2<R>& p,
                                      const Point_2<R>& q)
{
  typedef typename R::Point_2   RPoint_2;
  return lexicographically_xy_smaller_or_equal((const RPoint_2&)p,
                                               (const RPoint_2&)q);
}

template < class R >
inline
bool
lexicographically_xy_smaller(const Point_2<R>& p,
                                  const Point_2<R>& q)
{
  typedef typename R::Point_2   RPoint_2;
 return lexicographically_xy_smaller((const RPoint_2&)p,
                                     (const RPoint_2&)q);
}

template < class R >
inline
bool
lexicographically_xy_larger_or_equal(const Point_2<R>& p,
                                     const Point_2<R>& q)
{
  typedef typename R::Point_2   RPoint_2;
 return !lexicographically_xy_smaller((const RPoint_2&)p,
                                      (const RPoint_2&)q);
}

template < class R >
inline
bool
lexicographically_xy_larger(const Point_2<R>& p,
                            const Point_2<R>& q)
{
  typedef typename R::Point_2   RPoint_2;
  return !lexicographically_xy_smaller_or_equal((const RPoint_2&)p,
                                                (const RPoint_2&)q);
}


template < class R >
inline
Comparison_result
compare_lexicographically_yx(const Point_2<R>& p,
                                  const Point_2<R>& q)
{
  typedef typename R::Point_2   RPoint_2;
  return  compare_lexicographically_yx((const RPoint_2&)p,
                                       (const RPoint_2&)q);
}

template < class R >
inline
bool
lexicographically_yx_smaller_or_equal(const Point_2<R>& p,
                                      const Point_2<R>& q)
{
  typedef typename R::Point_2   RPoint_2;
  return lexicographically_yx_smaller_or_equal((const RPoint_2&)p,
                                               (const RPoint_2&)q);
}

template < class R >
inline
bool
lexicographically_yx_smaller(const Point_2<R>& p,
                             const Point_2<R>& q)
{
  typedef typename R::Point_2   RPoint_2;
 return lexicographically_yx_smaller((const RPoint_2&)p,
                                     (const RPoint_2&)q);
}

template < class R >
inline
bool
lexicographically_yx_larger_or_equal(const Point_2<R>& p,
                                     const Point_2<R>& q)
{
  typedef typename R::Point_2   RPoint_2;
 return !lexicographically_yx_smaller((const RPoint_2&)p,
                                      (const RPoint_2&)q);
}

template < class R >
inline
bool
lexicographically_yx_larger(const Point_2<R>& p,
                            const Point_2<R>& q)
{
  typedef typename R::Point_2   RPoint_2;
  return !lexicographically_yx_smaller_or_equal((const RPoint_2&)p,
                                                (const RPoint_2&)q);
}

template < class R >
inline
bool
are_ordered_along_line(const Point_2<R> &p,
                       const Point_2<R> &q,
                       const Point_2<R> &r)
{
  typedef typename R::Point_2   RPoint_2;
  return are_ordered_along_line((const RPoint_2&)p,
                                (const RPoint_2&)q,
                                (const RPoint_2&)r);
}

template < class R >
inline
bool
collinear_are_ordered_along_line(const Point_2<R> &p,
                                 const Point_2<R> &q,
                                 const Point_2<R> &r)
{
  typedef typename R::Point_2   RPoint_2;
  return collinear_are_ordered_along_line((const RPoint_2&)p,
                                          (const RPoint_2&)q,
                                          (const RPoint_2&)r);
}

template < class R >
inline
bool
are_strictly_ordered_along_line(const Point_2<R> &p,
                            const Point_2<R> &q,
                            const Point_2<R> &r)
{
  typedef typename R::Point_2   RPoint_2;
  return are_strictly_ordered_along_line((const RPoint_2&)p,
                                         (const RPoint_2&)q,
                                         (const RPoint_2&)r);
}
template < class R >
inline
bool
collinear_are_strictly_ordered_along_line(const Point_2<R> &p,
                                          const Point_2<R> &q,
                                          const Point_2<R> &r)
{
  typedef typename R::Point_2   RPoint_2;
  return
  collinear_are_strictly_ordered_along_line((const RPoint_2&)p,
                                            (const RPoint_2&)q,
                                            (const RPoint_2&)r);
}
template < class R >
inline
bool
collinear(const Point_2<R> &p,
          const Point_2<R> &q,
          const Point_2<R> &r)
{
  typedef typename R::Point_2   RPoint_2;
  return (collinear((const RPoint_2&)p,
                    (const RPoint_2&)q,
                    (const RPoint_2&)r));
}

template < class R >
inline
bool
leftturn(const Point_2<R> &p,
         const Point_2<R> &q,
         const Point_2<R> &r)
{
  typedef typename R::Point_2   RPoint_2;
  return leftturn((const RPoint_2&)p,
                  (const RPoint_2&)q,
                  (const RPoint_2&)r);
}

template < class R >
inline
bool
rightturn(const Point_2<R> &p,
          const Point_2<R> &q,
          const Point_2<R> &r)
{
  typedef typename R::Point_2   RPoint_2;
  return rightturn((const RPoint_2&)p,
                   (const RPoint_2&)q,
                   (const RPoint_2&)r);
}

template < class R >
inline
bool
rightturn(const Origin &o,
          const Point_2<R> &q,
          const Point_2<R> &r)
{
  typedef typename R::Point_2   RPoint_2;
  return rightturn(o, (const RPoint_2&)q, (const RPoint_2&)r);
}

template < class R >
inline
Orientation
orientation(const Point_2<R> &p,
            const Point_2<R>&q,
            const Point_2<R> &r)
{
  typedef typename R::Point_2   RPoint_2;
  return CGAL::orientation((const RPoint_2&)p,
                           (const RPoint_2&)q,
                           (const RPoint_2&)r);
}

template <class R >
inline
Oriented_side
side_of_oriented_circle(const Point_2<R> &p,
                        const Point_2<R> &q,
                        const Point_2<R> &r,
                        const Point_2<R> &test)
{
  typedef typename R::Point_2   RPoint_2;
  return side_of_oriented_circle((const RPoint_2&)p,
                                 (const RPoint_2&)q,
                                 (const RPoint_2&)r,
                                 (const RPoint_2&)test);
}

template <class R >
inline
Bounded_side
side_of_bounded_circle(const Point_2<R> &p,
                       const Point_2<R> &q,
                       const Point_2<R> &r,
                       const Point_2<R> &test)
{
  typedef typename R::Point_2   RPoint_2;
  return side_of_bounded_circle((const RPoint_2&)p,
                                (const RPoint_2&)q,
                                (const RPoint_2&)r,
                                (const RPoint_2&)test);
}

CGAL_END_NAMESPACE


#endif  // CGAL_PREDICATES_ON_POINTS_2_H
