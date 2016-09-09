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


// Source: predicates_on_points_3.h
// Author: Andreas Fabri

#ifndef CGAL_PREDICATES_ON_POINTS_3_H
#define CGAL_PREDICATES_ON_POINTS_3_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/predicates_on_pointsH3.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/predicates_on_pointsC3.h>
#endif // CGAL_CARTESIAN_H

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
inline
CGAL_Comparison_result 
CGAL_compare_x(const CGAL_Point_3<R> &p, const CGAL_Point_3<R> &q)
{
  return CGAL_compare_x((const R::Point_3&)p, (const R::Point_3&)q);
}


template < class R >
inline
CGAL_Comparison_result 
CGAL_compare_y(const CGAL_Point_3<R> &p, const CGAL_Point_3<R> &q)
{
  return CGAL_compare_y((const R::Point_3&)p, (const R::Point_3&)q);
}


template < class R >
inline
CGAL_Comparison_result 
CGAL_compare_z(const CGAL_Point_3<R> &p, const CGAL_Point_3<R> &q)
{
  return CGAL_compare_z((const R::Point_3&)p, (const R::Point_3&)q);
}



template < class R >
inline
bool CGAL_x_equal(const CGAL_Point_3<R> &p,
                  const CGAL_Point_3<R> &q)
{
  return CGAL_x_equal((const R::Point_3&)p, (const R::Point_3&)q);
}

template < class R >
inline
bool CGAL_y_equal(const CGAL_Point_3<R> &p,
                  const CGAL_Point_3<R> &q)
{
  return CGAL_y_equal((const R::Point_3&)p, (const R::Point_3&)q);
}

template < class R >
inline
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
inline bool CGAL_are_ordered_along_line(const CGAL_Point_3<R> &p,
                         const CGAL_Point_3<R> &q,
                         const CGAL_Point_3<R> &r)
{
 return (CGAL_are_ordered_along_line((const R::Point_3&)p,
                      (const R::Point_3&)q,
                      (const R::Point_3&)r));
}

template < class R >
inline bool CGAL_collinear_are_ordered_along_line(const CGAL_Point_3<R> &p,
                                   const CGAL_Point_3<R> &q,
                                   const CGAL_Point_3<R> &r)
{
 return (CGAL_collinear_are_ordered_along_line((const R::Point_3&)p,
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


#endif // CGAL_PREDICATES_ON_POINTS_3_H
