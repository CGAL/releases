// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
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
// chapter       : $CGAL_Chapter: Optimisation $
// file          : include/CGAL/Min_sphere_d.C
// package       : Min_sphere_d (1.9)
// source        : web/Optimisation/Min_sphere_d.aw
// revision      : $Revision: 1.1 $
// revision_date : $Date: 1998/06/05 16:16:13 $
// author(s)     : Sven Schönherr
//                 Bernd Gärtner
//
// coordinator   : ETH Zurich (Bernd Gärtner)
//
// implementation: dD Smallest Enclosing Sphere
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

// Class implementation (continued)
// ================================
// I/O
// ---
template < class Traits >
ostream&
operator << ( ostream& os, const CGAL_Min_sphere_d<Traits>& min_sphere)
{
    typedef typename CGAL_Min_sphere_d<Traits>::Point  Point;

    switch ( CGAL_get_mode( os)) {

      case CGAL_IO::PRETTY:
        os << endl;
        os << "CGAL_Min_sphere_d( |P| = " << min_sphere.number_of_points()
           << ", |S| = " << min_sphere.number_of_support_points() << endl;
        os << "  P = {" << endl;
        os << "    ";
        copy( min_sphere.points_begin(), min_sphere.points_end(),
              ostream_iterator<Point>( os, ",\n    "));
        os << "}" << endl;
        os << "  S = {" << endl;
        os << "    ";
        copy( min_sphere.support_points_begin(),
              min_sphere.support_points_end(),
              ostream_iterator<Point>( os, ",\n    "));
        os << "}" << endl;
        os << "  center = " << min_sphere.center() << endl;
        os << "  squared radius = " << min_sphere.squared_radius() << endl;
        os << ")" << endl;
        break;

      case CGAL_IO::ASCII:
        os << min_sphere.number_of_points() << endl;
        copy( min_sphere.points_begin(), min_sphere.points_end(),
              ostream_iterator<Point>( os, "\n"));
        break;

      case CGAL_IO::BINARY:
        os << min_sphere.number_of_points() << " ";
        copy( min_sphere.points_begin(), min_sphere.points_end(),
              ostream_iterator<Point>( os, " "));
        break;

      default:
        CGAL_optimisation_assertion_msg
            ( false, "CGAL_get_mode( os) invalid!");
        break; }

    return( os);
}

template < class Traits >
istream&
operator >> ( istream& is, CGAL_Min_sphere_d<Traits>& min_sphere)
{
    switch ( CGAL_get_mode( is)) {

      case CGAL_IO::PRETTY:
        cerr << endl;
        cerr << "Stream must be in ascii or binary mode" << endl;
        break;

      case CGAL_IO::ASCII:
      case CGAL_IO::BINARY:
      {
        min_sphere.clear();
        int n; is >> n;
        typename CGAL_Min_sphere_d<Traits>::Point p;
        for (int i=0; i<n; ++i) {
            is >> p;
            min_sphere.insert (p);
        }
      } break;

      default:
        CGAL_optimisation_assertion_msg( false, "CGAL_IO::mode invalid!");
        break;
 }

    return( is);
}



// ===== EOF ==================================================================

