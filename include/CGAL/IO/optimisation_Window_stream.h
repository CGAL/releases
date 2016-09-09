// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/IO/optimisation_Window_stream.h
// author(s)     : Sven Schönherr 
//                 N.N.
//
// email         : cgal@cs.uu.nl
//
// ============================================================================

// Each of the following operators is individually
// protected against multiple inclusion.

// Window_stream I/O operators
// ===========================

// Conic_2
// -------
#ifdef CGAL_CONIC_2_H
#ifndef CGAL_IO_WINDOW_STREAM_CONIC_2
#define CGAL_IO_WINDOW_STREAM_CONIC_2

template< class R >
CGAL_Window_stream&
operator << ( CGAL_Window_stream &ws, const CGAL_Conic_2<R>& c)
{
    // length of a pixel in window-coordinates
    double pixel = 1/ws.scale();

    // pixel dimensions of window
    int width  = (int)((ws.xmax() - ws.xmin()) * ws.scale()) + 1,
        height = (int)((ws.ymax() - ws.ymin()) * ws.scale()) + 1,
        dim    = CGAL_max( width, height);

    // pixel coordinates, stored for faster output
    double *X = new double [2*dim];
    double *Y = new double [2*dim];

    // actual number of pixels to be drawn
    int pixels;

    // conic coordinates
    double r = CGAL_to_double (c.r()),
           s = CGAL_to_double (c.s()),
           t = CGAL_to_double (c.t()),
           u = CGAL_to_double (c.u()),
           v = CGAL_to_double (c.v()),
           w = CGAL_to_double (c.w());

    // Phase I (drawing in x-direction)
    pixels = 0;
    // solve conic equation for y
    if (s != 0.0)
        for (double x = ws.xmin(); x <= ws.xmax(); x+=pixel) {
            double discr = (t*t-4.0*r*s)*(x*x) + (2.0*t*v-4.0*s*u)*x +
                             v*v - 4.0*s*w;
            if (discr >= 0.0) {
                double y1 = (-t*x - v - sqrt(discr))/(2.0*s);
                double y2 = (-t*x - v + sqrt(discr))/(2.0*s);
                X[pixels] = x; Y[pixels++] = y1;
                X[pixels] = x; Y[pixels++] = y2; } }
    else
        for (double x = ws.xmin(); x <= ws.xmax(); x+=pixel) {
            double denom = t*x + v;
            if (denom != 0.0) {
                double y = -(r*x*x + u*x + w)/denom;
                X[pixels] = x; Y[pixels++] = y; } }
    ws.draw_pixels (pixels, X, Y);

    // Phase II (drawing in y-direction)
    pixels = 0;
    // solve conic equation for x
    if (r != 0.0)
        for (double y = ws.ymin(); y <= ws.ymax(); y+=pixel) {
            double discr = (t*t-4.0*r*s)*(y*y) + (2.0*t*u-4.0*r*v)*y +
                             u*u - 4.0*r*w;
            if (discr >= 0.0) {
                double x1 = (-t*y - u - sqrt(discr))/(2.0*r);
                double x2 = (-t*y - u + sqrt(discr))/(2.0*r);
                X[pixels] = x1; Y[pixels++] = y;
                X[pixels] = x2; Y[pixels++] = y; } }
    else
        for (double y = ws.ymin(); y <= ws.ymax(); y+=pixel) {
            double denom = t*y + u;
            if (denom != 0.0) {
                double x = -(s*y*y + v*y + w)/denom;
                X[pixels] = x; Y[pixels++] = y; } }
    ws.draw_pixels (pixels, X, Y);

    // free memory
    delete[] Y;
    delete[] X;

    return( ws);
}

#endif // CGAL_IO_WINDOW_STREAM_CONIC_2
#endif // CGAL_CONIC_2_H

// Optimisation_circle_2
// ---------------------
#ifdef CGAL_OPTIMISATION_CIRCLE_2_H
#ifndef CGAL_IO_WINDOW_STREAM_OPTIMISATION_CIRCLE_2
#define CGAL_IO_WINDOW_STREAM_OPTIMISATION_CIRCLE_2

template< class R >
CGAL_Window_stream&
operator << ( CGAL_Window_stream &ws,
              const CGAL_Optimisation_circle_2<R>& optimisation_circle)
{
    double  cx( CGAL_to_double( optimisation_circle.center().x()));
    double  cy( CGAL_to_double( optimisation_circle.center().y()));
    double  sr( CGAL_to_double( optimisation_circle.squared_radius()));

    if ( ! CGAL_is_negative( sr))
        ws.draw_circle( cx, cy, sqrt( sr));
    return( ws);
}

#endif // CGAL_IO_WINDOW_STREAM_OPTIMISATION_CIRCLE_2
#endif // CGAL_OPTIMISATION_CIRCLE_2_H

// Optimisation_ellipse_2
// ---------------------
#ifdef CGAL_OPTIMISATION_ELLIPSE_2_H
#ifndef CGAL_IO_WINDOW_STREAM_OPTIMISATION_ELLIPSE_2
#define CGAL_IO_WINDOW_STREAM_OPTIMISATION_ELLIPSE_2

#ifndef CGAL_CARTESIAN_H
#  include <CGAL/Cartesian.h>
#endif
#ifndef CGAL_CONICCPA2_H
#  include <CGAL/ConicCPA2.h>
#endif

template< class R >
CGAL_Window_stream&
operator << ( CGAL_Window_stream &ws,
              const CGAL_Optimisation_ellipse_2<R>& oe)
{
    switch ( oe.n_boundary_points) {
      case 0:
        break;
      case 1:
        ws << oe.boundary_point1;
        break;
      case 2: {
        double  px1( CGAL_to_double( oe.boundary_point1.x()));
        double  py1( CGAL_to_double( oe.boundary_point1.y()));
        double  px2( CGAL_to_double( oe.boundary_point2.x()));
        double  py2( CGAL_to_double( oe.boundary_point2.y()));
        ws.draw_segment( px1, py1, px2, py2); }
        break;
      case 3:
      case 5:
        ws << oe.conic1;
        break;
      case 4: {
        CGAL_Conic_2<R> c( oe.conic1);
        double t = c.vol_minimum( oe.dr, oe.ds, oe.dt, oe.du, oe.dv, oe.dw);
        CGAL_Conic_2< CGAL_Cartesian<double> > e;
        e.set( CGAL_to_double( c.r()) + t*CGAL_to_double( oe.dr),
               CGAL_to_double( c.s()) + t*CGAL_to_double( oe.ds),
               CGAL_to_double( c.t()) + t*CGAL_to_double( oe.dt),
               CGAL_to_double( c.u()) + t*CGAL_to_double( oe.du),
               CGAL_to_double( c.v()) + t*CGAL_to_double( oe.dv),
               CGAL_to_double( c.w()) + t*CGAL_to_double( oe.dw));
        ws << e; }
        break;
      default:
        CGAL_optimisation_assertion( ( oe.n_boundary_points >= 0) &&
                                     ( oe.n_boundary_points <= 5) ); }

    return( ws);
}

#endif // CGAL_IO_WINDOW_STREAM_OPTIMISATION_ELLIPSE_2
#endif // CGAL_OPTIMISATION_ELLIPSE_2_H

// Min_circle_2
// ------------
#ifdef CGAL_MIN_CIRCLE_2_H
#ifndef CGAL_IO_WINDOW_STREAM_MIN_CIRCLE_2
#define CGAL_IO_WINDOW_STREAM_MIN_CIRCLE_2

template< class R >
CGAL_Window_stream&
operator << ( CGAL_Window_stream &ws,
              const CGAL_Min_circle_2<R>& min_circle)
{
    typedef  typename CGAL_Min_circle_2<R>::Point_iterator  Point_iterator;

    Point_iterator  first( min_circle.points_begin());
    Point_iterator  last ( min_circle.points_end());
    for ( ; first != last; ++first)
        ws << *first;
    return( ws << min_circle.circle());
}

#endif // CGAL_IO_WINDOW_STREAM_MIN_CIRCLE_2
#endif // CGAL_MIN_CIRCLE_2_H

// Min_ellipse_2
// -------------
#ifdef CGAL_MIN_ELLIPSE_2_H
#ifndef CGAL_IO_WINDOW_STREAM_MIN_ELLIPSE_2
#define CGAL_IO_WINDOW_STREAM_MIN_ELLIPSE_2

template< class R >
CGAL_Window_stream&
operator << ( CGAL_Window_stream &ws,
              const CGAL_Min_ellipse_2<R>& min_ellipse)
{
    typedef  typename CGAL_Min_ellipse_2<R>::Point_iterator  Point_iterator;

    Point_iterator  first( min_ellipse.points_begin());
    Point_iterator  last ( min_ellipse.points_end());
    for ( ; first != last; ++first)
        ws << *first;
    return( ws << min_ellipse.ellipse());
}

#endif // CGAL_IO_WINDOW_STREAM_MIN_ELLIPSE_2
#endif // CGAL_MIN_ELLIPSE_2_H

// ===== EOF ==================================================================
