// ============================================================================
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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/bops_Polygon_2.C
// author(s)     :            Wolfgang Freiseisen 
//
// email         : cgal@cs.uu.nl
//
// ============================================================================

#ifndef CGAL_BOPS_POLYGON_2_C
#define CGAL_BOPS_POLYGON_2_C


#include <CGAL/bops_Container_Polygon_2.h>
#include <CGAL/bops_Polygon_2.h>
#include <CGAL/bops_assertions.h>


template < class R, class Container >
bool CGAL_do_intersect( const CGAL_Polygon_2<CGAL_Polygon_traits_2<R>, Container>& A,
                        const CGAL_Polygon_2<CGAL_Polygon_traits_2<R>, Container>& B)
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
  return CGAL_do_intersect(
         A.vertices_begin(), A.vertices_end(),
         B.vertices_begin(), B.vertices_end(),
	 default_traits );
}

 
template < class R, class Container, class OutputIterator >
OutputIterator CGAL_intersection( const CGAL_Polygon_2<CGAL_Polygon_traits_2<R>, Container>& A,
                                  const CGAL_Polygon_2<CGAL_Polygon_traits_2<R>, Container>& B,
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
  return CGAL_intersection(
         A.vertices_begin(), A.vertices_end(),
         B.vertices_begin(), B.vertices_end(),
	 default_traits, result );
}


template < class R, class Container, class OutputIterator >
OutputIterator CGAL_union( const CGAL_Polygon_2<CGAL_Polygon_traits_2<R>, Container>& A,
			   const CGAL_Polygon_2<CGAL_Polygon_traits_2<R>, Container>& B,
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
  return CGAL_union(
         A.vertices_begin(), A.vertices_end(),
         B.vertices_begin(), B.vertices_end(),
	 default_traits, result );
}
 
template < class R, class Container, class OutputIterator >
OutputIterator CGAL_difference( const CGAL_Polygon_2<CGAL_Polygon_traits_2<R>, Container>& A,
		      const CGAL_Polygon_2<CGAL_Polygon_traits_2<R>, Container>& B,
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
  return CGAL_difference(
         A.vertices_begin(), A.vertices_end(),
         B.vertices_begin(), B.vertices_end(),
	 default_traits, result );
} 

#endif // CGAL_BOPS_POLYGON_2_C
