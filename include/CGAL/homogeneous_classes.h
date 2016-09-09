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
// source        : Homogeneous.fw
// file          : include/CGAL/homogeneous_classes.h
// package       : Kernel_basic (2.0.11)
// revision      : 2.0.11
// revision_date : 06 May 1999 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_HOMOGENEOUS_CLASSES_H
#define CGAL_HOMOGENEOUS_CLASSES_H

CGAL_BEGIN_NAMESPACE

template < class FT, class RT >
class PointH2;

template < class FT, class RT >
class VectorH2;

template < class FT, class RT >
class DirectionH2;

template < class FT, class RT >
class LineH2;

template < class FT, class RT >
class RayH2;

template < class FT, class RT >
class SegmentH2;

template < class FT, class RT >
class TriangleH2;

template < class FT, class RT >
class CircleH2;

template < class FT, class RT >
class Iso_rectangleH2;

template < class FT, class RT >
class Aff_transformationH2;

template < class FT, class RT >
class PointH3;

template < class FT, class RT >
class VectorH3;

template < class FT, class RT >
class DirectionH3;

template < class FT, class RT >
class PlaneH3;

template < class FT, class RT >
class LineH3;

template < class FT, class RT >
class RayH3;

template < class FT, class RT >
class SegmentH3;

template < class FT, class RT >
class TriangleH3;

template < class FT, class RT >
class Iso_rectangleH3;

template < class FT, class RT >
class TetrahedronH3;

template < class FT, class RT >
class Aff_transformationH3;

template < class PT, class DA >
class ConicHPA2;

template <class FT, class RT>
class PointHd;

CGAL_END_NAMESPACE


#endif // CGAL_HOMOGENEOUS_CLASSES_H
