// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/Min_circle_2_traits_2.h
// package       : Min_circle_2 (3.2.3)
// chapter       : $CGAL_Chapter: Geometric Optimisation $
//
// source        : web/Optimisation/Min_circle_2.aw
// revision      : $Revision: 5.8 $
// revision_date : $Date: 1999/04/19 16:20:38 $
// author(s)     : Sven Schönherr
//                 Bernd Gärtner
//
// coordinator   : ETH Zürich (Bernd Gärtner)
//
// implementation: default traits class for 2D Smallest Enclosing Circle
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_MIN_CIRCLE_2_TRAITS_2_H
#define CGAL_MIN_CIRCLE_2_TRAITS_2_H

// includes
#ifndef CGAL_POINT_2_H
#  include <CGAL/Point_2.h>
#endif
#ifndef CGAL_OPTIMISATION_CIRCLE_2_H
#  include <CGAL/Optimisation_circle_2.h>
#endif
#ifndef CGAL_PREDICATES_ON_POINTS_2_H
#  include <CGAL/predicates_on_points_2.h>
#endif

CGAL_BEGIN_NAMESPACE

// Class declarations
// ==================
template < class _Traits >
class Min_circle_2;

template < class _R >
class Min_circle_2_traits_2;

// Class interface and implementation
// ==================================
template < class _R >
class Min_circle_2_traits_2 {
  public:
    // types
    typedef  _R                              R;
    typedef  CGAL::Point_2<R>                Point;
    typedef  CGAL::Optimisation_circle_2<R>  Circle;

private:
    // data members
    Circle  circle;                                 // current circle

    // friends
    friend  class CGAL::Min_circle_2< CGAL::Min_circle_2_traits_2< R > >;

  public:
    // creation (use default implementations)
    // CGAL::Min_circle_2_traits_2( );
    // CGAL::Min_circle_2_traits_2( CGAL::Min_circle_2_traits_2<R> const&);

    // operations
    inline
    CGAL::Orientation
    orientation( const Point& p, const Point& q, const Point& r) const
    {
        return( CGAL::orientation( p, q, r));
    }
};

CGAL_END_NAMESPACE

#endif // CGAL_MIN_CIRCLE_2_TRAITS_2_H

// ===== EOF ==================================================================
