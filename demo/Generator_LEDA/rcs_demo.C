// ============================================================================
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
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : demo/Generator_LEDA/random_polys_demo.C
// package       : $CGAL_Package: Generator 2.12 (28 Jul 1999) $
// source        : src/rcs/rcs.aw
// revision      : $Revision: 1.2 $
// revision_date : $Date: 1998/03/06 16:19:47 $
// author(s)     : Michael Hoffmann
//
// coordinator   : ETH Zurich (Bernd Gaertner)
//
// Random Convex Point Sets: Demo Program
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#include <CGAL/basic.h>
#ifndef CGAL_USE_LEDA
int main() { std::cout << "\nSorry, this demo needs LEDA\n"; return 0; }
#else
#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/random_convex_set_2.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <CGAL/IO/Window_stream.h>

using CGAL::cgalize;

using std::cout;
using std::cerr;
using std::endl;
using std::flush;
using std::vector;
using std::back_inserter;
using CGAL::Cartesian;
using CGAL::Polygon_traits_2;
using CGAL::Creator_uniform_2;
using CGAL::Random_points_in_square_2;
using CGAL::set_pretty_mode;
using CGAL::random_convex_set_2;

typedef Cartesian< double >                          R;
typedef CGAL::Point_2< R >                           Point;
typedef Polygon_traits_2< R >                        P_traits;
typedef vector< Point >                              Cont;
typedef CGAL::Polygon_2< P_traits, Cont >            Polygon_2;
typedef Creator_uniform_2< double, Point >           Creator;
typedef Random_points_in_square_2< Point, Creator >  Point_generator;

int
main( int argc, char* argv[])
{
  
  // this is not initialized on MIPSPRO:
  set_pretty_mode( cout);
  set_pretty_mode( cerr);

  // take #points from command line:
  int n;
  if ( argc < 2 || (n = atoi( argv[1])) < 3) {
    cerr << "usage: " << argv[0] << " \"#points\" (>= 3)" << endl;
    return 1;
  }

  cout << "Test random_convex_set_2:\n" << endl;

  // build random n-gon:
  cout << "constructing random " << n << "-gon ..." << flush;
  Polygon_2 p;
  random_convex_set_2( n, back_inserter( p), Point_generator( 1));
  cout << " done." << endl;

  // output polygon:
  cout << "\nHere is the result:" << endl;

#ifdef CGAL_USE_LEDA
  leda_window W;
  cgalize( W);
  W.display();
  W.init( -1.05, 1.05, -1.05);
  W << p;

  // wait for mouse-click:
  W.read_mouse();
#else
  cout << p << endl;
#endif

  // check convexity:
  if ( ! p.is_convex()) {
    cerr << "ERROR: polygon is not convex." << endl;
    return 1;
  }

  cout << "done." << endl;
  return 0;
} // int main( argc, argv)

#endif // CGAL_USE_LEDA
// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

