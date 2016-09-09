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
// file          : include/CGAL/stl_extensions.C
// package       : Convex_hull (2.2.19)
// source        : stl_extensions.lw
// revision      : 2.2.4
// revision_date : 01 Sep 1999
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_STL_EXTENSIONS_C
#define CGAL_STL_EXTENSIONS_C

#include <CGAL/stl_extensions.h>

CGAL_BEGIN_NAMESPACE
template <class InputIterator, class OutputIterator, class UnaryPredicate>
OutputIterator
copy_if( InputIterator first, InputIterator last,
              OutputIterator  result,
              UnaryPredicate  pred )
{
 for ( ; first != last; first++ )
 {
    if ( pred(*first) )  *result++ = *first;
 }
 return result;
}


template <class InputIterator, class OutputIterator1, 
          class OutputIterator2, class UnaryPredicate>
std::pair<OutputIterator1,OutputIterator2>
copy_if_else( InputIterator first, InputIterator last,
                   OutputIterator1 result1,
                   OutputIterator2 result2,
                   UnaryPredicate  pred )
{
 for ( ; first != last; first++ )
 {
    if ( pred(*first) )
    {
        *result1++ = *first;
    }
    else
    {
     
        *result2++ = *first;
    }
 }
 return std::pair<OutputIterator1,OutputIterator2>(result1,result2);
}

CGAL_END_NAMESPACE

#endif // CGAL_STL_EXTENSIONS_C

