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

// Source: predicates_on_lines_2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_PREDICATES_ON_LINES_2_H
#define CGAL_PREDICATES_ON_LINES_2_H

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
