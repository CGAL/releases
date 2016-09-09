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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/convex_hull_2.h
// package       : Convex_hull_2 (3.34)
// revision      : $Revision: 1.7 $
// revision_date : $Date: 2001/12/05 15:16:18 $
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================


#ifndef CGAL_CONVEX_HULL_2_H
#define CGAL_CONVEX_HULL_2_H

#include <CGAL/basic.h>

#ifdef CGAL_REP_CLASS_DEFINED
#include <CGAL/convex_hull_traits_2.h>
#endif // CGAL_REP_CLASS_DEFINED

#include <CGAL/ch_akl_toussaint.h>
#include <CGAL/ch_bykat.h>
#include <iterator> 

CGAL_BEGIN_NAMESPACE

template <class InputIterator, class OutputIterator, class Traits>
inline
OutputIterator
CGAL_convex_hull_points_2(InputIterator first, InputIterator last,
                          OutputIterator  result,
                          const Traits& ch_traits,
                          std::input_iterator_tag )
{ return ch_bykat(first, last, result, ch_traits); }

template <class InputIterator, class OutputIterator, class Traits>
inline
OutputIterator
CGAL_convex_hull_points_2(InputIterator first, InputIterator last,
                          OutputIterator  result,
                          const Traits& ch_traits,
                          std::forward_iterator_tag )
{ return ch_akl_toussaint(first, last, result, ch_traits); }

template <class InputIterator, class OutputIterator, class Traits>
inline
OutputIterator
CGAL_convex_hull_points_2(InputIterator first, InputIterator last,
                          OutputIterator  result,
                          const Traits& ch_traits,
                          std::bidirectional_iterator_tag )
{ return ch_akl_toussaint(first, last, result, ch_traits); }

template <class InputIterator, class OutputIterator, class Traits>
inline
OutputIterator
CGAL_convex_hull_points_2(InputIterator first, InputIterator last,
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
    typedef std::iterator_traits<InputIterator>   ITraits;
    typedef typename ITraits::iterator_category   Category;
    return CGAL_convex_hull_points_2(first, last, result, ch_traits,
                                     Category());
}


template <class ForwardIterator, class OutputIterator>
inline
OutputIterator 
convex_hull_points_2(ForwardIterator first, ForwardIterator last, 
                     OutputIterator  result )
{ 
    typedef std::iterator_traits<ForwardIterator> ITraits;
    typedef typename ITraits::value_type          value_type;
    typedef typename ITraits::iterator_category   Category;
    typedef CGAL::Kernel_traits<value_type>       KTraits;
    typedef typename KTraits::Kernel              Kernel;
    return CGAL_convex_hull_points_2(first, last, result, Kernel(), 
                                     Category());
}


// generates the counterclockwise sequence of extreme points
// of the points in the range [|first|,|last|). The resulting sequence
// is placed starting at position |result|, and the past-the-end iterator
// for the resulting sequence is returned. It is not specified, at which
// point the cyclic sequence of extreme points is cut into a linear
// sequence.
// {\it Preconditions:}
// [|first|,|last|) does not contain |result|.
// {\sc traits}: operates on |Traits::Point_2| using |Traits::Less_xy_2|, 
// |Traits::Less_yx_2|, and |Traits::Leftturn_2|.
template <class InputIterator, class OutputIterator, class Traits>
inline
OutputIterator
convex_hull_2(InputIterator first, InputIterator last,
              OutputIterator  result, const Traits& ch_traits)
{
    return convex_hull_points_2(first, last, result, ch_traits);
}

template <class ForwardIterator, class OutputIterator>
inline
OutputIterator 
convex_hull_2(ForwardIterator first, ForwardIterator last, 
              OutputIterator  result )
{
    return convex_hull_points_2(first, last, result);
}


// generates the counterclockwise sequence of extreme points
// on the lower hull of the points in the range [|first|,|last|). 
// The resulting sequence is placed starting at position |result|, 
// and the past-the-end iterator for the resulting sequence is returned. 
// The sequence starts with the leftmost point, the rightmost point is
// not included.
// {\it Preconditions:}
// [|first|,|last|) does not contain |result|.
// {\sc traits}: operates on |Traits::Point_2| using |Traits::Less_xy_2|
// and |Traits::Leftturn_2|.
template <class InputIterator, class OutputIterator, class Traits>
inline
OutputIterator
lower_hull_points_2(InputIterator first, InputIterator last,
                    OutputIterator  result,
                    const Traits& ch_traits)
{ return ch_lower_hull_scan(first, last, result, ch_traits); }

template <class ForwardIterator, class OutputIterator>
inline
OutputIterator 
lower_hull_points_2(ForwardIterator first, ForwardIterator last, 
                    OutputIterator  result )
{ 
    typedef std::iterator_traits<ForwardIterator> ITraits;
    typedef typename ITraits::value_type          value_type;
    typedef CGAL::Kernel_traits<value_type>       KTraits;
    typedef typename KTraits::Kernel              Kernel;
    return lower_hull_points_2(first, last, result, Kernel());
}


// generates the counterclockwise sequence of extreme points
// on the upper hull of the points in the range [|first|,|last|). 
// The resulting sequence is placed starting at position |result|, 
// and the past-the-end iterator for the resulting sequence is returned. 
// The sequence starts with the rightmost point, the leftmost point is
// not included.
// {\it Preconditions:}
// [|first|,|last|) does not contain |result|.
// {\sc traits}: operates on |Traits::Point_2| using |Traits::Less_xy_2|
// and |Traits::Leftturn_2|.
template <class InputIterator, class OutputIterator, class Traits>
inline
OutputIterator
upper_hull_points_2(InputIterator first, InputIterator last,
                    OutputIterator  result,
                    const Traits& ch_traits)
{ return ch_upper_hull_scan(first, last, result, ch_traits); }


template <class ForwardIterator, class OutputIterator>
inline
OutputIterator 
upper_hull_points_2(ForwardIterator first, ForwardIterator last, 
                    OutputIterator  result )
{ 
    typedef std::iterator_traits<ForwardIterator> ITraits;
    typedef typename ITraits::value_type          value_type;
    typedef CGAL::Kernel_traits<value_type>       KTraits;
    typedef typename KTraits::Kernel              Kernel;
    return upper_hull_points_2(first, last, result, Kernel());
}
CGAL_END_NAMESPACE

#endif // CGAL_CONVEX_HULL_2_H







