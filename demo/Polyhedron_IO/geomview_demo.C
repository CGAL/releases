// ============================================================================
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
// file          : geomview_demo.C
// package       : $CGAL_Package: Polyhedron_IO 2.5 (29 Apr 1999) $
// revision      : $Revision: 1.3 $
// revision_date : $Date: 1999/03/09 22:18:32 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Illustrate output of a Polyhedron_3 to Geomview_stream.
// email         : cgal@cs.uu.nl
//
// ======================================================================

#include <CGAL/Cartesian.h>
#include <CGAL/Point_3.h>
#include <CGAL/Halfedge_data_structure_polyhedron_default_3.h>
#include <CGAL/Polyhedron_default_traits_3.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/IO/Polyhedron_geomview_ostream.h>

typedef  CGAL::Cartesian<double>                               R;
typedef  CGAL::Point_3<R>                                      Point;
typedef  CGAL::Polyhedron_default_traits_3<R>                  Traits;
typedef  CGAL::Halfedge_data_structure_polyhedron_default_3<R> HDS;
typedef  CGAL::Polyhedron_3<Traits,HDS>                        Polyhedron;

int main() {
    Point p( 1.0, 0.0, 0.0);
    Point q( 0.0, 1.0, 0.0);
    Point r( 0.0, 0.0, 1.0);
    Point s( 0.0, 0.0, 0.0);
    Polyhedron P;
    P.make_tetrahedron( p,q,r,s);
    CGAL::Geomview_stream geo;
    geo << P;

    // wait for a mouse click.
    Point click;
    geo >> click;
    return 0;
}
// EOF //
