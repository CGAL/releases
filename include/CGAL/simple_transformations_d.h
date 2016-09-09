// ======================================================================
//
// Copyright (c) 2000,2001 The CGAL Consortium

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
// file          : include/CGAL/simple_transformations_d.h
// package       : Kernel_d (0.9.47)
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2001/05/30 12:21:48 $
// author(s)     : Michael Seel
// coordinator   : MPI Saarbruecken
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_SIMPLE_TRANSFORMATIONS_D_H
#define CGAL_SIMPLE_TRANSFORMATIONS_D_H

#include <CGAL/Homogeneous_d.h>

CGAL_BEGIN_NAMESPACE
/*{\Moptions outfile=Simple_transformations.man}*/
/*{\Manpage{}{}{Simple Affine Transformations}{}}*/

template <class R>
Point_d<R> reflect(const Point_d<R>& p, const Point_d<R>& q)
/*{\Mfunc  returns |p| reflected at point |q|. }*/
{ return Point_d<R>(p + 2*(q-p)); }

template <class R>
Point_d<R> reflect(const Point_d<R>& p, const Line_d<R>& l)
/*{\Mfunc  returns |p| reflected across line |l|.}*/
{ // reflect point across line through r and s
  Point_d<R> c = l.projection(p);
  return Point_d<R>(p + 2*(c-p));
}

template <class R>
Sphere_d<R> reflect(const Sphere_d<R>& s, const Point_d<R>& p)
/*{\Mfunc returns |s| reflected across point |p|.}*/
{ std::vector< Point_d<R> > B(s.points_begin(),s.points_end());
  typename std::vector< Point_d<R> >::iterator it;
  for (it = B.begin(); it != B.end(); ++it) *it = reflect(*it,p);
  return Sphere_d<R>(p.dimension(),B.begin(),B.end());
}

template <class R>
Sphere_d<R> reflect(const Sphere_d<R>& s, const Line_d<R>& l)
/*{\Mfunc returns |s| reflected across line |l|.}*/
{ std::vector< Point_d<R> > B(s.points_begin(),s.points_end());
  typename std::vector< Point_d<R> >::iterator it;
  for (it = B.begin(); it != B.end(); ++it) *it = reflect(*it,l);
  return Sphere_d<R>(l.dimension(),B.begin(),B.end());
}

template <class R>
Segment_d<R> reflect(const Segment_d<R>& s, const Point_d<R>& p)
/*{\Mfunc returns |s| reflected across point |p|.}*/
{ return Segment_d<R>(reflect(s.point(0),p),reflect(s.point(1),p)); }

template <class R>
Segment_d<R> reflect(const Segment_d<R>& s, const Line_d<R>& l)
/*{\Mfunc returns |s| reflected across line |l|.}*/
{ return Segment_d<R>(reflect(s.point(0),l),reflect(s.point(1),l)); }

template <class R>
Ray_d<R> reflect(const Ray_d<R>& r, const Point_d<R>& p)
/*{\Mfunc returns |s| reflected across point |p|.}*/
{ return Ray_d<R>(reflect(r.point(0),p),reflect(r.point(1),p)); }

template <class R>
Ray_d<R> reflect(const Ray_d<R>& r, const Line_d<R>& l)
/*{\Mfunc returns |s| reflected across line |l|.}*/
{ return Ray_d<R>(reflect(r.point(0),l),reflect(r.point(1),l)); }

template <class R>
Line_d<R> reflect(const Line_d<R>& l, const Point_d<R>& p)
/*{\Mfunc returns |s| reflected across point |p|.}*/
{ return Line_d<R>(reflect(l.point(0),p),reflect(l.point(1),p)); }

template <class R>
Line_d<R> reflect(const Line_d<R>& s, const Line_d<R>& l)
/*{\Mfunc returns |s| reflected across line |l|.}*/
{ return Line_d<R>(reflect(s.point(0),l),reflect(s.point(1),l)); }

CGAL_END_NAMESPACE
#endif // CGAL_SIMPLE_TRANSFORMATIONS_D_H

