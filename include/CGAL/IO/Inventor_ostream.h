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
// file          : include/CGAL/IO/Inventor_ostream.h
// author(s)     : Andreas Fabri
//                 Lutz Kettner
//
// email         : cgal@cs.uu.nl
//
// ============================================================================

#ifndef CGAL_IO_INVENTOR_OSTREAM_H
#define CGAL_IO_INVENTOR_OSTREAM_H

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif // CGAL_BASIC_H
#ifndef CGAL_PROTECT_IOSTREAM_H
#include <iostream.h>
#define CGAL_PROTECT_IOSTREAM_H
#endif // CGAL_PROTECT_IOSTREAM_H

// OpenInventor and VRML 1.0 are quite similar formats, so 
// output operators could be shared if they use the following
// base class, which is common for both output streams.

class CGAL_Inventor_ostream_base {
public:
    CGAL_Inventor_ostream_base()           : m_os(0)  {}
    CGAL_Inventor_ostream_base(ostream& o) : m_os(&o) {}
    ~CGAL_Inventor_ostream_base()  { close(); }
    void open(ostream& o)        { m_os = &o; }    
    void close() {
	if ( m_os)
	    os() << endl;
	m_os = 0;
    }    
    typedef const void* Const_void_ptr;
    operator Const_void_ptr () const {
	if ( m_os)
	    return *m_os;
	return 0;
    }
    ostream& os() {
	// The behaviour if m_os == 0 could be changed to return
	// cerr or a file handle to /dev/null. The latter one would 
	// mimick the behaviour that one can still use a stream with
	// an invalid stream, but without producing any output.
	CGAL_assertion( m_os);
	return *m_os;
    }
private:
    ostream*  m_os;
};


class CGAL_Inventor_ostream : public  CGAL_Inventor_ostream_base {
public:
    CGAL_Inventor_ostream() {}
    CGAL_Inventor_ostream(ostream& o) : CGAL_Inventor_ostream_base(o) {
	header();
    }
    void open(ostream& o) {
	CGAL_Inventor_ostream_base::open(o); 
	header();
    }
private:
    void header() { 
	os() << "#Inventor V2.0 ascii" << endl;
	os() << "# File written with the help of the CGAL Library" << endl; 
    }
};

#endif // CGAL_IO_INVENTOR_OSTREAM_H
