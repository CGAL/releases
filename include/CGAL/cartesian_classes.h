// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

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
// file          : include/CGAL/cartesian_classes.h
// package       : Cartesian_kernel (6.24)
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2000/10/19 15:45:07 $
// authors       : Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_CLASSES_H
#define CGAL_CARTESIAN_CLASSES_H

CGAL_BEGIN_NAMESPACE

#ifdef CGAL_CFG_NO_ADVANCED_KERNEL

// The following scheme is proposed by Stefan Schirra
// It does not use partial specialization
// It is a partially extendible kernel, but you have to redefine and
// reinstantiate all the member classes in a new kernel
// even if only one differs

template < class R > class PointC2;
template < class R > class VectorC2;
template < class R > class DirectionC2;
template < class R > class LineC2;
template < class R > class RayC2;
template < class R > class SegmentC2;
template < class R > class TriangleC2;
template < class R > class CircleC2;
template < class R > class Data_accessorC2;
template < class PT, class DA > class ConicCPA2;
template < class R > class Iso_rectangleC2;
template < class R > class Aff_transformationC2;

template < class R > class PlaneC3;
template < class R > class PointC3;
template < class R > class VectorC3;
template < class R > class DirectionC3;
template < class R > class LineC3;
template < class R > class RayC3;
template < class R > class SegmentC3;
template < class R > class TriangleC3;
template < class R > class TetrahedronC3;
template < class R > class Iso_cuboidC3;
template < class R > class SphereC3;
template < class R > class Aff_transformationC3;

template < class R > class PointCd;

#endif // CGAL_CFG_NO_ADVANCED_KERNEL

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_CLASSES_H
