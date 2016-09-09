// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.0
// release_date  : 1999, June 03
// 
// source        : basic_constructions_3.fw
// file          : include/CGAL/basic_constructions_3.h
// package       : _3 (2.1.2)
// revision      : 2.1.2
// revision_date : 21 May 1999 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_BASIC_CONSTRUCTIONS_3_H
#define CGAL_BASIC_CONSTRUCTIONS_3_H

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/basic_constructionsH3.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/basic_constructionsC3.h>
#endif // CGAL_CARTESIAN_H

CGAL_BEGIN_NAMESPACE

template < class R >
inline
Point_3<R>
midpoint( const Point_3<R>& p,
               const Point_3<R>& q )
{
    typedef typename R::Point_3  RPoint_3;
    return( midpoint( CGAL_static_cast( const RPoint_3& , p),
                           CGAL_static_cast( const RPoint_3& , q)));
}
template < class R >
inline
Point_3<R>
circumcenter( const Point_3<R>& p,
                   const Point_3<R>& q,
                   const Point_3<R>& r,
                   const Point_3<R>& s)
{
    typedef typename R::Point_3  RPoint_3;
    return( circumcenter( CGAL_static_cast( const RPoint_3& , p),
                               CGAL_static_cast( const RPoint_3& , q),
                               CGAL_static_cast( const RPoint_3& , r),
                               CGAL_static_cast( const RPoint_3& , s)));
}
CGAL_END_NAMESPACE


#endif // CGAL_BASIC_CONSTRUCTIONS_3_H
