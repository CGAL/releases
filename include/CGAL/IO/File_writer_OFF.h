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
// file          : include/CGAL/IO/File_writer_OFF.h
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
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_IO_FILE_WRITER_OFF_H
#define CGAL_IO_FILE_WRITER_OFF_H 1
#ifndef CGAL_IO_BINARY_FILE_IO_H
#include <CGAL/IO/binary_file_io.h>
#endif // CGAL_IO_BINARY_FILE_IO_H
#ifndef CGAL_IO_FILE_INFO_H
#include <CGAL/IO/File_info.h>
#endif // CGAL_IO_FILE_INFO_H

#ifndef CGAL_PROTECT_IOSTREAM_H
#include <iostream.h>
#define CGAL_PROTECT_IOSTREAM_H
#endif // CGAL_PROTECT_IOSTREAM_H

class CGAL_File_writer_OFF {
    ostream*  out;
    size_t   _facets;
    bool     _binary;
    bool     _nocomments;
    bool     _skel;
    const CGAL_File_info*  file_info;
public:
    CGAL_File_writer_OFF( bool binary = false,
                         bool nocomments = false,
                         bool skel = false)
        : _binary( binary),
          _nocomments( nocomments),
          _skel( skel),
          file_info(0) {}
    CGAL_File_writer_OFF( const CGAL_File_info& info,
                         bool binary = false,
                         bool nocomments = false,
                         bool skel = false)
        : _binary( binary),
          _nocomments( nocomments),
          _skel( skel),
          file_info( &info) {}
    void set_skel( bool skel)   { _skel = skel; }
    void header( ostream& out,
                 size_t vertices,
                 size_t halfedges,
                 size_t facets,
                 int    normals = false);
    void footer() {
        if ( ! _binary && ! _nocomments)
            *out << "\n\n# End of OFF #";
        *out << endl;
    }
    void write_vertex( const double& x, const double& y, const double& z) {
        if ( _binary) {
            CGAL__Binary_write_float32( *out, x);
            CGAL__Binary_write_float32( *out, y);
            CGAL__Binary_write_float32( *out, z);
        } else {
            *out << '\n' << x << ' ' << y << ' ' << z;
        }
    }
    void write_normal( const double& x, const double& y, const double& z) {
        if ( _binary) {
            CGAL__Binary_write_float32( *out, x);
            CGAL__Binary_write_float32( *out, y);
            CGAL__Binary_write_float32( *out, z);
        } else {
            *out << ' ' << ' ' << x << ' ' << y << ' ' << z;
        }
    }
    void write_facet_header() {
        if ( ! _binary) {
            if ( _nocomments)
                *out << '\n';
            else {
                *out << "\n\n# " << _facets << " facets\n";
                *out << "# ------------------------------------------\n\n";
            }
        }
    }
    void write_facet_begin( size_t no) {
        if ( _binary)
            CGAL__Binary_write_integer32( *out, no);
        else
            *out << no << ' ';
    }
    void write_facet_vertex_index( size_t index) {
        if ( _binary)
            CGAL__Binary_write_integer32( *out, index);
        else
            *out << ' ' << index;
    }
    void write_facet_end() {
        if ( _binary)
            CGAL__Binary_write_integer32( *out, 0);
        else
            *out << '\n';
    }
};
#endif // CGAL_IO_FILE_WRITER_OFF_H //
// EOF //
