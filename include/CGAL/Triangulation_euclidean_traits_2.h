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
// file          : include/CGAL/Triangulation_euclidean_traits_2.h
// package       : Triangulation (3.17)
// source        : $RCSfile: Triangulation_euclidean_traits_2.h,v $
// revision      : $Revision: 1.6.1.15 $
// revision_date : $Date: 1999/05/01 09:58:12 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_EUCLIDEAN_TRAITS_2_H
#define CGAL_TRIANGULATION_EUCLIDEAN_TRAITS_2_H

#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Line_2.h>
#include <CGAL/Direction_2.h>
#include <CGAL/Ray_2.h>
#include <CGAL/basic_constructions_2.h>

#include <CGAL/triangulation_assertions.h>
#include <CGAL/Triangulation_short_names_2.h>
#include <CGAL/squared_distance_2.h>
#include <CGAL/Distance_2.h>

CGAL_BEGIN_NAMESPACE 

template < class R >
class Triangulation_euclidean_traits_2 {
public:
  typedef R Rep;
  typedef Point_2<R>  Point;
  typedef Segment_2<R> Segment;
  typedef Triangle_2<R> Triangle;
  typedef Line_2<R> Line;
  typedef Direction_2<R> Direction;
  typedef Ray_2<R> Ray;

  typedef Distance_2<Triangulation_euclidean_traits_2<R> > Distance;

  Triangulation_euclidean_traits_2(){}
  Triangulation_euclidean_traits_2(
				const Triangulation_euclidean_traits_2& et){}
  Triangulation_euclidean_traits_2 &operator=(
		       const Triangulation_euclidean_traits_2&  et){return *this;}

    Comparison_result compare_x(const Point &p, const Point &q) const
    {
        return CGAL::compare_x(p, q);
    }


    Comparison_result compare_y(const Point &p, const Point &q) const
    {
        return CGAL::compare_y(p, q);
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
        return CGAL::orientation(p, q, r);
    }


  Oriented_side side_of_oriented_circle(const Point &p,
					const Point &q,
					const Point &r,
					const Point &s) const
    {
      return CGAL::side_of_oriented_circle(p, q, r, s);
    }

  Point circumcenter(const Point &p, const Point &q, const Point &r) const
    {
        return CGAL::circumcenter(p, q, r);
    }

     // Cette fonction devrait être accessible à tout CGAL.
  Line bisector(const Segment &s) const
  {
    Point p = midpoint (s.source(), s.target());
    Line l(s.source(), s.target());
    return l.perpendicular(p);
  }
};

CGAL_END_NAMESPACE 

#endif // CGAL_TRIANGULATION_EUCLIDEAN_TRAITS_2_H
