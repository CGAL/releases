// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/Cartesian/global_operators_2.h
// package       : Cartesian_kernel (6.59)
// revision      : $Revision: 1.7 $
// revision_date : $Date: 2002/01/23 17:59:13 $
// author(s)     : Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_GLOBAL_OPERATORS_2_H
#define CGAL_CARTESIAN_GLOBAL_OPERATORS_2_H

CGAL_BEGIN_NAMESPACE

template < class R >
inline
typename R::Point_2
operator+(const PointC2<R> &p, const VectorC2<R> &v)
{
  return PointC2<R>(p.x() + v.x(), p.y() + v.y());
}

template < class R >
inline
typename R::Point_2
operator-(const PointC2<R> &p, const VectorC2<R> &v)
{
  return PointC2<R>(p.x() - v.x(), p.y() - v.y());
}

template < class R >
inline
typename R::Point_2
operator+(const Origin &, const VectorC2<R> &v)
{
  return PointC2<R>(v);
}

template < class R >
inline
typename R::Point_2
operator-(const Origin &, const VectorC2<R> &v)
{
  return PointC2<R>(-v);
}

template < class R >
inline
typename R::Vector_2
operator-(const PointC2<R> &p, const PointC2<R> &q)
{
  return VectorC2<R>(p.x() - q.x(), p.y() - q.y());
}

template < class R >
inline
typename R::Vector_2
operator-(const PointC2<R> &p, const Origin &)
{
  return VectorC2<R>(p);
}

template < class R >
inline
typename R::Vector_2
operator-(const Origin &, const PointC2<R> &p)
{
  return VectorC2<R>(-p.x(), -p.y());
}

template < class R >
CGAL_KERNEL_INLINE
typename R::Vector_2
operator*(const typename R::FT &c, const VectorC2<R> &w)
{
   return VectorC2<R>(c * w.x(), c * w.y());
}

template < class R >
CGAL_KERNEL_INLINE
typename R::Vector_2
operator*(const VectorC2<R> &w, const typename R::FT &c)
{
   return VectorC2<R>(c * w.x(), c * w.y());
}

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_GLOBAL_OPERATORS_2_H
