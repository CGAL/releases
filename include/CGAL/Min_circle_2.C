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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.1
// release_date  : 1998, July 24
//
// file          : include/CGAL/Min_circle_2.C
// package       : Min_circle_2 (3.0.2)
// chapter       : $CGAL_Chapter: Geometric Optimisation $
//
// source        : web/Optimisation/Min_circle_2.aw
// revision      : $Revision: 5.1 $
// revision_date : $Date: 1998/07/02 17:54:59 $
// author(s)     : Sven Schönherr
//                 Bernd Gärtner
//
// coordinator   : ETH Zürich (Bernd Gärtner)
//
// implementation: 2D Smallest Enclosing Circle
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

// Class implementation (continued)
// ================================
// I/O
// ---
template < class _Traits >
ostream&
operator << ( ostream& os, const CGAL_Min_circle_2<_Traits>& min_circle)
{
    typedef typename  CGAL_Min_circle_2<_Traits>::Point  Point;

    switch ( CGAL_get_mode( os)) {

      case CGAL_IO::PRETTY:
        os << endl;
        os << "CGAL_Min_circle_2( |P| = " << min_circle.number_of_points()
           << ", |S| = " << min_circle.number_of_support_points() << endl;
        os << "  P = {" << endl;
        os << "    ";
        copy( min_circle.points_begin(), min_circle.points_end(),
              ostream_iterator<Point>( os, ",\n    "));
        os << "}" << endl;
        os << "  S = {" << endl;
        os << "    ";
        copy( min_circle.support_points_begin(),
              min_circle.support_points_end(),
              ostream_iterator<Point>( os, ",\n    "));
        os << "}" << endl;
        os << "  circle = " << min_circle.circle() << endl;
        os << ")" << endl;
        break;

      case CGAL_IO::ASCII:
        copy( min_circle.points_begin(), min_circle.points_end(),
              ostream_iterator<Point>( os, "\n"));
        break;

      case CGAL_IO::BINARY:
        copy( min_circle.points_begin(), min_circle.points_end(),
              ostream_iterator<Point>( os));
        break;

      default:
        CGAL_optimisation_assertion_msg( false,
                                         "CGAL_get_mode( os) invalid!");
        break; }

    return( os);
}

template < class Traits >
istream&
operator >> ( istream& is, CGAL_Min_circle_2<Traits>& min_circle)
{
    switch ( CGAL_get_mode( is)) {

      case CGAL_IO::PRETTY:
        cerr << endl;
        cerr << "Stream must be in ascii or binary mode" << endl;
        break;

      case CGAL_IO::ASCII:
      case CGAL_IO::BINARY:
        typedef typename  CGAL_Min_circle_2<Traits>::Point   Point;
        typedef           istream_iterator<Point,ptrdiff_t>  Is_it;
        min_circle.clear();
        min_circle.insert( Is_it( is), Is_it());
        break;

      default:
        CGAL_optimisation_assertion_msg( false, "CGAL_IO::mode invalid!");
        break; }

    return( is);
}

// ===== EOF ==================================================================
