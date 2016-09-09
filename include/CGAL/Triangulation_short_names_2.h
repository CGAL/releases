// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/Triangulation_short_names_2.h
// package       : Triangulation (2.10)
// source        : $Source: /u/alcor/0/prisme_util/CGAL/Local/cvsroot/Triangulation/include/CGAL/Triangulation_short_names_2.h,v $
// revision      : $Revision: 1.3.1.4 $
// revision_date : $Date: 1998/12/03 17:11:35 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_SHORT_NAMES_2_H
#define CGAL_TRIANGULATION_SHORT_NAMES_2_H




// Define shorter names to please linker (g++/egcs)
   #define CGAL_Triangulation_default_data_structure_2 CGAL_Tdds
   #define CGAL_Triangulation_vertex_base_2  CGAL_Trvb
   #define CGAL_Triangulation_face_base_2  CGAL_Trfb
   #define CGAL_Triangulation_euclidean_traits_2 CGAL_Et2
   #define CGAL_Triangulation_euclidean_traits_xy_3 GGAL_Etxy3
   #define CGAL_Triangulation_euclidean_traits_xz_3 CGAL_Etxz3
   #define CGAL_Triangulation_euclidean_traits_yz_3 CGAL_Etyz3

   #define CGAL_Constrained_triangulation_face_base_2  CGAL_Ctrfb
   #define CGAL_Regular_triangulation_euclidean_traits_2 CGAL_Rtet2

   #define CGAL_Triangulation_vertex_2 CGAL_Trv
   #define CGAL_Triangulation_face_2 CGAL_Trf
   #define CGAL_Triangulation_vertex_handle_2 CGAL_Trvh
   #define CGAL_Triangulation_face_handle_2 CGAL_Trfh
   #define CGAL_Triangulation_vertex_iterator_2 CGAL_Trvi
   #define CGAL_Triangulation_face_iterator_2 CGAL_Trfi
   #define CGAL_Triangulation_edge_iterator_2 CGAL_Trei
   #define CGAL_Triangulation_vertex_circulator_2 CGAL_Trvc
   #define CGAL_Triangulation_face_circulator_2 CGAL_Trfc
   #define CGAL_Triangulation_edge_circulator_2 CGAL_Trec


#endif //CGAL_TRIANGULATION_SHORT_NAMES_2_H
