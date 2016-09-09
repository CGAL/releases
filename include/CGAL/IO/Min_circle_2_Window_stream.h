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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/IO/Min_circle_2_Window_stream.h
// package       : Min_circle_2 (3.15)
// chapter       : Geometric Optimisation
//
// source        : web/Min_circle_2.aw
// revision      : $Revision: 1.8 $
// revision_date : $Date: 2002/04/13 23:13:17 $
//
// author(s)     : Sven Schönherr, Bernd Gärtner
// coordinator   : ETH Zürich (Bernd Gärtner)
//
// implementation: graphical output to `leda_window' for Min_circle_2 algorith.
// email         : contact@cgal.org
// www           : http://www.cgal.org
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

template< class K_ >
CGAL::Window_stream&
operator << ( CGAL::Window_stream &ws,
              const CGAL::Optimisation_circle_2<K_>& oc)
{
    double  cx( CGAL::to_double( oc.center().x()));
    double  cy( CGAL::to_double( oc.center().y()));
    double  sr( CGAL::to_double( oc.squared_radius()));

    if ( ! CGAL_NTS is_negative( sr))
        ws.draw_circle( cx, cy, CGAL::sqrt( sr));
    return( ws);
}

#endif // CGAL_IO_WINDOW_STREAM_OPTIMISATION_CIRCLE_2
#endif // CGAL_OPTIMISATION_CIRCLE_2_H

// Min_circle_2
// ------------
#ifdef CGAL_MIN_CIRCLE_2_H
#ifndef CGAL_IO_WINDOW_STREAM_MIN_CIRCLE_2
#define CGAL_IO_WINDOW_STREAM_MIN_CIRCLE_2

template< class Traits_ >
CGAL::Window_stream&
operator << ( CGAL::Window_stream &ws,
              const CGAL::Min_circle_2<Traits_>& min_circle)
{
    typedef typename CGAL::Min_circle_2<Traits_>::Point_iterator
	                                          Point_iterator;

    Point_iterator  first( min_circle.points_begin());
    Point_iterator  last ( min_circle.points_end());
    for ( ; first != last; ++first)
        ws << *first;
    return( ws << min_circle.circle());
}

#endif // CGAL_IO_WINDOW_STREAM_MIN_CIRCLE_2
#endif // CGAL_MIN_CIRCLE_2_H

// ===== EOF ==================================================================
