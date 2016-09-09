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
// file          : include/CGAL/Cartesian/constructions_on_lines_2.h
// package       : C2 (4.4)
// revision      : $Revision: 1.8 $
// revision_date : $Date: 2000/08/23 13:47:26 $
// author(s)     : Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_CONSTRUCTIONS_ON_LINES_2_H
#define CGAL_CARTESIAN_CONSTRUCTIONS_ON_LINES_2_H

#include <CGAL/Cartesian/Point_2.h>
#include <CGAL/Cartesian/Line_2.h>

CGAL_BEGIN_NAMESPACE

template < class R >
inline
LineC2<R CGAL_CTAG>
line_from_points( PointC2<R CGAL_CTAG> const& p,
                  PointC2<R CGAL_CTAG> const& q)
{
  typename R::FT a,b,c;
  line_from_pointsC2(p.x(),p.y(),q.x(),q.y(),a,b,c);
  return LineC2<R CGAL_CTAG>(a,b,c);
}

template < class R >
inline
LineC2<R CGAL_CTAG>
line_from_point_direction( PointC2<R CGAL_CTAG> const& p,
                           DirectionC2<R CGAL_CTAG> const& d)
{
  typename R::FT a,b,c;
  line_from_point_directionC2(p.x(),p.y(),d.dx(),d.dy(),a,b,c);
  return LineC2<R CGAL_CTAG>(a,b,c);
}

template < class R >
inline
LineC2<R CGAL_CTAG>
bisector( PointC2<R CGAL_CTAG> const& p,
          PointC2<R CGAL_CTAG> const& q)
{
  typename R::FT a,b,c;
  bisector_of_pointsC2(p.x(),p.y(),q.x(),q.y(),a,b,c);
  return LineC2<R CGAL_CTAG>(a,b,c);
}

template < class R >
inline
LineC2<R CGAL_CTAG>
perpendicular_through_point( LineC2<R CGAL_CTAG> const& l,
                             PointC2<R CGAL_CTAG> const& p)
{
  typename R::FT a,b,c;
  perpendicular_through_pointC2(l.a(),l.b(),p.x(),p.y(),a,b,c);
  return LineC2<R CGAL_CTAG>(a,b,c);
}

template < class R >
inline
typename R::FT
line_y_at_x( LineC2<R CGAL_CTAG> const& l,
             typename R::FT const& x)
{
  return line_y_at_xC2(l.a(), l.b(), l.c(), x);
}

template < class R >
inline
typename R::FT
line_x_at_y( LineC2<R CGAL_CTAG> const& l,
             typename R::FT const& y)
{
  return line_y_at_xC2(l.b(), l.a(), l.c(), y);
}

template < class R >
inline
PointC2<R>
line_get_point( LineC2<R CGAL_CTAG> const& l, int i)
{
  typename R::FT x, y;
  line_get_pointC2(l.a(), l.b(), l.c(), i, x, y);
  return PointC2<R>(x,y);
}

template < class R >
inline
PointC2<R>
line_project_point( LineC2<R CGAL_CTAG> const& l,
                    PointC2<R CGAL_CTAG> const& p)
{
  typename R::FT x, y;
  line_project_pointC2(l.a(), l.b(), l.c(), p.x(), p.y(), x, y);
  return PointC2<R>(x,y);
}

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_CONSTRUCTIONS_ON_LINES_2_H
