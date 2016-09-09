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
// file          : include/CGAL/ch_akl_toussaint.C
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


#ifndef CGAL_CH_AKL_TOUSSAINT_C
#define CGAL_CH_AKL_TOUSSAINT_C

#ifndef CGAL_CH_AKL_TOUSSAINT_H
#include <CGAL/ch_akl_toussaint.h>
#endif // CGAL_CH_AKL_TOUSSAINT_H

CGAL_BEGIN_NAMESPACE
template <class ForwardIterator, class OutputIterator, class Traits>
OutputIterator
ch_akl_toussaint(ForwardIterator first, ForwardIterator last, 
                      OutputIterator  result,
                      const Traits&   ch_traits)
{
  typedef  typename Traits::Point_2                    Point_2;    
  typedef  typename Traits::Right_of_line              Right_of_line;
  typedef  typename Traits::Less_xy                    Less_xy;
  typedef  ch_Binary_predicate_reversor< Point_2, Less_xy>
                                                       Greater_xy;
  typedef  typename Traits::Less_yx                    Less_yx;
  typedef  ch_Binary_predicate_reversor< Point_2, Less_yx>
                                                       Greater_yx;

  if (first == last) return result;
  ForwardIterator n, s, e, w;
  ch_nswe_point( first, last, n, s, w, e, ch_traits);
  if ( *n == *s )
  {
      *result = *w;  ++result;
      return result;
  }


  std::vector< Point_2 > region1;
  std::vector< Point_2 > region2;
  std::vector< Point_2 > region3;
  std::vector< Point_2 > region4;
  region1.reserve(16);
  region2.reserve(16);
  region3.reserve(16);
  region4.reserve(16);
  region1.push_back( *w);
  region2.push_back( *s);
  region3.push_back( *e);
  region4.push_back( *n);

  Right_of_line  rol_we = ch_traits.get_right_of_line_object( *w, *e);
  Right_of_line  rol_en = ch_traits.get_right_of_line_object( *e, *n);
  Right_of_line  rol_nw = ch_traits.get_right_of_line_object( *n, *w);
  Right_of_line  rol_ws = ch_traits.get_right_of_line_object( *w, *s);
  Right_of_line  rol_se = ch_traits.get_right_of_line_object( *s, *e);

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
  Tee_for_output_iterator<OutputIterator,Point_2> res(result);
  #endif // no postconditions ...
  std::sort( successor(region1.begin() ), region1.end(), 
             ch_traits.get_less_xy_object() );
  std::sort( successor(region2.begin() ), region2.end(), 
             ch_traits.get_less_xy_object() );
  std::sort( successor(region3.begin() ), region3.end(), 
             Greater_xy(ch_traits.get_less_xy_object()) );
  std::sort( successor(region4.begin() ), region4.end(), 
             Greater_xy(ch_traits.get_less_xy_object()) );

  if ( *w != *s )
  {
      region1.push_back( *s );
      ch__ref_graham_andrew_scan( region1.begin(), region1.end(), 
                                       res, ch_traits);
  }
  if ( *s != *e )
  {
      region2.push_back( *e );
      ch__ref_graham_andrew_scan( region2.begin(), region2.end(),
                                       res, ch_traits);
  }
  if ( *e != *n )
  {
      region3.push_back( *n );
      ch__ref_graham_andrew_scan( region3.begin(), region3.end(),
                                       res, ch_traits);
  }
  if ( *n != *w )
  {
      region4.push_back( *w );
      ch__ref_graham_andrew_scan( region4.begin(), region4.end(),
                                       res, ch_traits);
  }

  CGAL_ch_postcondition_code( first = save_first; )
  CGAL_ch_postcondition( \
      is_ccw_strongly_convex_2( res.output_so_far_begin(), \
                                     res.output_so_far_end(), \
                                     ch_traits));
  CGAL_ch_expensive_postcondition( \
      ch_brute_force_check_2( \
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

CGAL_END_NAMESPACE

#endif // CGAL_CH_AKL_TOUSSAINT_C


