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
// file          : src/File_writer_OFF.C
// package       : Polyhedron_IO (1.9)
// chapter       : $CGAL_Chapter: Support Library ... $
// source        : polyhedron_io.fw
// revision      : $Revision: 1.6 $
// revision_date : $Date: 1998/06/03 20:34:54 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Writer for polyhedral surfaces in object file format (OFF)
//
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif // CGAL_BASIC_H
#ifndef CGAL_PROTECT_IOSTREAM_H
#include <iostream.h>
#define CGAL_PROTECT_IOSTREAM_H
#endif // CGAL_PROTECT_IOSTREAM_H
#ifndef CGAL_IO_FILE_WRITER_OFF_H
#include <CGAL/IO/File_writer_OFF.h>
#endif // CGAL_IO_FILE_WRITER_OFF_H

void
CGAL_File_writer_OFF::
header( ostream& o, size_t vertices, size_t halfedges, size_t facets,
        int normals) {
    out     = &o;
    _facets = facets;
    // Print header.
    if ( ! _nocomments) {
        *out << "# file written from a CGAL tool\n";
        *out << "#CBP halfedges " << halfedges << endl;
        if ( file_info) {
            *out << "# polyhedral_surface "
                 << (file_info->polyhedral_surface ? '1' : '0') << endl;
            *out << "# normalized_to_sphere "
                 << (file_info->normalized_to_sphere ? '1' : '0') << endl;
            *out << "# triangulated "
                 << (file_info->triangulated ? '1' : '0') << endl;
            *out << "# non_empty_facets "
                 << (file_info->non_empty_facets ? '1' : '0') << endl;
            *out << "# radius " << file_info->radius << endl;
            *out << "# rounded " << (file_info->rounded ? '1' : '0')<<endl;
            *out << "# rounded_bits " << file_info->rounded_bits << endl;
            *out << "# terrain " << (file_info->terrain ? '1' : '0')<<endl;
        }
        *out << "# ENDCBP\n\n";
    }
    if ( normals)
        *out << 'N';
    if ( _skel)
        *out << "SKEL";
    else
        *out << "OFF";
    if ( _binary) {
        *out << " BINARY\n";
        CGAL__Binary_write_integer32( *out, vertices);
        CGAL__Binary_write_integer32( *out, facets);
        if ( ! _skel)
            CGAL__Binary_write_integer32( *out, 0);
    } else {
        *out << '\n';
        *out << vertices << ' '<< facets;
        if ( ! _skel)
            *out << " 0";
        if ( ! _nocomments) {
            *out << "\n\n# " << vertices << " vertices\n";
            *out << "# ------------------------------------------\n";
        }
        *out << endl;
    }
}
// EOF //
