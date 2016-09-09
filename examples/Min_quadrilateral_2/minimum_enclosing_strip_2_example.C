// ============================================================================
//
// Copyright (c) 1999, 2000 The CGAL Consortium

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
// file          : examples/Min_quadrilateral_2/minimum_enclosing_strip_2_example.C
// chapter       : $CGAL_Chapter: Geometric Optimisation $
// package       : $CGAL_Package: Min_quadrilaterals $
// source        : oops.aw
// revision      : $Revision: 1.23 $
// revision_date : $Date: 2002/03/22 09:48:18 $
// author(s)     : Michael Hoffmann and
//                 Emo Welzl
//
// coordinator   : ETH
//
// Example Program: Computing a minimum enclosing strip
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/random_convex_set_2.h>
#include <CGAL/min_quadrilateral_2.h>
#include <vector>
#include <iostream>

using CGAL::Random_points_in_square_2;
using CGAL::random_convex_set_2;
using CGAL::min_strip_2;
using std::back_inserter;
using std::cout;
using std::endl;

typedef CGAL::Cartesian< double >                      R;
typedef R::Point_2                                     Point_2;
typedef R::Line_2                                      Line_2;
typedef CGAL::Polygon_traits_2< R >                    P_traits;
typedef std::vector< Point_2 >                         Cont;
typedef CGAL::Polygon_2< P_traits, Cont >              Polygon_2;
typedef CGAL::Creator_uniform_2< double, Point_2 >     Creator;
typedef Random_points_in_square_2< Point_2, Creator >  Point_generator;

int main()
{
  // build a random convex 20-gon p
  Polygon_2 p;
  random_convex_set_2(20, back_inserter(p), Point_generator(1.0));
  cout << p << endl;

  // compute the minimal enclosing strip p_m of p
  Line_2 p_m[2];
  min_strip_2(p.vertices_begin(), p.vertices_end(), p_m);
  cout << p_m[0] << "\n" << p_m[1] << endl;

  return 0;
} 
// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

