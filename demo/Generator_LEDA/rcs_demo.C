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
// file          : demo/Random/rcs_demo.C
// package       : $CGAL_Package: Generator 2.10 (26 May 1999) $
// source        : src/rcs/rcs.aw
// revision      : $Revision: 1.2 $
// revision_date : $Date: 1998/03/06 16:19:47 $
// author(s)     : Michael Hoffmann
//
// coordinator   : ETH Zurich (Bernd Gaertner)
//
// Random Convex Point Sets: Demo Program
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
#ifndef RANDOM_CONVEX_SETS_2_H
#include <CGAL/random_convex_set_2.h>
#endif // RANDOM_CONVEX_SETS_2_H
#ifndef CGAL_PROTECT_VECTOR
#include <vector>
#define CGAL_PROTECT_VECTOR
#endif
#ifndef CGAL_PROTECT_IOSTREAM
#include <iostream>
#define CGAL_PROTECT_IOSTREAM
#endif
#ifndef CGAL_PROTECT_CSTDLIB
#include <cstdlib>
#define CGAL_PROTECT_CSTDLIB
#endif
#ifdef CGAL_USE_LEDA
#ifndef CGAL_IO_WINDOW_STREAM_H
#include <CGAL/IO/Window_stream.h>
#endif // CGAL_IO_WINDOW_STREAM_H
#endif // CGAL_USE_LEDA

using CGAL::cgalize;

using std::vector;
using std::back_inserter;
using CGAL::Cartesian;
using CGAL::Polygon_traits_2;
using CGAL::Creator_uniform_2;
using CGAL::Random_points_in_square_2;
using CGAL::set_pretty_mode;
using CGAL::random_convex_set_2;

int
main( int argc, char* argv[])
{
  typedef Cartesian< double >                            R;
  typedef CGAL::Point_2< R >                             Point_2;
  typedef Polygon_traits_2< R >                          P_traits;
  typedef vector< Point_2 >                              Cont;
  typedef CGAL::Polygon_2< P_traits, Cont >              Polygon_2;
  typedef Creator_uniform_2< double, Point_2 >           Creator;
  typedef Random_points_in_square_2< Point_2, Creator >  Point_generator;
  
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
  Point_2 tmp_p;
  W >> tmp_p;
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

// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

