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
// file          : include/CGAL/bops_Polygon_2.h
// package       : bops (2.1.5)
// source        : include/CGAL/bops_Polygon_2.h
// revision      : $Revision: WIP $
// revision_date : $Date: Wed Dec  9 13:28:47 MET 1998  $
// author(s)     : Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_BOPS_POLYGON_2_H
#define CGAL_BOPS_POLYGON_2_H


#include <CGAL/bops_traits_2.h>

CGAL_BEGIN_NAMESPACE

template < class R, class Container >
bool do_intersect(
     const Polygon_2<Polygon_traits_2<R>, Container>& A,
     const Polygon_2<Polygon_traits_2<R>, Container>& B
);


template < class R, class Container, class OutputIterator >
OutputIterator
intersection( const Polygon_2<Polygon_traits_2<R>, Container>& A,
                   const Polygon_2<Polygon_traits_2<R>, Container>& B,
                   OutputIterator list_of_objects_it);

 
template < class R, class Container, class OutputIterator >
OutputIterator
UnionXS(        const Polygon_2<Polygon_traits_2<R>, Container>& A,
                   const Polygon_2<Polygon_traits_2<R>, Container>& B,
                   OutputIterator list_of_objects_it);
 
 
template < class R, class Container, class OutputIterator >
OutputIterator
difference(   const Polygon_2<Polygon_traits_2<R>, Container>& A,
                   const Polygon_2<Polygon_traits_2<R>, Container>& B,
                   OutputIterator list_of_objects_it);

CGAL_END_NAMESPACE

#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#include <CGAL/bops_Polygon_2.C>
#endif

#endif // CGAL_BOPS_POLYGON_2_H
