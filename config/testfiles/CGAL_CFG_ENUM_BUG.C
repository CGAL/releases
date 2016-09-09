// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : config/testfiles/CGAL_CFG_ENUM_BUG.C
// package       : Configuration (2.32)
// source        :
// revision      : 1.11
// revision_date : 29 Mar 1998
// author(s)     : various
//
// coordinator   : Utrecht University
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

// CGAL_CFG_ENUM_BUG.C
// ---------------------------------------------------------------------
// This program is used by cgal_configure.
// The following documentation will be pasted in the generated configfile.
// ---------------------------------------------------------------------

//| This flag is set, if the compiler does not promote enumeration types
//| (which depend on a template parameter) correctly when they are used 
//| as int template arguments. (e.g. Borland 5.5)

struct F {
  enum { a = 1 };
};

template < int i > struct B;
template <> struct B< 1 > {};

template < class T >
struct C {
  enum { ar = T::a };
  B< ar > b;
  // gives
  // Borland C++ 5.5.1 for Win32 Copyright (c) 1993, 2000 Borland
  // Error E2450 Undefined structure 'B<0>' in function main()
  
  // using 
  // B< T::a > b;
  // instead gives
  // Borland C++ 5.5.1 for Win32 Copyright (c) 1993, 2000 Borland
  // Error E2401 Invalid template argument list
  // Error E2040 Declaration terminated incorrectly
};

int main()
{
  C< F > c;
  (void) c;
  return 0;
}

// EOF //
