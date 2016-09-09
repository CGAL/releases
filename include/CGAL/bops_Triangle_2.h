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
// file          : include/CGAL/bops_Triangle_2.h
// package       : bops (2.1.5)
// source        : include/CGAL/bops_Triangle_2.h
// revision      : $Revision: WIP $
// revision_date : $Date: Wed Dec  9 13:28:48 MET 1998  $
// author(s)     : Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_BOPS_TRIANGLE2_H
#define CGAL_BOPS_TRIANGLE2_H


#include <CGAL/bops_traits_2.h>
#include <CGAL/Triangle_2.h>

CGAL_BEGIN_NAMESPACE

/* NOT IMPLEMENTED YET
#include <CGAL/Triangle_2_Triangle_2_intersection.h>
bool 
do_intersect( const Triangle_2<R>& A,
                   const Triangle_2<R>& B);
OutputIterator
intersection( const Triangle_2<R>& A,
                   const Triangle_2<R>& B,
                   OutputIterator object_it);
{
  CGAL_bops_precondition_msg( !A.is_degenerate(),
                              "Triangle_2<R> A is degenerated");
  CGAL_bops_precondition_msg( !B.is_degenerate(),
                              "Triangle_2<R> B is degenerated");

  *object_it++= intersection(A,B);
  return object_it;
}
*/


template < class R, class OutputIterator >
OutputIterator
Union(        const Triangle_2<R>& A,
                   const Triangle_2<R>& B,
                   OutputIterator object_it);
 
 
 
template < class R, class OutputIterator >
OutputIterator
difference(   const Triangle_2<R>& A,
                   const Triangle_2<R>& B,
                   OutputIterator list_of_objects_it);
 
CGAL_END_NAMESPACE

#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#include <CGAL/bops_Triangle_2.C>
#endif

#endif // CGAL_BOPS_TRIANGLE2_H
