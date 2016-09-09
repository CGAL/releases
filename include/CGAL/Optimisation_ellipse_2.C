// ======================================================================
//
// Copyright (c) 1997,1998 The CGAL Consortium
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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/Optimisation_ellipse_2.C
// package       : Min_ellipse_2 (3.1.1)
// chapter       : $CGAL_Chapter: Geometric Optimisation $
//
// source        : web/Optimisation/Min_ellipse_2.aw
// revision      : $Revision: 5.3 $
// revision_date : $Date: 1998/11/16 15:42:43 $
// author(s)     : Sven Schönherr
//                 Bernd Gärtner
//
// coordinator   : ETH Zürich (Bernd Gärtner)
//
// implementation: 2D Optimisation Ellipse
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

// Class implementation (continued)
// ================================
// includes
#ifndef CGAL_OPTIMISATION_ASSERTIONS_H
#  include <CGAL/optimisation_assertions.h>
#endif

// I/O
// ---
template < class _R >
ostream&
operator << ( ostream& os, const CGAL_Optimisation_ellipse_2<_R>& e)
{
    const char* const  empty       = "";
    const char* const  pretty_head = "CGAL_Optimisation_ellipse_2( ";
    const char* const  pretty_sep  = ", ";
    const char* const  pretty_tail = ")";
    const char* const  ascii_sep   = " ";

    const char*  head = empty;
    const char*  sep  = empty;
    const char*  tail = empty;

    switch ( CGAL_get_mode( os)) {
      case CGAL_IO::PRETTY:
        head = pretty_head;
        sep  = pretty_sep;
        tail = pretty_tail;
        break;
      case CGAL_IO::ASCII:
        sep  = ascii_sep;
        break;
      case CGAL_IO::BINARY:
        break;
      default:
        CGAL_optimisation_assertion_msg( false,
                                         "CGAL_get_mode( os) invalid!");
        break; }

    os << head << e.n_boundary_points;
    switch ( e.n_boundary_points) {
      case 0:
        break;
      case 1:
        os << sep << e.boundary_point1;
        break;
      case 2:
        os << sep << e.boundary_point1
           << sep << e.boundary_point2;
        break;
      case 3:
      case 5:
        os << sep << e.conic1;
        break;
      case 4:
        os << sep << e.conic1
           << sep << e.conic2;
        break; }
    os << tail;

    return( os);
}

template < class _R >
istream&
operator >> ( istream& is, CGAL_Optimisation_ellipse_2<_R>& e)
{
    switch ( CGAL_get_mode( is)) {

      case CGAL_IO::PRETTY:
        cerr << endl;
        cerr << "Stream must be in ascii or binary mode" << endl;
        break;

      case CGAL_IO::ASCII:
      case CGAL_IO::BINARY:
        CGAL_read( is, e.n_boundary_points);
        switch ( e.n_boundary_points) {
          case 0:
            break;
          case 1:
            is >> e.boundary_point1;
            break;
          case 2:
            is >> e.boundary_point1
               >> e.boundary_point2;
            break;
          case 3:
          case 5:
            is >> e.conic1;
            break;
          case 4:
            is >> e.conic1
               >> e.conic2;
            break; }
        break;

      default:
        CGAL_optimisation_assertion_msg( false,
                                         "CGAL_get_mode( is) invalid!");
        break; }

    return( is);
}

// ===== EOF ==================================================================
