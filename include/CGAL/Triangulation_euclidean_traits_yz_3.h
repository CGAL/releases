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
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : include/CGAL/Triangulation_euclidean_traits_yz_3.h
// package       : Triangulation (4.30)
// source        : $RCSfile: Triangulation_euclidean_traits_yz_3.h,v $
// revision      : $Revision: 1.12 $
// revision_date : $Date: 1999/10/15 16:45:06 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_EUCLIDEAN_TRAITS_YZ_3_H
#define CGAL_TRIANGULATION_EUCLIDEAN_TRAITS_YZ_3_H

#include <CGAL/Triangulation_short_names_2.h>
#include <CGAL/triangulation_assertions.h>
#include <CGAL/Distance_2.h>

#include <CGAL/Point_3.h>
#include <CGAL/Segment_3.h>
#include <CGAL/Triangle_3.h>
#include <CGAL/predicates/kernel_ftC2.h>


CGAL_BEGIN_NAMESPACE

template < class R >
class Triangulation_euclidean_traits_yz_3 {
public:
  typedef Triangulation_euclidean_traits_yz_3<R> Traits;
  typedef R Rp;
  typedef Point_3<R>  Point;
  typedef Segment_3<R> Segment;
  typedef Triangle_3<R> Triangle;
  typedef Line_3<R>   Line;
  typedef Ray_3<R>    Ray;
  typedef Direction_3<R> Direction;
  typedef Distance_xy_3<Traits> Distance;
    
  Triangulation_euclidean_traits_yz_3(){}
  Triangulation_euclidean_traits_yz_3(
	const Triangulation_euclidean_traits_yz_3& et){}
  Triangulation_euclidean_traits_yz_3 &operator=(
        const Triangulation_euclidean_traits_yz_3&  et){return *this;}
    
  typename Rp::FT x(const Point &p) const { return p.y(); }
  typename Rp::FT y(const Point &p) const { return p.z(); }
    
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
        
};


CGAL_END_NAMESPACE


#endif // CGAL_TRIANGULATION_EUCLIDEAN_TRAITS_YZ_3_H
