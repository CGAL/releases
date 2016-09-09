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


#include <CGAL/stl_extensions.h>

#ifndef CGAL_CH_GRAHAM_ANDREW_C
#define CGAL_CH_GRAHAM_ANDREW_C

#include <CGAL/ch_graham_andrew.h>


template <class BidirectionalIterator, class OutputIterator, class Traits>
OutputIterator
CGAL_ch_graham_andrew_scan( BidirectionalIterator first,
                            BidirectionalIterator last,
                            OutputIterator        result,
                            const Traits&             ch_traits)
{
  vector< BidirectionalIterator >    S;
  BidirectionalIterator              alpha;
  BidirectionalIterator              beta;
  BidirectionalIterator              iter;

  CGAL_ch_precondition( first != last );
  CGAL_ch_precondition( CGAL_successor(first) != last );

  --last;

  CGAL_ch_precondition( *first != *last );

  S.push_back( last  );
  S.push_back( first );


  iter = first;
  do
  {
      ++iter;
  }
  while (( iter != last ) && !ch_traits.leftturn(*last, *first, *iter) );

  if ( iter != last )
  {
      S.push_back( iter );
      typedef  vector< BidirectionalIterator >::reverse_iterator  rev_iterator;
      rev_iterator  stack_rev_iter = S.rbegin(); 
      alpha = iter;
      beta  = *++stack_rev_iter;

      for ( ++iter ; iter != last; ++iter )
      {
          if ( ch_traits.leftturn(*alpha, *iter, *last) )
          {
              while ( !ch_traits.leftturn(*beta, *alpha, *iter) )
              {
                  S.pop_back();
                  alpha = beta;
                  stack_rev_iter = S.rbegin();
                  beta  = *++stack_rev_iter;
                  CGAL_ch_assertion(S.size() >= 2);
              }
              S.push_back( iter  );
              beta = alpha;
              alpha = iter;
          }
      }

  }

  typedef  vector< BidirectionalIterator >::iterator  std_iterator;
  std_iterator  stack_iter = S.begin();
  CGAL_ch_postcondition_code( typedef  Traits::Point_2   Point_2; )
  CGAL_ch_postcondition_code( vector< Point_2 > VC; )
  CGAL_ch_postcondition_code( VC.push_back( **stack_iter ) );

  for ( ++stack_iter;  stack_iter != S.end(); ++stack_iter)
  {
      *result++ =  **stack_iter;
      CGAL_ch_postcondition_code( VC.push_back( **stack_iter ) );

  }
  CGAL_ch_postcondition( CGAL_is_ccw_strongly_convex_2( VC.begin(), VC.end(), \
                                                        ch_traits ));


  return result;

}

template <class BidirectionalIterator, class OutputIterator, class Traits>
OutputIterator
CGAL_ch__ref_graham_andrew_scan( BidirectionalIterator first,
                                 BidirectionalIterator last,
                                 OutputIterator&       result,
                                 const Traits&             ch_traits)
{
  vector< BidirectionalIterator >    S;
  BidirectionalIterator              alpha;
  BidirectionalIterator              beta;
  BidirectionalIterator              iter;

  CGAL_ch_precondition( first != last );
  CGAL_ch_precondition( CGAL_successor(first) != last );

  --last;

  CGAL_ch_precondition( *first != *last );

  S.push_back( last  );
  S.push_back( first );


  iter = first;
  do
  {
      ++iter;
  }
  while (( iter != last ) && !ch_traits.leftturn(*last, *first, *iter) );

  if ( iter != last )
  {
      S.push_back( iter );
      typedef  vector< BidirectionalIterator >::reverse_iterator  rev_iterator;
      rev_iterator  stack_rev_iter = S.rbegin(); 
      alpha = iter;
      beta  = *++stack_rev_iter;

      for ( ++iter ; iter != last; ++iter )
      {
          if ( ch_traits.leftturn(*alpha, *iter, *last) )
          {
              while ( !ch_traits.leftturn(*beta, *alpha, *iter) )
              {
                  S.pop_back();
                  alpha = beta;
                  stack_rev_iter = S.rbegin();
                  beta  = *++stack_rev_iter;
                  CGAL_ch_assertion(S.size() >= 2);
              }
              S.push_back( iter  );
              beta = alpha;
              alpha = iter;
          }
      }

  }

  typedef  vector< BidirectionalIterator >::iterator  std_iterator;
  std_iterator  stack_iter = S.begin();
  CGAL_ch_postcondition_code( typedef  Traits::Point_2   Point_2; )
  CGAL_ch_postcondition_code( vector< Point_2 > VC; )
  CGAL_ch_postcondition_code( VC.push_back( **stack_iter ) );

  for ( ++stack_iter;  stack_iter != S.end(); ++stack_iter)
  {
      *result++ =  **stack_iter;
      CGAL_ch_postcondition_code( VC.push_back( **stack_iter ) );

  }
  CGAL_ch_postcondition( CGAL_is_ccw_strongly_convex_2( VC.begin(), VC.end(), \
                                                        ch_traits ));


  return result;

}

template <class InputIterator, class OutputIterator, class Traits>
OutputIterator
CGAL_ch_graham_andrew( InputIterator  first,
                       InputIterator  last,
                       OutputIterator result,
                       const Traits&      ch_traits)
{
  typedef  Traits::Less_xy   Less_xy;
  typedef  Traits::Point_2   Point_2;

  if (first == last) return result;
  vector< Point_2 >  V;
  copy( first, last, back_inserter(V) );
  sort( V.begin(), V.end(), Less_xy() );
  if ( *(V.begin()) == *(V.rbegin()) )
  {
      *result++ = *(V.begin());
      return result;
  }

  OutputIterator  res(result);
  CGAL_ch__ref_graham_andrew_scan( V.begin(), V.end(),  res, ch_traits);
  CGAL_ch__ref_graham_andrew_scan( V.rbegin(), V.rend(), res, ch_traits);
  CGAL_ch_postcondition_code( \
      vector< Point_2 >  VC; )
  CGAL_ch_postcondition_code( \
      CGAL_ch_graham_andrew_scan(V.begin(), V.end(), back_inserter(VC), ch_traits);)
  CGAL_ch_postcondition_code( 
      CGAL_ch_graham_andrew_scan(V.rbegin(), V.rend(), back_inserter(VC), ch_traits);)
  CGAL_ch_postcondition( \
      CGAL_is_ccw_strongly_convex_2(VC.begin(), VC.end(), ch_traits));
  CGAL_ch_expensive_postcondition( \
      CGAL_ch_brute_force_check_2( first, last, VC.begin(), VC.end(), ch_traits ));


  return res;

}


#endif // CGAL_CH_GRAHAM_ANDREW_C


