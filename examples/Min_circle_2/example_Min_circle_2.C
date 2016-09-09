// ============================================================================
//
// Copyright (c) 1997-2001 The CGAL Consortium

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
// file          : examples/Min_circle_2/example_Min_circle_2.C
// package       : $CGAL_Package: Min_circle_2 $
// chapter       : Geometric Optimisation
//
// revision      : $Revision: 5.7 $
// revision_date : $Date: 2001/07/17 11:22:15 $
//
// author(s)     : Sven Schönherr, Bernd Gärtner
// coordinator   : ETH Zürich (Bernd Gärtner)
//
// example progr.: 2D Smallest Enclosing Circle
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

// includes
#include <CGAL/Homogeneous.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <CGAL/Gmpz.h>
#include <iostream>

// typedefs
typedef  CGAL::Gmpz                      NT;
typedef  CGAL::Homogeneous<NT>           K;
typedef  CGAL::Min_circle_2_traits_2<K>  Traits;
typedef  CGAL::Min_circle_2<Traits>      Min_circle;

typedef  K::Point_2                      Point;

// main
int
main( int, char**)
{
    int     n = 100;
    Point*  P = new Point[ n];

    for ( int i = 0; i < n; ++i)
	P[ i] = Point( (i%2 == 0 ? i : -i), 0);
    // (0,0), (-1,0), (2,0), (-3,0), ...

    Min_circle  mc1( P, P+n, false);    // very slow
    Min_circle  mc2( P, P+n, true);     // fast

    CGAL::set_pretty_mode( std::cout);
    std::cout << mc2;

    delete[] P;

    return( 0);
}

// ===== EOF ==================================================================
