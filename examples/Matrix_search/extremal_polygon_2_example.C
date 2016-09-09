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
// file          : examples/Matrix_search/extremal_polygon_2_example.C
// chapter       : $CGAL_Chapter: Geometric Optimisation $
// package       : $CGAL_Package: Matrix_search $
// source        : mon_search.aw
// revision      : $Revision: 1.52 $
// revision_date : $Date: 2002/03/25 15:04:51 $
// author(s)     : Michael Hoffmann
//
// coordinator   : ETH
//
// Example program: Compute extremal polygons of a convex polygon
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#include <CGAL/Cartesian.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/random_convex_set_2.h>
#include <CGAL/extremal_polygon_2.h>
#include <iostream>
#include <vector>

using namespace std;
using CGAL::random_convex_set_2;
using CGAL::maximum_area_inscribed_k_gon_2;

typedef double                                FT;
typedef CGAL::Cartesian< FT >                 K;
typedef K::Point_2                            Point;
typedef CGAL::Polygon_traits_2< K >           P_traits;
typedef vector< Point >                       Cont;
typedef CGAL::Polygon_2< P_traits, Cont >     Polygon;
typedef CGAL::Creator_uniform_2< FT, Point >  Creator;
typedef CGAL::Random_points_in_square_2< Point, Creator >
  Point_generator;

int main() {

  Polygon p;
  int number_of_points( 10);
  int k( 5);

  random_convex_set_2( number_of_points,
                       back_inserter( p),
                       Point_generator( 1));
  cout << "Generated Polygon:\n" << p << endl;

  Polygon k_gon;
  maximum_area_inscribed_k_gon_2(
    p.vertices_begin(),
    p.vertices_end(),
    k,
    back_inserter( k_gon));
  cout << "Maximum area " << k << "-gon:\n" << k_gon << endl;

  return 0;
} 
// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

