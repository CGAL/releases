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
// file          : include/CGAL/Halfedge_data_structure_default.h
// author(s)     : Lutz Kettner  
//
// email         : cgal@cs.uu.nl
//
// ============================================================================

#ifndef CGAL_HALFEDGE_DATA_STRUCTURE_DEFAULT_H
#define CGAL_HALFEDGE_DATA_STRUCTURE_DEFAULT_H 1
#ifndef CGAL_HALFEDGE_DATA_STRUCTURE_BASES_H
#include <CGAL/Halfedge_data_structure_bases.h>
#endif

#ifndef CGAL_HALFEDGE_DATA_STRUCTURE_USING_LIST_H
#include <CGAL/Halfedge_data_structure_using_list.h>
#endif

template <class Pt>
class CGAL_Halfedge_data_structure_default
    : public CGAL_Halfedge_data_structure_using_list<
          CGAL_Vertex_max_base<Pt>,
          CGAL_Halfedge_max_base,
          CGAL_Facet_max_base
      > {
public:  // CREATION

    CGAL_Halfedge_data_structure_default() {}
    CGAL_Halfedge_data_structure_default( Size v, Size h, Size f)
        : CGAL_Halfedge_data_structure_using_list<
              CGAL_Vertex_max_base<Pt>,
              CGAL_Halfedge_max_base,
              CGAL_Facet_max_base
          > (v,h,f) {}
};
#endif // CGAL_HALFEDGE_DATA_STRUCTURE_DEFAULT_H //
// EOF //
