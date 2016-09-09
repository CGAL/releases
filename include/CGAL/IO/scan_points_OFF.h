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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.1
// release_date  : 1998, July 24
//
// file          : include/CGAL/IO/scan_points_OFF.h
// package       : Polyhedron_IO (1.9)
// chapter       : $CGAL_Chapter: Support Library ... $
// source        : polyhedron_io.fw
// revision      : $Revision: 1.6 $
// revision_date : $Date: 1998/06/03 20:34:54 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// scans only the points from object file format (OFF) file
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_IO_SCAN_POINTS_OFF_H
#define CGAL_IO_SCAN_POINTS_OFF_H 1
#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif

#ifndef CGAL_PROTECT_STDDEF_H
#include <stddef.h>
#define CGAL_PROTECT_STDDEF_H
#endif // CGAL_PROTECT_STDDEF_H

#ifndef CGAL_IO_FILE_HEADER_OFF_H
#include <CGAL/IO/File_header_OFF.h>
#endif // CGAL_IO_FILE_HEADER_OFF_H

#ifndef CGAL_IO_FILE_SCANNER_OFF_H
#include <CGAL/IO/File_scanner_OFF.h>
#endif // CGAL_IO_FILE_SCANNER_OFF_H

#ifndef CGAL_PROTECT_IOSTREAM_H
#include <iostream.h>
#define CGAL_PROTECT_IOSTREAM_H
#endif // CGAL_PROTECT_IOSTREAM_H

template <class OutputIterator, class Point>
OutputIterator
CGAL_scan_points_OFF( CGAL_File_scanner_OFF& scanner,
                     OutputIterator points, const Point*)
{
    // scans the points from a polyhedral surface in OFF from `scanner',
    // the OFF header has already been scanned.
    // read in all vertices
    typedef typename Point::RT RT;
    int  i;
    for ( i = 0; i < scanner.size_of_vertices(); i++) {
        CGAL_file_scan_vertex( scanner, *points);
        ++ points;
        scanner.skip_to_next_vertex( i);
    }
    return points;
}
template <class OutputIterator>
OutputIterator
CGAL_scan_points_OFF( CGAL_File_scanner_OFF& scanner,
                     OutputIterator points)
{
    return CGAL_scan_points_OFF( scanner, points, value_type(points));
}

template <class Point>
Point*
CGAL_scan_points_OFF( istream& in, Point*& points, bool verbose = false) {
    // scans the points from a polyhedral surface in OFF from `in'
    // and stores them in a dynamically allocated array in `points'.
    // The user is responsible to `delete[]' the array when appropriate.
    // Returns the past-the-end iterator for the array `points'.
    CGAL_File_scanner_OFF scanner( in, verbose);
    if ( ! in) {
        if ( verbose) {
            cerr << " " << endl;
            cerr << "CGAL_scan_points_OFF(): "
                    "input error: file format is not in OFF." << endl;
        }
        points = 0;
        return 0;
    }
    // Allocate points.
    points = new Point[ scanner.size_of_vertices()];
    return CGAL_scan_points_OFF( scanner, points);
}
#endif // CGAL_IO_SCAN_POINTS_OFF_H //
// EOF //
