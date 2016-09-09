//  Copyright CGAL 1996
//
//  cgal@cs.ruu.nl
//
//  This file is part of an internal release of the CGAL kernel.
//  The code herein may be used and/or copied only in accordance
//  with the terms and conditions stipulated in the agreement
//  under which the code has been supplied or with the written
//  permission of the CGAL Project.
//
//  Look at http://www.cs.ruu.nl/CGAL/ for more information.
//  Please send any bug reports and comments to cgal@cs.ruu.nl
//
//  The code comes WITHOUT ANY WARRANTY; without even the implied
//  warranty of FITNESS FOR A PARTICULAR PURPOSE.
//

// Source: predicates_on_points_2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_PREDICATES_ON_POINTS_2_H
#define CGAL_PREDICATES_ON_POINTS_2_H

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
bool CGAL_collinear(const CGAL_Point_2<R> &p,
                    const CGAL_Point_2<R> &q,
                    const CGAL_Point_2<R> &r)
{
  return (CGAL_collinear((const R::Point_2&)p,
                         (const R::Point_2&)q,
                         (const R::Point_2&)r));
}

template < class R >
bool CGAL_between(const CGAL_Point_2<R> &p,
                  const CGAL_Point_2<R> &q,
                  const CGAL_Point_2<R> &r)
{
  if (!CGAL_collinear(p, q, r))
    {
      return false;
    }
  return CGAL_collinear_between(p, q, r);

}

template < class R >
inline bool CGAL_collinear_between(const CGAL_Point_2<R> &p,
                                   const CGAL_Point_2<R> &q,
                                   const CGAL_Point_2<R> &r)
{
  return (CGAL_collinear_between((const R::Point_2&)p,
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
