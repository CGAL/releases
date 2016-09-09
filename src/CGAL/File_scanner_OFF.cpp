// Copyright (c) 1997  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Stream_support/src/CGAL/File_scanner_OFF.cpp $
// $Id: File_scanner_OFF.cpp 56979 2010-06-22 13:15:46Z afabri $
// 
//
// Author(s)     : Lutz Kettner  <kettner@mpi-sb.mpg.de>

#include <CGAL/basic.h>
#include <cstdlib>
#include <iostream>
#include <CGAL/IO/binary_file_io.h>
#include <CGAL/IO/File_scanner_OFF.h>

namespace CGAL {

void
File_scanner_OFF::
skip_to_next_vertex( std::size_t current_vertex) {
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
skip_to_next_facet( std::size_t current_facet) {
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

} //namespace CGAL
// EOF //
