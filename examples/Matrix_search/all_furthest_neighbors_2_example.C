// ============================================================================
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
// file          : all_furthest_neighbors_2_example.C
// chapter       : $CGAL_Chapter: Geometric Optimisation $
// package       : $CGAL_Package: Matrix_search $
// source        : mon_search.aw
// revision      : $Revision: 1.17 $
// revision_date : $Date: 1999/06/01 14:07:44 $
// author(s)     : Michael Hoffmann
//
// coordinator   : ETH Zurich (Bernd Gaertner)
//
// Example program: All Furthest Neighbors for a Convex Polygon
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_CARTESIAN_H
#include <CGAL/Cartesian.h>
#endif // CGAL_CARTESIAN_H
#ifndef CGAL_POINT_2_H
#include <CGAL/Point_2.h>
#endif // CGAL_POINT_2_H
#ifndef CGAL_POLYGON_2_H
#include <CGAL/Polygon_2.h>
#endif // CGAL_POLYGON_2_H
#ifndef CGAL_POINT_GENERATORS_2_H
#include <CGAL/point_generators_2.h>
#endif // CGAL_POINT_GENERATORS_2_H
#ifndef CGAL_RANDOM_CONVEX_SET_2_H
#include <CGAL/random_convex_set_2.h>
#endif // CGAL_RANDOM_CONVEX_SET_2_H
#ifndef CGAL_ALL_FURTHEST_NEIGHBORS_2_H
#include <CGAL/all_furthest_neighbors_2.h>
#endif // CGAL_ALL_FURTHEST_NEIGHBORS_2_H
#ifndef CGAL_IO_OSTREAM_ITERATOR_H
#include <CGAL/IO/Ostream_iterator.h>
#endif // CGAL_IO_OSTREAM_ITERATOR_H
#include <iostream>
#include <vector>

using namespace std;
using CGAL::random_convex_set_2;
using CGAL::all_furthest_neighbors;

typedef double                                   FT;
typedef CGAL::Cartesian< FT >                    R;
typedef CGAL::Point_2< R >                       Point;
typedef CGAL::Polygon_traits_2< R >              P_traits;
typedef vector< Point >                          Point_cont;
typedef CGAL::Polygon_2< P_traits, Point_cont >  Polygon;
typedef CGAL::Creator_uniform_2< FT, Point >     Creator;
typedef CGAL::Random_points_in_square_2< Point, Creator >
  Point_generator;
typedef CGAL::Ostream_iterator< int, ostream >   Oiterator;

int
main()
{
  // generate random convex polygon:
  Polygon p;
  random_convex_set_2( 10, back_inserter( p), Point_generator( 1));

  // compute all furthest neighbors:
  all_furthest_neighbors(
    p.vertices_begin(),
    p.vertices_end(),
    Oiterator( cout));
  cout << endl;
} 
// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

