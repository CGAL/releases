// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/IO/scan_OFF.h
// package       : Polyhedron_IO (2.11)
// chapter       : $CGAL_Chapter: Support Library ... $
// source        : polyhedron_io.fw
// revision      : $Revision: 1.5 $
// revision_date : $Date: 1999/06/22 16:00:50 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Scan a Polyhedron_3 in object file format (OFF)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_IO_SCAN_OFF_H
#define CGAL_IO_SCAN_OFF_H 1
#ifndef CGAL_IO_POLYHEDRON_SCAN_OFF_H
#include <CGAL/IO/Polyhedron_scan_OFF.h>
#endif // CGAL_IO_POLYHEDRON_SCAN_OFF_H
//  Polyhedron
#ifndef CGAL_POLYHEDRON_3_H
#include <CGAL/Polyhedron_3.h>
#endif

CGAL_BEGIN_NAMESPACE

template <class Traits, class HDS> inline
void scan_OFF( std::istream& in, Polyhedron_3<Traits,HDS>& P,
               bool verbose = false) {
    // reads a polyhedron from `in' and appends it to P.
    typedef Polyhedron_scan_OFF<HDS> Scanner;
    Scanner scanner( in, verbose);
    P.delegate(scanner);
}

template <class Traits, class HDS> inline
void scan_OFF( std::istream& in,
               Polyhedron_3<Traits,HDS>& P,
               File_header_OFF& header) {
    // reads a polyhedron from `in' and appends it to P.
    // Returns also the File_header_OFF structure of the object.
    typedef Polyhedron_scan_OFF<HDS> Scanner;
    Scanner scanner( in, header.verbose());
    P.delegate(scanner);
    header = scanner.header();
}

CGAL_END_NAMESPACE
#endif // CGAL_IO_SCAN_OFF_H //
// EOF //
