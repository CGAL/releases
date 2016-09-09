// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/stl_extensions.C
// package       : Convex_hull (2.0.8)
// source        : stl_extensions.lw
// revision      : 2.0.1
// revision_date : 24 Mar 1999
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

