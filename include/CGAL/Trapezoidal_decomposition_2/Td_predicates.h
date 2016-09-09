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
// file          : include/CGAL/Trapezoidal_decomposition_2/Td_predicates.h
// package       : Trapezoidal_decomposition (1.26)
// source		 : 
// revision 	 : 
// revision_date : 
// author(s)	 : Oren Nechushtan
//		   Iddo Hanniel
//
// maintainer(s) : Oren Nechushtan
//
//
// coordinator	 : Tel-Aviv University (Dan Halperin)
//
// Chapter		 : 
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_TD_PREDICATES_H
#define CGAL_TD_PREDICATES_H

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif

#include <functional>

CGAL_BEGIN_NAMESPACE

template < class Td_traits> class Trapezoidal_decomposition_2;

template <class X_trapezoid>
struct Td_active_trapezoid : public std::unary_function<X_trapezoid,bool>
{
	bool operator()(const X_trapezoid& tr) const
	{
		return tr.is_active();
	}
};
template <class X_trapezoid,class Traits>
struct Td_active_non_degenerate_trapezoid : 
public std::unary_function<X_trapezoid,bool>
{
	Td_active_non_degenerate_trapezoid(Traits& t) : traits(t) {}
	bool operator()(const X_trapezoid& tr) const
	{
		return tr.is_active() && !traits.is_degenerate(tr);
	}
	protected:
		const Traits& traits;
};
template <class X_trapezoid,class Traits>
struct Td_active_right_degenerate_curve_trapezoid:
public std::unary_function<X_trapezoid,bool>
{
	Td_active_right_degenerate_curve_trapezoid(Traits& t) : traits(t) {}
	bool operator()(const X_trapezoid& tr) const
	{
		return tr.is_active() && traits.is_degenerate_curve(tr) && 
			!tr.right_bottom_neighbour();
	}
	protected:
		const Traits& traits;
};

CGAL_END_NAMESPACE

#endif //CGAL_TD_PREDICATES_H












