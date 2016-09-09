// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
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
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/Triangulation_euclidean_traits_2.h
// package       : Triangulation (2.10)
// source        : $Source: /u/alcor/0/prisme_util/CGAL/Local/cvsroot/Triangulation/include/CGAL/Triangulation_euclidean_traits_2.h,v $
// revision      : $Revision: 1.6.1.9 $
// revision_date : $Date: 1998/12/04 13:43:35 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
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

template < class R >
class CGAL_Triangulation_euclidean_traits_2 {
public:
  typedef R Rep;
  typedef CGAL_Point_2<R>  Point;
  typedef CGAL_Segment_2<R> Segment;
  typedef CGAL_Triangle_2<R> Triangle;
  typedef CGAL_Line_2<R> Line;
  typedef CGAL_Direction_2<R> Direction;
  typedef CGAL_Ray_2<R> Ray;

  typedef CGAL_Distance_2<CGAL_Triangulation_euclidean_traits_2<R> > Distance;

  CGAL_Triangulation_euclidean_traits_2(){}
  CGAL_Triangulation_euclidean_traits_2(
				const CGAL_Triangulation_euclidean_traits_2& et){}
  CGAL_Triangulation_euclidean_traits_2 &operator=(
		       const CGAL_Triangulation_euclidean_traits_2&  et){return *this;}

    CGAL_Comparison_result compare_x(const Point &p, const Point &q) const
    {
        return CGAL_compare_x(p, q);
    }


    CGAL_Comparison_result compare_y(const Point &p, const Point &q) const
    {
        return CGAL_compare_y(p, q);
    }

  bool compare(const Point &p, const Point &q) const
  {
    return (CGAL_compare_x(p, q)== CGAL_EQUAL &&  
	    CGAL_compare_y(p, q)== CGAL_EQUAL);
  }

    CGAL_Orientation orientation(const Point &p,
                                 const Point &q,
                                 const Point &r) const
    {
        return CGAL_orientation(p, q, r);
    }


   CGAL_Orientation extremal(const Point &p,
                              const Point &q,
                              const Point &r) const
      {
        if (compare(p,q)) return CGAL_COLLINEAR;
        if (compare(p,r)) return CGAL_COLLINEAR;
        if (compare(r,q)) return CGAL_COLLINEAR;
    
        return CGAL_orientation(p, q, r);
      }
    
    CGAL_Oriented_side side_of_oriented_circle(const Point &p,
                                               const Point &q,
                                               const Point &r,
                                               const Point &s) const
      {
        if (compare(p,s)) return CGAL_ON_ORIENTED_BOUNDARY;
        if (compare(q,s)) return CGAL_ON_ORIENTED_BOUNDARY;
        if (compare(r,s)) return CGAL_ON_ORIENTED_BOUNDARY;
    
        return CGAL_side_of_oriented_circle(p, q, r, s);
      }

     Point circumcenter(const Point &p, const Point &q, const Point &r) const
    {
        return CGAL_circumcenter(p, q, r);
    }

  Line bisector(const Segment &s) const
  {
    typedef typename Point::FT FT;
    Point p = s.source() + (s.target() - s.source()) * FT(0.5);
    Line l(s.source(), s.target());
    return l.perpendicular(p);
  }


};


#endif // CGAL_TRIANGULATION_EUCLIDEAN_TRAITS_2_H
