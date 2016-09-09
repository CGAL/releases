/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/


// Source: boolean_operations_2.C
// Author: Wolfgang Freiseisen
// Last Change by: Carl Van Geem
//                 (CGAL_union on simple polygons added)
 
#ifndef CGAL_BOOLEAN_OPERATIONS_2_C
#define CGAL_BOOLEAN_OPERATIONS_2_C


#include <CGAL/bops_2.h>
#include <CGAL/bops_simple_polygons_2.h>
#include <CGAL/boolean_operations_2.h>

#if 0  //#ifdef __GNUG__
#include <algo.h>
#define transform(_first, _last, _result, _unary_op) \
    while (_first != _last) *_result++ = _unary_op(*_first++);
#endif __GNUG__

/*
   transforms a sequence of special objects
   into a sequence of type CGAL_Object
*/
template <class InputIterator, class OutputIterator>
OutputIterator CGAL__transform_to_object(
         InputIterator first, InputIterator last, OutputIterator result) {
    while (first != last) *result++ = CGAL_make_object(*first++);
    return result;
}



#include <CGAL/intersection_2.h>
/*
#include <CGAL/Triangle_2_Triangle_2_intersection.h>
bool CGAL_do_intersect( const CGAL_Triangle_2<R>& A,
                        const CGAL_Triangle_2<R>& B);
CGAL_Object CGAL_intersection( const CGAL_Triangle_2<R>& A,
                        const CGAL_Triangle_2<R>& B)
NOT IMPLEMENTED YET*/
 
#include <CGAL/Iso_rectangle_2_Iso_rectangle_2_intersection.h>
/*
bool CGAL_do_intersect( const CGAL_Iso_rectangle_2<R>& A,
                        const CGAL_Iso_rectangle_2<R>& B);
CGAL_Object CGAL_intersection( const CGAL_Iso_rectangle_2<R>& A,
                        const CGAL_Iso_rectangle_2<R>& B)
NOT IMPLEMENTED YET*/
/***********************************/ 
/* For Polygons with traits class: */
/***********************************/ 

template < class InputIterator, class I > 
bool CGAL_do_intersect(InputIterator Afirst, InputIterator Alast,
		        InputIterator Bfirst, InputIterator Blast,
		        I &)
{
  I::Polygon A(Afirst,Alast);
  I::Polygon B(Bfirst,Blast);
  
  CGAL_Bops_Simple_Polygons_2_Intersection<I::R,I::Container> intersection(A,B);
  return intersection.do_intersect();
}


template < class InputIterator, class OutputIterator, class I > 
OutputIterator CGAL_intersection(
	InputIterator Afirst,    // first "polygon", defined by a sequence of points
	InputIterator Alast,
	InputIterator Bfirst,    // second "polygon"
	InputIterator Blast,
	I &,                     // traits class
	OutputIterator result    // the result
)
{
  if( Afirst == Alast || Bfirst == Blast )  // if one polygon is empty
    return result;                          // then the intersection is empty

  I::Polygon A(Afirst,Alast);
  I::Polygon B(Bfirst,Blast);
  

  /*** NOT IMPLEMENTED YET
  if( A.size() == 3 && B.size() == 3 ) 
     return CGAL_intersection( CGAL_Triangle_2<I::R>(*Afirst++,*Afirst++,*Afirst),
                               CGAL_Triangle_2<I::R>(*Bfirst++,*Bfirst++,*Bfirst),
                               result);

  else if( A.is_convex() && B.is_convex() ) 
     return CGAL_intersection_convex_polygons(A, B);
  */

  CGAL_Bops_Simple_Polygons_2_Intersection<I::R,I::Container> bops(A,B);
  bops.operation();
  return copy(bops.begin(), bops.end(), result);
}



template < class InputIterator, class OutputIterator, class I > 
OutputIterator CGAL_union(
	InputIterator Afirst,    // first "polygon", defined by a sequence of points
	InputIterator Alast,
	InputIterator Bfirst,    // second "polygon"
	InputIterator Blast,
	I &,                     // traits class
	OutputIterator result    // the result
)
{
  if( Afirst == Alast ) // if polygon A is empty then return polygon B
    return CGAL__transform_to_object(Bfirst, Blast, result);

  if( Bfirst == Blast ) // if polygon B is empty then return polygon A
    return CGAL__transform_to_object(Afirst, Alast, result);

  I::Polygon A(Afirst,Alast);
  I::Polygon B(Bfirst,Blast);
  CGAL_Bops_Simple_Polygons_2_Union<I::R,I::Container> bops(A,B);
  bops.operation();
  return copy(bops.begin(), bops.end(), result);
}

template < class InputIterator, class OutputIterator, class I > 
OutputIterator CGAL_difference(
	InputIterator Afirst,    // first "polygon", defined by a sequence of points
	InputIterator Alast,
	InputIterator Bfirst,    // second "polygon"
	InputIterator Blast,
	I &,                     // traits class
	OutputIterator result    // the result
)
{
  if( Afirst == Alast ) // if polygon A is empty then the difference is empty
    return result;      

  if( Bfirst == Blast ) // if polygon B is empty then return polygon A
    return CGAL__transform_to_object(Afirst, Alast, result);

  I::Polygon A(Afirst,Alast);
  I::Polygon B(Bfirst,Blast);
  CGAL_Bops_Simple_Polygons_2_Difference<I::R,I::Container> bops(A,B);
  bops.operation();
  return copy(bops.begin(), bops.end(), result);
}


/**************************/ 
/* For CGAL Objects only: */
/**************************/ 
#include <CGAL/bops_standard_traits.h>

template < class R, class Container >
bool CGAL_do_intersect( const CGAL_Polygon_2<R, Container>& A,
                        const CGAL_Polygon_2<R, Container>& B)
{
/*
  typedef Bops_default_I<R> TraitsCls;
  TraitsCls trcls;

  typedef CGAL_Polygon_2<R,Container>::Vertex_const_iterator vertex_iterator;
  vertex_iterator Afirst = A.vertices_begin();
  vertex_iterator Alast = A.vertices_end();
  vertex_iterator Bfirst = B.vertices_begin();
  vertex_iterator Blast = B.vertices_end();

  return CGAL_do_intersect(Afirst,Alast,Bfirst,Blast,trcls);
*/
  return CGAL_do_intersect(A.vertices_begin(), A.vertices_end(), B.vertices_begin(), B.vertices_end(),  Bops_default_I<R>() );
}
 
template < class R, class Container, class OutputIterator >
OutputIterator CGAL_intersection( const CGAL_Polygon_2<R, Container>& A,
                        const CGAL_Polygon_2<R, Container>& B,
		        OutputIterator result)
{
  typedef Bops_default_I<R> TraitsCls;
  TraitsCls trcls;

  typedef CGAL_Polygon_2<R,Container>::Vertex_const_iterator vertex_iterator;
  vertex_iterator Afirst = A.vertices_begin();
  vertex_iterator Alast = A.vertices_end();
  vertex_iterator Bfirst = B.vertices_begin();
  vertex_iterator Blast = B.vertices_end();

  return CGAL_intersection(Afirst,Alast,Bfirst,Blast,trcls,result);
}


template < class R, class OutputIterator >
OutputIterator CGAL_union( const CGAL_Triangle_2<R>& A,
                           const CGAL_Triangle_2<R>& B,
		           OutputIterator result)
{
  Bops_default_I<R> traits_class;
  Bops_default_I<R>::Polygon TA(A), TB(B);
  return CGAL_union(
         TA.vertices_begin(), TA.vertices_end(),
         TB.vertices_begin(), TB.vertices_end(),
         traits_class, result);
}
 
template < class R, class OutputIterator >
OutputIterator CGAL_union( const CGAL_Iso_rectangle_2<R>& A,
                           const CGAL_Iso_rectangle_2<R>& B,
		           OutputIterator result)
{
  Bops_default_I<R> traits_class;
  Bops_default_I<R>::Polygon TA(A), TB(B);
  return CGAL_union(
         TA.vertices_begin(), TA.vertices_end(),
         TB.vertices_begin(), TB.vertices_end(),
         traits_class, result);
}
 
template < class R, class Container, class OutputIterator >
OutputIterator CGAL_union( const CGAL_Polygon_2<R, Container>& A,
			   const CGAL_Polygon_2<R, Container>& B,
			   OutputIterator result)
{
  typedef Bops_default_I<R> TraitsCls;
  TraitsCls trcls;

  typedef CGAL_Polygon_2<R,Container>::Vertex_const_iterator vertex_iterator;
  vertex_iterator Afirst = A.vertices_begin();
  vertex_iterator Alast = A.vertices_end();
  vertex_iterator Bfirst = B.vertices_begin();
  vertex_iterator Blast = B.vertices_end();

  return CGAL_union(Afirst,Alast,Bfirst,Blast,trcls,result);
}
 
template < class R, class OutputIterator >
OutputIterator CGAL_difference( const CGAL_Triangle_2<R>& A,
		                const CGAL_Triangle_2<R>& B,
		                OutputIterator result)
{
  Bops_default_I<R> traits_class;
  Bops_default_I<R>::Polygon TA(A), TB(B);
  return CGAL_difference(
         TA.vertices_begin(), TA.vertices_end(),
         TB.vertices_begin(), TB.vertices_end(),
         traits_class, result);
} 
 
template < class R, class OutputIterator >
OutputIterator CGAL_difference( const CGAL_Iso_rectangle_2<R>& A,
			        const CGAL_Iso_rectangle_2<R>& B,
			        OutputIterator result)
{
  Bops_default_I<R> traits_class;
  Bops_default_I<R>::Polygon TA(A), TB(B);
  return CGAL_difference(
         TA.vertices_begin(), TA.vertices_end(),
         TB.vertices_begin(), TB.vertices_end(),
         traits_class, result);
} 
 
template < class R, class Container, class OutputIterator >
OutputIterator CGAL_difference( const CGAL_Polygon_2<R, Container>& A,
		      const CGAL_Polygon_2<R, Container>& B,
		      OutputIterator result)
{
  typedef Bops_default_I<R> TraitsCls;
  TraitsCls trcls;
  
  typedef CGAL_Polygon_2<R,Container>::Vertex_const_iterator vertex_iterator;
  vertex_iterator Afirst = A.vertices_begin();
  vertex_iterator Alast = A.vertices_end();
  vertex_iterator Bfirst = B.vertices_begin();
  vertex_iterator Blast = B.vertices_end();

  return CGAL_difference(Afirst,Alast,Bfirst,Blast,trcls,result);
} 


#endif // CGAL_BOOLEAN_OPERATIONS_2_C
