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
// file          : include/CGAL/all_furthest_neighbors_2.h
// package       : Matrix_search (1.30)
// chapter       : $CGAL_Chapter: Geometric Optimisation $
// source        : mon_search.aw
// revision      : $Revision: 1.30 $
// revision_date : $Date: 1999/12/17 11:58:48 $
// author(s)     : Michael Hoffmann
//
// coordinator   : ETH Zurich (Bernd Gaertner)
//
// Compute all furthest neighbors for the vertices of a convex polygon
// email         : cgal@cs.uu.nl
//
// ======================================================================

#if ! (CGAL_ALL_FURTHEST_NEIGHBORS_2_H)
#define CGAL_ALL_FURTHEST_NEIGHBORS_2_H 1

#include <CGAL/Optimisation/assertions.h>

#ifdef CGAL_REP_CLASS_DEFINED
#include <CGAL/All_furthest_neighbors_traits_2.h>
#endif // CGAL_REP_CLASS_DEFINED

#include <CGAL/Cartesian_matrix.h>
#include <CGAL/Dynamic_matrix.h>
#include <CGAL/monotone_matrix_search.h>
#include <functional>
#include <algorithm>

CGAL_BEGIN_NAMESPACE
#ifdef _MSC_VER
// that compiler cannot even distinguish between global
// and class scope, so ...
#define Base B_B_Base
#endif // _MSC_VER

template < class Operation, class RandomAccessIC >
class All_furthest_neighbor_matrix
: public Cartesian_matrix< Operation, RandomAccessIC, RandomAccessIC >
// represents the matrix used for computing
// all furthest neighbors of a convex polygon
{
public:
  typedef
    Cartesian_matrix< Operation, RandomAccessIC, RandomAccessIC >
  Base;

  All_furthest_neighbor_matrix( RandomAccessIC f,
                                RandomAccessIC l)
  : Base( f, l, f, l)
  {}

  int
  number_of_columns() const
  { return 2 * number_of_rows() - 1; }

  typename Base::Value
  operator()( int r, int c) const
  {
    CGAL_optimisation_precondition( r >= 0 && r < number_of_rows());
    CGAL_optimisation_precondition( c >= 0 && c < number_of_columns());
    if ( c <= r)
      return Value( c - r);
    else if ( c >= r + number_of_rows())
      return Value( 0);
    else if ( c >= number_of_rows())
      return Base::operator()( r, c - number_of_rows());
    else
      return Base::operator()( r, c);
  }
};

#ifdef _MSC_VER
#undef Base
#endif // _MSC_VER

#if !defined(CGAL_CFG_NO_ITERATOR_TRAITS) && \
!defined(CGAL_CFG_MATCHING_BUG_2)

CGAL_END_NAMESPACE
#include <iterator>
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
#ifndef CGAL_CFG_TYPENAME_BUG
  typedef All_furthest_neighbor_matrix< typename Traits::Distance,
                                        RandomAccessIC >
  Afn_matrix;
#else
  typedef All_furthest_neighbor_matrix< Traits::Distance, RandomAccessIC >
    Afn_matrix;
#endif // CGAL_CFG_TYPENAME_BUG

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

#ifndef CGAL_CFG_TYPENAME_BUG
  typedef All_furthest_neighbor_matrix< typename Traits::Distance,
                                        RandomAccessIC >
  Afn_matrix;
#else
  typedef All_furthest_neighbor_matrix< Traits::Distance, RandomAccessIC >
    Afn_matrix;
#endif // CGAL_CFG_TYPENAME_BUG

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

#endif // ! (CGAL_ALL_FURTHEST_NEIGHBORS_2_H)

// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

