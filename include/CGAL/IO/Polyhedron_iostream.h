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
// file          : include/CGAL/IO/Polyhedron_iostream.h
// package       : Polyhedron_IO (1.11)
// chapter       : $CGAL_Chapter: Support Library ... $
// source        : polyhedron_io.fw
// revision      : $Revision: 1.8 $
// revision_date : $Date: 1998/10/08 22:46:22 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Stream operators for Polyhedron_3 IO in object file format (OFF)
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_IO_POLYHEDRON_IOSTREAM_H
#define CGAL_IO_POLYHEDRON_IOSTREAM_H 1
#ifndef CGAL_PROTECT_IOSTREAM_H
#include <iostream.h>
#define CGAL_PROTECT_IOSTREAM_H
#endif // CGAL_PROTECT_IOSTREAM_H

#ifndef CGAL_IO_PRINT_OFF_H
#include <CGAL/IO/print_OFF.h>
#endif // CGAL_IO_PRINT_OFF_H

#ifndef CGAL_IO_SCAN_OFF_H
#include <CGAL/IO/scan_OFF.h>
#endif // CGAL_IO_SCAN_OFF_H

//  CGAL_Polyhedron
#ifndef CGAL_POLYHEDRON_3_H
#include <CGAL/Polyhedron_3.h>
#endif

template <class Traits, class HDS> inline
ostream& operator<<( ostream& out, const CGAL_Polyhedron_3<Traits,HDS>& P) {
    // writes P to `out' in PRETTY, ASCII or BINARY format
    // as the stream indicates.
    CGAL_File_header_OFF header( CGAL_is_binary( out));
    CGAL_print_OFF( out, P, header);
    return out;
}

template <class Traits, class HDS> inline
istream& operator>>( istream& in, CGAL_Polyhedron_3<Traits,HDS>& P) {
    // reads a polyhedron from `in' and appends it to P.
    CGAL_scan_OFF( in, P);
    return in;
}
#endif // CGAL_IO_POLYHEDRON_IOSTREAM_H //
// EOF //
