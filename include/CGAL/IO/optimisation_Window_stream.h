/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/


// file  : include/CGAL/IO/optimisation_Window_stream.h
// author: Sven Schönherr
// $Revision: 3.1 $
// $Date: 1997/06/23 13:23:20 $

#ifndef CGAL_OPTIMISATION_WINDOW_STREAM_H
#define CGAL_OPTIMISATION_WINDOW_STREAM_H

// Window_stream I/O operators
// ===========================

// Optimisation_circle_2
// ---------------------
#ifdef CGAL_OPTIMISATION_CIRCLE_2_H
template< class R >
CGAL_Window_stream&
operator << ( CGAL_Window_stream &ws,
	      CGAL_Optimisation_circle_2<R> const& optimisation_circle)
{
    double  cx( CGAL_to_double( optimisation_circle.center().x()));
    double  cy( CGAL_to_double( optimisation_circle.center().y()));
    double  sr( CGAL_to_double( optimisation_circle.squared_radius()));

    ws.draw_circle( cx, cy, sqrt( sr));
    return( ws);
}

template< class R >
CGAL_Window_stream&
operator >> ( CGAL_Window_stream &ws,
	      CGAL_Optimisation_circle_2<R> const& optimisation_circle)
{
    double  cx, cy;
    double  px, py;

    ws.read_mouse( cx, cy);
    ws.read_mouse_circle( cx, cy, px, py);

    CGAL_Point_2<R>  center( cx, cy), point( px, py);
    R::FT            sqr_rad( CGAL_squared_distance( point, center));
 
    ws.draw_circle( cx, cy, sqrt(sr));
    optimisation_circle.set( center, sqr_rad);
    return( ws);
}
#endif // CGAL_OPTIMISATION_CIRCLE_2_H


// Min_circle_2
// ------------
#ifdef CGAL_MIN_CIRCLE_2_H
template< class R >
CGAL_Window_stream&
operator << ( CGAL_Window_stream &ws,
	      CGAL_Min_circle_2<R> const& min_circle)
{
    typedef  CGAL_Min_circle_2<R>::Point_iterator  Point_iterator;
    Point_iterator  first( min_circle.points_begin());
    Point_iterator  last ( min_circle.points_end());
    for ( ; first != last; ++first)
	ws << *first;
    return( ws << min_circle.circle());
}
#endif // CGAL_MIN_CIRCLE_2_H

#endif // CGAL_OPTIMISATION_WINDOW_STREAM_H

// ===== EOF ==================================================================
