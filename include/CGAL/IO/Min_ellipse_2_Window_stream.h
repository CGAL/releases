// ======================================================================
//
// Copyright (c) 1997-2000 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------
//
// release       : $CGAL_Revision: CGAL-2.2-I-51 $
// release_date  : $CGAL_Date: 2000/10/01 $
//
// file          : include/CGAL/IO/Min_ellipse_2_Window_stream.h
// package       : Min_ellipse_2 (3.10.2)
// maintainer    : Sven Sch�nherr <sven@inf.ethz.ch>
// chapter       : $CGAL_Chapter: Geometric Optimisation $
//
// source        : web/Optimisation/Min_ellipse_2.aw
// revision      : $Revision: 5.29 $
// revision_date : $Date: 2000/09/18 09:57:06 $
//
// author(s)     : Sven Sch�nherr, Bernd G�rtner
// coordinator   : ETH Z�rich (Bernd G�rtner <gaertner@inf.ethz.ch>)
//
// implementation: graphical output to `leda_window' for Min_ellipse_2 algo.
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
