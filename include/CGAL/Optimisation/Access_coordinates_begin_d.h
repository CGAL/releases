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
// file          : include/CGAL/Optimisation/Access_coordinates_begin_d.h
// package       : Optimisation_basic (3.8.2)
// maintainer    : Sven Sch�nherr <sven@inf.ethz.ch>
//
// revision      : $Revision: 1.1 $
// revision_date : $Date: 2000/09/05 17:06:41 $
//
// author(s)     : Sven Sch�nherr
// coordinator   : ETH Z�rich (Bernd G�rtner <gaertner@inf.ethz.ch>)
//
// implementation: dD data accessor `coordinates'
// ======================================================================

#ifndef CGAL_OPTIMISATION_ACCESS_COORDINATES_BEGIN_D_H
#define CGAL_OPTIMISATION_ACCESS_COORDINATES_BEGIN_D_H

// includes
#ifndef CGAL_POINT_D_H
#  include <CGAL/Point_d.h>
#endif

CGAL_BEGIN_NAMESPACE

// Class declaration
// =================
template < class R_ >
class Access_coordinates_begin_d;

// Class interface
// ===============
template < class R_ >
class Access_coordinates_begin_d {
  public:
    // self
    typedef  R_                         R;
    typedef  Access_coordinates_begin_d<R>
                                        Self;

    // types
    typedef  typename R::Point_d        Point;
    typedef  const typename R::RT *     Coordinate_iterator;

    // unary function class types
    typedef  Coordinate_iterator        result_type;
    typedef  Point                      argument_type;

    // creation
    Access_coordinates_begin_d( ) { }

    // operations
    Coordinate_iterator
    operator() ( const Point& p) const { return p.begin(); }
};

CGAL_END_NAMESPACE

#endif // CGAL_OPTIMISATION_ACCESS_COORDINATES_BEGIN_D_H

// ===== EOF ==================================================================
