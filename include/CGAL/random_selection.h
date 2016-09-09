// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/random_selection.h
// package       : Generator (2.62)
// chapter       : $CGAL_Chapter: Geometric Object Generators $
// source        : generators.fw
// revision      : $Revision: 1.1.1.1 $
// revision_date : $Date: 2001/02/02 14:49:40 $
// author(s)     : Lutz Kettner
//
// coordinator   : INRIA, Sophia Antipolis
//
// Copy n randomly chosen items
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_RANDOM_SELECTION_H
#define CGAL_RANDOM_SELECTION_H 1
#ifndef CGAL_PROTECT_CSTDDEF
#include <cstddef>
#define CGAL_PROTECT_CSTDDEF
#endif
#ifndef CGAL_PROTECT_ITERATOR
#include <iterator>
#define CGAL_PROTECT_ITERATOR
#endif
#ifndef CGAL_RANDOM_H
#include <CGAL/Random.h>
#endif

CGAL_BEGIN_NAMESPACE

template <class RandomAccessIterator, class Size, class OutputIterator,
          class Random>
OutputIterator random_selection( RandomAccessIterator first,
                                 RandomAccessIterator last,
                                 Size n,
                                 OutputIterator result,
                                 Random& rnd)
    // choose a random item from the range [`first',`last') and write it
    // to `first2', each item from the range with equal probability.
    // Repeat this n times, thus writing n items to `first2'. A single
    // random number is needed from `rnd' for each item. Returns the
    // value of `first2' after inserting the n items.
{
    int m = int(last - first);
    for ( Size i = 0; i < n; i++) {
        *result++ = first[ rnd(m)];
    }
    return result;
}

template <class RandomAccessIterator, class Size, class OutputIterator>
OutputIterator random_selection( RandomAccessIterator first,
                                 RandomAccessIterator last,
                                 Size n,
                                 OutputIterator result)
{
    return random_selection( first, last, n, result, default_random);
}

CGAL_END_NAMESPACE    
#endif // CGAL_RANDOM_SELECTION_H //
// EOF //
