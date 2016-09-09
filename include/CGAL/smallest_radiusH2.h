// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/smallest_radiusH2.h
// package       : Alpha_shapes_2 (8.3)
// source        : $RCSfile: smallest_radiusH2.h,v $
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2000/02/04 12:56:05 $
// author(s)     : Tran Kai Frank DA
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_SMALLEST_RADIUSH2_H
#define CGAL_SMALLEST_RADIUSH2_H

#include <CGAL/PVDH2.h>

template < class FT, class RT>
FT
inline squared_radius_circumcircle(const PointH2<FT,RT> &p,
				   const PointH2<FT,RT> &q,
				   const PointH2<FT,RT> &r) const
{
  // compute the smallest radius directly
  if (orientation(p, q, r) == COLLINEAR)
    // what do we do 
    return typename R::FT (0);
  else
    
    {
      Circle_2<R> c(p, q, r);
      return typename R::FT (c.squared_radius());
    }
}

#endif //CGAL_SMALLEST_RADIUSH2_H
