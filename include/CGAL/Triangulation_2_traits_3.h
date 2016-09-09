// ======================================================================
//
// Copyright (c) 1997  The CGAL Consortium

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
// file          : include/CGAL/Triangulation_2_traits_3.h
// package       : Triangulation (4.69)
// source        : $RCSfile: Triangulation_2_traits_3.h,v $
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2000/08/25 13:07:19 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_2_TRAITS_3_H
#define CGAL_TRIANGULATION_2_TRAITS_3_H


#include <CGAL/Point_3.h>
#include <CGAL/Segment_3.h>
#include <CGAL/Triangle_3.h>


#include <CGAL/triangulation_assertions.h>

CGAL_BEGIN_NAMESPACE 

template<class R>
class Compare_yz_3
{
public:
  typedef Point_3<R>     Point;

  Comparison_result operator() (Point p, Point q){
    Comparison_result r;
    r = CGAL::compare_y<R>(p,q);
    if (r == EQUAL) r = CGAL::compare_z<R>(p,q);
    return r;
   }
};
    

template <class R>
class Orientation_2_3 
{
public:
  typedef Point_3<R>     Point; 
  Orientation operator()(const Point& p,
			 const Point& q,
			 const Point& r)
    {
      Orientation or;
      Point O(0.1111,0.1111,0.1111); 
      Point A(1.1111,0,0);
      Point B(0,1.1111,0);
      Point C(0,0,1.1111);

      Point P = ((or = CGAL::orientation(p,q,r,O)) != ZERO) ? O:
                ((or = CGAL::orientation(p,q,r,A)) != ZERO) ? A:
                ((or = CGAL::orientation(p,q,r,B)) != ZERO) ? B:
                ((or = CGAL::orientation(p,q,r,C)) != ZERO) ? C: C;
      return CGAL::orientation(p,q,r,P);
    }
};

template <class R>
class Side_of_oriented_circle_2_3 
{
public:
  typedef Point_3<R>     Point; 
  CGAL::Oriented_side operator() (const Point &p, 
				  const Point &q,
				  const Point &r, 
				  const Point &s)
    {
      //CGAL_triangulation_precondition( 
      //              CGAL::orientation(p,q,r,s) == COPLANAR );
      CGAL_triangulation_precondition( !CGAL::collinear(p,q,r) );

      // test belongs to the circle if and only if it belongs to a
      // sphere passing through pqr
      Orientation or;
      Point O(0.1111,0.1111,0.1111); 
      Point A(1.1111,0,0);
      Point B(0,1.1111,0);
      Point C(0,0,1.1111);

      Point P = ((or = CGAL::orientation(p,q,r,O)) != ZERO) ? O:
                ((or = CGAL::orientation(p,q,r,A)) != ZERO) ? A:
                ((or = CGAL::orientation(p,q,r,B)) != ZERO) ? B:
                ((or = CGAL::orientation(p,q,r,C)) != ZERO) ? C: C;

      return Oriented_side( or *
	      CGAL::side_of_oriented_sphere(p, q, r, P, s));
    }
};



template < class R >
class Triangulation_2_traits_3 {
public:
  typedef R Rep;
  typedef Point_3<R>  Point_2;
  typedef Segment_3<R> Segment_2;
  typedef Triangle_3<R> Triangle_2;
 
  typedef typename R::Compare_x_3         Compare_x_2;
  typedef Compare_yz_3<R>                 Compare_y_2;
  typedef Orientation_2_3<R>              Orientation_2;
  typedef Side_of_oriented_circle_2_3<R>  Side_of_oriented_circle_2;
  
  typedef typename R::Construct_segment_3        Construct_segment_2;
  typedef typename R::Construct_triangle_3       Construct_triangle_2;

  // for compatibility with previous versions
  typedef Point_2      Point;
  typedef Segment_2    Segment;
  typedef Triangle_2   Triangle;

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
#endif // CGAL_TRIANGULATION_2_TRAITS_3_H
