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
// file          : include/CGAL/Triangulation_short_names_2.h
// package       : Triangulation (3.17)
// source        : $Source: /u/alcor/0/prisme_util/CGAL/Local/cvsroot/Triangulation/include/CGAL/Triangulation_short_names_2.h,v $
// revision      : $Revision: 1.3.1.10 $
// revision_date : $Date: 1999/04/30 14:09:27 $
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
   #define Triangulation_vertex_base_2  Trvb
   #define Triangulation_face_base_2  Trfb
   #define Triangulation_euclidean_traits_2 Et2
   #define Triangulation_euclidean_traits_xy_3 Etxy3
   #define Triangulation_euclidean_traits_xz_3 Etxz3
   #define Triangulation_euclidean_traits_yz_3 Etyz3

   #define Constrained_triangulation_face_base_2  Ctrfb
   #define Regular_triangulation_euclidean_traits_2 Rtet2

   #define Triangulation_ds_vertex_2 Tdsv
   #define Triangulation_ds_face_2  Tdsf
   #define Triangulation_vertex_2 Trv
   #define Triangulation_face_2 Trf
   #define Triangulation_vertex_handle_2 Trvh
   #define Triangulation_face_handle_2 Trfh
   #define Triangulation_vertex_iterator_2 Trvi
   #define Triangulation_face_iterator_2 Trfi
   #define Triangulation_edge_iterator_2 Trei
   #define Triangulation_vertex_circulator_2 Trvc
   #define Triangulation_face_circulator_2 Trfc
   #define Triangulation_edge_circulator_2 Trec

   #define Regular_triangulation_face_base_2  Rtrfb



#endif //CGAL_TRIANGULATION_SHORT_NAMES_2_H
