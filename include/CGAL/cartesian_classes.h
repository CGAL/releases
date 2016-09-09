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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/cartesian_classes.h
// package       : Cartesian_basic (1.4)
// source        : web/Cartesian.fw
// revision      : $Revision: 1.6 $
// revision_date : $Date: 1998/06/22 13:03:48 $
// author(s)     : Andreas.Fabri
//
// coordinator   : INRIA Sophia-Antipolis
// (Herve.Bronnimann)
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_CARTESIAN_CLASSES_H
#define CGAL_CARTESIAN_CLASSES_H


#ifndef CGAL_BASIC_CLASSES_H
#include <CGAL/basic_classes.h>
#endif // CGAL_BASIC_CLASSES_H


template < class FT >
class CGAL_PointC2;

template < class FT >
class CGAL_VectorC2;

template < class FT >
class CGAL_DirectionC2;

template < class FT >
class CGAL_LineC2;

template < class FT >
class CGAL_RayC2;

template < class FT >
class CGAL_SegmentC2;

template < class FT >
class CGAL_TriangleC2;

template < class FT >
class CGAL_CircleC2;

template < class FT >
class CGAL_ParabolaC2;

template < class FT >
class CGAL_Parabola_arcC2;

template < class PT, class DA >
class CGAL_ConicCPA2;

template < class FT >
class CGAL_Iso_rectangleC2;

template < class FT >
class CGAL_Iso_rectangleC3;

template < class FT >
class CGAL_Aff_transformation_baseC2;

template < class R >
class CGAL_Aff_transformation_base_2;

template < class FT >
class CGAL_Aff_transformationC2;

template < class FT >
class CGAL_PlaneC3;

template < class FT >
class CGAL_PointC3;

template < class FT >
class CGAL_VectorC3;

template < class FT >
class CGAL_DirectionC3;

template < class FT >
class CGAL_LineC3;

template < class FT >
class CGAL_RayC3;

template < class FT >
class CGAL_SegmentC3;

template < class FT >
class CGAL_TriangleC3;

template < class FT >
class CGAL_TetrahedronC3;

template < class FT >
class CGAL_Aff_transformationC3;

template < class FT >
class CGAL_PointCd;

#endif // CGAL_CARTESIAN_CLASSES_H
