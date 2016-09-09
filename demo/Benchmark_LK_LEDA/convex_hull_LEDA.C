// ============================================================================
//
// Copyright (c) 1997 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------------
//
// release       : $CGAL_Revision: $
// release_date  : $CGAL_Date: $
//
// file          : examples/Benchmark_LK/convex_hull_LEDA.C
// source        : Benchmark_LK/web/convex_hull_LEDA.C
// revision      : $Revision: $
// revision_date : $Date: $ 
// author(s)     : Lutz Kettner  <kettner@inf.ethz.ch>
//
// coordinator   : INRIA, Sophia Antipolis
//
// A benchmark measuring the performance of the convex hull impl. of LEDA.
// ============================================================================

#include <CGAL/basic.h>
#include <vector.h>
#include <algo.h>
#include <CGAL/Timer.h>
#include <LEDA/point.h>
#include <LEDA/plane_alg.h>

#include "point_distributions.h"


struct LPoint : public leda_point {
    LPoint() {}
    LPoint( double x, double y) : leda_point(x,y) {}
    void operator=( const leda_point& p) { leda_point::operator=(p);}
    double x() const { return xcoord(); }
    double y() const { return ycoord(); }
};


// Main Program
// ----------------------------------------------------------------------
int main( int argc, char** argv)
{
    bool help    = false;
    bool err     = false;

    // Commandline parameters and their default values.
    int         n         = 1000;         // Number of points.
    const char* dist      = "disc";       // Input are random points in a disc.
    long        seed      = 1;            // Random number generator seed.

    // Parse commandline parameters.
    for ( int k = 1; k < argc; k++) 
    {
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
    if ( n < 1) 
    {
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
	cerr << "<dist>:\n  " << CGAL_available_distributions << endl;
	return 1;
    }

    // Generate input points for the algorithm.
    LPoint* p = new LPoint[ n];
    CGAL_point_distributions( dist, 250, p, n, seed);
    leda_list<leda_point> points;
    for ( LPoint* pp = p; pp != p+n; ++pp) {
	points.append( leda_point( *pp));
    }

    CGAL_Timer t;
    t.start();
    leda_list<leda_point> hull = CONVEX_HULL( points);
    t.stop();
    cout << "The convex hull has " << hull.size()
	 << " points. Time to compute: " << t.time() << " s." << endl;

    delete[] p;
    return 0;
}

// EOF //
