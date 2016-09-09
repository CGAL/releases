// ============================================================================
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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : all_furthest_neighbors_2_demo.C
// chapter       : $CGAL_Chapter: Geometric Optimisation $
// package       : $CGAL_Package: Matrix_search $
// source        : mon_search.aw
// revision      : $Revision: 1.10 $
// revision_date : $Date: 1998/11/26 16:24:47 $
// author(s)     : Michael Hoffmann
//
// coordinator   : ETH Zurich (Bernd Gaertner)
//
// Demo program: All Furthest Neighbors for a Convex Polygon
//
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
#ifndef CGAL_PROTECT_VECTOR_H
#include <vector.h>
#define CGAL_PROTECT_VECTOR_H
#endif // CGAL_PROTECT_VECTOR_H
#ifndef CGAL_SQUARED_DISTANCE_2_H
#include <CGAL/squared_distance_2.h>
#endif // CGAL_SQUARED_DISTANCE_2_H
#ifndef CGAL_IO_WINDOW_STREAM_H
#include <CGAL/IO/Window_stream.h>
#endif // CGAL_IO_WINDOW_STREAM_H
#ifndef CGAL_PROTECT_LEDA_POINT_SET_H
#include <LEDA/point_set.h>
#define CGAL_PROTECT_LEDA_POINT_SET_H
#endif // CGAL_PROTECT_LEDA_POINT_SET_H
#ifndef CGAL_PROTECT_IOSTREAM_H
#include <iostream.h>
#define CGAL_PROTECT_IOSTREAM_H
#endif // CGAL_PROTECT_IOSTREAM_H

typedef double                                 FT;
typedef CGAL_Cartesian< FT >                   R;
typedef CGAL_Point_2< R >                      Point_2;
typedef CGAL_Polygon_traits_2< R >             P_traits;
typedef vector< Point_2 >                      Point_cont;
typedef vector< int >                          Index_cont;
typedef CGAL_Polygon_2< P_traits, Point_cont > Polygon_2;
typedef CGAL_Random_points_in_square_2<
  Point_2,
  CGAL_Creator_uniform_2< FT, Point_2 > >
Point_generator;
#include <LEDA/REDEFINE_NAMES.h>
typedef point                              LEDA_Point;
typedef point_set< Point_2 >               LEDA_Point_set_Point;
#include <LEDA/UNDEFINE_NAMES.h>
void
wait_for_button_release( leda_window& W)
{
  // wait until mouse button is released
  double x, y;
  int v;
  do {}
  while ( W.read_event( v, x, y) != button_release_event);
}

int
main()
{
  leda_window W;
  W.init( -1.25, 1.25, -1.25);
  W.display();

  // get points, last point with middle button:
  cout << "\nCGAL ALL FURTHEST NEIGHBORS DEMO\n"
       << "================================\n\n"
       << " compute all points furthest neighbors\n"
       << " for the vertices of a convex polygon\n\n"
       << " < click left mouse button to get the furthest"
       << " neighbor of a vertex >\n"
       << " < click any other mouse button to quit >\n"
       << endl;
  int number_of_points( 30);
  // generate random convex polygon:
  Polygon_2 p;
  CGAL_random_convex_set_2( number_of_points,
                            back_inserter( p),
                            Point_generator( 1));
  W << CGAL_RED << p;
  // compute all furthest neighbors:
  Index_cont neighbors;
  CGAL_all_furthest_neighbors(
    p.vertices_begin(),
    p.vertices_end(),
    back_inserter( neighbors));
  // output solution:
  LEDA_Point_set_Point query_points;
  for ( int k( 0); k < p.size(); ++k)
    query_points.insert(
      LEDA_Point( p[k].x(), p[k].y()),
      p[neighbors[k]]);
  
  W.set_mode( leda_xor_mode);
  W.set_fg_color( leda_blue);
  ps_item qp;
  // first click, no need to clear old query from screen:
  int last_button;
  {
    double x, y;
    last_button = W.read_mouse( x, y);
    qp = query_points.nearest_neighbor( LEDA_Point( x, y));
  }
  for (;;) {
    double x, y;
    if ( last_button != MOUSE_BUTTON( 1))
      break;
    W.draw_disc( query_points.key( qp), .02);
    W.draw_disc( query_points.inf( qp).x(),
                 query_points.inf( qp).y(),
                 .03);
    last_button = W.read_mouse( x, y);
    W.draw_disc( query_points.key( qp), .02);
    W.draw_disc( query_points.inf( qp).x(),
                 query_points.inf( qp).y(),
                 .03);
    qp = query_points.nearest_neighbor( LEDA_Point( x, y));
  }
  
  wait_for_button_release( W);

} // int main()
// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

