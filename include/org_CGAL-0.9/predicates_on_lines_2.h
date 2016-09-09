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


// Source: predicates_on_lines_2.h
// Author: Andreas Fabri

#ifndef CGAL_PREDICATES_ON_LINES_2_H
#define CGAL_PREDICATES_ON_LINES_2_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/predicates_on_linesH2.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/predicates_on_linesC2.h>
#endif // CGAL_CARTESIAN_H

#include <CGAL/Point_2.h>
#include <CGAL/predicates_on_points_2.h>
#include <CGAL/Line_2.h>


template < class R >
inline CGAL_Comparison_result CGAL_compare_x(const CGAL_Point_2<R> &p,
                                             const CGAL_Line_2<R> &l1,
                                             const CGAL_Line_2<R> &l2)
{
  return CGAL_compare_x((const R::Point_2&)p,
                        (const R::Line_2&)l1,
                        (const R::Line_2&)l2);
}


template < class R >
inline CGAL_Comparison_result CGAL_compare_x(const CGAL_Line_2<R> &l1,
                                             const CGAL_Line_2<R> &l2,
                                             const CGAL_Line_2<R> &h1,
                                             const CGAL_Line_2<R> &h2)
{
  return CGAL_compare_x((const R::Line_2&)l1, (const R::Line_2&)l2,
                        (const R::Line_2&)h1, (const R::Line_2&)h2);
}


template < class R >
inline CGAL_Comparison_result CGAL_compare_x(const CGAL_Line_2<R> &l,
                                             const CGAL_Line_2<R> &h1,
                                             const CGAL_Line_2<R> &h2)
{
  return CGAL_compare_x((const R::Line_2&)l, (const R::Line_2&)h1,
                        (const R::Line_2&)l, (const R::Line_2&)h2);
}

template < class R >
inline CGAL_Comparison_result CGAL_compare_y(const CGAL_Point_2<R> &p,
                                             const CGAL_Line_2<R> &l1,
                                             const CGAL_Line_2<R> &l2)
{
  return CGAL_compare_y((const R::Point_2&)p,
                        (const R::Line_2&)l1,
                        (const R::Line_2&)l2);
}

template < class R >
inline CGAL_Comparison_result CGAL_compare_y(const CGAL_Line_2<R> &l1,
                                             const CGAL_Line_2<R> &l2,
                                             const CGAL_Line_2<R> &h1,
                                             const CGAL_Line_2<R> &h2)
{
  return CGAL_compare_y((const R::Line_2&)l1, (const R::Line_2&)l2,
                        (const R::Line_2&)h1, (const R::Line_2&)h2);
}


template < class R >
inline CGAL_Comparison_result CGAL_compare_y(const CGAL_Line_2<R> &l,
                                             const CGAL_Line_2<R> &h1,
                                             const CGAL_Line_2<R> &h2)
{
  return CGAL_compare_y((const R::Line_2&)l, (const R::Line_2&)h1,
                        (const R::Line_2&)l, (const R::Line_2&)h2);
}



template < class R >
CGAL_Comparison_result CGAL_compare_y_at_x(const CGAL_Point_2<R> &p,
                                           const CGAL_Line_2<R> &h)
{
  return CGAL_compare_y_at_x((const R::Point_2&)p,
                             (const R::Line_2&)h);
}

template < class R >
CGAL_Comparison_result CGAL_compare_y_at_x(const CGAL_Line_2<R> &l1,
                                           const CGAL_Line_2<R> &l2,
                                           const CGAL_Line_2<R> &h)
{
  return CGAL_compare_y_at_x((const R::Line_2&)l1,
                             (const R::Line_2&)l2,
                             (const R::Line_2&)h) ;
/*
  CGAL_Point_2<R> q;
  CGAL_Line_2_Line_2_pair<R> pair(&l1, &l2);
  if(pair.intersection_type() ==  CGAL_Line_2_Line_2_pair<R>::POINT){
    pair.intersection(q);
  } else {
    cerr << "Line l1 and l2 do not intersect.";
    CGAL_kernel_assertion(false);
  }

  return CGAL_compare_y_at_x(q, h);
*/
}

template < class R >
CGAL_Comparison_result CGAL_compare_y_at_x(const CGAL_Point_2<R> &p,
                                           const CGAL_Line_2<R> &h1,
                                           const CGAL_Line_2<R> &h2)
{
  CGAL_kernel_precondition( (! h1.is_vertical()) && (! h2.is_vertical()) );


  return CGAL_compare_y_at_x((const R::Point_2&)p,
                             (const R::Line_2&)h1,
                             (const R::Line_2&)h2);
}

template < class R >
CGAL_Comparison_result CGAL_compare_y_at_x(const CGAL_Line_2<R> &l1,
                                           const CGAL_Line_2<R> &l2,
                                           const CGAL_Line_2<R> &h1,
                                           const CGAL_Line_2<R> &h2)
{
  CGAL_kernel_precondition( (! h1.is_vertical()) && (! h2.is_vertical()) );


  return CGAL_compare_y_at_x((const R::Line_2&)l1,
                             (const R::Line_2&)l2,
                             (const R::Line_2&)h1,
                             (const R::Line_2&)h2);
}


#endif  // CGAL_PREDICATES_ON_LINES_2_H
