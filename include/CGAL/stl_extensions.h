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
// file          : include/CGAL/stl_extensions.h
// package       : Convex_hull_2 (3.34)
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2001/12/05 15:16:22 $
// author(s)     : Stefan Schirra 
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_STL_EXTENSIONS_H
#define CGAL_STL_EXTENSIONS_H

#include <CGAL/basic.h>
#include <iterator>
#include <utility>

CGAL_BEGIN_NAMESPACE
template <class ForwardIterator>
inline
ForwardIterator
successor( ForwardIterator it )
{
 return ++it;
}

template <class BidirectionalIterator>
inline
BidirectionalIterator
predecessor( BidirectionalIterator it )
{
 return --it;
}

template <class InputIterator, class OutputIterator, class UnaryPredicate>
OutputIterator
copy_if( InputIterator first, InputIterator last,
              OutputIterator  result,
              UnaryPredicate  pred );

template <class InputIterator, class OutputIterator1, 
          class OutputIterator2, class UnaryPredicate>
std::pair<OutputIterator1,OutputIterator2>
copy_if_else( InputIterator first, InputIterator last,
                   OutputIterator1 result1,
                   OutputIterator2 result2,
                   UnaryPredicate  pred );

CGAL_END_NAMESPACE
#include <CGAL/IO/Tee_for_output_iterator.h>

#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#include <CGAL/stl_extensions.C>
#endif // CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION


#endif // CGAL_STL_EXTENSIONS_H

