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
// file          : include/CGAL/basic_constructions_2.h
// package       : _2 (3.19)
// revision      : $Revision: 1.6 $
// revision_date : $Date: 2001/06/20 15:11:38 $
// author(s)     : Sven Schoenherr
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_BASIC_CONSTRUCTIONS_2_H
#define CGAL_BASIC_CONSTRUCTIONS_2_H

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

template < class R >
inline
Point_2<R>
centroid( const Point_2<R>& p,
          const Point_2<R>& q,
          const Point_2<R>& r)
{
    typedef typename R::Point_2_base  RPoint_2;
    return( centroid( static_cast<const RPoint_2&>(p),
                      static_cast<const RPoint_2&>(q),
                      static_cast<const RPoint_2&>(r)));
}

template < class R >
inline
Point_2<R>
centroid( const Point_2<R>& p,
          const Point_2<R>& q,
          const Point_2<R>& r,
          const Point_2<R>& s)
{
    typedef typename R::Point_2_base  RPoint_2;
    return( centroid( static_cast<const RPoint_2&>(p),
                      static_cast<const RPoint_2&>(q),
                      static_cast<const RPoint_2&>(r),
                      static_cast<const RPoint_2&>(s)));
}

CGAL_END_NAMESPACE

#endif // CGAL_BASIC_CONSTRUCTIONS_2_H
