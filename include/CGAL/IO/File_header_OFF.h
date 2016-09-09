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
// file          : include/CGAL/IO/File_header_OFF.h
// package       : Polyhedron_IO (1.9)
// chapter       : $CGAL_Chapter: Support Library ... $
// source        : polyhedron_io.fw
// revision      : $Revision: 1.6 $
// revision_date : $Date: 1998/06/03 20:34:54 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// File header information of an object file format (OFF) file
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_IO_FILE_HEADER_OFF_H
#define CGAL_IO_FILE_HEADER_OFF_H 1
#ifndef CGAL_IO_FILE_INFO_H
#include <CGAL/IO/File_info.h>
#endif // CGAL_IO_FILE_INFO_H

#ifndef CGAL_PROTECT_IOSTREAM_H
#include <iostream.h>
#define CGAL_PROTECT_IOSTREAM_H
#endif // CGAL_PROTECT_IOSTREAM_H

// Info structure for OFF file headers
// ===================================
class CGAL_File_header_OFF {
protected:
    bool m_verbose;     // Print error messages if true.
    bool m_skel;        // signals SKEL format instead of OFF format.
    int  n_vertices;
    int  n_halfedges;
    int  n_facets;
    int  m_offset;      // index offset for vertices
    bool m_colors;      // COFF detected.
    bool m_normals;     // NOFF format stores also normals at vertices.
    bool m_tag4;        // 4OFF detected.
    bool m_tagDim;      // nOFF detected (will not be supported).
    int  m_dim;         // dimension for nOFF (will not be supported).
    bool m_binary;      // OFF in binary format.
    CGAL_File_info  m_file_info;
public:
    CGAL_File_header_OFF( istream& in, bool verbose = false);

    bool verbose() const            { return m_verbose; }
    bool is_SKEL() const            { return m_skel; }   // SKEL format.
    bool is_OFF()  const            { return ! m_skel; } // OFF format.
    int  size_of_vertices()  const  { return n_vertices; }
    int  size_of_halfedges() const  { return n_halfedges; }
    int  size_of_facets()    const  { return n_facets; }
    int  index_offset() const       { return m_offset; }
    bool has_colors() const         { return m_colors; } // COFF detected.
    bool has_normals() const        { return m_normals;} // NOFF format.
    bool is_homogeneous() const     { return m_tag4; }   // 4OFF detected.
                           // nOFF detected. (will not be supported).
    bool n_dimsional() const        { return m_tagDim; }
                           // dimension for nOFF (will not be supported).
    int  dimension() const          { return m_dim; }
    bool is_binary() const          { return m_binary; } // OFF BINARY.
    CGAL_File_info&
         file_info()                { return m_file_info; }
    const CGAL_File_info&
         file_info() const          { return m_file_info; }
};
#endif // CGAL_IO_FILE_HEADER_OFF_H //
// EOF //
