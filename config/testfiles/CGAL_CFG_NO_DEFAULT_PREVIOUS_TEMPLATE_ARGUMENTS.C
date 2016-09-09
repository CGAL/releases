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
// file          : config/testfiles/CGAL_CFG_NO_DEFAULT_PREVIOUS_TEMPLATE_ARGUMENTS.C
// author(s)     : various
//
// email         : cgal@cs.uu.nl
//
// ============================================================================

//CGAL_CFG_NO_DEFAULT_PREVIOUS_TEMPLATE_ARGUMENTS.C
// ---------------------------------------------------------------------
// A short test program to evaluate a C++ compiler.
// This program is used by cgal_configure.
// The following documentation will be pasted in the generated configfile.
// ---------------------------------------------------------------------

//| Default template arguments that are dependant on previous template
//| arguments like in 'template< class A, class C = vector<A> >' are not
//| supported by any compiler. The following definition is set if they are
//| not supported. Note that if CGAL_CFG_NO_DEFAULT_TEMPLATE_ARGUMENTS is 
//| set, this definition must also be set.

template< class T = int>
struct A {
    T i;
    A( T _i) : i(_i) {}
};

template< class S, class T = S>
struct B {
    S i;
    T j;
    B( S _i, T _j) : i(_i), j(_j) {}
};

int main() {
    A<> a( 5);
    B<double> b( 0.4, 8.3);
    return 0;
}

// EOF //
