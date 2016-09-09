// ======================================================================
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
// ----------------------------------------------------------------------
// 
// release       : CGAL-1.1
// release_date  : 1998, July 24
// 
// source        : user_classes.fw
// file          : include/CGAL/user_classes.h
// package       : Kernel_basic (1.2)
// revision      : 1.2
// revision_date : 12 Jun 1998 
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : cgal@cs.uu.nl
//
// ======================================================================
 

#ifndef CGAL_USER_CLASSES_H
#define CGAL_USER_CLASSES_H

template < class R >
class CGAL_Point_2;

template < class R >
class CGAL_Vector_2;

template < class R >
class CGAL_Direction_2;

template < class R >
class CGAL_Line_2;

template < class R >
class CGAL_Ray_2;

template < class R >
class CGAL_Segment_2;

template < class R >
class CGAL_Triangle_2;

template < class R >
class CGAL_Iso_rectangle_2;

template < class R >
class CGAL_Iso_rectangle_3;

template < class R >
class CGAL_Aff_transformation_base_2;

template < class R >
class CGAL_Aff_transformation_2;

template < class R >
class CGAL_Aff_transformation_3;

template < class R >
class CGAL_Plane_3;

template < class FT >
class CGAL_Point_3;

template < class FT >
class CGAL_Vector_3;

template < class FT >
class CGAL_Direction_3;

template < class R >
class CGAL_Line_3;

template < class FT >
class CGAL_Ray_3;

template < class FT >
class CGAL_Segment_3;

template < class FT >
class CGAL_Triangle_3;

template < class FT >
class CGAL_Tetrahedron_3;


template < class R >
class CGAL__Vector_2_rft_wrapper;

template < class R >
class CGAL__Vector_3_rft_wrapper;

template < class R>
class CGAL_Point_d;

#endif  // CGAL_USER_CLASSES_H
