// Copyright (c) 1998-2003  ETH Zurich (Switzerland).
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
// $Source: /CVSROOT/CGAL/Packages/Matrix_search/include/CGAL/Pierce_rectangles_2_traits.h,v $
// $Revision: 1.58 $ $Date: 2003/09/29 08:41:44 $
// $Name: current_submission $
//
// Author(s)     : Michael Hoffmann <hoffmann@inf.ethz.ch>

#if ! (CGAL_PIERCE_RECTANGLES_2_TRAITS_H)
#define CGAL_PIERCE_RECTANGLES_2_TRAITS_H 1

#include <CGAL/Point_2.h>

CGAL_BEGIN_NAMESPACE

template < class R_ >
struct Piercing_traits_cartesian {
  // types
  typedef R_                           R;
  typedef typename R::FT               FT;
  typedef Point_2< R >                 Point_2;
  // constructions
  typedef Infinity_distance_2< R >     Infinity_distance_2;

  // get object methods:
  Infinity_distance_2
  get_infinity_distance_2() const
  { return Infinity_distance_2(); }

}; // Piercing_traits_cartesian
CGAL_END_NAMESPACE


#endif // ! (CGAL_PIERCE_RECTANGLES_2_TRAITS_H)
// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

