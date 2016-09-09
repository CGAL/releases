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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.1
// release_date  : 1998, July 24
//
// file          : include/CGAL/IO/polygon_Window_stream.h
// package       : Polygon (1.10)
// source        :
// revision      : 1.8a
// revision_date : 13 Mar 1998
// author(s)     : Wieger Wesselink
//
// coordinator   : Utrecht University
// email         : cgal@cs.uu.nl
//
// ======================================================================

// Window_stream I/O operators
// ===========================

// Polygon_2
// ---------
#ifdef CGAL_POLYGON_2_H
#ifndef CGAL_WINDOW_STREAM_POLYGON_2_H
#define CGAL_WINDOW_STREAM_POLYGON_2_H
template <class Traits, class Container>
CGAL_Window_stream&
operator<<(CGAL_Window_stream& ws,
           const CGAL_Polygon_2<Traits,Container> &polygon)
{
  typedef CGAL_Polygon_2<Traits,Container>::Edge_const_circulator EI;
  EI e = polygon.edges_circulator();
  if (e != NULL) {
    EI end = e;
    do {
      ws << *e;
      ws << (*e).source();
      ++e;
      } while (e != end);
    }
  return ws;
}
#endif // CGAL_WINDOW_STREAM_POLYGON_2_H
#endif // CGAL_POLYGON_2_H

