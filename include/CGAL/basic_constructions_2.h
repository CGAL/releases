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
// release       : CGAL-2.2
// release_date  : 2000, September 30
// 
// source        : basic_constructions_2.fw
// file          : include/CGAL/basic_constructions_2.h
// package       : _2 (3.6)
// revision      : 3.6
// revision_date : 30 Jul 2000 
// author(s)     : Sven Schoenherr
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
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
#include <CGAL/Cartesian/basic_constructions_2.h>
#endif // CGAL_BASIC_CONSTRUCTIONSC2_H
#endif // CGAL_CARTESIAN_H

#ifdef CGAL_SIMPLE_CARTESIAN_H
#include <CGAL/SimpleCartesian/basic_constructionsS2.h>
#endif // CGAL_SIMPLE_CARTESIAN_H


CGAL_BEGIN_NAMESPACE

template < class R >
inline
Point_2<R>
midpoint( const Point_2<R>& p,
          const Point_2<R>& q )
{
    typedef typename R::Point_2_base  RPoint_2;
    return( midpoint( static_cast<const RPoint_2&>(p),
                      static_cast<const RPoint_2&>(q)));
}
template < class R >
inline
Point_2<R>
circumcenter( const Point_2<R>& p,
              const Point_2<R>& q,
              const Point_2<R>& r)
{
    typedef typename R::Point_2_base  RPoint_2;
    return( circumcenter( static_cast<const RPoint_2&>(p),
                          static_cast<const RPoint_2&>(q),
                          static_cast<const RPoint_2&>(r)));
}
CGAL_END_NAMESPACE


#endif // CGAL_BASIC_CONSTRUCTIONS_2_H
