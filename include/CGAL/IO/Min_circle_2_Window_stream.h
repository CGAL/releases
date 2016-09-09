// ======================================================================
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
// file          : include/CGAL/IO/Min_circle_2_Window_stream.h
// package       : Min_circle_2 (3.2.3)
// chapter       : $CGAL_Chapter: Geometric Optimisation $
//
// source        : web/Optimisation/Min_circle_2.aw
// revision      : $Revision: 5.8 $
// revision_date : $Date: 1999/04/19 16:20:38 $
// author(s)     : Sven Schönherr
//                 Bernd Gärtner
//
// coordinator   : ETH Zürich (Bernd Gärtner)
//
// implementation: graphical output to `leda_window' for Min_circle_2 algorith.
// email         : cgal@cs.uu.nl
//
// ======================================================================

// Each of the following operators is individually
// protected against multiple inclusion.

// Window_stream I/O operators
// ===========================

// Optimisation_circle_2
// ---------------------
#ifdef CGAL_OPTIMISATION_CIRCLE_2_H
#ifndef CGAL_IO_WINDOW_STREAM_OPTIMISATION_CIRCLE_2
#define CGAL_IO_WINDOW_STREAM_OPTIMISATION_CIRCLE_2

template< class R >
CGAL::Window_stream&
operator << ( CGAL::Window_stream &ws,
              const CGAL::Optimisation_circle_2<R>& oc)
{
    double  cx( CGAL::to_double( oc.center().x()));
    double  cy( CGAL::to_double( oc.center().y()));
    double  sr( CGAL::to_double( oc.squared_radius()));

    if ( ! CGAL::is_negative( sr))
        ws.draw_circle( cx, cy, sqrt( sr));
    return( ws);
}

#endif // CGAL_IO_WINDOW_STREAM_OPTIMISATION_CIRCLE_2
#endif // CGAL_OPTIMISATION_CIRCLE_2_H

// Min_circle_2
// ------------
#ifdef CGAL_MIN_CIRCLE_2_H
#ifndef CGAL_IO_WINDOW_STREAM_MIN_CIRCLE_2
#define CGAL_IO_WINDOW_STREAM_MIN_CIRCLE_2

template< class R >
CGAL::Window_stream&
operator << ( CGAL::Window_stream &ws,
              const CGAL::Min_circle_2<R>& min_circle)
{
    typedef  CGAL::Min_circle_2<R>::Point_iterator  Point_iterator;

    Point_iterator  first( min_circle.points_begin());
    Point_iterator  last ( min_circle.points_end());
    for ( ; first != last; ++first)
        ws << *first;
    return( ws << min_circle.circle());
}

#endif // CGAL_IO_WINDOW_STREAM_MIN_CIRCLE_2
#endif // CGAL_MIN_CIRCLE_2_H

// ===== EOF ==================================================================
