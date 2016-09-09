// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// file          : include/CGAL/Polyhedron_old/Polyhedron_default_traits_3.h
// package       : Polyhedron (3.21)
// chapter       : $CGAL_Chapter: 3D-Polyhedral Surfaces $
// source        : polyhedron.fw
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2001/07/05 21:09:50 $
// author(s)     : Lutz Kettner
//
// coordinator   : MPI Saarbruecken (Stefan Schirra)
//
// Default Traits for Polyhedral Surfaces in CGAL.
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_POLYHEDRON_OLD_POLYHEDRON_DEFAULT_TRAITS_3_H
#define CGAL_POLYHEDRON_OLD_POLYHEDRON_DEFAULT_TRAITS_3_H 1

#include <CGAL/basic.h>

CGAL_BEGIN_NAMESPACE

template < class Kernel_ >
class Polyhedron_default_traits_3 {
public:
    typedef Kernel_                    Kernel;
    // typedef Kernel            R;  // maybe for backwards compatibility
    typedef typename Kernel::Point_3   Point_3;
    typedef typename Kernel::Vector_3  Vector_3;
    typedef typename Kernel::Plane_3   Plane_3;
    typedef typename Kernel::Construct_opposite_vector_3 
                                       Construct_opposite_vector_3;
    typedef typename Kernel::Construct_opposite_plane_3 
                                       Construct_opposite_plane_3;
private:
    Kernel m_kernel;

public:
    Polyhedron_default_traits_3() {}
    Polyhedron_default_traits_3( const Kernel& kernel) : m_kernel(kernel) {}

    Construct_opposite_vector_3 construct_opposite_vector_3_object() const {
        return m_kernel.construct_opposite_vector_3_object();
    }
    Construct_opposite_plane_3  construct_opposite_plane_3_object()  const {
        return m_kernel.construct_opposite_plane_3_object();
    }
};

CGAL_END_NAMESPACE
#endif // CGAL_POLYHEDRON_OLD_POLYHEDRON_DEFAULT_TRAITS_3_H //
// EOF //
