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
// file          : config/testfiles/CGAL_CFG_NO_CONST_REFERENCE_OVERLOADING.C
// package       : Configuration (1.30)
// source        :
// revision      : 1.11
// revision_date : 29 Mar 1998
// author(s)     : various
//
// coordinator   : Utrecht University
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

// CGAL_CFG_NO_CONST_REFERENCE_OVERLOADING.C
// ---------------------------------------------------------------------
// A short test program to evaluate a C++ compiler.
// This program is used by cgal_configure.
// The following documentation will be pasted in the generated configfile.
// ---------------------------------------------------------------------

//| The Gnu g++ 2.7.2.1 isn't able to distinguish cleanly between 
//| overloading with a reference and a const reference parameter
//| if he looks fpor a match with a derived class and reports an 
//| ambigious overloading resolution. One workaround could be to
//| remove the const reference declaration. g++ will warn a converion
//| from const X& to X& but compiles. Another workaround would be the
//| explicit cast to the base class (if known).
//| The following definition is set if the compiler fails to
//| distinguish those functions.


#include <cassert>

struct Y {
    int i;
    Y(int j) : i(j) {}
};

struct X : public Y {
    X(int j) : Y(j) {}
};

template < class T>
struct A {
    T&       foo( T& t)       const { return t; }
    const T& foo( const T& t) const { return t; }
};

int main() {
    A<Y> a;
    X       i(42);
    const X j(43);
    assert( (a.foo(i)).i == 42);
    assert( (a.foo(j)).i == 43);
    return 0;
}

// EOF //


