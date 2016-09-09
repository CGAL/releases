// Copyright (c) 2003,2004  INRIA Sophia-Antipolis (France) and
// Notre Dame University (U.S.A.).  All rights reserved.
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
// $Source: /CVSROOT/CGAL/Packages/Segment_Voronoi_diagram_2/include/CGAL/predicates/Svd_oriented_side_C2.h,v $
// $Revision: 1.7 $ $Date: 2004/08/13 16:55:52 $
// $Name:  $
//
// Author(s)     : Menelaos Karavelas <mkaravel@cse.nd.edu>



#ifndef CGAL_SVD_ORIENTED_SIDE_C2_H
#define CGAL_SVD_ORIENTED_SIDE_C2_H

#include <CGAL/predicates/Svd_basic_predicates_C2.h>
#include <CGAL/predicates/Segment_Voronoi_diagram_vertex_2.h>


CGAL_BEGIN_NAMESPACE

//-----------------------------------------------------------------------------



template<class K, class Method_tag>
class Svd_oriented_side_C2
  : public Svd_basic_predicates_C2<K>
{
private:

  typedef Svd_basic_predicates_C2<K>          Base;
  typedef Svd_voronoi_vertex_2<K,Method_tag>  Voronoi_vertex_2;
  
  typedef typename Base::Point_2              Point_2;
  typedef typename Base::Segment_2            Segment_2;
  typedef typename Base::Line_2               Line_2;
  typedef typename Base::Site_2               Site_2;
  typedef typename Base::FT                   FT;
  typedef typename Base::RT                   RT;

public:
  typedef Oriented_side              result_type;
  typedef Site_2                     argument_type;
  typedef Arity_tag<5>               Arity;

  // computes the oriented side of the point q
  // wrt the line that is passes through the point p and its direction
  // is the direction of the supporting line of s, rotated by 90
  // degrees counterclockwise.
  Oriented_side operator()(const Site_2& q, 
			   const Site_2& s, const Site_2& p) const
  {
    CGAL_precondition( q.is_point() );
    CGAL_precondition( s.is_segment() && p.is_point() );

    Line_2 l = compute_supporting_line( s );
    Line_2 lp = compute_perpendicular(l, p.point());

    return lp.oriented_side(q.point());
  }

  // computes the oriented side of the Voronoi vertex of s1, s2, s3
  // wrt the line that is passes through the point p and its direction
  // is the direction of the supporting line of s, rotated by 90
  // degrees counterclockwise.
  Oriented_side operator()(const Site_2& s1, const Site_2& s2,
			   const Site_2& s3,
			   const Site_2& s, const Site_2& p) const
  {
    CGAL_precondition( s.is_segment() && p.is_point() );

    Voronoi_vertex_2 v(s1, s2, s3);
    Line_2 l = compute_supporting_line( s );
    Line_2 lp = compute_perpendicular(l, p.point());

    return v.oriented_side(lp);
  }
};


//-----------------------------------------------------------------------------

CGAL_END_NAMESPACE

#endif // CGAL_SVD_ORIENTED_SIDE_C2_H
