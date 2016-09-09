// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
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
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/convex_hull_2.h
// package       : Convex_hull_2 (3.21)
// revision      : $Revision: 1.6 $
// revision_date : $Date: 2001/06/25 16:22:44 $
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================


#ifndef CGAL_CONVEX_HULL_2_H
#define CGAL_CONVEX_HULL_2_H

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


#include <CGAL/ch_akl_toussaint.h>
#include <CGAL/ch_bykat.h>
#include <iterator> 

CGAL_BEGIN_NAMESPACE
/*{\Moptions
outfile=cgal_ch_I_default.man
}*/

/*{\Mtext
\settowidth{\typewidth}{|OutputIterator|}
\addtolength{\typewidth}{\colsep}
\settowidth{\callwidth}{|ch_|}
\computewidths
}*/

/*{\Mtext [[\#include <CGAL/convex_hull_2.h>]]
}*/

template <class InputIterator, class OutputIterator, class Traits>
inline
OutputIterator
__convex_hull_points_2(InputIterator first, InputIterator last,
                       OutputIterator  result,
                       const Traits& ch_traits,
                       std::input_iterator_tag )
{ return ch_bykat(first, last, result, ch_traits); }

template <class InputIterator, class OutputIterator, class Traits>
inline
OutputIterator
__convex_hull_points_2(InputIterator first, InputIterator last,
                       OutputIterator  result,
                       const Traits& ch_traits,
                       std::forward_iterator_tag )
{ return ch_akl_toussaint(first, last, result, ch_traits); }

template <class InputIterator, class OutputIterator, class Traits>
inline
OutputIterator
__convex_hull_points_2(InputIterator first, InputIterator last,
                       OutputIterator  result,
                       const Traits& ch_traits,
                       std::bidirectional_iterator_tag )
{ return ch_akl_toussaint(first, last, result, ch_traits); }

template <class InputIterator, class OutputIterator, class Traits>
inline
OutputIterator
__convex_hull_points_2(InputIterator first, InputIterator last,
                       OutputIterator  result,
                       const Traits& ch_traits,
                       std::random_access_iterator_tag )
{ return ch_akl_toussaint(first, last, result, ch_traits); }


template <class InputIterator, class OutputIterator, class Traits>
inline
OutputIterator
convex_hull_points_2(InputIterator first, InputIterator last,
                     OutputIterator  result,
                     const Traits& ch_traits)
{
  return __convex_hull_points_2(first, last, result, ch_traits,
#ifndef CGAL_CFG_NO_ITERATOR_TRAITS
                    std::iterator_traits<InputIterator>::iterator_category() );
#else
                    std::iterator_category(first) );
#endif // CGAL_CFG_NO_ITERATOR_TRAITS
}
template <class InputIterator, class OutputIterator, class Traits>
inline
OutputIterator
convex_hull_2(InputIterator first, InputIterator last,
              OutputIterator  result, const Traits& ch_traits)
{
  return __convex_hull_points_2(first, last, result, ch_traits,
#ifndef CGAL_CFG_NO_ITERATOR_TRAITS
                    std::iterator_traits<InputIterator>::iterator_category() );
#else
                    std::iterator_category(first) );
#endif // CGAL_CFG_NO_ITERATOR_TRAITS
}
/*{\Mfuncl generates the counterclockwise sequence of extreme points
of the points in the range [|first|,|last|). The resulting sequence
is placed starting at position |result|, and the past-the-end iterator
for the resulting sequence is returned. It is not specified, at which
point the cyclic sequence of extreme points is cut into a linear
sequence.\\
{\it Preconditions:}
[|first|,|last|) does not contain |result|.\\
{\sc traits}: operates on |Traits::Point_2| using |Traits::Less_xy_2|, 
|Traits::Less_yx_2|, and |Traits::Leftturn_2|.
}*/

/*{\Moptions
outfile=cgal_ch_I_default2.man
}*/

/*{\Mtext
\settowidth{\typewidth}{|OutputIterator|}
\addtolength{\typewidth}{\colsep}
\settowidth{\callwidth}{|ch_|}
\computewidths
}*/

template <class InputIterator, class OutputIterator, class Traits>
inline
OutputIterator
lower_hull_points_2(InputIterator first, InputIterator last,
                         OutputIterator  result,
                         const Traits& ch_traits)
{ return ch_lower_hull_scan(first, last, result, ch_traits); }
/*{\Mfuncl generates the counterclockwise sequence of extreme points
on the lower hull of the points in the range [|first|,|last|). 
The resulting sequence is placed starting at position |result|, 
and the past-the-end iterator for the resulting sequence is returned. 
The sequence starts with the leftmost point, the rightmost point is
not included.\\
{\it Preconditions:}
[|first|,|last|) does not contain |result|.\\
{\sc traits}: operates on |Traits::Point_2| using |Traits::Less_xy_2|
and |Traits::Leftturn_2|.
}*/

template <class InputIterator, class OutputIterator, class Traits>
inline
OutputIterator
upper_hull_points_2(InputIterator first, InputIterator last,
                         OutputIterator  result,
                         const Traits& ch_traits)
{ return ch_upper_hull_scan(first, last, result, ch_traits); }
/*{\Mfuncl generates the counterclockwise sequence of extreme points
on the upper hull of the points in the range [|first|,|last|). 
The resulting sequence is placed starting at position |result|, 
and the past-the-end iterator for the resulting sequence is returned. 
The sequence starts with the rightmost point, the leftmost point is
not included.\\
{\it Preconditions:}
[|first|,|last|) does not contain |result|.\\
{\sc traits}: operates on |Traits::Point_2| using |Traits::Less_xy_2|
and |Traits::Leftturn_2|.
}*/
#ifdef CGAL_POINT_2_H
/*{\Moptions
outfile=cgal_ch_default.man
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
_convex_hull_points_2(ForwardIterator first, ForwardIterator last, 
                      OutputIterator  result,
                      Point_2<R>* )
{ 
  return convex_hull_points_2(first, last, result,
                              R() );
}

template <class ForwardIterator, class OutputIterator>
inline
OutputIterator 
convex_hull_points_2(ForwardIterator first, ForwardIterator last, 
                     OutputIterator  result )
{ 
  return _convex_hull_points_2(first, last, result,
                               ch_value_type(first) );
}
template <class ForwardIterator, class OutputIterator>
inline
OutputIterator 
convex_hull_2(ForwardIterator first, ForwardIterator last, 
                     OutputIterator  result )
{ 
  return _convex_hull_points_2(first, last, result,
                               ch_value_type(first) );
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
must be |Point_2<R>| for some representation class |R|. 
}*/
/*{\Moptions
outfile=cgal_ch_default2.man
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
_lower_hull_points_2(ForwardIterator first, ForwardIterator last, 
                          OutputIterator  result,
                          Point_2<R>* )
{ 
  return lower_hull_points_2(first, last, result,
                                  R() );
}

template <class ForwardIterator, class OutputIterator>
inline
OutputIterator 
lower_hull_points_2(ForwardIterator first, ForwardIterator last, 
                         OutputIterator  result )
{ 
  return _lower_hull_points_2(first, last, result,
                                   ch_value_type(first) );
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
must be |Point_2<R>| for some representation class |R|. 
}*/

template <class ForwardIterator, class OutputIterator, class R>
inline
OutputIterator 
_upper_hull_points_2(ForwardIterator first, ForwardIterator last, 
                          OutputIterator  result,
                          Point_2<R>* )
{ 
  return upper_hull_points_2(first, last, result,
                                  R() );
}

template <class ForwardIterator, class OutputIterator>
inline
OutputIterator 
upper_hull_points_2(ForwardIterator first, ForwardIterator last, 
                         OutputIterator  result )
{ 
  return _upper_hull_points_2(first, last, result,
                                   ch_value_type(first) );
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
must be |Point_2<R>| for some representation class |R|. 
}*/
#endif // CGAL_POINT_2_H
CGAL_END_NAMESPACE

#endif // CGAL_CONVEX_HULL_2_H

