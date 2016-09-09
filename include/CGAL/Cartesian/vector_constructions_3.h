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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/Cartesian/vector_constructions_3.h
// package       : Cartesian_kernel (6.59)
// revision      : $Revision: 1.6 $
// revision_date : $Date: 2002/01/28 13:25:22 $
// author(s)     : Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_VECTOR_CONSTRUCTIONS_3_H
#define CGAL_CARTESIAN_VECTOR_CONSTRUCTIONS_3_H

#include <CGAL/Cartesian/Vector_3.h>
#include <CGAL/constructions/kernel_ftC3.h>

CGAL_BEGIN_NAMESPACE

template < class R >
typename R::Vector_3
cross_product(const VectorC3<R> &v, const VectorC3<R> &w)
{
    return VectorC3<R>(v.y() * w.z() - v.z() * w.y(),
                       v.z() * w.x() - v.x() * w.z(),
                       v.x() * w.y() - v.y() * w.x());
}

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_VECTOR_CONSTRUCTIONS_3_H
