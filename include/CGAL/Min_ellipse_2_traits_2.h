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
// $Source: /CVSROOT/CGAL/Packages/Min_ellipse_2/include/CGAL/Min_ellipse_2_traits_2.h,v $
// $Revision: 1.4 $ $Date: 2003/09/18 10:23:12 $
// $Name: current_submission $
//
// Author(s)     : Sven Sch�nherr <sven@inf.ethz.ch>, Bernd G�rtner

#ifndef CGAL_MIN_ELLIPSE_2_TRAITS_2_H
#define CGAL_MIN_ELLIPSE_2_TRAITS_2_H

// includes
#ifndef CGAL_POINT_2_H
#  include <CGAL/Point_2.h>
#endif
#ifndef CGAL_OPTIMISATION_ELLIPSE_2_H
#  include <CGAL/Optimisation_ellipse_2.h>
#endif

CGAL_BEGIN_NAMESPACE

// Class declarations
// ==================
template < class Traits_ >
class Min_ellipse_2;

template < class K_ >
class Min_ellipse_2_traits_2;

// Class interface and implementation
// ==================================
template < class K_ >
class Min_ellipse_2_traits_2 {
  public:
    // types
    typedef  K_                               K;
    typedef  CGAL::Point_2<K>                 Point;
    typedef  CGAL::Optimisation_ellipse_2<K>  Ellipse;

private:
    // data members
    Ellipse  ellipse;                                // current ellipse

    // friends
    friend  class CGAL::Min_ellipse_2< CGAL::Min_ellipse_2_traits_2<K> >;

  public:
    // creation (use default implementations)
    // Min_ellipse_2_traits_2( );
    // Min_ellipse_2_traits_2( Min_ellipse_2_traits_2<K> const&);
};

CGAL_END_NAMESPACE

#endif // CGAL_MIN_ELLIPSE_2_TRAITS_2_H

// ===== EOF ==================================================================
