// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------------
//
// release       : $CGAL_Revision $
// release_date  : $CGAL_Date $
//
// file          : demo/Random/rcs_demo.C
// package       : $CGAL_Package: Random 1.9 (06 Mar 1998) $
// source        : src/rcs/rcs.aw
// revision      : $Revision: 1.2 $
// revision_date : $Date: 1998/03/06 16:19:47 $
// author(s)     : Michael Hoffmann <hoffmann@inf.ethz.ch>
//
// coordinator   : ETH Zurich (Bernd Gaertner <gaertner@inf.ethz.ch>)
//
// Random Convex Point Sets: Demo Program
// ============================================================================

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
#ifndef CGAL_RANDOM_CONVEX_SETS_2_H
#include <CGAL/random_convex_set_2.h>
#endif // CGAL_RANDOM_CONVEX_SETS_2_H
#ifndef CGAL_COPY_N_H
#include <CGAL/copy_n.h>
#endif // CGAL_COPY_N_H
#ifndef CGAL_PROTECT_VECTOR_H
#include <vector.h>
#define CGAL_PROTECT_VECTOR_H
#endif // CGAL_PROTECT_VECTOR_H
#ifndef CGAL_PROTECT_IOSTREAM_H
#include <iostream.h>
#define CGAL_PROTECT_IOSTREAM_H
#endif // CGAL_PROTECT_IOSTREAM_H
#ifndef CGAL_PROTECT_STDLIB_H
#include <stdlib.h>
#define CGAL_PROTECT_STDLIB_H
#endif // CGAL_PROTECT_STDLIB_H
#ifdef CGAL_USE_LEDA
#ifndef CGAL_IO_WINDOW_STREAM_H
#include <CGAL/IO/Window_stream.h>
#endif // CGAL_IO_WINDOW_STREAM_H
#endif // CGAL_USE_LEDA

int
main( int argc, char* argv[])
{
  typedef CGAL_Cartesian< double >          R;
  typedef CGAL_Point_2< R >                 Point_2;
  typedef CGAL_Polygon_traits_2< R >        P_traits;
  typedef vector< Point_2 >                 Cont;
  typedef CGAL_Polygon_2< P_traits, Cont >  Polygon_2;
  typedef CGAL_Random_points_in_square_2<
    Point_2,
    CGAL_Creator_uniform_2< double, Point_2 > >
  Point_generator;
  
  // this is not initialized on MIPSPRO:
  CGAL_set_pretty_mode( cout);
  CGAL_set_pretty_mode( cerr);

  // take #points from command line:
  int n;
  if ( argc < 1 || (n = atoi( argv[1])) < 3) {
    cerr << "usage: " << argv[0] << " \"#points\" (>= 3)" << endl;
    return 1;
  }

  cout << "Test CGAL_random_convex_set_2:\n" << endl;

  // build random n-gon:
  cout << "constructing random " << n << "-gon ..." << flush;
  Polygon_2 p;
  CGAL_random_convex_set_2( n,
                            back_inserter( p),
                            Point_generator( 1));
  cout << " done." << endl;

  // output polygon:
  cout << "\nHere is the result:" << endl;

#ifdef CGAL_USE_LEDA
  CGAL_Window_stream W;
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

