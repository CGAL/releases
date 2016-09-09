// ======================================================================
//
// Copyright (c) 1997,1998,1999 The CGAL Consortium

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
// file          : include/CGAL/IO/Min_ellipse_2_Window_stream.h
// package       : Min_ellipse_2 (3.5.4)
// chapter       : $CGAL_Chapter: Geometric Optimisation $
//
// source        : web/Optimisation/Min_ellipse_2.aw
// revision      : $Revision: 5.22 $
// revision_date : $Date: 1999/12/20 19:06:47 $
// author(s)     : Sven Schönherr
//                 Bernd Gärtner
//
// coordinator   : ETH Zürich (Bernd Gärtner)
//
// implementation: graphical output to `leda_window' for Min_ellipse_2 algo.
// email         : cgal@cs.uu.nl
//
// ======================================================================

// Each of the following operators is individually
// protected against multiple inclusion.

// Window_stream I/O operators
// ===========================
// includes
#ifndef CGAL_CONIC_2_WINDOW_STREAM_H
#  include <CGAL/IO/Conic_2_Window_stream.h>
#endif

// Optimisation_ellipse_2
// ----------------------
#ifdef CGAL_OPTIMISATION_ELLIPSE_2_H
#ifndef CGAL_IO_WINDOW_STREAM_OPTIMISATION_ELLIPSE_2
#define CGAL_IO_WINDOW_STREAM_OPTIMISATION_ELLIPSE_2

template< class R >
CGAL::Window_stream&
operator << ( CGAL::Window_stream &ws,
              const CGAL::Optimisation_ellipse_2<R>& oe)
{
    switch ( oe.n_boundary_points) {
      case 0:
        break;
      case 1:
        ws << oe.boundary_point1;
        break;
      case 2: {
        double  px1( CGAL::to_double( oe.boundary_point1.x()));
        double  py1( CGAL::to_double( oe.boundary_point1.y()));
        double  px2( CGAL::to_double( oe.boundary_point2.x()));
        double  py2( CGAL::to_double( oe.boundary_point2.y()));
        ws.draw_segment( px1, py1, px2, py2); }
        break;
      case 3:
      case 4:
      case 5:
        ws << oe.to_double();
        break;
      default:
        CGAL_optimisation_assertion( ( oe.n_boundary_points >= 0) &&
                                     ( oe.n_boundary_points <= 5) ); }
    return( ws);
}

#endif // CGAL_IO_WINDOW_STREAM_OPTIMISATION_ELLIPSE_2
#endif // CGAL_OPTIMISATION_ELLIPSE_2_H

// Min_ellipse_2
// -------------
#ifdef CGAL_MIN_ELLIPSE_2_H
#ifndef CGAL_IO_WINDOW_STREAM_MIN_ELLIPSE_2
#define CGAL_IO_WINDOW_STREAM_MIN_ELLIPSE_2

template< class R >
CGAL::Window_stream&
operator << ( CGAL::Window_stream &ws,
              const CGAL::Min_ellipse_2<R>& min_ellipse)
{
    typedef CGAL::Min_ellipse_2<R>::Point_iterator  Point_iterator;

    Point_iterator  first( min_ellipse.points_begin());
    Point_iterator  last ( min_ellipse.points_end());
    for ( ; first != last; ++first)
        ws << *first;
    return( ws << min_ellipse.ellipse());
}
#endif // CGAL_IO_WINDOW_STREAM_MIN_ELLIPSE_2
#endif // CGAL_MIN_ELLIPSE_2_H

// ===== EOF ==================================================================
