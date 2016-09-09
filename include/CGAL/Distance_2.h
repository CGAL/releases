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
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/Distance_2.h
// package       : Triangulation (4.69)
// source        : $RCSfile: Distance_2.h,v $
// revision      : $Revision: 1.5 $
// revision_date : $Date: 1999/10/07 14:16:01 $
// author(s)     : Mariette Yvinec
//                 Sylvain Pion
//
// coordinator   : Mariette Yvinec
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_DISTANCE_2_H
#define CGAL_DISTANCE_2_H

#include <CGAL/assertions.h>
#include <CGAL/distance_predicates_2.h>

CGAL_BEGIN_NAMESPACE

template <class I>
struct Distance_2
{
  typedef typename I::Point Point;

  Distance_2(const I* = NULL) {}

  Distance_2(const Point& p0, const I* = NULL)
  { p[0]=p0; }

  Distance_2(const Point& p0, const Point& p1, const I* = NULL)
  { p[0]=p0; p[1]=p1; }

  Distance_2(const Point& p0, const Point& p1, const Point& p2, 
	     const I* = NULL)
  { p[0]=p0; p[1]=p1; p[2]=p2; }

  void set_point(int i, const Point& q)
  {
    CGAL_precondition( ((unsigned int) i) < 3 );
    p[i] = q;
  }

  Point get_point(int i) const
  {
    CGAL_precondition( ((unsigned int) i) < 3 );
    return p[i];
  }

  Comparison_result compare() const
  {
    return cmp_dist_to_point(p[0], p[1], p[2]);
  }

private:
  Point p[3];
};

template <class Traits>
struct Distance_xy_3  : public Distance_2<Traits> 
{
  typedef typename Distance_2<Traits>::Point Point;

public:
  Distance_xy_3(const Point& p0,
	   const Traits* traits = NULL)
    : Distance_2<Traits>(p0, traits) { }
    
    
  Distance_xy_3(const Point& p0,
	   const Point& p1,
	   const Traits* traits = NULL)
    : Distance_2<Traits>(p0,p1,traits) { }
    
  Distance_xy_3(const Point& p0,
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

CGAL_END_NAMESPACE

#endif // CGAL_DISTANCE_2_H
