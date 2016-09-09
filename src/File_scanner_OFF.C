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
// file          : src/File_scanner_OFF.C
// package       : Polyhedron_IO (1.9)
// chapter       : $CGAL_Chapter: Support Library ... $
// source        : polyhedron_io.fw
// revision      : $Revision: 1.6 $
// revision_date : $Date: 1998/06/03 20:34:54 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// File scanner for an object in an object file format (OFF) file
//
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif // CGAL_BASIC_H
#ifndef CGAL_PROTECT_STDLIB_H
#include <stdlib.h>
#define CGAL_PROTECT_STDLIB_H
#endif // CGAL_PROTECT_STDLIB_H
#ifndef CGAL_PROTECT_IOSTREAM_H
#include <iostream.h>
#define CGAL_PROTECT_IOSTREAM_H
#endif // CGAL_PROTECT_IOSTREAM_H
#ifndef CGAL_IO_BINARY_FILE_IO_H
#include <CGAL/IO/binary_file_io.h>
#endif // CGAL_IO_BINARY_FILE_IO_H
#ifndef CGAL_IO_FILE_SCANNER_OFF_H
#include <CGAL/IO/File_scanner_OFF.h>
#endif // CGAL_IO_FILE_SCANNER_OFF_H

void
CGAL_File_scanner_OFF::
skip_to_next_vertex( int current_vertex) {
    CGAL_assertion( current_vertex < n_vertices);
    if ( m_binary) {
        float f;
        if ( m_normals && ! normals_read) {
            CGAL__Binary_read_float32( m_in, f);
            CGAL__Binary_read_float32( m_in, f);
            CGAL__Binary_read_float32( m_in, f);
            if ( m_tag4)
                CGAL__Binary_read_float32( m_in, f);
        }
        if ( m_colors) {
            // It is not well stated in the Geomview manual
            // how color is coded following a vertex. It is
            // parsed similar to the optional color for facets.
            CGAL_Integer32 k;
            CGAL__Binary_read_integer32( m_in, k);
            if (k<0 || k>4) {
                m_in.clear( ios::badbit);
                if ( m_verbose) {
                    cerr << " " << endl;
                    cerr << "CGAL_File_scanner_OFF::" << endl;
                    cerr << "skip_to_next_vertex(): input error: bad "
                            " number of color indices at vertex "
                         << current_vertex << "." << endl;
                }
                return;
            }
            while (k--) {
                float dummy;
                CGAL__Binary_read_float32( m_in, dummy);
            }
        }
    } else {
        if ( m_normals && ! normals_read) {
            double dummy;
            if ( m_tag4) {
                m_in >> dummy >> dummy >> dummy >> dummy;
            } else {
                m_in >> dummy >> dummy >> dummy;
            }
        }
        if ( m_colors) { // skip color entries (1 to 4)
            char c;
            while ( m_in.get(c) && c != '\n')
                ;
        }
    }
    if( ! m_in) {
        if ( m_verbose) {
            cerr << " " << endl;
            cerr << "CGAL_File_scanner_OFF::" << endl;
            cerr << "skip_to_next_vertex(): input error: cannot read OFF "
                    "file beyond vertex " << current_vertex << "." << endl;
        }
        return;
    }
    normals_read = false;
}

void
CGAL_File_scanner_OFF::
skip_to_next_facet( int current_facet) {
    // Take care of trailing informations like color triples.
    if ( m_binary) {
        CGAL_Integer32 k;
        CGAL__Binary_read_integer32( m_in, k);
        if (k<0 || k>4) {
            m_in.clear( ios::badbit);
            if ( m_verbose) {
                cerr << " " << endl;
                cerr << "CGAL_File_scanner_OFF::" << endl;
                cerr << "skip_to_next_facet(): input error: bad number of "
                        "color indices at vertex " << current_facet << "."
                     << endl;
            }
            return;
        }
        while (k--) {
            float dummy;
            CGAL__Binary_read_float32( m_in, dummy);
        }
    } else {
        char c;
        // Scan over them until the end of line.
        while( m_in.get(c) && c != '\n')
            ;
    }
}
// EOF //
