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
// file          : include/CGAL/Alpha_shape_euclidean_traits_3.h
// package       : Alpha_shapes_3 (3.6)
// source        : $RCSfile: Alpha_shape_euclidean_traits_3.h,v $
// revision      : $Revision: 1.6 $
// revision_date : $Date: 2001/07/11 13:28:04 $
// author(s)     : Tran Kai Frank DA
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_ALPHA_SHAPE_EUCLIDEAN_TRAITS_3_H
#define CGAL_ALPHA_SHAPE_EUCLIDEAN_TRAITS_3_H 

//#include <CGAL/basic.h>


#include <CGAL/squared_distance_3.h>   // to avoid a g++ problem
#include <CGAL/Point_3.h>
#include <CGAL/predicates_on_points_3.h>

#include <CGAL/Triangulation_geom_traits_3.h>

#include <CGAL/smallest_radius_3.h>

//-------------------------------------------------------------------
CGAL_BEGIN_NAMESPACE
//-------------------------------------------------------------------

//------------------ Function Objects ---------------------------------

template < class return_type, class T >
class Compute_squared_radius_circumsphere_3
{
public:

  typedef return_type result_type;

  result_type operator()(const T& p, const T& q, const T& r, const T& s)
    { 
      return CGAL::squared_radius(p, q, r, s);
    }

  result_type operator()(const T& p, const T& q, const T& r)
    { 
      return CGAL::squared_radius(p, q, r);
    }

  result_type operator()(const T& p, const T& q)
    { 
      return CGAL::squared_radius_smallest_circumsphere(p, q);
    }
};

//------------------ Traits class -------------------------------------

template <class R>
class Alpha_shape_euclidean_traits_3 : public Triangulation_geom_traits_3<R>
{
public:
 
  typedef R Rep;
  typedef typename R::FT Coord_type;
  typedef typename Triangulation_geom_traits_3<R>::Point_3 Point_3;
  typedef Point_3  Point;
  typedef typename Triangulation_geom_traits_3<R>::Segment_3 Segment_3;

  typedef Compute_squared_radius_circumsphere_3<Coord_type, Point_3> 
  Compute_squared_radius_circumsphere_3;
  typedef typename R::Side_of_bounded_sphere_3 Side_of_bounded_sphere_3;

  //---------------------------------------------------------------------

  Compute_squared_radius_circumsphere_3 compute_squared_radius_3_object() const
    {
      return Compute_squared_radius_circumsphere_3();
    }
  //---------------------------------------------------------------------
  
  Side_of_bounded_sphere_3 side_of_bounded_sphere_3_object() const
    {
      return Side_of_bounded_sphere_3();
    }
};

//-------------------------------------------------------------------
CGAL_END_NAMESPACE
//-------------------------------------------------------------------

#endif //CGAL_ALPHA_SHAPE_EUCLIDEAN_TRAITS_3_H
