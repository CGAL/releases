// ======================================================================
//
// Copyright (c) 1997-2001 The CGAL Consortium

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
// file          : include/CGAL/Optimisation_d_traits_d.h
// package       : Optimisation_basic (3.8.14)
// chapter       : Geometric Optimisation
//
// source        : web/Optimisation_d_traits.aw
// revision      : $Revision: 1.5 $
// revision_date : $Date: 2002/03/18 15:07:49 $
//
// author(s)     : Sven Schönherr
// coordinator   : ETH Zürich (Bernd Gärtner)
//
// implementation: Traits class (dD) for dD optimisation algorithms
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_OPTIMISATION_D_TRAITS_D_H
#define CGAL_OPTIMISATION_D_TRAITS_D_H

// includes
#ifndef CGAL_OPTIMISATION_ACCESS_DIMENSION_D_H
#  include <CGAL/Optimisation/Access_dimension_d.h>
#endif
#ifndef CGAL_OPTIMISATION_ACCESS_COORDINATES_BEGIN_D_H
#  include <CGAL/Optimisation/Access_coordinates_begin_d.h>
#endif
#ifndef CGAL_OPTIMISATION_CONSTRUCT_POINT_D_H
#  include <CGAL/Optimisation/Construct_point_d.h>
#endif

CGAL_BEGIN_NAMESPACE

// Class declaration
// =================
template < class K_, class ET_ = CGAL_TYPENAME_MSVC_NULL K_::RT,
                     class NT_ = CGAL_TYPENAME_MSVC_NULL K_::RT >
class Optimisation_d_traits_d;

// Class interface
// ===============
template < class K_, class ET_, class NT_>
class Optimisation_d_traits_d {
  public:
    // self
    typedef  K_                         K;
    typedef  ET_                        ET;
    typedef  NT_                        NT;
    typedef  Optimisation_d_traits_d<K,ET,NT>
                                        Self;

    // types
    typedef  typename K::Point_d        Point_d;

    typedef  typename K::Rep_tag        Rep_tag;

    typedef  typename K::RT             RT;
    typedef  typename K::FT             FT;

    typedef  CGAL::Access_dimension_d<K>      Access_dimension_d;
    typedef  CGAL::Access_coordinates_begin_d<K>
                                        Access_coordinates_begin_d;

    typedef  CGAL::Construct_point_d<K>       Construct_point_d;

    // creation
    Optimisation_d_traits_d( ) { }
    Optimisation_d_traits_d( const Optimisation_d_traits_d<K_,ET_,NT_>&) {}

    // operations
    Access_dimension_d
    access_dimension_d_object( ) const
        { return Access_dimension_d(); }

    Access_coordinates_begin_d
    access_coordinates_begin_d_object( ) const
        { return Access_coordinates_begin_d(); }

    Construct_point_d
    construct_point_d_object( ) const
        { return Construct_point_d(); }
};

CGAL_END_NAMESPACE

#endif // CGAL_OPTIMISATION_D_TRAITS_D_H

// ===== EOF ==================================================================
