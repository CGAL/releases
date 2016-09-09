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
// file          : examples/Benchmark_LK/point_distributions.h
// chapter       : $CGAL_Chapter: (none) $
// package       : $CGAL_Package: Benchmark_LK 2.2 (26 May 1999) $
// source        : Benchmark_LK/web/point_distributions.h
// revision      : $Revision: 1.2 $
// revision_date : $Date: 1999/03/07 22:22:25 $ 
// author(s)     : Lutz Kettner
//
// coordinator   : INRIA, Sophia Antipolis
//
// A benchmark measuring the performance of the default convex hull impl.
// email         : cgal@cs.uu.nl
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
    return point_distributions( d, range, o, n, seed, std::value_type(o));
}

CGAL_END_NAMESPACE

#endif // POINT_DISTRIBUTIONS_H //
// EOF //

