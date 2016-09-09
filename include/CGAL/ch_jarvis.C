// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/ch_jarvis.C
// package       : Convex_hull_2 (3.21)
// source        : convex_hull_2.lw
// revision      : 3.3
// revision_date : 03 Aug 2000
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================


#ifndef CGAL_CH_JARVIS_C
#define CGAL_CH_JARVIS_C

#ifndef CGAL_CH_JARVIS_H
#include <CGAL/ch_jarvis.h>
#endif // CGAL_CH_JARVIS_H

#include <CGAL/functional.h>

CGAL_BEGIN_NAMESPACE
template <class ForwardIterator, class OutputIterator, 
          class Point, class Traits>
OutputIterator
ch_jarvis_march(ForwardIterator first, ForwardIterator last,
                const Point& start_p, 
                const Point& stop_p, 
                OutputIterator  result,
                const Traits& ch_traits)
{
  if (first == last) return result;
  typedef   typename Traits::Less_rotate_ccw_2       Less_rotate_ccw;
  typedef   typename Traits::Point_2               Point_2;
  #if defined(CGAL_CH_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
    || defined(NDEBUG)
  OutputIterator  res(result);
  #else
  Tee_for_output_iterator<OutputIterator,Point_2> res(result);
  #endif // no postconditions ...
  CGAL_ch_assertion_code( \
      int count_points = 0; )
  CGAL_ch_assertion_code( \
      for (ForwardIterator fit = first; fit!= last; ++fit) ++count_points; )
  Less_rotate_ccw  
      rotation_predicate = ch_traits.less_rotate_ccw_2_object( );
  *res = start_p;  ++res;
  CGAL_ch_assertion_code( \
      int constructed_points = 1; )
  CGAL_ch_exactness_assertion_code( \
      Point previous_point = start_p; ) 

  ForwardIterator it = std::min_element( first, last, 
                                         bind_1(rotation_predicate, start_p) );
  while ( *it != stop_p )
  {
      CGAL_ch_exactness_assertion( \
          *it != previous_point );
      CGAL_ch_exactness_assertion_code( \
          previous_point = *it; )

      *res = *it;  ++res;
      CGAL_ch_assertion_code( \
          ++constructed_points;)
      CGAL_ch_assertion( \
          constructed_points <= count_points + 1 );

      it = std::min_element( first, last, 
                             bind_1(rotation_predicate, *it) );
  } 
  CGAL_ch_postcondition( \
      is_ccw_strongly_convex_2( res.output_so_far_begin(), \
                                     res.output_so_far_end(), \
                                     ch_traits));
  CGAL_ch_expensive_postcondition( \
      ch_brute_force_check_2( 
          first, last, \
          res.output_so_far_begin(), res.output_so_far_end(), \
          ch_traits));
  #if defined(CGAL_CH_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
    || defined(NDEBUG)
  return res;
  #else
  return res.to_output_iterator();
  #endif // no postconditions ...
}

template <class ForwardIterator, class OutputIterator, class Traits>
OutputIterator
ch_jarvis(ForwardIterator first, ForwardIterator last, 
               OutputIterator  result,
               const Traits& ch_traits)
{
  if (first == last) return result;
  ForwardIterator start;
  ch_w_point(first, last, start, ch_traits);
  return ch_jarvis_march( first, last, *start, *start, result, ch_traits);
}

CGAL_END_NAMESPACE

#endif // CGAL_CH_JARVIS_C

