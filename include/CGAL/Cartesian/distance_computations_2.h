// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : include/CGAL/Cartesian/distance_computations_2.h
// package       : C2 (3.3.11)
// revision      : $Revision: 1.4 $
// revision_date : $Date: 1999/11/05 22:29:57 $
// author(s)     : Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_CARTESIAN_DISTANCE_COMPUTATIONS_2_H
#define CGAL_CARTESIAN_DISTANCE_COMPUTATIONS_2_H

#include <utility>
#include <CGAL/Cartesian/redefine_names_2.h>

CGAL_BEGIN_NAMESPACE

template < class R >
inline
typename R::FT
squared_distance( PointC2<R CGAL_CTAG> const& p,
                  PointC2<R CGAL_CTAG> const& q)
{
  return squared_distanceC2(p.x(),p.y(),q.x(),q.y());
}

template < class R >
inline
typename R::FT
scaled_distance_to_line( LineC2<R CGAL_CTAG> const& l,
                         PointC2<R CGAL_CTAG> const& p)
{
  return scaled_distance_to_lineC2(l.a(),l.b(),l.c(),p.x(),p.y());
}

template < class R >
inline
typename R::FT
scaled_distance_to_line( PointC2<R CGAL_CTAG> const& p,
                         PointC2<R CGAL_CTAG> const& q,
                         PointC2<R CGAL_CTAG> const& r)
{
  return scaled_distance_to_lineC2(p.x(),p.y(),q.x(),q.y(),r.x(),r.y());
}

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_DISTANCE_COMPUTATIONS_2_H
