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
// file          : include/CGAL/convexity_check_2.h
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


#ifndef CGAL_CONVEXITY_CHECK_2_H
#define CGAL_CONVEXITY_CHECK_2_H

#include <CGAL/stl_extensions.h>
#include <algo.h>
#include <CGAL/ch_utils.h>
#ifdef CGAL_REP_CLASS_DEFINED
#include <CGAL/convex_hull_traits_2.h>
#ifdef CGAL_STL_GCC
#ifndef CGAL_GNU_ISTREAM_ITERATOR_VALUE_TYPE_FIX_H
#include <CGAL/gnu_istream_iterator_value_type_fix.h>
#endif // CGAL_GNU_ISTREAM_ITERATOR_VALUE_TYPE_FIX_H
#endif // CGAL_STL_GCC
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
{\sc traits}: uses |Traits::Leftturn| and |Traits::Less_xy|.
}*/

template <class ForwardIterator, class Traits>
bool
CGAL_is_cw_strongly_convex_2( ForwardIterator first, ForwardIterator last, 
                              const Traits& ch_traits);
/*{\Mfunc returns true, if the point elements in [|first|,|last|) form a 
clockwise oriented strongly convex polygon.\\ 
{\sc traits}: uses |Traits::Rightturn| and |Traits::Less_xy|.
}*/


/*{\Moptions
outfile=cgal_ch_I_cc2.man
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
outfile=cgal_ch_I_cc3.man
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
{ return CGAL__is_cw_convex_2( first, last, value_type(first) ); }
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
{ return CGAL__is_ccw_convex_2( first, last, value_type(first) ); }
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

#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#include <CGAL/convexity_check_2.C>
#endif // CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION

#endif // CGAL_CONVEXITY_CHECK_2_H

