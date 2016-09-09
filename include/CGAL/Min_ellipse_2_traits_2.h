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
// file          : include/CGAL/Min_ellipse_2_traits_2.h
// package       : Min_ellipse_2 (3.10.2)
// maintainer    : Sven Schönherr <sven@inf.ethz.ch>
// chapter       : $CGAL_Chapter: Geometric Optimisation $
//
// source        : web/Optimisation/Min_ellipse_2.aw
// revision      : $Revision: 5.29 $
// revision_date : $Date: 2000/09/18 09:57:06 $
//
// author(s)     : Sven Schönherr, Bernd Gärtner
// coordinator   : ETH Zürich (Bernd Gärtner <gaertner@inf.ethz.ch>)
//
// implementation: default traits class for 2D Smallest Enclosing Ellipse
// ======================================================================

#ifndef CGAL_MIN_ELLIPSE_2_TRAITS_2_H
#define CGAL_MIN_ELLIPSE_2_TRAITS_2_H

// includes
#ifndef CGAL_POINT_2_H
#  include <CGAL/Point_2.h>
#endif
#ifndef CGAL_OPTIMISATION_ELLIPSE_2_H
#  include <CGAL/Optimisation_ellipse_2.h>
#endif

CGAL_BEGIN_NAMESPACE

// Class declarations
// ==================
template < class _Traits >
class Min_ellipse_2;

template < class _R >
class Min_ellipse_2_traits_2;

// Class interface and implementation
// ==================================
template < class _R >
class Min_ellipse_2_traits_2 {
  public:
    // types
    typedef  _R                               R;
    typedef  CGAL::Point_2<R>                 Point;
    typedef  CGAL::Optimisation_ellipse_2<R>  Ellipse;

private:
    // data members
    Ellipse  ellipse;                                // current ellipse

    // friends
    friend  class CGAL::Min_ellipse_2< CGAL::Min_ellipse_2_traits_2< R > >;

  public:
    // creation (use default implementations)
    // Min_ellipse_2_traits_2( );
    // Min_ellipse_2_traits_2( Min_ellipse_2_traits_2<R> const&);
};

CGAL_END_NAMESPACE

#endif // CGAL_MIN_ELLIPSE_2_TRAITS_2_H

// ===== EOF ==================================================================
