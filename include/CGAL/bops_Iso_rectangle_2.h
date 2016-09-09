// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// file          : include/CGAL/bops_Iso_rectangle_2.h
// package       : bops (2.4)
// source        : include/CGAL/bops_Iso_rectangle_2.h
// revision      : $Revision: 1.1.1.1 $
// revision_date : $Date: 1999/10/11 13:50:31 $
// author(s)     : Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_BOPS_ISO_RECTANGLE_2_H
#define CGAL_BOPS_ISO_RECTANGLE_2_H

#include <CGAL/bops_traits_2.h>
#include <CGAL/bops_assertions.h>


#include <CGAL/Iso_rectangle_2_Iso_rectangle_2_intersection.h>

CGAL_BEGIN_NAMESPACE

/*
bool 
do_intersect( const Iso_rectangle_2<R>& A,
                   const Iso_rectangle_2<R>& B);
*/

template < class R, class OutputIterator >
inline OutputIterator
intersection( const Iso_rectangle_2<R>& A,
                   const Iso_rectangle_2<R>& B,
                   OutputIterator object_it) {
  CGAL_bops_precondition_msg( !A.is_degenerate(),
                              "Iso_rectangle_2<R> A is degenerated");
  CGAL_bops_precondition_msg( !B.is_degenerate(),
                              "Iso_rectangle_2<R> B is degenerated");

  *object_it++= intersection(A,B);
  return object_it;
}


template < class R, class OutputIterator >
OutputIterator
Union(        const Iso_rectangle_2<R>& A,
                   const Iso_rectangle_2<R>& B,
                   OutputIterator object_it);
 
 
template < class R, class OutputIterator >
OutputIterator
difference(   const Iso_rectangle_2<R>& A,
                   const Iso_rectangle_2<R>& B,
                   OutputIterator object_it);
 
CGAL_END_NAMESPACE

#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#include <CGAL/bops_Iso_rectangle_2.C>
#endif

#endif // CGAL_BOPS_ISO_RECTANGLE_2_H
