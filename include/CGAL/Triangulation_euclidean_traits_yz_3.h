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
// file          : include/CGAL/Triangulation_euclidean_traits_yz_3.h
// package       : Triangulation (2.10)
// source        : $SOURCE SCVSROOT/Triangulation/include/CGAL/Triangulation_euclidean_traits_yz_3.h,v $
// revision      : $Revision: 1.2.1.5 $
// revision_date : $Date: 1998/12/18 10:22:59 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
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
#include <CGAL/predicates_on_ftC2.h>

template < class R >
class CGAL_Triangulation_euclidean_traits_yz_3 {
public:
    typedef CGAL_Triangulation_euclidean_traits_yz_3<R> Traits;
    typedef R Rep;
    typedef CGAL_Point_3<R>  Point;
    typedef CGAL_Segment_3<R> Segment;
    typedef CGAL_Triangle_3<R> Triangle;
    typedef CGAL_Line_3<R>   Line;
    typedef CGAL_Ray_3<R>    Ray;
    typedef CGAL_Direction_3<R> Direction;
    
   
    
      typename Rep::FT x(const Point &p) const { return p.y(); }
      typename Rep::FT y(const Point &p) const { return p.z(); }
    
    CGAL_Comparison_result compare_x(const Point &p, const Point &q) const
      {
        return CGAL_compare(x(p), x(q));
      }
    CGAL_Comparison_result compare_y(const Point &p, const Point &q) const
      {
        return CGAL_compare(y(p), y(q));
      }
    bool compare(const Point &p, const Point &q) const
      {
        return (x(p)==x(q)) &&  (y(p)==y(q));
      }
    
    CGAL_Orientation orientation(const Point &p,
                                 const Point &q,
                                 const Point &r) const
      {
        return CGAL_orientationC2(x(p), y(p), x(q), y(q), x(r), y(r));
      }
    
    CGAL_Orientation extremal(const Point &p,
                              const Point &q,
                              const Point &r) const
      {
        if (compare(p,q)) return CGAL_COLLINEAR;
        if (compare(p,r)) return CGAL_COLLINEAR;
        if (compare(r,q)) return CGAL_COLLINEAR;
    
        return CGAL_orientationC2(x(p), y(p), x(q), y(q), x(r), y(r));
      }
    
    CGAL_Oriented_side side_of_oriented_circle(const Point &p,
                                               const Point &q,
                                               const Point &r,
                                               const Point &s) const
      {
        if (compare(p,s)) return CGAL_ON_ORIENTED_BOUNDARY;
        if (compare(q,s)) return CGAL_ON_ORIENTED_BOUNDARY;
        if (compare(r,s)) return CGAL_ON_ORIENTED_BOUNDARY;
    
        return CGAL_side_of_oriented_circleC2(x(p), y(p),
                                              x(q), y(q),
                                              x(r), y(r),
                                              x(s), y(s));
      }
    

        
    class Distance : public CGAL_Distance_2<Traits> {
    public:
        Distance(const Point& p0,
                 const Traits* traits = NULL)
            : CGAL_Distance_2<Traits>(p0, traits) { }
    
    
        Distance(const Point& p0,
                 const Point& p1,
                 const Traits* traits = NULL)
            : CGAL_Distance_2<Traits>(p0,p1,traits) { }
    
        Distance(const Point& p0,
                 const Point& p1,
                 const Point& p2,
                 const Traits* traits = NULL)
            : CGAL_Distance_2<Traits>(p0,p1,p2,traits) { }
    
        CGAL_Comparison_result
        compare() const
        {
          Point p0 = get_point(0);
          Point p1 = get_point(1);
          Point p2 = get_point(2);
          return CGAL_cmp_dist_to_pointC2(x(p0),y(p0),x(p1),y(p1),x(p2),y(p2));
        }
    };
    
};


#endif // CGAL_TRIANGULATION_EUCLIDEAN_TRAITS_YZ_3_H
