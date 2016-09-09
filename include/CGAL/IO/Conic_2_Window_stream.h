// ======================================================================
//
// Copyright (c) 1997-2001 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
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
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/IO/Conic_2_Window_stream.h
// package       : Min_ellipse_2 (3.14)
// chapter       : Geometric Optimisation
//
// source        : web/Conic_2.aw
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2001/07/17 12:51:05 $
//
// author(s)     : Bernd Gärtner, Sven Schönherr
// coordinator   : ETH Zürich (Bernd Gärtner)
//
// implementation: graphical output to `leda_window' for Conic_2 algo.
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

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
CGAL::Window_stream&
operator << ( CGAL::Window_stream& ws, const CGAL::Conic_2<R>& c)
{
    // length of a pixel in window-coordinates
    double pixel = 1/ws.scale();

    // pixel dimensions of window
    int width  = (int)((ws.xmax() - ws.xmin()) * ws.scale()) + 1,
        height = (int)((ws.ymax() - ws.ymin()) * ws.scale()) + 1,
        dim    = std::max( width, height);

    // pixel coordinates, stored for faster output
    double *X = new double [2*dim];
    double *Y = new double [2*dim];

    // actual number of pixels to be drawn
    int pixels;

    // conic coordinates
    double r = CGAL::to_double (c.r()),
           s = CGAL::to_double (c.s()),
           t = CGAL::to_double (c.t()),
           u = CGAL::to_double (c.u()),
           v = CGAL::to_double (c.v()),
           w = CGAL::to_double (c.w());

    // Phase I (drawing in x-direction)
    pixels = 0;
    // solve conic equation for y
    if (s != 0.0)
        for (double x = ws.xmin(); x <= ws.xmax(); x+=pixel) {
            double discr = (t*t-4.0*r*s)*(x*x) + (2.0*t*v-4.0*s*u)*x +
                             v*v - 4.0*s*w;
            if (discr >= 0.0) {
                double y1 = (-t*x - v - CGAL::sqrt(discr))/(2.0*s);
                double y2 = (-t*x - v + CGAL::sqrt(discr))/(2.0*s);
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
                double x1 = (-t*y - u - CGAL::sqrt(discr))/(2.0*r);
                double x2 = (-t*y - u + CGAL::sqrt(discr))/(2.0*r);
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

// ===== EOF ==================================================================
