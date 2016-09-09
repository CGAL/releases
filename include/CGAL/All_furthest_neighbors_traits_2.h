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
// file          : include/CGAL/All_furthest_neighbors_traits_2.h
// package       : Matrix_search (1.17)
// chapter       : $CGAL_Chapter: Geometric Optimisation $
// source        : mon_search.aw
// revision      : $Revision: 1.17 $
// revision_date : $Date: 1999/06/01 14:07:58 $
// author(s)     : Michael Hoffmann
//
// coordinator   : ETH Zurich (Bernd Gaertner)
//
// Compute all furthest neighbors for the vertices of a convex polygon
// email         : cgal@cs.uu.nl
//
// ======================================================================

#if ! (ALL_FURTHEST_NEIGHBORS_TRAITS_2_H)
#define ALL_FURTHEST_NEIGHBORS_TRAITS_2_H 1

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif // CGAL_BASIC_H
#ifndef CGAL_OPTIMISATION_ASSERTIONS_H
#include <CGAL/optimisation_assertions.h>
#endif // CGAL_OPTIMISATION_ASSERTIONS_H
//!!! this should go into function_objects.h
#ifndef CGAL_PROTECT_FUNCTIONAL
#include <functional>
#define CGAL_PROTECT_FUNCTIONAL
#endif
#ifndef CGAL_SQUARED_DISTANCE_2_H
#include <CGAL/squared_distance_2.h>
#endif // CGAL_SQUARED_DISTANCE_2_H

CGAL_BEGIN_NAMESPACE

template < class T1, class T2 >
struct Squared_distance
: public CGAL_STD::binary_function< T1, T2, typename T1::R::FT >
{
  typename T1::R::FT
  operator()( const T1& t1, const T2& t2) const
  { return squared_distance( t1, t2); }
};

CGAL_END_NAMESPACE
#ifdef CGAL_CFG_NO_MEMBER_TEMPLATES
#ifndef CGAL_PROTECT_VECTOR
#include <vector>
#define CGAL_PROTECT_VECTOR
#endif
#endif
CGAL_BEGIN_NAMESPACE

template < class _R >
class All_furthest_neighbors_traits {
public:
  typedef _R                                    R;
  typedef Point_2< R >                          Point_2;
  typedef Squared_distance< Point_2, Point_2 >  Distance;

#ifdef CGAL_CFG_NO_MEMBER_TEMPLATES
  typedef typename std::vector< Point_2 >::iterator
    RandomAccessIC;
  typedef typename std::vector< int >::reverse_iterator
    OutputIterator;
#endif

  #ifndef CGAL_CFG_NO_MEMBER_TEMPLATES
  template < class RandomAccessIC >
  #endif
  bool
  is_convex( RandomAccessIC points_begin,
             RandomAccessIC points_end) const
  // PRE: value_type of RandomAccessIC is Point_2
  // POST: return true, iff the points [ points_begin, points_end)
  //   form a convex chain.
  {
    typedef Polygon_traits_2< R >        P_traits;
    typedef vector< Point_2 >            Cont;
    typedef Polygon_2< P_traits, Cont >  Polygon_2;
  
    Polygon_2 p( points_begin, points_end);
    return p.is_convex();
  } // is_convex( points_begin, points_end)
};

template < class RandomAccessIC, class OutputIterator >
inline
OutputIterator
all_furthest_neighbors( RandomAccessIC points_begin,
                        RandomAccessIC points_end,
                        OutputIterator o)
{
  return
  _CGAL_all_furthest_neighbors(
    points_begin,
    points_end,
    o,
    std::value_type( points_begin));
} // all_furthest_neighbors( ... )

template < class RandomAccessIC,
           class OutputIterator,
           class R >
inline
OutputIterator
_CGAL_all_furthest_neighbors( RandomAccessIC points_begin,
                              RandomAccessIC points_end,
                              OutputIterator o,
                              Point_2< R >*)
{
  return
  all_furthest_neighbors(
    points_begin,
    points_end,
    o,
    All_furthest_neighbors_traits< R >());
} // _CGAL_all_furthest_neighbors( ... )

CGAL_END_NAMESPACE

#endif // ! (ALL_FURTHEST_NEIGHBORS_TRAITS_2_H)

// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

