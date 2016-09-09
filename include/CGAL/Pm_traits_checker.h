// Copyright (c) 1999  Tel-Aviv University (Israel).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source: /CVSROOT/CGAL/Packages/Planar_map/include/CGAL/Pm_traits_checker.h,v $
// $Revision: 1.10 $ $Date: 2003/09/18 10:24:36 $
// $Name: current_submission $
//
// Author(s)     : Oren Nechushtan	<theoren@math.tau.ac.il>
/*

  Edited by 

  Iddo Hanniel
  Oren Nechushtan

*/
#ifndef CGAL_PM_TRAITS_CHECKER_H
#define CGAL_PM_TRAITS_CHECKER_H

/* Pm_traits_checker is a traits template that recieves two template
parameters, which are traits themselves.  The predicates will work
well iff all of the parameter traits predicates did, giving the same
answer.  It is assumed through out this traits that the parameter
traits do not require any storage.
*/
CGAL_BEGIN_NAMESPACE

// Tr1 and Tr2 are traits with the same predicate names
// C is a convertion between the geometric objects of Tr1 to those of Tr2
template <class Tr1,class Tr2>
class Pm_traits_checker_default_adaptor;

template <class Tr1,
	  class Tr2,
          class C=Pm_traits_checker_default_adaptor<Tr1,Tr2> >
class Pm_traits_checker : public Tr1
/* The inheritance here is to ensure that constants, enumerations,
   public classes, etc are inherited to the checker whenever this is
   required */
{
  Tr1 t;
  Tr2 b;
  C P; //P converts Tr1 objects to Tr2 objects (to enable comparison)
public:

  typedef typename Tr1::X_curve X_curve;
  typedef typename Tr1::Point_2 Point;
  typedef typename Tr1::Point_2 Point_2;

  Pm_traits_checker() : Tr1(),t(),b(),P() {};
  ~Pm_traits_checker() {}

  Point curve_source(const X_curve & cv) const 
  { 
    CGAL_assertion(P(t.curve_source(cv))==b.curve_source(P(cv)));
    return t.curve_source(cv);
  }
  Point curve_target(const X_curve & cv) const 
  {
    CGAL_assertion(P(t.curve_target(cv))==b.curve_target(P(cv)));
    return t.curve_target(cv);
  }

  bool curve_is_vertical(const X_curve & cv) const 
  {
    CGAL_assertion(t.curve_is_vertical(cv)==b.curve_is_vertical(P(cv)));
    return t.curve_is_vertical(cv);
  }	

  bool point_in_x_range(const X_curve & cv, const Point & q) const
  {
    CGAL_assertion(t.point_in_x_range(cv,q) == 
                   b.point_in_x_range(P(cv),P(q)));
    return t.point_in_x_range(cv,q);
  }

  Comparison_result curve_compare_y_at_x (const Point & p,
                                          const X_curve & cv) const
  {
    CGAL_assertion(t.curve_compare_y_at_x(p, cv) == 
                   b.curve_compare_y_at_x(P(p), P(cv)));
    return t.curve_compare_y_at_x(p, cv);
  }
  
  Comparison_result 
  curves_compare_y_at_x(const X_curve &cv1, const X_curve &cv2, const Point &q)
    const 
  {
    CGAL_assertion(t.curves_compare_y_at_x(cv1,cv2,q) ==
                   b.curves_compare_y_at_x(P(cv1),P(cv2),P(q)));
    return t.curves_compare_y_at_x(cv1,cv2,q);
  }
  
  Comparison_result 
  curves_compare_y_at_x_left(const X_curve &cv1, const X_curve &cv2, 
                          const Point &q) const 
  {
    CGAL_assertion(t.curves_compare_y_at_x_left(cv1,cv2,q) ==
                   b.curves_compare_y_at_x_left(P(cv1),P(cv2),P(q)));
    return t.curves_compare_y_at_x_left(cv1,cv2,q);
  }
  
  Comparison_result 
  curves_compare_y_at_x_right(const X_curve & cv1,
			   const X_curve & cv2, 
			   const Point   & q) const 
  {
    CGAL_assertion(t.curves_compare_y_at_x_right(cv1,cv2,q) ==
		   b.curves_compare_y_at_x_right(P(cv1),P(cv2),P(q)));
    return t.curves_compare_y_at_x_right(cv1,cv2,q);
  }

  Comparison_result compare_x(const Point &p1, const Point &p2) const
  {
    CGAL_assertion(t.compare_x(p1,p2)==b.compare_x(P(p1),P(p2)));
    return t.compare_x(p1,p2);
  }
  Comparison_result compare_xy(const Point &p1, const Point &p2) const
  {
    CGAL_assertion(t.compare_xy(p1,p2)==b.compare_xy(P(p1),P(p2)));
    return t.compare_xy(p1,p2);
  }
  bool curve_equal(const X_curve &cv1, const X_curve &cv2) const
    {
    CGAL_assertion(t.curve_equal(cv1,cv2)==b.curve_equal(P(cv1),P(cv2)));
    return t.curve_equal(cv1,cv2);
    }

};

template <class Tr1,class Tr2>
class Pm_traits_checker_default_adaptor
{
public:
  const typename Tr2::Point operator()(const typename Tr1::Point& p) const 
  {return typename Tr2::Point(p);}
  const typename Tr2::X_curve operator()(const typename Tr1::X_curve& c) const 
  {return typename Tr2::X_curve(c);}
};

CGAL_END_NAMESPACE

#endif // CGAL_PM_SEGMENT_EXACT_TRAITS_CHECKER_H





