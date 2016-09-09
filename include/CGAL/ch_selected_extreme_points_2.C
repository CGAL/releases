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
// file          : include/CGAL/ch_selected_extreme_points_2.C
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


#ifndef CGAL_CH_SELECTED_EXTREME_POINTS_2_C
#define CGAL_CH_SELECTED_EXTREME_POINTS_2_C

#ifndef CGAL_CH_SELECTED_EXTREME_POINTS_2_H
#include <CGAL/ch_selected_extreme_points_2.h>
#endif // CGAL_CH_SELECTED_EXTREME_POINTS_2_H
template <class ForwardIterator, class Traits>
void
CGAL_ch_nswe_point( ForwardIterator first, ForwardIterator last,
                    ForwardIterator& n,
                    ForwardIterator& s,
                    ForwardIterator& w,
                    ForwardIterator& e,
                    const Traits& )
{
  typename Traits::Less_xy    lexicographically_xy_smaller;
  typename Traits::Less_yx    lexicographically_yx_smaller;
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
CGAL_ch_we_point( ForwardIterator first, ForwardIterator last,
                  ForwardIterator& w,
                  ForwardIterator& e,
                  const Traits& ch_traits)
{
 typename Traits::Less_xy    lexicographically_xy_smaller;
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
CGAL_ch_ns_point( ForwardIterator first, ForwardIterator last,
                  ForwardIterator& n,
                  ForwardIterator& s,
                  const Traits& )
{
 typename Traits::Less_yx    lexicographically_yx_smaller;
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
CGAL_ch_n_point( ForwardIterator first, ForwardIterator last,
                 ForwardIterator& n,
                 const Traits& )
{
 typename Traits::Less_yx lexicographically_yx_smaller;
 n = first;
 while ( first != last )
 {
    if ( lexicographically_yx_smaller ( *n, *first ))  n = first;
    ++first;
 }
}

template <class ForwardIterator, class Traits>
void
CGAL_ch_s_point( ForwardIterator first, ForwardIterator last,
                 ForwardIterator& s,
                 const Traits& )
{
 typename Traits::Less_yx    lexicographically_yx_smaller;
 s = first;
 while ( first != last )
 {
    if ( lexicographically_yx_smaller( *first, *s ))  s = first;
    ++first;
 }
}

template <class ForwardIterator, class Traits>
void
CGAL_ch_e_point( ForwardIterator first, ForwardIterator last,
                 ForwardIterator& e,
                 const Traits& )
{
 typename Traits::Less_xy  lexicographically_xy_smaller;
 e = first;
 while ( first != last )
 {
    if ( lexicographically_xy_smaller( *e, *first ))  e = first;
    ++first;
 }
}

template <class ForwardIterator, class Traits>
void
CGAL_ch_w_point( ForwardIterator first, ForwardIterator last,
                 ForwardIterator& w,
                 const Traits& )
{
 typename Traits::Less_xy    lexicographically_xy_smaller;
 w = first;
 while ( first != last )
 {
    if ( lexicographically_xy_smaller( *first, *w ))  w = first;
    ++first;
 }
}

#endif // CGAL_CH_SELECTED_EXTREME_POINTS_2_C

