
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
// source        : PV_decl.fw
// file          : include/CGAL/point_vector_declarations_3.h
// package       : _3 (2.8.1)
// revision      : 2.8.1
// revision_date : 07 Nov 1999 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_POINT_VECTOR_DECLARATIONS_3_H
#define CGAL_POINT_VECTOR_DECLARATIONS_3_H

#include <CGAL/user_classes.h>

CGAL_BEGIN_NAMESPACE


template < class R >
inline
Vector_3<R>
point_to_vector_conversion(const Point_3<R>& p);

template < class R >
inline
Point_3<R>
vector_to_point_conversion(const Vector_3<R>& v);

template < class R >
inline
Point_3<R>
operator+(const Point_3<R>& p, const Vector_3<R>& v);

template < class R >
inline
Point_3<R>
operator-(const Point_3<R>& p, const Vector_3<R>& v);

template < class R >
inline
Point_3<R>
operator+(const Origin& , const Vector_3<R>& v);

template < class R >
inline
Point_3<R>
operator-(const Origin& , const Vector_3<R>& v);

template < class R >
inline
Vector_3<R>
operator-(const Point_3<R>& p, const Point_3<R>& q);

template < class R >
inline
Vector_3<R>
operator-(const Point_3<R>& p, const Origin& );

template < class R >
inline
Vector_3<R>
operator-(const Origin& , const Point_3<R>& p);
CGAL_END_NAMESPACE


#endif // CGAL_POINT_VECTOR_DECLARATIONS_3_H
