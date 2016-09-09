// ============================================================================
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
// release       : CGAL-2.2
// release_date  : 2000, September 30
// 
// source        : advanced_user_classes.fw
// file          : user_classes.h
// revision      : 3.4
// revision_date : 07 Apr 2000 
// author(s)     : Herve Broennimann
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_USER_CLASSES_H
#define CGAL_USER_CLASSES_H

namespace CGAL {
/* 2D */
template < class R, class T = typename R::Rep_tag > class Point_2;
template < class R, class T = typename R::Rep_tag > class Vector_2;
template < class R, class T = typename R::Rep_tag > class Direction_2;
template < class R, class T = typename R::Rep_tag > class Line_2;
template < class R, class T = typename R::Rep_tag > class Ray_2;
template < class R, class T = typename R::Rep_tag > class Segment_2;
template < class R, class T = typename R::Rep_tag > class Triangle_2;
template < class R, class T = typename R::Rep_tag > class Circle_2;
template < class R, class T = typename R::Rep_tag > class Data_accessor_2;
template < class R, class T = typename R::Rep_tag > class Iso_rectangle_2;
template < class R, class T = typename R::Rep_tag > class Aff_transformation_2;

/* 3D */
template < class R, class T = typename R::Rep_tag > class Plane_3;
template < class R, class T = typename R::Rep_tag > class Point_3;
template < class R, class T = typename R::Rep_tag > class Vector_3;
template < class R, class T = typename R::Rep_tag > class Direction_3;
template < class R, class T = typename R::Rep_tag > class Line_3;
template < class R, class T = typename R::Rep_tag > class Ray_3;
template < class R, class T = typename R::Rep_tag > class Segment_3;
template < class R, class T = typename R::Rep_tag > class Triangle_3;
template < class R, class T = typename R::Rep_tag > class Tetrahedron_3;
template < class R, class T = typename R::Rep_tag > class Iso_cuboid_3;
template < class R, class T = typename R::Rep_tag > class Aff_transformation_3;

/* dD */
template < class R> class Point_d;

inline
bool
advanced_kernel_enabled()
{
#ifndef CGAL_CFG_NO_ADVANCED_KERNEL
  return true;
#else
  return false;
#endif // CGAL_CFG_NO_ADVANCED_KERNEL
}

} // namespace CGAL
#endif // CGAL_USER_CLASSES_H
