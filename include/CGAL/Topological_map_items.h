// ======================================================================
//
// Copyright (c) 2001 The CGAL Consortium

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
// file          : include/CGAL/Topological_map_items.h
// package       : Planar_map (5.113)
// author(s)     : Shai Hirsch
//
// coordinator   : Tel-Aviv University (Dan Halperin halperin<@math.tau.ac.il>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_TOPOLOGICAL_MAP_ITEMS_H
#define CGAL_TOPOLOGICAL_MAP_ITEMS_H 1

#ifndef CGAL_HALFEDGEDS_VERTEX_BASE_H
#include <CGAL/HalfedgeDS_vertex_base.h>
#endif
#ifndef CGAL_HALFEDGEDS_HALFEDGE_BASE_H
#include <CGAL/HalfedgeDS_halfedge_base.h>
#endif
#ifndef CGAL_HALFEDGEDS_FACE_BASE_H
#include <CGAL/Topological_map_face_base.h>
#endif

CGAL_BEGIN_NAMESPACE

class Topological_map_items {
public:
  template < class Refs, class Traits >
  struct Vertex_wrapper {
    typedef typename Traits::Point_2 Point;
    typedef HalfedgeDS_vertex_base< Refs, Tag_true, Point > Vertex;
  };
  template < class Refs, class Traits>
  struct Halfedge_wrapper {
    typedef typename Traits::X_curve X_curve;
    typedef HalfedgeDS_halfedge_base< Refs >                Halfedge;
  };
  template < class Refs, class Triats>
  struct Face_wrapper {
    typedef Topological_map_face_list_base< Refs >          Face;
  };
};

CGAL_END_NAMESPACE
#endif // CGAL_TOPOLOGICAL_MAP_ITEMS_H
// EOF //
