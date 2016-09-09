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
// file          : include/CGAL/cartesian_classes.h
// package       : Cartesian_basic (2.1)
// source        : web/Cartesian.fw
// revision      : $Revision: 1.2 $
// revision_date : $Date: 1999/02/28 09:20:04 $
// author(s)     : Andreas.Fabri
//
// coordinator   : INRIA Sophia-Antipolis
// (Herve.Bronnimann)
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_CARTESIAN_CLASSES_H
#define CGAL_CARTESIAN_CLASSES_H

#ifndef CGAL_BASIC_CLASSES_H
#include <CGAL/basic_classes.h>
#endif // CGAL_BASIC_CLASSES_H

CGAL_BEGIN_NAMESPACE

template < class FT > class PointC2;
template < class FT > class VectorC2;
template < class FT > class DirectionC2;
template < class FT > class LineC2;
template < class FT > class RayC2;
template < class FT > class SegmentC2;
template < class FT > class TriangleC2;
template < class FT > class CircleC2;
template < class FT > class ParabolaC2;
template < class FT > class Parabola_arcC2;
template < class PT, class DA > class ConicCPA2;
template < class FT > class Iso_rectangleC2;
template < class FT > class Iso_rectangleC3;
template < class FT > class Aff_transformation_baseC2;
template < class R > class Aff_transformation_base_2;
template < class FT > class Aff_transformationC2;

template < class FT > class PlaneC3;
template < class FT > class PointC3;
template < class FT > class VectorC3;
template < class FT > class DirectionC3;
template < class FT > class LineC3;
template < class FT > class RayC3;
template < class FT > class SegmentC3;
template < class FT > class TriangleC3;
template < class FT > class TetrahedronC3;
template < class FT > class Aff_transformationC3;

template < class FT > class PointCd;

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_CLASSES_H
