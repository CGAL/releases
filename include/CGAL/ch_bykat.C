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
// file          : include/CGAL/ch_bykat.C
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


#ifndef CGAL_CH_BYKAT_C
#define CGAL_CH_BYKAT_C

#ifndef CGAL_CH_BYKAT_H
#include <CGAL/ch_eddy.h>
#endif // CGAL_CH_BYKAT_H

CGAL_BEGIN_NAMESPACE
template <class InputIterator, class OutputIterator, class Traits>
OutputIterator
ch_bykat(InputIterator first, InputIterator last, 
              OutputIterator  result,
              const Traits& ch_traits)
{
  typedef typename Traits::Point_2               Point_2;
  typedef typename Traits::Right_of_line         Right_of_line;
  typedef typename Traits::Less_dist_to_line     Less_dist;

  if (first == last) return result;

  std::vector< Point_2 >       P;      // Points in subsets
  std::vector< Point_2 >       H;      // right endpoints of subproblems
  P.reserve(16);
  H.reserve(16);
  
  typedef typename std::vector< Point_2 >::iterator   PointIterator;
  std::vector< PointIterator > L;      // start of subset range
  std::vector< PointIterator > R;      // end of subset range
  L.reserve(16);
  R.reserve(16);
  PointIterator           l;
  PointIterator           r;
  Point_2                 a,b,c;
  
  std::copy(first,last,std::back_inserter(P));
  ch_we_point(P.begin(), P.end(), l, r, ch_traits);
  a = *l;
  b = *r;
  if ( a == b) 
  {
      *result = a;  ++result;
      return result;
  }
  #if defined(CGAL_CH_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
    || defined(NDEBUG)
  OutputIterator  res(result);
  #else
  Tee_for_output_iterator<OutputIterator,Point_2> res(result);
  #endif // no postconditions ...
  H.push_back( a );
  L.push_back( P.begin() );
  R.push_back( l = std::partition( P.begin(), P.end(), 
                                   ch_traits.get_right_of_line_object(b,a) ) );
  r = std::partition( l, P.end(), ch_traits.get_right_of_line_object(a,b) );
  
  for (;;)
  {
      if ( l != r)
      {
          c = *std::max_element( l, r, ch_traits.get_less_dist_to_line_object(a,b) );
          H.push_back( b );
          L.push_back( l );
          R.push_back( l = std::partition(l, r, ch_traits.get_right_of_line_object(c,b)));
          r = std::partition(l, r, ch_traits.get_right_of_line_object(a,c));
          b = c; 
      }
      else
      {
          *res = a;  ++res;
          if ( L.empty() ) break;
          a = b;
          b = H.back(); H.pop_back();
          l = L.back(); L.pop_back();
          r = R.back(); R.pop_back();
      }
  }
  CGAL_ch_postcondition( \
      is_ccw_strongly_convex_2( res.output_so_far_begin(), \
                                     res.output_so_far_end(), \
                                     ch_traits));
  CGAL_ch_expensive_postcondition( \
      ch_brute_force_check_2( \
          P.begin(), P.end(), \
          res.output_so_far_begin(), res.output_so_far_end(), \
          ch_traits));
  #if defined(CGAL_CH_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
    || defined(NDEBUG)
  return res;
  #else
  return res.to_output_iterator();
  #endif // no postconditions ...
}

#define CGAL_ch_THRESHOLD 10
template <class InputIterator, class OutputIterator, class Traits>
OutputIterator
ch_bykat_with_threshold(InputIterator   first, InputIterator last, 
                             OutputIterator  result,
                             const Traits&   ch_traits)
{
  typedef typename Traits::Point_2               Point_2;
  typedef typename Traits::Right_of_line         Right_of_line;
  typedef typename Traits::Less_dist_to_line     Less_dist;
  typedef typename Traits::Less_xy               Less_xy;
  typedef ch_Binary_predicate_reversor< Point_2, Less_xy >
                                                 Greater_xy;
  typedef typename std::vector< Point_2 >::iterator   PointIterator;

  if (first == last) return result;

  std::vector< Point_2 >       P;      // points in subsets
  std::vector< Point_2 >       H;      // right endpoints of subproblems
  P.reserve(16);
  H.reserve(16);
  std::vector< PointIterator > L;      // start of subset range
  std::vector< PointIterator > R;      // end of subset range
  L.reserve(16);
  R.reserve(16);
  PointIterator           l;
  PointIterator           r;
  Point_2                 a,b,c;
  PointIterator           Pbegin, Pend;
  
  P.push_back(Point_2() );
  std::copy(first,last,std::back_inserter(P));
  P.push_back(Point_2() );
  Pbegin = successor(P.begin());
  Pend   = predecessor(P.end());
  ch_we_point(Pbegin, Pend, l, r, ch_traits);
  a = *l;
  b = *r;
  if ( a == b) 
  {
      *result = a;  ++result;
      return result;
  }
  #if defined(CGAL_CH_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
    || defined(NDEBUG)
  OutputIterator  res(result);
  #else
  Tee_for_output_iterator<OutputIterator,Point_2> res(result);
  #endif // no postconditions ...
  H.push_back( a );
  L.push_back( Pbegin );
  R.push_back( l = std::partition( Pbegin, Pend, ch_traits.get_right_of_line_object(b,a) ) );
  r = std::partition( l, Pend, ch_traits.get_right_of_line_object(a,b) );
  
  for (;;)
  {
      if ( l != r)
      {
          if ( r-l > CGAL_ch_THRESHOLD )
          {
              c = *std::max_element( l, r, ch_traits.get_less_dist_to_line_object(a,b) );
              H.push_back( b );
              L.push_back( l );
              R.push_back( l = std::partition(l, r, ch_traits.get_right_of_line_object(c,b)) );
              r = std::partition(l, r, ch_traits.get_right_of_line_object(a,c));
              b = c; 
          }
          else
          {
              std::swap( a, *--l);
              std::swap( b, *++r);
              if ( ch_traits.get_less_xy_object()(*l,*r) )
              {
                  std::sort(successor(l), r, 
                            ch_traits.get_less_xy_object() );
              }
              else
              {
                  std::sort(successor(l), r, 
                            Greater_xy(ch_traits.get_less_xy_object()) );
              }
              ch__ref_graham_andrew_scan(l, successor(r), res, ch_traits);
              std::swap( a, *l);
              std::swap( b, *r);
              if ( L.empty() ) break;
              a = b;
              b = H.back(); H.pop_back();
              l = L.back(); L.pop_back();
              r = R.back(); R.pop_back();
          }
              
      }
      else
      {
          *res = a;  ++res;
          if ( L.empty() ) break;
          a = b;
          b = H.back(); H.pop_back();
          l = L.back(); L.pop_back();
          r = R.back(); R.pop_back();
      }
  }
  CGAL_ch_postcondition( \
      is_ccw_strongly_convex_2( res.output_so_far_begin(), \
                                     res.output_so_far_end(), \
                                     ch_traits));
  CGAL_ch_expensive_postcondition( \
      ch_brute_force_check_2( \
          Pbegin, Pend, \
          res.output_so_far_begin(), res.output_so_far_end(), \
          ch_traits));
  #if defined(CGAL_CH_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
    || defined(NDEBUG)
  return res;
  #else
  return res.to_output_iterator();
  #endif // no postconditions ...
}

CGAL_END_NAMESPACE

#endif // CGAL_CH_BYKAT_C


