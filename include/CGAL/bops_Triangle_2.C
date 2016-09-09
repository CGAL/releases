//  -*- Mode: c++ -*-
// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
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
// file          : include/CGAL/bops_Triangle_2.C
// package       : bops (1.1.2)
// source        : include/CGAL/bops_Triangle_2.C
// revision      : $Revision: 1.1.2 $
// revision_date : $Date: Wed Dec  9 13:28:47 MET 1998  $
// author(s)     :             Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_BOPS_TRIANGLE_2_C
#define CGAL_BOPS_TRIANGLE_2_C

//#define CGAL__BOPS_USE_STANDARD_CODE
   // if CGAL__BOPS_USE_STANDARD_CODE is defined, then the
   // code for simple polygons will be used for computing 
   // BOPS on iso-rectangles and triangles.

#include <CGAL/bops_simple_polygons_2.h>
#include <CGAL/bops_Container_Polygon_2.h>

#include<CGAL/bops_Triangle_2.h>
#include <CGAL/bops_assertions.h>

/*
#include <CGAL/Triangle_2_Triangle_2_intersection.h>
bool CGAL_do_intersect( const CGAL_Triangle_2<R>& A,
                        const CGAL_Triangle_2<R>& B);
CGAL_Object CGAL_intersection( const CGAL_Triangle_2<R>& A,
                        const CGAL_Triangle_2<R>& B)
see 'CGAL/Triangle_2_Triangle_2_intersection.h'
*/
 

template < class R, class OutputIterator >
OutputIterator CGAL_union( const CGAL_Triangle_2<R>& A,
                           const CGAL_Triangle_2<R>& B,
		           OutputIterator result)
{
  CGAL_bops_precondition_msg( !A.is_degenerate(),
                              "Triangle_2<R> A is degenerated");
  CGAL_bops_precondition_msg( !B.is_degenerate(),
                              "Triangle_2<R> B is degenerated");

  Bops_default_I<R> default_traits;
  typedef typename Bops_default_I<R>::Input_polygon_container input;
  input cA, cB;
  back_insert_iterator<input> inA(cA), inB(cB);
  for(int i= 0; i<3; i++) { *inA++ = A[i]; *inB++ = B[i]; }

  return CGAL_union( cA.begin(), cA.end(), cB.begin(), cB.end(),
	 default_traits, result );
}
 
 
template < class R, class OutputIterator >
OutputIterator CGAL_difference( const CGAL_Triangle_2<R>& A,
		                const CGAL_Triangle_2<R>& B,
		                OutputIterator result)
{
  CGAL_bops_precondition_msg( !A.is_degenerate(),
                              "Triangle_2<R> A is degenerated");
  CGAL_bops_precondition_msg( !B.is_degenerate(),
                              "Triangle_2<R> B is degenerated");

  Bops_default_I<R> default_traits;
  typedef typename Bops_default_I<R>::Input_polygon_container input;
  input cA, cB;
  back_insert_iterator<input> inA(cA), inB(cB);
  for(int i= 0; i<3; i++) { *inA++= A[i]; *inB++= B[i]; }

  return CGAL_difference( cA.begin(), cA.end(), cB.begin(), cB.end(),
	 default_traits, result );
} 
 

#endif // CGAL_BOPS_TRIANGLE_2_C
