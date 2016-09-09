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
// file          : demo/Optimisation/demo_Min_ellipse_2.C
// chapter       : $CGAL_Chapter: Geometric Optimisation $
// package       : $CGAL_Package: Min_ellipse_2 3.2.3 (20 May 1999) $
//
// revision      : $Revision: 5.2 $
// revision_date : $Date: 1999/02/25 17:01:48 $
// author(s)     : Sven Schönherr
//
// coordinator   : ETH Zürich (Bernd Gärtner)
//
// demo program  : 2D Smallest Enclosing Ellipse
// email         : cgal@cs.uu.nl
//
// ======================================================================

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// NOTE: In this release correct results are only guaranteed if exact
// arithmetic is used, so this demo (using inexact floating-point
// arithmetic) is only intended to illustrate the techniques. However,
// the program will terminate, but the computed ellipse may neither
// contain all points nor be the smallest one.
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// includes
#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/Min_ellipse_2.h>
#include <CGAL/Min_ellipse_2_traits_2.h>
#include <CGAL/IO/Window_stream.h>

using namespace CGAL;

// typedefs
typedef  Cartesian< double >          R;
typedef  Point_2< R >                 Point;
typedef  Min_ellipse_2_traits_2< R >  Traits;
typedef  Min_ellipse_2< Traits >      Min_ellipse;

// main
int
main( int, char**)
{
    cerr << "  left button: insert point" << endl;
    cerr << "middle button: clear points" << endl;
    cerr << " right button: exit"         << endl;

    // create empty min_ellipse;
    Min_ellipse  me;

    // open window
    Window_stream ws( "CGAL Demo: Smallest Enclosing Ellipse in 2D");
    ws.set_icon_label("CGAL");
    ws.set_icon_pixrect( ws.create_pixrect( esprit_logo));
    ws.set_node_width( 5);
    ws.init( -100.0, 100.0, -100.0);
    ws.display();

    // main loop
    double  x, y;
    int     button, i;
    do {
	// get mouse click
	button = ws.read_mouse( x, y);

	switch ( button) {

	  case MOUSE_BUTTON( 1):                        // left button
	    ws << WHITE << me.ellipse();
	    me.insert( ::Point( x, y));
	    ws << BLACK << me;
	    ws << BLUE  << me.ellipse();
	    ws << RED;
	    for ( i = 0; i < me.number_of_support_points(); ++i)
		ws << me.support_point( i);
	    break;

	  case MOUSE_BUTTON( 2):                        // middle button
	    ws.clear();
	    me.clear();
	    break; } }

    while ( button != MOUSE_BUTTON( 3));                // right button

    return( 0);
}

// ===== EOF ==================================================================
