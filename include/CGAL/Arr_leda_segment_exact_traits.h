// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// file          : include/CGAL/Arr_leda_segment_exact_traits.h
// package       : arr (1.73)
// author(s)     : Iddo Hanniel
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_ARR_LEDA_SEGMENT_EXACT_TRAITS
#define CGAL_ARR_LEDA_SEGMENT_EXACT_TRAITS


#include <list>

#include <CGAL/Pm_leda_segment_exact_traits.h>

CGAL_BEGIN_NAMESPACE


class Arr_leda_segment_exact_traits 
        : public Pm_leda_segment_exact_traits
{
public:
        Arr_leda_segment_exact_traits() 
                : Pm_leda_segment_exact_traits() {}

public:
  typedef Pm_leda_segment_exact_traits Base;
  
  typedef Base::Curve_status           Curve_status;
  typedef Base::Curve_point_status     Curve_point_status;
  
  typedef Base::X_curve                X_curve;
  typedef X_curve                      Curve;

  bool is_x_monotone(const Curve& cv) {return true;}
  //segments are x_monotone:
  void make_x_monotone(const Curve& cv, std::list<Curve>& l) {} 

  X_curve curve_flip(const X_curve& cv) const {
    return X_curve(curve_target(cv), curve_source(cv));
  }

  void curve_split(const X_curve& cv, X_curve& c1, X_curve& c2, 
                   const Point& split_pt) const
  {
    //split curve at split point (x coordinate) into c1 and c2
    CGAL_precondition(curve_get_point_status(cv,split_pt)==ON_CURVE);
    // does not suit pmwx 
	//CGAL_precondition(curve_source(cv)!=split_pt);
    //CGAL_precondition(curve_target(cv)!=split_pt);
    
    c1=X_curve(curve_source(cv),split_pt);
    c2=X_curve(split_pt,curve_target(cv));
  }


  //returns true iff the intersection is strictly right of pt
  bool do_intersect_to_right(const X_curve& c1, const X_curve& c2,
                             const Point& pt) const 
  {

    X_curve xcv;
    bool res = c1.intersection(c2, xcv);
    if (!res) return false;
    
    if (lexicographically_xy_larger(xcv.source(),pt) || 
        lexicographically_xy_larger(xcv.target(),pt))
      return true;
    
    return false;
  }


  bool nearest_intersection_to_right(const X_curve& c1,
                                     const X_curve& c2,
                                     const Point& pt,
                                     Point& p1,
                                     Point& p2) const {
    X_curve xcv;
    bool res = c1.intersection(c2, xcv);
    if (!res) return false;

    if (lexicographically_xy_larger(xcv.source(),xcv.target()))
      xcv=curve_flip(xcv);
    if (lexicographically_xy_larger(xcv.target(),pt)) {
      p2=point_normalize(xcv.target());
      if (lexicographically_xy_larger(xcv.source(),pt))
        p1=point_normalize(xcv.source());
      else
        p1=pt;
      
      return true;
    }

    return false;
  }


  X_curve curve_reflect_in_x_and_y (const X_curve& cv) const
  {
    X_curve reflected_cv( point_reflect_in_x_and_y( cv.source()),
			  point_reflect_in_x_and_y( cv.target()));
    return reflected_cv;
  }
      

  Point point_reflect_in_x_and_y (const Point& pt) const
  {
    Point reflected_pt( -pt.xcoord(), -pt.ycoord());
    return reflected_pt;
  }
      

  bool curves_overlap(const X_curve& ca, const X_curve& cb) const {
    X_curve xcv;
    //    bool res = 
    ca.intersection(cb, xcv);
    return !(xcv.is_trivial());
  }


private:
  Point point_normalize(const Point &pt) const {

    leda_integer g, x, y, w;
    x = pt.X();
    y = pt.Y();
    w = pt.W();
    if (x.iszero() &&  y.iszero()) {
      //g = w;
      return Point(x,y,leda_integer(1));
    }
    else {
      g = gcd(x, y);
      g = gcd(g, w);

      return Point(x/g,y/g,w/g);
    }

  }
  

public:

  //in future versions of LEDA these operators should be defined
// friend inline
// Window_stream& operator<<(Window_stream& os, const Point& p){
//     return os << leda_point(p.xcoordD(),p.ycoordD());
//   }
// friend inline
// Window_stream& operator<<(Window_stream& os, const X_curve& c){
//     leda_segment s(c.xcoord1D(),c.ycoord1D(),c.xcoord2D(),c.ycoord2D());
//     return os << s;
//   }


};

CGAL_END_NAMESPACE

#endif





