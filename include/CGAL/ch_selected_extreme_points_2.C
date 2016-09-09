// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/ch_selected_extreme_points_2.C
// package       : Convex_hull_2 (3.34)
// source        : convex_hull_2.lw
// revision      : 3.3
// revision_date : 03 Aug 2000
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================


#ifndef CGAL_CH_SELECTED_EXTREME_POINTS_2_C
#define CGAL_CH_SELECTED_EXTREME_POINTS_2_C

#ifndef CGAL_CH_SELECTED_EXTREME_POINTS_2_H
#include <CGAL/ch_selected_extreme_points_2.h>
#endif // CGAL_CH_SELECTED_EXTREME_POINTS_2_H

#ifndef CH_NO_POSTCONDITIONS
#include <CGAL/convexity_check_2.h>
#endif // CH_NO_POSTCONDITIONS

CGAL_BEGIN_NAMESPACE
template <class ForwardIterator, class Traits>
void
ch_nswe_point( ForwardIterator first, ForwardIterator last,
                    ForwardIterator& n,
                    ForwardIterator& s,
                    ForwardIterator& w,
                    ForwardIterator& e,
                    const Traits& ch_traits )
{
  typename Traits::Less_xy_2    
      lexicographically_xy_smaller = ch_traits.less_xy_2_object();
  typename Traits::Less_yx_2    
      lexicographically_yx_smaller = ch_traits.less_yx_2_object();
  n = s = w = e = first;
  while ( first != last )
  {
      if ( lexicographically_xy_smaller( *first, *w ))  w = first;
      if ( lexicographically_xy_smaller( *e, *first ))  e = first;
      if ( lexicographically_yx_smaller( *n, *first ))  n = first;
      if ( lexicographically_yx_smaller( *first, *s ))  s = first;
      ++first;
  }
}


template <class ForwardIterator, class Traits>
void
ch_we_point( ForwardIterator first, ForwardIterator last,
                  ForwardIterator& w,
                  ForwardIterator& e,
                  const Traits& ch_traits)
{
 typename Traits::Less_xy_2    
    lexicographically_xy_smaller = ch_traits.less_xy_2_object();
 w = e = first;
 while ( first != last )
 {
    if ( lexicographically_xy_smaller( *first, *w ))  w = first;
    if ( lexicographically_xy_smaller( *e, *first ))  e = first;
    ++first;
 }
}

template <class ForwardIterator, class Traits>
void
ch_ns_point( ForwardIterator first, ForwardIterator last,
                  ForwardIterator& n,
                  ForwardIterator& s,
                  const Traits& ch_traits)
{
 typename Traits::Less_yx_2    
    lexicographically_yx_smaller = ch_traits.less_yx_2_object();
 n = s = first;
 while ( first != last )
 {
    if ( lexicographically_yx_smaller( *first, *s ))  s = first;
    if ( lexicographically_yx_smaller( *n, *first ))  n = first;
    ++first;
 }
}

template <class ForwardIterator, class Traits>
void
ch_n_point( ForwardIterator first, ForwardIterator last,
                 ForwardIterator& n,
                 const Traits& ch_traits)
{
 typename Traits::Less_yx_2    
    lexicographically_yx_smaller = ch_traits.less_yx_2_object();
 n = first;
 while ( first != last )
 {
    if ( lexicographically_yx_smaller ( *n, *first ))  n = first;
    ++first;
 }
}

template <class ForwardIterator, class Traits>
void
ch_s_point( ForwardIterator first, ForwardIterator last,
                 ForwardIterator& s,
                 const Traits& ch_traits)
{
 typename Traits::Less_yx_2    
    lexicographically_yx_smaller = ch_traits.less_yx_2_object();
 s = first;
 while ( first != last )
 {
    if ( lexicographically_yx_smaller( *first, *s ))  s = first;
    ++first;
 }
}

template <class ForwardIterator, class Traits>
void
ch_e_point( ForwardIterator first, ForwardIterator last,
                 ForwardIterator& e,
                 const Traits& ch_traits)
{
 typename Traits::Less_xy_2    
    lexicographically_xy_smaller = ch_traits.less_xy_2_object();
 e = first;
 while ( first != last )
 {
    if ( lexicographically_xy_smaller( *e, *first ))  e = first;
    ++first;
 }
}

template <class ForwardIterator, class Traits>
void
ch_w_point( ForwardIterator first, ForwardIterator last,
                 ForwardIterator& w,
                 const Traits& ch_traits)
{
 typename Traits::Less_xy_2    
    lexicographically_xy_smaller = ch_traits.less_xy_2_object();
 w = first;
 while ( first != last )
 {
    if ( lexicographically_xy_smaller( *first, *w ))  w = first;
    ++first;
 }
}
CGAL_END_NAMESPACE

#endif // CGAL_CH_SELECTED_EXTREME_POINTS_2_C

