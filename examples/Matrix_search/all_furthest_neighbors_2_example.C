// ============================================================================
//
// Copyright (c) 1998, 1999, 2000 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
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
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : examples/Matrix_search/all_furthest_neighbors_2_example.C
// chapter       : $CGAL_Chapter: Geometric Optimisation $
// package       : $CGAL_Package: Matrix_search $
// source        : mon_search.aw
// revision      : $Revision: 1.47 $
// revision_date : $Date: 2001/07/12 07:17:50 $
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

