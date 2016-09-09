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
// file          : include/CGAL/Tee_for_output_iterator.h
// package       : Convex_hull (1.3.2)
// source        : convex_hull_2.lw
// revision      : 1.3.2
// revision_date : 09 Dec 1998
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_TEE_FOR_OUTPUT_ITERATOR_H
#define CGAL_TEE_FOR_OUTPUT_ITERATOR_H

#include <iterator.h>
#include <vector.h>
#include <CGAL/Handle.h>

template <class T> class CGAL__Tee_for_output_iterator_rep;

template <class OutputIterator, class T>
class CGAL_Tee_for_output_iterator 
  : public CGAL_Handle, public output_iterator
{
  typedef typename vector<T>::iterator  iterator;
  typedef T                             value_type;

public:
  CGAL_Tee_for_output_iterator(const OutputIterator& o) : o_it(o) 
  {  PTR = (CGAL_Rep*) new CGAL__Tee_for_output_iterator_rep<T>(); }

  CGAL_Tee_for_output_iterator<OutputIterator,T>& 
  operator=(const T& value) 
  { 
    ptr()->output_so_far.push_back(value);
    *o_it = value;
    return *this;
  }

  CGAL_Tee_for_output_iterator<OutputIterator,T>& 
  operator*() 
  { return *this; }

  CGAL_Tee_for_output_iterator<OutputIterator,T>& 
  operator++() 
  { 
    ++o_it; 
    return *this; 
  } 

  CGAL_Tee_for_output_iterator<OutputIterator,T> 
  operator++(int) 
  { 
    CGAL_Tee_for_output_iterator<OutputIterator,T> tmp = *this;
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

  CGAL__Tee_for_output_iterator_rep<T>*
  ptr()
  { return (CGAL__Tee_for_output_iterator_rep<T>*)PTR; }

protected:
  OutputIterator o_it;
};

template <class T>
class CGAL__Tee_for_output_iterator_rep : public CGAL_Rep
{
public:
  vector<T> output_so_far;
};

template <class OutputIterator, class T>
inline 
output_iterator_tag
iterator_category(const CGAL_Tee_for_output_iterator<OutputIterator,T>&)
{ return output_iterator_tag(); }

template <class OutputIterator, class T>
inline 
T*
value_type(const CGAL_Tee_for_output_iterator<OutputIterator,T>&)
{ return (T*)0; }

#endif // CGAL_TEE_FOR_OUTPUT_ITERATOR_H
