// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/Pm_with_intersections_misc.h
// package       : Arrangement (2.52)
// author(s)     : Eyal flato
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_PM_WITH_INTERSECTIONS_MISC_H
#define CGAL_PM_WITH_INTERSECTIONS_MISC_H

#ifndef CGAL_PLANAR_MAP_MISC_H
#include <CGAL/Planar_map_2/Planar_map_misc.h>
#endif

CGAL_BEGIN_NAMESPACE

template <class I>
class Planar_map_with_intersections_traits_wrap : 
  public Planar_map_traits_wrap<I>
{
public:
  typedef  Planar_map_traits_wrap<I> Base;
  typedef  typename Base::X_curve    X_curve;
  typedef  typename Base::Point      Point;
  
  Planar_map_with_intersections_traits_wrap() : Base()
  {
  }

  Planar_map_with_intersections_traits_wrap(const Base& tw) : Base(tw)
  {
  }

  void directed_curve_split(const X_curve &cv, const Point &first_pnt, 
			    const Point &split_pnt,
			    X_curve &split1, X_curve &split2) 
  {
    CGAL_assertion(point_is_same(curve_source(cv), first_pnt) || 
	   point_is_same(curve_target(cv), first_pnt));
    CGAL_assertion(!point_is_same(curve_source(cv), split_pnt));
    CGAL_assertion(!point_is_same(curve_target(cv), split_pnt));

    curve_split(cv, split1, split2, split_pnt);
//      if (!point_is_same(curve_source(split1), first_pnt)) //start flip
//        {
//  	X_curve c = split2;
//  	split2 = curve_flip(split1);
//  	split1 = curve_flip(c);
//        }// end flip
  }

  // expand (split) the segment[p1, p2] from the curve cv
//   X_curve curve_portion(const X_curve &cv, const Point &p1, const Point &p2)
//   {
//     CGAL_assertion(!point_is_same(p1, p2));
//     // direct cv as p1-->p2
//     X_curve acv = cv;
//     bool p1_p2_right;//start flip
//     bool curve_right;
//     Point ap1=p1, ap2=p2;

//      p1_p2_right = point_is_left_low(p1, p2);
//      curve_right = point_is_left_low(curve_source(cv), curve_target(cv));
//      if (curve_right != p1_p2_right) {
//             acv = curve_flip(cv);//end flip
// //        ap1 = p2;
// //        ap2 = p1;
//      }

//     // split twice to find the portion [ap1, ap2]
//     X_curve split1, split2, split3, part_cv;
//     CGAL_assertion(!point_is_same(curve_target(acv), ap1));
//     if (point_is_same(curve_source(acv), ap1))
//       split2 = acv;
//     else
//       directed_curve_split(acv, curve_source(acv), ap1, split1, split2);
//     CGAL_assertion(!point_is_same(curve_source(split2), ap2));
//     if (point_is_same(curve_target(split2), ap2))
//       part_cv = split2;
//     else
//       directed_curve_split(split2, curve_source(split2), ap2, part_cv, 
  //split3);
//     return part_cv;
//   }

  void points_swap(Point &p1, Point &p2)
  {
    Point p = p1;
    p1 = p2;
    p2 = p;
  }

#ifndef CGAL_PMWX_TRAITS_HAVE_INTERSECT_TO_LEFT

  // maps the curves to their mirror images over the y coordinate
  // and calls nearest_intersect_to_right (see there).
  bool nearest_intersection_to_left(const X_curve& cv1,
                                    const X_curve& cv2,
                                    const Point& pt,
                                    Point& p1,
                                    Point& p2) const 
    {
      Point rpt = point_reflect_in_x_and_y( pt);
      X_curve rcv1 = curve_reflect_in_x_and_y( cv1);
      X_curve rcv2 = curve_reflect_in_x_and_y( cv2);

      Point rp1, rp2;
      bool result = nearest_intersection_to_right(rcv1, rcv2, rpt, rp1, rp2);

      p1 = point_reflect_in_x_and_y( rp1);
      p2 = point_reflect_in_x_and_y( rp2);

      return result;
    }


  // maps the curves to their mirror images over the y coordinate
  // and calls do_intersect_to_right (see there).
  bool do_intersect_to_left(const X_curve& ca, const X_curve& cb,
			    const Point& pt) const
  {
      Point rpt = point_reflect_in_x_and_y( pt);
      X_curve rca = curve_reflect_in_x_and_y( ca);
      X_curve rcb = curve_reflect_in_x_and_y( cb);

      return do_intersect_to_right(rca, rcb, rpt);
  }

#endif //CGAL_PMWX_TRAITS_HAVE_INTERSECT_TO_LEFT

};

CGAL_END_NAMESPACE

#endif
