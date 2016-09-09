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
// file          : include/CGAL/ch_eddy.C
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


#ifndef CGAL_CH_EDDY_C
#define CGAL_CH_EDDY_C

#ifndef CGAL_CH_EDDY_H
#include <CGAL/ch_eddy.h>
#endif // CGAL_CH_EDDY_H

CGAL_BEGIN_NAMESPACE
template <class List, class ListIterator, class Traits>
void
ch__recursive_eddy(List& L, 
                        ListIterator  a_it, ListIterator  b_it, 
                        const Traits& ch_traits)
{
  typedef  typename Traits::Point_2                    Point_2;    
  typedef  typename Traits::Right_of_line              Right_of_line;
  typedef  typename Traits::Less_dist_to_line          Less_dist;

  CGAL_ch_precondition( \
    std::find_if(a_it, b_it, \
            ch_traits.get_right_of_line_object(*a_it,*b_it)) \
    != b_it );


  ListIterator f_it = successor(a_it);
  ListIterator 
      c_it = std::max_element( f_it, b_it, ch_traits.get_less_dist_to_line_object(*a_it,*b_it));
  Point_2 c = *c_it;

  c_it = std::partition( f_it, b_it, ch_traits.get_right_of_line_object(*a_it, c ) );
  f_it = std::partition( c_it, b_it, ch_traits.get_right_of_line_object(c, *b_it ) );
  c_it = L.insert(c_it, c);
  L.erase( f_it, b_it );

  if ( successor(a_it) != c_it )
  {
      ch__recursive_eddy( L, a_it, c_it, ch_traits);
  }
  if ( successor(c_it) != b_it )
  {
      ch__recursive_eddy( L, c_it, b_it, ch_traits);
  }


}

template <class InputIterator, class OutputIterator, class Traits>
OutputIterator
ch_eddy(InputIterator first, InputIterator last,
             OutputIterator  result,
             const Traits& ch_traits)
{
  typedef  typename Traits::Point_2                    Point_2;    
  typedef  typename Traits::Right_of_line              Right_of_line;
  typedef  typename Traits::Less_dist_to_line          Less_dist;

  if (first == last) return result;
  std::list< Point_2 >   L;
  std::copy( first, last, std::back_inserter(L) );

  typedef  std::list< Point_2 >::iterator  list_iterator;
  list_iterator   w, e;
  ch_we_point(L.begin(), L.end(), w, e, ch_traits);
  Point_2 wp = *w;
  Point_2 ep = *e;
  if ( wp == ep )
  {
      *result = wp;  ++result;
      return result;
  }

  L.erase(w);
  L.erase(e);
  e = std::partition(L.begin(), L.end(), ch_traits.get_right_of_line_object( wp, ep) );
  L.push_front(wp);
  e = L.insert(e, ep);

  if ( successor(L.begin()) != e )
  {
      ch__recursive_eddy( L, L.begin(), e, ch_traits);
  }
  w = std::find_if( e, L.end(), ch_traits.get_right_of_line_object( ep, wp) );
  if ( w == L.end() )
  {
      L.erase( ++e, L.end() );
      return std::copy( L.begin(), L.end(), result );
  }
  w = L.insert(L.end(), wp);
  ch__recursive_eddy( L, e, w, ch_traits);


  CGAL_ch_postcondition( \
      is_ccw_strongly_convex_2( L.begin(), w, ch_traits) );
  CGAL_ch_expensive_postcondition( \
      ch_brute_force_check_2( first, last, \
                                   L.begin(), w, ch_traits ) );

  return std::copy( L.begin(), w, result );

}

CGAL_END_NAMESPACE

#endif // CGAL_CH_EDDY_C

