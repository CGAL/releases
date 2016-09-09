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
// file          : src/File_scanner_OFF.C
// package       : Polyhedron_IO (3.11)
// chapter       : Support Library
//
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2001/12/17 12:41:02 $
//
// author(s)     : Lutz Kettner
// coordinator   : INRIA, Sophia Antipolis
//
// File scanner for an object in an object file format (OFF) file
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif // CGAL_BASIC_H
#ifndef CGAL_PROTECT_CSTDLIB
#include <cstdlib>
#define CGAL_PROTECT_CSTDLIB
#endif
#ifndef CGAL_PROTECT_IOSTREAM
#include <iostream>
#define CGAL_PROTECT_IOSTREAM
#endif
#ifndef CGAL_IO_BINARY_FILE_IO_H
#include <CGAL/IO/binary_file_io.h>
#endif // CGAL_IO_BINARY_FILE_IO_H
#ifndef CGAL_IO_FILE_SCANNER_OFF_H
#include <CGAL/IO/File_scanner_OFF.h>
#endif // CGAL_IO_FILE_SCANNER_OFF_H

CGAL_BEGIN_NAMESPACE

void
File_scanner_OFF::
skip_to_next_vertex( int current_vertex) {
    CGAL_assertion( current_vertex < size_of_vertices());
    if ( binary()) {
        float f;
        if ( has_normals() && ! normals_read) {
            I_Binary_read_big_endian_float32( m_in, f);
            I_Binary_read_big_endian_float32( m_in, f);
            I_Binary_read_big_endian_float32( m_in, f);
            if ( is_homogeneous())
                I_Binary_read_big_endian_float32( m_in, f);
        }
        if ( has_colors()) {
            // It is not well stated in the Geomview manual
            // how color is coded following a vertex. It is
            // parsed similar to the optional color for facets.
            Integer32 k;
            I_Binary_read_big_endian_integer32( m_in, k);
            if (k<0 || k>4) {
                m_in.clear( std::ios::badbit);
                if ( verbose()) {
                    std::cerr << " " << std::endl;
                    std::cerr << "File_scanner_OFF::" << std::endl;
                    std::cerr << "skip_to_next_vertex(): input error: bad "
                                 " number of color indices at vertex "
                              << current_vertex << "." << std::endl;
                }
                set_off_header( false);
                return;
            }
            while (k--) {
                float dummy;
                I_Binary_read_big_endian_float32( m_in, dummy);
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
            m_in >> skip_until_EOL;
        }
    }
    if( ! m_in) {
        if ( verbose()) {
            std::cerr << " " << std::endl;
            std::cerr << "File_scanner_OFF::" << std::endl;
            std::cerr << "skip_to_next_vertex(): input error: cannot read "
                         "OFF file beyond vertex " << current_vertex << "."
                      << std::endl;
        }
        set_off_header( false);
        return;
    }
    normals_read = false;
}

void
File_scanner_OFF::
skip_to_next_facet( int current_facet) {
    // Take care of trailing informations like color triples.
    if ( binary()) {
        Integer32 k;
        I_Binary_read_big_endian_integer32( m_in, k);
        if (k<0 || k>4) {
            m_in.clear( std::ios::badbit);
            if ( verbose()) {
                std::cerr << " " << std::endl;
                std::cerr << "File_scanner_OFF::" << std::endl;
                std::cerr << "skip_to_next_facet(): input error: bad "
                             "number of color indices at vertex "
                          << current_facet << "." << std::endl;
            }
            set_off_header( false);
            return;
        }
        while (k--) {
            float dummy;
            I_Binary_read_big_endian_float32( m_in, dummy);
        }
    } else {
        m_in >> skip_until_EOL;
    }
}

CGAL_END_NAMESPACE
// EOF //
