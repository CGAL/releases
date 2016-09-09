// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// file          : include/CGAL/Triangulation_short_names_3.h
// package       : Triangulation3 (1.29)
// revision      : $Revision: 1.10 $
//
// author(s)     : Monique Teillaud
//
// coordinator   : INRIA Sophia Antipolis 
//                 (Mariette Yvinec)
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_SHORT_NAMES_3_H
#define CGAL_TRIANGULATION_SHORT_NAMES_3_H

// needed for MSVC

// ======
#define Triangulation_vertex_base_3                 T_vb
#define Triangulation_cell_base_3                   T_cb

#define Triangulation_geom_traits_3                 T_gt

// ======
#define Triangulation_data_structure_3              TDS

#define Triangulation_ds_vertex_3                   TDS_v
#define Triangulation_ds_cell_3                     TDS_c

#define Triangulation_ds_vertex_iterator_3          TDS_vit
#define Triangulation_ds_edge_iterator_3            TDS_eit
#define Triangulation_ds_facet_iterator_3           TDS_fit
#define Triangulation_ds_cell_iterator_3            TDS_cit

#define Triangulation_ds_cell_circulator_3          TDS_ccir
#define Triangulation_ds_facet_circulator_3         TDS_fcir

// ======
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

// ======
#define Delaunay_triangulation_3                    DT

#define Regular_triangulation_euclidean_traits_3    R_gt
#define Regular_triangulation_3                     RT


#endif //CGAL_TRIANGULATION_SHORT_NAMES_3_H
