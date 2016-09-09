// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium

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
//
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : include/CGAL/Transform_iterator.h
// package       : Matrix_search (1.30)
// chapter       : $CGAL_Chapter: Geometric Optimisation $
// source        : mon_search.aw
// revision      : $Revision: 1.30 $
// revision_date : $Date: 1999/12/17 11:58:48 $
// author(s)     : Michael Hoffmann
//
// coordinator   : ETH Zurich (Bernd Gaertner)
//
// An OutputIterator Adaptor applying an unary function
// email         : cgal@cs.uu.nl
//
// ======================================================================

#if ! (CGAL_TRANSFORM_ITERATOR_H)
#define CGAL_TRANSFORM_ITERATOR_H 1

#include <CGAL/Optimisation/assertions.h>
#include <CGAL/circulator_bases.h>
#include <iterator>

CGAL_BEGIN_NAMESPACE

template < class OutputIterator, class Operation >
class Transform_iterator : public CGAL_STD::output_iterator {
public:
  typedef Transform_iterator< OutputIterator, Operation >
    self;
  typedef typename Operation::argument_type
    argument_type;

  Transform_iterator( const OutputIterator& o,
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
Transform_iterator< OutputIterator, Operation >
transform_iterator( const OutputIterator& o,
                         const Operation& op)
{ return Transform_iterator< OutputIterator, Operation >( o, op); }

template < class OutputIterator, class Operation > inline
std::output_iterator_tag
iterator_category(
  const Transform_iterator< OutputIterator, Operation >&)
{ return output_iterator_tag(); }

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

