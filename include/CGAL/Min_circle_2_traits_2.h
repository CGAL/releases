// Copyright (c) 1997-2001  Freie Universitaet Berlin (Germany).
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
// $Source: /CVSROOT/CGAL/Packages/Min_circle_2/include/CGAL/Min_circle_2_traits_2.h,v $
// $Revision: 1.8 $ $Date: 2003/09/18 10:23:08 $
// $Name: current_submission $
//
// Author(s)     : Sven Sch�nherr <sven@inf.ethz.ch>, Bernd G�rtner

#ifndef CGAL_MIN_CIRCLE_2_TRAITS_2_H
#define CGAL_MIN_CIRCLE_2_TRAITS_2_H

// includes
#ifndef CGAL_POINT_2_H
#  include <CGAL/Point_2.h>
#endif
#ifndef CGAL_OPTIMISATION_CIRCLE_2_H
#  include <CGAL/Optimisation_circle_2.h>
#endif
#ifndef CGAL_PREDICATES_ON_POINTS_2_H
#  include <CGAL/predicates_on_points_2.h>
#endif

CGAL_BEGIN_NAMESPACE

// Class declarations
// ==================
template < class Traits_ >
class Min_circle_2;

template < class K_ >
class Min_circle_2_traits_2;

// Class interface and implementation
// ==================================
template < class K_ >
class Min_circle_2_traits_2 {
  public:
    // types
    typedef  K_                              K;
    typedef  CGAL::Point_2<K>                Point;
    typedef  CGAL::Optimisation_circle_2<K>  Circle;

private:
    // data members
    Circle  circle;                                 // current circle

    // friends
    friend  class CGAL::Min_circle_2< CGAL::Min_circle_2_traits_2<K> >;

  public:
    // creation (use default implementations)
    // CGAL::Min_circle_2_traits_2( );
    // CGAL::Min_circle_2_traits_2( CGAL::Min_circle_2_traits_2<K> const&);

    // operations
    inline
    CGAL::Orientation
    orientation( const Point& p, const Point& q, const Point& r) const
    {
        return( CGAL::orientation( p, q, r));
    }
};

CGAL_END_NAMESPACE

#endif // CGAL_MIN_CIRCLE_2_TRAITS_2_H

// ===== EOF ==================================================================
