// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// chapter       : $CGAL_Chapter: Optimisation $
// file          : include/CGAL/Min_sphere_d.C
// package       : Min_sphere_d (2.30)
// source        : web/Optimisation/Min_sphere_d.aw
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2002/02/05 10:18:34 $
// author(s)     : Sven Schönherr
//                 Bernd Gärtner
//
// coordinator   : ETH Zurich (Bernd Gärtner)
//
// implementation: dD Smallest Enclosing Sphere
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#include <iterator>

CGAL_BEGIN_NAMESPACE

// Class implementation (continued)
// ================================
// I/O
// ---
template < class Traits >
std::ostream&
operator << ( std::ostream& os, const Min_sphere_d<Traits>& min_sphere)
{
    typedef typename Min_sphere_d<Traits>::Point  Point;

    switch ( get_mode( os)) {

      case IO::PRETTY:
        os << std::endl;
        os << "Min_sphere_d( |P| = " << min_sphere.number_of_points()
           << ", |S| = " << min_sphere.number_of_support_points()
           << std::endl;
        os << "  P = {" << std::endl;
        os << "    ";
        std::copy( min_sphere.points_begin(), min_sphere.points_end(),
              std::ostream_iterator<Point>( os, ",\n    "));
        os << "}" << std::endl;
        os << "  S = {" << std::endl;
        os << "    ";
        std::copy( min_sphere.support_points_begin(),
              min_sphere.support_points_end(),
              std::ostream_iterator<Point>( os, ",\n    "));
        os << "}" << std::endl;
        os << "  center = " << min_sphere.center() << std::endl;
        os << "  squared radius = " << min_sphere.squared_radius()
           << std::endl;
        os << ")" << std::endl;
        break;

      case IO::ASCII:
        os << min_sphere.number_of_points() << std::endl;
        std::copy( min_sphere.points_begin(), min_sphere.points_end(),
              std::ostream_iterator<Point>( os, "\n"));
        break;

      case IO::BINARY:
        os << min_sphere.number_of_points() << " ";
        std::copy( min_sphere.points_begin(), min_sphere.points_end(),
              std::ostream_iterator<Point>( os, " "));
        break;

      default:
        CGAL_optimisation_assertion_msg
            ( false, "get_mode( os) invalid!");
        break; }

    return( os);
}

template < class Traits >
std::istream&
operator >> ( std::istream& is, Min_sphere_d<Traits>& min_sphere)
{
    switch ( get_mode( is)) {

      case IO::PRETTY:
        std::cerr << std::endl;
        std::cerr << "Stream must be in ascii or binary mode" << std::endl;
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

