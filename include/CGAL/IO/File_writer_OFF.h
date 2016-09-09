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
// file          : include/CGAL/IO/File_writer_OFF.h
// package       : Polyhedron_IO (2.11)
// chapter       : $CGAL_Chapter: Support Library ... $
// source        : polyhedron_io.fw
// revision      : $Revision: 1.5 $
// revision_date : $Date: 1999/06/22 16:00:50 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Writer for polyhedral surfaces in object file format (OFF)
// email         : contact@cgal.org
// www           : http://www.cgal.org
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
#ifndef CGAL_PROTECT_IOSTREAM
#include <iostream>
#define CGAL_PROTECT_IOSTREAM
#endif
#ifndef CGAL_PROTECT_CSTDDEF
#include <cstddef>
#define CGAL_PROTECT_CSTDDEF
#endif

CGAL_BEGIN_NAMESPACE

class File_writer_OFF {
    std::ostream*           m_out;
    File_header_OFF         m_header;
public:
    File_writer_OFF( bool verbose = false) : m_header( verbose) {}
    File_writer_OFF( const File_header_OFF& h) : m_header( h) {}

    std::ostream&           out()          { return *m_out;   }
    File_header_OFF&        header()       { return m_header; }
    const File_header_OFF&  header() const { return m_header; }

    void write_header( std::ostream& out,
                       std::size_t   vertices,
                       std::size_t   halfedges,
                       std::size_t   facets,
                       int           normals = false);
    void write_footer() {
        if ( m_header.ascii() && m_header.comments())
            out() << "\n\n# End of OFF #";
        out() << std::endl;
    }
    void write_vertex( const double& x, const double& y, const double& z) {
        if ( m_header.binary()) {
            _Binary_write_float32( out(), x);
            _Binary_write_float32( out(), y);
            _Binary_write_float32( out(), z);
        } else {
            out() << '\n' << x << ' ' << y << ' ' << z;
        }
    }
    void write_normal( const double& x, const double& y, const double& z) {
        if ( m_header.binary()) {
            _Binary_write_float32( out(), x);
            _Binary_write_float32( out(), y);
            _Binary_write_float32( out(), z);
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
    void write_facet_begin( std::size_t no) {
        if ( m_header.binary())
            _Binary_write_integer32( out(), no);
        else
            out() << no << ' ';
    }
    void write_facet_vertex_index( std::size_t index) {
        if ( m_header.binary())
            _Binary_write_integer32( out(), index);
        else
            out() << ' ' << index;
    }
    void write_facet_end() {
        if ( m_header.binary())
            _Binary_write_integer32( out(), 0);
        else
            out() << '\n';
    }
};

CGAL_END_NAMESPACE
#endif // CGAL_IO_FILE_WRITER_OFF_H //
// EOF //
