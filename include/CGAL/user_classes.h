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
// file          : include/CGAL/user_classes.h
// package       : Kernel_basic (3.53)
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2001/06/19 06:47:55 $
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
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
class Circle_2;

template < class R >
class Aff_transformation_base_2;

template < class R >
class Aff_transformation_2;

template < class R >
class Aff_transformation_3;

template < class R >
class Plane_3;

template < class R >
class Point_3;

template < class R >
class Vector_3;

template < class R >
class Direction_3;

template < class R >
class Line_3;

template < class R >
class Ray_3;

template < class R >
class Segment_3;

template < class R >
class Triangle_3;

template < class R >
class Tetrahedron_3;

template < class R >
class Iso_cuboid_3;

template < class R >
class Sphere_3;

CGAL_END_NAMESPACE

#include <CGAL/Point_2.h>
#include <CGAL/Vector_2.h>
#include <CGAL/Direction_2.h>
#include <CGAL/Line_2.h>
#include <CGAL/Ray_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Iso_rectangle_2.h>
#include <CGAL/Circle_2.h>
#include <CGAL/Aff_transformation_2.h>

#include <CGAL/Point_3.h>
#include <CGAL/Plane_3.h>
#include <CGAL/Vector_3.h>
#include <CGAL/Direction_3.h>
#include <CGAL/Line_3.h>
#include <CGAL/Ray_3.h>
#include <CGAL/Segment_3.h>
#include <CGAL/Triangle_3.h>
#include <CGAL/Tetrahedron_3.h>
#include <CGAL/Iso_cuboid_3.h>
#include <CGAL/Sphere_3.h>
#include <CGAL/Aff_transformation_3.h>

CGAL_BEGIN_NAMESPACE

template < class R>
class Point_d;

CGAL_END_NAMESPACE

#endif  // CGAL_USER_CLASSES_H
