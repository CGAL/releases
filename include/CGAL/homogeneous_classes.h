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
// source        : Homogeneous.fw
// file          : include/CGAL/homogeneous_classes.h
// package       : Kernel_basic (1.2)
// revision      : 1.2
// revision_date : 12 Jun 1998 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_HOMOGENEOUS_CLASSES_H
#define CGAL_HOMOGENEOUS_CLASSES_H

template < class FT, class RT >
class CGAL_PointH2;

template < class FT, class RT >
class CGAL_VectorH2;

template < class FT, class RT >
class CGAL_DirectionH2;

template < class FT, class RT >
class CGAL_LineH2;

template < class FT, class RT >
class CGAL_RayH2;

template < class FT, class RT >
class CGAL_SegmentH2;

template < class FT, class RT >
class CGAL_TriangleH2;

template < class FT, class RT >
class CGAL_CircleH2;

template < class FT, class RT >
class CGAL_Iso_rectangleH2;

template < class FT, class RT >
class CGAL_Aff_transformationH2;

template < class FT, class RT >
class CGAL_PointH3;

template < class FT, class RT >
class CGAL_VectorH3;

template < class FT, class RT >
class CGAL_DirectionH3;

template < class FT, class RT >
class CGAL_PlaneH3;

template < class FT, class RT >
class CGAL_LineH3;

template < class FT, class RT >
class CGAL_RayH3;

template < class FT, class RT >
class CGAL_SegmentH3;

template < class FT, class RT >
class CGAL_TriangleH3;

template < class FT, class RT >
class CGAL_Iso_rectangleH3;

template < class FT, class RT >
class CGAL_TetrahedronH3;

template < class FT, class RT >
class CGAL_Aff_transformationH3;

template < class PT, class DA >
class CGAL_ConicHPA2;

template <class FT, class RT>
class CGAL_PointHd;


#endif // CGAL_HOMOGENEOUS_CLASSES_H
