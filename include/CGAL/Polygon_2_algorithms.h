// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
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
// file          : include/CGAL/Polygon_2_algorithms.h
// package       : Polygon (1.10)
// source        : 
// revision      : 1.8a
// revision_date : 13 Mar 1998
// author(s)     : Wieger Wesselink
//
// coordinator   : Utrecht University
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_POLYGON_2_ALGORITHMS_H
#define CGAL_POLYGON_2_ALGORITHMS_H

#include <CGAL/basic.h>

#include <CGAL/enum.h>
#include <CGAL/Bbox_2.h>

#include <CGAL/polygon_assertions.h>

#ifdef CGAL_REP_CLASS_DEFINED
#include <CGAL/Polygon_traits_2.h>
#endif // CGAL_REP_CLASS_DEFINED

//-----------------------------------------------------------------------//
//                  algorithms for sequences of 2D points
//-----------------------------------------------------------------------//

template <class ForwardIterator, class Traits>
ForwardIterator CGAL_left_vertex_2(ForwardIterator first,
                                   ForwardIterator last,
                                   const Traits& traits);

template <class ForwardIterator, class Traits>
ForwardIterator CGAL_right_vertex_2(ForwardIterator first,
                                    ForwardIterator last,
                                    const Traits& traits);

template <class ForwardIterator, class Traits>
ForwardIterator CGAL_top_vertex_2(ForwardIterator first,
                                  ForwardIterator last,
                                  const Traits& traits);

template <class ForwardIterator, class Traits>
ForwardIterator CGAL_bottom_vertex_2(ForwardIterator first,
                                     ForwardIterator last,
                                     const Traits& traits);

template <class InputIterator>
CGAL_Bbox_2 CGAL_bbox_2(InputIterator first, InputIterator last);

template <class ForwardIterator, class Numbertype, class Traits>
void CGAL_area_2(ForwardIterator first,
                 ForwardIterator last,
                 Numbertype& result,
                 const Traits& traits);

template <class ForwardIterator, class Traits>
bool CGAL_is_convex_2(ForwardIterator first,
                      ForwardIterator last,
                      const Traits& traits);

template <class ForwardIterator, class Traits>
bool CGAL_is_simple_2(ForwardIterator first,
                      ForwardIterator last,
                      const Traits& traits);

// In the following two functions we would like to use Traits::Point_2 instead
// of Point, but this is not allowed by g++ 2.7.2.

template <class ForwardIterator, class Point, class Traits>
CGAL_Oriented_side CGAL_oriented_side_2(ForwardIterator first,
                                        ForwardIterator last,
                                        const Point& point,
                                        const Traits& traits);

template <class ForwardIterator, class Point, class Traits>
CGAL_Bounded_side CGAL_bounded_side_2(ForwardIterator first,
                                      ForwardIterator last,
                                      const Point& point,
                                      const Traits& traits);

template <class ForwardIterator, class Traits>
CGAL_Orientation CGAL_orientation_2(ForwardIterator first,
                                    ForwardIterator last,
                                    const Traits& traits);

//-----------------------------------------------------------------------//
//                         implementation
//-----------------------------------------------------------------------//

#ifdef CGAL_REP_CLASS_DEFINED
template <class ForwardIterator, class R>
inline
ForwardIterator CGAL_left_vertex_2_aux(ForwardIterator first,
                                       ForwardIterator last,
                                       const CGAL_Point_2<R>)
{
  return CGAL_left_vertex_2(first, last, CGAL_Polygon_traits_2<R>());
}

template <class ForwardIterator>
inline
ForwardIterator CGAL_left_vertex_2(ForwardIterator first,
                                   ForwardIterator last)
{
  return CGAL_left_vertex_2_aux(first, last, *first);
}

template <class ForwardIterator, class R>
inline
ForwardIterator CGAL_right_vertex_2_aux(ForwardIterator first,
                                        ForwardIterator last,
                                        const CGAL_Point_2<R>&)
{
  return CGAL_right_vertex_2(first, last, CGAL_Polygon_traits_2<R>());
}

template <class ForwardIterator>
inline
ForwardIterator CGAL_right_vertex_2(ForwardIterator first,
                                    ForwardIterator last)
{
  return CGAL_right_vertex_2_aux(first, last, *first);
}

template <class ForwardIterator, class R>
inline
ForwardIterator CGAL_top_vertex_2_aux(ForwardIterator first,
                                      ForwardIterator last,
                                      const CGAL_Point_2<R>&)
{
  return CGAL_top_vertex_2(first, last, CGAL_Polygon_traits_2<R>());
}

template <class ForwardIterator>
inline
ForwardIterator CGAL_top_vertex_2(ForwardIterator first,
                                  ForwardIterator last)
{
  return CGAL_top_vertex_2_aux(first, last, *first);
}

template <class ForwardIterator, class R>
inline
ForwardIterator CGAL_bottom_vertex_2_aux(ForwardIterator first,
                                         ForwardIterator last,
                                         const CGAL_Point_2<R>&)
{
  return CGAL_bottom_vertex_2(first, last, CGAL_Polygon_traits_2<R>());
}

template <class ForwardIterator>
inline
ForwardIterator CGAL_bottom_vertex_2(ForwardIterator first,
                                     ForwardIterator last)
{
  return CGAL_bottom_vertex_2_aux(first, last, *first);
}

template <class ForwardIterator, class Numbertype, class R>
inline
void CGAL_area_2_aux(ForwardIterator first,
                     ForwardIterator last,
                     Numbertype& result,
                     const CGAL_Point_2<R>&)
{
  CGAL_area_2(first, last, result, CGAL_Polygon_traits_2<R>());
}

template <class ForwardIterator, class Numbertype>
inline
void CGAL_area_2(ForwardIterator first,
                 ForwardIterator last,
                 Numbertype& result)
{
  CGAL_area_2_aux(first, last, result, *first);
}

template <class ForwardIterator, class R>
inline
bool CGAL_is_convex_2_aux(ForwardIterator first,
                          ForwardIterator last,
                          const CGAL_Point_2<R>&)
{
  return CGAL_is_convex_2(first, last, CGAL_Polygon_traits_2<R>());
}

template <class ForwardIterator>
inline
bool CGAL_is_convex_2(ForwardIterator first,
                      ForwardIterator last)
{
  return CGAL_is_convex_2_aux(first, last, *first);
}

template <class ForwardIterator, class R>
inline
bool CGAL_is_simple_2_aux(ForwardIterator first,
                          ForwardIterator last,
                          const CGAL_Point_2<R>&)
{
  return CGAL_is_simple_2(first, last, CGAL_Polygon_traits_2<R>());
}

template <class ForwardIterator>
inline
bool CGAL_is_simple_2(ForwardIterator first,
                      ForwardIterator last)
{
  return CGAL_is_simple_2_aux(first, last, *first);
}

template <class ForwardIterator, class R>
inline
CGAL_Oriented_side CGAL_oriented_side_2(ForwardIterator first,
                                        ForwardIterator last,
                                        const CGAL_Point_2<R>& point)
{
  return CGAL_oriented_side_2(first, last, point, CGAL_Polygon_traits_2<R>());
}

template <class ForwardIterator, class R>
inline
CGAL_Bounded_side CGAL_bounded_side_2(ForwardIterator first,
                                      ForwardIterator last,
                                      const CGAL_Point_2<R>& point)
{
  return CGAL_bounded_side_2(first, last, point, CGAL_Polygon_traits_2<R>());
}

template <class ForwardIterator, class R>
inline
CGAL_Orientation CGAL_orientation_2_aux(ForwardIterator first,
                                        ForwardIterator last,
                                        const CGAL_Point_2<R>&)
{
  return CGAL_orientation_2(first, last, CGAL_Polygon_traits_2<R>());
}

template <class ForwardIterator>
inline
CGAL_Orientation CGAL_orientation_2(ForwardIterator first,
                                    ForwardIterator last)
{
  return CGAL_orientation_2_aux(first, last, *first);
}
#endif // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION 
#include <CGAL/Polygon_2_algorithms.C>
#endif // CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION

#endif // CGAL_POLYGON_2_ALGORITHMS_H

