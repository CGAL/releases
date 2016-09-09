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
// file          : src/File_header_OFF.C
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
//
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif // CGAL_BASIC_H
#ifndef CGAL_KNOWN_BIT_SIZE_INTEGERS_H
#include <CGAL/known_bit_size_integers.h>
#endif
#ifndef CGAL_PROTECT_STDLIB_H
#include <stdlib.h>
#define CGAL_PROTECT_STDLIB_H
#endif // CGAL_PROTECT_STDLIB_H
#ifndef CGAL_PROTECT_CTYPE_H
#include <ctype.h>
#define CGAL_PROTECT_CTYPE_H
#endif // CGAL_PROTECT_CTYPE_H
#ifndef CGAL_PROTECT_STRING_H
#include <string.h>
#define CGAL_PROTECT_STRING_H
#endif // CGAL_PROTECT_STRING_H
#ifndef CGAL_PROTECT_IOSTREAM_H
#include <iostream.h>
#define CGAL_PROTECT_IOSTREAM_H
#endif // CGAL_PROTECT_IOSTREAM_H
#ifndef CGAL_IO_BINARY_FILE_IO_H
#include <CGAL/IO/binary_file_io.h>
#endif // CGAL_IO_BINARY_FILE_IO_H
#ifndef CGAL_IO_FILE_HEADER_OFF_H
#include <CGAL/IO/File_header_OFF.h>
#endif // CGAL_IO_FILE_HEADER_OFF_H

CGAL_File_header_OFF::CGAL_File_header_OFF( istream& in, bool verbose) {
    m_verbose     = false;
    m_skel        = false;
    n_halfedges   = 0;
    m_offset      = 1;
    m_colors      = false;
    m_normals     = false;
    m_tag4        = false;
    m_tagDim      = false;
    m_dim         = 3;
    m_binary      = false;

    // read in the first character and scan for comments, `OFF', or `NOFF',
    // or `SKEL', or `4SKEL'.
    char c;
    char keyword[42] = "";
    bool again = false;
    do {
        again = false;
        in >> c;
        if ( c == '#') {
            if ( in.get(c) && c == 'C' &&
                 in.get(c) && c == 'B' &&
                 in.get(c) && c == 'P') {
                in >> keyword;
                while ( strcmp( keyword, "ENDCBP") != 0) {
                    if ( strcmp( keyword, "#") != 0) {
                        if ( strcmp( keyword, "polyhedral_surface") ==0){
                            in >> c;
                            m_file_info.polyhedral_surface = (c == '1');
                        }
                        if ( strcmp( keyword, "halfedges") == 0) {
                            in >> n_halfedges;
                            m_file_info.halfedges = n_halfedges;
                        }
                        if ( strcmp( keyword, "triangulated") ==0){
                            in >> c;
                            m_file_info.triangulated = (c == '1');
                        }
                        if ( strcmp( keyword, "non_empty_facets") ==0){
                            in >> c;
                            m_file_info.non_empty_facets = (c == '1');
                        }
                        if ( strcmp( keyword, "normalized_to_sphere") ==0){
                            in >> c;
                            m_file_info.normalized_to_sphere = (c == '1');
                        }
                        if ( strcmp( keyword, "radius") == 0)
                            in >> m_file_info.radius;
                        if ( strcmp( keyword, "rounded") == 0) {
                            in >> c;
                            m_file_info.rounded = (c == '1');
                        }
                        if ( strcmp( keyword, "rounded_bits") == 0)
                            in >> m_file_info.rounded_bits;
                        if ( strcmp( keyword, "terrain") == 0) {
                            in >> c;
                            m_file_info.terrain = (c == '1');
                        }
                    }
                    in >> keyword;
                }
                c = ' ';
            }
            if ( c != '\n')
                while ( in.get(c) && c != '\n')
                    ;
            again = true;
        } else {
            int i = 0;
            keyword[i++] = c;
            while( i < 20 && in.get(c) && isalnum(c))
                keyword[i++] = c;
            keyword[i] = '\0';
            if ( i<2 || ( isdigit(keyword[0]) && keyword[0] != '4')
                     || isdigit(keyword[1]))
                n_vertices = atoi( keyword);
            else {
                m_offset = 0;
                int j = 0;
                if ( j<i && keyword[j] == 'C') {
                    m_colors = true;
                    j++;
                }
                if ( j<i && keyword[j] == 'N') {
                    m_normals = true;
                    j++;
                }
                if ( j<i && keyword[j] == '4') {
                    m_tag4 = true;
                    j++;
                }
                if ( j<i && keyword[j] == 'n') {
                    m_tagDim = true;
                    j++;
                }
                if ( i-j != 3 || keyword[j]   != 'O'
                              || keyword[j+1] != 'F'
                              || keyword[j+2] != 'F') {
                    if ( i-j != 4 || keyword[j]   != 'S'
                                  || keyword[j+1] != 'K'
                                  || keyword[j+2] != 'E'
                                  || keyword[j+3] != 'L') {
                        in.clear( ios::badbit);
                        if ( m_verbose) {
                            cerr << " " << endl;
                            cerr << "CGAL_File_scanner_OFF<Traits,HDS>::";
                            cerr << "\nCBP_File_scanner_OFF(): "
                                "Wrong format: neither OFF nor SKEL."
                                 << endl;
                        }
                        return;
                    } else {
                        m_skel = true;
                    }
                }
                while( (in >> c) && c == '#')
                    while ( in.get(c) && c != '\n')
                        ;
                if ( isdigit(c)) {
                    in.putback(c);
                    in >> n_vertices;
                } else {
                    i = 0;
                    keyword[i++] = c;
                    while( i < 20 && in.get(c) && isalnum(c))
                        keyword[i++] = c;
                    keyword[i] = '\0';
                    if ( strcmp( keyword, "BINARY") == 0) {
                        m_binary = true;
                        while (  c != '\n')
                            in.get(c);
                    }
                    else {
                        in.clear( ios::badbit);
                        if ( m_verbose) {
                            cerr << " " << endl;
                            cerr << "CGAL_File_scanner_OFF<Traits,HDS>::";
                            cerr << "\nCBP_File_scanner_OFF(): "
                                "Wrong format: neither OFF nor SKEL."
                                 << endl;
                        }
                        return;
                    }
                }
            }
        }
    } while ( again);

    // Read remaining size value.
    int n_h;
    if ( m_binary) {
        CGAL_Integer32 a, b, c;
        CGAL__Binary_read_integer32( in, a);
        if ( m_tagDim) {
            m_dim = a;
            CGAL__Binary_read_integer32( in, a);
        }
        CGAL__Binary_read_integer32( in, b);
        if ( ! m_skel)
            CGAL__Binary_read_integer32( in, c);
        else
            c = 0;
        n_vertices = a;
        n_facets   = b;
        n_h        = c;
    } else {
        if ( m_tagDim) {
            m_dim = n_vertices;
            in >> n_vertices;
        }
        in >> n_facets;
        if ( ! m_skel)
            in >> n_h;
        else
            n_h = 0;
    }
    if ( n_h == 0)
        m_offset = 0;
    if ( ! in || n_vertices <= 0 || n_facets < 0) {
        in.clear( ios::badbit);
        if ( m_verbose) {
            cerr << " " << endl;
            cerr << "CGAL_File_scanner_OFF<Traits,HDS>::\n";
            cerr << "CGAL_File_scanner_OFF(): "
                "File contains <= 0 vertices or < 0 facets." << endl;
        }
        return;
    }
    if ( n_halfedges == 0) {
        // be careful, because border edges count twice
        n_halfedges = 2 * n_h;
        // check against the Eulerian equation for connected planar graps.
        // We do not know the number of facets that are holes and we do not
        // know the genus of the surface. So we add 12 and a factor
        // of 5 percent.
        if (    n_halfedges == 0
             || n_halfedges > (n_vertices + n_facets - 2 + 12) * 2.1
             || n_halfedges < (n_vertices + n_facets - 2) * 2
        )
            n_halfedges = int((n_vertices + n_facets - 2 + 12) * 2.1);
    }
}
// EOF //
