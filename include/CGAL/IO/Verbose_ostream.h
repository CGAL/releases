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

/*
  Authors  : Lutz Kettner
  Version  : $Revision: 1.1 $  $Date: 1997/05/04 15:47:43 $
*/

#ifndef CGAL_VERBOSE_OSTREAM_H
#define CGAL_VERBOSE_OSTREAM_H 1

#include <iostream.h>

#define CGAL__VERB(x) if (b) o << x; return *this

class CGAL_Verbose_ostream {
    bool     b;
    ostream& o;
public:
    CGAL_Verbose_ostream( bool active = false, ostream& out = cerr) 
        : b(active), o(out){}
    CGAL_Verbose_ostream( const CGAL_Verbose_ostream& v) : b(v.b), o(v.o) {}
    CGAL_Verbose_ostream&  operator<<( char c)               { CGAL__VERB(c);}
    CGAL_Verbose_ostream&  operator<<( const char* s)        { CGAL__VERB(s);}
    CGAL_Verbose_ostream&  operator<<( int a)                { CGAL__VERB(a);}
    CGAL_Verbose_ostream&  operator<<( long l)               { CGAL__VERB(l);}
    CGAL_Verbose_ostream&  operator<<( double d)             { CGAL__VERB(d);}
    CGAL_Verbose_ostream&  operator<<( float f)              { CGAL__VERB(f);}
    CGAL_Verbose_ostream&  operator<<( unsigned int a)       { CGAL__VERB(a);}
    CGAL_Verbose_ostream&  operator<<( unsigned long l)      { CGAL__VERB(l);}
#ifdef _LONGLONG
    CGAL_Verbose_ostream&  operator<<( long long ll)         { CGAL__VERB(ll);}
    CGAL_Verbose_ostream&  operator<<( unsigned long long ll){ CGAL__VERB(ll);}
#endif /* _LONGLONG */
    CGAL_Verbose_ostream&  operator<<( void* p)              { CGAL__VERB(p);}
    CGAL_Verbose_ostream&  operator<<( short i)              { CGAL__VERB(i);}
    CGAL_Verbose_ostream&  operator<<( unsigned short i)     { CGAL__VERB(i);}
    CGAL_Verbose_ostream&  operator<<( ostream& (*f)(ostream&)){CGAL__VERB(f);}
    CGAL_Verbose_ostream&  operator<<( ios& (*f)(ios&) )     { CGAL__VERB(f);}
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

#endif // ! (CGAL_VERBOSE_OSTREAM_H)

/* EOF */
