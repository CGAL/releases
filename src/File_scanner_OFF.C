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
// file          : src/File_scanner_OFF.C
// package       : Polyhedron_IO (1.11)
// chapter       : $CGAL_Chapter: Support Library ... $
// source        : polyhedron_io.fw
// revision      : $Revision: 1.8 $
// revision_date : $Date: 1998/10/08 22:46:22 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// File scanner for an object in an object file format (OFF) file
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
    CGAL_assertion( current_vertex < size_of_vertices());
    if ( binary()) {
        float f;
        if ( has_normals() && ! normals_read) {
            CGAL__Binary_read_float32( m_in, f);
            CGAL__Binary_read_float32( m_in, f);
            CGAL__Binary_read_float32( m_in, f);
            if ( is_homogeneous())
                CGAL__Binary_read_float32( m_in, f);
        }
        if ( has_colors()) {
            // It is not well stated in the Geomview manual
            // how color is coded following a vertex. It is
            // parsed similar to the optional color for facets.
            CGAL_Integer32 k;
            CGAL__Binary_read_integer32( m_in, k);
            if (k<0 || k>4) {
                m_in.clear( ios::badbit);
                if ( verbose()) {
                    cerr << " " << endl;
                    cerr << "CGAL_File_scanner_OFF::" << endl;
                    cerr << "skip_to_next_vertex(): input error: bad "
                            " number of color indices at vertex "
                         << current_vertex << "." << endl;
                }
                set_off_header( false);
                return;
            }
            while (k--) {
                float dummy;
                CGAL__Binary_read_float32( m_in, dummy);
            }
        }
    } else {
        if ( has_normals() && ! normals_read) {
            double dummy;
            if ( is_homogeneous()) {
                m_in >> dummy >> dummy >> dummy >> dummy;
            } else {
                m_in >> dummy >> dummy >> dummy;
            }
        }
        if ( has_colors()) { // skip color entries (1 to 4)
            m_in >> CGAL_skip_until_EOL;
        }
    }
    if( ! m_in) {
        if ( verbose()) {
            cerr << " " << endl;
            cerr << "CGAL_File_scanner_OFF::" << endl;
            cerr << "skip_to_next_vertex(): input error: cannot read OFF "
                    "file beyond vertex " << current_vertex << "." << endl;
        }
        set_off_header( false);
        return;
    }
    normals_read = false;
}

void
CGAL_File_scanner_OFF::
skip_to_next_facet( int current_facet) {
    // Take care of trailing informations like color triples.
    if ( binary()) {
        CGAL_Integer32 k;
        CGAL__Binary_read_integer32( m_in, k);
        if (k<0 || k>4) {
            m_in.clear( ios::badbit);
            if ( verbose()) {
                cerr << " " << endl;
                cerr << "CGAL_File_scanner_OFF::" << endl;
                cerr << "skip_to_next_facet(): input error: bad number of "
                        "color indices at vertex " << current_facet << "."
                     << endl;
            }
            set_off_header( false);
            return;
        }
        while (k--) {
            float dummy;
            CGAL__Binary_read_float32( m_in, dummy);
        }
    } else {
        m_in >> CGAL_skip_until_EOL;
    }
}
// EOF //
