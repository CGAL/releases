// ============================================================================
//
// Copyright (c) 1997,1998 The CGAL Consortium
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
// file          : examples/Optimisation/example_Min_circle_2.C
// chapter       : $CGAL_Chapter: Geometric Optimisation $
// package       : $CGAL_Package: Min_circle_2 3.1.1 (16 Nov 1998) $
//
// revision      : $Revision: 5.1 $
// revision_date : $Date: 1998/07/02 17:54:53 $
// author(s)     : Sven Schönherr
//                 Bernd Gärtner
//
// coordinator   : ETH Zürich (Bernd Gärtner)
//
// example progr.: 2D Smallest Enclosing Circle
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

// includes
#include <CGAL/Gmpz.h>
#include <CGAL/Homogeneous.h>
#include <CGAL/Point_2.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <iostream.h>

// typedefs
typedef  CGAL_Gmpz                      NT;
typedef  CGAL_Homogeneous<NT>           R;
typedef  CGAL_Point_2<R>                Point;
typedef  CGAL_Min_circle_2_traits_2<R>  Traits;
typedef  CGAL_Min_circle_2<Traits>      Min_circle;

// main
int
main( int, char**)
{
    int     n = 100;
    Point*  P = new Point[ n];

    for ( int i = 0; i < n; ++i)
	P[ i] = Point( (i%2 == 0 ? i : -i), 0);
    // (0,0), (-1,0), (2,0), (-3,0), ...

    Min_circle  mc1( P, P+n);           // very slow
    Min_circle  mc2( P, P+n, true);     // fast

    CGAL_set_pretty_mode( cout);
    cout << mc2;

    delete[] P;

    return( 0);
}

// ===== EOF ==================================================================
