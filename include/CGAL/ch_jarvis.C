// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/ch_jarvis.C
// package       : Convex_hull (2.0.8)
// source        : convex_hull_2.lw
// revision      : 2.0.8
// revision_date : 06 May 1999
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_CH_JARVIS_C
#define CGAL_CH_JARVIS_C

#ifndef CGAL_CH_JARVIS_H
#include <CGAL/ch_jarvis.h>
#endif // CGAL_CH_JARVIS_H

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
  typedef   typename Traits::Less_rotate_ccw       Less_rotate_ccw;
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
      rotation_predicate = ch_traits.get_less_rotate_ccw_object( start_p );
  *res = start_p;  ++res;
  CGAL_ch_assertion_code( \
      int constructed_points = 1; )
  CGAL_ch_exactness_assertion_code( \
      Point previous_point = start_p; ) 

  ForwardIterator it = std::min_element( first, last, rotation_predicate );
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

      rotation_predicate = ch_traits.get_less_rotate_ccw_object( *it );
      it = std::min_element( first, last, rotation_predicate );
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

