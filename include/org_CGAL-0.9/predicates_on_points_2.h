/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/


// Source: predicates_on_points_2.h
// Author: Andreas Fabri

#ifndef CGAL_PREDICATES_ON_POINTS_2_H
#define CGAL_PREDICATES_ON_POINTS_2_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/predicates_on_pointsH2.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/predicates_on_pointsC2.h>
#endif // CGAL_CARTESIAN_H

#include <CGAL/Point_2.h>
template < class R >
bool CGAL_x_equal(const CGAL_Point_2<R> &p,
                  const CGAL_Point_2<R> &q)
{
  return CGAL_x_equal((const R::Point_2&)p, (const R::Point_2&)q);
}

template < class R >
bool CGAL_y_equal(const CGAL_Point_2<R> &p,
                  const CGAL_Point_2<R> &q)
{
  return CGAL_y_equal((const R::Point_2&)p, (const R::Point_2&)q);
}


template < class R >
CGAL_Comparison_result CGAL_compare_x(const CGAL_Point_2<R> &p,
                                      const CGAL_Point_2<R> &q)
{
  return CGAL_compare_x((const R::Point_2&)p, (const R::Point_2&)q);
}

template < class R >
CGAL_Comparison_result CGAL_compare_y(const CGAL_Point_2<R> &p,
                                      const CGAL_Point_2<R> &q)
{
  return CGAL_compare_y((const R::Point_2&)p, (const R::Point_2&)q);
}


template < class R >
CGAL_Comparison_result
CGAL_compare_lexicographically_xy(const CGAL_Point_2<R>& p,
                                  const CGAL_Point_2<R>& q)
{
  return  CGAL_compare_lexicographically_xy((const R::Point_2&)p,
                                            (const R::Point_2&)q);
}

template < class R >
bool
CGAL_lexicographically_xy_smaller_or_equal(const CGAL_Point_2<R>& p,
                                           const CGAL_Point_2<R>& q)
{
  return CGAL_lexicographically_xy_smaller_or_equal((const R::Point_2&)p,
                                                    (const R::Point_2&)q);
}

template < class R >
bool
CGAL_lexicographically_xy_smaller(const CGAL_Point_2<R>& p,
                                  const CGAL_Point_2<R>& q)
{
 return CGAL_lexicographically_xy_smaller((const R::Point_2&)p,
                                          (const R::Point_2&)q);
}

template < class R >
bool
CGAL_lexicographically_xy_larger_or_equal(const CGAL_Point_2<R>& p,
                                          const CGAL_Point_2<R>& q)
{
 return !CGAL_lexicographically_xy_smaller((const R::Point_2&)p,
                                           (const R::Point_2&)q);
}

template < class R >
bool
CGAL_lexicographically_xy_larger(const CGAL_Point_2<R>& p,
                                 const CGAL_Point_2<R>& q)
{
  return !CGAL_lexicographically_xy_smaller_or_equal((const R::Point_2&)p,
                                                     (const R::Point_2&)q);
}


template < class R >
CGAL_Comparison_result
CGAL_compare_lexicographically_yx(const CGAL_Point_2<R>& p,
                                  const CGAL_Point_2<R>& q)
{
  return  CGAL_compare_lexicographically_yx((const R::Point_2&)p,
                                            (const R::Point_2&)q);
}

template < class R >
bool
CGAL_lexicographically_yx_smaller_or_equal(const CGAL_Point_2<R>& p,
                                           const CGAL_Point_2<R>& q)
{
  return CGAL_lexicographically_yx_smaller_or_equal((const R::Point_2&)p,
                                                    (const R::Point_2&)q);
}

template < class R >
bool
CGAL_lexicographically_yx_smaller(const CGAL_Point_2<R>& p,
                                  const CGAL_Point_2<R>& q)
{
 return CGAL_lexicographically_yx_smaller((const R::Point_2&)p,
                                          (const R::Point_2&)q);
}

template < class R >
bool
CGAL_lexicographically_yx_larger_or_equal(const CGAL_Point_2<R>& p,
                                          const CGAL_Point_2<R>& q)
{
 return !CGAL_lexicographically_yx_smaller((const R::Point_2&)p,
                                           (const R::Point_2&)q);
}

template < class R >
bool
CGAL_lexicographically_yx_larger(const CGAL_Point_2<R>& p,
                                 const CGAL_Point_2<R>& q)
{
  return !CGAL_lexicographically_yx_smaller_or_equal((const R::Point_2&)p,
                                                     (const R::Point_2&)q);
}


template < class R >
bool CGAL_collinear(const CGAL_Point_2<R> &p,
                    const CGAL_Point_2<R> &q,
                    const CGAL_Point_2<R> &r)
{
  return (CGAL_collinear((const R::Point_2&)p,
                         (const R::Point_2&)q,
                         (const R::Point_2&)r));
}

template < class R >
bool CGAL_are_ordered_along_line(const CGAL_Point_2<R> &p,
                  const CGAL_Point_2<R> &q,
                  const CGAL_Point_2<R> &r)
{
  if (!CGAL_collinear(p, q, r))
    {
      return false;
    }
  return CGAL_collinear_are_ordered_along_line(p, q, r);

}

template < class R >
inline bool CGAL_collinear_are_ordered_along_line(const CGAL_Point_2<R> &p,
                                   const CGAL_Point_2<R> &q,
                                   const CGAL_Point_2<R> &r)
{
  return (CGAL_collinear_are_ordered_along_line((const R::Point_2&)p,
                                 (const R::Point_2&)q,
                                 (const R::Point_2&)r));
}

template < class R >
inline bool CGAL_leftturn(const CGAL_Point_2<R> &p,
                          const CGAL_Point_2<R> &q,
                          const CGAL_Point_2<R> &r)
{
  return CGAL_leftturn((const R::Point_2&)p,
                       (const R::Point_2&)q,
                       (const R::Point_2&)r);
}

template < class R >
inline bool CGAL_rightturn(const CGAL_Point_2<R> &p,
                           const CGAL_Point_2<R> &q,
                           const CGAL_Point_2<R> &r)
{
   return CGAL_rightturn((const R::Point_2&)p,
                         (const R::Point_2&)q,
                         (const R::Point_2&)r);
}

template < class R >
inline bool CGAL_rightturn(const CGAL_Origin &o,
                           const CGAL_Point_2<R> &q,
                           const CGAL_Point_2<R> &r)
{
   return CGAL_rightturn(o,
                         (const R::Point_2&)q,
                         (const R::Point_2&)r);
}

template < class R >
inline CGAL_Orientation CGAL_orientation(const CGAL_Point_2<R> &p,
                                         const CGAL_Point_2<R>&q,
                                         const CGAL_Point_2<R> &r)
{
  return CGAL_orientation((const R::Point_2&)p,
                          (const R::Point_2&)q,
                          (const R::Point_2&)r);
}
/*
template < class RT, class R >
inline RT CGAL_area2(const CGAL_Point_2<R> &p,
                     const CGAL_Point_2<R> &q,
                     const CGAL_Point_2<R> &r)
{
  return CGAL_area2((const R::Point_2&)p,
                    (const R::Point_2&)q,
                    (const R::Point_2&)r);
}
*/
template <class R >
CGAL_Oriented_side CGAL_side_of_oriented_circle(const CGAL_Point_2<R> &p,
                                                const CGAL_Point_2<R> &q,
                                                const CGAL_Point_2<R> &r,
                                                const CGAL_Point_2<R> &test)
{
  return CGAL_side_of_oriented_circle((const R::Point_2&)p,
                                      (const R::Point_2&)q,
                                      (const R::Point_2&)r,
                                      (const R::Point_2&)test);
}

template <class R >
CGAL_Bounded_side CGAL_side_of_bounded_circle(const CGAL_Point_2<R> &p,
                                               const CGAL_Point_2<R> &q,
                                               const CGAL_Point_2<R> &r,
                                               const CGAL_Point_2<R> &test)
{
  return CGAL_side_of_bounded_circle((const R::Point_2&)p,
                                     (const R::Point_2&)q,
                                     (const R::Point_2&)r,
                                     (const R::Point_2&)test);
}


#endif  // CGAL_PREDICATES_ON_POINTS_2_H
