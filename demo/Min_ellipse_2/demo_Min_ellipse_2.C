// ============================================================================
//
// Copyright (c) 1997,1998,1999 The CGAL Consortium

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
// file          : demo/Optimisation/demo_Min_ellipse_2.C
// chapter       : $CGAL_Chapter: Geometric Optimisation $
// package       : $CGAL_Package: Min_ellipse_2 3.10.2 (29 Sep 2000) $
//
// revision      : $Revision: 5.4 $
// revision_date : $Date: 2000/07/27 12:17:00 $
// author(s)     : Sven Schönherr
//
// coordinator   : ETH Zürich (Bernd Gärtner)
//
// demo program  : 2D Smallest Enclosing Ellipse
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// NOTE: In this release correct results are only guaranteed if exact
// arithmetic is used, so this demo (using inexact floating-point
// arithmetic) is only intended to illustrate the techniques. However,
// the program will terminate, but the computed ellipse may neither
// contain all points nor be the smallest one.
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// needs LEDA
#ifdef CGAL_USE_LEDA

// includes
#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/Min_ellipse_2.h>
#include <CGAL/Min_ellipse_2_traits_2.h>
#include <CGAL/IO/Window_stream.h>

// typedefs
typedef  CGAL::Cartesian< double >          R;
typedef  CGAL::Point_2< R >                 Point;
typedef  CGAL::Min_ellipse_2_traits_2< R >  Traits;
typedef  CGAL::Min_ellipse_2< Traits >      Min_ellipse;

// main
int
main( int, char**)
{
    using namespace std;

    cerr << "  left button: insert point" << endl;
    cerr << "middle button: clear points" << endl;
    cerr << " right button: exit"         << endl;

    // create empty min_ellipse;
    Min_ellipse  me;

    // open window
    CGAL::Window_stream ws( "CGAL Demo: Smallest Enclosing Ellipse in 2D");
    ws.set_icon_label("CGAL");
    ws.set_icon_pixrect( ws.create_pixrect( CGAL::esprit_logo));
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
	    ws << CGAL::WHITE << me.ellipse();
	    me.insert( Point( x, y));
	    ws << CGAL::BLACK << me;
	    ws << CGAL::BLUE  << me.ellipse();
	    ws << CGAL::RED;
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

#else
// no LEDA available

#include <iostream>

int
main( int, char**)
{
    using namespace std;

    cerr << "This demo program needs LEDA!" << endl;

    return( 0);
}
#endif // CGAL_USE_LEDA

// ===== EOF ==================================================================
