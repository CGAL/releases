// ======================================================================
//
// Copyright (c) 1997-2000 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------
//
// release       : $CGAL_Revision: CGAL-2.2-I-51 $
// release_date  : $CGAL_Date: 2000/10/01 $
//
// file          : include/CGAL/Optimisation_d_traits_3.h
// package       : Optimisation_basic (3.8.2)
// maintainer    : Sven Sch�nherr <sven@inf.ethz.ch>
// chapter       : $CGAL_Chapter: Geometric Optimisation $
//
// source        : web/Optimisation_d_traits.aw
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2000/09/26 10:47:49 $
//
// author(s)     : Sven Sch�nherr
// coordinator   : ETH Z�rich (Bernd G�rtner <gaertner@inf.ethz.ch>)
//
// implementation: Traits class (3D) for dD optimisation algorithms
// ======================================================================

#ifndef CGAL_OPTIMISATION_D_TRAITS_3_H
#define CGAL_OPTIMISATION_D_TRAITS_3_H

// includes
#ifndef CGAL_OPTIMISATION_ACCESS_DIMENSION_3_H
#  include <CGAL/Optimisation/Access_dimension_3.h>
#endif
#ifndef CGAL_OPTIMISATION_ACCESS_COORDINATES_BEGIN_3_H
#  include <CGAL/Optimisation/Access_coordinates_begin_3.h>
#endif
#ifndef CGAL_OPTIMISATION_CONSTRUCT_POINT_3_H
#  include <CGAL/Optimisation/Construct_point_3.h>
#endif

CGAL_BEGIN_NAMESPACE

// Class declaration
// =================
template < class R_, class ET_ = CGAL_TYPENAME_MSVC_NULL R_::RT,
                     class NT_ = CGAL_TYPENAME_MSVC_NULL R_::RT >
class Optimisation_d_traits_3;

// Class interface
// ===============
template < class R_, class ET_, class NT_>
class Optimisation_d_traits_3 {
  public:
    // self
    typedef  R_                         R;
    typedef  ET_                        ET;
    typedef  NT_                        NT;
    typedef  Optimisation_d_traits_3<R,ET,NT>
                                        Self;

    // types
    typedef  typename R::Point_3        Point_d;

    typedef  typename R::Rep_tag        Rep_tag;

    typedef  typename R::RT             RT;
    typedef  typename R::FT             FT;

    typedef  Access_dimension_3<R>      Access_dimension_d;
    typedef  Access_coordinates_begin_3<R>
                                        Access_coordinates_begin_d;

    typedef  Construct_point_3<R>       Construct_point_d;

    // creation
    Optimisation_d_traits_3( ) { }
    Optimisation_d_traits_3( const Optimisation_d_traits_3<R_,ET_,NT_>&) {}

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

#endif // CGAL_OPTIMISATION_D_TRAITS_3_H

// ===== EOF ==================================================================
