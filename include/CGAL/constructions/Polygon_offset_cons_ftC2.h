// Copyright (c) 2005, 2006 Fernando Luis Cacciola Carballal. All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.2-branch/Straight_skeleton_2/include/CGAL/constructions/Polygon_offset_cons_ftC2.h $
// $Id: Polygon_offset_cons_ftC2.h 29640 2006-03-20 21:25:42Z fcacciola $
// 
// Author(s)     : Fernando Cacciola <fernando_cacciola@ciudad.com.ar>
//
#ifndef CGAL_POLYGON_OFFSET_CONS_FTC2_H
#define CGAL_POLYGON_OFFSET_CONS_FTC2_H 1

#include <CGAL/constructions/Straight_skeleton_cons_ftC2.h>

CGAL_BEGIN_NAMESPACE

namespace CGAL_SS_i
{

// Givenan offset distance 't' and 2 oriented lines l0:(a0,b0,c0), l1:(a1,b1,c1) returns the coordinates (x,y)
// of the intersection of their offsets at the given distance.
//
// PRECONDITIONS:
// The line coefficients must be normalized: a�+b�==1 and (a,b) being the leftward normal vector
// The offsets at the given distance do intersect in a single point.

template<class FT>
optional< Vertex<FT> > construct_offset_pointC2 ( FT t, Edge<FT> const& e0, Edge<FT> const& e1 )
{
  FT x(0.0),y(0.0) ;

  optional< Line<FT> > l0 = compute_normalized_line_ceoffC2(e0) ;
  optional< Line<FT> > l1 = compute_normalized_line_ceoffC2(e1) ;

  optional< Vertex<FT> > q = compute_oriented_midpoint(e0,e1);
  
  bool ok = false ;
  
  if ( l0 && l1 && q )
  {
    FT den = l1->a() * l0->b() - l0->a() * l1->b() ;
  
    if ( CGAL_NTS is_finite(den) )
    {
      if ( ! CGAL_NTS is_zero(den) )
      {
        FT numX = t * l1->b() - t * l0->b() + l0->b() * l1->c() - l1->b() * l0->c() ;
        FT numY = t * l1->a() - t * l0->a() + l0->a() * l1->c() - l1->a() * l0->c() ;
          
        x = -numX / den ;
        y =  numY / den ;
      }
      else
      {
        x = q->x() + l0->a() * t  ;
        y = q->y() + l0->b() * t  ;
      }
      
      ok = CGAL_NTS is_finite(x) && CGAL_NTS is_finite(y) ;
    }
  }

  return make_optional(ok,Vertex<FT>(x,y)) ;
}

} // namespace CGAL_SS_i

CGAL_END_NAMESPACE

#endif // CGAL_POLYGON_OFFSET_CONS_FTC2_H //
// EOF //

