// ============================================================================
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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/ch_eddy.C
// author(s)     : Stefan Schirra 
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


#ifndef CGAL_CH_EDDY_C
#define CGAL_CH_EDDY_C

#ifndef CGAL_CH_EDDY_H
#include <CGAL/ch_eddy.h>
#endif // CGAL_CH_EDDY_H

template <class List, class ListIterator, class Traits>
void
CGAL_ch__recursive_eddy(List& L, 
                        ListIterator  a_it, ListIterator  b_it, 
                        const Traits& ch_traits)
{
  typedef  typename Traits::Point_2                    Point_2;    
  typedef  typename Traits::Right_of_line              Right_of_line;
  typedef  typename Traits::Less_dist_to_line          Less_dist;

  CGAL_CH_USE_ARGUMENT(ch_traits);
  CGAL_ch_precondition( \
    find_if(a_it, b_it, Right_of_line(*a_it,*b_it)) != b_it);


  ListIterator f_it = CGAL_successor(a_it);
  ListIterator c_it = max_element( f_it, b_it, Less_dist(*a_it,*b_it) );
  Point_2 c = *c_it;

  #ifndef CGAL_CH_VISUALIZE_EDDY
  c_it = partition( f_it, b_it, Right_of_line(*a_it, c ) );
  f_it = partition( c_it, b_it, Right_of_line(c, *b_it ) );
  c_it = L.insert(c_it, c);
  L.erase( f_it, b_it );

  #else
  typedef   typename Traits::Segment_2   Segment_2;
  CGAL_Window_ostream_iterator< Point_2 > winout(*W_global_ptr);
  (*W_global_ptr).clear();
  (*W_global_ptr) << CGAL_BLUE;
  copy( L.begin(), L.end(), winout );
  click_to_continue( *W_global_ptr );
  (*W_global_ptr) << CGAL_GREEN;
  copy( a_it, b_it, winout );
  (*W_global_ptr) << CGAL_BLACK;
  (*W_global_ptr) << *a_it;
  (*W_global_ptr) << *b_it;
  (*W_global_ptr) << CGAL_GREEN;
  (*W_global_ptr) << Segment_2(*a_it,*b_it);
  click_to_continue( *W_global_ptr );
  (*W_global_ptr) << CGAL_BLACK << c;
  click_to_continue( *W_global_ptr );
  c_it = partition( f_it, b_it, Right_of_line(*a_it, c ) );
  (*W_global_ptr) << CGAL_VIOLET;
  (*W_global_ptr) << Segment_2(*a_it,c);
  copy( f_it, c_it, winout );
  click_to_continue( *W_global_ptr );
  f_it = partition( c_it, b_it, Right_of_line(c, *b_it ) );
  (*W_global_ptr) << CGAL_RED;
  (*W_global_ptr) << Segment_2(c, *b_it);
  copy( c_it, f_it, winout );
  click_to_continue( *W_global_ptr );
  c_it = L.insert(c_it, c);
  (*W_global_ptr) << CGAL_BLACK << c;
  // copy( f_it, b_it, winout );
  L.erase( f_it, b_it );
  click_to_continue( *W_global_ptr );

  #endif // CGAL_CH_VISUALIZE_EDDY

  if ( CGAL_successor(a_it) != c_it )
  {
      CGAL_ch__recursive_eddy( L, a_it, c_it, ch_traits);
  }
  if ( CGAL_successor(c_it) != b_it )
  {
      CGAL_ch__recursive_eddy( L, c_it, b_it, ch_traits);
  }


}

template <class InputIterator, class OutputIterator, class Traits>
OutputIterator
CGAL_ch_eddy(InputIterator first, InputIterator last,
             OutputIterator  result,
             const Traits& ch_traits)
{
  typedef  typename Traits::Point_2                    Point_2;    
  typedef  typename Traits::Right_of_line              Right_of_line;
  typedef  typename Traits::Less_dist_to_line          Less_dist;

  if (first == last) return result;
  list< Point_2 >   L;
  copy( first, last, back_inserter(L) );
  #ifdef CGAL_CH_VISUALIZE_EDDY
  CGAL_Window_ostream_iterator< Point_2 > winout(*W_global_ptr);
  (*W_global_ptr) << CGAL_BLUE;
  copy( L.begin(), L.end(), winout );
  click_to_continue( *W_global_ptr );

  #endif // CGAL_CH_VISUALIZE_EDDY

  typedef  list< Point_2 >::iterator  list_iterator;
  list_iterator   w, e;
  CGAL_ch_we_point(L.begin(), L.end(), w, e, ch_traits);
  Point_2 wp = *w;
  Point_2 ep = *e;
  if ( wp == ep )
  {
      *result++ = wp;
      return result;
  }

  L.erase(w);
  L.erase(e);
  e = partition(L.begin(), L.end(), Right_of_line( wp, ep) );
  L.push_front(wp);
  e = L.insert(e, ep);

  if ( CGAL_successor(L.begin()) != e )
  {
      CGAL_ch__recursive_eddy( L, L.begin(), e, ch_traits);
  }
  w = find_if( e, L.end(), Right_of_line( ep, wp) );
  if ( w == L.end() )
  {
      L.erase( ++e, L.end() );
      return copy( L.begin(), L.end(), result );
  }
  w = L.insert(L.end(), wp);
  CGAL_ch__recursive_eddy( L, e, w, ch_traits);


  CGAL_ch_postcondition( \
      CGAL_is_ccw_strongly_convex_2( L.begin(), w, ch_traits) );
  CGAL_ch_expensive_postcondition( \
      CGAL_ch_brute_force_check_2( first, last, \
                                   L.begin(), w, ch_traits ) );

  #ifdef CGAL_CH_VISUALIZE_EDDY
  (*W_global_ptr).clear();
  (*W_global_ptr) << CGAL_BLUE;
  copy( L.begin(), w, winout );
  click_to_continue( *W_global_ptr );

  #endif // CGAL_CH_VISUALIZE_EDDY
  return copy( L.begin(), w, result );

}


#endif // CGAL_CH_EDDY_C


