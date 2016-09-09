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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.1
// release_date  : 1998, July 24
//
// file          : include/CGAL/IO/Verbose_ostream.h
// package       : Support_LK (1.17)
// chapter       : $CGAL_Chapter: Support Library Manual ... $
// source        : support.fw
// revision      : $Revision: 1.10 $
// revision_date : $Date: 1998/07/23 15:15:34 $
// author(s)     : Lutz Kettner
//
// coordinator   : INRIA, Sophia Antipolis
//
// A stream like output class for verbose output.
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_IO_VERBOSE_OSTREAM_H
#define CGAL_IO_VERBOSE_OSTREAM_H 1
#ifndef CGAL_PROTECT_IOSTREAM_H
#include <iostream.h>
#define CGAL_PROTECT_IOSTREAM_H
#endif // CGAL_PROTECT_IOSTREAM_H

#define CGAL__VERB(x) if (b) o << x; return *this

class CGAL_Verbose_ostream {
    bool     b;
    ostream& o;
public:
    CGAL_Verbose_ostream( bool active = false, ostream& out = cerr)
        : b(active), o(out){}
    CGAL_Verbose_ostream( const CGAL_Verbose_ostream& v) : b(v.b), o(v.o) {}

    CGAL_Verbose_ostream&  operator<<( char c)                { CGAL__VERB(c);}
    CGAL_Verbose_ostream&  operator<<( const char* s)         { CGAL__VERB(s);}
    CGAL_Verbose_ostream&  operator<<( int a)                 { CGAL__VERB(a);}
    CGAL_Verbose_ostream&  operator<<( long l)                { CGAL__VERB(l);}
    CGAL_Verbose_ostream&  operator<<( double d)              { CGAL__VERB(d);}
    CGAL_Verbose_ostream&  operator<<( float f)               { CGAL__VERB(f);}
    CGAL_Verbose_ostream&  operator<<( unsigned int a)        { CGAL__VERB(a);}
    CGAL_Verbose_ostream&  operator<<( unsigned long l)       { CGAL__VERB(l);}
#ifdef _LONGLONG
    CGAL_Verbose_ostream&  operator<<( long long l)           { CGAL__VERB(l);}
    CGAL_Verbose_ostream&  operator<<( unsigned long long l)  { CGAL__VERB(l);}
#endif /* _LONGLONG */
    CGAL_Verbose_ostream&  operator<<( void* p)               { CGAL__VERB(p);}
    CGAL_Verbose_ostream&  operator<<( short i)               { CGAL__VERB(i);}
    CGAL_Verbose_ostream&  operator<<( unsigned short i)      { CGAL__VERB(i);}
    CGAL_Verbose_ostream&  operator<<( ostream& (*f)(ostream&))
                                                              { CGAL__VERB(f);}
    CGAL_Verbose_ostream&  operator<<( ios& (*f)(ios&) )      { CGAL__VERB(f);}
    CGAL_Verbose_ostream&  flush() {
        if (b)
            o.flush();
        return *this;
    }
    CGAL_Verbose_ostream&  put(char c) {
        if (b)
            o.put(c);
        return *this;
    }
    CGAL_Verbose_ostream&  write(const char*  s,int n) {
        if (b)
            o.write( s, n);
        return *this;
    }
};

#undef CGAL__VERB
#endif // CGAL_IO_VERBOSE_OSTREAM_H //
// EOF //
