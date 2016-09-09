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

#ifndef CGAL_CH_JARVIS_H
#define CGAL_CH_JARVIS_H

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

template <class ForwardIterator, class OutputIterator, class Point, class Traits>
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
{
  return CGAL_ch__jarvis( first, last, result, value_type(first) );
}
/*{\Mfuncl
same as |CGAL_convex_hull_points_2(first,last,result)|.
}*/


#endif // CGAL_POINT_2_H

#ifdef CGAL_INCLUDE_TEMPLATE_CODE
#include <CGAL/ch_jarvis.C>
#endif // CGAL_INCLUDE_TEMPLATE_CODE

#endif // CGAL_CH_JARVIS_H

