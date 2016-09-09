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
// file          : include/CGAL/ch_bykat.C
// author(s)     : Stefan Schirra 
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


#ifndef CGAL_CH_BYKAT_C
#define CGAL_CH_BYKAT_C

#ifndef CGAL_CH_BYKAT_H
#include <CGAL/ch_eddy.h>
#endif // CGAL_CH_BYKAT_H
template <class InputIterator, class OutputIterator, class Traits>
OutputIterator
CGAL_ch_bykat(InputIterator first, InputIterator last, 
              OutputIterator  result,
              const Traits& ch_traits)
{
  typedef typename Traits::Point_2               Point_2;
  typedef typename Traits::Right_of_line         Right_of_line;
  typedef typename Traits::Less_dist_to_line     Less_dist;

  if (first == last) return result;

  vector< Point_2 >       P;      // Points in subsets
  vector< Point_2 >       H;      // right endpoints of subproblems
  P.reserve(16);
  H.reserve(16);
  
  typedef vector< Point_2 >::iterator   PointIterator;
  vector< PointIterator > L;      // start of subset range
  vector< PointIterator > R;      // end of subset range
  L.reserve(16);
  R.reserve(16);
  PointIterator           l;
  PointIterator           r;
  Point_2                 a,b,c;
  
  copy(first,last,back_inserter(P));
  CGAL_ch_we_point(P.begin(), P.end(), l, r, ch_traits);
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
  CGAL_Tee_for_output_iterator<OutputIterator,Point_2> res(result);
  #endif // no postconditions ...
  H.push_back( a );
  L.push_back( P.begin() );
  R.push_back( l = partition( P.begin(), P.end(), Right_of_line(b,a) ) );
  r = partition( l, P.end(), Right_of_line(a,b) );
  
  for (;;)
  {
      if ( l != r)
      {
          c = *max_element( l, r, Less_dist(a,b) );
          H.push_back( b );
          L.push_back( l );
          R.push_back( l = partition(l, r, Right_of_line(c,b)) );
          r = partition(l, r, Right_of_line(a,c));
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
      CGAL_is_ccw_strongly_convex_2( res.output_so_far_begin(), \
                                     res.output_so_far_end(), \
                                     ch_traits));
  CGAL_ch_expensive_postcondition( \
      CGAL_ch_brute_force_check_2( \
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
CGAL_ch_bykat_with_threshold(InputIterator   first, InputIterator last, 
                             OutputIterator  result,
                             const Traits&   ch_traits)
{
  typedef typename Traits::Point_2               Point_2;
  typedef typename Traits::Right_of_line         Right_of_line;
  typedef typename Traits::Less_dist_to_line     Less_dist;
  typedef typename Traits::Less_xy               Less_xy;
  typedef CGAL_ch_Binary_predicate_reversor< Point_2, Less_xy >
                                                 Greater_xy;
  typedef typename vector< Point_2 >::iterator   PointIterator;

  if (first == last) return result;

  vector< Point_2 >       P;      // points in subsets
  vector< Point_2 >       H;      // right endpoints of subproblems
  P.reserve(16);
  H.reserve(16);
  vector< PointIterator > L;      // start of subset range
  vector< PointIterator > R;      // end of subset range
  L.reserve(16);
  R.reserve(16);
  PointIterator           l;
  PointIterator           r;
  Point_2                 a,b,c;
  PointIterator           Pbegin, Pend;
  
  P.push_back(Point_2() );
  copy(first,last,back_inserter(P));
  P.push_back(Point_2() );
  Pbegin = CGAL_successor(P.begin());
  Pend   = CGAL_predecessor(P.end());
  CGAL_ch_we_point(Pbegin, Pend, l, r, ch_traits);
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
  CGAL_Tee_for_output_iterator<OutputIterator,Point_2> res(result);
  #endif // no postconditions ...
  H.push_back( a );
  L.push_back( Pbegin );
  R.push_back( l = partition( Pbegin, Pend, Right_of_line(b,a) ) );
  r = partition( l, Pend, Right_of_line(a,b) );
  
  for (;;)
  {
      if ( l != r)
      {
          if ( r-l > CGAL_ch_THRESHOLD )
          {
              c = *max_element( l, r, Less_dist(a,b) );
              H.push_back( b );
              L.push_back( l );
              R.push_back( l = partition(l, r, Right_of_line(c,b)) );
              r = partition(l, r, Right_of_line(a,c));
              b = c; 
          }
          else
          {
              swap( a, *--l);
              swap( b, *++r);
              if ( Less_xy()(*l,*r) )
              {
                  sort(CGAL_successor(l), r, Less_xy() );
              }
              else
              {
                  sort(CGAL_successor(l), r, Greater_xy() );
              }
              CGAL_ch__ref_graham_andrew_scan(l, CGAL_successor(r), 
                                              res, ch_traits);
              swap( a, *l);
              swap( b, *r);
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
      CGAL_is_ccw_strongly_convex_2( res.output_so_far_begin(), \
                                     res.output_so_far_end(), \
                                     ch_traits));
  CGAL_ch_expensive_postcondition( \
      CGAL_ch_brute_force_check_2( \
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


#endif // CGAL_CH_BYKAT_C


