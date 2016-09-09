// ============================================================================
//
// Copyright (c) 1998, 1999, 2000 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// This file is part of an example program for CGAL.  This example
// program may be used, distributed and modified without limitation.

// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : examples/Matrix_search/all_furthest_neighbors_2_example.C
// chapter       : $CGAL_Chapter: Geometric Optimisation $
// package       : $CGAL_Package: Matrix_search $
// source        : mon_search.aw
// revision      : $Revision: 1.52 $
// revision_date : $Date: 2002/03/25 15:04:51 $
// author(s)     : Michael Hoffmann
//
// coordinator   : ETH
//
// Example program: All Furthest Neighbors for a Convex Polygon
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#include <CGAL/Cartesian.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/random_convex_set_2.h>
#include <CGAL/all_furthest_neighbors_2.h>
#include <CGAL/IO/Ostream_iterator.h>
#include <iostream>
#include <vector>

using namespace std;
using CGAL::random_convex_set_2;
using CGAL::all_furthest_neighbors_2;

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
  all_furthest_neighbors_2(
    p.vertices_begin(),
    p.vertices_end(),
    Oiterator( cout));
  cout << endl;

  return 0;
} 
// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

