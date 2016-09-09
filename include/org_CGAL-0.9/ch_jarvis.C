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

// Author: Stefan Schirra
// Source: cgal_convex_hull_2.lw

#ifndef CGAL_CH_JARVIS_C
#define CGAL_CH_JARVIS_C

#include <CGAL/ch_jarvis.h>

template <class ForwardIterator, class OutputIterator, class Point, class Traits>
OutputIterator
CGAL_ch_jarvis_march(ForwardIterator first, ForwardIterator last,
                     const Point& start_p, 
                     const Point& stop_p, 
                     OutputIterator  result,
                     const Traits& ch_traits)
{
  if (first == last) return result;
  typedef   Traits::Less_rotate_ccw       Less_rotate_ccw;
  CGAL_CH_USE_ARGUMENT(ch_traits);
  CGAL_ch_assertion_code( \
      int count_points = 0; )
  CGAL_ch_assertion_code( \
      for (ForwardIterator fit = first; fit!= last; ++fit) count_points++; )
  CGAL_ch_postcondition_code( \
      typedef   Traits::Point_2       Point_2; )

  Less_rotate_ccw  rotation_predicate( start_p );
  *result++ = start_p;
  CGAL_ch_assertion_code( \
      int constructed_points = 1; )
  CGAL_ch_postcondition_code( \
      vector< Point_2 > VC; )
  CGAL_ch_postcondition_code( \
      VC.push_back( start_p); )
  CGAL_ch_exactness_assertion_code( \
      Point previous_point = start_p; ) 

  ForwardIterator it = min_element( first, last, rotation_predicate );
  while ( *it != stop_p )
  {
      CGAL_ch_exactness_assertion( \
          *it != previous_point );
      CGAL_ch_exactness_assertion_code( \
          previous_point = *it; )

      *result++ = *it;
      CGAL_ch_postcondition_code( \
          VC.push_back( *it ); )
      CGAL_ch_assertion_code( \
          ++constructed_points;)
      CGAL_ch_assertion( \
          constructed_points <= count_points + 1 );

      rotation_predicate = Less_rotate_ccw( *it );
      it = min_element( first, last, rotation_predicate );
  } 
  CGAL_ch_postcondition( \
      CGAL_is_ccw_strongly_convex_2( VC.begin(), VC.end(), ch_traits ));
  CGAL_ch_expensive_postcondition( \
      CGAL_ch_brute_force_chain_check_2( first, last, VC.begin(), VC.end(), \
                                         ch_traits) );


  return result;
}

template <class ForwardIterator, class OutputIterator, class Traits>
OutputIterator
CGAL_ch_jarvis(ForwardIterator first, ForwardIterator last, 
               OutputIterator  result,
               const Traits& ch_traits)
{
  if (first == last) return result;
  ForwardIterator start;
  CGAL_ch_w_point(first, last, start, ch_traits);
  return CGAL_ch_jarvis_march( first, last, *start, *start, result, ch_traits);
}



#endif // CGAL_CH_JARVIS_C

