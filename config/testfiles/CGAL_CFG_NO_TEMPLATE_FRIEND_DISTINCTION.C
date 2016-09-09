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
// file          : config/testfiles/CGAL_CFG_NO_TEMPLATE_FRIEND_DISTINCTION.C
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

// CGAL_CFG_NO_TEMPLATE_FRIEND_DISTINCTION.C
// ---------------------------------------------------------------------
// A short test program to evaluate a C++ compiler whether it distinguishes
// a template instantiation and a non-templated function with the same
// signature in a friend declaration.
// This program is used by cgal_configure.
// The following documentation will be pasted in the generated configfile.
// ---------------------------------------------------------------------

//| If a compiler doesn't distinguish a template instantiation and 
//| a non-templated function with the same signature, 
//| CGAL_CFG_NO_TEMPLATE_FRIEND_DISTINCTION is set.

template < class T >
int y( const T& t) {
  return t.a;
}

template < class T >
T
operator+(const T& a, const T&) {
  return a;
}

class X {
  int a;
  friend int y<>( const X&);
  friend X operator+<>(const X&, const X&);
};

int main()
{
  X x;
  y( x);
  X z = x + x;
  return 0;
}

// EOF //

