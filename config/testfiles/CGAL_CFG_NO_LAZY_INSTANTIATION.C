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
// file          : config/testfiles/CGAL_CFG_NO_LAZY_INSTANTIATION.C
// package       : Configuration (1.21)
// source        :
// revision      : 1.11
// revision_date : 29 Mar 1998
// author(s)     : various
//
// coordinator   : Utrecht University
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

// CGAL_CFG_NO_LAZY_INSTANTIATION.C
// ---------------------------------------------------------------------
// A short test program to evaluate a C++ compiler.
// This program is used by cgal_configure.
// The following documentation will be pasted in the generated configfile.
// ---------------------------------------------------------------------

//| Implicit instantiation of a class template does only instantiate member
//| functions when needed (Dec. 1996 C++ Standard draft, 14.7.1). 
//| This implies that member functions that are not instantiated in a 
//| certain context are allowed to use functionality from the template 
//| arguments that are not provided by the actual argument. For example
//| the Gnu g++ 2.7.2 does not comply to this. The following definition
//| is set if the implicit instantiation does not work in this lazy fashion.

#include <assert.h>

struct A {
    int i;
    A( int _i) : i(_i) {}
    A& operator++() {
	++i;
	return *this;
    }
};

template< class T>
struct B {
    T a;
    B( T _a) : a(_a) {}
    B& operator++() {
	++a;
	return *this;
    }
    B& operator--() {  // This one is not used nor supported by A.
	--a;
	return *this;
    }
};

int main() {
    A a( 5);
    B<A> b( a);
    ++b;
    assert( b.a.i == 6);
    return 0;
}

// EOF //
