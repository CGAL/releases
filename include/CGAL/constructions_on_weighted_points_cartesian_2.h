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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/constructions_on_weighted_points_cartesian_2.h
// package       : Triangulation_2 (5.18)
// source        : $RCSfile: constructions_on_weighted_points_cartesian_2.h,v $
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2000/12/26 08:54:34 $
// author(s)     : Julia Flototto, Mariette Yvinec
//
// coordinator   : Mariette Yvinec 
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CONSTRUCTIONS_ON_WEIGHTED_POINTS_CARTESIAN_2_H
#define CGAL_CONSTRUCTIONS_ON_WEIGHTED_POINTS_CARTESIAN_2_H

#include <CGAL/Cartesian/redefine_names_2.h>

CGAL_BEGIN_NAMESPACE 


template < class RT >
void
weighted_circumcenter_translateC2(const RT &dqx, const RT &dqy, const RT &dqw,
				  const RT &drx, const RT &dry, const RT &drw,
				  RT &dcx,       RT &dcy)
{
  // Given 3 points P, Q, R, this function takes as input:
  // qx-px, qy-py,qw-pw,  rx-px, ry-py, rw-pw.  And returns cx-px, cy-py,
  // where (cx, cy) are the coordinates of the circumcenter C.

  // What we do is intersect the radical axis
  RT r2 = CGAL_NTS square(drx) + CGAL_NTS square(dry) - drw;
  RT q2 = CGAL_NTS square(dqx) + CGAL_NTS square(dqy) - dqw;

  RT den = RT(2) * det2x2_by_formula(dqx, dqy, drx, dry);

  // The 3 points aren't collinear.
  // Hopefully, this is already checked at the upper level.
  CGAL_assertion ( den != RT(0) );

  // One possible optimization here is to precompute 1/den, to avoid one
  // division.  However, we loose precision, and it's maybe not worth it (?).
  dcx =   det2x2_by_formula (dry, dqy, r2, q2) / den;
  dcy = - det2x2_by_formula (drx, dqx, r2, q2) / den;
}

//template < class RT >
template < class RT, class We>
void
weighted_circumcenterC2( const RT &px, const RT &py, const We &pw,
			 const RT &qx, const RT &qy, const We &qw,
			 const RT &rx, const RT &ry, const We &rw,
			 RT &x, RT &y )
{
  RT dqw = RT(qw-pw);
  RT drw = RT(rw-pw);
 
  weighted_circumcenter_translateC2(qx-px, qy-py, dqw,rx-px, ry-py,drw,x, y);
  x += px;
  y += py;
}


template < class RT , class We>
void
radical_axisC2(const RT &px, const RT &py, const We &pw,
	       const RT &qx, const RT &qy, const We &qw,
	       RT &a, RT &b, RT& c )
{
  a =  RT(2)*(px - qx);
  b =  RT(2)*(py - qy);
  c = - CGAL_NTS square(px) - CGAL_NTS square(py) 
      + CGAL_NTS square(qx) + CGAL_NTS square(qy) 
       +RT(pw) - RT(qw);
}




CGAL_END_NAMESPACE
#endif //CGAL_CONSTRUCTIONS_ON_WEIGHTED_POINTS_CARTESIAN_2_H
