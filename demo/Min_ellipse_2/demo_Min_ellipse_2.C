// ============================================================================
//
// Copyright (c) 1997-2001 The CGAL Consortium

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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : demo/Min_ellipse_2/demo_Min_ellipse_2.C
// package       : $CGAL_Package: Min_ellipse_2 $
// chapter       : Geometric Optimisation
//
// revision      : $Revision: 5.7 $
// revision_date : $Date: 2001/07/17 12:32:59 $
//
// author(s)     : Sven Schönherr
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

// includes
#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/Min_ellipse_2.h>
#include <CGAL/Min_ellipse_2_traits_2.h>
#include <CGAL/IO/Window_stream.h>

// typedefs
typedef  CGAL::Cartesian< double >          K;
typedef  CGAL::Point_2< K >                 Point;
typedef  CGAL::Min_ellipse_2_traits_2< K >  Traits;
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

// ===== EOF ==================================================================
