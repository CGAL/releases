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


#ifndef CGAL_CONVEXITY_CHECK_2_C
#define CGAL_CONVEXITY_CHECK_2_C

#include <CGAL/convexity_check_2.h>
#include <algo.h>
#include <CGAL/stl_extensions.h>

template <class ForwardIterator, class Traits>
bool
CGAL_is_ccw_strongly_convex_2( ForwardIterator first, ForwardIterator last, 
                               const Traits& ch_traits)
{
  typedef  Traits::Less_xy      Less_xy;
  Less_xy  smaller_xy;

  ForwardIterator iter1;
  ForwardIterator iter2;
  ForwardIterator iter3;

  if ( first == last) return true;

  iter2 = first;
  iter3 = ++iter2;

  if (iter3 == last ) return true;

  ++iter3;

  if (iter3 == last ) return ( *first != *iter2 );

  iter1 = first;
  short int f = 0;

  while (iter3 != last) 
  {
      if ( !ch_traits.leftturn( *iter1, *iter2, *iter3 ) ) return false; 
      if ( smaller_xy( *iter2, *iter1 ) && smaller_xy( *iter2, *iter3 )) ++f;

      ++iter1;
      ++iter2;
      ++iter3;
  }

  iter3 = first;
  if ( !ch_traits.leftturn( *iter1, *iter2, *iter3 ) ) return false; 
  if ( smaller_xy( *iter2, *iter1 ) && smaller_xy( *iter2, *iter3 )) ++f;


  iter1 = iter2;
  iter2 = first;
  iter3++;
  if ( !ch_traits.leftturn( *iter1, *iter2, *iter3 ) ) return false; 
  if ( smaller_xy( *iter2, *iter1 ) && smaller_xy( *iter2, *iter3 )) ++f;


  return ( f > 1 ) ? false : true;
}

template <class ForwardIterator, class Traits>
bool
CGAL_is_cw_strongly_convex_2( ForwardIterator first, ForwardIterator last, 
                              const Traits& ch_traits)
{
  typedef  Traits::Less_xy      Less_xy;
  Less_xy  smaller_xy;

  ForwardIterator iter1;
  ForwardIterator iter2;
  ForwardIterator iter3;

  if ( first == last) return true;

  iter2 = first;
  iter3 = ++iter2;

  if (iter3 == last ) return true;

  ++iter3;

  if (iter3 == last ) return ( *first != *iter2 );

  iter1 = first;
  short int f = 0;

  while (iter3 != last) 
  {
      if ( !ch_traits.rightturn( *iter1, *iter2, *iter3 ) ) return false;
      if ( smaller_xy( *iter2, *iter1 ) && smaller_xy( *iter2, *iter3 )) ++f;

      ++iter1;
      ++iter2;
      ++iter3;
  }

  iter3 = first;
  if ( !ch_traits.rightturn( *iter1, *iter2, *iter3 ) ) return false;
  if ( smaller_xy( *iter2, *iter1 ) && smaller_xy( *iter2, *iter3 )) ++f;


  iter1 = iter2;
  iter2 = first;
  iter3++;
  if ( !ch_traits.rightturn( *iter1, *iter2, *iter3 ) ) return false;
  if ( smaller_xy( *iter2, *iter1 ) && smaller_xy( *iter2, *iter3 )) ++f;


  return ( f > 1 ) ? false : true;
}

template <class ForwardIterator1, class ForwardIterator2, class Traits>
bool
CGAL_ch_brute_force_check_2(ForwardIterator1 first1, ForwardIterator1 last1,
                            ForwardIterator2 first2, ForwardIterator2 last2,
                            const Traits& ch_traits)
{
  CGAL_CH_USE_ARGUMENT(ch_traits);
  typedef    Traits::Right_of_line    Right_of_line;
  ForwardIterator1 iter11;
  ForwardIterator2 iter21;
  ForwardIterator2 iter22;

  if ( first1 == last1) return true;

  if ( first2 == last2) return false;

  if ( CGAL_successor(first2) == last2 )
  {
      while (first1 != last1)
      {
          if ( *first1++ != *first2 ) return false;
      }
      return true;
  }

  Right_of_line  rol(*first2, *CGAL_successor(first2) );
  iter22 = first2;
  iter21 = iter22++;
  while (iter22 != last2)
  {
      rol = Right_of_line( *iter21++, *iter22++ );
      iter11 = find_if( first1, last1, rol );
      if (iter11 != last1 ) return false;
  }

  rol = Right_of_line( *iter21, *first2 );   
  iter11 = find_if( first1, last1, rol );
  if (iter11 != last1 ) return false;


  return true;

}

template <class ForwardIterator1, class ForwardIterator2, class Traits>
bool
CGAL_ch_brute_force_chain_check_2(ForwardIterator1 first1, 
                                  ForwardIterator1 last1,
                                  ForwardIterator2 first2, 
                                  ForwardIterator2 last2,
                                  const Traits& ch_traits)
{
  CGAL_CH_USE_ARGUMENT(ch_traits);
  typedef    Traits::Right_of_line    Right_of_line;
  ForwardIterator1 iter11;
  ForwardIterator2 iter21;
  ForwardIterator2 iter22;

  if ( first1 == last1) return true;

  if ( first2 == last2) return false;

  if ( CGAL_successor(first2) == last2 )
  {
      while (first1 != last1)
      {
          if ( *first1++ != *first2 ) return false;
      }
      return true;
  }

  Right_of_line  rol(*first2, *CGAL_successor(first2) );
  iter22 = first2;
  iter21 = iter22++;
  while (iter22 != last2)
  {
      rol = Right_of_line( *iter21++, *iter22++ );
      iter11 = find_if( first1, last1, rol );
      if (iter11 != last1 ) return false;
  }

  return true;

}



#endif // CGAL_CONVEXITY_CHECK_2_C

