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
// file          : include/CGAL/Polyhedron_default_traits_3.h
// package       : Polyhedron (3.21)
// chapter       : $CGAL_Chapter: 3D-Polyhedral Surfaces $
// source        : polyhedron.fw
// revision      : $Revision: 1.5 $
// revision_date : $Date: 2001/06/25 08:14:47 $
// author(s)     : Lutz Kettner
//
// coordinator   : MPI Saarbruecken (Stefan Schirra)
//
// Default Traits for Polyhedral Surfaces in CGAL.
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_POLYHEDRON_DEFAULT_TRAITS_3_H
#define CGAL_POLYHEDRON_DEFAULT_TRAITS_3_H 1

#include <CGAL/basic.h>
// MS Visual C++ 6.0 does not work with the new design.
#if defined( _MSC_VER) && (_MSC_VER <= 1200)
#ifndef CGAL_USE_POLYHEDRON_DESIGN_TWO
#define CGAL_USE_POLYHEDRON_DESIGN_ONE 1
#endif
#endif

#ifdef CGAL_USE_POLYHEDRON_DESIGN_ONE
#include <CGAL/Polyhedron_old/Polyhedron_default_traits_3.h>
#else // CGAL_USE_POLYHEDRON_DESIGN_ONE //
#define CGAL_USE_POLYHEDRON_DESIGN_TWO 1

// Use renamed traits class and provide derived class for backwards
// compatibility.

#include <CGAL/Polyhedron_traits_3.h>

CGAL_BEGIN_NAMESPACE

template < class Kernel_ >
class Polyhedron_default_traits_3 : public Polyhedron_traits_3<Kernel_> {
public:
    typedef Kernel_ Kernel;
    Polyhedron_default_traits_3() {}
    Polyhedron_default_traits_3( const Kernel& kernel) 
        : Polyhedron_traits_3<Kernel>(kernel) {}
};

CGAL_END_NAMESPACE

#endif // CGAL_USE_POLYHEDRON_DESIGN_ONE //
#endif // CGAL_POLYHEDRON_DEFAULT_TRAITS_3_H //
// EOF //


