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
// chapter       : $CGAL_Chapter: Optimisation $
// file          : include/CGAL/Min_sphere_d.C
// package       : Min_sphere_d (1.13)
// source        : web/Optimisation/Min_sphere_d.aw
// revision      : $Revision: 1.2 $
// revision_date : $Date: 1999/02/26 12:13:50 $
// author(s)     : Sven Schönherr
//                 Bernd Gärtner
//
// coordinator   : ETH Zurich (Bernd Gärtner)
//
// implementation: dD Smallest Enclosing Sphere
// email         : cgal@cs.uu.nl
//
// ======================================================================

CGAL_BEGIN_NAMESPACE

// Class implementation (continued)
// ================================
// I/O
// ---
template < class Traits >
ostream&
operator << ( ostream& os, const Min_sphere_d<Traits>& min_sphere)
{
    typedef typename Min_sphere_d<Traits>::Point  Point;

    switch ( get_mode( os)) {

      case IO::PRETTY:
        os << endl;
        os << "Min_sphere_d( |P| = " << min_sphere.number_of_points()
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

      case IO::ASCII:
        os << min_sphere.number_of_points() << endl;
        copy( min_sphere.points_begin(), min_sphere.points_end(),
              ostream_iterator<Point>( os, "\n"));
        break;

      case IO::BINARY:
        os << min_sphere.number_of_points() << " ";
        copy( min_sphere.points_begin(), min_sphere.points_end(),
              ostream_iterator<Point>( os, " "));
        break;

      default:
        CGAL_optimisation_assertion_msg
            ( false, "get_mode( os) invalid!");
        break; }

    return( os);
}

template < class Traits >
istream&
operator >> ( istream& is, Min_sphere_d<Traits>& min_sphere)
{
    switch ( get_mode( is)) {

      case IO::PRETTY:
        cerr << endl;
        cerr << "Stream must be in ascii or binary mode" << endl;
        break;

      case IO::ASCII:
      case IO::BINARY:
      {
        min_sphere.clear();
        int n; is >> n;
        typename Min_sphere_d<Traits>::Point p;
        for (int i=0; i<n; ++i) {
            is >> p;
            min_sphere.insert (p);
        }
      } break;

      default:
        CGAL_optimisation_assertion_msg( false, "IO::mode invalid!");
        break;
 }

    return( is);
}



CGAL_END_NAMESPACE

// ===== EOF ==================================================================

