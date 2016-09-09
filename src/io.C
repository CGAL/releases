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
// file          : src/io.C
// package       : iostream (2.1)
// source        : $RCSfile: io.C,v $
// revision      : $Revision: 1.2 $
// revision_date : $Date: 1999/05/27 14:19:24 $
// author(s)     : Andreas Fabri
//
// coordinator   : Mariette.Yvinec
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_IO_C
#define CGAL_IO_C

#include <CGAL/basic.h>
#include <CGAL/IO/io.h>

CGAL_BEGIN_NAMESPACE

int IO::mode = std::ios::xalloc();


IO::Mode
get_mode(std::ios& i)
{
    return CGAL_static_cast(IO::Mode,i.iword(IO::mode));
}

IO::Mode
set_ascii_mode(std::ios& i)
{
    IO::Mode m = get_mode(i);
    i.iword(IO::mode) = IO::ASCII;
    return m;
}


IO::Mode
set_binary_mode(std::ios& i)
{
    IO::Mode m = get_mode(i);
    i.iword(IO::mode) = IO::BINARY;
    return m;
}


IO::Mode
set_pretty_mode(std::ios& i)
{
    IO::Mode m = get_mode(i);
    i.iword(IO::mode) = IO::PRETTY;
    return m;
}


IO::Mode
set_mode(std::ios& i, IO::Mode m)
{
    IO::Mode old = get_mode(i);
    i.iword(IO::mode) = m;
    return old;
}

bool
is_pretty(std::ios& i)
{
    return i.iword(IO::mode) == IO::PRETTY;
}

bool
is_ascii(std::ios& i)
{
    return i.iword(IO::mode) == IO::ASCII;
}


bool
is_binary(std::ios& i)
{
    return i.iword(IO::mode) == IO::BINARY;
}

CGAL_END_NAMESPACE

#endif // CGAL_IO_C
