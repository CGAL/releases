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
// file          : include/CGAL/convex_hull_2.h
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


#ifndef CGAL_CONVEX_HULL_2_H
#define CGAL_CONVEX_HULL_2_H

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


#include <CGAL/ch_akl_toussaint.h>
#include <CGAL/ch_bykat.h>
#include <iterator.h> 
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

template <class InputIterator, class OutputIterator, class Traits>
inline
OutputIterator
CGAL___convex_hull_points_2(InputIterator first, InputIterator last,
                            OutputIterator  result,
                            const Traits& ch_traits,
                            input_iterator_tag )
{ return CGAL_ch_bykat(first, last, result, ch_traits); }

template <class InputIterator, class OutputIterator, class Traits>
inline
OutputIterator
CGAL___convex_hull_points_2(InputIterator first, InputIterator last,
                            OutputIterator  result,
                            const Traits& ch_traits,
                            forward_iterator_tag )
{ return CGAL_ch_akl_toussaint(first, last, result, ch_traits); }

template <class InputIterator, class OutputIterator, class Traits>
inline
OutputIterator
CGAL___convex_hull_points_2(InputIterator first, InputIterator last,
                            OutputIterator  result,
                            const Traits& ch_traits,
                            bidirectional_iterator_tag )
{ return CGAL_ch_akl_toussaint(first, last, result, ch_traits); }

template <class InputIterator, class OutputIterator, class Traits>
inline
OutputIterator
CGAL___convex_hull_points_2(InputIterator first, InputIterator last,
                            OutputIterator  result,
                            const Traits& ch_traits,
                            random_access_iterator_tag )
{ return CGAL_ch_akl_toussaint(first, last, result, ch_traits); }


template <class InputIterator, class OutputIterator, class Traits>
inline
OutputIterator
CGAL_convex_hull_points_2(InputIterator first, InputIterator last,
                          OutputIterator  result,
                          const Traits& ch_traits)
{
  return CGAL___convex_hull_points_2(first, last, result, ch_traits,
                                     iterator_category(first) );
}
/*{\Mfuncl generates the counterclockwise sequence of extreme points
of the points in the range [|first|,|last|). The resulting sequence
is placed starting at position |result|, and the past-the-end iterator
for the resulting sequence is returned. It is not specified, at which
point the cyclic sequence of extreme points is cut into a linear
sequence.\\
{\it Preconditions:}
[|first|,|last|) does not contain |result|.\\
{\sc traits}: operates on |Traits::Point_2| using |Traits::Less_xy|, 
|Traits::Less_yx|, and |Traits::Leftturn|.
}*/

/*{\Moptions
outfile=cgal_ch_I_default2.man
}*/

/*{\Mtext
\settowidth{\typewidth}{|OutputIterator|}
\addtolength{\typewidth}{\colsep}
\settowidth{\callwidth}{|CGAL_ch_|}
\computewidths
}*/

template <class InputIterator, class OutputIterator, class Traits>
inline
OutputIterator
CGAL_lower_hull_points_2(InputIterator first, InputIterator last,
                         OutputIterator  result,
                         const Traits& ch_traits)
{ return CGAL_ch_lower_hull_scan(first, last, result, ch_traits); }
/*{\Mfuncl generates the counterclockwise sequence of extreme points
on the lower hull of the points in the range [|first|,|last|). 
The resulting sequence is placed starting at position |result|, 
and the past-the-end iterator for the resulting sequence is returned. 
The sequence starts with the leftmost point, the rightmost point is
not included.\\
{\it Preconditions:}
[|first|,|last|) does not contain |result|.\\
{\sc traits}: operates on |Traits::Point_2| using |Traits::Less_xy|
and |Traits::Leftturn|.
}*/

template <class InputIterator, class OutputIterator, class Traits>
inline
OutputIterator
CGAL_upper_hull_points_2(InputIterator first, InputIterator last,
                         OutputIterator  result,
                         const Traits& ch_traits)
{ return CGAL_ch_upper_hull_scan(first, last, result, ch_traits); }
/*{\Mfuncl generates the counterclockwise sequence of extreme points
on the upper hull of the points in the range [|first|,|last|). 
The resulting sequence is placed starting at position |result|, 
and the past-the-end iterator for the resulting sequence is returned. 
The sequence starts with the rightmost point, the leftmost point is
not included.\\
{\it Preconditions:}
[|first|,|last|) does not contain |result|.\\
{\sc traits}: operates on |Traits::Point_2| using |Traits::Less_xy|
and |Traits::Leftturn|.
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

template <class ForwardIterator, class OutputIterator, class R>
inline
OutputIterator 
CGAL__convex_hull_points_2(ForwardIterator first, ForwardIterator last, 
                           OutputIterator  result,
                           CGAL_Point_2<R>* )
{ 
  return CGAL_convex_hull_points_2(first, last, result,
                                   CGAL_convex_hull_traits_2<R>() );
}

template <class ForwardIterator, class OutputIterator>
inline
OutputIterator 
CGAL_convex_hull_points_2(ForwardIterator first, ForwardIterator last, 
                          OutputIterator  result )
{ 
  return CGAL__convex_hull_points_2(first, last, result,
                                    value_type(first) );
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
/*{\Moptions
outfile=cgal_ch_default2.man
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
CGAL__lower_hull_points_2(ForwardIterator first, ForwardIterator last, 
                          OutputIterator  result,
                          CGAL_Point_2<R>* )
{ 
  return CGAL_lower_hull_points_2(first, last, result,
                                  CGAL_convex_hull_traits_2<R>() );
}

template <class ForwardIterator, class OutputIterator>
inline
OutputIterator 
CGAL_lower_hull_points_2(ForwardIterator first, ForwardIterator last, 
                         OutputIterator  result )
{ 
  return CGAL__lower_hull_points_2(first, last, result,
                                   value_type(first) );
}
/*{\Mfuncl generates the counterclockwise sequence of extreme points
on the lower hull of the points in the range [|first|,|last|). 
The resulting sequence is placed starting at position |result|, 
and the past-the-end iterator for the resulting sequence is returned. 
The sequence starts with the leftmost point, the rightmost point is
not included.\\
{\it Preconditions:} 
The source range [|first|,|last|) does not contain |result|.
As for all default versions, the value type of the iterators 
must be |CGAL_Point_2<R>| for some representation class |R|. 
}*/

template <class ForwardIterator, class OutputIterator, class R>
inline
OutputIterator 
CGAL__upper_hull_points_2(ForwardIterator first, ForwardIterator last, 
                          OutputIterator  result,
                          CGAL_Point_2<R>* )
{ 
  return CGAL_upper_hull_points_2(first, last, result,
                                  CGAL_convex_hull_traits_2<R>() );
}

template <class ForwardIterator, class OutputIterator>
inline
OutputIterator 
CGAL_upper_hull_points_2(ForwardIterator first, ForwardIterator last, 
                         OutputIterator  result )
{ 
  return CGAL__upper_hull_points_2(first, last, result,
                                   value_type(first) );
}
/*{\Mfuncl generates the counterclockwise sequence of extreme points
on the upper hull of the points in the range [|first|,|last|). 
The resulting sequence is placed starting at position |result|, 
and the past-the-end iterator for the resulting sequence is returned. 
The sequence starts with the rightmost point, the leftmost point is
not included.\\
{\it Preconditions:} 
The source range [|first|,|last|) does not contain |result|.
As for all default versions, the value type of the iterators 
must be |CGAL_Point_2<R>| for some representation class |R|. 
}*/
#endif // CGAL_POINT_2_H

#endif // CGAL_CONVEX_HULL_2_H

