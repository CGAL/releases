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
// file          : include/CGAL/IO/Tee_for_output_iterator.h
// package       : Convex_hull (2.2.19)
// source        : convex_hull_2.lw
// revision      : 2.2.19
// revision_date : 03 Dec 1999
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_IO_TEE_FOR_OUTPUT_ITERATOR_H
#define CGAL_IO_TEE_FOR_OUTPUT_ITERATOR_H

#include <iterator>
#include <vector>
#include <CGAL/Handle.h>

CGAL_BEGIN_NAMESPACE
template <class T> class _Tee_for_output_iterator_rep;

template <class OutputIterator, class T>
class Tee_for_output_iterator 
  : public Handle
#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
  , public std::output_iterator
#endif // CGAL_CFG_NO_ITERATOR_TRAITS
{
  typedef std::vector<T>                             container;
  typedef typename container::iterator               iterator;
  typedef T                                          value_type;
  typedef std::output_iterator_tag                   iterator_category;
#ifndef CGAL_CFG_NO_ITERATOR_TRAITS
  typedef std::iterator_traits<iterator>             iter_traits;
  typedef typename iter_traits::pointer              pointer;
  typedef typename iter_traits::reference            reference;
#endif // CGAL_CFG_NO_ITERATOR_TRAITS

public:
  Tee_for_output_iterator(const OutputIterator& o) : o_it(o) 
  {  PTR = (Rep*) new _Tee_for_output_iterator_rep<T>(); }

  Tee_for_output_iterator<OutputIterator,T>& 
  operator=(const T& value) 
  { 
    ptr()->output_so_far.push_back(value);
    *o_it = value;
    return *this;
  }

  Tee_for_output_iterator<OutputIterator,T>& 
  operator*() 
  { return *this; }

  Tee_for_output_iterator<OutputIterator,T>& 
  operator++() 
  { 
    ++o_it; 
    return *this; 
  } 

  Tee_for_output_iterator<OutputIterator,T> 
  operator++(int) 
  { 
    Tee_for_output_iterator<OutputIterator,T> tmp = *this;
    o_it++; 
    return tmp; 
  } 

  iterator
  output_so_far_begin()
  { return ptr()->output_so_far.begin(); }

  iterator
  output_so_far_end()
  { return ptr()->output_so_far.end(); }

  OutputIterator&
  to_output_iterator()
  { return o_it; }

  _Tee_for_output_iterator_rep<T>*
  ptr()
  { return (_Tee_for_output_iterator_rep<T>*)PTR; }

protected:
  OutputIterator o_it;
};

template <class T>
class _Tee_for_output_iterator_rep : public Rep
{
public:
  std::vector<T> output_so_far;
};

template <class OutputIterator, class T>
inline 
T*
value_type(const Tee_for_output_iterator<OutputIterator,T>&)
{ return (T*)0; }
CGAL_END_NAMESPACE

template <class OutputIterator, class T>
inline 
std::output_iterator_tag
iterator_category(const CGAL::Tee_for_output_iterator<OutputIterator,T>&)
{ return std::output_iterator_tag(); }


#endif // CGAL_IO_TEE_FOR_OUTPUT_ITERATOR_H
