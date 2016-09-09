// ======================================================================
//
// Copyright (c) 1997, 1998, 1999, 2000 The CGAL Consortium

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
// file          : include/CGAL/algorithm.h
// package       : STL_Extension (2.57)
// chapter       : $CGAL_Chapter: STL Extensions for CGAL $
// source        : stl_extension.fw
// revision      : $Revision: 1.36 $
// revision_date : $Date: 2002/03/28 15:24:30 $
// author(s)     : Michael Hoffmann
//                 Lutz Kettner
//
// coordinator   : ETH
//
// STL like algorithms
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_ALGORITHM_H
#define CGAL_ALGORITHM_H 1

#include <CGAL/basic.h>
#include <CGAL/copy_n.h>
#include <algorithm>

CGAL_BEGIN_NAMESPACE

template < class ForwardIterator >
std::pair< ForwardIterator, ForwardIterator >
min_max_element(ForwardIterator first, ForwardIterator last)
{
  typedef std::pair< ForwardIterator, ForwardIterator > FP;
  FP result(first, first);
  if (first != last)
    while (++first != last) {
      if (*first < *result.first)
        result.first = first;
      if (*result.second < *first)
        result.second = first;
    }
  return result;
}
template < class ForwardIterator, class CompareMin, class CompareMax >
std::pair< ForwardIterator, ForwardIterator >
min_max_element(ForwardIterator first,
                ForwardIterator last,
                CompareMin comp_min,
                CompareMax comp_max)
{
  typedef std::pair< ForwardIterator, ForwardIterator > FP;
  FP result(first, first);
  if (first != last)
    while (++first != last) {
      if (comp_min(*first, *result.first))
        result.first = first;
      if (comp_max(*result.second, *first))
        result.second = first;
    }
  return result;
}
template < class ForwardIterator, class Predicate >
ForwardIterator
min_element_if(ForwardIterator first,
               ForwardIterator last,
               Predicate pred)
{
  ForwardIterator result = first = std::find_if(first, last, pred);
  if (first != last)
    while (++first != last)
      if (*first < *result && pred(*first))
        result = first;
  return result;
}
template < class ForwardIterator, class Compare, class Predicate >
ForwardIterator
min_element_if(ForwardIterator first,
               ForwardIterator last,
               Compare comp,
               Predicate pred)
{
  ForwardIterator result = first = std::find_if(first, last, pred);
  if (first != last)
    while (++first != last)
      if (comp(*first, *result) && pred(*first))
        result = first;
  return result;
}
template < class ForwardIterator, class Predicate >
ForwardIterator
max_element_if(ForwardIterator first,
               ForwardIterator last,
               Predicate pred)
{
  ForwardIterator result = first = std::find_if(first, last, pred);
  if (first != last)
    while (++first != last)
      if (*result < *first && pred(*first))
        result = first;
  return result;
}
template < class ForwardIterator, class Compare, class Predicate >
ForwardIterator
max_element_if(ForwardIterator first,
               ForwardIterator last,
               Compare comp,
               Predicate pred)
{
  ForwardIterator result = first = std::find_if(first, last, pred);
  if (first != last)
    while (++first != last)
      if (comp(*result, *first) && pred(*first))
        result = first;
  return result;
}


CGAL_END_NAMESPACE

#endif // CGAL_ALGORITHM_H //
// EOF //
