// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/all_furthest_neighbors_2.h
// package       : Matrix_search (1.17)
// chapter       : $CGAL_Chapter: Geometric Optimisation $
// source        : mon_search.aw
// revision      : $Revision: 1.17 $
// revision_date : $Date: 1999/06/01 14:08:11 $
// author(s)     : Michael Hoffmann
//
// coordinator   : ETH Zurich (Bernd Gaertner)
//
// Compute all furthest neighbors for the vertices of a convex polygon
// email         : cgal@cs.uu.nl
//
// ======================================================================

#if ! (ALL_FURTHEST_NEIGHBORS_2_H)
#define ALL_FURTHEST_NEIGHBORS_2_H 1

#ifndef CGAL_OPTIMISATION_ASSERTIONS_H
#include <CGAL/optimisation_assertions.h>
#endif // CGAL_OPTIMISATION_ASSERTIONS_H

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
#ifndef CGAL_PROTECT_FUNCTIONAL
#include <functional>
#define CGAL_PROTECT_FUNCTIONAL
#endif
#ifndef CGAL_PROTECT_ALGORITHM
#include <algorithm>
#define CGAL_PROTECT_ALGORITHM
#endif

CGAL_BEGIN_NAMESPACE
template < class Operation, class RandomAccessIC >
class All_furthest_neighbor_matrix
: public Cartesian_matrix< Operation, RandomAccessIC, RandomAccessIC >
// represents the matrix used for computing
// all furthest neighbors of a convex polygon
{
public:
  typedef
    Cartesian_matrix< Operation, RandomAccessIC, RandomAccessIC >
  BaseClass;

  All_furthest_neighbor_matrix( RandomAccessIC f,
                                RandomAccessIC l)
  : BaseClass( f, l, f, l)
  {}

  int
  number_of_columns() const
  { return 2 * number_of_rows() - 1; }

  Value
  operator()( int r, int c) const
  {
    CGAL_optimisation_precondition( r >= 0 && r < number_of_rows());
    CGAL_optimisation_precondition( c >= 0 && c < number_of_columns());
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

CGAL_END_NAMESPACE
#ifndef CGAL_PROTECT_ITERATOR
#include <iterator>
#define CGAL_PROTECT_ITERATOR
#endif
CGAL_BEGIN_NAMESPACE

template < class RandomAccessIC, class OutputIterator, class Traits >
inline
OutputIterator
all_furthest_neighbors( RandomAccessIC points_begin,
                        RandomAccessIC points_end,
                        OutputIterator o,
                        const Traits& t)
{
  return
  all_furthest_neighbors(
    points_begin,
    points_end,
    o,
    t,
    std::iterator_traits< OutputIterator >::iterator_category());
} // all_furthest_neighbors( ... )

template < class RandomAccessIC,
           class OutputIterator,
           class Traits >
OutputIterator
all_furthest_neighbors( RandomAccessIC points_begin,
                        RandomAccessIC points_end,
                        OutputIterator o,
                        const Traits& t,
                        std::random_access_iterator_tag)
{
  typedef All_furthest_neighbor_matrix<
    typename Traits::Distance,
    RandomAccessIC
    >
  Afn_matrix;

  // check preconditions:
  int number_of_points(
    iterator_distance( points_begin, points_end));
  CGAL_optimisation_precondition( number_of_points > 0);
  CGAL_optimisation_expensive_precondition(
    t.is_convex( points_begin, points_end));

  // compute maxima:
  monotone_matrix_search(
    dynamic_matrix(
      Afn_matrix( points_begin, points_end)),
    o);

  return o + number_of_points;
} // all_furthest_neighbors( ... )

template < class RandomAccessIC,
           class OutputIterator,
           class Traits,
           class IteratorCategory >
OutputIterator
all_furthest_neighbors( RandomAccessIC points_begin,
                        RandomAccessIC points_end,
                        OutputIterator o,
                        const Traits& t,
                        IteratorCategory)
#else
template < class RandomAccessIC,
           class OutputIterator,
           class Traits >
OutputIterator
all_furthest_neighbors( RandomAccessIC points_begin,
                        RandomAccessIC points_end,
                        OutputIterator o,
                        const Traits& t)
#endif
{
#ifndef CGAL_CFG_NO_NAMESPACE
  using std::vector;
  using std::transform;
  using std::bind2nd;
  using std::modulus;
#endif

  typedef All_furthest_neighbor_matrix<
    typename Traits::Distance,
    RandomAccessIC
    >
  Afn_matrix;

 // check preconditions:
  int number_of_points(
    iterator_distance( points_begin, points_end));
  CGAL_optimisation_precondition( number_of_points > 0);
  CGAL_optimisation_expensive_precondition(
    t.is_convex( points_begin, points_end));

  // prepare random access container:
  //vector< int > v( number_of_points, 0);
  vector< int > v;
  v.reserve( number_of_points);
  for (int i = 0; i < number_of_points; ++i)
    v.push_back( 0);

  // compute maxima:
  monotone_matrix_search(
    dynamic_matrix(
      Afn_matrix( points_begin, points_end)),
    v.begin());

  // output result:
  return transform( v.begin(),
                    v.end(),
                    o,
                    bind2nd( modulus< int >(), number_of_points));
} // all_furthest_neighbors( ... )

CGAL_END_NAMESPACE

#endif // ! (ALL_FURTHEST_NEIGHBORS_2_H)

// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

