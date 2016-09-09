//  -*- Mode: c++ -*-
// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.1
// release_date  : 1998, July 24
//
// file          : include/CGAL/min_sqr_distance_traits.h
// package       : bops (1.0.5)
// source        : include/CGAL/min_sqr_distance_traits.h
// revision      : $Revision: 1.0.5 $
// revision_date : $Date: Tue Jun 30 19:04:35 MET DST 1998  $
// author(s)     :        Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_MIN_SQR_DISTANCE_TRAITS_H
#define CGAL_MIN_SQR_DISTANCE_TRAITS_H

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif
#ifndef CGAL_CARTESIAN_H
#include <CGAL/Cartesian.h>
#endif
#ifndef CGAL_HOMOGENEOUS_H
#include <CGAL/Homogeneous.h>
#endif
#include <list.h>
#include <vector.h>
#include <multiset.h>
#include <algo.h>
#ifndef CGAL_POINT_2_H
#include <CGAL/Point_2.h>
#endif


template < class _R >
struct min_sqr_distance_traits : public _R {
  typedef _R R;
  typedef typename _R::FT NT;
  //typedef CGAL_Point_2< CGAL_Cartesian<double> > dPoint;
  struct dPoint {
    dPoint() : _x(0.0), _y(0.0) {}
    dPoint(double sx, double sy) : _x(sx), _y(sy) {}
    dPoint(const dPoint& p) : _x(p.x()), _y(p.y()) {}
    double x() const { return _x; }
    double y() const { return _y; }
    dPoint& operator=(const dPoint& p) {
      _x= p.x();
      _y= p.y();
      return *this;
    }
    double _x, _y;
  };

  typedef CGAL_Point_2<R>  Point;


  NT sqr( const NT& a ) const { return a * a; }
  double dsqr( const double& a ) const { return a * a; }

  double to_double(const NT& a) const {
    return CGAL_to_double(a);
  }
 

  dPoint to_dPoint(const Point& pt) const {
    return dPoint(to_double(pt.x()), to_double(pt.y()) );
  }


  double double_squared_distance(const Point& p1, const Point& p2) const {
    /* returns the square go the euclidean metric: 
               (p1.x-p2.x)^2 + (p1.y-p2.y)^2
    */
    return to_double( sqr(p1.x()-p2.x()) + sqr(p1.y()-p2.y()) );
  }

  double squared_distance(const dPoint& p1, const dPoint& p2) const {
    /* returns the square go the euclidean metric: 
               (p1.x-p2.x)^2 + (p1.y-p2.y)^2
    */
    return dsqr(p1.x()-p2.x()) + dsqr(p1.y()-p2.y());
  }

  double squared_distance_x(const dPoint& p1, const dPoint& p2) const {
    /* returns (p1.x-p2.x)^2 */
    return dsqr(p1.x()-p2.x());
  }
};

#endif // CGAL_MIN_SQR_DISTANCE_TRAITS_H
