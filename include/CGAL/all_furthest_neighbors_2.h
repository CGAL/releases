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
// file          : include/CGAL/all_furthest_neighbors_2.h
// author(s)     : Michael Hoffmann 
//
// email         : cgal@cs.uu.nl
//
// ============================================================================

#if ! (CGAL_ALL_FURTHEST_NEIGHBORS_2_H)
#define CGAL_ALL_FURTHEST_NEIGHBORS_2_H 1

#ifdef CGAL_REP_CLASS_DEFINED
#ifndef CGAL_ALL_FURTHEST_NEIGHBORS_TRAITS_2_H
#include <CGAL/All_furthest_neighbors_traits_2.h>
#endif // CGAL_ALL_FURTHEST_NEIGHBORS_TRAITS_2_H
#endif // CGAL_REP_CLASS_DEFINED

#ifndef CGAL_CARTESIAN_MATRIX_H
#include <CGAL/Cartesian_matrix.h>
#endif // CGAL_CARTESIAN_MATRIX_H
#ifndef CGAL_DYNAMIC_MATRIX_H
#include <CGAL/Dynamic_matrix.h>
#endif // CGAL_DYNAMIC_MATRIX_H
#ifndef CGAL_MONOTONE_MATRIX_SEARCH_H
#include <CGAL/monotone_matrix_search.h>
#endif // CGAL_MONOTONE_MATRIX_SEARCH_H
#ifndef CGAL_PROTECT_FUNCTION_H
#include <function.h>
#define CGAL_PROTECT_FUNCTION_H
#endif // CGAL_PROTECT_FUNCTION_H
#ifndef CGAL_PROTECT_ALGO_H
#include <algo.h>
#define CGAL_PROTECT_ALGO_H
#endif // CGAL_PROTECT_ALGO_H

template < class Operation, class RandomAccessIC >
class CGAL__All_furthest_neighbor_matrix
: public CGAL_Cartesian_matrix< Operation,
                                RandomAccessIC,
                                RandomAccessIC >
// represents the matrix used for computing
// all furthest neighbors of a convex polygon
{
public:
  typedef
    CGAL_Cartesian_matrix< Operation, RandomAccessIC, RandomAccessIC >
  BaseClass;

  CGAL__All_furthest_neighbor_matrix( RandomAccessIC f,
                                      RandomAccessIC l)
  : BaseClass( f, l, f, l)
  {}

  int
  number_of_columns() const
  { return 2 * number_of_rows() - 1; }

  Value
  operator()( int r, int c) const
  {
    CGAL_precondition( r >= 0 && r < number_of_rows());
    CGAL_precondition( c >= 0 && c < number_of_columns());
    if ( c <= r)
      return Value( c - r);
    else if ( c >= r + number_of_rows())
      return Value( 0);
    else if ( c >= number_of_rows())
      return BaseClass::operator()( r, c - number_of_rows());
    else
      return BaseClass::operator()( r, c);
  }
};

#if !defined(CGAL_CFG_NO_ITERATOR_TRAITS) && \
!defined(CGAL_CFG_MATCHING_BUG_2)

#ifndef CGAL_PROTECT_ITERATOR_H
#include <iterator.h>
#define CGAL_PROTECT_ITERATOR_H
#endif // CGAL_PROTECT_ITERATOR_H

template < class RandomAccessIC, class OutputIterator, class Traits >
inline
OutputIterator
CGAL_all_furthest_neighbors( RandomAccessIC points_begin,
                             RandomAccessIC points_end,
                             OutputIterator o,
                             const Traits& t)
{
  return
  CGAL_all_furthest_neighbors(
    points_begin,
    points_end,
    o,
    t,
    iterator_traits< OutputIterator >::iterator_category());
} // CGAL_all_furthest_neighbors( ... )

template < class RandomAccessIC,
           class OutputIterator,
           class Traits >
OutputIterator
CGAL_all_furthest_neighbors( RandomAccessIC points_begin,
                             RandomAccessIC points_end,
                             OutputIterator o,
                             const Traits& t,
                             random_access_iterator_tag)
{
  typedef CGAL__All_furthest_neighbor_matrix<
    typename Traits::Distance,
    RandomAccessIC
    >
  Afn_matrix;

  // check preconditions:
  int number_of_points(
    CGAL_iterator_distance( points_begin, points_end));
  CGAL_precondition( number_of_points > 0);
  CGAL_expensive_precondition(
    t.is_convex( points_begin, points_end));

  // compute maxima:
  CGAL_monotone_matrix_search(
    CGAL_dynamic_matrix(
      Afn_matrix( points_begin, points_end)),
    o);

  return o + number_of_points;
} // CGAL_all_furthest_neighbors( ... )

template < class RandomAccessIC,
           class OutputIterator,
           class Traits,
           class IteratorCategory >
OutputIterator
CGAL_all_furthest_neighbors( RandomAccessIC points_begin,
                             RandomAccessIC points_end,
                             OutputIterator o,
                             const Traits& t,
                             IteratorCategory)
#else
template < class RandomAccessIC,
           class OutputIterator,
           class Traits >
OutputIterator
CGAL_all_furthest_neighbors( RandomAccessIC points_begin,
                             RandomAccessIC points_end,
                             OutputIterator o,
                             const Traits& t)
#endif
{
  typedef CGAL__All_furthest_neighbor_matrix<
    typename Traits::Distance,
    RandomAccessIC
    >
  Afn_matrix;

 // check preconditions:
  int number_of_points(
    CGAL_iterator_distance( points_begin, points_end));
  CGAL_precondition( number_of_points > 0);
  CGAL_expensive_precondition(
    t.is_convex( points_begin, points_end));

  // prepare random access container:
  vector< int > v( number_of_points);

  // compute maxima:
  CGAL_monotone_matrix_search(
    CGAL_dynamic_matrix(
      Afn_matrix( points_begin, points_end)),
    v.begin());

  // output result:
  return transform( v.begin(),
                    v.end(),
                    o,
                    bind2nd( modulus< int >(), number_of_points));
} // CGAL_all_furthest_neighbors( ... )

#endif // ! (CGAL_ALL_FURTHEST_NEIGHBORS_2_H)

// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

