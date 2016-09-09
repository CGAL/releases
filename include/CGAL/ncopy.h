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


// | STL like copy that copies n elements
// | Extracted from generators.fw
// | $Revision: 1.1 $
// | $Date: 1997/06/13 00:17:03 $
// | 1997   Lutz Kettner


#ifndef CGAL_NCOPY_H
#define CGAL_NCOPY_H 1

#ifndef __STDDEF_H__
#include <stddef.h>
#endif

template <class InputIterator, class OutputIterator>
OutputIterator CGAL_ncopy( InputIterator first,
                           size_t n,
                           OutputIterator first2) {
    // copies the first n elements from `first' to `first2'.
    while( n--) {
        *first2 = *first;
        first++;
        first2++;
    }
    return first2;
}

 
#endif // CGAL_NCOPY_H //
// EOF //
