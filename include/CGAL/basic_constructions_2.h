// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-1.2
// release_date  : 1999, January 18
// 
// source        : basic_constructions_2.fw
// file          : include/CGAL/basic_constructions_2.h
// package       : _2 (1.3)
// revision      : 1.3
// revision_date : 15 Dec 1998 
// author(s)     : Sven Schoenherr
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
//
// email         : cgal@cs.uu.nl
//
// ======================================================================
 

#ifndef CGAL_BASIC_CONSTRUCTIONS_2_H
#define CGAL_BASIC_CONSTRUCTIONS_2_H 1

#ifdef CGAL_HOMOGENEOUS_H
#ifndef CGAL_BASIC_CONSTRUCTIONSH2_H
#include <CGAL/basic_constructionsH2.h>
#endif // CGAL_BASIC_CONSTRUCTIONSH2_H
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#ifndef CGAL_BASIC_CONSTRUCTIONSC2_H
#include <CGAL/basic_constructionsC2.h>
#endif // CGAL_BASIC_CONSTRUCTIONSC2_H
#endif // CGAL_CARTESIAN_H

template < class R >
inline
CGAL_Point_2<R>
CGAL_midpoint( const CGAL_Point_2<R>& p,
               const CGAL_Point_2<R>& q )
{
    typedef typename R::Point_2  Point_2;
    return( CGAL_midpoint( CGAL_static_cast( const Point_2&, p),
                           CGAL_static_cast( const Point_2&, q)));
}
template < class R >
inline
CGAL_Point_2<R>
CGAL_circumcenter( const CGAL_Point_2<R>& p,
                   const CGAL_Point_2<R>& q,
                   const CGAL_Point_2<R>& r)
{
    typedef typename R::Point_2  Point_2;
    return( CGAL_circumcenter( CGAL_static_cast( const Point_2&, p),
                               CGAL_static_cast( const Point_2&, q),
                               CGAL_static_cast( const Point_2&, r)));
}

#endif // CGAL_BASIC_CONSTRUCTIONS_2_H
