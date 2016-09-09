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
// file          : include/CGAL/IO/Tee_for_output_iterator.h
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


#ifndef CGAL_IO_TEE_FOR_OUTPUT_ITERATOR_H
#define CGAL_IO_TEE_FOR_OUTPUT_ITERATOR_H

#include <CGAL/basic.h>
#include <iterator>
#include <vector>
#include <CGAL/Handle.h>

CGAL_BEGIN_NAMESPACE
template <class T> class _Tee_for_output_iterator_rep;

template <class OutputIterator, class T>
class Tee_for_output_iterator 
  : public Handle
{
  typedef std::vector<T>                             container;
  typedef typename container::iterator               iterator;
  typedef T                                          value_type;
  typedef std::output_iterator_tag                   iterator_category;
  typedef std::iterator_traits<iterator>             iter_traits;
  typedef typename iter_traits::pointer              pointer;
  typedef typename iter_traits::reference            reference;

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

CGAL_END_NAMESPACE

#endif // CGAL_IO_TEE_FOR_OUTPUT_ITERATOR_H
