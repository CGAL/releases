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
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : examples/Optimisation/example_Min_ellipse_2.C
// chapter       : $CGAL_Chapter: Geometric Optimisation $
// package       : $CGAL_Package: Min_ellipse_2 3.5.4 (20 Dec 1999) $
//
// revision      : $Revision: 5.4 $
// revision_date : $Date: 1999/10/12 18:51:36 $
// author(s)     : Sven Schönherr
//                 Bernd Gärtner
//
// coordinator   : ETH Zürich (Bernd Gärtner)
//
// example progr.: 2D Smallest Enclosing Ellipse
// email         : cgal@cs.uu.nl
//
// ======================================================================

// includes
#include <CGAL/Homogeneous.h>
#include <CGAL/Point_2.h>
#include <CGAL/Min_ellipse_2.h>
#include <CGAL/Min_ellipse_2_traits_2.h>
#include <CGAL/Gmpz.h>

// typedefs
typedef  CGAL::Gmpz                       NT;
typedef  CGAL::Homogeneous<NT>            R;
typedef  CGAL::Point_2<R>                 Point;
typedef  CGAL::Min_ellipse_2_traits_2<R>  Traits;
typedef  CGAL::Min_ellipse_2<Traits>      Min_ellipse;

// main
int
main( int, char**)
{
    int     n = 100;
    Point*  P = new Point[ n];

    for ( int i = 0; i < n; ++i)
	P[ i] = Point( (i%2 == 0 ? i : -i), 0);
    // (0,0), (-1,0), (2,0), (-3,0), ...

    Min_ellipse  me1( P, P+n, false);    // very slow
    Min_ellipse  me2( P, P+n, true);     // fast

    CGAL::set_pretty_mode( std::cout);
    std::cout << me2;

    delete[] P;

    return( 0);
}

// ===== EOF ==================================================================
