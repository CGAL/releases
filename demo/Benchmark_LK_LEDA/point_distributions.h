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
// file          : examples/Benchmark_LK/point_distributions.h
// source        : Benchmark_LK/web/point_distributions.h
// revision      : $Revision: $
// revision_date : $Date: $ 
// author(s)     : Lutz Kettner  <kettner@inf.ethz.ch>
//
// coordinator   : INRIA, Sophia Antipolis
//
// A benchmark measuring the performance of the default convex hull impl.
// ============================================================================

#ifndef CGAL_POINT_DISTRIBUTIONS_H
#define CGAL_POINT_DISTRIBUTIONS_H 1

#ifndef CGAL_COPY_N_H
#include <CGAL/copy_n.h>
#endif
#ifndef CGAL_POINT_GENERATORS_H
#include <CGAL/point_generators_2.h>
#endif



const char* CGAL_available_distributions = 
    "disc, circle, in_square, on_square, horizontal, vertical, grid, "
    "perturbed";


template < class ForwardIterator, class Point>
ForwardIterator CGAL_point_distributions( const char* d, double range, 
					 ForwardIterator o,
					 int n, long seed, const Point*) {
    typedef CGAL_Creator_uniform_2<double,Point>           Creator;
    typedef CGAL_Random_points_in_disc_2<Point,Creator>    Random_in_disc;
    typedef CGAL_Random_points_on_circle_2<Point,Creator>  Random_on_circle;
    typedef CGAL_Random_points_in_square_2<Point,Creator>  Random_in_square;
    typedef CGAL_Random_points_on_square_2<Point,Creator>  Random_on_square;
    typedef CGAL_Random_points_on_segment_2<Point,Creator> Random_on_segment;
    typedef CGAL_Points_on_segment_2<Point>                On_segment;
    CGAL_Random rnd(seed);

    if ( strcmp( d, "disc") == 0) {
	Random_in_disc  rnd_points( range, rnd);
	o = CGAL_copy_n( rnd_points, n, o);
    } else if ( strcmp( d, "circle") == 0) {
	Random_on_circle  rnd_points( range, rnd);
	o = CGAL_copy_n( rnd_points, n, o);
    } else if ( strcmp( d, "in_square") == 0) {
	Random_in_square  rnd_points( range, rnd);
	o = CGAL_copy_n( rnd_points, n, o);
    } else if ( strcmp( d, "on_square") == 0) {
	Random_on_square  rnd_points( range, rnd);
	o = CGAL_copy_n( rnd_points, n, o);
    } else if ( strcmp( d, "horizontal") == 0) {
	o = CGAL_points_on_segment_2( Point(-range,0), Point(range,0), n, o);
    } else if ( strcmp( d, "vertical") == 0) {
	o = CGAL_points_on_segment_2( Point(0,-range), Point(0,range), n, o);
    } else if ( strcmp( d, "grid") == 0) {
	o = CGAL_points_on_square_grid_2( range, n, o, Creator());
    } else if ( strcmp( d, "perturbed") == 0) {
	ForwardIterator beyond = 
	    CGAL_points_on_square_grid_2( range, n, o, Creator());
	CGAL_perturb_points_2( o, beyond, range*1e-5, range*1e-5, rnd, 
			       Creator());
	o = beyond;
    } else {
	cerr << "Unkown point distribution '" << d << "'. Possible values are:"
             << endl << CGAL_available_distributions << endl;
	exit(1);
    }
    return o;
}

template < class ForwardIterator>
ForwardIterator CGAL_point_distributions( const char* d, double range, 
					  ForwardIterator o,
					  int n, long seed) {
    return CGAL_point_distributions( d, range, o, n, seed, value_type(o));
}


#endif // CGAL_POINT_DISTRIBUTIONS_H //
// EOF //

