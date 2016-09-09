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
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : include/CGAL/Triangulation_short_names_2.h
// package       : Triangulation (4.30)
// source        : $RCSfile: Triangulation_short_names_2.h,v $
// revision      : $Revision: 1.9 $
// revision_date : $Date: 1999/08/19 15:06:02 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_SHORT_NAMES_2_H
#define CGAL_TRIANGULATION_SHORT_NAMES_2_H


//Define shorter names to please linker (g++/egcs)

#define Triangulation_default_data_structure_2 Tdds
#define Triangulation_vertex_base_2  Tvb
#define Triangulation_face_base_2  Tfb
#define Triangulation_euclidean_traits_2 Et2
#define Triangulation_euclidean_traits_xy_3 Etxy3
#define Triangulation_euclidean_traits_xz_3 Etxz3
#define Triangulation_euclidean_traits_yz_3 Etyz3



#define Triangulation_ds_vertex_2             Tdsv
#define Triangulation_ds_face_2               Tdsf
#define Triangulation_vertex_2                Tv
#define Triangulation_face_2                  Tf
#define Triangulation_vertex_handle_2           Tvh
#define Triangulation_face_handle_2           Tfh
#define Triangulation_vertex_iterator_2       Tvi
#define Triangulation_face_iterator_2         Tfi
#define Triangulation_edge_iterator_2         Tei
#define Triangulation_all_faces_iterator_2    Tafi
#define Triangulation_all_edges_iterator_2    Taei
#define Triangulation_all_vertices_iterator_2 Tavi
#define Triangulation_finite_faces_iterator_2 Tffi
#define Triangulation_finite_edges_iterator_2 Tfei
#define Triangulation_finite_vertices_iterator_2 Tfvi
#define Triangulation_vertex_circulator_2     Tvc
#define Triangulation_face_circulator_2       Tfc
#define Triangulation_edge_circulator_2       Tec

#define Constrained_triangulation_face_base_2  Ctfb
#define Regular_triangulation_euclidean_traits_2 Rtet2
#define Regular_triangulation_face_base_2  Rtfb



#endif //CGAL_TRIANGULATION_SHORT_NAMES_2_H
