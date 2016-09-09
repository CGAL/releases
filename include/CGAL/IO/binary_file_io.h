// Copyright (c) 1997  ETH Zurich (Switzerland).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source: /CVSROOT/CGAL/Packages/Polyhedron_IO/include/CGAL/IO/binary_file_io.h,v $
// $Revision: 1.6 $ $Date: 2003/09/18 10:25:05 $
// $Name: current_submission $
//
// Author(s)     : Lutz Kettner  <kettner@mpi-sb.mpg.de>

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
