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
// file          : include/CGAL/homogeneous_classes.h
// package       : H2 (2.37)
// revision      : $Revision: 1.1 $
// revision_date : $Date: 2001/06/07 14:42:04 $
// author(s)     : Stefan Schirra
//
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_HOMOGENEOUS_CLASSES_H
#define CGAL_HOMOGENEOUS_CLASSES_H

CGAL_BEGIN_NAMESPACE

template < class R >
class PointH2;

template < class R >
class VectorH2;

template < class R >
class DirectionH2;

template < class R >
class LineH2;

template < class R >
class RayH2;

template < class R >
class SegmentH2;

template < class R >
class TriangleH2;

template < class R >
class CircleH2;

template < class R >
class Iso_rectangleH2;

template < class R >
class Aff_transformationH2;

template < class R >
class PointH3;

template < class R >
class VectorH3;

template < class R >
class DirectionH3;

template < class R >
class PlaneH3;

template < class R >
class LineH3;

template < class R >
class RayH3;

template < class R >
class SegmentH3;

template < class R >
class TriangleH3;

template < class R >
class Iso_rectangleH3;

template < class R >
class TetrahedronH3;

template < class R >
class Iso_cuboidH3;

template < class R >
class SphereH3;

template < class R >
class Aff_transformationH3;

template < class PT, class DA >
class ConicHPA2;

template <class FT, class RT>
class PointHd;

CGAL_END_NAMESPACE


#endif // CGAL_HOMOGENEOUS_CLASSES_H
