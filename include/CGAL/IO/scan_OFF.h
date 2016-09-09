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
// file          : include/CGAL/IO/scan_OFF.h
// package       : Polyhedron_IO (2.5)
// chapter       : $CGAL_Chapter: Support Library ... $
// source        : polyhedron_io.fw
// revision      : $Revision: 1.4 $
// revision_date : $Date: 1999/03/24 11:16:26 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Scan a Polyhedron_3 in object file format (OFF)
// email         : cgal@cs.uu.nl
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
