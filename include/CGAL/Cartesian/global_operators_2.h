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
// file          : include/CGAL/Cartesian/global_operators_2.h
// package       : C2 (4.4)
// revision      : $Revision: 1.7 $
// revision_date : $Date: 2000/07/09 10:46:14 $
// author(s)     : Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_GLOBAL_OPERATORS_2_C
#define CGAL_CARTESIAN_GLOBAL_OPERATORS_2_C

#include <CGAL/Cartesian/redefine_names_2.h>

CGAL_BEGIN_NAMESPACE

template < class R >
inline
PointC2<R CGAL_CTAG>
operator+(const PointC2<R CGAL_CTAG> &p, const VectorC2<R CGAL_CTAG> &v)
{
  return PointC2<R CGAL_CTAG>(p.x() + v.x(), p.y() + v.y());
}

template < class R >
inline
PointC2<R CGAL_CTAG>
operator-(const PointC2<R CGAL_CTAG> &p, const VectorC2<R CGAL_CTAG> &v)
{
  return PointC2<R CGAL_CTAG>(p.x() - v.x(), p.y() - v.y());
}

template < class R >
inline
PointC2<R CGAL_CTAG>
operator+(const Origin &, const VectorC2<R CGAL_CTAG> &v)
{
  return PointC2<R CGAL_CTAG>(v);
}

template < class R >
inline
PointC2<R CGAL_CTAG>
operator-(const Origin &, const VectorC2<R CGAL_CTAG> &v)
{
  return PointC2<R CGAL_CTAG>(-v);
}

template < class R >
inline
VectorC2<R CGAL_CTAG>
operator-(const PointC2<R CGAL_CTAG> &p, const PointC2<R CGAL_CTAG> &q)
{
  return VectorC2<R CGAL_CTAG>(p.x() - q.x(), p.y() - q.y());
}

template < class R >
inline
VectorC2<R CGAL_CTAG>
operator-(const PointC2<R CGAL_CTAG> &p, const Origin &)
{
  return VectorC2<R CGAL_CTAG>(p);
}

template < class R >
inline
VectorC2<R CGAL_CTAG>
operator-(const Origin &, const PointC2<R CGAL_CTAG> &p)
{
  return VectorC2<R CGAL_CTAG>(-p.x(), -p.y());
}

template < class R >
CGAL_KERNEL_INLINE
VectorC2<R CGAL_CTAG>
operator*(const typename R::FT &c, const VectorC2<R CGAL_CTAG> &w)
{
   return VectorC2<R CGAL_CTAG>( c * w.x(), c * w.y());
}

template < class R >
CGAL_KERNEL_INLINE
VectorC2<R CGAL_CTAG>
operator*(const VectorC2<R CGAL_CTAG> &w, const typename R::FT &c)
{
   return VectorC2<R CGAL_CTAG>( c * w.x(), c * w.y());
}

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_GLOBAL_OPERATORS_2_C
