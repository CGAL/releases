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
// file          : include/CGAL/bops_Polygon_2.C
// package       : bops (2.4)
// source        : include/CGAL/bops_Polygon_2.C
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

#ifndef CGAL_BOPS_POLYGON_2_C
#define CGAL_BOPS_POLYGON_2_C

#include <CGAL/bops_Container_Polygon_2.h>
#include <CGAL/bops_Polygon_2.h>
#include <CGAL/bops_assertions.h>
#include <CGAL/bops_Convex_Polygon_2.h>

CGAL_BEGIN_NAMESPACE

template < class R, class Container >
bool do_intersect(
     const Polygon_2<Polygon_traits_2<R>, Container>& A,
     const Polygon_2<Polygon_traits_2<R>, Container>& B)
{
  CGAL_bops_precondition_msg(A.is_simple(),
                             "Polygon_2<R> A is not simple");
  CGAL_bops_precondition_msg(B.is_simple(),
                             "Polygon_2<R> B is not simple");
  CGAL_bops_precondition_msg(A.is_counterclockwise_oriented(),
                             "Polygon_2<R> A is not counterclockwise oriented");
  CGAL_bops_precondition_msg(B.is_counterclockwise_oriented(),
                             "Polygon_2<R> B is not counterclockwise oriented");

  Bops_default_I<R> default_traits;
  return do_intersect(
         A.vertices_begin(), A.vertices_end(),
         B.vertices_begin(), B.vertices_end(),
	 default_traits );
}

 
template < class R, class Container, class OutputIterator >
OutputIterator intersection(
       const Polygon_2<Polygon_traits_2<R>, Container>& A,
       const Polygon_2<Polygon_traits_2<R>, Container>& B,
       OutputIterator result)
{
  CGAL_bops_precondition_msg(A.is_simple(),
                             "Polygon_2<R> A is not simple");
  CGAL_bops_precondition_msg(B.is_simple(),
                             "Polygon_2<R> B is not simple");
  CGAL_bops_precondition_msg(A.is_counterclockwise_oriented(),
                             "Polygon_2<R> A is not counterclockwise oriented");
  CGAL_bops_precondition_msg(B.is_counterclockwise_oriented(),
                             "Polygon_2<R> B is not counterclockwise oriented");


  if( A.is_convex() && B.is_convex() ) {
     Polygon_2<Polygon_traits_2<R>, Container> C, AA(A), BB(B);
     C= Convex_Intersection(AA, BB);
     result++ = make_object(C);
     return result;
  }

  Bops_default_I<R> default_traits;
  return intersection(
         A.vertices_begin(), A.vertices_end(),
         B.vertices_begin(), B.vertices_end(),
	 default_traits, result );
}


template < class R, class Container, class OutputIterator >
OutputIterator Union(
      const Polygon_2<Polygon_traits_2<R>, Container>& A,
      const Polygon_2<Polygon_traits_2<R>, Container>& B,
      OutputIterator result)
{
  CGAL_bops_precondition_msg(A.is_simple(),
                             "Polygon_2<R> A is not simple");
  CGAL_bops_precondition_msg(B.is_simple(),
                             "Polygon_2<R> B is not simple");
  CGAL_bops_precondition_msg(A.is_counterclockwise_oriented(),
                             "Polygon_2<R> A is not counterclockwise oriented");
  CGAL_bops_precondition_msg(B.is_counterclockwise_oriented(),
                             "Polygon_2<R> B is not counterclockwise oriented");

  Bops_default_I<R> default_traits;
  return Union(
         A.vertices_begin(), A.vertices_end(),
         B.vertices_begin(), B.vertices_end(),
	 default_traits, result );
}
 
template < class R, class Container, class OutputIterator >
OutputIterator difference(
	       const Polygon_2<Polygon_traits_2<R>, Container>& A,
	       const Polygon_2<Polygon_traits_2<R>, Container>& B,
	       OutputIterator result)
{
  CGAL_bops_precondition_msg(A.is_simple(),
                             "Polygon_2<R> A is not simple");
  CGAL_bops_precondition_msg(B.is_simple(),
                             "Polygon_2<R> B is not simple");
  CGAL_bops_precondition_msg(A.is_counterclockwise_oriented(),
                             "Polygon_2<R> A is not counterclockwise oriented");
  CGAL_bops_precondition_msg(B.is_counterclockwise_oriented(),
                             "Polygon_2<R> B is not counterclockwise oriented");

  Bops_default_I<R> default_traits;
  return difference(
         A.vertices_begin(), A.vertices_end(),
         B.vertices_begin(), B.vertices_end(),
	 default_traits, result );
} 

CGAL_END_NAMESPACE

#endif // CGAL_BOPS_POLYGON_2_C
