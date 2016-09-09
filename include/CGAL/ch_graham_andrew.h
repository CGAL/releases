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

#ifndef CGAL_CH_GRAHAM_ANDREW_H
#define CGAL_CH_GRAHAM_ANDREW_H

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


#include <vector.h>
#include <algo.h>
/*{\Moptions
outfile=cgal_ch_I_gas.man
}*/

/*{\Mtext
\settowidth{\typewidth}{|OutputIterator|}
\addtolength{\typewidth}{\colsep}
\settowidth{\callwidth}{|CGAL_ch_|}
\computewidths
}*/

/*{\Mtext [[\#include <CGAL/ch_graham_andrew.h>]]
}*/

template <class BidirectionalIterator, class OutputIterator, class Traits>
OutputIterator
CGAL_ch_graham_andrew_scan( BidirectionalIterator first,
                            BidirectionalIterator last,
                            OutputIterator        result,
                            const Traits&             ch_traits);
/*{\Mfuncl 
computes the sorted sequence of extreme points which are not left 
of $pq$ and reports this sequence in a range starting at |result|,
where $p$ is the value of |first| and $q$ is the value of |last| $-1$.
The sequence reported starts with $p$, point $q$ is omitted.\\
{\it Precondition:} The points in [|first|,|last|) are sorted with respect
to $pq$ and the range [|first|,|last|) contains at least two different points.\\
{\sc traits}: uses method |Traits::leftturn| operating on the 
point type |Traits::Point_2|.
}*/

template <class BidirectionalIterator, class OutputIterator, class Traits>
OutputIterator
CGAL_ch__ref_graham_andrew_scan( BidirectionalIterator first,
                                 BidirectionalIterator last,
                                 OutputIterator&       result,
                                 const Traits&             ch_traits);

/*{\Moptions
outfile=cgal_ch_I_ga.man
}*/

/*{\Mtext [[\#include <CGAL/ch_graham_andrew.h>]]
}*/

template <class InputIterator, class OutputIterator, class Traits>
OutputIterator
CGAL_ch_graham_andrew( InputIterator  first,
                       InputIterator  last,
                       OutputIterator result,
                       const Traits&      ch_traits);
/*{\Mfuncl 
same as |CGAL_convex_hull_points_2(first,last,result)|.\\
{\sc traits}: operates on |Traits::Point_2| using |Traits::leftturn(...)|
and |Traits::Less_xy|.
}*/

#ifdef CGAL_POINT_2_H
/*{\Moptions
outfile=cgal_ch_gas.man
}*/

/*{\Mtext 
\settowidth{\typewidth}{|OutputIterator|}
\addtolength{\typewidth}{\colsep}
\settowidth{\callwidth}{|CGAL_ch_|}
\computewidths
}*/

template <class BidirectionalIterator, class OutputIterator, class R>
inline
OutputIterator
CGAL_ch__graham_andrew_scan( BidirectionalIterator first,
                             BidirectionalIterator last,
                             OutputIterator        result,
                             CGAL_Point_2<R>* )
{
  return CGAL_ch_graham_andrew_scan( first, last, result, 
                                     CGAL_convex_hull_traits_2<R>() );
}

template <class BidirectionalIterator, class OutputIterator>
inline
OutputIterator
CGAL_ch_graham_andrew_scan( BidirectionalIterator first,
                            BidirectionalIterator last,
                            OutputIterator        result )
{
  return CGAL_ch__graham_andrew_scan( first, last, result, value_type(first) );
}
/*{\Mfuncl 
computes the sorted sequence of extreme points which are not left 
of $pq$ and reports this sequence in a range starting at |result|,
where $p$ is the value of |first| and $q$ is the value of |last| $-1$.
The sequence reported starts with $p$, point $q$ is omitted.\\
}*/

/*{\Moptions
outfile=cgal_ch_ga.man
}*/

template <class InputIterator, class OutputIterator, class R>
inline
OutputIterator
CGAL_ch__graham_andrew( InputIterator     first,
                        InputIterator     last,
                        OutputIterator    result,
                        CGAL_Point_2<R>* )
{
  return CGAL_ch_graham_andrew(first, last, result, 
                               CGAL_convex_hull_traits_2<R>());
}

template <class InputIterator, class OutputIterator>
inline
OutputIterator
CGAL_ch_graham_andrew( InputIterator  first,
                       InputIterator  last,
                       OutputIterator result )
{
  return CGAL_ch__graham_andrew( first, last, result, value_type(first) );
}
/*{\Mfuncl 
same as |CGAL_convex_hull_points_2(first,last,result)|.
}*/

#endif // CGAL_POINT_2_H

#ifdef CGAL_INCLUDE_TEMPLATE_CODE
#include <CGAL/ch_graham_andrew.C>
#endif // CGAL_INCLUDE_TEMPLATE_CODE

#endif // CGAL_CH_GRAHAM_ANDREW_H

