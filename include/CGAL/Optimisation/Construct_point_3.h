// Copyright (c) 1997-2001  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source: /CVSROOT/CGAL/Packages/Optimisation_basic/include/CGAL/Optimisation/Construct_point_3.h,v $
// $Revision: 1.7 $ $Date: 2003/10/21 12:22:03 $
// $Name: current_submission $
//
// Author(s)     : Sven Sch�nherr <sven@inf.ethz.ch>

#ifndef CGAL_OPTIMISATION_CONSTRUCT_POINT_3_H
#define CGAL_OPTIMISATION_CONSTRUCT_POINT_3_H

// includes
#ifndef CGAL_POINT_3_H
#  include <CGAL/Point_3.h>
#endif
#ifndef CGAL_PROTECT_VECTOR
#  include <vector>
#  define CGAL_PROTECT_VECTOR
#endif
#ifndef CGAL_PROTECT_FUNCTIONAL
#  include <functional>
#  define CGAL_PROTECT_FUNCTIONAL
#endif
#ifndef CGAL_PROTECT_ITERATOR
#  include <iterator>
#  define CGAL_PROTECT_ITERATOR
#endif

CGAL_BEGIN_NAMESPACE

// Class declaration
// =================
template < class R >
class Construct_point_3;

// Class interface
// ===============
template < class R_ >
class Construct_point_3 {
  public:
    // self
    typedef  R_                         R;
    typedef  Construct_point_3<R>       Self;

    // types
    typedef  typename R::Point_3        Point;

    // creation
    Construct_point_3( ) { }

    // operations
    template < class InputIterator >
    Point
    operator() ( int, InputIterator first, InputIterator last) const
    {
	std::vector<CGAL_TYPENAME_MSVC_NULL R::RT>  coords;
	std::copy( first, last, std::back_inserter( coords));
	if ( coords.size() < 4) {
	    return Point( coords[ 0], coords[ 1], coords[ 2]);
	} else {
	    return Point( coords[ 0], coords[ 1], coords[ 2], coords[ 3]);
	}
    }
};

CGAL_END_NAMESPACE

#endif // CGAL_OPTIMISATION_CONSTRUCT_POINT_3_H

// ===== EOF ==================================================================
