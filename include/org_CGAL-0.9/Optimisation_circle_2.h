/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/


// file  : include/CGAL/Optimisation_circle_2.h
// author: Sven Schönherr 

#ifndef CGAL_OPTIMISATION_CIRCLE_2_H
#define CGAL_OPTIMISATION_CIRCLE_2_H

// Class declaration
// =================
template < class _R >
class CGAL_Optimisation_circle_2;

// Class interface and implementation
// ==================================
// includes
#ifndef CGAL_POINT_2_H
#  include <CGAL/Point_2.h>
#endif
#ifndef CGAL_BASIC_CONSTRUCTIONS_2_H
#  include <CGAL/basic_constructions_2.h>
#endif
#ifndef CGAL_SQUARED_DISTANCE_2_H
#  include <CGAL/squared_distance_2.h>
#endif

template < class _R >
class CGAL_Optimisation_circle_2 {
  public:
    // types
    typedef           _R               R;
    typedef           CGAL_Point_2<R>  Point;
    typedef typename  _R::FT           Distance;

  private:
    // data members
    Point     _center;
    Distance  _squared_radius;

  public:
    // creation
    CGAL_Optimisation_circle_2( ) { }
    
    void  set( )
    {
	_center         =  Point( CGAL_ORIGIN);
	_squared_radius = -Distance( 1);
    }
    
    void  set( Point const& p)
    {
	_center         = p;
	_squared_radius = Distance( 0);
    }
    
    void  set( Point const& p, Point const& q)
    {
	_center         = CGAL_midpoint( p, q);
	_squared_radius = CGAL_squared_distance( p, _center);
    }
    
    void  set( Point const& p, Point const& q, Point const& r)
    {
	_center         = CGAL_circumcenter( p, q, r);
	_squared_radius = CGAL_squared_distance( p, _center);
    }
    
    void  set( Point const& center, Distance const& squared_radius)
    {
	_center         = center;
	_squared_radius = squared_radius;
    }
    
    // predicates
    CGAL_Bounded_side
    bounded_side( Point const& p) const
    {
	return( CGAL_static_cast( CGAL_Bounded_side,
				  CGAL_sign( CGAL_squared_distance( p, _center)
					     - _squared_radius)));
    }
    
    bool
    has_on_bounded_side( Point const& p) const
    {
	return( CGAL_squared_distance( p, _center) < _squared_radius);
    }
    
    bool
    has_on_boundary( Point const& p) const
    {
	return( CGAL_squared_distance( p, _center) == _squared_radius);
    }
    
    bool
    has_on_unbounded_side( Point const& p) const
    {
	return( _squared_radius < CGAL_squared_distance( p, _center));
    }
    
    bool
    is_empty( ) const
    {
	return( CGAL_is_negative( _squared_radius));
    }
    
    bool
    is_degenerate( ) const
    {
	return( ! CGAL_is_positive( _squared_radius));
    }
    
    // additional operations for checking
    bool
    operator == ( CGAL_Optimisation_circle_2<R> const& c) const
    {
	return( ( _center          == c._center        ) &&
		( _squared_radius  == c._squared_radius) );
    }
    
    Point const&
    center( ) const
    {
	return( _center);
    }
    
    Distance const&
    squared_radius( ) const
    {
	return( _squared_radius);
    }
};

// Function declarations
// =====================
// I/O
// ---
template < class R >
ostream& operator << ( ostream& os, CGAL_Optimisation_circle_2<R> const& c);

template < class R >
istream& operator >> ( istream& is, CGAL_Optimisation_circle_2<R>      & c);


#ifdef CGAL_INCLUDE_TEMPLATE_CODE
#  include <CGAL/Optimisation_circle_2.C>
#endif

#endif // CGAL_OPTIMISATION_CIRCLE_2_H

// ===== EOF ==================================================================
