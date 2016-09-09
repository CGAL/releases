/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/

#ifndef CGAL_CONSTRUCTIVE_CONVEX_HULL_TRAITS_2_H
#define CGAL_CONSTRUCTIVE_CONVEX_HULL_TRAITS_2_H

#include <CGAL/Point_2.h>
#include <CGAL/Line_2.h>
#include <CGAL/predicates_on_points_2.h>
#include <CGAL/distance_predicates_2.h>
#include <CGAL/predicate_objects_on_points_2.h>

template <class _R>
class CGAL_convex_hull_constructive_traits_2 : public _R
{
 public:

   typedef   _R                                             R;
   typedef   CGAL_Point_2<R>                                Point_2;    
   typedef   CGAL_p_Less_xy<Point_2>                        Less_xy;
   typedef   CGAL_p_Less_yx<Point_2>                        Less_yx;
   typedef   CGAL_p_Greater_xy<Point_2>                     Greater_xy;
   typedef   CGAL_p_Greater_yx<Point_2>                     Greater_yx;
   typedef   CGAL_r_Right_of_line<R>                        Right_of_line;
   typedef   CGAL_r_Less_negative_dist_to_line<R>           Less_dist_to_line;
   typedef   CGAL_p_Less_rotate_ccw<Point_2>                Less_rotate_ccw;

   bool      leftturn(const Point_2& p,const Point_2& q,const Point_2& r) const
             {
               return ::CGAL_leftturn((const R::Point_2&)p,
                                      (const R::Point_2&)q,
                                      (const R::Point_2&)r );
             }

   bool      rightturn(const Point_2& p,const Point_2& q,const Point_2& r) const
             {
               return ::CGAL_rightturn((const R::Point_2&)p,
                                       (const R::Point_2&)q,
                                       (const R::Point_2&)r ); 
             } 

};


#endif // CGAL_CONSTRUCTIVE_CONVEX_HULL_TRAITS_2_H

