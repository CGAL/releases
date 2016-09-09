// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/IO/binary_file_io.h
// package       : Polyhedron_IO (2.5)
// chapter       : $CGAL_Chapter: Support Library ... $
// source        : polyhedron_io.fw
// revision      : $Revision: 1.4 $
// revision_date : $Date: 1999/03/24 11:16:26 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Binary read and write on streams for Integer32 and float
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_IO_BINARY_FILE_IO_H
#define CGAL_IO_BINARY_FILE_IO_H 1
#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif
#ifndef CGAL_KNOWN_BIT_SIZE_INTEGERS_H
#include <CGAL/known_bit_size_integers.h>
#endif
#ifndef CGAL_PROTECT_IOSTREAM
#include <iostream>
#define CGAL_PROTECT_IOSTREAM
#endif

CGAL_BEGIN_NAMESPACE

void inline
_Binary_write_integer32(ostream& out, Integer32 i) {
    out.write( (char*)(&i), 4);
}
void inline
_Binary_write_float32(std::ostream& out, float f) {
    out.write( (char*)(&f), 4);
}

void inline
_Binary_read_integer32(std::istream& in, Integer32& i) {
    in.read( (char*)(&i), 4);
}
void inline
_Binary_read_float32(std::istream& in, float& f) {
    in.read( (char*)(&f), 4);
}

void inline
_swap_to_big_endian( UInteger32& u) {
    (void)u;
#ifdef CGAL_LITTLE_ENDIAN
u = ((u >> 24) | (u << 24) | ((u >> 8) & 0xff00) | ((u << 8) & 0xff0000));
#endif
}

void inline
_swap_to_big_endian( Integer32& i) {
    UInteger32& u = (UInteger32&)i;
    _swap_to_big_endian( u);
}

void inline
_swap_to_big_endian( float& f) {
    UInteger32& u = (UInteger32&)f;
    _swap_to_big_endian( u);
}

void inline
_Binary_write_big_endian_integer32(std::ostream& out, Integer32 i) {
    _swap_to_big_endian( i);
    out.write( (char*)(&i), 4);
}
void inline
_Binary_write_big_endian_float32(std::ostream& out, float f) {
    _swap_to_big_endian( f);
    out.write( (char*)(&f), 4);
}

void inline
_Binary_read_big_endian_integer32(std::istream& in, Integer32& i) {
    in.read( (char*)(&i), 4);
    _swap_to_big_endian( i);
}
void inline
_Binary_read_big_endian_float32(std::istream& in, float& f) {
    in.read( (char*)(&f), 4);
    _swap_to_big_endian( f);
}

CGAL_END_NAMESPACE
#endif // CGAL_IO_BINARY_FILE_IO_H //
// EOF //
