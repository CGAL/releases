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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-1.2
// release_date  : 1999, January 18
// 
// source        : predicates_on_lines_2.fw
// file          : include/CGAL/predicates_on_lines_2.h
// package       : _2 (1.3)
// revision      : 1.3
// revision_date : 15 Dec 1998 
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
//
// email         : cgal@cs.uu.nl
//
// ======================================================================
 

#ifndef CGAL_PREDICATES_ON_LINES_2_H
#define CGAL_PREDICATES_ON_LINES_2_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#ifndef CGAL_PREDICATES_ON_LINESH2_H
#include <CGAL/predicates_on_linesH2.h>
#endif // CGAL_PREDICATES_ON_LINESH2_H
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#ifndef CGAL_PREDICATES_ON_LINESC2_H
#include <CGAL/predicates_on_linesC2.h>
#endif // CGAL_PREDICATES_ON_LINESC2_H
#endif // CGAL_CARTESIAN_H

#ifndef CGAL_POINT_2_H
#include <CGAL/Point_2.h>
#endif // CGAL_POINT_2_H
#ifndef CGAL_PREDICATES_ON_POINTS_2_H
#include <CGAL/predicates_on_points_2.h>
#endif // CGAL_PREDICATES_ON_POINTS_2_H
#ifndef CGAL_LINE_2_H
#include <CGAL/Line_2.h>
#endif // CGAL_LINE_2_H


template < class R >
inline
CGAL_Comparison_result
CGAL_compare_x(const CGAL_Point_2<R> &p,
               const CGAL_Line_2<R> &l1,
               const CGAL_Line_2<R> &l2)
{
  typedef typename  R::Point_2    Point_2;
  typedef typename  R::Line_2     Line_2 ;
  return CGAL_compare_x((const Point_2&)p,
                        (const Line_2&)l1,
                        (const Line_2&)l2);
}

template < class R >
inline
CGAL_Comparison_result
CGAL_compare_x(const CGAL_Line_2<R> &l1,
               const CGAL_Line_2<R> &l2,
               const CGAL_Line_2<R> &h1,
               const CGAL_Line_2<R> &h2)
{
  typedef typename  R::Line_2     Line_2 ;
  return CGAL_compare_x((const Line_2&)l1, (const Line_2&)l2,
                        (const Line_2&)h1, (const Line_2&)h2);
}


template < class R >
inline
CGAL_Comparison_result
CGAL_compare_x(const CGAL_Line_2<R> &l,
               const CGAL_Line_2<R> &h1,
               const CGAL_Line_2<R> &h2)
{
  typedef typename  R::Line_2     Line_2 ;
  return CGAL_compare_x((const Line_2&)l, (const Line_2&)h1,
                        (const Line_2&)l, (const Line_2&)h2);
}

template < class R >
inline
CGAL_Comparison_result
CGAL_compare_y(const CGAL_Point_2<R> &p,
               const CGAL_Line_2<R> &l1,
               const CGAL_Line_2<R> &l2)
{
  typedef typename  R::Point_2    Point_2;
  typedef typename  R::Line_2     Line_2 ;
  return CGAL_compare_y((const Point_2&)p,
                        (const Line_2&)l1,
                        (const Line_2&)l2);
}

template < class R >
inline
CGAL_Comparison_result
CGAL_compare_y(const CGAL_Line_2<R> &l1,
               const CGAL_Line_2<R> &l2,
               const CGAL_Line_2<R> &h1,
               const CGAL_Line_2<R> &h2)
{
  typedef typename  R::Line_2     Line_2 ;
  return CGAL_compare_y((const Line_2&)l1, (const Line_2&)l2,
                        (const Line_2&)h1, (const Line_2&)h2);
}

template < class R >
inline
CGAL_Comparison_result
CGAL_compare_y(const CGAL_Line_2<R> &l,
               const CGAL_Line_2<R> &h1,
               const CGAL_Line_2<R> &h2)
{
  typedef typename  R::Line_2     Line_2 ;
  return CGAL_compare_y((const Line_2&)l, (const Line_2&)h1,
                        (const Line_2&)l, (const Line_2&)h2);
}


template < class R >
inline
CGAL_Comparison_result
CGAL_compare_y_at_x(const CGAL_Point_2<R> &p, const CGAL_Line_2<R> &h)
{
  typedef typename  R::Point_2    Point_2;
  typedef typename  R::Line_2     Line_2 ;
  return CGAL_compare_y_at_x((const Point_2&)p,
                             (const Line_2&)h);
}

template < class R >
inline
CGAL_Comparison_result
CGAL_compare_y_at_x(const CGAL_Line_2<R> &l1,
                    const CGAL_Line_2<R> &l2,
                    const CGAL_Line_2<R> &h)
{
  typedef typename  R::Line_2     Line_2 ;
  return CGAL_compare_y_at_x((const Line_2&)l1,
                             (const Line_2&)l2,
                             (const Line_2&)h) ;
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
inline
CGAL_Comparison_result
CGAL_compare_y_at_x(const CGAL_Point_2<R> &p,
                    const CGAL_Line_2<R> &h1,
                    const CGAL_Line_2<R> &h2)
{
  CGAL_kernel_precondition( (! h1.is_vertical()) && (! h2.is_vertical()) );
  typedef typename  R::Point_2    Point_2;
  typedef typename  R::Line_2     Line_2 ;
  return CGAL_compare_y_at_x((const Point_2&)p,
                             (const Line_2&)h1,
                             (const Line_2&)h2);
}

template < class R >
inline
CGAL_Comparison_result
CGAL_compare_y_at_x(const CGAL_Line_2<R> &l1,
                    const CGAL_Line_2<R> &l2,
                    const CGAL_Line_2<R> &h1,
                    const CGAL_Line_2<R> &h2)
{
  CGAL_kernel_precondition( (! h1.is_vertical()) && (! h2.is_vertical()) );
  typedef typename  R::Line_2     Line_2 ;
  return CGAL_compare_y_at_x((const Line_2&)l1,
                             (const Line_2&)l2,
                             (const Line_2&)h1,
                             (const Line_2&)h2);
}


#endif  // CGAL_PREDICATES_ON_LINES_2_H
