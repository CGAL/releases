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
// file          : include/CGAL/IO/triangulation_Window_stream.h
// package       : Triangulation (4.69)
// source        : $RCSfile: triangulation_Window_stream.h,v $
// revision      : $Revision: 1.10 $
// revision_date : $Date: 1999/09/01 15:38:04 $
// author(s)     : Olivier Devillers
//                 Andreas Fabri
//                 Monique Teillaud
//                 Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================


#ifdef CGAL_TRIANGULATION_2_H
#ifndef CGAL_WINDOW_STREAM_TRIANGULATION_2_H
#define CGAL_WINDOW_STREAM_TRIANGULATION_2_H
CGAL_BEGIN_NAMESPACE
template < class Gt, class Tds>
Window_stream&
operator<<(Window_stream& os,  const Triangulation_2<Gt, Tds> &t)
{
  return t.draw_triangulation(os);
}
CGAL_END_NAMESPACE
#endif // CGAL_WINDOW_STREAM_TRIANGULATION_2_H
#endif // CGAL_TRIANGULATION_2_H

#ifdef CGAL_DELAUNAY_TRIANGULATION_2_H
#ifndef CGAL_WINDOW_STREAM_DELAUNAY_TRIANGULATION_2_H
#define CGAL_WINDOW_STREAM_DELAUNAY_TRIANGULATION_2_H
CGAL_BEGIN_NAMESPACE
template < class Gt, class Tds >
Window_stream&
operator<<(Window_stream& os,  const Delaunay_triangulation_2<Gt,Tds> &dt)
{
   return dt.draw_triangulation(os);
}
CGAL_END_NAMESPACE
#endif // CGAL_WINDOW_STREAM_DELAUNAY_TRIANGULATION_2_H
#endif // CGAL_DELAUNAY_TRIANGULATION_2_H

#ifdef CGAL_CONSTRAINED_TRIANGULATION_2_H
#ifndef CGAL_WINDOW_STREAM_CONSTRAINED_TRIANGULATION_2_H
#define CGAL_WINDOW_STREAM_CONSTRAINED_TRIANGULATION_2_H
CGAL_BEGIN_NAMESPACE
template < class Gt, class Tds>
Window_stream&
operator<<(Window_stream& os,  const Constrained_triangulation_2<Gt,Tds> &t)
{
  return t.draw_triangulation(os);
}
CGAL_END_NAMESPACE
#endif // CGAL_WINDOW_STREAM_CONSTRAINED_TRIANGULATION_2_H
#endif // CGAL_CONSTRAINED_TRIANGULATION_2_H


#ifdef CGAL_WEIGHTED_POINT_H
#ifndef CGAL_WINDOW_STREAM_WEIGHTED_POINT_H
#define CGAL_WINDOW_STREAM_WEIGHTED_POINT_H
CGAL_BEGIN_NAMESPACE
template < class Point, class We >
Window_stream&
operator<<(Window_stream& os, const Weighted_point< Point, We > &p)
{
  double cx = to_double(p.point().x()),
         cy = to_double(p.point().y()),
         r = to_double(p.weight());

  os<<p.point();
  os.draw_circle(cx, cy , /*sqrt*/(r));
  return os;
}

template < class Point, class We >
Window_stream& operator>>(Window_stream &os, Weighted_point< Point, We > &wp)
{
  double cx, cy, x1, y1;
  os.read_mouse(cx,cy);
  os.read_mouse_circle(cx,cy, x1, y1);
  Point center(cx, cy);

  We sr = We (sqrt( square(cx-x1)+square(cy-y1) ) );

  os.draw_circle(cx, cy , sr );
  wp = Weighted_point< Point, We >(center, sr);
  return os;
}

CGAL_END_NAMESPACE
#endif // CGAL_WINDOW_STREAM_WEIGHTED_POINT_H
#endif // CGAL_WEIGHTED_POINT_H


#ifdef CGAL_REGULAR_TRIANGULATION_2_H
#ifndef CGAL_WINDOW_STREAM_REGULAR_TRIANGULATION_2_H
#define CGAL_WINDOW_STREAM_REGULAR_TRIANGULATION_2_H
CGAL_BEGIN_NAMESPACE
template < class Gt, class Tds >
Window_stream&
operator<<(Window_stream& os, Regular_triangulation_2<Gt,Tds> &t)
{
    return t.draw_triangulation(os);
}
CGAL_END_NAMESPACE
#endif // CGAL_WINDOW_STREAM_REGULAR_TRIANGULATION_2_H
#endif // CGAL_REGULAR_TRIANGULATION_2_H
