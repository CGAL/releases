// ======================================================================
//
// Copyright (c) 1998, 1999, 2000 The CGAL Consortium

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
// file          : include/CGAL/Transform_iterator.h
// package       : Matrix_search (1.54)
// chapter       : $CGAL_Chapter: Geometric Optimisation $
// source        : mon_search.aw
// revision      : $Revision: 1.52 $
// revision_date : $Date: 2002/03/25 15:04:56 $
// author(s)     : Michael Hoffmann
//
// coordinator   : ETH
//
// An OutputIterator Adaptor applying an unary function
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#if ! (CGAL_TRANSFORM_ITERATOR_H)
#define CGAL_TRANSFORM_ITERATOR_H 1

#include <CGAL/Optimisation/assertions.h>
#include <CGAL/circulator_bases.h>
#include <iterator>

CGAL_BEGIN_NAMESPACE

template < class OutputIterator, class Operation >
struct Transform_iterator {
  typedef std::output_iterator_tag             iterator_category;
  typedef Transform_iterator< OutputIterator, Operation >   self;
  typedef typename Operation::argument_type        argument_type;

  Transform_iterator( const OutputIterator& o,
                      const Operation& op)
    : o_( o), op_( op)
  {}

  operator OutputIterator() { return o_; }

  self& operator*() { return *this; }

  self& operator++() { return *this; }

  self& operator++( int) { return *this; }

  self& operator=( const argument_type& a) {
    *(o_++) = op_( a);
    return *this;
  }

private:
  OutputIterator o_;
  Operation      op_;
};

template < class OutputIterator, class Operation > inline
Transform_iterator< OutputIterator, Operation >
transform_iterator( const OutputIterator& o,
                         const Operation& op)
{ return Transform_iterator< OutputIterator, Operation >( o, op); }

template < class OutputIterator, class Operation > inline
Iterator_tag
query_circulator_or_iterator(
  const Transform_iterator< OutputIterator, Operation >&)
{ return Iterator_tag(); }

CGAL_END_NAMESPACE

#endif // ! (CGAL_TRANSFORM_ITERATOR_H)
// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

