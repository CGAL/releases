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
// $Source: /CVSROOT/CGAL/Packages/Optimisation_basic/include/CGAL/Optimisation/Access_dimension_2.h,v $
// $Revision: 1.5 $ $Date: 2003/10/21 12:22:02 $
// $Name: CGAL_3_0_1  $
//
// Author(s)     : Sven Sch�nherr <sven@inf.ethz.ch>

#ifndef CGAL_OPTIMISATION_ACCESS_DIMENSION_2_H
#define CGAL_OPTIMISATION_ACCESS_DIMENSION_2_H

// includes
#ifndef CGAL_POINT_2_H
#  include <CGAL/Point_2.h>
#endif

CGAL_BEGIN_NAMESPACE

// Class declaration
// =================
template < class R_ >
class Access_dimension_2;

// Class interface
// ===============
template < class R_ >
class Access_dimension_2 {
  public:
    // self
    typedef  R_                         R;
    typedef  Access_dimension_2<R>      Self;

    // types
    typedef  typename R::Point_2        Point;

    // unary function class types
    typedef  int                        result_type;
    typedef  Point                      argument_type;

    // creation
    Access_dimension_2( ) { }

    // operations
    int  operator() ( const Point& p) const { return p.dimension(); }
};

CGAL_END_NAMESPACE

#endif // CGAL_OPTIMISATION_ACCESS_DIMENSION_2_H

// ===== EOF ==================================================================
