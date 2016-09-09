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
// file          : include/CGAL/IO/Pm_Postscript_file_stream.h
// package       : Planar_map (5.113)
// source        : 
// revision      : 
// revision_date : 
// author(s)     : Eti Ezra
//
//
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// Chapter       : 
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_IO_PM_POSTSCRIPT_FILE_STREAM_H
#define CGAL_IO_PM_POSTSCRIPT_FILE_STREAM_H

#ifndef CGAL_LEDA_WINDOW_H
#include <CGAL/IO/leda_window.h>
#endif

#ifndef CGAL_POSTSCRIPT_FILE_STREAM_H
#include <CGAL/IO/Postscript_file_stream.h>
#endif

#ifndef CGAL_PLANAR_MAP_2_H
#include <CGAL/Planar_map_2.h>
#endif
  
/*  #ifndef CGAL_IO_PM_BOUNDING_BOX_BASE_WINDOW_STREAM_H
  #include <CGAL/IO/Pm_bounding_box_base_Window_stream.h>
  #endif
*/

#ifndef CGAL_IO_PM_DRAWER_H
#include <CGAL/IO/Pm_drawer.h>
#endif

#ifndef CGAL_IO_DRAW_PM_H
#include  <CGAL/IO/draw_pm.h>
#endif

CGAL_BEGIN_NAMESPACE

template <class Dcel,class Traits>
Postscript_file_stream & operator << (Postscript_file_stream & ps,
                                      Planar_map_2<Dcel,Traits> & pm)
{
  Pm_drawer< Planar_map_2<Dcel,Traits> , Postscript_file_stream>  drawer(ps);
  
  draw_pm(pm, drawer, ps);

  return ps;
}  


/*template <class Dcel,class Traits>
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
        } */ 


CGAL_END_NAMESPACE

#endif







