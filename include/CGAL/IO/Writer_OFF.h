// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/IO/Writer_OFF.h
// package       : Polyhedron_IO (3.11)
// chapter       : Support Library
//
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2001/12/17 12:40:59 $
//
// author(s)     : Lutz Kettner
// coordinator   : INRIA, Sophia Antipolis
//
// STL compliant interface to write OFF.
// email         : contact@cgal.org
// www           : http://www.cgal.org
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

CGAL_BEGIN_NAMESPACE

template < class Pt >
class Writer_OFF : public Generic_writer<File_writer_OFF,Pt> {
public:
    Writer_OFF( std::ostream& out,
                std::size_t   v,
                std::size_t   h,
                std::size_t   f,
                bool          verbose = false)
    : Generic_writer<File_writer_OFF,Pt>(
        File_writer_OFF( verbose), out, v, h, f
    ) {}
    Writer_OFF( std::ostream& out,
                std::size_t   v,
                std::size_t   h,
                std::size_t   f,
                const File_header_OFF& header)
    : Generic_writer<File_writer_OFF,Pt>(
        File_writer_OFF( header), out, v, h, f
    ) {}
};

CGAL_END_NAMESPACE
#endif // CGAL_IO_WRITER_OFF_H //
// EOF //
