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

#ifndef CGAL_CONVEX_HULL_2_H
#define CGAL_CONVEX_HULL_2_H

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


#include <CGAL/ch_akl_toussaint.h>
/*{\Moptions
outfile=cgal_ch_I_default.man
}*/

/*{\Mtext
\settowidth{\typewidth}{|OutputIterator|}
\addtolength{\typewidth}{\colsep}
\settowidth{\callwidth}{|CGAL_ch_|}
\computewidths
}*/

/*{\Mtext [[\#include <CGAL/convex_hull_2.h>]]
}*/

template <class ForwardIterator, class OutputIterator, class Traits>
inline
OutputIterator
CGAL_convex_hull_points_2(ForwardIterator first, ForwardIterator last,
                           OutputIterator  result,
                           const Traits& ch_traits)
{
  return CGAL_ch_akl_toussaint(first, last, result, ch_traits);
}
/*{\Mfuncl generates the counterclockwise sequence of extreme points
of the points in the range [|first|,|last|). The resulting sequence
is placed starting at position |result|, and the past-the-end iterator
for the resulting sequence is returned. It is not specified, at which
point the cyclic sequence of extreme points is cut into a linear
sequence.\\
{\it Preconditions:}
[|first|,|last|) does not contain |result|.\\
{\sc traits}: uses |Traits::Point_2|, |Traits::Less_xy|, |Traits::Less_yx|,
|Traits::Greater_xy|, |Traits::Greater_yx|, and |Traits::leftturn(...)|.
}*/

#ifdef CGAL_POINT_2_H
/*{\Moptions
outfile=cgal_ch_default.man
}*/

/*{\Mtext 
\settowidth{\typewidth}{|OutputIterator|}
\addtolength{\typewidth}{\colsep}
\settowidth{\callwidth}{|CGAL_ch_|}
\computewidths
}*/

template <class ForwardIterator, class OutputIterator>
inline
OutputIterator 
CGAL_convex_hull_points_2(ForwardIterator first, ForwardIterator last, 
                          OutputIterator  result )
{
  return CGAL_ch_akl_toussaint(first, last, result);
}
/*{\Mfuncl generates the counterclockwise sequence of extreme points
of the points in the range [|first|,|last|). The resulting sequence
is placed starting at position |result|, and the past-the-end iterator
for the resulting sequence is returned. It is not specified, at which
point the cyclic sequence of extreme points is cut into a linear
sequence.\\
{\it Preconditions:} 
The source range [|first|,|last|) does not contain |result|.
As for all default versions, the value type of the iterators 
must be |CGAL_Point_2<R>| for some representation class |R|. 
}*/

#endif // CGAL_POINT_2_H

#endif // CGAL_CONVEX_HULL_2_H

