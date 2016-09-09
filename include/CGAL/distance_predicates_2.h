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

// Source: distance_predicates_2.h
// Author: Stefan Schirra

#ifndef CGAL_DISTANCE_PREDICATES_2_H
#define CGAL_DISTANCE_PREDICATES_2_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/distance_predicatesH2.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/distance_predicatesC2.h>
#endif // CGAL_CARTESIAN_H

#include <CGAL/Point_2.h>
#include <CGAL/Line_2.h>



template < class R >
CGAL_Comparison_result
CGAL_cmp_dist_to_point(const CGAL_Point_2<R>& p,
                       const CGAL_Point_2<R>& q,
                       const CGAL_Point_2<R>& r)
{
 return CGAL_cmp_dist_to_point( (const R::Point_2 &)p,
                                (const R::Point_2 &)q,
                                (const R::Point_2 &)r );
}

template < class R >
bool
CGAL_has_larger_dist_to_point(const CGAL_Point_2<R>& p,
                              const CGAL_Point_2<R>& q,
                              const CGAL_Point_2<R>& r)
{
 return CGAL_has_larger_dist_to_point((const R::Point_2 &)p,
                                      (const R::Point_2 &)q,
                                      (const R::Point_2 &)r );
}

template < class R >
bool
CGAL_has_smaller_dist_to_point(const CGAL_Point_2<R>& p,
                               const CGAL_Point_2<R>& q,
                               const CGAL_Point_2<R>& r)
{
 return CGAL_has_smaller_dist_to_point((const R::Point_2 &)p,
                                       (const R::Point_2 &)q,
                                       (const R::Point_2 &)r );
}

template < class R >
CGAL_Comparison_result
CGAL_cmp_signed_dist_to_line(const CGAL_Line_2<R>&  l,
                             const CGAL_Point_2<R>& p,
                             const CGAL_Point_2<R>& q)
{
 return CGAL_cmp_signed_dist_to_line((const R::Line_2 &)l,
                                     (const R::Point_2 &)p,
                                     (const R::Point_2 &)q );
}

template < class R >
bool
CGAL_has_larger_signed_dist_to_line(const CGAL_Line_2<R>&  l,
                                    const CGAL_Point_2<R>& p,
                                    const CGAL_Point_2<R>& q)
{
 return CGAL_has_larger_signed_dist_to_line((const R::Line_2 &)l,
                                            (const R::Point_2 &)p,
                                            (const R::Point_2 &)q );
}

template < class R >
bool
CGAL_has_smaller_signed_dist_to_line(const CGAL_Line_2<R>&  l,
                                     const CGAL_Point_2<R>& p,
                                     const CGAL_Point_2<R>& q)
{
 return CGAL_has_smaller_signed_dist_to_line((const R::Line_2 &)l,
                                             (const R::Point_2 &)p,
                                             (const R::Point_2 &)q );
}

template < class R >
CGAL_Comparison_result
CGAL_cmp_signed_dist_to_line(const CGAL_Point_2<R>& p,
                             const CGAL_Point_2<R>& q,
                             const CGAL_Point_2<R>& r,
                             const CGAL_Point_2<R>& s)
{ 
 return CGAL_cmp_signed_dist_to_line((const R::Point_2 &)p,
                                     (const R::Point_2 &)q,
                                     (const R::Point_2 &)r,
                                     (const R::Point_2 &)s );
}

template < class R >
bool
CGAL_has_smaller_signed_dist_to_line(const CGAL_Point_2<R>& p,
                                     const CGAL_Point_2<R>& q,
                                     const CGAL_Point_2<R>& r,
                                     const CGAL_Point_2<R>& s)
{ 
 return CGAL_has_smaller_signed_dist_to_line((const R::Point_2 &)p,
                                             (const R::Point_2 &)q,
                                             (const R::Point_2 &)r,
                                             (const R::Point_2 &)s );
}

template < class R >
bool
CGAL_has_larger_signed_dist_to_line(const CGAL_Point_2<R>& p,
                                    const CGAL_Point_2<R>& q,
                                    const CGAL_Point_2<R>& r,
                                    const CGAL_Point_2<R>& s)
{ 
 return CGAL_has_larger_signed_dist_to_line((const R::Point_2 &)p,
                                            (const R::Point_2 &)q,
                                            (const R::Point_2 &)r,
                                            (const R::Point_2 &)s );
}


#endif //CGAL_DISTANCE_PREDICATES_2_H
