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
// source        : Homogeneous.fw
// file          : include/CGAL/homogeneous_classes.h
// package       : Kernel_basic (2.9)
// revision      : 2.9
// revision_date : 04 Dec 1999 
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
class Iso_cuboidH3;

template < class FT, class RT >
class Aff_transformationH3;

template < class PT, class DA >
class ConicHPA2;

template <class FT, class RT>
class PointHd;

CGAL_END_NAMESPACE


#endif // CGAL_HOMOGENEOUS_CLASSES_H
