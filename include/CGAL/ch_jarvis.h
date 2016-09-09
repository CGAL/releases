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
// file          : include/CGAL/ch_jarvis.h
// author(s)     : Stefan Schirra 
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


#ifndef CGAL_CH_JARVIS_H
#define CGAL_CH_JARVIS_H

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


#include <algo.h>
/*{\Moptions
outfile=cgal_ch_I_jm.man
}*/

/*{\Mtext 
\settowidth{\typewidth}{|OutputIterator|}
\addtolength{\typewidth}{\colsep}
\settowidth{\callwidth}{|CGAL_ch_|}
\computewidths
}*/

/*{\Mtext [[\#include <CGAL/ch_jarvis.h>]]
}*/

template <class ForwardIterator, class OutputIterator, 
          class Point, class Traits>
OutputIterator
CGAL_ch_jarvis_march(ForwardIterator first, ForwardIterator last,
                     const Point& start_p, const Point& stop_p,
                     OutputIterator  result,
                     const Traits& ch_traits);
/*{\Mfunc generates the counterclockwise ordered subsequence of
extreme points between |start_p| and |stop_p| of the points in the
range [|first|,|last|), starting at position result with point |start_p|.
The last point generated is the point preceding |stop_p| in the
counterclockwise order of extreme points.\\
{\it Precondition:} |start_p| and |stop_p| are extreme points with respect to
the points in the range [|first|,|last|) and |stop_p| is an element of
range [|first|,|last|).\\
{\sc traits}: uses |Traits::Point_2| $\equiv$ |Point|, and 
|Traits::Less_rotate_ccw|.
}*/


/*{\Moptions
outfile=cgal_ch_I_ja.man
}*/

/*{\Mtext [[\#include <CGAL/ch_jarvis.h>]]
}*/

template <class ForwardIterator, class OutputIterator, class Traits>
OutputIterator
CGAL_ch_jarvis(ForwardIterator first, ForwardIterator last, 
               OutputIterator  result,
               const Traits& ch_traits);
/*{\Mfuncl
same as |CGAL_convex_hull_points_2(first,last,result)|.\\
{\sc traits}: uses |Traits::Point_2|, |Traits::Less_rotate_ccw|, and
|Traits::Less_xy|.
}*/

#ifdef CGAL_POINT_2_H
/*{\Moptions
outfile=cgal_ch_jm.man
}*/

/*{\Mtext
\settowidth{\typewidth}{|OutputIterator|}
\addtolength{\typewidth}{\colsep}
\settowidth{\callwidth}{|CGAL_ch_|}
\computewidths
}*/

template <class ForwardIterator, class OutputIterator, class R>
inline
OutputIterator
CGAL_ch_jarvis_march(ForwardIterator first, ForwardIterator last,
                     const CGAL_Point_2<R>& start_p,
                     const CGAL_Point_2<R>& stop_p,
                     OutputIterator  result )
{
  return CGAL_ch_jarvis_march( first, last,
                               start_p, stop_p,
                               results, CGAL_convex_hull_traits_2<R>() );
}

/*{\Mfunc generates the counterclockwise ordered subsequence of 
extreme points between |start_p| and |stop_p| of the points in the 
range [|first|,|last|), starting at position result with point |start_p|. 
The last point generated is the point preceding |stop_p| in the 
counterclockwise order of extreme points.\\
{\it Precondition:} |start_p| and |stop_p| are extreme points with respect to
the points in the range [|first|,|last|) and |stop_p| is an element of
range [|first|,|last|).}*/

/*{\Moptions
outfile=cgal_ch_ja.man
}*/

template <class ForwardIterator, class OutputIterator, class R>
inline
OutputIterator
CGAL_ch__jarvis(ForwardIterator first, ForwardIterator last, 
                OutputIterator  result,
                CGAL_Point_2<R>* )
{
  return CGAL_ch_jarvis( first, last, result, CGAL_convex_hull_traits_2<R>() );
}

template <class ForwardIterator, class OutputIterator>
inline
OutputIterator
CGAL_ch_jarvis(ForwardIterator first, ForwardIterator last, 
               OutputIterator  result)
{ return CGAL_ch__jarvis( first, last, result, value_type(first) ); }
/*{\Mfuncl
same as |CGAL_convex_hull_points_2(first,last,result)|.
}*/


#endif // CGAL_POINT_2_H

#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#include <CGAL/ch_jarvis.C>
#endif // CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION

#endif // CGAL_CH_JARVIS_H
