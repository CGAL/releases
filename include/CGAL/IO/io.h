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
// file          : include/CGAL/IO/io.h
// package       : iostream (1.8)
// source        : web/io.fw
// revision      : $Revision: 1.10 $
// revision_date : $Date: 1998/07/22 12:49:21 $
// author(s)     : Andreas Fabri
//
// coordinator   : Herve Bronnimann
//
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

class CGAL_IO {
public:
    static int mode;
    enum Mode {ASCII = 0, PRETTY, BINARY};
};

CGAL_IO::Mode
CGAL_get_mode(ios& i);

CGAL_IO::Mode
CGAL_set_ascii_mode(ios& i);

CGAL_IO::Mode
CGAL_set_binary_mode(ios& i);

CGAL_IO::Mode
CGAL_set_pretty_mode(ios& i);

CGAL_IO::Mode
CGAL_set_mode(ios& i, CGAL_IO::Mode m);
bool
CGAL_is_pretty(ios& i);

bool
CGAL_is_ascii(ios& i);

bool
CGAL_is_binary(ios& i);

inline CGAL_io_Read_write CGAL_io_tag(char){ return CGAL_io_Read_write(); }


template < class T >
inline
void
CGAL_write(ostream& os, const T& t, const CGAL_io_Read_write&)
{
    os.write((char*)&t, sizeof(t));
}


template < class T >
inline
void
CGAL_write(ostream& os, const T& t, const CGAL_io_Operator&)
{
    os << t;
}


template < class T >
inline
void
CGAL_write(ostream& os, const T& t, const CGAL_io_Extract_insert&)
{
    CGAL_insert(os, t);
}


template < class T >
inline
void
CGAL_write(ostream& os, const T& t)
{
    CGAL_write(os, t, CGAL_io_tag(t));
}


template < class T >
inline
void
CGAL_read(istream& is, T& t, const CGAL_io_Read_write&)
{
    is.read((char*)&t, sizeof(t));
}


template < class T >
inline
void
CGAL_read(istream& is, T& t, const CGAL_io_Operator&)
{
    is >> t;
}


template < class T >
inline
void
CGAL_read(istream& is, T& t, const CGAL_io_Extract_insert&)
{
    CGAL_extract(is, t);
}


template < class T >
inline
void
CGAL_read(istream& is, T& t)
{
    CGAL_read(is, t, CGAL_io_tag(t));
}


inline
ostream& operator<<( ostream& out, const CGAL_Color& col)
{
    switch(out.iword(CGAL_IO::mode)) {
    case CGAL_IO::ASCII :
        return out << col.red() << ' ' << col.green() << ' ' << col.blue();
    case CGAL_IO::BINARY :
        CGAL_write(out, col.red());
        CGAL_write(out, col.green());
        CGAL_write(out, col.blue());
        return out;
    default:
        return out << "Color(" << col.red() << ", " << col.green() << ", "
                   << col.blue() << ')';
    }
}

inline
istream &operator>>(istream &is, CGAL_Color& col)
{
    int r, g, b;
    switch(is.iword(CGAL_IO::mode)) {
    case CGAL_IO::ASCII :
        is >> r >> g >> b;
        break;
    case CGAL_IO::BINARY :
        CGAL_read(is, r);
        CGAL_read(is, g);
        CGAL_read(is, b);
        break;
    default:
        cerr << "" << endl;
        cerr << "Stream must be in ascii or binary mode" << endl;
        break;
    }
    col = CGAL_Color(r,g,b);
    return is;
}


#endif // CGAL_IO_H
