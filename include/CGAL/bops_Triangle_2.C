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
// file          : include/CGAL/bops_Triangle_2.C
// package       : bops (2.4)
// source        : include/CGAL/bops_Triangle_2.C
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

CGAL_BEGIN_NAMESPACE 

/*
#include <CGAL/Triangle_2_Triangle_2_intersection.h>
bool do_intersect( const Triangle_2<R>& A,
                        const Triangle_2<R>& B);
Object intersection( const Triangle_2<R>& A,
                        const Triangle_2<R>& B)
see 'CGAL/Triangle_2_Triangle_2_intersection.h'
*/
 

template < class R, class OutputIterator >
OutputIterator Union( const Triangle_2<R>& A,
                           const Triangle_2<R>& B,
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

  return Union( cA.begin(), cA.end(), cB.begin(), cB.end(),
	 default_traits, result );
}
 
 
template < class R, class OutputIterator >
OutputIterator difference( const Triangle_2<R>& A,
		                const Triangle_2<R>& B,
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

  return difference( cA.begin(), cA.end(), cB.begin(), cB.end(),
	 default_traits, result );
} 
 
CGAL_END_NAMESPACE

#endif // CGAL_BOPS_TRIANGLE_2_C
