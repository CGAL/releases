// ======================================================================
//
// Copyright (c) 1997-2000 The CGAL Consortium

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
// file          : include/CGAL/IO/Filtered_extended_homogeneous_Window_stream.h
// package       : Nef_2 (1.18)
// chapter       : Nef Polyhedra
//
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2001/06/22 09:18:25 $
//
// author(s)     : Michael Seel
// coordinator   : Michael Seel
//
// implementation: Drawing filtered extended objects
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef FILTERED_EXTENDED_HOMOGENEOUS_WINDOW_STREAM_H
#define FILTERED_EXTENDED_HOMOGENEOUS_WINDOW_STREAM_H

#ifdef CGAL_USE_LEDA
#include <CGAL/Filtered_extended_homogeneous.h>
#include <CGAL/IO/Window_stream.h>

CGAL_BEGIN_NAMESPACE

template <class RT> 
CGAL::Window_stream& operator<<(CGAL::Window_stream& w, 
                                const Extended_point<RT>& p)
{ w.draw_filled_node(CGAL::to_double(p.x()),CGAL::to_double(p.y())); 
  return w;
}

template <class RT> 
CGAL::Window_stream& operator<<(CGAL::Window_stream& w, 
                                const Extended_segment<RT>& s)
{ w.draw_segment(CGAL::to_double(s.source().x()),
                 CGAL::to_double(s.source().y()),
                 CGAL::to_double(s.target().x()),
                 CGAL::to_double(s.target().y())); 
  return w;
}

template <class RT> 
leda_point pnt(const Extended_point<RT>& p)
{ return leda_point(CGAL::to_double(p.x()),CGAL::to_double(p.y())); }

CGAL_END_NAMESPACE
#endif // CGAL_USE_LEDA
#endif // FILTERED_EXTENDED_HOMOGENEOUS_WINDOW_STREAM_H

