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
// file          : examples/Benchmark_LK/point_distributions.h
// chapter       : 
// package       : Benchmark_LK
// source        : Benchmark_LK/web/point_distributions.h
// revision      : 2.4 
// revision_date : 19 Apr 2000
// author(s)     : Lutz Kettner
//
// coordinator   : INRIA, Sophia Antipolis
//
// A benchmark measuring the performance of the default convex hull impl.
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef POINT_DISTRIBUTIONS_H
#define POINT_DISTRIBUTIONS_H 1

#ifndef CGAL_COPY_N_H
#include <CGAL/copy_n.h>
#endif
#ifndef POINT_GENERATORS_H
#include <CGAL/point_generators_2.h>
#endif

CGAL_BEGIN_NAMESPACE

const char* available_distributions = 
    "disc, circle, in_square, on_square, horizontal, vertical, grid, "
    "perturbed";


template < class ForwardIterator, class Point>
ForwardIterator point_distributions( const char* d, double range, 
				     ForwardIterator o,
				     int n, long seed, const Point*) {
    typedef Creator_uniform_2<double,Point>           Creator;
    typedef Random_points_in_disc_2<Point,Creator>    Random_in_disc;
    typedef Random_points_on_circle_2<Point,Creator>  Random_on_circle;
    typedef Random_points_in_square_2<Point,Creator>  Random_in_square;
    typedef Random_points_on_square_2<Point,Creator>  Random_on_square;
    typedef Random_points_on_segment_2<Point,Creator> Random_on_segment;
    typedef Points_on_segment_2<Point>                On_segment;
    Random rnd(seed);

    if ( strcmp( d, "disc") == 0) {
	Random_in_disc  rnd_points( range, rnd);
	o = CGAL::copy_n( rnd_points, n, o);
    } else if ( strcmp( d, "circle") == 0) {
	Random_on_circle  rnd_points( range, rnd);
	o = CGAL::copy_n( rnd_points, n, o);
    } else if ( strcmp( d, "in_square") == 0) {
	Random_in_square  rnd_points( range, rnd);
	o = CGAL::copy_n( rnd_points, n, o);
    } else if ( strcmp( d, "on_square") == 0) {
	Random_on_square  rnd_points( range, rnd);
	o = CGAL::copy_n( rnd_points, n, o);
    } else if ( strcmp( d, "horizontal") == 0) {
	o = points_on_segment_2( Point(-range,0), Point(range,0), n, o);
    } else if ( strcmp( d, "vertical") == 0) {
	o = points_on_segment_2( Point(0,-range), Point(0,range), n, o);
    } else if ( strcmp( d, "grid") == 0) {
	o = points_on_square_grid_2( range, n, o, Creator());
    } else if ( strcmp( d, "perturbed") == 0) {
	ForwardIterator beyond = points_on_square_grid_2(range,n,o,Creator());
	perturb_points_2( o, beyond, range*1e-5, range*1e-5, rnd, Creator());
	o = beyond;
    } else {
	cerr << "Unkown point distribution '" << d << "'. Possible values are:"
             << endl << available_distributions << endl;
	exit(1);
    }
    return o;
}

template < class ForwardIterator>
ForwardIterator point_distributions( const char* d, double range, 
				     ForwardIterator o,
				     int n, long seed) {
    return point_distributions( d, range, o, n, seed, 
        static_cast< std::iterator_traits<ForwardIterator>::value_type*>(0 ));
                                // std::value_type(o));
}

CGAL_END_NAMESPACE

#endif // POINT_DISTRIBUTIONS_H //
// EOF //

