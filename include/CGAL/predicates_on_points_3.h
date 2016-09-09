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

// Source: predicates_on_points_3.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_PREDICATES_ON_POINTS_3_H
#define CGAL_PREDICATES_ON_POINTS_3_H

#include <CGAL/Point_3.h>

template < class R >
CGAL_Comparison_result CGAL_compare_lexicographically_xyz(
                                                     const CGAL_Point_3<R> &p,
                                                     const CGAL_Point_3<R> &q)
{
 return CGAL_compare_lexicographically_xyz((const R::Point_3&)p,
                                           (const R::Point_3&)q);
}


template < class R >
bool CGAL_lexicographically_xyz_smaller_or_equal(const CGAL_Point_3<R> &p,
                                                 const CGAL_Point_3<R> &q)
{
  return ( !( CGAL_compare_lexicographically_xyz((const R::Point_3&)p,
                                                 (const R::Point_3&)q)
              == CGAL_LARGER ) );
}

template < class R >
bool CGAL_lexicographically_xyz_smaller(const CGAL_Point_3<R> &p,
                                        const CGAL_Point_3<R> &q)
{
  return ( CGAL_compare_lexicographically_xyz((const R::Point_3&)p,
                                              (const R::Point_3&)q)
           == CGAL_SMALLER );
}


template < class R >
bool CGAL_x_equal(const CGAL_Point_3<R> &p,
                  const CGAL_Point_3<R> &q)
{
  return CGAL_x_equal((const R::Point_3&)p, (const R::Point_3&)q);
}

template < class R >
bool CGAL_y_equal(const CGAL_Point_3<R> &p,
                  const CGAL_Point_3<R> &q)
{
  return CGAL_y_equal((const R::Point_3&)p, (const R::Point_3&)q);
}

template < class R >
bool CGAL_z_equal(const CGAL_Point_3<R> &p,
                  const CGAL_Point_3<R> &q)
{
  return CGAL_z_equal((const R::Point_3&)p, (const R::Point_3&)q);
}


template < class R >
inline bool CGAL_coplanar(const CGAL_Point_3<R> &p,
                          const CGAL_Point_3<R> &q,
                          const CGAL_Point_3<R> &r,
                          const CGAL_Point_3<R> &s)
{
  return ( CGAL_coplanar((const R::Point_3&)p, (const R::Point_3&)q,
                         (const R::Point_3&)r, (const R::Point_3&)s) );
}

template < class R >
bool CGAL_collinear(const CGAL_Point_3<R> &p,
                    const CGAL_Point_3<R> &q,
                    const CGAL_Point_3<R> &r)
{
 return (CGAL_collinear((const R::Point_3&)p,
                        (const R::Point_3&)q,
                        (const R::Point_3&)r));
}

template < class R >
inline bool CGAL_between(const CGAL_Point_3<R> &p,
                         const CGAL_Point_3<R> &q,
                         const CGAL_Point_3<R> &r)
{
 return (CGAL_between((const R::Point_3&)p,
                      (const R::Point_3&)q,
                      (const R::Point_3&)r));
}

template < class R >
inline bool CGAL_collinear_between(const CGAL_Point_3<R> &p,
                                   const CGAL_Point_3<R> &q,
                                   const CGAL_Point_3<R> &r)
{
 return (CGAL_collinear_between((const R::Point_3&)p,
                                (const R::Point_3&)q,
                                (const R::Point_3&)r));
}


template < class R >
inline CGAL_Orientation CGAL_orientation(const CGAL_Point_3<R> &p,
                                         const CGAL_Point_3<R> &q,
                                         const CGAL_Point_3<R> &r,
                                         const CGAL_Point_3<R> &s)
{
  return CGAL_orientation((const R::Point_3&)p, (const R::Point_3&)q,
                          (const R::Point_3&)r, (const R::Point_3&)s);
}

template <class R >
CGAL_Bounded_side CGAL_side_of_bounded_sphere(
                         const CGAL_Point_3<R> &p, const CGAL_Point_3<R> &q,
                         const CGAL_Point_3<R> &r, const CGAL_Point_3<R> &s,
                         const CGAL_Point_3<R> &test)
{
  return CGAL_side_of_bounded_sphere((const R::Point_3&)p,
                                     (const R::Point_3&)q,
                                     (const R::Point_3&)r,
                                     (const R::Point_3&)s,
                                     (const R::Point_3&)test);
}


#endif // CGAL_PREDICATES_ON_POINTS_3_H
