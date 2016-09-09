// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : include/CGAL/ch_graham_andrew.C
// package       : Convex_hull (2.2.19)
// source        : convex_hull_2.lw
// revision      : 2.2.19
// revision_date : 03 Dec 1999
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_CH_GRAHAM_ANDREW_C
#define CGAL_CH_GRAHAM_ANDREW_C

#include <CGAL/stl_extensions.h>
#ifndef CGAL_CH_GRAHAM_ANDREW_H
#include <CGAL/ch_graham_andrew.h>
#endif // CGAL_CH_GRAHAM_ANDREW_H

CGAL_BEGIN_NAMESPACE

template <class BidirectionalIterator, class OutputIterator, class Traits>
OutputIterator
ch_graham_andrew_scan( BidirectionalIterator first,
                       BidirectionalIterator last,
                       OutputIterator        result,
                       const Traits&         ch_traits)
{
  typedef  typename Traits::Less_xy   Less_xy;
  typedef  typename Traits::Point_2   Point_2;
  typedef  typename Traits::Leftturn  Leftturn;

  std::vector< BidirectionalIterator >    S;
  BidirectionalIterator              alpha;
  BidirectionalIterator              beta;
  BidirectionalIterator              iter;
  CGAL_ch_precondition( first != last );
  CGAL_ch_precondition( successor(first) != last );

  --last;
  CGAL_ch_precondition( *first != *last );
  S.push_back( last  );
  S.push_back( first );
  Leftturn    leftturn = ch_traits.get_leftturn_object();


  iter = first;
  do
  {
      ++iter;
  }
  while (( iter != last ) && !leftturn(*last, *first, *iter) );

  if ( iter != last )
  {
      S.push_back( iter );
      typedef typename std::vector<BidirectionalIterator>::reverse_iterator  
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

  typedef typename std::vector< BidirectionalIterator >::iterator  std_iterator;
  std_iterator  stack_iter = S.begin();
  #if defined(CGAL_CH_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
    || defined(NDEBUG)
  OutputIterator  res(result);
  #else
  Tee_for_output_iterator<OutputIterator,Point_2> res(result);
  #endif // no postconditions ...
  for ( ++stack_iter;  stack_iter != S.end(); ++stack_iter)
  { *res =  **stack_iter;  ++res; }
  CGAL_ch_postcondition( \
      is_ccw_strongly_convex_2( res.output_so_far_begin(), \
                                     res.output_so_far_end(), \
                                     ch_traits));
  CGAL_ch_expensive_postcondition( \
      ch_brute_force_chain_check_2( \
          first, last, \
          res.output_so_far_begin(), res.output_so_far_end(), \
          ch_traits));
  #if defined(CGAL_CH_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
    || defined(NDEBUG)
  return res;
  #else
  return res.to_output_iterator();
  #endif // no postconditions ...
}

template <class BidirectionalIterator, class OutputIterator, class Traits>
OutputIterator
ch__ref_graham_andrew_scan( BidirectionalIterator first,
                                 BidirectionalIterator last,
                                 OutputIterator&       result,
                                 const Traits&         ch_traits)
{
  typedef  typename Traits::Less_xy   Less_xy;
  typedef  typename Traits::Point_2   Point_2;
  typedef  typename Traits::Leftturn  Leftturn;

  std::vector< BidirectionalIterator >    S;
  BidirectionalIterator              alpha;
  BidirectionalIterator              beta;
  BidirectionalIterator              iter;
  CGAL_ch_precondition( first != last );
  CGAL_ch_precondition( successor(first) != last );

  --last;
  CGAL_ch_precondition( *first != *last );
  S.push_back( last  );
  S.push_back( first );
  Leftturn    leftturn = ch_traits.get_leftturn_object();


  iter = first;
  do
  {
      ++iter;
  }
  while (( iter != last ) && !leftturn(*last, *first, *iter) );

  if ( iter != last )
  {
      S.push_back( iter );
      typedef typename std::vector<BidirectionalIterator>::reverse_iterator  
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

  typedef typename std::vector< BidirectionalIterator >::iterator  std_iterator;
  std_iterator  stack_iter = S.begin();
  for ( ++stack_iter;  stack_iter != S.end(); ++stack_iter)
  { *result =  **stack_iter;  ++result; }
  return result;
}

template <class InputIterator, class OutputIterator, class Traits>
OutputIterator
ch_graham_andrew( InputIterator  first,
                       InputIterator  last,
                       OutputIterator result,
                       const Traits&  ch_traits)
{
  typedef  typename Traits::Less_xy   Less_xy;
  typedef  typename Traits::Point_2   Point_2;
  typedef  typename Traits::Leftturn  Leftturn;

  if (first == last) return result;
  std::vector< Point_2 >  V;
  std::copy( first, last, std::back_inserter(V) );
  std::sort( V.begin(), V.end(), ch_traits.get_less_xy_object() );
  if ( *(V.begin()) == *(V.rbegin()) )
  {
      *result = *(V.begin());  ++result;
      return result;
  }

  #if defined(CGAL_CH_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
    || defined(NDEBUG)
  OutputIterator  res(result);
  #else
  Tee_for_output_iterator<OutputIterator,Point_2> res(result);
  #endif // no postconditions ...
  ch__ref_graham_andrew_scan( V.begin(), V.end(),  res, ch_traits);
  ch__ref_graham_andrew_scan( V.rbegin(), V.rend(), res, ch_traits);
  CGAL_ch_postcondition( \
      is_ccw_strongly_convex_2( res.output_so_far_begin(), \
                                     res.output_so_far_end(), \
                                     ch_traits));
  CGAL_ch_expensive_postcondition( \
      ch_brute_force_check_2( \
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
ch_lower_hull_scan( InputIterator  first,
                         InputIterator  last,
                         OutputIterator result,
                         const Traits&  ch_traits)
{
  typedef  typename Traits::Less_xy   Less_xy;
  typedef  typename Traits::Point_2   Point_2;
  typedef  typename Traits::Leftturn  Leftturn;

  if (first == last) return result;
  std::vector< Point_2 >  V;
  std::copy( first, last, std::back_inserter(V) );
  std::sort( V.begin(), V.end(), ch_traits.get_less_xy_object() );
  if ( *(V.begin()) == *(V.rbegin()) )
  {
      *result = *(V.begin());  ++result;
      return result;
  }

  #if defined(CGAL_CH_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
    || defined(NDEBUG)
  OutputIterator  res(result);
  #else
  Tee_for_output_iterator<OutputIterator,Point_2> res(result);
  #endif // no postconditions ...
  ch_graham_andrew_scan( V.begin(), V.end(), res, ch_traits);
  #if defined(CGAL_CH_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
    || defined(NDEBUG)
  return res;
  #else
  return res.to_output_iterator();
  #endif // no postconditions ...
}
template <class InputIterator, class OutputIterator, class Traits>
OutputIterator
ch_upper_hull_scan( InputIterator  first,
                         InputIterator  last,
                         OutputIterator result,
                         const Traits&  ch_traits)
{
  typedef  typename Traits::Less_xy   Less_xy;
  typedef  typename Traits::Point_2   Point_2;
  typedef  typename Traits::Leftturn  Leftturn;

  if (first == last) return result;
  std::vector< Point_2 >  V;
  std::copy( first, last, std::back_inserter(V) );
  std::sort( V.begin(), V.end(), ch_traits.get_less_xy_object() );
  if ( *(V.begin()) == *(V.rbegin()) )
  { return result; }
  #if defined(CGAL_CH_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
    || defined(NDEBUG)
  OutputIterator  res(result);
  #else
  Tee_for_output_iterator<OutputIterator,Point_2> res(result);
  #endif // no postconditions ...
  ch_graham_andrew_scan( V.rbegin(), V.rend(), res, ch_traits);
  #if defined(CGAL_CH_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
    || defined(NDEBUG)
  return res;
  #else
  return res.to_output_iterator();
  #endif // no postconditions ...
}
CGAL_END_NAMESPACE

#endif // CGAL_CH_GRAHAM_ANDREW_C
