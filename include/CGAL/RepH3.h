// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.1
// release_date  : 2000, January 11
// 
// source        : PointVectorDirectionH3.fw
// file          : include/CGAL/RepH3.h
// package       : H3 (2.3.7)
// revision      : 2.3.7
// revision_date : 03 Dec 1999 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_REPH3_H
#define CGAL_REPH3_H

CGAL_BEGIN_NAMESPACE

template <class NT>
class iRepH3 : public Rep
{
public:
  NT  e0;
  NT  e1;
  NT  e2;
  NT  e3;

  iRepH3()
   // : e0(NT(42)), e1(NT(42)), e2(NT(42)), e3(NT(1))
  {}
  iRepH3(const NT& a0, const NT& a1, const NT& a2, const NT& a3)
    : e0(a0), e1(a1), e2(a2), e3(a3)
  {}
  ~iRepH3()
  {}

  NT    hx() { return e0; }
  NT    hy() { return e1; }
  NT    hz() { return e2; }
  NT    hw() { return e3; } // homogenizing component
};


CGAL_END_NAMESPACE


#endif // CGAL_REPH3_H
