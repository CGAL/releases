// ============================================================================
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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/Transform_iterator.h
// author(s)     : Michael Hoffmann 
//
// email         : cgal@cs.uu.nl
//
// ============================================================================

#if ! (CGAL_TRANSFORM_ITERATOR_H)
#define CGAL_TRANSFORM_ITERATOR_H 1

#ifndef CGAL_CIRCULATOR_BASES_H
#include <CGAL/circulator_bases.h>
#endif // CGAL_CIRCULATOR_BASES_H
#ifndef CGAL_PROTECT_ITERATOR_H
#include <iterator.h>
#define CGAL_PROTECT_ITERATOR_H
#endif // CGAL_PROTECT_ITERATOR_H

template < class OutputIterator, class Operation >
class CGAL_Transform_iterator : public output_iterator {
public:
  typedef CGAL_Transform_iterator< OutputIterator, Operation >
    self;
  typedef typename Operation::argument_type
    argument_type;

  CGAL_Transform_iterator( const OutputIterator& o,
                           const Operation& op)
    : _o( o), _op( op)
  {}

  operator OutputIterator()
  { return _o; }

  self& operator*()
  { return *this; }

  self& operator++()
  { return *this; }

  self& operator++( int)
  { return *this; }

  self& operator=( const argument_type& a)
  {
    *(_o++) = _op( a);
    return *this;
  }

private:
  OutputIterator _o;
  Operation      _op;
};

template < class OutputIterator, class Operation > inline
CGAL_Transform_iterator< OutputIterator, Operation >
CGAL_transform_iterator( const OutputIterator& o,
                         const Operation& op)
{ return CGAL_Transform_iterator< OutputIterator, Operation >( o, op); }

template < class OutputIterator, class Operation > inline
output_iterator_tag
iterator_category(
  const CGAL_Transform_iterator< OutputIterator, Operation >&)
{ return output_iterator_tag(); }

template < class OutputIterator, class Operation > inline
CGAL_Iterator_tag
CGAL_query_circulator_or_iterator(
  const CGAL_Transform_iterator< OutputIterator, Operation >&)
{ return CGAL_Iterator_tag(); }    

#endif // ! (CGAL_TRANSFORM_ITERATOR_H)

// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

