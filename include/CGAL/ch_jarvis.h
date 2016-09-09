// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/ch_jarvis.h
// package       : Convex_hull (2.0.8)
// source        : convex_hull_2.lw
// revision      : 2.0.8
// revision_date : 06 May 1999
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_CH_JARVIS_H
#define CGAL_CH_JARVIS_H

#include <CGAL/ch_utils.h>
#ifdef CGAL_REP_CLASS_DEFINED
#include <CGAL/convex_hull_traits_2.h>
#ifdef STL_GCC
#ifndef GNU_ISTREAM_ITERATOR_VALUE_TYPE_FIX_H
#include <CGAL/gnu_istream_iterator_value_type_fix.h>
#endif // GNU_ISTREAM_ITERATOR_VALUE_TYPE_FIX_H
#endif // STL_GCC
#endif // CGAL_REP_CLASS_DEFINED
#ifndef CH_NO_POSTCONDITIONS
#include <CGAL/convexity_check_2.h>

#endif // CH_NO_POSTCONDITIONS


#include <algorithm>

CGAL_BEGIN_NAMESPACE
/*{\Moptions
outfile=cgal_ch_I_jm.man
}*/

/*{\Mtext 
\settowidth{\typewidth}{|OutputIterator|}
\addtolength{\typewidth}{\colsep}
\settowidth{\callwidth}{|ch_|}
\computewidths
}*/

/*{\Mtext [[\#include <CGAL/ch_jarvis.h>]]
}*/

template <class ForwardIterator, class OutputIterator, 
          class Point, class Traits>
OutputIterator
ch_jarvis_march(ForwardIterator first, ForwardIterator last,
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
ch_jarvis(ForwardIterator first, ForwardIterator last, 
               OutputIterator  result,
               const Traits& ch_traits);
/*{\Mfuncl
same as |convex_hull_points_2(first,last,result)|.\\
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
\settowidth{\callwidth}{|ch_|}
\computewidths
}*/

template <class ForwardIterator, class OutputIterator, class R>
inline
OutputIterator
ch_jarvis_march(ForwardIterator first, ForwardIterator last,
                const Point_2<R>& start_p,
                const Point_2<R>& stop_p,
                OutputIterator  result )
{
  return ch_jarvis_march( first, last,
                          start_p, stop_p,
                          results, convex_hull_traits_2<R>() );
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
ch__jarvis(ForwardIterator first, ForwardIterator last, 
                OutputIterator  result,
                Point_2<R>* )
{
  return ch_jarvis( first, last, result, convex_hull_traits_2<R>() );
}

template <class ForwardIterator, class OutputIterator>
inline
OutputIterator
ch_jarvis(ForwardIterator first, ForwardIterator last, 
               OutputIterator  result)
{ return ch__jarvis( first, last, result, std::value_type(first) ); }
/*{\Mfuncl
same as |convex_hull_points_2(first,last,result)|.
}*/


#endif // CGAL_POINT_2_H
CGAL_END_NAMESPACE

#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#include <CGAL/ch_jarvis.C>
#endif // CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION

#endif // CGAL_CH_JARVIS_H

