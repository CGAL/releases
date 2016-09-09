// Copyright (c) 1998-2003  ETH Zurich (Switzerland).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source: /CVSROOT/CGAL/Packages/Matrix_search/include/CGAL/Transform_iterator.h,v $
// $Revision: 1.58 $ $Date: 2003/09/29 08:41:45 $
// $Name: current_submission $
//
// Author(s)     : Michael Hoffmann <hoffmann@inf.ethz.ch>

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

