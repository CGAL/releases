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
// file          : include/CGAL/bops_Convex_Polygon_2.h
// package       : bops (2.4)
// source        : include/CGAL/bops_Convex_Polygon_2.h
// revision      : $Revision: 1.1.1.1 $
// revision_date : $Date: 1999/10/11 13:50:32 $
// author(s)     : Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_BOPS_CONVEX_POLYGON_2_H
#define CGAL_BOPS_CONVEX_POLYGON_2_H

#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/Vector_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/predicates_on_points_2.h>
#include <CGAL/Segment_2_Segment_2_intersection.h>
#include <list>

CGAL_BEGIN_NAMESPACE

#define CONVEX_INTERSECTION_PROCEDURE // now this proc. will be used
template <class R_type, class Container>
Polygon_2<Polygon_traits_2<R_type>, Container>
Convex_Intersection(
           Polygon_2<Polygon_traits_2<R_type>, Container> P,
           Polygon_2<Polygon_traits_2<R_type>, Container> Q);





template<class I>
class Bops_Convex_Polygons_2 : public Bops_Polygons_2<I>
{
public:
	typedef CGAL::Vector_2<R>		Vector;
	typedef typename I::NT			NT;
	typedef typename I::Polygon	Polygon;
	typedef typename I::Point	Point;
	typedef typename I::Segment	Segment;
	typedef typename I::Polygon::Vertex_circulator	Vertex_circulator;
	typedef CGAL::Orientation	Orientation;
	Polygon _pgonA,_pgonB;
	Bops_Convex_Polygons_2() {}
	Bops_Convex_Polygons_2(const Polygon& A, const Polygon& B)
		:
		_pgonA(A),
		_pgonB(B) {}
	
	virtual ~Bops_Convex_Polygons_2() {}
	
protected:
	enum InFlag {Unknown, Pin, Qin};

	virtual void conditional_insert(
		InFlag inpgon,
		InFlag inflag,
		const Point& pt
	) {} // = 0;

	virtual void handle_special_cases() = 0;
	
	void mainProcedure();
	
	bool operation() {
#   ifdef CONVEX_INTERSECTION_PROCEDURE
		add_to_result(Convex_Intersection(_pgonA, _pgonB));
#   else
		init();
		mainProcedure();
		if (_inflag == Unknown)
			handle_special_cases();
		else
			add_to_result(_pt_list);
#   endif
		return empty();
	}	
	
	void insert( const Point& pt )
		// inserts a solution point in the point-list
	{
		if (!_pt_list.empty() ) {
			if ( (_pt_list.back() != pt) && (_pt_list.front() != pt) )
				_pt_list.push_back(pt);
		}
		else
			_pt_list.push_back(pt);
		return;
	}
	
	void advancePolygonA() // advance the pointers on polygon A
	{
		_aAdv++; _pCir++; _pCir1++;
		// abortion check
		_lastaAdv++; _lastbAdv=0;
		return;
	}
	
	void advancePolygonB() // advance the pointers on polygon B
	{
		_bAdv++; _qCir++; _qCir1++;
		// abortion check
		_lastbAdv++; _lastaAdv=0;
		return;
	}
	
	void init()
		   // initialize variables
	{
		_lastaAdv = _lastbAdv = 0;
		_aAdv = _bAdv = 0;
		_inflag = Unknown;
		_pCir = _pCir1 = _pgonA.vertices_circulator ();
		_qCir = _qCir1 = _pgonB.vertices_circulator ();
		_pCir1--; _qCir1--;   
		return;
	}
	
	bool wentAround() const
	{
		return (_aAdv >= _pgonA.size() && _bAdv >= _pgonB.size()) ||
		       _lastaAdv > _pgonA.size() || _lastbAdv > _pgonB.size();
	}

	InFlag handleIntersectionPoint(const Point& pt, const Orientation& aHB);
	InFlag handleIntersectionSegment(const Segment& seg);
	

	/*
	 *	Variables
	 */
	//Polygon	_A, _B;
	int _aAdv, _bAdv;           // number of iterations over each polygon
	Vertex_circulator _pCir, _qCir, _pCir1, _qCir1;
                                // circulators over polygons
	InFlag _inflag;             // which polygon is inside
	std::list<Point> _pt_list;     // points forming solution-polynom
	int _lastaAdv, _lastbAdv;   // variables to avoid endless loop
};



template<class I>
struct Bops_Convex_Polygons_2_Intersection
		: public Bops_Convex_Polygons_2<I> {
	Bops_Convex_Polygons_2_Intersection() {}
	Bops_Convex_Polygons_2_Intersection(const Polygon& A, const Polygon& B)
		: Bops_Convex_Polygons_2<I>(A,B) {}

	void conditional_insert(InFlag inPolygon, InFlag inflag, const Point& pt) {
		if (inflag == inPolygon)
			insert(pt);
		return;
	}
	
	void handle_special_cases()
	{
		//polygons do not intersect
		if (_pgonA.bounded_side(*_qCir)==ON_BOUNDED_SIDE)
			add_to_result(_pgonA);
		else if (_pgonB.bounded_side(*_pCir)==ON_BOUNDED_SIDE)
			add_to_result(_pgonB);
		else
			add_to_result(_pt_list);
	}
};

CGAL_END_NAMESPACE

#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#include <CGAL/bops_Convex_Polygon_2.C>
#endif

#endif // CGAL_BOPS_CONVEX_POLYGON_2_H
