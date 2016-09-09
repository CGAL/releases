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
// file          : include/CGAL/Pm_leda_segment_exact_traits.h
// package       : pm (5.43)
// author(s)     : Eyal flato
//		   Iddo hanniel
//
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_PM_LEDA_SEGMENT_EXACT_TRAITS_H
#define CGAL_PM_LEDA_SEGMENT_EXACT_TRAITS_H

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif

#include <CGAL/rat_leda_in_CGAL_2.h>

#include <cmath>
#include <cassert>

#ifdef CGAL_PM_LEDA_SEGMENT_EXACT_TRAITS_DEBUG
#include <CGAL/Pm_traits_operations_count.h>
#define OP_CONSUME(x, y) OP.Consume(x, y)
#else
#define OP_CONSUME(x, y) 
#endif

CGAL_BEGIN_NAMESPACE

class Pm_leda_segment_exact_traits
{
public:
	
	typedef leda_rat_segment	X_curve;
	typedef leda_rat_point	Point;
	typedef leda_rat_point	Point_2;
	typedef leda_rat_vector	Vector;
	typedef leda_rat_vector	Vector_2;
	typedef leda_rational	NumberType;
	
	typedef enum 
	{
		CURVE_VERTICAL_UP = 0,
		CURVE_VERTICAL_DOWN = 2,
		CURVE_LEFT = 3,
		CURVE_RIGHT = 1
	} Curve_status;
	
	typedef enum
	{
		UNDER_CURVE = -1,
		ABOVE_CURVE = 1,
		ON_CURVE = 2,
		CURVE_NOT_IN_RANGE = 0
		//CURVE_VERTICAL = 3
	} Curve_point_status;	
	
#ifdef CGAL_PM_LEDA_SEGMENT_EXACT_TRAITS_DEBUG
	COperationsConsumptionCount OP;
#endif
	
public:
	
	Pm_leda_segment_exact_traits()
#ifdef CGAL_PM_LEDA_SEGMENT_EXACT_TRAITS_DEBUG
		: OP(opNumOperations)
#endif
	{
	}
	
	~Pm_leda_segment_exact_traits() 
	{
#ifdef CGAL_PM_LEDA_SEGMENT_EXACT_TRAITS_DEBUG
		std::ofstream os("OpCount.txt");
		OP.Write(os);
#endif
	}
	
	Point curve_source(const X_curve & cv) const 
	{ 
		return cv.source(); 
	}
	
	Point curve_target(const X_curve & cv) const 
	{
		return cv.target(); 
	}
	
	bool curve_is_vertical(const X_curve & cv) const 
	{
		OP_CONSUME(opCompare, 1);
		if (cv.is_trivial())
			return true;
		return cv.is_vertical();
	}
	
	bool curve_is_in_x_range(const X_curve & cv, const Point & q) const
	{ 
		OP_CONSUME(opCompare, 3);
		return !( is_right(q, rightmost(cv.source(), cv.target())) ||
			is_left(q, leftmost(cv.source(), cv.target()))	 );
	}
	
	bool curve_is_in_y_range(const X_curve &cv, const Point & q) const
	{ 
		OP_CONSUME(opCompare, 3);
		bool r = !( is_lower(q, lowest(cv.source(), cv.target())) ||
			is_higher(q, highest(cv.source(), cv.target())) );
		return r;
	}
	
	Orientation orientation(const Point &p, const Point &q, const Point &r) const
	{
		OP_CONSUME(opOrientation, 1);
		return CGAL::orientation(p, q, r);
	}
	
	Curve_point_status 
		curve_get_point_status(const X_curve &cv, const Point & p) const
	{
		if (!curve_is_in_x_range(cv, p))
			return CURVE_NOT_IN_RANGE;
		if (!curve_is_vertical(cv))
		{
			Orientation o;
			if (compare_x(cv.source(), cv.target()) < 0)
				o = orientation(cv.source(), cv.target(), p);
			else
				o = orientation(cv.target(), cv.source(), p);
			
			if (o < 0)
				return UNDER_CURVE;
			if (o > 0)
				return ABOVE_CURVE;
			if (o == 0)
				return ON_CURVE;
			return ON_CURVE;
		}
		else
		{
			//return CURVE_VERTICAL; //&&& - copied from exact-traits ask Oren & Iddo 1/4/99
			
			if (is_lower(p,lowest(curve_source(cv),curve_target(cv))))
				return UNDER_CURVE;
			if (is_higher(p,highest(curve_source(cv),curve_target(cv))))
				return ABOVE_CURVE;
			// if (curve_is_in_y_range(cv,p))
			return ON_CURVE;
		}                    
	}
	
	Comparison_result 
		curve_compare_at_x(const X_curve &cv1, const X_curve &cv2, const Point &q) 
		const 
	{
		if ((!curve_is_in_x_range(cv1, q)) || (!curve_is_in_x_range(cv2, q)))
			return EQUAL;
		
		int res;
		// bug ??? in LEDA - 
		// cmp_segments_at_xcoord returns wrong answer if
		// cv1 (or cv2) are from right to left
		// cv1_ and cv2_ are the same as cv1 and cv2 - oriented from left to right
		X_curve cv1_ = cv1;
		X_curve cv2_ = cv2;
		if (is_left(cv1.target(), cv1.source()))
			cv1_ = cv1.reversal();
		if (is_left(cv2.target(), cv2.source()))
			cv2_ = cv2.reversal();
		
		OP_CONSUME(opSegmentX, 1);
		res = cmp_segments_at_xcoord(cv1_, cv2_, q);
		
		if (res < 0) 
			return SMALLER;
		if (res > 0) 
			return LARGER;
		return EQUAL;
	}
	
	
	Comparison_result 
		curve_compare_at_x_left(const X_curve &cv1, const X_curve &cv2, 
		const Point &q) const 
	{
		if (curve_is_vertical(cv1) || (curve_is_vertical(cv2))) return EQUAL;
		if (!is_left(leftmost(cv1.source(), cv1.target()), q)) return EQUAL;
		if (!is_left(leftmost(cv2.source(), cv2.target()), q)) return EQUAL;
		
		Comparison_result r = curve_compare_at_x(cv1, cv2, q);
		
		if ( r != EQUAL)
			return r;     // since the curve is continous 
		
		// <cv2> and <cv1> meet at a point with the same x-coordinate as q
		return (Comparison_result)
			orientation(leftmost(cv2.source(), cv2.target()), q,
			leftmost(cv1.source(), cv1.target()) );
	}
	
	Comparison_result 
		curve_compare_at_x_right(const X_curve &cv1, const X_curve &cv2, const Point & q) const 
	{
		if (curve_is_vertical(cv1) || (curve_is_vertical(cv2))) return EQUAL;
		if (!is_right(rightmost(cv1.source(), cv1.target()), q)) return EQUAL;
		if (!is_right(rightmost(cv2.source(), cv2.target()), q)) return EQUAL;
		
		Comparison_result r = curve_compare_at_x(cv1, cv2, q);
		
		if ( r != EQUAL)
			return r;     // since the curve is continous (?)
		
		// <cv1> and <cv2> meet at a point with the same x-coordinate as q
		return (Comparison_result)
			orientation(q, rightmost(cv2.source(), cv2.target()),  
			rightmost(cv1.source(), cv1.target()) );
	}
	
	
	X_curve curve_flip(const X_curve &cv) const
	{
		return cv.reversal();
	}
	
	Curve_status curve_get_status(const X_curve &cv) const
	{
		if (curve_is_vertical(cv)) 
		{
			if ( is_higher(cv.target(), cv.source()) )
				return CURVE_VERTICAL_UP;
			else
				return CURVE_VERTICAL_DOWN;
		}
		else
		{
			if ( is_right(cv.target(), cv.source()) )
				return CURVE_RIGHT;
			else
				return CURVE_LEFT;
		}
	}
	
	
	bool curve_is_between_cw(const X_curve &cv, 
		const X_curve &first, 
		const X_curve &second, 
		const Point &point)	const
		// TRUE if cv is between first and second in cw direction
		// precondition: this, first and second have a common endpoint
		// precondition: first, second, this are pairwise interior disjoint
	{
		Point p = point;
		
		X_curve cv0 = first;
		X_curve cv1 = second;
		X_curve cvx = cv;
		
		if ( !is_same(cv0.source(),p) ) cv0 = curve_flip(cv0);
		if ( !is_same(cv1.source(),p) ) cv1 = curve_flip(cv1);
		if ( !is_same(cvx.source(),p) ) cvx = curve_flip(cvx);
		
		Point p0(cv0.target()), p1(cv1.target()), px(cvx.target());
		
		int or0=orientation(p0,p,px);
		int or1=orientation(p1,p,px);
		int or=or0*or1;
		
		if (or < 0) 
		{ //one is a leftturn the other rightturn
			return (or0 == LEFTTURN); //leftturn
		}
		else 
		{ //both are either left or right turns (or one is colinear)
			if (orientation(p0,p,p1)==RIGHTTURN)
			{
				if ((or1 == 0) && (or0 == RIGHTTURN)) 
					return false; // the case where cvx and cv1 are colinear
				else 
					return true;
			}
			else
			{
				return false;
			}
		}
	}
	
	/*
	bool curve_is_between_cw(const X_curve &cv, 
	const X_curve &first, 
	const X_curve &second, 
	const Point &point)	const
	{
    bool res_iddo, res_orig;
    res_iddo = curve_is_between_cw_iddo(cv, first, second, point);
    res_orig = curve_is_between_cw_orig(cv, first, second, point);
    if (res_iddo != res_orig) 
    {
	cout << "-----------------  is_between_cw - not good" << endl;
	cout << cv << endl;
	cout << first << endl;
	cout << second << endl;
	cout << point << endl;
	cout << "iddo:" << res_iddo << "     orig:" << res_orig << endl;
	}
    //return res_orig;
	return res_iddo;
  }*/
	
	bool curve_is_between_cw_orig(const X_curve &cv, 
		const X_curve &first, 
		const X_curve &second, 
		const Point &point)	const
		// TRUE if cv is between first and second in cw direction
		// precondition: this, first and second have a common endpoint
		// precondition: first, second, this are pairwise interior disjoint
	{
		// assert(is_intersection_simple(first, second);
		// assert(is_intersection_simple(first, *this);
		// assert(is_intersection_simple(*this, second);
		
		Curve_status cv0_status, cv1_status, cvx_status;
		int cv0_cv1, cv0_cvx, cv1_cvx;
		cv0_cv1 = cv0_cvx = cv1_cvx = -1;
		
		Point cp = point;
		
		X_curve cv0 = first;
		X_curve cv1 = second;
		X_curve cvx = cv;
		
		if ( !is_same(cv0.source(),cp) ) cv0 = curve_flip(cv0);
		if ( !is_same(cv1.source(),cp) ) cv1 = curve_flip(cv1);
		if ( !is_same(cvx.source(),cp) ) cvx = curve_flip(cvx);
		
		cv0_status = curve_get_status(cv0);
		cv1_status = curve_get_status(cv1);
		cvx_status = curve_get_status(cvx);
		
		//cout << "cv0: " << cv0 << endl;
		//cout << "cv1: " << cv1 << endl;
		//cout << "cvx: " << cvx << endl;
		
		//	the circle:				    0
		//						 ** | **
		//						*	*
		//					     3 *	 * 1
		//						*	*
		//						 ** | **
		//						    2
		
		if (cv0_status == cv1_status)
		{
			if (cv0_status == CURVE_RIGHT)
				cv0_cv1 = curve_compare_at_x_right(cv0, cv1, cp);
			if (cv0_status == CURVE_LEFT)
				cv0_cv1 = curve_compare_at_x_left(cv0, cv1, cp);
		}
		if (cv0_status == cvx_status)
		{
			if (cv0_status == CURVE_RIGHT)
				cv0_cvx = curve_compare_at_x_right(cv0, cvx, cp);
			if (cv0_status == CURVE_LEFT)
				cv0_cvx = curve_compare_at_x_left(cv0, cvx, cp);
		}
		if (cv1_status == cvx_status)
		{
			if (cv1_status == CURVE_RIGHT)
				cv1_cvx = curve_compare_at_x_right(cv1, cvx, cp);
			if (cv1_status == CURVE_LEFT)
				cv1_cvx = curve_compare_at_x_left(cv1, cvx, cp);
		}
		
		if (cv0_status == cv1_status)
		{
			if (cv0_status == CURVE_LEFT)
			{
				if ( ((cv0_cv1==1) && (cvx_status==cv0_status) && 
					((cv0_cvx==-1) || (cv1_cvx==1))) ||
					((cv0_cv1==1) && (cvx_status!=cv0_status)) ||
					((cv0_cv1==-1) && (cvx_status==cv0_status) && 
					((cv0_cvx==-1) && (cv1_cvx==1))) )
					return true;
			}
			if (cv0_status == CURVE_RIGHT)
			{
				if ( ((cv0_cv1==1) && (cvx_status==cv0_status) && 
					((cv0_cvx==1) && (cv1_cvx==-1))) ||
					((cv0_cv1==-1) && (cvx_status!=cv0_status)) ||
					((cv0_cv1==-1) && (cvx_status==cv0_status) && 
					((cv0_cvx==1) || (cv1_cvx==-1))) )
					return true;
			}
			return false;
		}
		// else do the following
		
		if (cv0_status == cvx_status)
		{
			if ( ((cv0_status == CURVE_LEFT) && (cv0_cvx==-1)) ||
				((cv0_status == CURVE_RIGHT) && (cv0_cvx==1)) )
				return true;
			
			//Addition by iddo for enabeling addition of null segments - testing
			if ( (cv0_status==CURVE_VERTICAL_DOWN)&&
				((cv0.source()==cv0.target())||(cvx.source()==cvx.target())) )
				return true; //a null segment (=point) 
			
			return false;
		}
		
		if (cv1_status == cvx_status)
		{
			if ( ((cv1_status == CURVE_LEFT) && (cv1_cvx==1)) ||
				((cv1_status == CURVE_RIGHT) && (cv1_cvx==-1)) )
				return true;
			
			//Addition by iddo for enabeling addition of null segments - testing
			if ( (cv1_status==CURVE_VERTICAL_DOWN)&&
				((cv1.source()==cv1.target())||(cvx.source()==cvx.target())) )
				return true; //a null segment (=point)  
			
			return false;
		}
		
		// cv1 and cv0 are on diffrent part of the circle - it is easy
		if ( ((cv1_status - cv0_status + 4)%4) < 
			((cvx_status - cv0_status + 4)%4) )
			return false;
		else
			// if there is an equality or inequality to the other side
			// everything is ok
			return true;
  }
  
  Comparison_result Comparison_result_from_int(int res) const 
  {
	  if (res < 0) return SMALLER;
	  if (res > 0) return LARGER;
	  return EQUAL;
  }
  
  Comparison_result compare_x(const Point &p1, const Point &p2) const
  {
	  OP_CONSUME(opCompare, 1);
	  return Comparison_result_from_int(

#if (__LEDA__ >= 380)
Point::cmp_x(p1,p2)
#else // backward compatability to LEDA
compare(p1.xcoord(),p2.xcoord())
#endif

);
	  /*static double d;
	  d = p1.xcoordD() - p2.xcoordD();
	  if (abs(d) >= 0.000001)
      if (d > 0)
	  return LARGER;
      else
	  return SMALLER;
	  return Comparison_result_from_int(compare(p1.xcoord(), p2.xcoord()));
	  */
  }
  
  Comparison_result compare_y(const Point &p1, const Point &p2) const
  {
	  OP_CONSUME(opCompare, 1);
	  return Comparison_result_from_int(

#if (__LEDA__ >= 380)
Point::cmp_y(p1,p2)
#else // backward compatability to LEDA   
compare(p1.ycoord(),p2.ycoord()) 
#endif

	);

	  /*static double d;
	  d = p1.ycoordD() - p2.ycoordD();
	  if (abs(d) >= 0.000001)
      if (d > 0)
	  return LARGER;
      else
	  return SMALLER;
	  return Comparison_result_from_int(compare(p1.ycoord(), p2.ycoord()));
	  */
  }
  
public:
	Point point_to_left(const Point& p) const  {return Point(p.xcoord()-1, p.ycoord());}
	Point point_to_right(const Point& p) const {return Point(p.xcoord()+1, p.ycoord());}
	
	bool curve_is_same(const X_curve &cv1, const X_curve &cv2) const
	{
		OP_CONSUME(opCompare, 4);
		return (cv1 == cv2) != 0;
	}
	
	bool is_point_on_curve(const X_curve &cv, const Point& p) const //check
	{
		//return (cv.sqr_dist(p) <= 0);
		OP_CONSUME(opSegmentX, 1);
		return cv.contains(p);
	}
	
public:
	bool is_left(const Point &p1, const Point &p2) const 
    { 
		OP_CONSUME(opCompare, 1); 
		return (compare_x(p1, p2) == SMALLER); 
	}
	
	bool is_right(const Point &p1, const Point &p2) const 
	{ 
		OP_CONSUME(opCompare, 1);  
		return (compare_x(p1, p2) == LARGER);
	}
	
	bool is_same_x(const Point &p1, const Point &p2) const 
	{ 
		OP_CONSUME(opCompare, 1);  
		return (compare_x(p1, p2) == EQUAL);
	}
	
	bool is_lower(const Point &p1, const Point &p2) const 
	{ 
		OP_CONSUME(opCompare, 1);  
		return (compare_y(p1, p2) == SMALLER);
	}
	
	bool is_higher(const Point &p1, const Point &p2) const 
	{ 
		OP_CONSUME(opCompare, 1); 
		return (compare_y(p1, p2) == LARGER); 
	}
	
	bool is_same_y(const Point &p1, const Point &p2) const 
	{ 
		OP_CONSUME(opCompare, 1); 
		return (compare_y(p1, p2) == EQUAL); 
	}
	
	bool is_same(const Point &p1, const Point &p2) const
	{ 
		OP_CONSUME(opCompare, 2); 
		return (p1 == p2); 
	}
	
	const Point& leftmost(const Point &p1, const Point &p2) const
    { return (is_left(p1, p2) ? p1 : p2); }
	
	const Point& rightmost(const Point &p1, const Point &p2) const
    { return (is_right(p1, p2) ? p1 : p2); }
	
	const Point& lowest(const Point &p1, const Point &p2) const
    { return (is_lower(p1, p2) ? p1 : p2); }
	
	const Point& highest(const Point &p1, const Point &p2) const
    { return (is_higher(p1, p2) ? p1 : p2); }
	
	
	
};

CGAL_END_NAMESPACE


#endif // PM_LEDA_SEGMENT_EXACT_TRAITS_H













