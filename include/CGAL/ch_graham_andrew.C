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
// file          : include/CGAL/ch_graham_andrew.C
// author(s)     : Stefan Schirra 
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


#ifndef CGAL_CH_GRAHAM_ANDREW_C
#define CGAL_CH_GRAHAM_ANDREW_C

#include <CGAL/stl_extensions.h>
#ifndef CGAL_CH_GRAHAM_ANDREW_H
#include <CGAL/ch_graham_andrew.h>
#endif // CGAL_CH_GRAHAM_ANDREW_H

template <class BidirectionalIterator, class OutputIterator, class Traits>
OutputIterator
CGAL_ch_graham_andrew_scan( BidirectionalIterator first,
                            BidirectionalIterator last,
                            OutputIterator        result,
                            const Traits&         ch_traits)
{
  typedef  typename Traits::Less_xy   Less_xy;
  typedef  typename Traits::Point_2   Point_2;
  typedef  typename Traits::Leftturn  Leftturn;

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
  Leftturn    leftturn;


  iter = first;
  do
  {
      ++iter;
  }
  while (( iter != last ) && !leftturn(*last, *first, *iter) );

  if ( iter != last )
  {
      S.push_back( iter );
      typedef typename vector<BidirectionalIterator>::reverse_iterator  
              rev_iterator;
      rev_iterator  stack_rev_iter = S.rbegin(); 
      alpha = iter;
      beta  = *++stack_rev_iter;

      for ( ++iter ; iter != last; ++iter )
      {
          if ( leftturn(*alpha, *iter, *last) )
          {
              while ( !leftturn(*beta, *alpha, *iter) )
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

  typedef typename vector< BidirectionalIterator >::iterator  std_iterator;
  std_iterator  stack_iter = S.begin();
  #if defined(CGAL_CH_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
    || defined(NDEBUG)
  OutputIterator  res(result);
  #else
  CGAL_Tee_for_output_iterator<OutputIterator,Point_2> res(result);
  #endif // no postconditions ...
  for ( ++stack_iter;  stack_iter != S.end(); ++stack_iter)
  { *res =  **stack_iter;  ++res; }
  #if defined(CGAL_CH_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
    || defined(NDEBUG)
  return res;
  #else
  return res.to_output_iterator();
  #endif // no postconditions ...
  CGAL_ch_postcondition( \
      CGAL_is_ccw_strongly_convex_2( res.output_so_far_begin(), \
                                     res.output_so_far_end(), \
                                     ch_traits));
  CGAL_ch_expensive_postcondition( \
      CGAL_ch_brute_force_check_2( \
          first, last, \
          res.output_so_far_begin(), res.output_so_far_end(), \
          ch_traits));
}

template <class BidirectionalIterator, class OutputIterator, class Traits>
OutputIterator
CGAL_ch__ref_graham_andrew_scan( BidirectionalIterator first,
                                 BidirectionalIterator last,
                                 OutputIterator&       result,
                                 const Traits&         ch_traits)
{
  typedef  typename Traits::Less_xy   Less_xy;
  typedef  typename Traits::Point_2   Point_2;
  typedef  typename Traits::Leftturn  Leftturn;

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
  Leftturn    leftturn;


  iter = first;
  do
  {
      ++iter;
  }
  while (( iter != last ) && !leftturn(*last, *first, *iter) );

  if ( iter != last )
  {
      S.push_back( iter );
      typedef typename vector<BidirectionalIterator>::reverse_iterator  
              rev_iterator;
      rev_iterator  stack_rev_iter = S.rbegin(); 
      alpha = iter;
      beta  = *++stack_rev_iter;

      for ( ++iter ; iter != last; ++iter )
      {
          if ( leftturn(*alpha, *iter, *last) )
          {
              while ( !leftturn(*beta, *alpha, *iter) )
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

  typedef typename vector< BidirectionalIterator >::iterator  std_iterator;
  std_iterator  stack_iter = S.begin();
  for ( ++stack_iter;  stack_iter != S.end(); ++stack_iter)
  { *result =  **stack_iter;  ++result; }
  return result;
}

template <class InputIterator, class OutputIterator, class Traits>
OutputIterator
CGAL_ch_graham_andrew( InputIterator  first,
                       InputIterator  last,
                       OutputIterator result,
                       const Traits&  ch_traits)
{
  typedef  typename Traits::Less_xy   Less_xy;
  typedef  typename Traits::Point_2   Point_2;
  typedef  typename Traits::Leftturn  Leftturn;

  if (first == last) return result;
  vector< Point_2 >  V;
  copy( first, last, back_inserter(V) );
  sort( V.begin(), V.end(), Less_xy() );
  if ( *(V.begin()) == *(V.rbegin()) )
  {
      *result = *(V.begin());  ++result;
      return result;
  }

  #if defined(CGAL_CH_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
    || defined(NDEBUG)
  OutputIterator  res(result);
  #else
  CGAL_Tee_for_output_iterator<OutputIterator,Point_2> res(result);
  #endif // no postconditions ...
  CGAL_ch__ref_graham_andrew_scan( V.begin(), V.end(),  res, ch_traits);
  CGAL_ch__ref_graham_andrew_scan( V.rbegin(), V.rend(), res, ch_traits);
  CGAL_ch_postcondition( \
      CGAL_is_ccw_strongly_convex_2( res.output_so_far_begin(), \
                                     res.output_so_far_end(), \
                                     ch_traits));
  CGAL_ch_expensive_postcondition( \
      CGAL_ch_brute_force_check_2( \
          V.begin(), V.end(), \
          res.output_so_far_begin(), res.output_so_far_end(), \
          ch_traits));
  #if defined(CGAL_CH_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
    || defined(NDEBUG)
  return res;
  #else
  return res.to_output_iterator();
  #endif // no postconditions ...


}

template <class InputIterator, class OutputIterator, class Traits>
OutputIterator
CGAL_ch_lower_hull_scan( InputIterator  first,
                         InputIterator  last,
                         OutputIterator result,
                         const Traits&  ch_traits)
{
  typedef  typename Traits::Less_xy   Less_xy;
  typedef  typename Traits::Point_2   Point_2;
  typedef  typename Traits::Leftturn  Leftturn;

  if (first == last) return result;
  vector< Point_2 >  V;
  copy( first, last, back_inserter(V) );
  sort( V.begin(), V.end(), Less_xy() );
  if ( *(V.begin()) == *(V.rbegin()) )
  {
      *result = *(V.begin());  ++result;
      return result;
  }

  #if defined(CGAL_CH_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
    || defined(NDEBUG)
  OutputIterator  res(result);
  #else
  CGAL_Tee_for_output_iterator<OutputIterator,Point_2> res(result);
  #endif // no postconditions ...
  CGAL_ch_graham_andrew_scan( V.begin(), V.end(), res, ch_traits);
  #if defined(CGAL_CH_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
    || defined(NDEBUG)
  return res;
  #else
  return res.to_output_iterator();
  #endif // no postconditions ...
}
template <class InputIterator, class OutputIterator, class Traits>
OutputIterator
CGAL_ch_upper_hull_scan( InputIterator  first,
                         InputIterator  last,
                         OutputIterator result,
                         const Traits&  ch_traits)
{
  typedef  typename Traits::Less_xy   Less_xy;
  typedef  typename Traits::Point_2   Point_2;
  typedef  typename Traits::Leftturn  Leftturn;

  if (first == last) return result;
  vector< Point_2 >  V;
  copy( first, last, back_inserter(V) );
  sort( V.begin(), V.end(), Less_xy() );
  if ( *(V.begin()) == *(V.rbegin()) )
  { return result; }
  #if defined(CGAL_CH_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
    || defined(NDEBUG)
  OutputIterator  res(result);
  #else
  CGAL_Tee_for_output_iterator<OutputIterator,Point_2> res(result);
  #endif // no postconditions ...
  CGAL_ch_graham_andrew_scan( V.rbegin(), V.rend(), res, ch_traits);
  #if defined(CGAL_CH_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
    || defined(NDEBUG)
  return res;
  #else
  return res.to_output_iterator();
  #endif // no postconditions ...
}

#endif // CGAL_CH_GRAHAM_ANDREW_C
