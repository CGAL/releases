// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// file          : include/CGAL/IO/Straight_2_stream.h
// package       : Planar_map (5.113)
// source        : 
// revision      : 
// revision_date : 
// author(s)     : Oren Nechushtan
//                 
//
//
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// Chapter       : 
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_IO_PM_STRAIGHT_2_STREAM_H
#define CGAL_IO_PM_STRAIGHT_2_STREAM_H

#ifndef CGAL_STRAIGHT_2_H
#include <CGAL/Straight_2.h>
#endif

#include <ostream>

CGAL_BEGIN_NAMESPACE

template <class R> 
std::ostream& operator<<(std::ostream& os,const Straight_2_<R>& cv)
{
	typedef Straight_2_<R> Straight;
	switch(cv.current_state())
	{
	case Straight::EMPTY:
	  return os;
	case Straight::POINT:
		{
			Point_2<R> p;
			cv.current(p);
			return os << p;
		}
	case Straight::SEGMENT:
		{
			Segment_2<R> seg;
			cv.current(seg);
			return os << seg;
		}
	case Straight::RAY:
		{
			Ray_2<R> ray;
			cv.current(ray);
			return os << ray;
		}
	case Straight::LINE:
		{
			Line_2<R> line;
			cv.current(line);
			return os << line;
		}
	}
	CGAL_assertion_msg(
		cv.current_state()==Straight::EMPTY||
		cv.current_state()==Straight::POINT||
		cv.current_state()==Straight::SEGMENT||
		cv.current_state()==Straight::RAY||
		cv.current_state()==Straight::LINE,
		"\nUnknown type in  leda_window& operator<<(leda_window& os,\
const Straight& cv)");
	return os;
}
template <class R> 
std::istream& operator>>(std::istream& os,const Straight_2_<R>& cv)
{
	typedef Straight_2_<R> Straight;
	switch(cv.current_state())
	{
	case Straight::EMPTY:
	  return os;
	case Straight::POINT:
		{
			Point_2<R> p;
			cv.current(p);
			return os >> p;
		}
	case Straight::SEGMENT:
		{
			Segment_2<R> seg;
			cv.current(seg);
			return os >> seg;
		}
	case Straight::RAY:
		{
			Ray_2<R> ray;
			cv.current(ray);
			return os >> ray;
		}
	case Straight::LINE:
		{
			Line_2<R> line;
			cv.current(line);
			return os >> line;
		}
	}
	CGAL_assertion_msg(
		cv.get_type()==Straight::EMPTY||
		cv.get_type()==Straight::POINT||
		cv.get_type()==Straight::SEGMENT||
		cv.get_type()==Straight::RAY||
		cv.get_type()==Straight::LINE,
		"\nUnknown type in  leda_window& operator>>(leda_window& os," 
		<< "const Straight& cv)");
	return os;
}

CGAL_END_NAMESPACE

#endif // CGAL_IO_PM_STRAIGHT_2_STREAM_H















