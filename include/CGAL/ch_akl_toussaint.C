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
// file          : include/CGAL/ch_akl_toussaint.C
// author(s)     : Stefan Schirra 
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


#ifndef CGAL_CH_AKL_TOUSSAINT_C
#define CGAL_CH_AKL_TOUSSAINT_C

#ifndef CGAL_CH_AKL_TOUSSAINT_H
#include <CGAL/ch_akl_toussaint.h>
#endif // CGAL_CH_AKL_TOUSSAINT_H
template <class ForwardIterator, class OutputIterator, class Traits>
OutputIterator
CGAL_ch_akl_toussaint(ForwardIterator first, ForwardIterator last, 
                      OutputIterator  result,
                      const Traits& ch_traits)
{
  typedef  typename Traits::Point_2                    Point_2;    
  typedef  typename Traits::Right_of_line              Right_of_line;
  typedef  typename Traits::Less_xy                    Less_xy;
  typedef  CGAL_ch_Binary_predicate_reversor< Point_2, Less_xy>
                                                       Greater_xy;
  typedef  typename Traits::Less_yx                    Less_yx;
  typedef  CGAL_ch_Binary_predicate_reversor< Point_2, Less_yx>
                                                       Greater_yx;

  if (first == last) return result;
  ForwardIterator n, s, e, w;
  CGAL_ch_nswe_point( first, last, n, s, w, e, ch_traits);
  if ( *n == *s )
  {
      *result = *w;  ++result;
      return result;
  }


  vector< Point_2 > region1;
  vector< Point_2 > region2;
  vector< Point_2 > region3;
  vector< Point_2 > region4;
  region1.reserve(16);
  region2.reserve(16);
  region3.reserve(16);
  region4.reserve(16);
  region1.push_back( *w);
  region2.push_back( *s);
  region3.push_back( *e);
  region4.push_back( *n);

  Right_of_line  rol_we( *w, *e);
  Right_of_line  rol_en( *e, *n);
  Right_of_line  rol_nw( *n, *w);
  Right_of_line  rol_ws( *w, *s);
  Right_of_line  rol_se( *s, *e);

  CGAL_ch_postcondition_code( ForwardIterator save_first = first; )

  for ( ; first != last; ++first )
  {
      if ( rol_we( *first ) )   
      {
          if ( rol_ws( *first ) )        region1.push_back( *first );
          else if ( rol_se( *first ) )   region2.push_back( *first );
      }
      else
      {
          if ( rol_en( *first ) )        region3.push_back( *first );
          else if ( rol_nw( *first ) )   region4.push_back( *first );
      }
  }

  #if defined(CGAL_CH_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
    || defined(NDEBUG)
  OutputIterator  res(result);
  #else
  CGAL_Tee_for_output_iterator<OutputIterator,Point_2> res(result);
  #endif // no postconditions ...
  sort( CGAL_successor(region1.begin() ), region1.end(), Less_xy() );
  sort( CGAL_successor(region2.begin() ), region2.end(), Less_xy() );
  sort( CGAL_successor(region3.begin() ), region3.end(), Greater_xy() );
  sort( CGAL_successor(region4.begin() ), region4.end(), Greater_xy() );

  if ( *w != *s )
  {
      region1.push_back( *s );
      CGAL_ch__ref_graham_andrew_scan( region1.begin(), region1.end(), 
                                       res, ch_traits);
  }
  if ( *s != *e )
  {
      region2.push_back( *e );
      CGAL_ch__ref_graham_andrew_scan( region2.begin(), region2.end(),
                                       res, ch_traits);
  }
  if ( *e != *n )
  {
      region3.push_back( *n );
      CGAL_ch__ref_graham_andrew_scan( region3.begin(), region3.end(),
                                       res, ch_traits);
  }
  if ( *n != *w )
  {
      region4.push_back( *w );
      CGAL_ch__ref_graham_andrew_scan( region4.begin(), region4.end(),
                                       res, ch_traits);
  }

  CGAL_ch_postcondition_code( first = save_first; )
  CGAL_ch_postcondition( \
      CGAL_is_ccw_strongly_convex_2( res.output_so_far_begin(), \
                                     res.output_so_far_end(), \
                                     ch_traits));
  CGAL_ch_expensive_postcondition( \
      CGAL_ch_brute_force_check_2( \
          first, last, \
          res.output_so_far_begin(), res.output_so_far_end(), \
          ch_traits)
  );
  #if defined(CGAL_CH_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
    || defined(NDEBUG)
  return res;
  #else
  return res.to_output_iterator();
  #endif // no postconditions ...

}


#endif // CGAL_CH_AKL_TOUSSAINT_C


