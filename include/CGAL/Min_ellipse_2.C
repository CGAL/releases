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
// file          : include/CGAL/Min_ellipse_2.C
// package       : Min_ellipse_2 (3.14)
// chapter       : Geometric Optimisation
//
// source        : web/Min_ellipse_2.aw
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2001/07/17 12:51:07 $
//
// author(s)     : Sven Schönherr, Bernd Gärtner
// coordinator   : ETH Zürich (Bernd Gärtner)
//
// implementation: 2D Smallest Enclosing Ellipse
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

CGAL_BEGIN_NAMESPACE

// Class implementation (continued)
// ================================
// I/O
// ---
template < class Traits_ >
std::ostream&
operator << ( std::ostream& os,
              const Min_ellipse_2<Traits_>& min_ellipse)
{
    CGAL_USING_NAMESPACE_STD

    typedef  Min_ellipse_2<Traits_>::Point  Point;
    typedef  ostream_iterator<Point>        Os_it;

    switch ( CGAL::get_mode( os)) {

      case CGAL::IO::PRETTY:
        os << endl;
        os << "CGAL::Min_ellipse_2( |P| = "<<min_ellipse.number_of_points()
           << ", |S| = " << min_ellipse.number_of_support_points() << endl;
        os << "  P = {" << endl;
        os << "    ";
        copy( min_ellipse.points_begin(), min_ellipse.points_end(),
              Os_it( os, ",\n    "));
        os << "}" << endl;
        os << "  S = {" << endl;
        os << "    ";
        copy( min_ellipse.support_points_begin(),
              min_ellipse.support_points_end(),
              Os_it( os, ",\n    "));
        os << "}" << endl;
        os << "  ellipse = " << min_ellipse.ellipse() << endl;
        os << ")" << endl;
        break;

      case CGAL::IO::ASCII:
        copy( min_ellipse.points_begin(), min_ellipse.points_end(),
              Os_it( os, "\n"));
        break;

      case CGAL::IO::BINARY:
        copy( min_ellipse.points_begin(), min_ellipse.points_end(),
              Os_it( os));
        break;

      default:
        CGAL_optimisation_assertion_msg( false,
                                         "CGAL::get_mode( os) invalid!");
        break; }

    return( os);
}

template < class Traits_ >
std::istream&
operator >> ( std::istream& is, CGAL::Min_ellipse_2<Traits_>& min_ellipse)
{
    CGAL_USING_NAMESPACE_STD

    switch ( CGAL::get_mode( is)) {

      case CGAL::IO::PRETTY:
        cerr << endl;
        cerr << "Stream must be in ascii or binary mode" << endl;
        break;

      case CGAL::IO::ASCII:
      case CGAL::IO::BINARY:
        typedef  Min_ellipse_2<Traits_>::Point  Point;
        typedef  istream_iterator<Point>       Is_it;
        min_ellipse.clear();
        min_ellipse.insert( Is_it( is), Is_it());
        break;

      default:
        CGAL_optimisation_assertion_msg( false, "CGAL::IO::mode invalid!");
        break; }

    return( is);
}

CGAL_END_NAMESPACE

// ===== EOF ==================================================================
