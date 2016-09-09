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
// file          : include/CGAL/Topological_map_new.h
// package       : Planar_map (5.113)
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
#ifndef  CGAL_TOPOLOGICAL_MAP_H
#define  CGAL_TOPOLOGICAL_MAP_H

#include <CGAL/Topological_map_items.h>
#include <CGAL/HalfedgeDS_default.h>

CGAL_BEGIN_NAMESPACE

template < class Traits,
           class TopologicalMapItems = Topological_map_items,
#ifndef CGAL_CFG_NO_TMPL_IN_TMPL_PARAM
           template < class T, class I, class A>
#endif
           class T_HDS = HalfedgeDS_default, 
           class Alloc = CGAL_ALLOCATOR(int)>
class Topological_map
{
  typedef Topological_map < Traits, TopologicalMapItems, T_HDS, Alloc> Self;
  typedef TopologicalMapItems                                          Items;

#ifndef CGAL_CFG_NO_TMPL_IN_TMPL_PARAM
  typedef T_HDS< Traits, Items, Alloc>  HDS;
#else
  typedef typename T_HDS::template HDS< Traits, Items, Alloc>  HDS;
#endif

};

CGAL_END_NAMESPACE

#endif // CGAL_TOPOLOGICAL_MAP_H




