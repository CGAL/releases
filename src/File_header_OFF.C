// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : src/File_header_OFF.C
// author(s)     : Lutz Kettner  
//
// email         : cgal@cs.uu.nl
//
// ============================================================================

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif // CGAL_BASIC_H
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
    _verbose     = false;
    _skel        = false;
    n_halfedges = 0;
    _offset      = 1;
    _colors      = false;
    _normals     = false;
    _tag4        = false;
    _tagDim      = false;
    _dim         = 3;
    _binary      = false;

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
                        if ( strcmp( keyword, "halfedges") == 0)
                            in >> n_halfedges;
                        if ( strcmp( keyword, "linear") == 0) {
#ifdef CGAL_IO_FILE_INFO_H
                            double m11, m12, m13;
                            double m21, m22, m23;
                            double m31, m32, m33;
                            in >> m11 >> m12 >> m13;
                            in >> m21 >> m22 >> m23;
                            in >> m31 >> m32 >> m33;
                            _file_info.linear = CGAL_File_info::Matrix(
                              m11, m12, m13, m21, m22, m23, m31, m32, m33);
#else // CGAL_IO_FILE_INFO_H //
                            // This is code from the CEBAP project
                            // now useless in CGAL.
                            in >> _file_info.linear;
#endif
                        }
                        if ( strcmp( keyword, "normalized_to_sphere") ==0){
                            in >> c;
                            _file_info.normalized_to_sphere = (c == '1');
                        }
                        if ( strcmp( keyword, "radius") == 0)
                            in >> _file_info.radius;
                        if ( strcmp( keyword, "rounded") == 0) {
                            in >> c;
                            _file_info.rounded = (c == '1');
                        }
                        if ( strcmp( keyword, "rounded_bits") == 0)
                            in >> _file_info.rounded_bits;
                        if ( strcmp( keyword, "terrain") == 0) {
                            in >> c;
                            _file_info.terrain = (c == '1');
                        }
                        if ( strcmp( keyword, "terrain_vector") == 0) {
#ifdef CGAL_IO_FILE_INFO_H
                            double x, y, z;
                            in >> x >> y >> z;
                            _file_info.terrain_vector =
                                CGAL_File_info::Vector( x, y, z);
#else // CGAL_IO_FILE_INFO_H //
                            // This is code from the CEBAP project
                            in >> _file_info.terrain_vector;
#endif // CGAL_IO_FILE_INFO_H //
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
                _offset = 0;
                int j = 0;
                if ( j<i && keyword[j] == 'C') {
                    _colors = true;
                    j++;
                }
                if ( j<i && keyword[j] == 'N') {
                    _normals = true;
                    j++;
                }
                if ( j<i && keyword[j] == '4') {
                    _tag4 = true;
                    j++;
                }
                if ( j<i && keyword[j] == 'n') {
                    _tagDim = true;
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
                        if ( _verbose) {
                            cerr << " " << endl;
                            cerr << "CGAL_File_scanner_OFF<Traits,HDS>::";
                            cerr << "\nCBP_File_scanner_OFF(): "
                                "Wrong format: neither OFF nor SKEL."
                                 << endl;
                        }
                        return;
                    } else {
                        _skel = true;
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
                        _binary = true;
                        while (  c != '\n')
                            in.get(c);
                    }
                    else {
                        in.clear( ios::badbit);
                        if ( _verbose) {
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
    if ( _binary) {
        CGAL_Integer32 a, b, c;
        CGAL__Binary_read_integer32( in, a);
        if ( _tagDim) {
            _dim = a;
            CGAL__Binary_read_integer32( in, a);
        }
        CGAL__Binary_read_integer32( in, b);
        if ( ! _skel)
            CGAL__Binary_read_integer32( in, c);
        else
            c = 0;
        n_vertices = a;
        n_facets   = b;
        n_h        = c;
    } else {
        if ( _tagDim) {
            _dim = n_vertices;
            in >> n_vertices;
        }
        in >> n_facets;
        if ( ! _skel)
            in >> n_h;
        else
            n_h = 0;
    }
    if ( n_h == 0)
        _offset = 0;
    if ( ! in || n_vertices <= 0 || n_facets < 0) {
        in.clear( ios::badbit);
        if ( _verbose) {
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
