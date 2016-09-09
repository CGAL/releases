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

// +--------------------------------------------------------------------+
// | STL like copy that copies n elements
// | Extracted from generators.fw
// | $Revision: 1.4 $
// | $Date: 1997/06/27 21:30:01 $
// |
// | 1997   Lutz Kettner
// +--------------------------------------------------------------------+


#ifndef CGAL_RANDOM_SELECTION_H
#define CGAL_RANDOM_SELECTION_H 1

#ifndef __STDDEF_H__
#include <stddef.h>
#endif
#ifndef ITERATOR_H
#include <iterator.h>
#endif
#ifndef CGAL_RANDOM_H
#include <CGAL/Random.h>
#endif

template <class RandomAccessIterator, class Size, class OutputIterator,
          class Random>
OutputIterator CGAL_random_selection( RandomAccessIterator first,
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
OutputIterator CGAL_random_selection( RandomAccessIterator first,
                                      RandomAccessIterator last,
                                      Size n,
                                      OutputIterator result)
{
    return CGAL_random_selection( first, last, n, result, CGAL_random);
}
 
#endif // CGAL_RANDOM_SELECTION_H //
// EOF //
