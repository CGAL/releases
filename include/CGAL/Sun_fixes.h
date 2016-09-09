// ======================================================================
//
// Copyright (c) 1997-2002 The CGAL Consortium

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
// file          : include/CGAL/Sun_fixes.h
// package       : Configuration (2.32)
// source        :
// revision      : 1.11
// revision_date : 30 Mar 1998
// author(s)     : Michael Hoffmann
//
// coordinator   : Utrecht University
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_SUN_FIXES_H
#define CGAL_SUN_FIXES_H 1

//----------------------------------------------------------------------//
//             enable member templates for stdlib                       //
//----------------------------------------------------------------------//

#include <stdcomp.h>
#undef RWSTD_NO_MEMBER_TEMPLATES
#undef _RWSTD_NO_MEMBER_TEMPLATES

//----------------------------------------------------------------------//
//             fake iterator_traits                                     //
//----------------------------------------------------------------------//

#include <iterator>
namespace std {
  template <class Iterator> struct iterator_traits
  {
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
    typedef typename Iterator::iterator_category iterator_category;
  };
  template <class T> struct iterator_traits<T*>
  {
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;
    typedef random_access_iterator_tag iterator_category;
  };
  template <class T> struct iterator_traits<const T*>
  {
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef const T* pointer;
    typedef const T& reference;
    typedef random_access_iterator_tag iterator_category;
  };
  template <class ForwardIterator>
  inline ptrdiff_t
  distance (ForwardIterator first, ForwardIterator last)
  {
    ptrdiff_t n = 0;
    __distance(first, last, n, 
               iterator_traits<ForwardIterator>::iterator_category());
    return n;
  }

  template < class T >
  inline typename T::value_type*
  __value_type (const T&)
  { return (typename T::value_type*)(0); }

  template < class T >
  inline typename T::difference_type*
  __distance_type(const T&)
  { return (typename T::difference_type*)(0); }

  template < class T >
  inline typename T::iterator_category
  __iterator_category (const T&)
  {
    typename T::iterator_category tmp;
    return tmp;
  }
} // namespace std

#endif // CGAL_SUN_FIXES_H
