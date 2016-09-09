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
// file          : include/CGAL/IO/binary_file_io.h
// author(s)     : Lutz Kettner  
//
// email         : cgal@cs.uu.nl
//
// ============================================================================

#ifndef CGAL_IO_BINARY_FILE_IO_H
#define CGAL_IO_BINARY_FILE_IO_H 1
#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif

#ifndef CGAL_PROTECT_IOSTREAM_H
#include <iostream.h>
#define CGAL_PROTECT_IOSTREAM_H
#endif // CGAL_PROTECT_IOSTREAM_H

void inline
CGAL__Binary_write_integer32(ostream& out, CGAL_Integer32 i) {
    out.write( (char*)(&i), 4);
}
void inline
CGAL__Binary_write_float32(ostream& out, float f) {
    out.write( (char*)(&f), 4);
}

void inline
CGAL__Binary_read_integer32(istream& in, CGAL_Integer32& i) {
    in.read( (char*)(&i), 4);
}
void inline
CGAL__Binary_read_float32(istream& in, float& f) {
    in.read( (char*)(&f), 4);
}

void inline
CGAL__swap_to_big_endian( CGAL_UInteger32& u) {
#ifdef CGAL_LITTLE_ENDIAN
u = ((u >> 24) | (u << 24) | ((u >> 8) & 0xff00) | ((u << 8) & 0xff0000));
#endif
}

void inline
CGAL__swap_to_big_endian( CGAL_Integer32& i) {
    CGAL_UInteger32& u = (CGAL_UInteger32&)i;
    CGAL__swap_to_big_endian( u);
}

void inline
CGAL__swap_to_big_endian( float& f) {
    CGAL_UInteger32& u = (CGAL_UInteger32&)f;
    CGAL__swap_to_big_endian( u);
}

void inline
CGAL__Binary_write_big_endian_integer32(ostream& out, CGAL_Integer32 i) {
    CGAL__swap_to_big_endian( i);
    out.write( (char*)(&i), 4);
}
void inline
CGAL__Binary_write_big_endian_float32(ostream& out, float f) {
    CGAL__swap_to_big_endian( f);
    out.write( (char*)(&f), 4);
}

void inline
CGAL__Binary_read_big_endian_integer32(istream& in, CGAL_Integer32& i) {
    in.read( (char*)(&i), 4);
    CGAL__swap_to_big_endian( i);
}
void inline
CGAL__Binary_read_big_endian_float32(istream& in, float& f) {
    in.read( (char*)(&f), 4);
    CGAL__swap_to_big_endian( f);
}
#endif // CGAL_IO_BINARY_FILE_IO_H //
// EOF //
