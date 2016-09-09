/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/


#ifndef CGAL_IO_H
#define CGAL_IO_H
#include <iostream.h>
#include <CGAL/IO/io_tags.h>
#include <CGAL/Object.h>

class CGAL_IO {
public:
    static int mode;

    enum Mode {ASCII = 0, PRETTY, BINARY};
};

CGAL_IO::Mode
CGAL_set_ascii_mode(ios& i);

CGAL_IO::Mode
CGAL_set_binary_mode(ios& i);

CGAL_IO::Mode
CGAL_set_pretty_mode(ios& i);

CGAL_IO::Mode
CGAL_set_mode(ios& i, CGAL_IO::Mode m);

CGAL_IO::Mode
CGAL_get_mode(ios& i);

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


#endif // CGAL_IO_H
