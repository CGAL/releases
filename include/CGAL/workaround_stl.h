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

// Implementation: Workarounds for STL
// file  : include/CGAL/workaround_stl.h
// author: Sven Schönherr 

#if ! ( CGAL_WORKAROUND_STL_H)
#define CGAL_WORKAROUND_STL_H 1

// fix for GNU's type unification bug for STL's `distance' function
// ----------------------------------------------------------------
template < class BidirectionalIterator, class Distance >
void distance( BidirectionalIterator first,
	       BidirectionalIterator last,
	       Distance& n);

template < class BidirectionalIterator, class Distance >
inline
void
CGAL__distance( BidirectionalIterator first,
		BidirectionalIterator last, 
                Distance& n)
{
#ifdef __GNUG__
    while ( first != last) {
	++first;
	++n;
    }
#else
    distance( first, last, n);
#endif // __GNUG__
}
 
#endif // CGAL_WORKAROUND_STL_H

// ===== EOF ==================================================================
