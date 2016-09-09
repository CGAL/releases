
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
// 
// release       : CGAL-2.2
// release_date  : 2000, September 30
// 
// source        : melkman.fw
// file          : include/CGAL/ch_melkman.C
// package       : Convex_hull (3.3)
// revision      : 3.3
// revision_date : 03 Aug 2000 
// author(s)     : Stefan Schirra
//
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_CH_MELKMAN_C
#define CGAL_CH_MELKMAN_C


#include <queue>
#include <CGAL/ch_utils.h>
#ifndef CH_NO_POSTCONDITIONS
#include <CGAL/convexity_check_2.h>
#endif // CH_NO_POSTCONDITIONS


CGAL_BEGIN_NAMESPACE

template <class InputIterator, class OutputIterator, class Traits>
OutputIterator
ch_melkman( InputIterator first, InputIterator last,
            OutputIterator result, const Traits& ch_traits);


template <class ForwardIterator, class OutputIterator, class R>
inline
OutputIterator
_ch_melkman(ForwardIterator first, ForwardIterator last,
            OutputIterator  result, Point_2<R>* )
{ return ch_melkman(first, last, result, R() ); }


template <class InputIterator, class OutputIterator>
OutputIterator
ch_melkman( InputIterator first, InputIterator last,  OutputIterator result)
{ return _ch_melkman( first, last, result, ch_value_type(first) ); }


template <class InputIterator, class OutputIterator, class Traits>
OutputIterator
ch_melkman( InputIterator first, InputIterator last,
            OutputIterator result, const Traits& ch_traits)
{
  typedef typename Traits::Point_2      Point;
  typedef typename Traits::Segment_2    Segment;
  typename Traits::Leftturn_2 leftturn  = ch_traits.leftturn_2_object();
  CGAL_ch_assertion_code( \
  typename Traits::Less_xy_2 less       = ch_traits.less_xy_2_object(); )
  
  std::deque< Point> Q;
  
  CGAL_ch_expensive_postcondition_code( std::deque< Point> IN; )
  if (first == last) return result;           // 0 elements
  Point p = *first;
  CGAL_ch_expensive_postcondition_code( IN.push_back(p); )
  if (++first == last)
  { *result = p; ++result; return result; }   // 1 element
  Point q = *first;
  CGAL_ch_expensive_postcondition_code( IN.push_back(q); )
  if (++first == last)                        // 2 elements
  {
    *result = p; ++result;
    if ( p != q)
    { *result = q; ++result; }
    return result;
  }
  Q.push_back( p);
  
  Point r;
  while (first != last)
  {
    r = *first;
    CGAL_ch_expensive_postcondition_code( IN.push_back(r); )
    // visited input sequence =  p,..., q, r
    if ( leftturn(p,q,r)) { Q.push_back( q);  break; }
    if ( leftturn(q,p,r)) { Q.push_front( q); break; }
    CGAL_ch_assertion( less( p, q) ? less (p, r) : less( r, p));
    q = r;
    ++first;
  }
  
  
  Point current = q;
  if (first != last)           // non-collinear point r exists
  {
    
    current = r;
    // current, Q.front(), ..., Q.back()
    // ccw convex hull of visited points
    Point s;
    while ( ++first != last)
    {
      r = *first;
      CGAL_ch_expensive_postcondition_code( IN.push_back(r); )
      if (leftturn( current, r, Q.front()) || leftturn( Q.back(), r, current))
      // r outside cone Q.front(), current, Q.back() <=>
      // rightturn( current, Q.front(), r) || rightturn( Q.back(), current, r)
      {
        s = current;
        while ( !leftturn( r, s, Q.front()))
        //      !leftturn( r, s, Q.front())
        { s = Q.front(); Q.pop_front(); }
        Q.push_front(s);
        s = current;
        while ( !leftturn( s, r, Q.back()))
        //     !rightturn( r, s, Q.back())
        { s = Q.back(); Q.pop_back(); }
        Q.push_back(s);
        current = r;
      }
      
    }
    
  }
  
  
  Q.push_back( current);       // add last point to Q
  CGAL_ch_postcondition( \
  is_ccw_strongly_convex_2( Q.begin(), Q.end(), ch_traits));
  CGAL_ch_expensive_postcondition( \
  ch_brute_force_check_2( IN.begin(),IN.end(), Q.begin(),Q.end(), ch_traits));
  std::copy( Q.begin(), Q.end(), result);
  return result;
  
}

CGAL_END_NAMESPACE


#endif // CGAL_CH_MELKMAN_C
