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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.1
// release_date  : 1998, July 24
//
// file          : include/CGAL/random_convex_set_2.h
// package       : Random (1.12)
// source        : src/rcs/rcs.aw
// revision      : $Revision: 1.2 $
// revision_date : $Date: 1998/03/06 16:19:47 $
// author(s)     : Michael Hoffmann
//
// coordinator   : ETH Zurich (Bernd Gaertner)
//
// Random Convex Point Sets
// email         : cgal@cs.uu.nl
//
// ======================================================================

#if ! (CGAL_RANDOM_CONVEX_SET_2_H)
#define CGAL_RANDOM_CONVEX_SET_2_H 1

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif
#ifndef CGAL_PROTECT_VECTOR_H
#include <vector.h>
#define CGAL_PROTECT_VECTOR_H
#endif
#ifndef CGAL_PROTECT_ALGO_H
#include <algo.h>
#define CGAL_PROTECT_ALGO_H
#endif
#ifdef CGAL_REP_CLASS_DEFINED
#ifndef CGAL_RANDOM_CONVEX_SET_TRAITS_2_H
#include <CGAL/Random_convex_set_traits_2.h>
#endif
#endif

template < class OutputIterator, class Point_generator, class Traits >
OutputIterator
CGAL_random_convex_set_2( int n,
                          OutputIterator o,
                          const Point_generator& pg,
                          Traits t)
{
  CGAL_precondition( n >= 3);

  typedef typename Traits::Point_2         Point_2;
  typedef typename Traits::FT              FT;
  typedef vector< Point_2 >                Container;
  typedef typename Traits::Sum             Sum;
  typedef typename Traits::Scale           Scale;
  typedef typename Traits::Angle_less      Angle_less;
  typedef typename Traits::Max_coordinate  Max_coordinate;

  // GCC 2.8 and egcs-1.0.1 require these:
  // (does not accept s.l. Scale()( p, 1))
  Scale scale;
  Max_coordinate max_coordinate;
  Sum sum;

  // build random point set:
  Container points;
  points.reserve( n);
  CGAL_copy_n( pg, n, back_inserter( points));

  // compute centroid of points:
  Point_2 centroid(
    scale(
      accumulate( points.begin(), points.end(), t.origin(), Sum()),
      FT( 1) / FT( n)));

  // translate s.t. centroid == origin:
  transform(
    points.begin(),
    points.end(),
    points.begin(),
    bind2nd( Sum(), scale( centroid, FT( -1))));

  // sort them according to their direction's angle
  // w.r.t. the positive x-axis:
  sort( points.begin(), points.end(), Angle_less());

  // construct polygon:
  partial_sum(
    points.begin(), points.end(), points.begin(), Sum());

  // and compute its centroid:
  Point_2 new_centroid(
    scale(
      accumulate( points.begin(), points.end(), t.origin(), Sum()),
      FT( 1) / FT( n)));

  // translate s.t. centroids match:
  transform(
    points.begin(),
    points.end(),
    points.begin(),
    bind2nd( Sum(), sum( centroid,
                         scale( new_centroid, FT( -1)))));

  // compute maximal coordinate:
  FT maxcoord( max_coordinate(
    *max_element( points.begin(),
                  points.end(),
                  CGAL_compose2_2( less< FT >(),
                                   Max_coordinate(),
                                   Max_coordinate()))));

  // and finally scale to fit into original grid:
  return transform(
    points.begin(),
    points.end(),
    o,
    bind2nd( Scale(), FT( pg.range()) / maxcoord));

} // CGAL_random_convex_set_2( n, o, pg, t)

#endif // ! (CGAL_RANDOM_CONVEX_SET_2_H)

// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

