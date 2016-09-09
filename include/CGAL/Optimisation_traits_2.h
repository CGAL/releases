// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/Optimisation_traits_2.h
// author(s)     : Sven Schönherr 
//
// email         : cgal@cs.uu.nl
//
// ============================================================================

#ifndef CGAL_OPTIMISATION_TRAITS_2_H
#define CGAL_OPTIMISATION_TRAITS_2_H

// Class declarations
// ==================
template < class _R >
class CGAL_Optimisation_traits_2;
                     
template < class _Traits >
class CGAL_Min_circle_2;
   
template < class _Traits >
class CGAL_Min_ellipse_2;
   
// Class interface and implementation
// ==================================
// includes
#ifndef CGAL_POINT_2_H
#  include <CGAL/Point_2.h>
#endif
#ifndef CGAL_OPTIMISATION_CIRCLE_2_H
#  include <CGAL/Optimisation_circle_2.h>
#endif
#ifndef CGAL_OPTIMISATION_ELLIPSE_2_H
#  include <CGAL/Optimisation_ellipse_2.h>
#endif
#ifndef CGAL_PREDICATES_ON_POINTS_2_H
#  include <CGAL/predicates_on_points_2.h>
#endif

template < class _R >
class CGAL_Optimisation_traits_2 {
  public:
    // types
    typedef  _R                              R;
    typedef  CGAL_Point_2<R>                 Point;
    typedef  CGAL_Optimisation_circle_2<R>   Circle;
    typedef  CGAL_Optimisation_ellipse_2<R>  Ellipse;

  private:
    // data members
    Circle   circle;
    Ellipse  ellipse;

    // friends
    friend class CGAL_Min_circle_2 < CGAL_Optimisation_traits_2< R > >;
    friend class CGAL_Min_ellipse_2< CGAL_Optimisation_traits_2< R > >;

  public:
    // creation (use default implementations)
    // CGAL_Optimisation_traits_2( );
    // CGAL_Optimisation_traits_2( CGAL_Optimisation_traits_2<R> const&);
    
    // operations
    inline
    CGAL_Orientation
    orientation( Point const& p, Point const& q, Point const& r) const
    {
	return( CGAL_orientation( p, q, r));
    }
};

#endif // CGAL_OPTIMISATION_TRAITS_2_H

// ===== EOF ==================================================================
