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

#ifndef CGAL_CH_AKL_TOUSSAINT_C
#define CGAL_CH_AKL_TOUSSAINT_C

#include <CGAL/ch_akl_toussaint.h>

template <class ForwardIterator, class OutputIterator, class Traits>
OutputIterator
CGAL_ch_akl_toussaint(ForwardIterator first, ForwardIterator last, 
                      OutputIterator  result,
                      const Traits& ch_traits)
{
  typedef  Traits::Point_2                    Point_2;    
  typedef  Traits::Right_of_line              Right_of_line;
  typedef  Traits::Less_xy                    Less_xy;
  typedef  Traits::Greater_xy                 Greater_xy;
  typedef  Traits::Less_yx                    Less_yx;
  typedef  Traits::Greater_yx                 Greater_yx;


  if (first == last) return result;
  ForwardIterator n, s, e, w;
  CGAL_ch_nswe_point( first, last, n, s, w, e, ch_traits);
  if ( *n == *s )
  {
      *result++ = *w;
      return result;
  }


  vector< Point_2 > region1;
  vector< Point_2 > region2;
  vector< Point_2 > region3;
  vector< Point_2 > region4;
  region1.push_back( *w);
  region2.push_back( *s);
  region3.push_back( *e);
  region4.push_back( *n);

  Right_of_line  rol_we( *w, *e);
  Right_of_line  rol_en( *e, *n);
  Right_of_line  rol_nw( *n, *w);
  Right_of_line  rol_ws( *w, *s);
  Right_of_line  rol_se( *s, *e);
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

  OutputIterator  res(result);
  CGAL_ch_postcondition_code( vector< Point_2 >  VC; )

  sort( CGAL_successor(region1.begin() ), region1.end(), Less_xy() );
  sort( CGAL_successor(region2.begin() ), region2.end(), Less_xy() );
  sort( CGAL_successor(region3.begin() ), region3.end(), Greater_xy() );
  sort( CGAL_successor(region4.begin() ), region4.end(), Greater_xy() );

  if ( *w != *s )
  {
      region1.push_back( *s );
      CGAL_ch__ref_graham_andrew_scan( region1.begin(), region1.end(), 
                                       res, ch_traits);
      CGAL_ch_postcondition_code( \
          CGAL_ch_graham_andrew_scan( region1.begin(), region1.end(), \
                                      back_inserter(VC), ch_traits ); )

  }
  if ( *s != *e )
  {
      region2.push_back( *e );
      CGAL_ch__ref_graham_andrew_scan( region2.begin(), region2.end(),
                                       res, ch_traits);
      CGAL_ch_postcondition_code( \
          CGAL_ch_graham_andrew_scan( region2.begin(), region2.end(), \
                                      back_inserter(VC), ch_traits ); )

  }
  if ( *e != *n )
  {
      region3.push_back( *n );
      CGAL_ch__ref_graham_andrew_scan( region3.begin(), region3.end(),
                                       res, ch_traits);
      CGAL_ch_postcondition_code( \
          CGAL_ch_graham_andrew_scan( region3.begin(), region3.end(), \
                                      back_inserter(VC), ch_traits ); )

  }
  if ( *n != *w )
  {
      region4.push_back( *w );
      CGAL_ch__ref_graham_andrew_scan( region4.begin(), region4.end(),
                                       res, ch_traits);
      CGAL_ch_postcondition_code( \
          CGAL_ch_graham_andrew_scan( region4.begin(), region4.end(), \
                                      back_inserter(VC), ch_traits ); )

  }
  CGAL_ch_postcondition( \
      CGAL_is_ccw_strongly_convex_2(VC.begin(), VC.end(), ch_traits ));
  CGAL_ch_expensive_postcondition( \
      CGAL_ch_brute_force_check_2( first, last, VC.begin(), VC.end(), ch_traits ));



  return res;

}


#endif // CGAL_CH_AKL_TOUSSAINT_C


