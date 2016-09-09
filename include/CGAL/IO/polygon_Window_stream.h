// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/IO/polygon_Window_stream.h
// package       : Polygon (2.19)
// source        :
// revision      : 1.8a
// revision_date : 13 Mar 1998
// author(s)     : Wieger Wesselink
//
// coordinator   : Utrecht University
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

// Window_stream I/O operators
// ===========================

// Polygon_2
// ---------
#ifdef CGAL_POLYGON_2_H
#ifndef CGAL_WINDOW_STREAM_POLYGON_2_H
#define CGAL_WINDOW_STREAM_POLYGON_2_H

CGAL_BEGIN_NAMESPACE

template <class Traits, class Container>
Window_stream&
operator<<(Window_stream& ws,
           const Polygon_2<Traits,Container> &polygon)
{
  typedef Polygon_2<Traits,Container>::Edge_const_circulator EI;
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

CGAL_END_NAMESPACE

#endif // CGAL_WINDOW_STREAM_POLYGON_2_H
#endif // CGAL_POLYGON_2_H

