// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/Pm_default_point_location.C
// package       : pm (5.43)
// source        : 
// revision      : 
// revision_date : 
// author(s)     : Oren Nechushtan
//
//
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// Chapter       : 
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_PM_DEFAULT_POINT_LOCATION_C
#define CGAL_PM_DEFAULT_POINT_LOCATION_C

#ifndef CGAL_PM_DEFAULT_POINT_LOCATION_H
#include <CGAL/Pm_default_point_location.h>
#endif // CGAL_PM_DEFAULT_POINT_LOCATION_H

CGAL_BEGIN_NAMESPACE

//IMPLEMENTATION
//if unbounded face - returns NULL or some edge on unbounded face 
//if its a vertex returns a halfedge pointing _at_ it
	/* postconditions:
	The output Halfedge_handle represents a 
	planar map subdivision region that contains the 
	input Point in its interior or equal to it.
	The input Locate_type is equal to the type 
	of this region.
	*/
template <class Planar_map>
Pm_default_point_location<Planar_map>::Halfedge_handle
Pm_default_point_location<Planar_map>::locate(const Point& p, Locate_type& lt) const{
		//there are different internal compiler errors if we
		// typedef the Locate_type
		typename TD::Locate_type td_lt; 
		
		const X_curve_plus& cv = td.locate(p,td_lt).top();
		// treat special case, where trapezoid is unbounded.
		//	for then get_parent() is not defined
		if (td_lt==TD::UNBOUNDED_TRAPEZOID)
		{
			lt=PM::UNBOUNDED_FACE;
			return halfedge_representing_unbounded_face();
		}
		Halfedge_handle h = cv.get_parent();
		lt=convert(p,td_lt,h);
		
		return h;
    }

template <class Planar_map>
Pm_default_point_location<Planar_map>::Halfedge_handle
Pm_default_point_location<Planar_map>::locate(const Point& p, Locate_type& lt){
	((Bounding_box*)get_bounding_box())->insert(p);
	Halfedge_handle h=((cPLp)this)->locate(p,lt);
	if (!((Bounding_box*)get_bounding_box())->locate(p,lt,h))
		h=((cPLp)this)->locate(p,lt);
	return h;
}

	/* postconditions:
	The output Halfedge_handle represents a planar map 
	subdivision region that contains the first Point 
	on the closed vertical ray eminating from the input 
	Point in upward or downward direction depending on 
	the input bool in its interior or equal to it.
	The input Locate_type is equal to the type 
	of this region.
	*/
template <class Planar_map>
Pm_default_point_location<Planar_map>::Halfedge_handle
Pm_default_point_location<Planar_map>::vertical_ray_shoot(
	const Point& p, Locate_type& lt, bool up) const{

		//trying to workaround internal compiler error
		typename TD::Locate_type td_lt;
		
		X_curve_plus cv = td.vertical_ray_shoot(p,td_lt,up);
		// treat special case, where trapezoid is unbounded.
		//	for then get_parent() is not defined
		if (td_lt==TD::UNBOUNDED_TRAPEZOID)
		{
			lt=PM::UNBOUNDED_FACE;
			return halfedge_representing_unbounded_face();
		}
		Halfedge_handle h=cv.get_parent();
		lt=convert(p,td_lt,h,up);
		
		return h;
    }

template <class Planar_map>
Pm_default_point_location<Planar_map>::Halfedge_handle
Pm_default_point_location<Planar_map>::vertical_ray_shoot(
	const Point& p, Locate_type& lt, bool up){
/* Make sure the source point is in the bounding box on the output */
	((Bounding_box*)get_bounding_box())->insert(p);
	Halfedge_handle h=((cPLp)this)->vertical_ray_shoot(p,lt,up);
/* Apply the bounding box on the output */
	if (!((Bounding_box*)get_bounding_box())->vertical_ray_shoot(p,lt,up,h))
	{
		h=((cPLp)this)->vertical_ray_shoot(p,lt,up);
		CGAL_assertion(lt!=Planar_map::UNBOUNDED_FACE);
	}
	return h;
}

CGAL_END_NAMESPACE

#endif // CGAL_PM_DEFAULT_POINT_LOCATION_C
