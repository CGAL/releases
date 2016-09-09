// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : include/CGAL/ch_graham_andrew.h
// package       : Convex_hull (2.2.19)
// source        : convex_hull_2.lw
// revision      : 2.2.19
// revision_date : 03 Dec 1999
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_CH_GRAHAM_ANDREW_H
#define CGAL_CH_GRAHAM_ANDREW_H

#include <CGAL/ch_utils.h>
#include <CGAL/ch_value_type.h>
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


#include <vector>
#include <algorithm>

CGAL_BEGIN_NAMESPACE
/*{\Moptions
outfile=cgal_ch_I_gas.man
}*/

/*{\Mtext
\settowidth{\typewidth}{|OutputIterator|}
\addtolength{\typewidth}{\colsep}
\settowidth{\callwidth}{|ch_|}
\computewidths
}*/

/*{\Mtext [[\#include <CGAL/ch_graham_andrew.h>]]
}*/

template <class BidirectionalIterator, class OutputIterator, class Traits>
OutputIterator
ch_graham_andrew_scan( BidirectionalIterator first,
                            BidirectionalIterator last,
                            OutputIterator        result,
                            const Traits& ch_traits );
/*{\Mfuncl 
computes the sorted sequence of extreme points which are not left 
of $pq$ and reports this sequence in a range starting at |result|,
where $p$ is the value of |first| and $q$ is the value of |last| $-1$.
The sequence reported starts with $p$, point $q$ is omitted.\\
{\it Precondition:} The points in [|first|,|last|) are sorted with respect
to $pq$ and the range [|first|,|last|) contains at least two different points.\\
{\sc traits}: uses |Traits::Leftturn| operating on the 
point type |Traits::Point_2|.
}*/

template <class BidirectionalIterator, class OutputIterator, class Traits>
OutputIterator
ch__ref_graham_andrew_scan( BidirectionalIterator first,
                                 BidirectionalIterator last,
                                 OutputIterator&       result,
                                 const Traits&         ch_traits);

/*{\Moptions
outfile=cgal_ch_I_ga.man
}*/

/*{\Mtext [[\#include <CGAL/ch_graham_andrew.h>]]
}*/

template <class InputIterator, class OutputIterator, class Traits>
OutputIterator
ch_graham_andrew( InputIterator  first,
                       InputIterator  last,
                       OutputIterator result,
                       const Traits&  ch_traits );
/*{\Mfuncl 
same as |convex_hull_points_2(first,last,result)|.\\
{\sc traits}: uses |Traits::Point_2|, |Traits::Leftturn|
and |Traits::Less_xy|.
}*/

#ifdef CGAL_POINT_2_H

/*{\Moptions
outfile=cgal_ch_gas.man
}*/

/*{\Mtext 
\settowidth{\typewidth}{|OutputIterator|}
\addtolength{\typewidth}{\colsep}
\settowidth{\callwidth}{|ch_|}
\computewidths
}*/

template <class BidirectionalIterator, class OutputIterator, class R>
inline
OutputIterator
ch__graham_andrew_scan( BidirectionalIterator first,
                             BidirectionalIterator last,
                             OutputIterator        result,
                             Point_2<R>* )
{
  return ch_graham_andrew_scan( first, last, result, 
                                convex_hull_traits_2<R>() );
}

template <class BidirectionalIterator, class OutputIterator>
inline
OutputIterator
ch_graham_andrew_scan( BidirectionalIterator first,
                            BidirectionalIterator last,
                            OutputIterator        result )
{ 
  return ch__graham_andrew_scan( first, last, result, 
                                 ch_value_type(first) ); 
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
ch__graham_andrew( InputIterator     first,
                        InputIterator     last,
                        OutputIterator    result,
                        Point_2<R>* )
{
  return ch_graham_andrew(first, last, result, 
                               convex_hull_traits_2<R>());
}

template <class InputIterator, class OutputIterator>
inline
OutputIterator
ch_graham_andrew( InputIterator  first,
                       InputIterator  last,
                       OutputIterator result )
{ return ch__graham_andrew( first, last, result, ch_value_type(first) ); }
/*{\Mfuncl 
same as |convex_hull_points_2(first,last,result)|.
}*/

#endif // CGAL_POINT_2_H
template <class InputIterator, class OutputIterator, class Traits>
OutputIterator
ch_lower_hull_scan( InputIterator  first,
                         InputIterator  last,
                         OutputIterator result,
                         const Traits&  ch_traits);
template <class InputIterator, class OutputIterator, class Traits>
OutputIterator
ch_upper_hull_scan( InputIterator  first,
                         InputIterator  last,
                         OutputIterator result,
                         const Traits&  ch_traits);
CGAL_END_NAMESPACE

#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#include <CGAL/ch_graham_andrew.C>
#endif // CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION

#endif // CGAL_CH_GRAHAM_ANDREW_H

