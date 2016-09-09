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


#ifndef CGAL_STL_EXTENSIONS_H
#define CGAL_STL_EXTENSIONS_H

#include <iterator.h>

template <class ForwardIterator>
inline
ForwardIterator
CGAL_successor( ForwardIterator it )
{
 return ++it;
}

template <class BidirectionalIterator>
inline
BidirectionalIterator
CGAL_predecessor( BidirectionalIterator it )
{
 return --it;
}

template <class InputIterator, class OutputIterator, class UnaryPredicate>
OutputIterator
CGAL_copy_if( InputIterator first, InputIterator last,
              OutputIterator  result,
              UnaryPredicate  pred );

template <class InputIterator, class OutputIterator1, 
          class OutputIterator2, class UnaryPredicate>
pair<OutputIterator1,OutputIterator2>
CGAL_copy_if_else( InputIterator first, InputIterator last,
                   OutputIterator1 result1,
                   OutputIterator2 result2,
                   UnaryPredicate  pred );


#ifdef CGAL_INCLUDE_TEMPLATE_CODE
#include <CGAL/stl_extensions.C>
#endif // CGAL_INCLUDE_TEMPLATE_CODE


#endif // CGAL_STL_EXTENSIONS_H

