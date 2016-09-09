// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/Halfedge_data_structure_polyhedron_default_3.h
// package       : Halfedge_DS (2.4)
// chapter       : $CGAL_Chapter: Halfedge Data Structures $
// source        : hds.fw
// revision      : $Revision: 1.3 $
// revision_date : $Date: 1999/04/07 19:29:14 $
// author(s)     : Lutz Kettner
//
// coordinator   : MPI Saarbruecken (Stefan Schirra)
//
// Halfedge Data Structure Default for Polyhedral Surfaces.
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_HALFEDGE_DATA_STRUCTURE_POLYHEDRON_DEFAULT_3_H
#define CGAL_HALFEDGE_DATA_STRUCTURE_POLYHEDRON_DEFAULT_3_H 1
#ifndef CGAL_HALFEDGE_DATA_STRUCTURE_BASES_H
#include <CGAL/Halfedge_data_structure_bases.h>
#endif
#ifndef CGAL_HALFEDGE_DATA_STRUCTURE_USING_LIST_H
#include <CGAL/Halfedge_data_structure_using_list.h>
#endif
#ifndef CGAL_POINT_3_H
#include <CGAL/Point_3.h>
#endif
#ifndef CGAL_PLANE_3_H
#include <CGAL/Plane_3.h>
#endif
#ifndef CGAL_VECTOR_3_H
#include <CGAL/Vector_3.h>
#endif

CGAL_BEGIN_NAMESPACE

template <class T>
class Halfedge_data_structure_polyhedron_default_3
    : public Halfedge_data_structure_using_list<
          Vertex_max_base< Point_3<T> >,
          Halfedge_max_base,
          Polyhedron_facet_base_3<T>
      > {
public:  // CREATION
    Halfedge_data_structure_polyhedron_default_3() {}
    Halfedge_data_structure_polyhedron_default_3(
        Size v, Size h, Size f)
        : Halfedge_data_structure_using_list<
              Vertex_max_base< Point_3<T> >,
              Halfedge_max_base,
              Polyhedron_facet_base_3<T>
          > (v,h,f) {}
};

CGAL_END_NAMESPACE
#endif // CGAL_HALFEDGE_DATA_STRUCTURE_POLYHEDRON_DEFAULT_3_H //
// EOF //
