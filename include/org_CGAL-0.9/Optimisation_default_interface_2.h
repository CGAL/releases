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


// file  : include/CGAL/Optimisation_default_interface_2.h
// author: Sven Schönherr 
// $Revision: 2.1 $
// $Date: 1997/05/27 13:34:04 $

#ifndef CGAL_OPTIMISATION_DEFAULT_INTERFACE_2_H
#define CGAL_OPTIMISATION_DEFAULT_INTERFACE_2_H

// Class declaration
// =================
template < class R >
class CGAL_Optimisation_default_interface_2;
                        
// Class interface and definition
// ==============================
// includes
#ifndef CGAL_POINT_2_H
#  include <CGAL/Point_2.h>
#endif
#ifndef CGAL_CIRCLE_2_H
#  include <CGAL/Circle_2.h>
#endif
#ifndef CGAL_PREDICATES_ON_POINTS_2_H
#  include <CGAL/predicates_on_points_2.h>
#endif
#ifndef CGAL_SQUARED_DISTANCE_2_H
#  include <CGAL/squared_distance_2.h>
#endif
#ifndef CGAL_BASIC_CONSTRUCTIONS_2_H
#  include <CGAL/basic_constructions_2.h>
#endif

template < class R >
class CGAL_Optimisation_default_interface_2 {
  public:
    // types
    typedef typename  CGAL_Point_2<R>   Point;
    typedef typename  CGAL_Circle_2<R>  Circle;
    typedef typename  R::FT             Distance;
    
    // creation
    CGAL_Optimisation_default_interface_2( ) { }
    
    // operations
    inline
    Distance
    squared_distance( Point const& p, Point const& q) const
    {
	return( CGAL_squared_distance( p, q));
    }

    inline
    Point
    circumcenter( Point const& p, Point const& q, Point const& r) const
    {
	return( CGAL_circumcenter( p, q, r));
    }

    inline
    Point
    midpoint( Point const& p, Point const& q) const
    {
	return( CGAL_midpoint( p, q));
    }

    inline
    CGAL_Orientation
    orientation( Point const& p, Point const& q, Point const& r) const
    {
	return( CGAL_orientation( p, q, r));
    }
};

#endif // CGAL_OPTIMISATION_DEFAULT_INTERFACE_2_H

// ===== EOF ==================================================================
