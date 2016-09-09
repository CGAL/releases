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
// file          : include/CGAL/IO/File_writer_OFF.h
// package       : Polyhedron_IO (1.11)
// chapter       : $CGAL_Chapter: Support Library ... $
// source        : polyhedron_io.fw
// revision      : $Revision: 1.8 $
// revision_date : $Date: 1998/10/08 22:46:22 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Writer for polyhedral surfaces in object file format (OFF)
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_IO_FILE_WRITER_OFF_H
#define CGAL_IO_FILE_WRITER_OFF_H 1
#ifndef CGAL_IO_BINARY_FILE_IO_H
#include <CGAL/IO/binary_file_io.h>
#endif // CGAL_IO_BINARY_FILE_IO_H
#ifndef CGAL_IO_FILE_HEADER_OFF_H
#include <CGAL/IO/File_header_OFF.h>
#endif // CGAL_IO_FILE_HEADER_OFF_H

#ifndef CGAL_PROTECT_IOSTREAM_H
#include <iostream.h>
#define CGAL_PROTECT_IOSTREAM_H
#endif // CGAL_PROTECT_IOSTREAM_H
#ifndef CGAL_PROTECT_STDDEF_H
#include <stddef.h>
#define CGAL_PROTECT_STDDEF_H
#endif // CGAL_PROTECT_STDDEF_H

class CGAL_File_writer_OFF {
    ostream*                    m_out;
    CGAL_File_header_OFF         m_header;
public:
    CGAL_File_writer_OFF( bool verbose = false) : m_header( verbose) {}
    CGAL_File_writer_OFF( const CGAL_File_header_OFF& h) : m_header( h) {}

    ostream&                    out()          { return *m_out;   }
    CGAL_File_header_OFF&        header()       { return m_header; }
    const CGAL_File_header_OFF&  header() const { return m_header; }

    void write_header( ostream& out,
                       size_t vertices,
                       size_t halfedges,
                       size_t facets,
                       int    normals = false);
    void write_footer() {
        if ( m_header.ascii() && m_header.comments())
            out() << "\n\n# End of OFF #";
        out() << endl;
    }
    void write_vertex( const double& x, const double& y, const double& z) {
        if ( m_header.binary()) {
            CGAL__Binary_write_float32( out(), x);
            CGAL__Binary_write_float32( out(), y);
            CGAL__Binary_write_float32( out(), z);
        } else {
            out() << '\n' << x << ' ' << y << ' ' << z;
        }
    }
    void write_normal( const double& x, const double& y, const double& z) {
        if ( m_header.binary()) {
            CGAL__Binary_write_float32( out(), x);
            CGAL__Binary_write_float32( out(), y);
            CGAL__Binary_write_float32( out(), z);
        } else {
            out() << ' ' << ' ' << x << ' ' << y << ' ' << z;
        }
    }
    void write_facet_header() {
        if ( m_header.ascii()) {
            if ( m_header.no_comments())
                out() << '\n';
            else {
                out() << "\n\n# " << m_header.size_of_facets()
                       << " facets\n";
                out() << "# ------------------------------------------"
                          "\n\n";
            }
        }
    }
    void write_facet_begin( size_t no) {
        if ( m_header.binary())
            CGAL__Binary_write_integer32( out(), no);
        else
            out() << no << ' ';
    }
    void write_facet_vertex_index( size_t index) {
        if ( m_header.binary())
            CGAL__Binary_write_integer32( out(), index);
        else
            out() << ' ' << index;
    }
    void write_facet_end() {
        if ( m_header.binary())
            CGAL__Binary_write_integer32( out(), 0);
        else
            out() << '\n';
    }
};
#endif // CGAL_IO_FILE_WRITER_OFF_H //
// EOF //
