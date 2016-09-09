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
// file          : include/CGAL/IO/Writer_OFF.h
// package       : Polyhedron_IO (1.9)
// chapter       : $CGAL_Chapter: Support Library ... $
// source        : polyhedron_io.fw
// revision      : $Revision: 1.6 $
// revision_date : $Date: 1998/06/03 20:34:54 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// STL compliant interface to write OFF.
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_IO_WRITER_OFF_H
#define CGAL_IO_WRITER_OFF_H 1
#ifndef CGAL_IO_FILE_WRITER_OFF_H
#include <CGAL/IO/File_writer_OFF.h>
#endif // CGAL_IO_FILE_WRITER_OFF_H
#ifndef CGAL_IO_GENERIC_WRITER_H
#include <CGAL/IO/Generic_writer.h>
#endif // CGAL_IO_GENERIC_WRITER_H

template < class Pt >
class CGAL_Writer_OFF : public CGAL_Generic_writer<CGAL_File_writer_OFF,Pt> {
public:
    CGAL_Writer_OFF( ostream& out, size_t v, size_t h, size_t f,
                    bool binary = false,
                    bool nocomments = false,
                    bool skel = false)
    : CGAL_Generic_writer<CGAL_File_writer_OFF,Pt>(
        CGAL_File_writer_OFF( binary, nocomments, skel), out, v, h, f
    ) {}
    CGAL_Writer_OFF( ostream& out, size_t v, size_t h, size_t f,
                    const CGAL_File_info& info,
                    bool binary = false,
                    bool nocomments = false,
                    bool skel = false)
    : CGAL_Generic_writer<CGAL_File_writer_OFF,Pt>(
        CGAL_File_writer_OFF( info, binary, nocomments, skel), out, v, h, f
    ) {}
};
#endif // CGAL_IO_WRITER_OFF_H //
// EOF //
