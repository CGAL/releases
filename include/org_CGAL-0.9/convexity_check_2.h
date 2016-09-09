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

#ifndef CGAL_CONVEXITY_CHECK_2_H
#define CGAL_CONVEXITY_CHECK_2_H

#include <CGAL/ch_assertions.h>
#include <CGAL/ch_utils.h>
#ifdef CGAL_REP_CLASS_DEFINED
#include <CGAL/convex_hull_traits_2.h>
#ifdef __GNUG__
#include <CGAL/gnu_istream_iterator_value_type_fix.h>
#endif // __GNUG__
#endif // CGAL_REP_CLASS_DEFINED
#ifndef CGAL_CH_NO_POSTCONDITIONS
#include <CGAL/convexity_check_2.h>

#endif // CGAL_CH_NO_POSTCONDITIONS


/*{\Moptions
outfile=cgal_ch_I_cc.man
}*/

/*{\Mtext 
\settowidth{\typewidth}{|OutputIterator|}
\addtolength{\typewidth}{\colsep}
\settowidth{\callwidth}{|CGAL_ch_|}
\computewidths
}*/

/*{\Mtext [[\#include <CGAL/convexity_check_2.h>]]
}*/

template <class ForwardIterator, class Traits>
bool
CGAL_is_ccw_strongly_convex_2( ForwardIterator first, ForwardIterator last, 
                               const Traits& ch_traits);
/*{\Mfunc returns true, if the point elements in [|first|,|last|) form a 
counterclockwise oriented strongly convex polygon.\\ 
{\sc traits}: uses |Traits::leftturn()| and |Traits::Less_xy|.
}*/

template <class ForwardIterator, class Traits>
bool
CGAL_is_cw_strongly_convex_2( ForwardIterator first, ForwardIterator last, 
                              const Traits& ch_traits);
/*{\Mfunc returns true, if the point elements in [|first|,|last|) form a 
clockwise oriented strongly convex polygon.\\ 
{\sc traits}: uses |Traits::rightturn()| and |Traits::Less_xy|.
}*/


/*{\Moptions
outfile=cgal_ch_I_cc.man
}*/

template <class ForwardIterator1, class ForwardIterator2, class Traits>
bool
CGAL_ch_brute_force_check_2(ForwardIterator1 first1, ForwardIterator1 last1,
                            ForwardIterator2 first2, ForwardIterator2 last2,
                            const Traits& ch_traits);
/*{\Mfunc returns true, if all points in [|first1|,|last1|) are 
not right of the lines defined by consecutive points in the range 
[|first2|,|last2|), where the range is considered as a cycle.\\
{\sc traits}: uses |Traits::Right_of_line|.
}*/


/*{\Moptions
outfile=cgal_ch_I_cc.man
}*/

template <class ForwardIterator1, class ForwardIterator2, class Traits>
bool
CGAL_ch_brute_force_chain_check_2(ForwardIterator1 first1, 
                                  ForwardIterator1 last1,
                                  ForwardIterator2 first2, 
                                  ForwardIterator2 last2,
                                  const Traits& ch_traits);
/*{\Mfunc returns true, if all points in [|first1|,|last1|) are 
not right of the lines defined by consecutive points in the range 
[|first2|,|last2|).\\ 
{\sc traits}: uses |Traits::Right_of_line|.
}*/

#ifdef CGAL_POINT_2_H
/*{\Moptions
outfile=cgal_ch_cc.man
}*/

/*{\Mtext
\settowidth{\typewidth}{|OutputIterator|}
\addtolength{\typewidth}{\colsep}
\settowidth{\callwidth}{|CGAL_ch_|}
\computewidths
}*/

template <class ForwardIterator, class R>
inline
bool
CGAL__is_cw_convex_2( ForwardIterator first, ForwardIterator last, 
                      CGAL_Point_2<R>* )
{
  return CGAL_is_cw_strongly_convex_2( first, last, 
                                       CGAL_convex_hull_traits_2<R>() );
}

template <class ForwardIterator>
inline
bool
CGAL_is_cw_strongly_convex_2( ForwardIterator first, ForwardIterator last )
{
  return CGAL__is_cw_convex_2( first, last, value_type(first) );
}
/*{\Mfunc returns true, if the point elements in [|first|,|last|) form a 
clockwise oriented strongly convex polygon. Strongly means, there are
no three collinear points.}*/

template <class ForwardIterator, class R>
inline
bool
CGAL__is_ccw_convex_2( ForwardIterator first, ForwardIterator last, 
                       CGAL_Point_2<R>* )
{
  return CGAL_is_ccw_strongly_convex_2( first, last, 
                                        CGAL_convex_hull_traits_2<R>() );
}

template <class ForwardIterator>
inline
bool
CGAL_is_ccw_strongly_convex_2( ForwardIterator first, ForwardIterator last )
{
  return CGAL__is_ccw_convex_2( first, last, value_type(first) );
}
/*{\Mfunc returns true, if the point elements in [|first|,|last|) form a 
counterclockwise oriented strongly convex polygon. Strongly means, there are
no three collinear points.}*/


/*{\Moptions
outfile=cgal_ch_cc.man
}*/

template <class ForwardIterator1, class ForwardIterator2, class R>
inline
bool
CCGAL_ch__brute_force_check_2(ForwardIterator1 first1,ForwardIterator1 last1,
                              ForwardIterator2 first2,ForwardIterator2 last2,
                              CGAL_Point_2<R>* )
{
  return CGAL_ch_brute_force_check_2( first1, last1, 
                                      first2, last2,
                                      CGAL_convex_hull_traits_2<R>() );
}

template <class ForwardIterator1, class ForwardIterator2>
inline
bool
CGAL_ch_brute_force_check_2(ForwardIterator1 first1, ForwardIterator1 last1,
                            ForwardIterator2 first2, ForwardIterator2 last2)
{
  return CCGAL_ch__brute_force_check_2( first1, last1, 
                                        first2, last2,
                                        value_type(first1) );
}


/*{\Moptions
outfile=cgal_ch_cc.man
}*/

template <class ForwardIterator1, class ForwardIterator2, class R>
inline
bool
CCGAL_ch__brute_force_chain_check_2(ForwardIterator1 first1,
                                    ForwardIterator1 last1,
                                    ForwardIterator2 first2,
                                    ForwardIterator2 last2,
                                    CGAL_Point_2<R>* )
{
  return CGAL_ch_brute_force_chain_check_2( first1, last1, 
                                            first2, last2,
                                            CGAL_convex_hull_traits_2<R>() );
}

template <class ForwardIterator1, class ForwardIterator2>
inline
bool
CGAL_ch_brute_force_chain_check_2(ForwardIterator1 first1, 
                                  ForwardIterator1 last1,
                                  ForwardIterator2 first2, 
                                  ForwardIterator2 last2)
{
  return CCGAL_ch__brute_force_chain_check_2( first1, last1, 
                                              first2, last2,
                                              value_type(first1) );
}

#endif // CGAL_POINT_2_H

#ifdef CGAL_INCLUDE_TEMPLATE_CODE
#include <CGAL/convexity_check_2.C>
#endif // CGAL_INCLUDE_TEMPLATE_CODE

#endif // CGAL_CONVEXITY_CHECK_2_H

