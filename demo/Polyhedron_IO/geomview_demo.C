// ============================================================================
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
// file          : demo/Polyhedron_IO/geomview_demo.C
// package       : $CGAL_Package: Polyhedron_IO 2.11 (04 Feb 2000) $
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2001/06/29 06:24:52 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Illustrate output of a Polyhedron_3 to Geomview_stream.
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#include <CGAL/Cartesian.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/IO/Polyhedron_geomview_ostream.h>

typedef  CGAL::Cartesian<double>               Kernel;
typedef  Kernel::Point_3                       Point;
typedef  CGAL::Polyhedron_3<Kernel>            Polyhedron;

int main() {
    Point p( 1.0, 0.0, 0.0);
    Point q( 0.0, 1.0, 0.0);
    Point r( 0.0, 0.0, 1.0);
    Point s( 0.0, 0.0, 0.0);
    Polyhedron P;
    P.make_tetrahedron( p,q,r,s);
    CGAL::Geomview_stream geo;
    geo << CGAL::GREEN << P;

    // wait for a mouse click.
    Point click;
    geo >> click;
    return 0;
}
// EOF //
