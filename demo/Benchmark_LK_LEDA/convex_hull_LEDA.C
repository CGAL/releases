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
// file          : examples/Benchmark_LK/convex_hull_LEDA.C
// chapter       : $CGAL_Chapter: (none) $
// package       : $CGAL_Package: Benchmark_LK 2.2 (26 May 1999) $
// source        : Benchmark_LK/web/convex_hull_LEDA.C
// revision      : $Revision: 1.2 $
// revision_date : $Date: 1999/03/07 22:22:25 $ 
// author(s)     : Lutz Kettner
//
// coordinator   : INRIA, Sophia Antipolis
//
// A benchmark measuring the performance of the convex hull impl. of LEDA.
// email         : cgal@cs.uu.nl
//
// ======================================================================

#include <CGAL/basic.h>
#include <vector>
#include <algorithm>
#include <CGAL/Timer.h>
#include <LEDA/point.h>
#include <LEDA/plane_alg.h>

#include "point_distributions.h"

using namespace std;

struct LPoint : public leda_point {
    LPoint() {}
    LPoint( double x, double y) : leda_point(x,y) {}
    void operator=( const leda_point& p) { leda_point::operator=(p);}
    double x() const { return xcoord(); }
    double y() const { return ycoord(); }
};

int main( int argc, char** argv) {
    bool help = false;
    bool err  = false;

    // Commandline parameters and their default values.
    int         n         = 1000;     // Number of points.
    const char* dist      = "disc";   // Input are random points in a disc.
    long        seed      = 1;        // Random number generator seed.

    // Parse commandline parameters.
    for ( int k = 1; k < argc; k++) {
	if ( 0 == strcmp( argv[k], "-h"))
	    help = true;
	if ( 0 == strcmp( argv[k], "-help"))
	    help = true;
	if ( 0 == strcmp( argv[k], "-d")) {
	    if ( k+1 < argc) {
		k++;
		dist = argv[k];
	    } else
		err = true;
	    continue;
	}
	if ( 0 == strcmp( argv[k], "-seed")) {
	    if ( k+1 < argc) {
		k++;
		seed = atoi( argv[k]);
	    } else
		err = true;
	    continue;
	}
	if ( isdigit( argv[k][0]))
	    n = atoi( argv[k]);
	else
	    if ( argv[k][0] != '-')
		err = true;
    }
    if ( err)
	cerr << "Error in commandline parsing." << endl;
    if ( n < 1) {
	cerr << "Wrong number of points (1 < n)." << endl;
	err = true;
    }
    if ( err || help) {
	cerr << "Usage: " << argv[0] << " [<Options>] [n]" << endl;
	cerr << "         n = number of points." << endl;
	cerr << "Options: -h, -help    this message." << endl;
	cerr << "         -d <dist>    point distribution <dist>." << endl;
	cerr << "         -seed <s>    seed s for the random number source" 
	     << endl;
	cerr << "<dist>:\n  " << CGAL::available_distributions << endl;
	return 1;
    }

    // Generate input points for the algorithm.
    LPoint* p = new LPoint[ n];
    CGAL::point_distributions( dist, 1.0, p, n, seed);
    leda_list<leda_point> points;
    for ( LPoint* pp = p; pp != p+n; ++pp) {
	points.append( leda_point( *pp));
    }
    CGAL::Timer t;
    t.start();
    leda_list<leda_point> hull = CONVEX_HULL( points);
    t.stop();
    cout << "The convex hull has " << hull.size()
	 << " points. Time to compute: " << t.time() << " s." << endl;

    delete[] p;
    return 0;
}

// EOF //
