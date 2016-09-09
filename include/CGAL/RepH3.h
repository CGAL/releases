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
// file          : include/CGAL/RepH3.h
// author(s)     : Stefan Schirra 
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


#ifndef CGAL_REPH3_H
#define CGAL_REPH3_H

template <class NT>
class CGAL__RepH3 : public CGAL_Rep
{
public:
  NT  e0;
  NT  e1;
  NT  e2;
  NT  e3;

  CGAL__RepH3()
   // : e0(NT(42)), e1(NT(42)), e2(NT(42)), e3(NT(1))
  {}
  CGAL__RepH3(const NT& a0, const NT& a1, const NT& a2, const NT& a3)
    : e0(a0), e1(a1), e2(a2), e3(a3)
  {}
  ~CGAL__RepH3()
  {}

  NT    hx() { return e0; }
  NT    hy() { return e1; }
  NT    hz() { return e2; }
  NT    hw() { return e3; } // homogenizing component
};



#endif // CGAL_REPH3_H