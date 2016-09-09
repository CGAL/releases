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
// file          : include/CGAL/Halfedge_data_structure_polyhedron_default_3.h
// author(s)     : Lutz Kettner  
//
// email         : cgal@cs.uu.nl
//
// ============================================================================

#ifndef CGAL_HALFEDGE_DATA_STRUCTURE_POLYHEDRON_DEFAULT_3_H
#define CGAL_HALFEDGE_DATA_STRUCTURE_POLYHEDRON_DEFAULT_3_H 1
#ifndef CGAL_HALFEDGE_DATA_STRUCTURE_BASES_H
#include <CGAL/Halfedge_data_structure_bases.h>
#endif

#ifndef CGAL_HALFEDGE_DATA_STRUCTURE_USING_LIST_H
#include <CGAL/Halfedge_data_structure_using_list.h>
#endif

#ifdef CGAL_HALFEDGE_DATA_STRUCTURE_POLYHEDRON_DEFAULT_3_H

#ifndef CGAL_POINT_3_H
#include <CGAL/Point_3.h>
#endif
#ifndef CGAL_PLANE_3_H
#include <CGAL/Plane_3.h>
#endif
#ifndef CGAL_VECTOR_3_H
#include <CGAL/Vector_3.h>
#endif

    template <class _R>
    class CGAL_Halfedge_data_structure_polyhedron_default_3
        : public CGAL_Halfedge_data_structure_using_list<
              CGAL_Vertex_max_base< CGAL_Point_3< _R > >,
              CGAL_Halfedge_max_base,
              CGAL_Polyhedron_facet_base_3< _R >
          > {
    public:  // CREATION

        CGAL_Halfedge_data_structure_polyhedron_default_3() {}
        CGAL_Halfedge_data_structure_polyhedron_default_3(
            Size v, Size h, Size f)
            : CGAL_Halfedge_data_structure_using_list<
                  CGAL_Vertex_max_base< CGAL_Point_3<_R> >,
                  CGAL_Halfedge_max_base,
                  CGAL_Polyhedron_facet_base_3< _R >
              > (v,h,f) {}
    };

#else // CGAL_HALFEDGE_DATA_STRUCTURE_POLYHEDRON_DEFAULT_3_H //
// The following is part of a local project where the halfedge date
// structure has evolved from. It is not part of CGAL and not used.

    template <class Pt, class Pln>
    class CGAL_Halfedge_data_structure_polyhedron_default_3
        : public CGAL_Halfedge_data_structure_using_list<
              CGAL_Vertex_max_base<Pt>,
              CGAL_Halfedge_max_base,
              CGAL_Polyhedron_facet_base_3<Pln>
          > {
    public:  // CREATION

        CGAL_Halfedge_data_structure_polyhedron_default_3() {}
        CGAL_Halfedge_data_structure_polyhedron_default_3(
            Size v, Size h, Size f)
            : CGAL_Halfedge_data_structure_using_list<
                  CGAL_Vertex_max_base<Pt>,
                  CGAL_Halfedge_max_base,
                  CGAL_Polyhedron_facet_base_3<Pln>
              > (v,h,f) {}
    };
#endif // CGAL_HALFEDGE_DATA_STRUCTURE_POLYHEDRON_DEFAULT_3_H //
#endif // CGAL_HALFEDGE_DATA_STRUCTURE_POLYHEDRON_DEFAULT_3_H //
// EOF //
