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
// file          : include/CGAL/IO/Planar_map_Window_stream.h
// package       : pm (5.43)
// source        : 
// revision      : 
// revision_date : 
// author(s)     : Iddo Hanniel
//                 Oren Nechushtan
//
//
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// Chapter       : 
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_IO_PLANAR_MAP_WINDOW_STREAM_H
#define CGAL_IO_PLANAR_MAP_WINDOW_STREAM_H

#ifndef CGAL_LEDA_WINDOW_H
#include <CGAL/leda_window.h>
#endif

#ifndef CGAL_PLANAR_MAP_2_H
#include <CGAL/Planar_map_2.h>
#endif
/*
#ifndef CGAL_IO_PM_BOUNDING_BOX_BASE_WINDOW_STREAM_H
#include <CGAL/IO/Pm_bounding_box_base_Window_stream.h>
#endif
*/
CGAL_BEGIN_NAMESPACE

template <class Dcel,class Traits>
Window_stream& operator<<(Window_stream& os,
                          Planar_map_2<Dcel,Traits> &m)
{
//  os << *m.get_bounding_box();
  Halfedge_iterator it = m.halfedges_begin(), end = m.halfedges_end();

  while(it != end){
    os << it->curve();
    os << it->target()->point();
    os << it->source()->point();
    ++it;++it;
  }
  return os;
}  


template <class Dcel,class Traits>
Window_stream& write(Window_stream& os, Planar_map_2<Dcel,Traits> &m)
{
//  os << *m.get_bounding_box();
  Halfedge_iterator it = m.halfedges_begin(), end = m.halfedges_end();
  const Traits& traits=m.get_traits();
  while(it != end){
	write(os,it->curve(),traits);
    ++it;++it;
  }
  return os;
}  


CGAL_END_NAMESPACE

#endif


