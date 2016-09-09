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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/stl_extensions.h
// package       : Convex_hull (1.3.2)
// source        : stl_extensions.lw
// revision      : 1.3.2
// revision_date : 09 Dec 1998
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_STL_EXTENSIONS_H
#define CGAL_STL_EXTENSIONS_H

#include <iterator.h>
#include <vector.h>
#include <pair.h>

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

#include <CGAL/Tee_for_output_iterator.h>

#ifdef CGAL_INCLUDE_TEMPLATE_CODE
#include <CGAL/stl_extensions.C>
#endif // CGAL_INCLUDE_TEMPLATE_CODE


#endif // CGAL_STL_EXTENSIONS_H

