// ============================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// file          : examples/Benchmark_LK/convex_hull_LEDA.C
// chapter       : 
// package       : Benchmark_LK
// source        : 
// revision      : 2.4
// revision_date : 19 Apr 2000
// author(s)     : Lutz Kettner
//
// coordinator   : 
//
// A benchmark measuring the performance of the convex hull impl. of LEDA.
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#include <CGAL/basic.h>
#ifndef CGAL_USE_LEDA
int main() { std::cout << "\nSorry, this demo needs LEDA\n"; return 0; }
#else
#include <vector>
#include <string>
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

CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(LPoint);


int 
main( int argc, char** argv) 
{
    bool help = false;
    bool err  = false;

    // Commandline parameters and their default values.
    int         n         = 1000;     // Number of points.
    string      dist      = "disc";   // Input are random points in a disc.
    long        seed      = 1;        // Random number generator seed.

    // Parse commandline parameters.
    for ( int k = 1; k < argc; k++) 
    {
        string argvk = argv[k];
        if ( argvk == "-h") help = true;
        if ( argvk == "-help") help = true;
        if ( argvk == "-d") 
        {
            if ( k+1 < argc) 
            {
                k++;
                dist = argvk;
            } 
            else
                err = true;
            continue;
        }
		if ( argvk == "-seed") 
        {
            if ( k+1 < argc) 
            {
                k++;
                seed = atoi( argvk.c_str());
            } 
            else
                err = true;
            continue;
        }
        if ( isdigit( argvk[0]))
            n = atoi( argvk.c_str());
        else
            if ( argvk[0] != '-')
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
    CGAL::point_distributions( dist.c_str(), 1.0, p, n, seed);
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
#endif // USE_LEDA
