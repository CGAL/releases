// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/Triangulation_short_names_3.h
// package       : Triangulation_3 (1.83)
// revision      : $Revision: 1.15 $
//
// author(s)     : Monique Teillaud
//
// coordinator   : INRIA Sophia Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_SHORT_NAMES_3_H
#define CGAL_TRIANGULATION_SHORT_NAMES_3_H

#define Triangulation_vertex_base_3                 T_vb
#define Triangulation_cell_base_3                   T_cb

#define Triangulation_geom_traits_3                 T_gt

#define Triangulation_data_structure_3              TDS

#define Triangulation_ds_vertex_3                   TDS_v
#define Triangulation_ds_cell_3                     TDS_c

#define Triangulation_ds_vertex_iterator_3          TDS_vit
#define Triangulation_ds_edge_iterator_3            TDS_eit
#define Triangulation_ds_facet_iterator_3           TDS_fit
#define Triangulation_ds_cell_iterator_3            TDS_cit

#define Triangulation_ds_cell_circulator_3          TDS_ccir
#define Triangulation_ds_facet_circulator_3         TDS_fcir

#define Triangulation_3                             TR

#define Triangulation_vertex_3                      T_v
#define Triangulation_cell_3                        T_c

#define Triangulation_vertex_handle_3               T_vh
#define Triangulation_cell_handle_3                 T_ch

#define Triangulation_vertex_iterator_3             T_vit
#define Triangulation_edge_iterator_3               T_eit
#define Triangulation_facet_iterator_3              T_fit
#define Triangulation_cell_iterator_3               T_cit

#define Triangulation_cell_circulator_3             T_ccir
#define Triangulation_facet_circulator_3            T_fcir

#define Delaunay_triangulation_3                    DT
#define Delaunay_remove_tds_face_3_2                DRf32
#define Delaunay_remove_tds_vertex_3_2              DRv32
#define Delaunay_remove_tds_halfedge_compare_3_2    DRthc32

#define Regular_triangulation_euclidean_traits_3    R_gt
#define Regular_triangulation_3                     RT

#define Triangulation_hierarchy_3                   TH_3
#define Triangulation_hierarchy_vertex_base_3       TH_vb3

#endif // CGAL_TRIANGULATION_SHORT_NAMES_3_H
