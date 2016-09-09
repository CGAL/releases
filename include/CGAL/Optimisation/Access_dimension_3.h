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
// file          : include/CGAL/Optimisation/Access_dimension_3.h
// package       : Optimisation_basic (3.8.2)
// maintainer    : Sven Sch�nherr <sven@inf.ethz.ch>
//
// revision      : $Revision: 1.1 $
// revision_date : $Date: 2000/09/05 17:06:42 $
//
// author(s)     : Sven Sch�nherr
// coordinator   : ETH Z�rich (Bernd G�rtner <gaertner@inf.ethz.ch>)
//
// implementation: 3D data accessor `dimension'
// ======================================================================

#ifndef CGAL_OPTIMISATION_ACCESS_DIMENSION_3_H
#define CGAL_OPTIMISATION_ACCESS_DIMENSION_3_H

CGAL_BEGIN_NAMESPACE

// Class declaration
// =================
template < class R_ >
class Access_dimension_3;

// Class interface
// ===============
template < class R_ >
class Access_dimension_3 {
  public:
    // self
    typedef  R_                         R;
    typedef  Access_dimension_3<R>      Self;

    // types
    typedef  typename R::Point_3        Point;

    // unary function class types
    typedef  int                        result_type;
    typedef  Point                      argument_type;

    // creation
    Access_dimension_3( ) { }

    // operations
    int  operator() ( const Point& p) const { return p.dimension(); }
};

CGAL_END_NAMESPACE

#endif // CGAL_OPTIMISATION_ACCESS_DIMENSION_3_H

// ===== EOF ==================================================================