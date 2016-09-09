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
// file          : include/CGAL/Triangulation_euclidean_traits_xy_3.h
// package       : Triangulation (3.17)
// source        : $RCSfile: Triangulation_euclidean_traits_xy_3.h,v $
// revision      : $Revision: 1.2.1.12 $
// revision_date : $Date: 1999/05/10 07:47:00 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
// email         : cgal@cs.uu.nl
//
// ======================================================================



#ifndef CGAL_TRIANGULATION_EUCLIDEAN_TRAITS_XY_3_H
#define CGAL_TRIANGULATION_EUCLIDEAN_TRAITS_XY_3_H


#include <CGAL/Triangulation_short_names_2.h>
#include <CGAL/triangulation_assertions.h>
#include <CGAL/Distance_2.h>


#include <CGAL/Point_3.h>
#include <CGAL/Segment_3.h>
#include <CGAL/Triangle_3.h>
#include <CGAL/predicates_on_ftC2.h>

CGAL_BEGIN_NAMESPACE 

template < class R >
class Triangulation_euclidean_traits_xy_3 {
public:
    typedef Triangulation_euclidean_traits_xy_3<R> Traits;
    typedef R Rep;
    typedef Point_3<R>  Point;
    typedef Segment_3<R> Segment;
    typedef Triangle_3<R> Triangle;
    typedef Line_3<R>   Line;
    typedef Ray_3<R>    Ray;
    typedef Direction_3<R> Direction;
    
  Triangulation_euclidean_traits_xy_3(){}
  Triangulation_euclidean_traits_xy_3(
				const Triangulation_euclidean_traits_xy_3& et){}
  Triangulation_euclidean_traits_xy_3 &operator=(
		       const Triangulation_euclidean_traits_xy_3&  et){return *this;}


    
  typename Rep::FT x(const Point &p) const { return p.x(); }
  typename Rep::FT y(const Point &p) const { return p.y(); }
    
    Comparison_result compare_x(const Point &p, const Point &q) const
      {
        return CGAL::compare(x(p), x(q));
      }
    Comparison_result compare_y(const Point &p, const Point &q) const
      {
        return CGAL::compare(y(p), y(q));
      }
    bool compare(const Point &p, const Point &q) const
      {
        return (compare_x(p, q)== EQUAL &&  
		compare_y(p, q)== EQUAL);
      }
    
    Orientation orientation(const Point &p,
                                 const Point &q,
                                 const Point &r) const
      {
        return orientationC2(x(p), y(p), x(q), y(q), x(r), y(r));
      }
    
    
  Oriented_side side_of_oriented_circle(const Point &p,
					const Point &q,
					const Point &r,
					const Point &s) const
      {
	return side_of_oriented_circleC2(x(p), y(p),
					 x(q), y(q),
					 x(r), y(r),
					 x(s), y(s));
      }
    
    
    class Distance : public Distance_2<Traits> {
    public:
        Distance(const Point& p0,
                 const Traits* traits = NULL)
            : Distance_2<Traits>(p0, traits) { }
    
    
        Distance(const Point& p0,
                 const Point& p1,
                 const Traits* traits = NULL)
            : Distance_2<Traits>(p0,p1,traits) { }
    
        Distance(const Point& p0,
                 const Point& p1,
                 const Point& p2,
                 const Traits* traits = NULL)
            : Distance_2<Traits>(p0,p1,p2,traits) { }
    
        Comparison_result
        compare() const
        {
          Point p0 = get_point(0);
          Point p1 = get_point(1);
          Point p2 = get_point(2);
          return cmp_dist_to_pointC2(x(p0),y(p0),x(p1),y(p1),x(p2),y(p2));
        }
    };
    
};

CGAL_END_NAMESPACE 

#endif // CGAL_TRIANGULATION_EUCLIDEAN_TRAITS_XY_3_H
