// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.3
// release_date  : 2001, August 13
// 
// file          : include/CGAL/IEEE_754_unions.h
// package       : Number_types (4.30)
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2001/06/14 13:03:06 $
// author(s)     : Stefan Schirra
//
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 
#ifndef CGAL_IEEE_754_UNIONS_H
#define CGAL_IEEE_754_UNIONS_H

#include <iomanip>

union IEEE_754_double
{
  double   a;
#ifdef CGAL_BIG_ENDIAN
  struct { unsigned sign : 1;
           unsigned exp  :11;
           unsigned high :20;
           unsigned low  :32;
         } b;
  struct { unsigned H    :32;
           unsigned L    :32;
         } c;
#else
  struct { unsigned low  :32;
           unsigned sign : 1;
           unsigned exp  :11;
           unsigned high :20;
         } b;
  struct { unsigned L    :32;
           unsigned H    :32;
         } c;
#endif
};

union IEEE_754_float
{
  float    a;
  struct { unsigned sign : 1;
           unsigned exp  : 8;
           unsigned high :23;
         } b;
  unsigned c;
};

inline
void
show( IEEE_754_double* p)
{
  std::cout << std::endl;
  std::cout << std::hex << std::setw(8) << std::setfill('0') << p->c.H;
  std::cout << ' ';
  std::cout << std::hex << std::setw(8) << std::setfill('0') << p->c.L;
  std::cout << std::endl;
}

inline
void
show( IEEE_754_float* p)
{
  std::cout << std::endl;
  std::cout << std::hex << std::setw(8) << std::setfill('0') << p->c;
  std::cout << std::endl;
}

#endif // CGAL_IEEE_754_UNIONS_H
