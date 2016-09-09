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
// file          : include/CGAL/Weighted_alpha_shape_euclidean_traits_2.h
// package       : Alpha_shapes_2 (8.3)
// source        : $RCSfile: Weighted_alpha_shape_euclidean_traits_2.h,v $
// revision      : $Revision: 1.7 $
// revision_date : $Date: 2000/07/11 16:16:06 $
// author(s)     : Tran Kai Frank DA
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_WEIGHTED_ALPHA_SHAPE_EUCLIDEAN_TRAITS_H
#define CGAL_WEIGHTED_ALPHA_SHAPE_EUCLIDEAN_TRAITS_H

#include <CGAL/basic.h>
#include <CGAL/Cartesian.h>

//#include <CGAL/Homogeneous.h>
//#include <CGAL/Integer.h>
//#include <CGAL/Rational.h>
//#include <CGAL/Fixed.h>

#include <CGAL/squared_distance_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Segment_2.h>

#include <CGAL/in_smallest_orthogonalcircleC2.h>
#include <CGAL/squared_radius_smallest_orthogonalcircleC2.h>

#include <CGAL/Regular_triangulation_euclidean_traits_2.h>

//-------------------------------------------------------------------
CGAL_BEGIN_NAMESPACE
//-------------------------------------------------------------------

//------------------ Traits class -------------------------------------

template< class R >
class Weighted_alpha_shape_euclidean_traits_2 : public
Regular_triangulation_euclidean_traits_2<R, typename R::FT> 
{

public: 
  
  typedef typename R::FT Coord_type;
  typedef typename 
   Regular_triangulation_euclidean_traits_2<R, typename R::FT>::Weighted_point 
     Point;

  //---------------------------------------------------------------------

  Coord_type squared_radius(const Point &p,
			    const Point &q,
			    const Point &r) const 
    {
  
      return
	std::max
	(Coord_type(0), CGAL::squared_radius_orthogonalcircle(p, q, r));
    }




  Coord_type squared_radius(const Point &p,
			    const Point &q) const 
    {

      return
	std::max
	(Coord_type(0), CGAL::squared_radius_smallest_orthogonalcircle(p, q));
    }

  Bounded_side side_of_circle(const Point &p,
			      const Point &q,
			      const Point &t) const 
    {
  
      return
	CGAL::in_smallest_orthogonalcircle(p, q, t);
    }

};
  
//-------------------------------------------------------------------
CGAL_END_NAMESPACE
//-------------------------------------------------------------------

#endif
