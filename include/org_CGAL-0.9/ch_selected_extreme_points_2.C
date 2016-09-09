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

#ifndef CGAL_CH_SELECTED_EXTREME_POINTS_2_C
#define CGAL_CH_SELECTED_EXTREME_POINTS_2_C

#include <CGAL/ch_selected_extreme_points_2.h>

template <class ForwardIterator, class Traits>
void
CGAL_ch_nswe_point( ForwardIterator first, ForwardIterator last,
                    ForwardIterator& n,
                    ForwardIterator& s,
                    ForwardIterator& w,
                    ForwardIterator& e,
                    const Traits& ch_traits)
{
 CGAL_CH_USE_ARGUMENT(ch_traits);
 Traits::Less_xy    lexicographically_xy_smaller;
 Traits::Less_yx    lexicographically_yx_smaller;
 Traits::Greater_xy lexicographically_xy_larger;
 Traits::Greater_yx lexicographically_yx_larger;
 n = s = w = e = first;
 while ( first != last )
 {
    if ( lexicographically_xy_smaller( *first, *w ))  w = first;
    if ( lexicographically_xy_larger ( *first, *e ))  e = first;
    if ( lexicographically_yx_larger ( *first, *n ))  n = first;
    if ( lexicographically_yx_smaller( *first, *s ))  s = first;
    first++;
 }
}

template <class ForwardIterator, class Traits>
void
CGAL_ch_we_point( ForwardIterator first, ForwardIterator last,
                  ForwardIterator& w,
                  ForwardIterator& e,
                  const Traits& ch_traits)
{
 CGAL_CH_USE_ARGUMENT(ch_traits);
 Traits::Less_xy    lexicographically_xy_smaller;
 Traits::Greater_xy lexicographically_xy_larger;
 w = e = first;
 while ( first != last )
 {
    if ( lexicographically_xy_smaller( *first, *w ))  w = first;
    if ( lexicographically_xy_larger ( *first, *e ))  e = first;
    first++;
 }
}

template <class ForwardIterator, class Traits>
void
CGAL_ch_ns_point( ForwardIterator first, ForwardIterator last,
                  ForwardIterator& n,
                  ForwardIterator& s,
                  const Traits& ch_traits)
{
 CGAL_CH_USE_ARGUMENT(ch_traits);
 Traits::Less_yx    lexicographically_yx_smaller;
 Traits::Greater_yx lexicographically_yx_larger;
 n = s = first;
 while ( first != last )
 {
    if ( lexicographically_yx_smaller( *first, *s ))  s = first;
    if ( lexicographically_yx_larger ( *first, *n ))  n = first;
    first++;
 }
}

template <class ForwardIterator, class Traits>
void
CGAL_ch_n_point( ForwardIterator first, ForwardIterator last,
                 ForwardIterator& n,
                 const Traits& ch_traits)
{
 CGAL_CH_USE_ARGUMENT(ch_traits);
 Traits::Greater_yx lexicographically_yx_larger;
 n = first;
 while ( first != last )
 {
    if ( lexicographically_yx_larger ( *first, *n ))  n = first;
    first++;
 }
}

template <class ForwardIterator, class Traits>
void
CGAL_ch_s_point( ForwardIterator first, ForwardIterator last,
                 ForwardIterator& s,
                 const Traits& ch_traits)
{
 CGAL_CH_USE_ARGUMENT(ch_traits);
 Traits::Less_yx    lexicographically_yx_smaller;
 s = first;
 while ( first != last )
 {
    if ( lexicographically_yx_smaller( *first, *s ))  s = first;
    first++;
 }
}

template <class ForwardIterator, class Traits>
void
CGAL_ch_e_point( ForwardIterator first, ForwardIterator last,
                 ForwardIterator& e,
                 const Traits& ch_traits)
{
 CGAL_CH_USE_ARGUMENT(ch_traits);
 Traits::Greater_xy  lexicographically_xy_larger;
 e = first;
 while ( first != last )
 {
    if ( lexicographically_xy_larger( *first, *e ))  e = first;
    first++;
 }
}

template <class ForwardIterator, class Traits>
void
CGAL_ch_w_point( ForwardIterator first, ForwardIterator last,
                 ForwardIterator& w,
                 const Traits& ch_traits)
{
 CGAL_CH_USE_ARGUMENT(ch_traits);
 Traits::Less_xy    lexicographically_xy_smaller;
 w = first;
 while ( first != last )
 {
    if ( lexicographically_xy_smaller( *first, *w ))  w = first;
    first++;
 }
}


#endif // CGAL_CH_SELECTED_EXTREME_POINTS_2_C

