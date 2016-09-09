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
// file          : include/CGAL/bops_Container_Polygon_2.C
// author(s)     :            Wolfgang Freiseisen 
//
// email         : cgal@cs.uu.nl
//
// ============================================================================

#ifndef CGAL_BOPS_CONTAINER_POLYGON_2_C
#define CGAL_BOPS_CONTAINER_POLYGON_2_C


#include <CGAL/bops_simple_polygons_2.h>
#include <CGAL/bops_Container_Polygon_2.h>
#include <CGAL/bops_assertions.h>


/*
   transforms a sequence of special objects
   into a sequence of type CGAL_Object
*/
template <class ForwardIterator, class OutputIterator>
OutputIterator CGAL__transform_to_object(
         ForwardIterator first, ForwardIterator last, OutputIterator result) {
    while (first != last) *result++ = CGAL_make_object(*first++);
    return result;
}




/***********************************/ 
/* For Polygons with traits class: */
/***********************************/ 

template < class ForwardIterator, class Traits > 
bool CGAL_do_intersect(ForwardIterator Afirst, ForwardIterator Alast,
		       ForwardIterator Bfirst, ForwardIterator Blast,
		       Traits &)
{
  typename Traits::Input_polygon A(Afirst,Alast);
  typename Traits::Input_polygon B(Bfirst,Blast);
  
  CGAL_Bops_Simple_Polygons_2_Intersection<Traits> intersection(A,B);
  return intersection.do_intersect();
}


template < class ForwardIterator, class OutputIterator, class Traits > 
OutputIterator CGAL_intersection(
	ForwardIterator Afirst,    // first "polygon", defined by a sequence of points
	ForwardIterator Alast,
	ForwardIterator Bfirst,    // second "polygon"
	ForwardIterator Blast,
	Traits &,                     // traits class
	OutputIterator result    // the result
)
{
  if( Afirst == Alast || Bfirst == Blast )  // if one polygon is empty
    return result;                          // then the intersection is empty

  typename Traits::Input_polygon A(Afirst,Alast);
  typename Traits::Input_polygon B(Bfirst,Blast);
  

  /*** NOT IMPLEMENTED YET
  if( A.size() == 3 && B.size() == 3 ) 
     return CGAL_intersection( CGAL_Triangle_2<Traits::R>(*Afirst++,*Afirst++,*Afirst),
                               CGAL_Triangle_2<Traits::R>(*Bfirst++,*Bfirst++,*Bfirst),
                               result);

  else if( A.is_convex() && B.is_convex() ) 
     return CGAL_intersection_convex_polygons(A, B);
  */

  CGAL_Bops_Simple_Polygons_2_Intersection<Traits> bops(A,B);
  bops.operation();
  return copy(bops.begin(), bops.end(), result);
}



template < class ForwardIterator, class OutputIterator, class Traits > 
OutputIterator CGAL_union(
	ForwardIterator Afirst,    // first "polygon", defined by a sequence of points
	ForwardIterator Alast,
	ForwardIterator Bfirst,    // second "polygon"
	ForwardIterator Blast,
	Traits &,                     // traits class
	OutputIterator result    // the result
)
{
  if( Afirst == Alast ) // if polygon A is empty then return polygon B
    return CGAL__transform_to_object(Bfirst, Blast, result);

  if( Bfirst == Blast ) // if polygon B is empty then return polygon A
    return CGAL__transform_to_object(Afirst, Alast, result);

  typename Traits::Input_polygon A(Afirst,Alast);
  typename Traits::Input_polygon B(Bfirst,Blast);
  CGAL_Bops_Simple_Polygons_2_Union<Traits> bops(A,B);
  bops.operation();
  return copy(bops.begin(), bops.end(), result);
}

template < class ForwardIterator, class OutputIterator, class Traits > 
OutputIterator CGAL_difference(
	ForwardIterator Afirst,    // first "polygon", defined by a sequence of points
	ForwardIterator Alast,
	ForwardIterator Bfirst,    // second "polygon"
	ForwardIterator Blast,
	Traits &,                     // traits class
	OutputIterator result    // the result
)
{
  if( Afirst == Alast ) // if polygon A is empty then the difference is empty
    return result;      

  if( Bfirst == Blast ) // if polygon B is empty then return polygon A
    return CGAL__transform_to_object(Afirst, Alast, result);

  typename Traits::Input_polygon A(Afirst,Alast);
  typename Traits::Input_polygon B(Bfirst,Blast);
  CGAL_Bops_Simple_Polygons_2_Difference<Traits> bops(A,B);
  bops.operation();
  return copy(bops.begin(), bops.end(), result);
}


#endif // CGAL_BOPS_CONTAINER_POLYGON_2_C
