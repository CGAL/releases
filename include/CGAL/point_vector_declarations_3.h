
// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// file          : include/CGAL/point_vector_declarations_3.h
// package       : _3 (3.23)
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2001/06/21 08:16:39 $
// author(s)     : Stefan Schirra
//
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_POINT_VECTOR_DECLARATIONS_3_H
#define CGAL_POINT_VECTOR_DECLARATIONS_3_H

#include <CGAL/user_classes.h>

CGAL_BEGIN_NAMESPACE

template < class R >
inline
Vector_3<R>
point_to_vector_conversion(const Point_3<R>& p)
{ return Vector_3<R>(p); }

template < class R >
inline
Point_3<R>
vector_to_point_conversion(const Vector_3<R>& v)
{ return Point_3<R>(v); }

template < class R >
inline
Point_3<R>
operator+(const Point_3<R>& p, const Vector_3<R>& v)
{
  typedef typename  R::Point_3_base  RPoint_3;
  typedef typename  R::Vector_3_base  RVector_3;
  return Point_3<R>(static_cast<const RPoint_3&>(p) +
                    static_cast<const RVector_3&>(v)) ;
}

template < class R >
inline
Point_3<R>
operator-(const Point_3<R>& p, const Vector_3<R>& v)
{
  typedef typename  R::Point_3_base  RPoint_3;
  typedef typename  R::Vector_3_base  RVector_3;
  return Point_3<R>(static_cast<const RPoint_3&>(p) -
                    static_cast<const RVector_3&>(v));
}

template < class R >
inline
Point_3<R>
operator+(const Origin& , const Vector_3<R>& v)
{ return vector_to_point_conversion(v) ; }

template < class R >
inline
Point_3<R>
operator-(const Origin& , const Vector_3<R>& v)
{ return vector_to_point_conversion(-v) ; }

template < class R >
inline
Vector_3<R>
operator-(const Point_3<R>& p, const Point_3<R>& q)
{
  typedef typename  R::Point_3_base  RPoint_3;
  return Vector_3<R>(static_cast<const RPoint_3&>(p) -
                     static_cast<const RPoint_3&>(q));
}

template < class R >
inline
Vector_3<R>
operator-(const Point_3<R>& p, const Origin& )
{ return point_to_vector_conversion(p) ; }

template < class R >
inline
Vector_3<R>
operator-(const Origin& , const Point_3<R>& p)
{
  typedef typename  R::Point_3_base  RPoint_3;
  return Vector_3<R>(ORIGIN - static_cast<const RPoint_3&>(p));
}

CGAL_END_NAMESPACE

#endif // CGAL_POINT_VECTOR_DECLARATIONS_3_H
