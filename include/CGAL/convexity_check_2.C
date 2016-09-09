// ======================================================================
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
// ----------------------------------------------------------------------
// release       : CGAL-1.1
// release_date  : 1998, July 24
//
// file          : include/CGAL/convexity_check_2.C
// package       : Convex_hull (1.2.3)
// source        : convex_hull_2.lw
// revision      : 1.2.3
// revision_date : 07 Apr 1998
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_CONVEXITY_CHECK_2_C
#define CGAL_CONVEXITY_CHECK_2_C

#ifndef CGAL_CONVEXITY_CHECK_2_H
#include <CGAL/convexity_check_2.h>
#endif // CGAL_CONVEXITY_CHECK_2_H
template <class ForwardIterator, class Traits>
bool
CGAL_is_ccw_strongly_convex_2( ForwardIterator first, ForwardIterator last, 
                               const Traits& ch_traits)
{
  typedef  typename Traits::Less_xy      Less_xy;
  typedef  typename Traits::Leftturn     Leftturn;

  Less_xy  smaller_xy;
  Leftturn leftturn;

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
      if ( !leftturn( *iter1, *iter2, *iter3 ) ) return false; 
      if ( smaller_xy( *iter2, *iter1 ) && smaller_xy( *iter2, *iter3 )) ++f;

      ++iter1;
      ++iter2;
      ++iter3;
  }

  iter3 = first;
  if ( !leftturn( *iter1, *iter2, *iter3 ) ) return false; 
  if ( smaller_xy( *iter2, *iter1 ) && smaller_xy( *iter2, *iter3 )) ++f;


  iter1 = iter2;
  iter2 = first;
  ++iter3;
  if ( !leftturn( *iter1, *iter2, *iter3 ) ) return false; 
  if ( smaller_xy( *iter2, *iter1 ) && smaller_xy( *iter2, *iter3 )) ++f;


  return ( f > 1 ) ? false : true;
}

template <class ForwardIterator, class Traits>
bool
CGAL_is_cw_strongly_convex_2( ForwardIterator first, ForwardIterator last, 
                              const Traits& ch_traits)
{
  typedef  typename Traits::Less_xy      Less_xy;
  typedef  typename Traits::Rightturn    Rightturn;

  Less_xy   smaller_xy;
  Rightturn rightturn;

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
      if ( !rightturn( *iter1, *iter2, *iter3 ) ) return false;
      if ( smaller_xy( *iter2, *iter1 ) && smaller_xy( *iter2, *iter3 )) ++f;

      ++iter1;
      ++iter2;
      ++iter3;
  }

  iter3 = first;
  if ( !rightturn( *iter1, *iter2, *iter3 ) ) return false;
  if ( smaller_xy( *iter2, *iter1 ) && smaller_xy( *iter2, *iter3 )) ++f;


  iter1 = iter2;
  iter2 = first;
  ++iter3;
  if ( !rightturn( *iter1, *iter2, *iter3 ) ) return false;
  if ( smaller_xy( *iter2, *iter1 ) && smaller_xy( *iter2, *iter3 )) ++f;


  return ( f > 1 ) ? false : true;
}

template <class ForwardIterator1, class ForwardIterator2, class Traits>
bool
CGAL_ch_brute_force_check_2(ForwardIterator1 first1, ForwardIterator1 last1,
                            ForwardIterator2 first2, ForwardIterator2 last2,
                            const Traits& )
{
  typedef    typename Traits::Right_of_line    Right_of_line;
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
                                  const Traits& )
{
  typedef    typename Traits::Right_of_line    Right_of_line;
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
