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
// file          : include/CGAL/IO/io.h
// package       : iostream (2.1)
// source        : $RCSfile: io.h,v $
// revision      : $Revision: 1.3 $
// revision_date : $Date: 1999/05/27 13:54:49 $
// author(s)     : Andreas Fabri
//
// coordinator   : Herve Bronnimann
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_IO_H
#define CGAL_IO_H

#include <iostream.h>
#include <CGAL/IO/io_tags.h>
#include <CGAL/IO/Color.h>
#include <CGAL/Object.h>

CGAL_BEGIN_NAMESPACE

class IO {
public:
    static int mode;
    enum Mode {ASCII = 0, PRETTY, BINARY};
};

IO::Mode
get_mode(std::ios& i);

IO::Mode
set_ascii_mode(std::ios& i);

IO::Mode
set_binary_mode(std::ios& i);

IO::Mode
set_pretty_mode(std::ios& i);

IO::Mode
set_mode(std::ios& i, IO::Mode m);
bool
is_pretty(std::ios& i);

bool
is_ascii(std::ios& i);

bool
is_binary(std::ios& i);

inline io_Read_write io_tag(char){ return io_Read_write(); }


template < class T >
inline
void
write(ostream& os, const T& t, const io_Read_write&)
{
    os.write((char*)&t, sizeof(t));
}


template < class T >
inline
void
write(ostream& os, const T& t, const io_Operator&)
{
    os << t;
}


template < class T >
inline
void
write(ostream& os, const T& t, const io_Extract_insert&)
{
    insert(os, t);
}


template < class T >
inline
void
write(ostream& os, const T& t)
{
    write(os, t, io_tag(t));
}


template < class T >
inline
void
read(istream& is, T& t, const io_Read_write&)
{
    is.read((char*)&t, sizeof(t));
}


template < class T >
inline
void
read(istream& is, T& t, const io_Operator&)
{
    is >> t;
}


template < class T >
inline
void
read(istream& is, T& t, const io_Extract_insert&)
{
    extract(is, t);
}


template < class T >
inline
void
read(istream& is, T& t)
{
    read(is, t, io_tag(t));
}


inline
ostream& operator<<( ostream& out, const Color& col)
{
    switch(out.iword(IO::mode)) {
    case IO::ASCII :
        return out << col.red() << ' ' << col.green() << ' ' << col.blue();
    case IO::BINARY :
        write(out, col.red());
        write(out, col.green());
        write(out, col.blue());
        return out;
    default:
        return out << "Color(" << col.red() << ", " << col.green() << ", "
                   << col.blue() << ')';
    }
}

inline
istream &operator>>(istream &is, Color& col)
{
    int r, g, b;
    switch(is.iword(IO::mode)) {
    case IO::ASCII :
        is >> r >> g >> b;
        break;
    case IO::BINARY :
        read(is, r);
        read(is, g);
        read(is, b);
        break;
    default:
        cerr << "" << endl;
        cerr << "Stream must be in ascii or binary mode" << endl;
        break;
    }
    col = Color(r,g,b);
    return is;
}

CGAL_END_NAMESPACE

#endif // CGAL_IO_H
