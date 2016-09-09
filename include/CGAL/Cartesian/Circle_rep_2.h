// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

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
// file          : include/CGAL/Cartesian/Circle_rep_2.h
// package       : C2 (4.4)
// revision      : $Revision: 1.9 $
// revision_date : $Date: 2000/06/26 15:00:21 $
// author(s)     : Andreas Fabri, Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_CIRCLE_REP_2_H
#define CGAL_CARTESIAN_CIRCLE_REP_2_H

CGAL_BEGIN_NAMESPACE

template < class R >
class Circle_repC2 
//: public Rep
  : public Ref_counted
{
public:
  typedef typename R::FT                        FT;
#ifndef CGAL_CFG_NO_ADVANCED_KERNEL
  typedef typename R::Point_2                   Point_2;
#else
  typedef typename R::Point_2_base              Point_2;
#endif

  Point_2      center;
  FT           squared_radius;
  Orientation  orient;


  Circle_repC2() {}

  Circle_repC2(const Point_2 & c, const FT & r, const Orientation &o)
    : center(c), squared_radius(r), orient(o) {}

  ~Circle_repC2() {}
};

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_CIRCLE_REP_2_H
