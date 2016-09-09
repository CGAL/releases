// Copyright (c) 1997  Tel-Aviv University (Israel).
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
// $Source: /CVSROOT/CGAL/Packages/Trapezoidal_decomposition/include/CGAL/Trapezoidal_decomposition_2/Td_predicates.h,v $
// $Revision: 1.2 $ $Date: 2003/09/18 10:26:00 $
// $Name: current_submission $
//
// Author(s)	 : Oren Nechushtan <theoren@math.tau.ac.il>
//		   Iddo Hanniel <hanniel@math.tau.ac.il>
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












