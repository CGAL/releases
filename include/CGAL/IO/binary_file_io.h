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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/IO/binary_file_io.h
// package       : Polyhedron_IO (3.9)
// chapter       : $CGAL_Chapter: Support Library ... $
// source        : polyhedron_io.fw
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2001/06/19 07:23:18 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Binary read and write on streams for Integer32 and float
// email         : contact@cgal.org
// www           : http://www.cgal.org
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

inline void
I_Binary_write_integer32(std::ostream& out, Integer32 i) {
    out.write( (char*)(&i), 4);
}
inline void
I_Binary_write_float32(std::ostream& out, float f) {
    out.write( (char*)(&f), 4);
}

inline void
I_Binary_read_integer32(std::istream& in, Integer32& i) {
    in.read( (char*)(&i), 4);
}
inline void
I_Binary_read_float32(std::istream& in, float& f) {
    in.read( (char*)(&f), 4);
}

inline void
I_swap_to_big_endian( UInteger32& u) {
    (void)u;
#ifdef CGAL_LITTLE_ENDIAN
u = ((u >> 24) | (u << 24) | ((u >> 8) & 0xff00) | ((u << 8) & 0xff0000));
#endif
}

inline void
I_swap_to_big_endian( Integer32& i) {
    UInteger32& u = (UInteger32&)i;
    I_swap_to_big_endian( u);
}

inline void
I_swap_to_big_endian( float& f) {
    UInteger32& u = (UInteger32&)f;
    I_swap_to_big_endian( u);
}

inline void
I_Binary_write_big_endian_integer32(std::ostream& out, Integer32 i) {
    I_swap_to_big_endian( i);
    out.write( (char*)(&i), 4);
}
inline void
I_Binary_write_big_endian_float32(std::ostream& out, float f) {
    I_swap_to_big_endian( f);
    out.write( (char*)(&f), 4);
}

inline void
I_Binary_read_big_endian_integer32(std::istream& in, Integer32& i) {
    in.read( (char*)(&i), 4);
    I_swap_to_big_endian( i);
}
inline void
I_Binary_read_big_endian_float32(std::istream& in, float& f) {
    in.read( (char*)(&f), 4);
    I_swap_to_big_endian( f);
}

CGAL_END_NAMESPACE
#endif // CGAL_IO_BINARY_FILE_IO_H //
// EOF //
