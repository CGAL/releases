// ============================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// file          : examples/Benchmark_LK/convex_hull.C
// chapter       : 
// package       : Benchmark_LK
// source        : 
// revision      : 2.3.2
// revision_date : 16 Dec 1999
// author(s)     : Lutz Kettner
//                 maintained by Stefan Schirra
//
// coordinator   : 
//
// A benchmark measuring the performance of the default convex hull impl.
// email         : cgal@cs.uu.nl
//
// ======================================================================

#include <CGAL/basic.h>
#include <vector>
#include <string>
#include <algorithm>
#include <CGAL/Timer.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/IO/Ostream_iterator.h>
#include <CGAL/IO/Window_stream.h>

#include "point_distributions.h"

using namespace std;

typedef CGAL::Cartesian<double>  Rep;
typedef CGAL::Point_2<Rep>       Point;
typedef CGAL::Segment_2<Rep>     Segment;

int main( int argc, char** argv) {
    bool help    = false;
    bool err     = false;
    bool window  = true;

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
        if ( argvk == "-nw") window = false;
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
            if ( argvk[0] != '-') { err = true; }
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
        cerr << "         -nw          no window output." << endl;
        cerr << "         -d <dist>    point distribution <dist>." << endl;
        cerr << "         -seed <s>    seed s for the random number source" 
             << endl;
        cerr << "<dist>:\n  " << CGAL::available_distributions << endl;
        return 1;
    }

    CGAL::Window_stream* w = 0;
    if ( window) {
        // Display points and the convex hull in a 512x512 pixel window.
        w = CGAL::create_and_display_demo_window();
        w->set_frame_label( "Convex Hull (CGAL)");
    }

    // Generate input points for the algorithm.
    Point* p = new Point[ n];
    CGAL::point_distributions( dist.c_str(), 1.0, p, n, seed);
    if ( window) {
        if ( n > 10000)
            cout << "Display of points is suppressed." << endl;
        else {
            *w << CGAL::BLACK;
            copy( p, p+n, 
                  CGAL::Ostream_iterator<Point,CGAL::Window_stream>(*w));
        }
        cout << "Click into window to start computation." << endl;
        Point q;
        *w << CGAL::WHITE;
        *w >> q;
    }
    Point* hull = new Point[n+1]; // Reserved space for the convex hull.
    CGAL::Timer t;
    t.start();
    Point* beyond = CGAL::convex_hull_points_2( p, p+n, hull);
    t.stop();
    cout << "The convex hull has " << beyond-hull
         << " points. Time to compute: " << t.time() << " s." << endl;

    if ( window) {
        // Display the result.
        *w << CGAL::RED;
        // Copy first point to the end position -- this wrap around
        // allows the easy drawing of the connecting segments.
        *beyond = hull[0];
        for ( Point* pt = hull; pt != beyond; ++pt)
            *w << Segment( *pt, *(pt+1));
        *w << CGAL::GREEN;
        copy( hull, beyond, 
              CGAL::Ostream_iterator<Point,CGAL::Window_stream>(*w));

        cout << "The drawing is finished. Click into window to close it." 
             << endl;
        Point q;
        *w << CGAL::WHITE;
        *w >> q;
        delete w;
    }
    delete[] p;
    delete[] hull;
    return 0;
}

// EOF //
