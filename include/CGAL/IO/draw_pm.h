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
// file          : include/CGAL/IO/draw_pm.h
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
#ifndef CGAL_IO_DRAW_PM_H
#define CGAL_IO_DRAW_PM_H

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif

//#ifndef CGAL_PLANAR_MAP_2_H
//#include <CGAL/Planar_map_2.h>
//#endif

#ifndef CGAL_INVERSE_INDEX_H
#include <CGAL/Inverse_index.h>
#endif

#include <iostream>

CGAL_BEGIN_NAMESPACE


template <class PM, class Drawer, class Window>
void draw_pm(const PM& pm,
             Drawer& drawer, 
             Window& w) 
{

  drawer.draw_faces(pm.faces_begin(), pm.faces_end());
  
  drawer.draw_halfedges(pm.halfedges_begin(), pm.halfedges_end());

  drawer.draw_vertices(pm.vertices_begin(), pm.vertices_end());
}

CGAL_END_NAMESPACE

#endif




