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
// file          : include/CGAL/Triangulation_euclidean_traits_xy_3.h
// package       : Triangulation_2 (5.18)
// source        : $RCSfile: Triangulation_euclidean_traits_xy_3.h,v $
// revision      : $Revision: 1.18 $
// revision_date : $Date: 2000/11/27 13:34:04 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================



#ifndef CGAL_TRIANGULATION_EUCLIDEAN_TRAITS_XY_3_H
#define CGAL_TRIANGULATION_EUCLIDEAN_TRAITS_XY_3_H


#include <CGAL/Triangulation_short_names_2.h>
#include <CGAL/triangulation_assertions.h>

#include <CGAL/Point_3.h>
#include <CGAL/Segment_3.h>
#include <CGAL/Triangle_3.h>
#include <CGAL/predicates/kernel_ftC2.h>

CGAL_BEGIN_NAMESPACE 

template <class R>
class Orientation_xy_3 
{
public:
  typedef Point_3<R>     Point; 
  typename R::FT x(const Point &p) const { return p.x(); }
  typename R::FT y(const Point &p) const { return p.y(); }

  CGAL::Orientation operator()(const Point& p,
			       const Point& q,
			       const Point& r)
    {
      return orientationC2(x(p), y(p), x(q), y(q), x(r), y(r));
    }
};

template <class R>
class Side_of_oriented_circle_xy_3 
{
public:
  typedef Point_3<R>     Point; 
  typename R::FT x(const Point &p) const { return p.x(); }
  typename R::FT y(const Point &p) const { return p.y(); }

  CGAL::Oriented_side operator() (const Point &p, 
				  const Point &q,
				  const Point &r, 
				  const Point &s) 
    {
      return side_of_oriented_circleC2(x(p), y(p),
				       x(q), y(q),
				       x(r), y(r),
				       x(s), y(s));
    }
};

template < class R >
class Triangulation_euclidean_traits_xy_3 {
public:
  typedef Triangulation_euclidean_traits_xy_3<R> Traits;
  typedef R Rp;
  typedef Point_3<R>     Point_2;
  typedef Segment_3<R>   Segment_2;
  typedef Triangle_3<R>  Triangle_2;

  typedef typename Rp::Compare_x_3          Compare_x_2;
  typedef typename Rp::Compare_y_3          Compare_y_2;
  typedef Orientation_xy_3<Rp>              Orientation_2;
  typedef Side_of_oriented_circle_xy_3<Rp>  Side_of_oriented_circle_2;
  typedef typename Rp::Construct_segment_3   Construct_segment_2;
  typedef typename Rp::Construct_triangle_3  Construct_triangle_2;

  // for compatibility with previous versions
  typedef Point_2      Point;
  typedef Segment_2    Segment;
  typedef Triangle_2   Triangle;

  Triangulation_euclidean_traits_xy_3(){}
  Triangulation_euclidean_traits_xy_3(
		   const Triangulation_euclidean_traits_xy_3&){}
  Triangulation_euclidean_traits_xy_3 &operator=(
	    const Triangulation_euclidean_traits_xy_3&){return *this;}

  typename Rp::FT x(const Point_2 &p) const { return p.x(); }
  typename Rp::FT y(const Point_2 &p) const { return p.y(); }
    
 
  Compare_x_2
  compare_x_2_object() const
    { return Compare_x_2();}

  Compare_y_2
  compare_y_2_object() const
    { return Compare_y_2();}

  Orientation_2
  orientation_2_object() const
    { return Orientation_2();}

  Side_of_oriented_circle_2
  side_of_oriented_circle_2_object() const
    {return Side_of_oriented_circle_2();}

  Construct_segment_2  construct_segment_2_object() const
    {return Construct_segment_2();}

  Construct_triangle_2  construct_triangle_2_object() const
    {return Construct_triangle_2();}

};
  

CGAL_END_NAMESPACE 

#endif // CGAL_TRIANGULATION_EUCLIDEAN_TRAITS_XY_3_H
