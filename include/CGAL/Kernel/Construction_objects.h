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
// file          : include/CGAL/Kernel/Construction_objects.h
// package       : Cartesian_basic (3.3.7)
// revision      : $Revision: 1.3 $
// revision_date : $Date: 1999/11/22 13:44:12 $
// author(s)     : Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_KERNEL_CONSTRUCTION_OBJECTS_H
#define CGAL_KERNEL_CONSTRUCTION_OBJECTS_H

#include <CGAL/Kernel/Construction_objects_2.h>
#include <CGAL/Kernel/Construction_objects_3.h>

CGAL_BEGIN_NAMESPACE

template < class R >
class Kernel_construction_objects
{
public:
typedef typename R::FT                      FT;
typedef typename R::RT                      RT;
typedef typename R::Point_2                 Point_2;
typedef typename R::Vector_2                Vector_2;
typedef typename R::Direction_2             Direction_2;
typedef typename R::Segment_2               Segment_2;
typedef typename R::Line_2                  Line_2;
typedef typename R::Ray_2                   Ray_2;
typedef typename R::Triangle_2              Triangle_2;
typedef typename R::Circle_2                Circle_2;
typedef typename R::Iso_rectangle_2         Iso_rectangle_2;
typedef typename R::Aff_transformation_2    Aff_transformation_2;

CGAL_UNPACK_KERNEL_CONSTRUCTION_OBJECTS_2(typename Kernel_construction_objects_2<R>)
CGAL_UNPACK_KERNEL_CONSTRUCTION_OBJECTS_3(typename Kernel_construction_objects_3<R>)
};

CGAL_END_NAMESPACE

// This macro is provided for convenience in defining the Kernel
// function objects inside a new representation class.
// See Cartesian_2.h and Cartesian.h

#define CGAL_UNPACK_KERNEL_CONSTRUCTION_OBJECTS(CO) \
CGAL_UNPACK_KERNEL_CONSTRUCTION_OBJECTS_2(CO) \
CGAL_UNPACK_KERNEL_CONSTRUCTION_OBJECTS_3(CO)

#endif // CGAL_KERNEL_CONSTRUCTION_OBJECTS_2_H
