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
// file          : include/CGAL/HalfedgeDS_min_items.h
// package       : HalfedgeDS (3.33)
// chapter       : Halfedge Data Structures
//
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2001/12/18 13:01:47 $
//
// author(s)     : Lutz Kettner
// coordinator   : MPI Saarbruecken
//
// Minimal items class for HDS (Vertex, Halfedge, Face).
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_HALFEDGEDS_MIN_ITEMS_H
#define CGAL_HALFEDGEDS_MIN_ITEMS_H 1
#ifndef CGAL_HALFEDGEDS_VERTEX_MIN_BASE_H
#include <CGAL/HalfedgeDS_vertex_min_base.h>
#endif
#ifndef CGAL_HALFEDGEDS_HALFEDGE_MIN_BASE_H
#include <CGAL/HalfedgeDS_halfedge_min_base.h>
#endif
#ifndef CGAL_HALFEDGEDS_FACE_MIN_BASE_H
#include <CGAL/HalfedgeDS_face_min_base.h>
#endif

CGAL_BEGIN_NAMESPACE

class HalfedgeDS_min_items {
public:
    template < class Refs, class Traits>
    struct Vertex_wrapper {
        typedef HalfedgeDS_vertex_min_base< Refs>   Vertex;
    };
    template < class Refs, class Traits>
    struct Halfedge_wrapper {
        typedef HalfedgeDS_halfedge_min_base< Refs> Halfedge;
    };
    template < class Refs, class Traits>
    struct Face_wrapper {
        typedef HalfedgeDS_face_min_base< Refs>     Face;
    };
};

CGAL_END_NAMESPACE
#endif // CGAL_HALFEDGEDS_MIN_ITEMS_H //
// EOF //
