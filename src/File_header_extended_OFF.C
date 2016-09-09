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
// file          : src/File_header_extended_OFF.C
// package       : Polyhedron_IO (1.11)
// chapter       : $CGAL_Chapter: Support Library ... $
// source        : polyhedron_io.fw
// revision      : $Revision: 1.8 $
// revision_date : $Date: 1998/10/08 22:46:22 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Extended file header information of an object file format (OFF) file
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_IO_FILE_HEADER_EXTENDED_OFF_H
#include <CGAL/IO/File_header_extended_OFF.h>
#endif // CGAL_IO_FILE_HEADER_EXTENDED_OFF_H

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
#ifndef CGAL_PROTECT_STRSTREAM_H
#include <strstream.h>
#define CGAL_PROTECT_STRSTREAM_H
#endif // CGAL_PROTECT_STRSTREAM_H
#ifndef CGAL_PROTECT_ALGO_H
#include <algo.h>
#define CGAL_PROTECT_ALGO_H
#endif // CGAL_PROTECT_ALGO_H


bool CGAL_File_header_extended_OFF::
is_POL()  const {
    return is_OFF() && polyhedral_surface();
}

bool CGAL_File_header_extended_OFF::
is_CBP()  const {
    return is_POL() && triangulated() && non_empty_facets() &&
        normalized_to_sphere() && radius() <= 1.0;
}

bool CGAL_File_header_extended_OFF::
is_TRN()  const {
    return is_CBP() && terrain();
}

int  CGAL_File_header_extended_OFF::
is_CBPn() const {
    if ( is_POL() && triangulated() && non_empty_facets() &&
         normalized_to_sphere() && rounded() &&
         (radius() <= ( 1l << rounded_bits())))
        return rounded_bits();
    else
        return 0;
}

int  CGAL_File_header_extended_OFF::
is_TRNn() const {
    return ( terrain() ? is_CBPn() : 0);
}


// The proper file suffix with respect to file format.
const char* CGAL_File_header_extended_OFF::
suffix() const {
    if ( is_TRNn()) {
        ostrstream out( (char*)m_suffix, 20);
        out << "trn" << m_rounded_bits << '\0';
        return m_suffix;
    }
    if ( is_TRN())
        return "trn";
    if ( is_CBPn()) {
        ostrstream out( (char*)m_suffix, 20);
        out << "cbp" << m_rounded_bits << '\0';
        return m_suffix;
    }
    if ( is_CBP())
        return "cbp";
    if ( is_POL())
        return "pol";
    return "off";
}

// The proper format name.
const char* CGAL_File_header_extended_OFF::
format_name() const {
    if ( is_TRNn()) {
        ostrstream out( (char*)m_format_name, 20);
        out << "TRN" << m_rounded_bits << '\0';
        return m_format_name;
    }
    if ( is_TRN())
        return "TRN";
    if ( is_CBPn()) {
        ostrstream out( (char*)m_format_name, 20);
        out << "CBP" << m_rounded_bits << '\0';
        return m_format_name;
    }
    if ( is_CBP())
        return "CBP";
    if ( is_POL())
        return "POL";
    return "OFF";
}

CGAL_File_header_extended_OFF& CGAL_File_header_extended_OFF::
operator+=( const CGAL_File_header_extended_OFF& header) {
    m_verbose              = m_verbose || header.m_verbose;
    m_polyhedral_surface   = m_polyhedral_surface &&
                             header.m_polyhedral_surface;
    m_halfedges           += header.m_halfedges;
    m_triangulated         = m_triangulated && header.m_triangulated;
    m_non_empty_facets     = m_non_empty_facets &&
                             header.m_non_empty_facets;
    m_terrain              = m_terrain && header.m_terrain;
    m_normalized_to_sphere = m_normalized_to_sphere &&
                             header.m_normalized_to_sphere;
    m_radius               = max(m_radius, header.m_radius);
    m_rounded              = m_rounded && header.m_rounded;
    m_rounded_bits         = max( m_rounded_bits, header.m_rounded_bits);
    m_off_header           = m_off_header && header.m_off_header;
    return *this;
}

#define OUT(item) out << "# " #item " " << h.item() << '\n'
#define OUTBOOL(item) out << "# " #item " " << (h.item() ? '1':'0') << '\n'

// Write extended header incl. CGAL/ENDCBP keywords.
ostream& operator<<( ostream& out, const CGAL_File_header_extended_OFF& h) {
    out << "#CBP\n";
    OUTBOOL( polyhedral_surface);
    OUT(     halfedges);
    OUTBOOL( triangulated);
    OUTBOOL( non_empty_facets);
    OUTBOOL( terrain);
    OUTBOOL( normalized_to_sphere);
    OUT(     radius);
    OUTBOOL( rounded);
    OUT(     rounded_bits);
    out << "# ENDCBP\n" << endl;
    return out;
}
#undef OUT
#undef OUTBOOL

#define IN(item,type)                         \
    else if ( strcmp( keyword, #item) == 0) { \
        type t;                               \
        in >> t;                              \
        h.set_##item( t);                     \
    }

#define INBOOL(item)                          \
    else if ( strcmp( keyword, #item) == 0) { \
        in >> c;                              \
        h.set_##item( c == '1');              \
    }

// Scan extended header. The CBP keyword must be read already.
istream& operator>>( istream& in, CGAL_File_header_extended_OFF& h) {
    const int max_keyword = 42;
    char c;
    char keyword[max_keyword] = "";
    in >> keyword;
    while ( in && strcmp( keyword, "ENDCBP") != 0) {
        if ( strcmp( keyword, "#") == 0)
            ;
        INBOOL( polyhedral_surface)
        IN(     halfedges, int)
        INBOOL( triangulated)
        INBOOL( non_empty_facets)
        INBOOL( terrain)
        INBOOL( normalized_to_sphere)
        IN(     radius, double)
        INBOOL( rounded)
        IN(     rounded_bits, int)
        else if ( h.verbose()) {
            cerr << "warning: CGAL_File_header_extended_OFF: unknown key '"
                 << keyword << "'." << endl;
        }
        in >> keyword;
    }
    in >> CGAL_skip_until_EOL >> CGAL_skip_comment_OFF;
    return in;
}
#undef IN
#undef INBOOL
// EOF //
