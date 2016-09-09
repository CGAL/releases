// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/Pm_advanced_point_location_base.h
// package       : Planar_map (5.73)
// source        : 
// revision      : 
// revision_date : 
// author(s)     : Iddo Hanniel
//                 Oren Nechushtan
//
//
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// Chapter       : 
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_PM_ADVANCED_POINT_LOCATION_BASE_H
#define CGAL_PM_ADVANCED_POINT_LOCATION_BASE_H

#ifndef CGAL_PM_BOUNDING_BOX_BASE_H
#include <CGAL/Pm_bounding_box_base.h>
#endif

CGAL_BEGIN_NAMESPACE


////////////////////////////////////////////////////////////////////
//               ABSTRACT BASE CLASS OF STRATEGY
//////////////////////////////////////////////////////////////////

template <class _Planar_map>
class Pm_advanced_point_location_base : 
	public Pm_advanced_point_location_base<_Planar_map>{
public:
	typedef _Planar_map Planar_map;
	typedef typename Planar_map::Traits Traits;
	typedef typename Planar_map::Locate_type Locate_type;
	typedef typename Planar_map::Ccb_halfedge_circulator 
		Ccb_halfedge_circulator;
	typedef typename Planar_map::Halfedge_handle Halfedge_handle;
	typedef typename Planar_map::Halfedge Halfedge;
	typedef typename Traits::X_curve X_curve;
	typedef typename Traits::Point Point;
	typedef Pm_bounding_box_base<Planar_map> Bounding_box;
	
	Pm_advanced_point_location_base():Pm_point_location_base {}
	
	virtual Halfedge_handle ray_shoot(const Point& p, 
					  Locate_type& lt, 
					  const X_curve&) = 0;
	virtual Halfedge_handle x_curve_shoot(const Point& p, 
					      Locate_type& lt, 
					      const Ray&) = 0;
	
};


CGAL_END_NAMESPACE

#endif //CGAL_PM_ADVANCED_POINT_LOCATION_BASE_H














