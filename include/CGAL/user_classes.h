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
// source        : user_classes.fw
// file          : include/CGAL/user_classes.h
// package       : Kernel_basic (2.0.11)
// revision      : 2.0.11
// revision_date : 06 May 1999 
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : cgal@cs.uu.nl
//
// ======================================================================
 

#ifndef CGAL_USER_CLASSES_H
#define CGAL_USER_CLASSES_H

CGAL_BEGIN_NAMESPACE

template < class R >
class Point_2;

template < class R >
class Vector_2;

template < class R >
class Direction_2;

template < class R >
class Line_2;

template < class R >
class Ray_2;

template < class R >
class Segment_2;

template < class R >
class Triangle_2;

template < class R >
class Iso_rectangle_2;

template < class R >
class Iso_rectangle_3;

template < class R >
class Aff_transformation_base_2;

template < class R >
class Aff_transformation_2;

template < class R >
class Aff_transformation_3;

template < class R >
class Plane_3;

template < class FT >
class Point_3;

template < class FT >
class Vector_3;

template < class FT >
class Direction_3;

template < class R >
class Line_3;

template < class FT >
class Ray_3;

template < class FT >
class Segment_3;

template < class FT >
class Triangle_3;

template < class FT >
class Tetrahedron_3;


template < class R >
class _Vector_2_rft_wrapper;

template < class R >
class _Vector_3_rft_wrapper;

template < class R>
class Point_d;
CGAL_END_NAMESPACE

#endif  // CGAL_USER_CLASSES_H
