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
// file          : include/CGAL/bops_Container_Polygon_2.C
// package       : bops (2.4)
// source        : include/CGAL/bops_Container_Polygon_2.C
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

#ifndef CGAL_BOPS_CONTAINER_POLYGON_2_C
#define CGAL_BOPS_CONTAINER_POLYGON_2_C


#include <CGAL/bops_simple_polygons_2.h>
#include <CGAL/bops_Convex_Polygon_2.h>
#include <CGAL/bops_Container_Polygon_2.h>
#include <CGAL/bops_assertions.h>

CGAL_BEGIN_NAMESPACE

/*
   transforms a sequence of special objects
   into a sequence of type Object
*/
template <class ForwardIterator, class OutputIterator>
OutputIterator _transform_to_object(
         ForwardIterator first, ForwardIterator last, OutputIterator result) {
    while (first != last) *result++ = make_object(*first++);
    return result;
}




/***********************************/ 
/* For Polygons with traits class: */
/***********************************/ 

template < class ForwardIterator, class Traits > 
bool do_intersect(ForwardIterator Afirst, ForwardIterator Alast,
		       ForwardIterator Bfirst, ForwardIterator Blast,
		       Traits &)
{
  typename Traits::Input_polygon A(Afirst,Alast);
  typename Traits::Input_polygon B(Bfirst,Blast);
  
  Bops_Simple_Polygons_2_Intersection<Traits> intersection(A,B);
  return intersection.do_intersect();
}


template < class ForwardIterator, class OutputIterator, class Traits > 
OutputIterator intersection(
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
     return intersection(
	Triangle_2<Traits::R>(*Afirst++,*Afirst++,*Afirst),
        Triangle_2<Traits::R>(*Bfirst++,*Bfirst++,*Bfirst),
        result);
  */
  
	Bops_Polygons_2<Traits> *bops;
  
	if( A.is_convex() && B.is_convex() )
		bops= new Bops_Convex_Polygons_2_Intersection<Traits>(A,B);
	else
		bops= new Bops_Simple_Polygons_2_Intersection<Traits>(A,B);
		
  	bops->operation();
	std::copy(bops->begin(), bops->end(), result);
	
	return result;
}



template < class ForwardIterator, class OutputIterator, class Traits > 
OutputIterator Union(
	ForwardIterator Afirst,    // first "polygon", defined by a sequence of points
	ForwardIterator Alast,
	ForwardIterator Bfirst,    // second "polygon"
	ForwardIterator Blast,
	Traits &,                     // traits class
	OutputIterator result    // the result
)
{
  if( Afirst == Alast ) // if polygon A is empty then return polygon B
    return _transform_to_object(Bfirst, Blast, result);

  if( Bfirst == Blast ) // if polygon B is empty then return polygon A
    return _transform_to_object(Afirst, Alast, result);

  typename Traits::Input_polygon A(Afirst,Alast);
  typename Traits::Input_polygon B(Bfirst,Blast);
  Bops_Simple_Polygons_2_Union<Traits> bops(A,B);
  bops.operation();
  return std::copy(bops.begin(), bops.end(), result);
}

template < class ForwardIterator, class OutputIterator, class Traits > 
OutputIterator difference(
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
    return _transform_to_object(Afirst, Alast, result);

  typename Traits::Input_polygon A(Afirst,Alast);
  typename Traits::Input_polygon B(Bfirst,Blast);
  Bops_Simple_Polygons_2_Difference<Traits> bops(A,B);
  bops.operation();
  return std::copy(bops.begin(), bops.end(), result);
}

CGAL_END_NAMESPACE

#endif // CGAL_BOPS_CONTAINER_POLYGON_2_C
